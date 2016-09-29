#ifndef _CGI_H_
#define _CGI_H_

char* cgi_get_data(int *data_length);
void cgi_init_param(void);
char *cgi_get_param(char *name);
void cgi_free(void);

#endif
