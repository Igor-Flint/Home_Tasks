#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char *data;
    struct Node* next;
};

struct Node* createNode(const char* val)
{
    struct Node* newNode = calloc(1, sizeof(struct Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "No enough memory\n");
        return NULL;
    }
    
    newNode->data = malloc(strlen(val) + 1);
	if (newNode->data == NULL) {
		fprintf(stderr, "No enough memory\n");
		free(newNode);
		return NULL;
	}
	strcpy(newNode->data, val);
    newNode->next = NULL;
    return newNode;
}

void insertInEnd(struct Node **head, const char* val)
{
    struct Node* newNode = createNode(val);
    if (newNode != NULL)
    {
        if (*head == NULL)
        {
            *head = newNode;
            return;
        }

        struct Node* tmp = *head;
        while(tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = newNode;
    }
}

void deleteNodeByValue(struct Node **head, const char* key)
{
    struct Node *tmp = *head;
    struct Node* prev = NULL;

    while (tmp != NULL && strcmp(tmp->data, key) == 0)
    {
        *head = tmp->next;
        free(tmp->data);
		free(tmp);
        tmp = *head;
    }

    while(tmp != NULL)
    {
        while(tmp != NULL && strcmp(tmp->data, key) != 0)
        {
            prev = tmp;
            tmp = tmp->next;
        }

        if (tmp == NULL) return;

        prev->next = tmp->next;
        free(tmp->data);
		free(tmp);

        tmp = prev->next;
    }
}

void print(struct Node* head) {
    struct Node* current = head;
	while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->data);
		free(tmp);
    }
}

int main(void) {
    struct Node* head = NULL;

    int symbol;
    char *word = NULL;
	size_t word_size = 0;
	size_t i = 0;
	
	printf("Введите список слов:\n");
    while ((symbol = getchar()) != EOF) {
        if (symbol == ' ' || symbol == '\t' || symbol == '\n') {
            if (i > 0) {
                if (i >= word_size) {
					word_size = i + 1;
					word = realloc(word, word_size);
				}
				word[i] = '\0';
				insertInEnd(&head, word);
				i = 0;
            }
        } else {
            if (i + 1 >= word_size) {
                word_size = (word_size == 0) ? 32 : word_size * 2;
                word = realloc(word, word_size);
            }
            word[i] = symbol;
            i++;
        }
    }

    if (i > 0) {
        if (i >= word_size) {
            word_size = i + 1;
            word = realloc(word, word_size);
        }
        word[i] = '\0';
        insertInEnd(&head, word);
    }
	
	free(word);

    if (head == NULL) {
        printf("\n");
        return 0;
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    char *lastWord = malloc(strlen(current->data) + 1);
    strcpy(lastWord, current->data);

    deleteNodeByValue(&head, lastWord);
    insertInEnd(&head, lastWord);

    print(head);
    
    free(lastWord);
    freeList(head);

    return 0;
}
