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

static char *device_id = NULL;
static char *device_secrete = NULL;
static char *server_instance = NULL;
static char *proxy_key = NULL;

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
static int loadbalance_discover_device(void)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns;
	char response_buf[1024];
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
	request_root = xml_new_element(NULL, "DiscoverDevice", default_ns);
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
	write(server_socket, header, strlen(header));
	dump_msg("\nsend http header:", header, strlen(header));
	http_free(header);
	write(server_socket, xml_request, strlen(xml_request));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
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

		if((response_root = xml_parse_doc(response_buf, read_size, NULL, "DiscoverDeviceResponse", default_ns)) != NULL) {
			node_set = xml_find_path(response_root, "/DiscoverDeviceResponse/Instance");

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
	char response_buf[1024];
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
	xml_add_child(proxy_type_node, xml_new_text("ControllerProxy"));	//ProxyType for controller should be "ControllerProxy"
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	write(server_socket, header, strlen(header));
	dump_msg("\nsend http header:", header, strlen(header));
	http_free(header);
	write(server_socket, xml_request, strlen(xml_request));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
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
	char response_buf[1024];
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
	xml_add_child(proxy_type_node, xml_new_text("ControllerProxy"));	//ProxyType for controller should be "ControllerProxy"
	xml_add_child(request_root, proxy_key_node);
	xml_add_child(proxy_key_node, xml_new_text(proxy_key));
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	write(server_socket, header, strlen(header));
	dump_msg("\nsend http header:", header, strlen(header));
	http_free(header);
	write(server_socket, xml_request, strlen(xml_request));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
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

static void message_forward_message(char *application_content, char *timeout)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns, *doc_prefix = NULL, *doc_name = NULL, *doc_uri = NULL;
	char response_buf[1024];
	int read_size;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node, *message_node, *type_node, *content_node, *application_root, *timeout_node;

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
	xml_add_child(type_node, xml_new_text("ToDevice"));	//For controller, Message/Type should be "ToDevice"
	xml_add_child(content_node, application_root);	//Add application document root to request content node as child

	if(timeout != NULL) {
		timeout_node = xml_new_element(NULL, "Timeout", NULL);
		xml_add_child(timeout_node, xml_new_text(timeout));
		xml_add_child(request_root, timeout_node);
	}

	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	write(server_socket, header, strlen(header));
	dump_msg("\nsend http header:", header, strlen(header));
	http_free(header);
	write(server_socket, xml_request, strlen(xml_request));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
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

static void message_query_status(char *op, char *time1, char *time2, char *limit)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns;
	char response_buf[4096];
	int read_size;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node, *op_node, *time_node, *time1_node, *time2_node, *limit_node;

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
	request_root = xml_new_element(NULL, "QueryStatus", default_ns);
	auth_node = xml_new_element(NULL, "Authentication", NULL);
	id_node = xml_new_element(NULL, "Id", NULL);
	secrete_node = xml_new_element(NULL, "Secrete", NULL);
	op_node = xml_new_element(NULL, "TimeOperation", NULL);
	xml_add_child(request_root, auth_node);
	xml_add_child(auth_node, id_node);
	xml_add_child(auth_node, secrete_node);
	xml_add_child(id_node, xml_new_text(device_id));
	xml_add_child(secrete_node, xml_new_text(device_secrete));
	xml_add_child(request_root, op_node);
	xml_add_child(op_node, xml_new_text(op));

	if(strcmp(op, "TimeRangeBetween") == 0) {
		time_node = xml_new_element(NULL, "TimeRange", NULL);
		xml_add_child(request_root, time_node);
		time1_node = xml_new_element(NULL, "StartTime", NULL);
		time2_node = xml_new_element(NULL, "EndTime", NULL);
		xml_add_child(time_node, time1_node);
		xml_add_child(time_node, time2_node);
		xml_add_child(time1_node, xml_new_text(time1));
		xml_add_child(time2_node, xml_new_text(time2));
	}
	else {
		time_node = xml_new_element(NULL, "Time", NULL);
		xml_add_child(request_root, time_node);
		xml_add_child(time_node, xml_new_text(time1));

		if((strcmp(op, "TimeGreaterThan") == 0) || (strcmp(op, "TimeLessThan") == 0)) {
			limit_node = xml_new_element(NULL, "QueryLimit", NULL);
			xml_add_child(request_root, limit_node);
			xml_add_child(limit_node, xml_new_text(limit));
		}
	}

	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	write(server_socket, header, strlen(header));
	dump_msg("\nsend http header:", header, strlen(header));
	http_free(header);
	write(server_socket, xml_request, strlen(xml_request));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
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

		if((response_root = xml_parse_doc(response_buf, read_size, NULL, "QueryStatusResponse", default_ns)) != NULL) {
			node_set = xml_find_path(response_root, "/QueryStatusResponse/Status");

			if(node_set->count) {
				int i;

				for(i = 0; i < node_set->count; i ++) {
					char *status_buf = xml_dump_tree(node_set->node[i]);
					printf("Receive Application-Dependent Statu[%d]: %s\n", i, status_buf);
					xml_free(status_buf);
				}
			}

			xml_delete_set(node_set);
			xml_delete_tree(response_root);
		}
	}

	free(default_ns);
	close(server_socket);
}

static void message_retrieve_message(void)
{
	int server_socket;
	struct sockaddr_in server_addr;
	char *header, *xml_request, *default_ns;
	char response_buf[1024];
	int read_size;
	struct xml_node *request_root, *auth_node, *id_node, *secrete_node, *proxy_type_node, *proxy_key_node, *period_node;

	char vpn_server_ip[16], cmd_buf[64];
	char *pserver_ip_start=NULL;
	char *pserver_ip_end=NULL;
	int get_server_ip_flag=0;
	
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
	xml_add_child(proxy_type_node, xml_new_text("ControllerProxy"));	//ProxyType for controller should be "ControllerProxy"
	xml_add_child(proxy_key_node, xml_new_text(proxy_key));
	xml_add_child(period_node, xml_new_text("30"));	//Set ack period in seconds
	xml_request = xml_dump_tree(request_root);
	xml_delete_tree(request_root);

	//Write HTTP
	header = http_post_header(server_instance, "/cgi-bin/generic_message", "text/xml", (int) strlen(xml_request));
	write(server_socket, header, strlen(header));
	dump_msg("\nsend http header:", header, strlen(header));
	http_free(header);
	write(server_socket, xml_request, strlen(xml_request));
	dump_msg("send xml request:", xml_request, strlen(xml_request));
	xml_free(xml_request);

	//Read HTTP
	while(get_server_ip_flag==0 && (read_size = read(server_socket, response_buf, sizeof(response_buf))) != 0) {
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

		if((response_root = xml_parse_doc(response_buf, read_size, NULL, "RetrieveMessageResponse", default_ns)) != NULL) {
			int has_message = 0;

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
				node_set = xml_find_path(response_root, "/RetrieveMessageResponse/Message/Content");

				if(node_set->count) {
					struct xml_node *content_node = node_set->node[0];

					if(content_node->child) {
						char *content_buf = xml_dump_tree(content_node->child);
						printf("Receive Application-Dependent Content: %s\n", content_buf);

						if(strncmp(content_buf, "<OpenvpnApplication><ServerIpElement>", strlen("<OpenvpnApplication><ServerIpElement>")) == 0)
						{
							pserver_ip_start=content_buf+strlen("<OpenvpnApplication><ServerIpElement>");
							for(pserver_ip_end=pserver_ip_start; pserver_ip_end!=NULL && *pserver_ip_end!='<'; pserver_ip_end++);
							strncpy(vpn_server_ip, pserver_ip_start, pserver_ip_end-pserver_ip_start);	
							vpn_server_ip[pserver_ip_end-pserver_ip_start]=0;
							printf("Recv VPN Server IP Address: %s\n", vpn_server_ip);
							sprintf(cmd_buf, "echo VpnServerIp:%s > /etc/openvpn/vpn_server_ip", vpn_server_ip);
							system(cmd_buf);
							get_server_ip_flag=1;
							system("/usr/sbin/openvpn_client_start.sh &");
						}
						
						xml_free(content_buf);
					}
				}

				xml_delete_set(node_set);
			}
			else {
				node_set = xml_find_path(response_root, "/RetrieveMessageResponse/Result");

				if(node_set->count) {
					xml_delete_set(node_set);
					xml_delete_tree(response_root);
					break;
				}

				xml_delete_set(node_set);
			}

			xml_delete_tree(response_root);
		}
	}

	free(default_ns);
	close(server_socket);
}

static void *cloud_listener(void *args)
{
	char vpn_client_content[512];
	if(loadbalance_discover_device() == 0) {
		if(message_apply_proxy() == 0)
		{
			char *public_address = loadbalance_lookup_address();
			if(public_address==NULL)
			{
				printf("VPN Client Get Public IP Fails!\n");
				return NULL;
			}
			printf("My Public IP Address: %s\n", public_address);
			sprintf(vpn_client_content, "<OpenvpnApplication><ClientIpElement>%s</ClientIpElement></OpenvpnApplication>", public_address);
			message_forward_message(vpn_client_content, NULL);
			free(public_address);
			
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
	else {
		printf("Usage: %s DEVICE_ID, DEVICE_SECRETE\n", argv[0]);
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
				message_release_proxy();
				pthread_join(listener, NULL);
				break;
			}
			else if(strncmp(cmd, "lookup", strlen("lookup")) == 0) {
				char *public_address = loadbalance_lookup_address();
				printf("My Public IP Address: %s\n", public_address);
				free(public_address);
			}
			else if(strncmp(cmd, "send ", strlen("send ")) == 0) {
				//example: send <TestApplication><TestElement>TestText</TestElement></TestApplication>
				char *content = NULL, *timeout = NULL;

				if(strncmp(cmd + strlen("send "), "timeout ", strlen("timeout ")) == 0) {
					timeout = cmd + strlen("send ") + strlen("timeout ");
					content = strstr(timeout, " ") + 1;
					*(content - 1) = '\0';
				}
				else {
					timeout = NULL;
					content = cmd + strlen("send ");
				}

				message_forward_message(content, timeout);
			}
			else if(strncmp(cmd, "query ", strlen("query ")) == 0) {
				//example: query greater 2013-10-09 17:00:00 limit 1
				char *time1 = NULL, *time2 = NULL, *limit = NULL;
				char *op = cmd + strlen("query ");
				int ret = 0;

				if(strncmp(op, "less ", strlen("less ")) == 0) {
					char *separate;
					time1 = op + strlen("less ");

					if((separate = strstr(time1, " limit ")) == NULL) {
						printf("'less' operation needs 'limit'\n");
						ret = -1;
					}
					else {
						limit = separate + strlen(" limit ");
						*separate = '\0';
					}

					op = "TimeLessThan";
				}
				else if(strncmp(op, "greater ", strlen("greater ")) == 0) {
					char *separate;
					time1 = op + strlen("greater ");

					if((separate = strstr(time1, " limit ")) == NULL) {
						printf("'greater' operation needs 'limit'\n");
						ret = -1;
					}
					else {
						limit = separate + strlen(" limit ");
						*separate = '\0';
					}

					op = "TimeGreaterThan";
				}
				else if(strncmp(op, "equal ", strlen("equal ")) == 0) {
					time1 = op + strlen("equal ");
					op = "TimeEqualTo";
				}
				else if(strncmp(op, "range ", strlen("range ")) == 0) {
					char *separate;
					time1 = op + strlen("range ");

					if((separate = strstr(time1, " ~ ")) == NULL) {
						printf("Need '~' to separate 2 time\n");
						ret = -1;
					}
					else {
						time2 = separate + strlen(" ~ ");
						*separate = '\0';
					}

					op = "TimeRangeBetween";
				}

				if(ret == 0)
					message_query_status(op, time1, time2, limit);
			}
		}

		printf("USER [%s]# ", argv[1]);
	}
#endif
ERROR_EXIT:
	printf("Cloud Controller Exit\n");
	return 0;
}
