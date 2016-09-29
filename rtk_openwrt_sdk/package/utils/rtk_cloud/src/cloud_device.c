#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "http.h"
#include "xml.h"

#define CLOUD_ENTRANCE	"176.34.62.248"
#define CLOUD_PORT	80

typedef enum _DEVICE_TYPE {
	DEVICE_LIGHT = 1,
	DEVICE_SENSOR,
} DEVICE_TYPE;

static char *device_id = NULL;
static char *device_secrete = NULL;
static char *server_instance = NULL;
static char *proxy_key = NULL;
static int device_type = 0;

static void dump_msg(char *title, char *request, int length)
{
	int i;

	printf("%s\n", title);
	
	for(i = 0; i < length; i ++) {
		if(request[i] == '\r')
			printf("\\r ");
		else if(request[i] == '\n')
			printf("\\n ");
		else
			printf("%c", request[i]);
	}

	printf("\n\n");
}

static char *loadbalance_lookup_address(void)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns, *public_address = NULL;
	char response_buf[1024];
	int read_size, ret = -1;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_instance);
	server_addr.sin_port = ntohs(CLOUD_PORT);

	if(connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		return NULL;

	//Build XML Request Document Tree
	default_ns = (char *) malloc(strlen("http://") + strlen(server_instance) + strlen("/Location") + 1);
	sprintf(default_ns, "http://%s/Location", server_instance);
	request_root = xml_new_element(NULL, "LookupAddress", default_ns);
	auth_node = xml_new_element(NULL, "Authentication", NULL);
	id_node = xml_new_element(NULL, "Id", NULL);
	secrete_node = xml_new_element(NULL, "Secrete", NULL);
	xml_add_child(request_root, auth_node);
	xml_add_child(auth_node, id_node);
	xml_add_child(auth_node, secrete_node);
	xml_add_child(id_node, xml_new_text(device_id));
	xml_add_child(secrete_node, xml_new_text(device_secrete));
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/location", "text/xml", (int) strlen(xml_request));
	write(server_socket, header, strlen(header));
	dump_msg("\nsend http header:", header, strlen(header));
	http_free(header);
	write(server_socket, xml_request, strlen(xml_request));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
	xml_free(xml_request);

	//Read HTTP
	if((read_size = read(server_socket, response_buf, sizeof(response_buf))) != 0) {
		struct xml_node *response_root, *address_text;
		struct xml_node_set *node_set;
		char *http_header, *http_body;

		if((http_header = http_response_header(response_buf, read_size)) != NULL) {
			dump_msg("\nrecv http header:", http_header, strlen(http_header));
			http_free(http_header);
		}

		if((http_body = http_response_body(response_buf, read_size)) != NULL) {
			dump_msg("recv http body:", http_body, strlen(http_body));
			http_free(http_body);
		}

		if((response_root = xml_parse_doc(response_buf, read_size, NULL, "LookupAddressResponse", default_ns)) != NULL) {
			node_set = xml_find_path(response_root, "/LookupAddressResponse/PublicAddress");

			if(node_set->count) {
				address_text = xml_text_child(node_set->node[0]);

				if(address_text) {
					public_address = (char *) malloc(strlen(address_text->text) + 1);
					strcpy(public_address, address_text->text);
					//printf("My Public IP Address: %s\n", public_address);
				}
			}

			xml_delete_set(node_set);
			xml_delete_tree(response_root);
		}
	}

	free(default_ns);
	close(server_socket);

	return public_address;
}

static int loadbalance_get_instance(void)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns;
	char response_buf[512];
	int read_size, ret = -1;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(CLOUD_ENTRANCE);
	server_addr.sin_port = ntohs(CLOUD_PORT);

	if(connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		close(server_socket);
		return -1;
	}

	//Build XML Request Document Tree
	default_ns = (char *) malloc(strlen("http://") + strlen(CLOUD_ENTRANCE) + strlen("/LoadBalance") + 1);
	sprintf(default_ns, "http://%s/LoadBalance", CLOUD_ENTRANCE);
	request_root = xml_new_element(NULL, "GetServerInstance", default_ns);
	auth_node = xml_new_element(NULL, "Authentication", NULL);
	id_node = xml_new_element(NULL, "Id", NULL);
	secrete_node = xml_new_element(NULL, "Secrete", NULL);
	xml_add_child(request_root, auth_node);
	xml_add_child(auth_node, id_node);
	xml_add_child(auth_node, secrete_node);
	xml_add_child(id_node, xml_new_text(device_id));
	xml_add_child(secrete_node, xml_new_text(device_secrete));
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(CLOUD_ENTRANCE, "/cgi-bin/load_balance", "text/xml", (int) strlen(xml_request));
	dump_msg("\nsend http header:", header, strlen(header));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
	write(server_socket, header, strlen(header));
	write(server_socket, xml_request, strlen(xml_request));
	http_free(header);
	xml_free(xml_request);

	//Read HTTP
	if((read_size = read(server_socket, response_buf, sizeof(response_buf))) != 0) {
		struct xml_node *response_root, *instance_text;
		struct xml_node_set *node_set;
		char *http_header, *http_body;

		if((http_header = http_response_header(response_buf, read_size)) != NULL) {
			dump_msg("\nrecv http header:", http_header, strlen(http_header));
			http_free(http_header);
		}

		if((http_body = http_response_body(response_buf, read_size)) != NULL) {
			dump_msg("recv http body:", http_body, strlen(http_body));
			http_free(http_body);
		}

		if((response_root = xml_parse_doc(response_buf, read_size, NULL, "GetServerInstanceResponse", default_ns)) != NULL) {
			node_set = xml_find_path(response_root, "/GetServerInstanceResponse/Instance");

			if(node_set->count) {
				instance_text = xml_text_child(node_set->node[0]);

				if(instance_text) {
					server_instance = (char *) malloc(strlen(instance_text->text) + 1);
					strcpy(server_instance, instance_text->text);
					ret = 0;
				}
			}

			xml_delete_set(node_set);
			xml_delete_tree(response_root);
		}
	}

	free(default_ns);
	close(server_socket);

	return ret;
}

static int message_apply_proxy(void)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns;
	char response_buf[512];
	int read_size, ret = -1;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node, *proxy_type_node;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_instance);
	server_addr.sin_port = ntohs(CLOUD_PORT);

	if(connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		close(server_socket);
		return -1;
	}

	//Build XML Request Document Tree
	default_ns = (char *) malloc(strlen("http://") + strlen(server_instance) + strlen("/GenericMessage") + 1);
	sprintf(default_ns, "http://%s/GenericMessage", server_instance);
	request_root = xml_new_element(NULL, "ApplyProxy", default_ns);
	auth_node = xml_new_element(NULL, "Authentication", NULL);
	id_node = xml_new_element(NULL, "Id", NULL);
	secrete_node = xml_new_element(NULL, "Secrete", NULL);
	proxy_type_node = xml_new_element(NULL, "ProxyType", NULL);
	xml_add_child(request_root, auth_node);
	xml_add_child(auth_node, id_node);
	xml_add_child(auth_node, secrete_node);
	xml_add_child(id_node, xml_new_text(device_id));
	xml_add_child(secrete_node, xml_new_text(device_secrete));
	xml_add_child(request_root, proxy_type_node);
	xml_add_child(proxy_type_node, xml_new_text("DeviceProxy"));	//ProxyType for device should be "DeviceProxy"
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	dump_msg("\nsend http header:", header, strlen(header));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
	write(server_socket, header, strlen(header));
	write(server_socket, xml_request, strlen(xml_request));
	http_free(header);
	xml_free(xml_request);

	//Read HTTP
	if((read_size = read(server_socket, response_buf, sizeof(response_buf))) != 0) {
		struct xml_node *response_root;
		struct xml_node_set *node_set;
		char *http_header, *http_body;

		if((http_header = http_response_header(response_buf, read_size)) != NULL) {
			dump_msg("\nrecv http header:", http_header, strlen(http_header));
			http_free(http_header);
		}

		if((http_body = http_response_body(response_buf, read_size)) != NULL) {
			dump_msg("recv http body:", http_body, strlen(http_body));
			http_free(http_body);
		}

		if((response_root = xml_parse_doc(response_buf, read_size, NULL, "ApplyProxyResponse", default_ns)) != NULL) {
			node_set = xml_find_path(response_root, "/ApplyProxyResponse/ProxyKey");

			if(node_set->count) {
				struct xml_node *proxy_text = xml_text_child(node_set->node[0]);

				if(proxy_text) {
					proxy_key = (char *) malloc(strlen(proxy_text->text) + 1);
					strcpy(proxy_key, proxy_text->text);
					ret = 0;
				}
			}

			xml_delete_set(node_set);
			xml_delete_tree(response_root);
		}
	}

	free(default_ns);
	close(server_socket);

	return ret;
}

static void message_release_proxy(void)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns;
	char response_buf[512];
	int read_size;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node, *proxy_type_node, *proxy_key_node;

	if((proxy_key == NULL) || (server_instance == NULL))
		return;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_instance);
	server_addr.sin_port = ntohs(CLOUD_PORT);

	if(connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		close(server_socket);
		return;
	}

	//Build XML Request Document Tree
	default_ns = (char *) malloc(strlen("http://") + strlen(server_instance) + strlen("/GenericMessage") + 1);
	sprintf(default_ns, "http://%s/GenericMessage", server_instance);
	request_root = xml_new_element(NULL, "ReleaseProxy", default_ns);
	auth_node = xml_new_element(NULL, "Authentication", NULL);
	id_node = xml_new_element(NULL, "Id", NULL);
	secrete_node = xml_new_element(NULL, "Secrete", NULL);
	proxy_type_node = xml_new_element(NULL, "ProxyType", NULL);
	proxy_key_node = xml_new_element(NULL, "ProxyKey", NULL);
	xml_add_child(request_root, auth_node);
	xml_add_child(auth_node, id_node);
	xml_add_child(auth_node, secrete_node);
	xml_add_child(id_node, xml_new_text(device_id));
	xml_add_child(secrete_node, xml_new_text(device_secrete));
	xml_add_child(request_root, proxy_type_node);
	xml_add_child(proxy_type_node, xml_new_text("DeviceProxy"));	//ProxyType for device should be "DeviceProxy"
	xml_add_child(request_root, proxy_key_node);
	xml_add_child(proxy_key_node, xml_new_text(proxy_key));
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	dump_msg("\nsend http header:", header, strlen(header));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
	write(server_socket, header, strlen(header));
	write(server_socket, xml_request, strlen(xml_request));
	http_free(header);
	xml_free(xml_request);

	//Read HTTP
	if((read_size = read(server_socket, response_buf, sizeof(response_buf))) != 0) {
		struct xml_node *response_root, *instance_text;
		struct xml_node_set *node_set;
		char *http_header, *http_body;

		if((http_header = http_response_header(response_buf, read_size)) != NULL) {
			dump_msg("\nrecv http header:", http_header, strlen(http_header));
			http_free(http_header);
		}

		if((http_body = http_response_body(response_buf, read_size)) != NULL) {
			dump_msg("recv http body:", http_body, strlen(http_body));
			http_free(http_body);
		}
	}

	free(default_ns);
	close(server_socket);
}

void message_forward_message(char *type, char *application_content, char *reply_key, char *status_rule)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns, *doc_prefix = NULL, *doc_name = NULL, *doc_uri = NULL;
	char response_buf[512];
	int read_size;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node, *message_node, *type_node, *content_node, *application_root, *reply_key_node, *status_rule_node;

	if(xml_doc_name(application_content, strlen(application_content), &doc_prefix, &doc_name, &doc_uri) == -1)
		return;

	if((application_root = xml_parse_doc(application_content, strlen(application_content), doc_prefix, doc_name, doc_uri)) == NULL)
		return;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_instance);
	server_addr.sin_port = ntohs(CLOUD_PORT);

	if(connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		close(server_socket);
		return;
	}

	//Build XML Request Document Tree
	default_ns = (char *) malloc(strlen("http://") + strlen(server_instance) + strlen("/GenericMessage") + 1);
	sprintf(default_ns, "http://%s/GenericMessage", server_instance);
	request_root = xml_new_element(NULL, "ForwardMessage", default_ns);
	auth_node = xml_new_element(NULL, "Authentication", NULL);
	id_node = xml_new_element(NULL, "Id", NULL);
	secrete_node = xml_new_element(NULL, "Secrete", NULL);
	message_node = xml_new_element(NULL, "Message", NULL);
	type_node = xml_new_element(NULL, "Type", NULL);
	content_node = xml_new_element(NULL, "Content", NULL);
	xml_add_child(request_root, auth_node);
	xml_add_child(auth_node, id_node);
	xml_add_child(auth_node, secrete_node);
	xml_add_child(id_node, xml_new_text(device_id));
	xml_add_child(secrete_node, xml_new_text(device_secrete));
	xml_add_child(request_root, message_node);
	xml_add_child(message_node, type_node);
	xml_add_child(message_node, content_node);
	xml_add_child(type_node, xml_new_text(type));	//For device, Message/Type should be "FromDevice" or "Status"
	xml_add_child(content_node, application_root);	//Add application document root to request content node as child

	if(reply_key != NULL) {
		reply_key_node = xml_new_element(NULL, "ReplyKey", NULL);
		xml_add_child(message_node, reply_key_node);
		xml_add_child(reply_key_node, xml_new_text(reply_key));
	}

	if((strcmp(type, "Status") == 0) && (status_rule != NULL)) {
		status_rule_node = xml_new_element(NULL, "StatusRule", NULL);
		xml_add_child(message_node, status_rule_node);
		xml_add_child(status_rule_node, xml_new_text(status_rule));
	}

	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	dump_msg("\nsend http header:", header, strlen(header));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
	write(server_socket, header, strlen(header));
	write(server_socket, xml_request, strlen(xml_request));
	http_free(header);
	xml_free(xml_request);

	//Read HTTP
	if((read_size = read(server_socket, response_buf, sizeof(response_buf))) != 0) {
		struct xml_node *response_root, *instance_text;
		struct xml_node_set *node_set;
		char *http_header, *http_body;

		if((http_header = http_response_header(response_buf, read_size)) != NULL) {
			dump_msg("\nrecv http header:", http_header, strlen(http_header));
			http_free(http_header);
		}

		if((http_body = http_response_body(response_buf, read_size)) != NULL) {
			dump_msg("recv http body:", http_body, strlen(http_body));
			http_free(http_body);
		}
	}

	if(doc_prefix)
		xml_free(doc_prefix);

	if(doc_name)
		xml_free(doc_name);

	if(doc_uri)
		xml_free(doc_uri);

	free(default_ns);
	close(server_socket);
}

static void message_retrieve_message(void)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns;
	char response_buf[512];
	int read_size, extra_read_size = 0;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node, *proxy_type_node, *proxy_key_node, *period_node;

	char vpn_server_content[512];	
	char vpn_client_ip[16], cmd_buf[64];
	char *pclient_ip_start=NULL;
	char *pclient_ip_end=NULL;
	char *public_address=NULL;
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_instance);
	server_addr.sin_port = ntohs(CLOUD_PORT);

	if(connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		close(server_socket);
		return;
	}

	//Build XML Request Document Tree
	default_ns = (char *) malloc(strlen("http://") + strlen(server_instance) + strlen("/GenericMessage") + 1);
	sprintf(default_ns, "http://%s/GenericMessage", server_instance);
	request_root = xml_new_element(NULL, "RetrieveMessage", default_ns);
	auth_node = xml_new_element(NULL, "Authentication", NULL);
	id_node = xml_new_element(NULL, "Id", NULL);
	secrete_node = xml_new_element(NULL, "Secrete", NULL);
	proxy_type_node = xml_new_element(NULL, "ProxyType", NULL);
	proxy_key_node = xml_new_element(NULL, "ProxyKey", NULL);
	period_node = xml_new_element(NULL, "AckPeriod", NULL);
	xml_add_child(request_root, auth_node);
	xml_add_child(auth_node, id_node);
	xml_add_child(auth_node, secrete_node);
	xml_add_child(id_node, xml_new_text(device_id));
	xml_add_child(secrete_node, xml_new_text(device_secrete));
	xml_add_child(request_root, proxy_type_node);
	xml_add_child(request_root, proxy_key_node);
	xml_add_child(request_root, period_node);
	xml_add_child(proxy_type_node, xml_new_text("DeviceProxy"));	//ProxyType for device should be "DeviceProxy"
	xml_add_child(proxy_key_node, xml_new_text(proxy_key));
	xml_add_child(period_node, xml_new_text("30"));	//Set ack period in seconds
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	dump_msg("\nsend http header:", header, strlen(header));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
	write(server_socket, header, strlen(header));
	write(server_socket, xml_request, strlen(xml_request));
	http_free(header);
	xml_free(xml_request);

	//Read HTTP
	while(1)
	{		
		extra_read_size=0;		
		while((read_size = read(server_socket, response_buf + extra_read_size, sizeof(response_buf) - extra_read_size)) != 0) {
			struct xml_node *response_root;
			struct xml_node_set *node_set;
			char *http_header, *http_body;
			int msg_no = 0;

			while(1) {
				read_size += extra_read_size;

				if(read_size == 0)
					break;

				if((http_header = http_response_header(response_buf, read_size)) != NULL) {
					dump_msg("\nrecv http header:", http_header, strlen(http_header));
					http_free(http_header);
				}

				if((http_body = http_response_body(response_buf, read_size)) != NULL) {
					dump_msg("recv http body:", http_body, strlen(http_body));
					http_free(http_body);
				}

				if((response_root = xml_parse_doc(response_buf, read_size, NULL, "RetrieveMessageResponse", default_ns)) != NULL) {
					int has_message = 0;
					int i;
					int processed_size = strstr(response_buf, "</RetrieveMessageResponse>") - response_buf + 
						strlen("</RetrieveMessageResponse>");

					while((processed_size < read_size) && ((response_buf[processed_size] == '\n') || (response_buf[processed_size] == '\r')))
						processed_size ++;

					extra_read_size = read_size - processed_size;

					/* move the extra read data to the beginning of buffer */
					for(i = 0; i < extra_read_size; i ++)
						response_buf[i] = response_buf[processed_size + i];

					node_set = xml_find_path(response_root, "/RetrieveMessageResponse/Message/Id");

					if(node_set->count) {
						struct xml_node *id_text = xml_text_child(node_set->node[0]);

						if(id_text) {
							if(strcmp(id_text->text, device_id) == 0)
								has_message = 1;
						}
					}

					xml_delete_set(node_set);

					if(has_message) {
						struct xml_node *application_node = NULL;
						char *reply_key = NULL;

						node_set = xml_find_path(response_root, "/RetrieveMessageResponse/Message/Content");

						if(node_set->count) {
							struct xml_node *content_node = node_set->node[0];

							application_node = content_node->child;
						}

						xml_delete_set(node_set);

						node_set = xml_find_path(response_root, "/RetrieveMessageResponse/Message/ReplyKey");

						if(node_set->count) {
							struct xml_node *reply_key_text = xml_text_child(node_set->node[0]);

							if(reply_key_text)
								reply_key = reply_key_text->text;
						}

						xml_delete_set(node_set);

						if(device_type == DEVICE_LIGHT) {
							//light_handle_message(application_node, reply_key);
						}
						else if(device_type == DEVICE_SENSOR) {
							//sensor_handle_message(application_node, reply_key);
						}
						else {
							if(application_node) {
								char *content_buf = xml_dump_tree(application_node);
								printf("Receive Application-Dependent Content: %s\n", content_buf);

								if(strncmp(content_buf, "<OpenvpnApplication><ClientIpElement>", strlen("<OpenvpnApplication><ClientIpElement>")) == 0)
								{								
									pclient_ip_start=content_buf+strlen("<OpenvpnApplication><ClientIpElement>");
									for(pclient_ip_end=pclient_ip_start; pclient_ip_end!=NULL && *pclient_ip_end!='<'; pclient_ip_end++);
									strncpy(vpn_client_ip, pclient_ip_start, pclient_ip_end-pclient_ip_start);	
									vpn_client_ip[pclient_ip_end-pclient_ip_start]=0;
									printf("Recv VPN Client IP Address: %s\n", vpn_client_ip);

									sprintf(cmd_buf, "echo VpnClientIp:%s > /etc/openvpn/vpn_client_ip", vpn_client_ip);
									system(cmd_buf);
									
									public_address = loadbalance_lookup_address();
									printf("My Public IP Address: %s\n", public_address);
									sprintf(vpn_server_content, "<OpenvpnApplication><ServerIpElement>%s</ServerIpElement></OpenvpnApplication>", public_address);
									message_forward_message("FromDevice", vpn_server_content, NULL, NULL);
									free(public_address);
									system("/usr/sbin/openvpn_server_start.sh &");
								}
								
								xml_free(content_buf);
							}

							if(reply_key)
								message_forward_message("FromDevice", "<Application>AutoReply</Application>", reply_key, NULL);
						}
					}
					else {
						node_set = xml_find_path(response_root, "/RetrieveMessageResponse/Result");

						if(node_set->count) {
							xml_delete_set(node_set);
							xml_delete_tree(response_root);
							goto finish;
						}

						xml_delete_set(node_set);
					}

					xml_delete_tree(response_root);
				}
				else {
					if(msg_no == 0)
						extra_read_size = 0;
						
					break;
				}

				read_size = 0;
				msg_no ++;
			}
		}
	}
	
finish:
	free(default_ns);
	close(server_socket);
}

static void *cloud_listener(void *args)
{
#if 0
	if(device_type == DEVICE_LIGHT) {
		light_init();
	}
	else if(device_type == DEVICE_SENSOR) {
		sensor_init();
	}
#endif

	if(loadbalance_get_instance() == 0) {
		//loadbalance_lookup_address();
		if(message_apply_proxy() == 0) {
#if 0
			if(device_type == DEVICE_SENSOR)
				sensor_start();
#endif			
			message_retrieve_message();
		}
	}

	printf("Cloud Listener Exit\n");

	if(server_instance) {
		free(server_instance);
		server_instance = NULL;
	}

	if(proxy_key) {
		free(proxy_key);
		proxy_key = NULL;
	}
}

int main(int argc, char **argv)
{
	//pthread_t listener;
	//char cmd[500];

	if(argc == 3) {
		device_id = argv[1];
		device_secrete = argv[2];
	}
	else if(argc == 4) {
		if(strcmp(argv[1], "light") == 0)
			device_type = DEVICE_LIGHT;
		else if(strcmp(argv[1], "sensor") == 0)
			device_type = DEVICE_SENSOR;

		device_id = argv[2];
		device_secrete = argv[3];
	}
	else {
		printf("Usage: %s [DEVICE_TYPE] DEVICE_ID DEVICE_SECRETE\n", argv[0]);
		return -1;
	}

	//pthread_create(&listener, NULL, cloud_listener, NULL);

	if (daemon(0, 0) == -1) 
	{
		printf("cloud device fork error");
		goto ERROR_EXIT;
	}
	
	cloud_listener(NULL);

#if 0
	while(gets(cmd)) {
		if(strlen(cmd) > 0) {
			if(strncmp(cmd, "exit", strlen("exit")) == 0) {
				if(device_type == DEVICE_SENSOR)
					sensor_exit();

				message_release_proxy();
				pthread_join(listener, NULL);
				break;
			}
			else if(strncmp(cmd, "lookup", strlen("lookup")) == 0) {
				printf("%s:%d########\n",__FUNCTION__,__LINE__);
				char *public_address = loadbalance_lookup_address();
				printf("My Public IP Address: %s\n", public_address);
				free(public_address);
			}
			else if(strncmp(cmd, "send ", strlen("send ")) == 0) {
				//example: send <TestApplication><TestElement>TestText</TestElement></TestApplication>
				char *content = cmd + strlen("send ");
				message_forward_message("FromDevice", content, NULL, NULL);
			}
			else if(strncmp(cmd, "lookupaddress", strlen("lookupaddress")) == 0) {
				//example: send <TestApplication><TestElement>TestText</TestElement></TestApplication>
				loadbalance_lookup_address();
			}
			else if(strncmp(cmd, "status ", strlen("status ")) == 0) {
				//example: status new <TestApplication><TestElement>TestText</TestElement></TestApplication>
				char *rule = cmd + strlen("status ");

				if(strncmp(rule, "new ", strlen("new ")) == 0) {
					char *content = rule + strlen("new ");
					message_forward_message("Status", content, NULL, "NewStatus");
				}
				else if(strncmp(rule, "update ", strlen("update ")) == 0) {
					char *content = rule + strlen("update ");
					message_forward_message("Status", content, NULL, "UpdateStatus");
				}
				else
					printf("Status rule is required\n");
			}
			else if(strncmp(cmd, "pir", strlen("pir")) == 0) {
				sensor_pir_handler();
			}
		}

		printf("DEVICE [%s]# ", device_id);
	}
#endif

ERROR_EXIT:
	printf("Cloud Device Exit\n");
	return 0;
}
