#ifndef LISTS_H
#define LISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *head;
    struct Node *tail;
} List;

List *empty();
int is_empty(List *l);
List *join(char *head, List *tail);
List *join_by_word(char *head, List *tail, char *word);
List *join_by_letter(char *head, List *tail, char *letters);
List *join_before_word(char *head, List *tail, char *word);
List *reverse(List *l);
List *filter(List *l, List *(*update) (char*, List*, char*), char *word);
void free_list(List *l);
void print_list(List *l);

#endif
