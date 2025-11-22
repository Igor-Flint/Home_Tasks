#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task3_struct.h"

void create_list(list_of_lines *list) {
    list->capacity = 10;
    list->length = 0;
    list->data = malloc(list->capacity * sizeof(char *));
	for (int i = 0; i < list->capacity; i++) {
        list->data[i] = NULL;
    }
}


void add_to_list(list_of_lines *list, const char *str) {
    if (str == NULL || strlen(str) == 0) {
        return;
    }

	if (list->length >= list->capacity) {
        list->capacity *= 2;
        char **new_data = realloc(list->data, list->capacity * sizeof(char *));
		list->data = new_data;
		
		for (int i = list->length; i < list->capacity; i++) {
            list->data[i] = NULL;
        }
	}


    list->data[list->length] = malloc(strlen(str) + 1);
	strcpy(list->data[list->length], str);
    list->length += 1;
}


void termlist(list_of_lines *list) {
	if (list->data == NULL) return;
	if (list->length >= list->capacity) {
        list->capacity = list->length + 1;
        list->data = realloc(list->data, list->capacity * sizeof(char *));
    }
    
    list->data[list->length] = NULL;
}


void sort_list(list_of_lines *list) {
    for (int i = 0; i < list->length - 1; i++) {
        for (int j = 0; j < list->length - i - 1; j++) {
            if (strcmp(list->data[j], list->data[j + 1]) > 0) {
                char *temp = list->data[j];
                list->data[j] = list->data[j + 1];
                list->data[j + 1] = temp;
            }
        }
    }
}


void free_list(list_of_lines *list) {
    for (int i = 0; i < list->length; i++) {
        free(list->data[i]);
    }
    free(list->data);
    list->data = NULL;
    list->length = 0;
	list->capacity = 0;
}
