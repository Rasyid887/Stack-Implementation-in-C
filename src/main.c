#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *collection;
    int  capacity;
    int  size;
} Stack;

typedef bool (*CommandFunc)(int argc, char *argv[]);

typedef struct {
    const char *name;
    CommandFunc func;
    const char *desc;
} Command;

Stack *stack_init(int capacity);
bool   is_empty(Stack *stack);
bool   is_full(Stack *stack);
bool   stack_push(Stack *stack, int data);
bool   stack_pop(Stack *stack, int *data);
bool   stack_peek(Stack *stack, int *data);

bool stack_help(int argc, char *argv[]);

Command commands[] = {{"help", stack_help, "Shows the list of available commands."},
                      {"stack_push", stack_push, "Push value to stack"}};

const int commands_count = sizeof(commands) / sizeof(commands[0]);

int parse_input(char *input, char *argv[]) {
    int argc = 0;

    char *token = strtok(input, " ");
    while (token != NULL) {
        argv[argc++] = token;
        token        = strtok(NULL, " ");
    }
    return argc;
}

int main() {
    char  capacity_input[50];
    char  command[50];
    char *end;
    int   capacity;
    int   action;
    bool  is_exit1 = false;
    bool  is_exit2 = false;
    int   data1, data2;

    CommandFunc stack_help = stack_help;

    while (!is_exit1) {
        char *argv[10];
        int   argc;

        puts("\n================================================");
        puts("============= Stack Implementation =============");
        puts("================================================\n");

        printf("Enter stack's capacity = ");
        fgets(capacity_input, sizeof(capacity_input), stdin);
        capacity_input[strcspn(capacity_input, "\n")] = '\0';
        capacity                                      = strtol(capacity_input, &end, 10);

        if (end == capacity_input || *end != '\0') {
            puts("Error: invalid capacity input.");
            return 1;
        }

        if (capacity <= 0) {
            puts("Error: capacity out of range.");
            return 1;
        }

        Stack *stack = stack_init(capacity);

        if (stack == NULL) {
            puts("Error: stack init");
            return 1;
        }

        printf("You have stack of size %d, what would you want to do? \n", capacity);
        printf(">> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        argc = parse_input(command, argv); //

        for (int i = 0; i < 3; i++) {
            if (strcmp(argv[0], commands[i].name) == 0) {
                commands[i].func(argc, argv);
                break;
            }
        }

        // if (strcmp(argv[0], "help") == 0) {
        //     stack_help(argc, argv);
        // }

        // printf("Stack's data = ");
        // for (int i = 0; i < stack->size; i++) {
        //     printf("%d, ", stack->collection[i]);
        // }
        // printf("\n");

        // stack_push(stack, 10);
        // stack_push(stack, 11);
        // stack_push(stack, 12);

        // stack_pop(stack, &data1);

        // for (int i = 0; i < stack->size; i++) {
        //     printf("data %d = %d\n", i + 1, stack->collection[i]);
        // }

        // if (is_full(stack)) {
        //     puts("Stack is full");
        // } else {
        //     puts("Stack isn't full");
        // }

        // stack_peek(stack, &data2);

        // printf("Last data on the stack = %d\n", data2);

        is_exit1 = true;
    }

    return 0;
}

Stack *stack_init(int capacity) {
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

bool stack_help(int argc, char *argv[]) {
    (void)argc; // avoid warnings
    (void)argv;

    printf("Available commands:\n");
    printf("  stack_help            : Tampilkan bantuan\n");
    printf("  stack_push <value>    : Push nilai ke stack\n");
    printf("  stack_pop             : Pop nilai dari stack\n");
    printf("  exit                  : Keluar program\n");

    return true;
}

bool is_empty(Stack *stack) {
    return stack->size == 0;
}

bool is_full(Stack *stack) {
    return stack->size == stack->capacity;
}

bool stack_push(Stack *stack, int data) {
    if (is_full(stack)) {
        return false;
    }

    stack->collection[stack->size] = data;
    stack->size++;

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

bool stack_peek(Stack *stack, int *data) {
    if (is_empty(stack)) {
        return false;
    }

    *data = stack->collection[stack->size - 1];

    return true;
}