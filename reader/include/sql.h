#ifndef __SQL_H
#define __SQL_H

int sql_create_tag_table(char *path);
int sql_insert_tag_info(char *path, tag_info_t *tag);
int sql_get_tag_info(char *path, tag_list_t **list);

#endif
