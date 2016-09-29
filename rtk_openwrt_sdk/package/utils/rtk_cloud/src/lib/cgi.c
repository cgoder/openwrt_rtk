#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cgi_nv_pair {
   char *name;
   char *value;
   struct cgi_nv_pair *next;
};

struct cgi_nv_pair *cgi_pairs_head = NULL;

char* cgi_get_data(int *data_length)
{
	char *cgi_data;

	if(strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
		if(getenv("CONTENT_LENGTH")) {
			*data_length = atoi(getenv("CONTENT_LENGTH"));
			cgi_data = (char *) malloc(*data_length + 1);
			fread(cgi_data, 1, *data_length, stdin);    
			cgi_data[*data_length] = '\0';
		}
	}

	if(strcmp(getenv("REQUEST_METHOD"), "GET") == 0) {
		*data_length = strlen(getenv("QUERY_STRING"));
		cgi_data = (char *)malloc(*data_length + 1);
		strcpy(cgi_data, getenv("QUERY_STRING"));
		cgi_data[*data_length] = '\0';
	}
	
	return cgi_data;
}
static char cgi_sp2ch(char *special)
{
   char ch;
   ch = (special[0] >= 'A'?((special[0] & 0xdf)-'A')+10:(special[0]-'0'));
   ch *= 16;
   ch += (special[1] >= 'A'?((special[1] & 0xdf)-'A')+10:(special[1]-'0'));
   return ch;
}

static void cgi_build_pair(char *cgi_data, int front, int lear)
{
	int n_length, v_length, now_pos, count;
	struct cgi_nv_pair *tmp_nv_pair;
	int eq_pos = front;
	int n_percent = 0;
	int v_percent = 0;
	struct cgi_nv_pair *nv_pair = (struct cgi_nv_pair *) malloc(sizeof(struct cgi_nv_pair));
   
	for(now_pos = front; now_pos <= lear; now_pos++) {
		if(cgi_data[now_pos] == '=')
			eq_pos = now_pos;
		if(cgi_data[now_pos] == '%')
			if(eq_pos == front)
				n_percent ++;
			else
				v_percent ++;
	}
	n_length = eq_pos - front - 2 * n_percent;
	v_length = lear - eq_pos - 2 * v_percent;
	
	nv_pair->name = NULL;
	nv_pair->value = NULL;
	nv_pair->next = NULL;

	if(n_length) {
		nv_pair->name = (char *) malloc(n_length + 1);
		for(count = 0, now_pos = front; count < n_length; count ++)
			if(cgi_data[now_pos] == '%') {
				(nv_pair->name)[count] = cgi_sp2ch(&cgi_data[now_pos + 1]);
				now_pos += 3;
			}
			else {
				(nv_pair->name)[count] = cgi_data[now_pos];
				now_pos ++;
			}

		(nv_pair->name)[n_length] = '\0';
	}

	if(v_length) {
		nv_pair->value = (char *)malloc(v_length + 1); 
		for(count = 0, now_pos = eq_pos + 1; count < v_length; count ++)
			if(cgi_data[now_pos] == '%') {
				(nv_pair->value)[count] = cgi_sp2ch(&cgi_data[now_pos + 1]);
				now_pos += 3;
			}
			else {
				(nv_pair->value)[count] = cgi_data[now_pos];
				now_pos ++;
			}

		(nv_pair->value)[v_length] = '\0';
	}

	if(!cgi_pairs_head)
		cgi_pairs_head = nv_pair;
	else {
		for(tmp_nv_pair = cgi_pairs_head; tmp_nv_pair->next; tmp_nv_pair = tmp_nv_pair->next)
			;
		tmp_nv_pair->next = nv_pair;
	}
}

void cgi_init_param(void)
{
	int front_pos, lear_pos;
	int data_length;
	char *cgi_data = cgi_get_data(&data_length);

	if(data_length != 0) {   
		for(front_pos = 0, lear_pos = 0; lear_pos < data_length; lear_pos ++) {
			if(cgi_data[lear_pos] == '&') {
				cgi_build_pair(cgi_data, front_pos, lear_pos - 1);
				front_pos = lear_pos + 1;
			}
			if(cgi_data[lear_pos] == '+')
				cgi_data[lear_pos] = ' ';
		}

		cgi_build_pair(cgi_data, front_pos, lear_pos - 1);
	}

	free(cgi_data);
	cgi_data = NULL;
}

char *cgi_get_param(char *name)
{
	struct cgi_nv_pair *pt = cgi_pairs_head;

	while(pt) {
		if(!strcmp(pt->name, name))
			return pt->value;
		pt = pt->next;
	}

	return NULL;
}

void cgi_free(void)
{
	struct cgi_nv_pair *pt;

	if(cgi_pairs_head)
		do {
			pt = cgi_pairs_head;
			cgi_pairs_head = cgi_pairs_head->next;
			free(pt->name);
			free(pt->value);
			free(pt);
		} while(cgi_pairs_head);
}

