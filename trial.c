#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100

struct Stack {
    int top;
    char items[MAX];
};

int main() {
    char in[MAX], post[MAX];

    printf("Enter infix expression: ");
    fgets(in, MAX, stdin);

    infixToPostfix(in, post);

    printf("Postfix expression: %s\n", post);

    return 0;
}

int isEmpty(struct Stack *le_stack) {
    return (le_stack->top == -1);

}


void push(struct Stack *le_stack, char value) {
    if (le_stack->top == MAX - 1) {
        printf("Stack Overflow\n");
    }
    le_stack->items[++(le_stack->top)] = value;
}

char pop(struct Stack *le_stack) {
    if (isEmpty(le_stack)) {
        printf("The stack is empty.Please enter values first\n");
    }
    return le_stack->items[(le_stack->top)--];
}

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));

    stack->top = -1;

    int i = 0;
    int j = 0;

    while (infix[i] != '\0') {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            postfix[j++] = infix[i++];
        } else if (infix[i] == '(') {
            push(stack, infix[i++]);
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && stack->items[stack->top] != '(') {
                postfix[j++] = pop(stack);
            }
            if (!isEmpty(stack) && stack->items[stack->top] != '(') {
                printf("Invalid Expression\n");
                exit(EXIT_FAILURE);
            } else {
                pop(stack);
            }
            i++;
        } else {
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(stack->items[stack->top])) {
                postfix[j++] = pop(stack);
            }
            push(stack, infix[i++]);
        }
    }

    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
    }

    postfix[j] = '\0';

    free(stack);
}
