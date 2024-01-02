#include "queue.h"

int put(Queue *q, char elem, int priority) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->priority = priority;
    new_node->elem = elem;
    int insert_check = insert(q, new_node);
    if (insert_check == 1) return 1;
    return 0;
}

char take_highest_priority(Queue *q, int *priority) {
    Node *elem;
    elem = *(q->body + q->size - 1);
    size_t min_index = q->size - 1;
    int deletion_check = del_item(q, min_index);
    if (deletion_check == 1) {
        fprintf(stderr, TAKE_ERROR);
        exit(EXIT_FAILURE);
    }
    char result = elem->elem;
    *priority = elem->priority;
    free(elem);
    return result;
}

int del_item(Queue *q, size_t index) {
    if (index != q->size - 1) {
        swap(q->body + index, q->body + q->size - 1);
        index = q->size - 1;
    }
    q->size -= 1;
    Node **tmp = realloc(q->body, q->size * sizeof(Node *));
    if (tmp == NULL && q->size != 0) return 1;
    q->body = tmp;
    for (int i = q->size / 2 - 1; i >= 0; i--) {
        heapify(q, i);
    }
    return 0;
}

void swap(Node **elem1, Node **elem2) {
    Node *tmp = *elem1;
    *elem1 = *elem2;
    *elem2 = tmp;
}

void heapify(Queue *q, int root) {
    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;
    Node *root_node = *(q->body + root);
    Node *left_node;
    Node *right_node;

    if (left < q->size) {
        left_node = *(q->body + left);
        if (left_node->priority > root_node->priority) {
            largest = left;
        }
    }

    if (right < q->size) {
        right_node = *(q->body + right);
        if (right_node->priority > root_node->priority) {
            largest = right;
        }
    }

    if (largest != (size_t)root) {
        swap(q->body + root, q->body + largest);
        heapify(q, largest);
    }
}

void free_queue(Queue *q) {
    for (size_t i = 0; i < q->size; i++) {
        free(*(q->body + i));
    }
    free(q->body);
}

int insert(Queue *q, Node *n) {
    q->size += 1;
    Node **tmp = realloc(q->body, q->size * sizeof(Node *));
    if (tmp == NULL) return 1;
    q->body = tmp;
    *(q->body + q->size - 1) = n;
    if (q->size != 1) {
        for (int i = q->size / 2 - 1; i >= 0; i--) {
            heapify(q, i);
        }
    }
    return 0;
}
