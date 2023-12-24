#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/lists.h"
#include "lib/queue.h"
#include "errors.h"

#define MENU "Выберете действие над списком:\n\t(a)Удалить все вхождения некоторого слова\n\t(b)Вставить новое слово перед вхождением указанного слова\nВыберете действие: "

List *get_list(int (*ascii)[128], char *symbol);
char *get_word(char *symbol, int (*acii)[128]);
size_t get_N();
void set_ascii_to_zero(int (*arr)[128]);
char *find_N_max_indices(int arr[128], size_t N);

int main() {
    size_t N;
    List *string = empty();
    char symbol = 0;
    char state;
    char *word;
    int ascii[128];
    set_ascii_to_zero(&ascii);
    while (symbol != EOF) {
        N = get_N();
        string = get_list(&ascii, &symbol);
        if (string == NULL) {
            print_list(string);
            continue;
        }
        word = find_N_max_indices(ascii, N); 
        if (word == NULL) {
            fprintf(stderr, "%s", errors[0]);
            return 1;
        }
        string = filter(reverse(string), join_by_letter, word);
        string = reverse(string);
        print_list(string);
        free(word);
        word = NULL;
        state = 0;
        char *new_word;
        while (state != EOF) {
            printf(MENU);
            state = getchar();
            if (state == EOF) break;
            symbol = getchar();
            printf("Укажите слово: ");
            word = get_word(&symbol, &ascii);
            if (word == NULL) {
                fprintf(stderr, "%s", errors[0]);
                free_list(string);
                return 1;
            }
            switch (state) {
                    case 'a':
                    string = filter(reverse(string), join_by_word, word);
                    free(word);
                    word = NULL;
                    break;
                case 'b':
                    printf("Введите слово, которое нужно вставить: ");
                    symbol = getchar();
                    new_word = get_word(&symbol, &ascii);
                    if (new_word == NULL) {
                        free_list(string);
                        fprintf(stderr, "%s", errors[0]);
                        return 1;
                    }
                    string = join_before_word(new_word, string, word);
                    free(word);
                    word = NULL;
                    break;
                default:
                    fprintf(stderr, "%s", errors[3]);
                    free(word);
                    word = NULL;
                    break;
            }
            print_list(string);

        }
        free_list(string);
        clearerr(stdin);
        set_ascii_to_zero(&ascii);
        if (word != NULL) {
            free(word);
            word = NULL;
        }
    }
    return 0;
}

List *get_list(int (*ascii)[128], char *symbol) {
    printf("Введите строку: ");
    *symbol = 0;
    char *word;
    List *l = empty();
    while (*symbol != '\n') {
        word = get_word(symbol, ascii);
        if (*symbol == ' ' || *symbol == '\t' || *symbol == '\n' || *symbol == EOF) {
            if (word != NULL) {
                l = join(word, l); 
                word = NULL;
            }
            if (*symbol == EOF) {
                free_list(l);
                return empty();
            }
            if (*symbol != '\n') {
                *symbol = getchar();
            }

            continue;
        }
        if (*symbol != '\n') {
            *(*(ascii) + *symbol) += 1;
        }
        if (word == NULL) {
            free_list(l);
            return empty();
        }
    }
    return l;
}

char *get_word(char *symbol, int (*ascii)[128]) {
    char *word = (char *)malloc(2 * sizeof(char));
    char *alloc_check;
    char *tmp = word;
    if (*symbol != '\n') *tmp++ = *symbol;
    *tmp = 0;
    *symbol = getchar();
    if (*symbol == ' ' || *symbol == '\t') {
        free(word);
        return NULL;
    }
    if (*symbol == EOF) return word;
    while (*symbol != '\n' && *symbol != ' ' && *symbol != '\t') {
        *((*ascii) + *symbol) += 1;
        alloc_check = realloc(word, (strlen(word) + 2) * sizeof(char));
        if (alloc_check == NULL) return NULL;
        word = alloc_check;
        tmp = word;
        while(*tmp != 0) tmp++;
        *tmp++ = *symbol;
        *tmp = 0;
        *symbol = getchar();
        if (*symbol == EOF) return NULL;
    }
    return word;
}

size_t get_N() {
    size_t N;
    printf("\nВведите N: ");
    int scanned = scanf("%zu", &N);
    if (scanned == EOF) {
        exit(EXIT_SUCCESS);
    }
    while (scanned != 1 || N > 94) {
        fprintf(stderr, "%s",  errors[2]);
        getchar();
        scanned = scanf("%zu", &N);
    }
    getchar();
    return N;
}

void set_ascii_to_zero(int (*ascii)[128]) {
    for (int i = 0; i < 128; i++) {
        *(*(ascii) + i) = 0;
    }
}

char *find_N_max_indices(int arr[128], size_t N) {
    int put_check;
    Queue q;
    q.size = 0;
    q.body = NULL;
    char index = 0;
    int priority = 0;
    for (char i = 33; i < 127; i++) {
        if (q.size < N) {
            index = i;
            priority = *(arr + i);
            put_check = put(&q, index, priority);
            if (put_check == 1) return NULL;
            continue;
        }
        index = take_highest_priority(&q, &priority);
        if (*(arr + i) > priority) {
            index = i;
            priority = *(arr + i);
        }
        put_check = put(&q, index, priority);
        if (put_check == 1) return NULL;
    }
    char *result = (char *)malloc((q.size + 1) * sizeof(char));
    if (result == NULL) return NULL;
    char *tmp = result;
    while (q.size > 0) {
        *tmp++ = take_highest_priority(&q, &priority);
    }
    *tmp = 0;
    return result;
}
