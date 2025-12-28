#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int  capacity;
    int  top;
} Stack;

typedef bool (*Commandfunc)(int argc, char *argv[], Stack *stack);

typedef struct {
    char       *name;
    Commandfunc func;
    char       *desc;
} Command;

Stack *stack_init(int capacity);
bool   is_full(Stack *stack);
bool   is_empty(Stack *stack);
bool   cmd_push(int argc, char *argv[], Stack *stack);
bool   cmd_pop(int argc, char *argv[], Stack *stack);
bool   cmd_peek(int argc, char *argv[], Stack *stack);
bool   cmd_help(int argc, char *argv[], Stack *stack);
bool   cmd_show(int argc, char *argv[], Stack *stack);
bool   cmd_capacity(int argc, char *argv[], Stack *stack);
bool   cmd_exit(int argc, char *argv[], Stack *stack);
int    cmd_parsing(char *command, char *argv[]);

Command commands[] = {{"push", cmd_push, "Push data to stack"},
                      {"pop", cmd_pop, "Pop data from stack"},
                      {"peek", cmd_peek, "Get the top data from stack"},
                      {"help", cmd_help, "Shows the list of commands available"},
                      {"show", cmd_show, "Show the stack's data"},
                      {"capacity", cmd_capacity, "Show the stack's capacity"},
                      {"exit", cmd_exit, "Exit"}};

bool is_exit        = false;
int  commands_count = sizeof(commands) / sizeof(commands[0]);

int main() {
    char  input_capacity[50];
    char  input_command[50];
    char *argv[5];
    char *end_capacity;
    int   int_capacity;
    int   argc;

    while (!is_exit) {
        puts("\n================================================");
        puts("============= Stack Implementation =============");
        puts("================================================\n");

        printf("Enter your stack capacity = ");
        fgets(input_capacity, sizeof(input_capacity), stdin);
        input_capacity[strcspn(input_capacity, "\n")] = '\0';
        int_capacity                                  = strtol(input_capacity, &end_capacity, 10);

        if (int_capacity < 0 || *end_capacity != '\0' || end_capacity == input_capacity) {
            printf("Error : invalid input capacity\n");
            continue;
        }

        Stack *stack = stack_init(int_capacity);

        printf("You have stack of size %d, what would you want to do? \n", int_capacity);

        while (!is_exit) {
            printf(">> ");

            fgets(input_command, sizeof(input_command), stdin);
            input_command[strcspn(input_command, "\n")] = '\0';

            argc = cmd_parsing(input_command, argv);
            for (int i = 0; i < commands_count; i++) {
                if (strcmp(argv[0], commands[i].name) == 0) {
                    commands[i].func(argc, argv, stack);
                }
            }
        }
    }

    return 0;
}

Stack *stack_init(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }

    stack->data = malloc(sizeof(Stack) * capacity);
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->top      = 0;

    return stack;
}

bool is_full(Stack *stack) {
    return stack->top == stack->capacity;
}

bool is_empty(Stack *stack) {
    return stack->top == 0;
}

bool cmd_push(int argc, char *argv[], Stack *stack) {
    char *end_data;
    int   data = strtol(argv[1], &end_data, 10);

    if (*end_data != '\0' || argv[1] == end_data || data < 0) {
        printf("Error : invalid value\n");

        return false;
    }

    if (is_full(stack)) {
        printf("Error : stack is full\n");

        return false;
    }

    stack->data[stack->top] = data;
    stack->top++;
    printf("Push operation success : %d has been added to the top of the stack.\n", data);

    return true;
}

bool cmd_pop(int argc, char *argv[], Stack *stack) {
    if (is_empty(stack)) {
        printf("Error : stack is empty\n");

        return false;
    }

    stack->top--;
    printf("Pop operation success : %d has been removed from the top of the stack.\n", stack->data[stack->top]);

    return true;
}

bool cmd_peek(int argc, char *argv[], Stack *stack) {
    printf("Top element of the stack : %d\n", stack->data[stack->top - 1]);

    return true;
}

bool cmd_help(int argc, char *argv[], Stack *stack) {
    int i = 0;

    printf("Available commands : \n");
    printf("   push {data}   : %s\n", commands[i++].desc);
    printf("   pop           : %s\n", commands[i++].desc);
    printf("   peek          : %s\n", commands[i++].desc);
    printf("   help          : %s\n", commands[i++].desc);
    printf("   show          : %s\n", commands[i++].desc);
    printf("   capacity      : %s\n", commands[i++].desc);
    printf("   exit          : %s\n", commands[i++].desc);

    return true;
}

bool cmd_show(int argc, char *argv[], Stack *stack) {
    printf("Stack's data : ");

    for (int i = 0; i < stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");

    return true;
}

bool cmd_capacity(int argc, char *argv[], Stack *stack) {
    printf("Stack's capacity : %d\n", stack->capacity);

    return true;
}

bool cmd_exit(int argc, char *argv[], Stack *stack) {
    is_exit = true;

    printf("Thank you for using this program.\n");

    return true;
}

int cmd_parsing(char *command, char *argv[]) {
    int   argc  = 0;
    char *token = strtok(command, " ");

    while (token != NULL) {
        argv[argc++] = token;
        token        = strtok(NULL, " ");
    }

    return argc;
}