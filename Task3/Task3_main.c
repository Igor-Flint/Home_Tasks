#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Task3_struct.h"

#define SIZE 128

int c;
char str[SIZE + 1];
int curstr;
int bytes_read;
char * buf;
int sizebuf;
int curbuf;

list_of_lines list;

typedef void * (*vertex)();
void * start();
void * word();
void * arrow();
void * greater();
void * amper();
void * vertStick();
void * newline();
void * stop();


void nullbuf() {
    if (buf != NULL) {
        free(buf);
    }
    buf = malloc(SIZE);
    sizebuf = SIZE;
    curbuf = 0;
    buf[0] = '\0';
}


void addsym() {
    if (curbuf >= sizebuf - 1) {
        sizebuf += SIZE;
        char *new_buf = realloc(buf, sizebuf);
        buf = new_buf;
    }
    if (buf != NULL) {
        buf[curbuf++] = (char)c;
    }
}


int symset(int c) {
    return (c != '\n') && (c != ' ') && (c != '\t') && (c != '>') && (c != '&') && (c != '|') && (c != EOF);
}


int getsym() {
    if (curstr >= bytes_read) {
        bytes_read = 0;
        curstr = 0;
        
        if (fscanf(stdin, "%128[^\n]", str) == 1) {
            bytes_read = strlen(str);
            int next_char = fgetc(stdin);
            if (next_char == '\n') {
                if (bytes_read < SIZE) {
                    str[bytes_read] = '\n';
                    bytes_read++;
                    str[bytes_read] = '\0';
                } else {
                    ungetc('\n', stdin);
                }
            } else if (next_char != EOF) {
                ungetc(next_char, stdin);
            }
        } else {
            int next_char = fgetc(stdin);
            if (next_char == '\n') {
                str[0] = '\n';
                bytes_read = 1;
                str[1] = '\0';
            } else if (next_char == EOF) {
                return EOF;
            } else {
                ungetc(next_char, stdin);
                return EOF;
            }
        }
    }
    
    if (curstr < bytes_read) {
        return (unsigned char)str[curstr++];
    } else {
        return EOF;
    }
}


void finish_word() {
    if (buf != NULL && curbuf > 0) {
        if (curbuf >= sizebuf) {
            buf = realloc(buf, sizebuf + 1);
            sizebuf += 1;
        }
        buf[curbuf] = '\0';

        if (curbuf > 0) {
            add_to_list(&list, buf);
        }
    }
    nullbuf();
}


int main() {
    vertex V = start;
    curstr = 0;
    bytes_read = 0;
    buf = NULL;
    nullbuf();
    create_list(&list);
    c = getsym();

    while(V != stop) {
        V = V();
    }
    
    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }
    return 0;
}


void* start() {
    if (c == ' ' || c == '\t') {
        c = getsym();
        return start;
    }
    else if (c == EOF) {
        finish_word();
        termlist(&list);
        sort_list(&list);
        printf("%d\n", list.length);
        for (int i = 0; i < list.length; i++) {
            if ((i % 2) == 0) printf("%s %s\n", list.data[i], list.data[i]);
			else printf("%s\n", list.data[i]);
        }
        free_list(&list);
        return stop;
    } else if (c == '\n') {
        finish_word();
        termlist(&list);
        sort_list(&list);
        printf("%d\n", list.length);
        for (int i = 0; i < list.length; i++) {
            if ((i % 2) == 0) printf("%s %s\n", list.data[i], list.data[i]);
			else printf("%s\n", list.data[i]);
        }
        free_list(&list);
        create_list(&list);
        c = getsym();
        return start;
    } else {
        char cprev = c;
        nullbuf();
        addsym();
        c = getsym();
        switch (cprev) {
            case '>': return arrow;
            case '&': return amper;
            case '|': return vertStick;
            case ';': 
            case '(': 
            case ')': 
            case '<':
                finish_word();
                return start;
            default: return word;
        }
    }
}


void* word() {
    if (symset(c)) {
        addsym();
        c = getsym();
        return word;
    } else {
        finish_word();
        return start;
    }
}


void* arrow() {
    if (c == '>') {
        addsym();
        c = getsym();
        finish_word();
        return start;
    } else {
        finish_word();
        return start;
    }
}


void* amper() {
    if (c == '&') {
        addsym();
        c = getsym();
        finish_word();
        return start;
    } else {
        finish_word();
        return start;
    }
}


void* vertStick() {
    if (c == '|') {
        addsym();
        c = getsym();
        finish_word();
        return start;
    } else {
        finish_word();
        return start;
    }
}


void* greater() {
    finish_word();
    return start;
}


void* newline() {
    finish_word();
    free_list(&list);
    create_list(&list);
    c = getsym();
    return start;
}


void* stop() {
    exit(0);
}
