#include "lists.h"

List *empty() {
    return NULL;
}

int is_empty(List *l) {
    return (l == empty());
}

List *join(char *head, List *tail) {
    List *result = (List *)malloc(sizeof(List));
    result->head = head;
    result->tail = tail;
    return result;
}

List *join_by_word(char *head, List *tail, char *word){
    if (strcmp(head, word) != 0) {
        tail = join(head, tail);
    }
    else {
        free(head);
    }
    return tail;
}

int is_in_string(char c, const char *string) {
    return strchr(string, c) != NULL;
}

List *join_by_letter(char *head, List *tail, char *letters) {
    char *tmp = letters;
    while (*tmp != 0) {
        if (is_in_string(*tmp, head)) {
            free(head);
            break;
        }
        tmp++;
    }
    if (*tmp == 0) tail = join(head, tail);
    return tail;
}

List *join_before_word(char *head, List *l, char *word) {
    List *result = empty();
    List *tmp;
    if (is_empty(l) && *word == 0) {
        tmp = l;
        result = join(head, result);
        free(tmp);
        return reverse(result);
    }
    while (!is_empty(l)) {
        tmp = l;
        if (strcmp(l->head,word) == 0) {
            result = join(head, result);
        }
        result = join(l->head, result);
        l = l->tail;
        free(tmp);
    }
    return reverse(result);
}

List *reverse(List *l) {
    List *result = empty();
    List *tmp;
    while (!is_empty(l)) {
        tmp = l;
        result = join(l->head, result);
        l = l->tail;
        free(tmp);
    }
    return result;
}

List *filter(List *l, List *(*update) (char*, List*, char*), char *word) {
    List *tmp;
    List *result = empty(); 
    while (!is_empty(l)) {
        tmp = l;
        result = update(l->head, result, word);
        l = l->tail;
        free(tmp);    
    }
    return result;
}

void free_list(List *l) {
    List *tmp;
    while (!is_empty(l)) {
    tmp = l;
    l = l->tail;
    free(tmp->head);
    free(tmp);
    }
}

void print_list(List *l) {
    List *t;
    printf("\n\"");
    while (!is_empty(l)) {
        printf("%s", l->head);
        t = l->tail;
        if (!is_empty(t)) {
            if (*t->head != 0) {
                printf(" ");
            }
        }
        l = l->tail;
    }
    printf("\"\n");
}
