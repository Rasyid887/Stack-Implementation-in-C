#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: delete stack
// TODO: is_full
// TODO: is_empty
// TODO: push stack
// TODO: pop stack

typedef struct {
    int *collection;
    int  capacity;
    int  size;
} Stack;

Stack *stack_init(int capacity);
bool   stack_delete(Stack *stack);
bool   is_full(Stack *stack);
bool   is_empty(Stack *stack);
bool   stack_push(Stack *stack, int data);
bool   stack_peek(Stack *stack, int *data);
bool   stack_pop(Stack *stack, int *data);

int main() {
    Stack *stack = stack_init(5);

    if (stack == NULL) {
        puts("Error");
        return 1;
    }

    if (is_empty(stack)) {
        puts("stack is empty");
    }

    stack_push(stack, 5);

    if (!is_empty(stack)) {
        puts("stack is not empty");
    }

    stack_push(stack, 6);
    stack_push(stack, 7);
    stack_push(stack, 8);

    printf("Stack size : %d\n", stack->size);

    int data  = 0;
    int data2 = 0;

    stack_pop(stack, &data);
    stack_peek(stack, &data2);

    printf("%d\n", data2);

    // stack_delete(stack);

    return 0;
}

Stack *stack_init(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    Stack *stack = malloc(sizeof(Stack));

    if (stack == NULL) {
        return NULL;
    }

    stack->collection = malloc(sizeof(int) * capacity);

    if (stack->collection == NULL) {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->size     = 0;

    return stack;
}

bool stack_delete(Stack *stack) {
    free(stack->collection);
    free(stack);

    return 1;
}

bool is_full(Stack *stack) {
    return stack->capacity == stack->size;
}

bool is_empty(Stack *stack) {
    return stack->size == 0;
}

bool stack_push(Stack *stack, int data) {
    if (is_full(stack)) {
        return false;
    }

    stack->collection[stack->size] = data;
    stack->size++;

    return true;
}

bool stack_peek(Stack *stack, int *data) {
    if (is_empty(stack)) {
        return false;
    }

    *data = stack->collection[stack->size - 1];

    return true;
}

bool stack_pop(Stack *stack, int *data) {
    if (is_empty(stack)) {
        return false;
    }

    stack->size--;
    *data = stack->collection[stack->size];

    return true;
}