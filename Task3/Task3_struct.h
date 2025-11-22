#ifndef TASK3_STRUCT_H
#define TASK3_STRUCT_H

typedef struct {
	char **data;
	int length;		/*длина массива на данный момент*/
	int capacity;	/*память, которую занимает массив на данный момент*/
} list_of_lines;

void create_list(list_of_lines *list);
void add_to_list(list_of_lines *list, const char *str);
void termlist(list_of_lines *list);
void sort_list(list_of_lines *list);
void print_list(const list_of_lines *list);
void free_list(list_of_lines *list);

#endif
