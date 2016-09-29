/*
Author: Alex Fang

Tree Structure
              root              root
              | ^                ^
          child |                |
              | parent         parent
              v |                |
NULL<-prev-child1-next-><-prev-child2-next->NULL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml.h"

static void* xml_malloc(unsigned int size)
{
	return malloc(size);
}

void xml_free(void *buf)
{
	free(buf);
}

static void parse_tag(char *tag, char **prefix, char **name, char **uri)
{
	char *ns_tag, *prefix_char;
	int have_prefix = 0;
	int have_uri = 0;

	prefix_char = strstr(tag, ":");

	if((ns_tag = strstr(tag, "xmlns")) != NULL) {
		have_uri = 1;

		if((prefix_char != NULL) && (prefix_char < ns_tag))
			have_prefix = 1;
	}
	else if(prefix_char) {
		have_prefix = 1;
	}

	if(have_prefix && have_uri) {
		char *prefix_front, *prefix_rear, *name_front, *name_rear, *uri_front, *uri_rear;
		int prefix_len, name_len, uri_len;

		prefix_front = tag;
		prefix_rear = prefix_char;
		prefix_len = prefix_rear - prefix_front;
		*prefix = (char *) xml_malloc(prefix_len + 1);
		memcpy(*prefix, prefix_front, prefix_len);
		(*prefix)[prefix_len] = '\0';

		name_front = prefix_char + 1;
		name_rear = ns_tag - 1;
		name_len = name_rear - name_front;
		*name = (char *) xml_malloc(name_len + 1);
		memcpy(*name, name_front, name_len);
		(*name)[name_len] = '\0';

		uri_front = strstr(ns_tag, "\"") + 1;
		uri_rear = strstr(uri_front, "\"");
		uri_len = uri_rear - uri_front;
		*uri = (char *) xml_malloc(uri_len + 1);
		memcpy(*uri, uri_front, uri_len);
		(*uri)[uri_len] = '\0';
	}
	else if(have_prefix) {
		char *prefix_front, *prefix_rear, *name_front, *name_rear;
		int prefix_len, name_len;

		prefix_front = tag;
		prefix_rear = prefix_char;
		prefix_len = prefix_rear - prefix_front;
		*prefix = (char *) xml_malloc(prefix_len + 1);
		memcpy(*prefix, prefix_front, prefix_len);
		(*prefix)[prefix_len] = '\0';

		name_front = prefix_char + 1;
		name_rear = tag + strlen(tag);
		name_len = name_rear - name_front;
		*name = (char *) xml_malloc(name_len + 1);
		memcpy(*name, name_front, name_len);
		(*name)[name_len] = '\0';

		*uri = NULL;
	}
	else if(have_uri) {
		char *name_front, *name_rear, *uri_front, *uri_rear;
		int name_len, uri_len;

		*prefix = NULL;

		name_front = tag;
		name_rear = ns_tag - 1;
		name_len = name_rear - name_front;
		*name = (char *) xml_malloc(name_len + 1);
		memcpy(*name, name_front, name_len);
		(*name)[name_len] = '\0';

		uri_front = strstr(ns_tag, "\"") + 1;
		uri_rear = strstr(uri_front, "\"");
		uri_len = uri_rear - uri_front;
		*uri = (char *) xml_malloc(uri_len + 1);
		memcpy(*uri, uri_front, uri_len);
		(*uri)[uri_len] = '\0';
	}
	else {
		*prefix = NULL;

		*name = (char *) xml_malloc(strlen(tag) + 1);
		strcpy(*name, tag);

		*uri = NULL;
	}
}

int xml_doc_name(char *doc_buf, int doc_len, char **doc_prefix, char **doc_name, char **doc_uri)
{
	char *xml_buf, *cur_pos, *tag_front, *tag_rear;
	char *start_tag, *end_tag;
	int tag_len, ret = -1;

	xml_buf = (char *) xml_malloc(doc_len + 1);
	memcpy(xml_buf, doc_buf, doc_len);
	xml_buf[doc_len] = '\0';

	cur_pos = xml_buf;

	while(cur_pos < (xml_buf + doc_len)) {
		if((tag_front = strstr(cur_pos, "<")) != NULL) {
			tag_front ++;

			if((tag_rear = strstr(tag_front, ">")) != NULL) {
				char *prefix = NULL, *name = NULL, *uri = NULL;

				//Element without content
				if(*(tag_rear - 1) == '/') {
					tag_len = tag_rear - 1 - tag_front;
					start_tag = (char *) xml_malloc(tag_len + 1);
					memcpy(start_tag, tag_front, tag_len);
					start_tag[tag_len] = '\0';
					parse_tag(start_tag, &prefix, &name, &uri);
					xml_free(start_tag);
					*doc_name = name;
					*doc_prefix = prefix;
					*doc_uri = uri;
					ret = 0;
					cur_pos = xml_buf + doc_len;
				}
				//Element with content
				else {
					tag_len = tag_rear - tag_front;
					start_tag = (char *) xml_malloc(tag_len + 1);
					memcpy(start_tag, tag_front, tag_len);
					start_tag[tag_len] = '\0';
					parse_tag(start_tag, &prefix, &name, &uri);
					xml_free(start_tag);

					if(prefix) {
						end_tag = (char *) xml_malloc(strlen(prefix) + strlen(name) + 5);
						sprintf(end_tag, "</%s:%s>", prefix, name);
					}
					else {
						end_tag = (char *) xml_malloc(strlen(name) + 4);
						sprintf(end_tag, "</%s>", name);
					}

					if(strstr(tag_rear + 1, end_tag)) {
						*doc_name = name;
						*doc_prefix = prefix;
						*doc_uri = uri;
						ret = 0;
						cur_pos = xml_buf + doc_len;
					}
					else {
						xml_free(name);
	
						if(prefix)
							xml_free(prefix);

						if(uri)
							xml_free(uri);			

						cur_pos = tag_rear + 1;
					}

					xml_free(end_tag);
				}
			}
			else {
				cur_pos = xml_buf + doc_len;
			}
		}
		else {
			cur_pos = xml_buf + doc_len;
		}
	}

	xml_free(xml_buf);
	
	return ret;
}

static void _xml_parse_doc(char *doc_buf, int doc_len, struct xml_node *root)
{
	char *xml_buf, *cur_pos;

	xml_buf = (char *) xml_malloc(doc_len + 1);
	memcpy(xml_buf, doc_buf, doc_len);
	xml_buf[doc_len] = '\0';

	cur_pos = xml_buf;

	while(cur_pos < (xml_buf + doc_len)) {
		char *tag_front, *tag_rear;
		struct xml_node *node;
		
		if((tag_front = strstr(cur_pos, "<")) != NULL) {
			tag_front ++;

			if((tag_rear = strstr(tag_front, ">")) != NULL) {
				char *doc_front, *doc_rear, *start_tag, *end_tag;
				char *prefix = NULL, *name = NULL, *uri = NULL;
				int tag_len;

				//Element without content
				if(*(tag_rear - 1) == '/') {
					doc_front = tag_rear + 1;
					tag_len = tag_rear - 1 - tag_front;
					start_tag = (char *) xml_malloc(tag_len + 1);
					memcpy(start_tag, tag_front, tag_len);
					start_tag[tag_len] = '\0';
					parse_tag(start_tag, &prefix, &name, &uri);
					node = xml_new_element(prefix, name, uri);
					xml_add_child(root, node);
					cur_pos = doc_front;
				}
				//Element with content
				else {
					doc_front = tag_rear + 1;
					tag_len = tag_rear - tag_front;
					start_tag = (char *) xml_malloc(tag_len + 1);
					memcpy(start_tag, tag_front, tag_len);
					start_tag[tag_len] = '\0';
					parse_tag(start_tag, &prefix, &name, &uri);

					if(prefix) {
						end_tag = (char *) xml_malloc(strlen(prefix) + strlen(name) + 5);
						sprintf(end_tag, "</%s:%s>", prefix, name);
					}
					else {
						end_tag = (char *) xml_malloc(strlen(name) + 4);
						sprintf(end_tag, "</%s>", name);
					}
			
					node = xml_new_element(prefix, name, uri);
					xml_add_child(root, node);

					if((doc_rear = strstr(doc_front, end_tag)) != NULL) {
						_xml_parse_doc(doc_front, doc_rear - doc_front, node);
						cur_pos = doc_rear + strlen(end_tag);
					}
					else {
						cur_pos = doc_front;
					}

					xml_free(end_tag);
				}

				xml_free(start_tag);
				xml_free(name);

				if(prefix)
					xml_free(prefix);

				if(uri)
					xml_free(uri);
			}
			else {
				if(strlen(cur_pos) > 0) {
					node = xml_new_text(cur_pos);
					xml_add_child(root, node);
				}

				cur_pos = xml_buf + doc_len;
			}
		}
		else {
			if(strlen(cur_pos) > 0) {
				node = xml_new_text(cur_pos);
				xml_add_child(root, node);
			}

			cur_pos = xml_buf + doc_len;
		}
	}

	xml_free(xml_buf);
}

struct xml_node *xml_parse_doc(char *doc_buf, int doc_len, char *doc_prefix, char *doc_name, char *doc_uri)
{
	struct xml_node *root = NULL;
	char *xml_buf, *start_tag, *end_tag, *empty_tag, *front, *rear;

	xml_buf = (char *) xml_malloc(doc_len + 1);
	memcpy(xml_buf, doc_buf, doc_len);
	xml_buf[doc_len] = '\0';

	if(doc_prefix && doc_uri) {
		start_tag = (char *) xml_malloc(2 * strlen(doc_prefix) + strlen(doc_name) + strlen(doc_uri) + 14);
		sprintf(start_tag, "<%s:%s xmlns:%s=\"%s\">", doc_prefix, doc_name, doc_prefix, doc_uri);
		empty_tag = (char *) xml_malloc(2 * strlen(doc_prefix) + strlen(doc_name) + strlen(doc_uri) + 15);
		sprintf(empty_tag, "<%s:%s xmlns:%s=\"%s\"/>", doc_prefix, doc_name, doc_prefix, doc_uri);

	}
	else if(doc_prefix) {
		start_tag = (char *) xml_malloc(strlen(doc_prefix) + strlen(doc_name) + 4);
		sprintf(start_tag, "<%s:%s>", doc_prefix, doc_name);
		empty_tag = (char *) xml_malloc(strlen(doc_prefix) + strlen(doc_name) + 5);
		sprintf(empty_tag, "<%s:%s/>", doc_prefix, doc_name);
	}
	else if(doc_uri) {
		start_tag = (char *) xml_malloc(strlen(doc_name) + strlen(doc_uri) + 12);
		sprintf(start_tag, "<%s xmlns=\"%s\">", doc_name, doc_uri);
		empty_tag = (char *) xml_malloc(strlen(doc_name) + strlen(doc_uri) + 13);
		sprintf(empty_tag, "<%s xmlns=\"%s\"/>", doc_name, doc_uri);
	}
	else {
		start_tag = (char *) xml_malloc(strlen(doc_name) + 3);
		sprintf(start_tag, "<%s>", doc_name);
		empty_tag = (char *) xml_malloc(strlen(doc_name) + 4);
		sprintf(empty_tag, "<%s/>", doc_name);
	}

	if(doc_prefix) {
		end_tag = (char *) xml_malloc(strlen(doc_prefix) + strlen(doc_name) + 5);
		sprintf(end_tag, "</%s:%s>", doc_prefix, doc_name);
	}
	else {
		end_tag = (char *) xml_malloc(strlen(doc_name) + 4);
		sprintf(end_tag, "</%s>", doc_name);
	}
	
	//Root element with content
	if((front = strstr(xml_buf, start_tag)) != NULL) {
		front += strlen(start_tag);

		if((rear = strstr(front, end_tag)) != NULL) {
			int xml_len = rear - front;

			root = xml_new_element(doc_prefix, doc_name, doc_uri);
			_xml_parse_doc(front, xml_len, root);
		}
	}
	//Root element without content
	else if((front = strstr(xml_buf, empty_tag)) != NULL) {
			root = xml_new_element(doc_prefix, doc_name, doc_uri);
	}

	xml_free(start_tag);
	xml_free(end_tag);
	xml_free(empty_tag);
	xml_free(xml_buf);

	return root;
}

static struct xml_node *xml_new_node(void)
{
	struct xml_node *node;

	node = (struct xml_node *) xml_malloc(sizeof(struct xml_node));
	memset(node, 0, sizeof(struct xml_node));

	return node;
}

struct xml_node *xml_new_element(char *prefix, char *name, char *uri)
{
	struct xml_node *node;

	node = xml_new_node();
	node->name = (char *) xml_malloc(strlen(name) + 1);
	strcpy(node->name, name);
	
	if(prefix) {
		node->prefix = (char *) xml_malloc(strlen(prefix) + 1);
		strcpy(node->prefix, prefix);
	}

	if(uri) {
		node->uri = (char *) xml_malloc(strlen(uri) + 1);
		strcpy(node->uri, uri);
	}

	return node;	
}

struct xml_node *xml_new_text(char *text)
{
	struct xml_node *node;
	char *text_buf;

	text_buf = (char *) xml_malloc(strlen(text) + 1);
	strcpy(text_buf, text);
	node = xml_new_node();
	node->text = text_buf;

	return node;
}

int xml_is_element(struct xml_node *node)
{
	int ret = 0;

	if((node->name != NULL) && (node->text == NULL))
		ret = 1;

	return ret;
}

int xml_is_text(struct xml_node *node)
{
	int ret = 0;

	if((node->name == NULL) && (node->text != NULL))
		ret = 1;

	return ret;
}

static void _xml_copy_tree(struct xml_node *root, struct xml_node *parent)
{
	struct xml_node *copy = NULL;

	if(xml_is_text(root)) {
		copy = xml_new_text(root->text);
	}
	else if(xml_is_element(root)) {
		struct xml_node *child = root->child;

		copy = xml_new_element(root->prefix, root->name, root->uri);

		while(child) {
			_xml_copy_tree(child, copy);
			child = child->next;
		}
	}

	if(copy)
		xml_add_child(parent, copy);
}

struct xml_node* xml_copy_tree(struct xml_node *root)
{
	struct xml_node *copy = NULL;

	if(xml_is_text(root)) {
		copy = xml_new_text(root->text);
	}
	else if(xml_is_element(root)) {
		struct xml_node *child = root->child;

		copy = xml_new_element(root->prefix, root->name, root->uri);

		while(child) {
			_xml_copy_tree(child, copy);
			child = child->next;
		}
	}

	return copy;
}

void xml_delete_tree(struct xml_node *root)
{
	if(root->name)
		xml_free(root->name);

	if(root->text)
		xml_free(root->text);

	if(root->prefix)
		xml_free(root->prefix);

	if(root->uri)
		xml_free(root->uri);

	while(root->child)
		xml_delete_tree(root->child);

	if(root->prev) {
		root->prev->next = root->next;

		if(root->next)
			root->next->prev = root->prev;
	}
	else if(root->parent) {
		root->parent->child = root->next;

		if(root->next)
			root->next->prev = NULL;
	}

	xml_free(root);
}

void xml_add_child(struct xml_node *node, struct xml_node *child)
{
	if(xml_is_element(node)) {
		if(node->child) {
			struct xml_node *last_child = node->child;

			while(last_child->next != NULL)
				last_child = last_child->next;

			last_child->next = child;
			child->prev = last_child;
		}
		else {
			node->child = child;
		}

		child->parent = node;
	}
}

void xml_clear_child(struct xml_node *node)
{
	while(node->child)
		xml_delete_tree(node->child);
}

struct xml_node* xml_text_child(struct xml_node *node)
{
	struct xml_node *child = NULL;

	if(node->child) {
		if(xml_is_text(node->child))
			child = node->child;
	}

	return child;
}

void xml_set_text(struct xml_node *node, char *text)
{
	if(xml_is_text(node)) {
		char *text_buf = (char *) xml_malloc(strlen(text) + 1);
		strcpy(text_buf, text);
		xml_free(node->text);
		node->text = text_buf;
	}
}

static void _xml_element_count(struct xml_node *root, char *name, int *count)
{
	if(xml_is_element(root)) {
		struct xml_node *child = root->child;

		if(strcmp(root->name, name) == 0) {
			(*count) ++;
		}

		while(child) {
			_xml_element_count(child, name, count);
			child = child->next;
		}
	}
}

static int xml_element_count(struct xml_node *root, char *name)
{
	int count = 0;

	_xml_element_count(root, name, &count);

	return count;
}

static void _xml_find_element(struct xml_node *root, char *name, struct xml_node_set *node_set)
{
	if(xml_is_element(root)) {
		struct xml_node *child = root->child;

		if(strcmp(root->name, name) == 0) {
			node_set->node[node_set->count] = root;
			node_set->count ++;
		}

		while(child) {
			_xml_find_element(child, name, node_set);
			child = child->next;
		}
	}
}

struct xml_node_set* xml_find_element(struct xml_node *root, char *name)
{
	struct xml_node_set *node_set = NULL;
	int node_count;

	node_set = (struct xml_node_set *) xml_malloc(sizeof(struct xml_node_set));
	node_set->count = 0;
	node_count = xml_element_count(root, name);

	if(node_count)
		node_set->node = (struct xml_node **) xml_malloc(node_count * sizeof(struct xml_node *));
	else
		node_set->node = NULL;

	_xml_find_element(root, name, node_set);

	return node_set;
}

static void _xml_path_count(struct xml_node *root, char *path, int *count)
{
	if(xml_is_element(root)) {
		char *front = NULL, *rear = NULL;

		if((front = strstr(path, "/")) != NULL) {
			int name_len;
			char *name;
			front ++;

			if((rear = strstr(front, "/")) != NULL) {
				name_len = rear - front;
				name = (char *) xml_malloc(name_len + 1);
				memcpy(name, front, name_len);
				name[name_len] = '\0';

				if(strcmp(root->name, name) == 0) {
					struct xml_node *child = root->child;

					while(child) {
						_xml_path_count(child, rear, count);
						child = child->next;
					}
				}
				
				xml_free(name);
			}
			else {
				name_len = strlen(path) - (front - path);
				name = (char *) xml_malloc(name_len + 1);
				strcpy(name, front);

				if(strcmp(root->name, name) == 0)
					(*count) ++;

				xml_free(name);
			}
		}
	}
}

static int xml_path_count(struct xml_node *root, char *path)
{
	int count = 0;

	_xml_path_count(root, path, &count);

	return count;
}

static void _xml_find_path(struct xml_node *root, char *path, struct xml_node_set *node_set)
{
	if(xml_is_element(root)) {
		char *front = NULL, *rear = NULL;

		if((front = strstr(path, "/")) != NULL) {
			int name_len;
			char *name;
			front ++;

			if((rear = strstr(front, "/")) != NULL) {
				name_len = rear - front;
				name = (char *) xml_malloc(name_len + 1);
				memcpy(name, front, name_len);
				name[name_len] = '\0';

				if(strcmp(root->name, name) == 0) {
					struct xml_node *child = root->child;

					while(child) {
						_xml_find_path(child, rear, node_set);
						child = child->next;
					}
				}
				
				xml_free(name);
			}
			else {
				name_len = strlen(path) - (front - path);
				name = (char *) xml_malloc(name_len + 1);
				strcpy(name, front);

				if(strcmp(root->name, name) == 0) {
					node_set->node[node_set->count] = root;
					node_set->count ++;
				}

				xml_free(name);
			}
		}
	}
}

struct xml_node_set* xml_find_path(struct xml_node *root, char *path)
{
	struct xml_node_set *node_set = NULL;
	int node_count;

	node_set = (struct xml_node_set *) xml_malloc(sizeof(struct xml_node_set));
	node_set->count = 0;
	node_count = xml_path_count(root, path);

	if(node_count)
		node_set->node = (struct xml_node **) xml_malloc(node_count * sizeof(struct xml_node *));
	else
		node_set->node = NULL;

	_xml_find_path(root, path, node_set);

	return node_set;
}

void xml_delete_set(struct xml_node_set *node_set)
{
	if(node_set->node)
		xml_free(node_set->node);

	xml_free(node_set);
}

static int xml_tree_size(struct xml_node *root)
{
	int size = 0;

	if(xml_is_text(root)) {
		size += strlen(root->text);
	}
	else if(xml_is_element(root)) {
		int start_size, end_size;
		struct xml_node *child = root->child;

		while(child) {
			size += xml_tree_size(child);
			child = child->next;
		}

		if(root->prefix && root->uri)
			start_size = 2 * strlen(root->prefix) + strlen(root->name) + strlen(root->uri) + 13;
		else if(root->prefix)
			start_size = strlen(root->prefix) + strlen(root->name) + 3;
		else if(root->uri)
			start_size = strlen(root->name) + strlen(root->uri) + 11;
		else
			start_size = strlen(root->name) + 2;

		if(root->prefix)
			end_size = strlen(root->prefix) + strlen(root->name) + 4;
		else
			end_size = strlen(root->name) + 3;

		size = size + start_size + end_size;
	}

	return size;
}

static void _xml_dump_tree(struct xml_node *root, char *xml_buf)
{
	if(xml_is_text(root)) {
		strcat(xml_buf, root->text);
	}
	else if(xml_is_element(root)) {
		struct xml_node *child = root->child;

		if(root->prefix && root->uri) {
			strcat(xml_buf, "<");
			strcat(xml_buf, root->prefix);
			strcat(xml_buf, ":");
			strcat(xml_buf, root->name);
			strcat(xml_buf, " xmlns:");
			strcat(xml_buf, root->prefix);
			strcat(xml_buf, "=\"");
			strcat(xml_buf, root->uri);
			strcat(xml_buf, "\">");
		}
		else if(root->prefix) {
			strcat(xml_buf, "<");
			strcat(xml_buf, root->prefix);
			strcat(xml_buf, ":");
			strcat(xml_buf, root->name);
			strcat(xml_buf, ">");
		}
		else if(root->uri) {
			strcat(xml_buf, "<");
			strcat(xml_buf, root->name);
			strcat(xml_buf, " xmlns=\"");
			strcat(xml_buf, root->uri);
			strcat(xml_buf, "\">");
		}
		else {
			strcat(xml_buf, "<");
			strcat(xml_buf, root->name);
			strcat(xml_buf, ">");
		}

		while(child) {
			_xml_dump_tree(child, xml_buf);
			child = child->next;
		}

		if(root->prefix) {
			strcat(xml_buf, "</");
			strcat(xml_buf, root->prefix);
			strcat(xml_buf, ":");
			strcat(xml_buf, root->name);
			strcat(xml_buf, ">");
		}
		else {
			strcat(xml_buf, "</");
			strcat(xml_buf, root->name);
			strcat(xml_buf, ">");
		}
	}
}

char *xml_dump_tree(struct xml_node *root)
{
	int xml_size;
	char *xml_buf;

	xml_size = xml_tree_size(root);
	xml_buf = (char *) xml_malloc(xml_size + 1);
	memset(xml_buf, 0, xml_size + 1);
	_xml_dump_tree(root, xml_buf);

	return xml_buf;
}

