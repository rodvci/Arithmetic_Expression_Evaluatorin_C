#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100;

typedef struct {
    int top;
    char stack[STACK_SIZE];
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

void push(Stack* stack, char value) {
    if (stack->top == STACK_SIZE - 1) {
        printf("Invalid");
        exit(1);
    }
    stack->stack[++stack->top] = value;
}

char pop(Stack* stack) {
    if (stack->top == -1) {
            printf("Invalid");
        exit(1);
    }
    return stack->stack[stack->top--];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char ch) {
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

void reverseString(char* str) {
    int len = strlen(str);
    int i = 0;
    int j = len - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void infixToPostfix(char* infixExpression, char* postfixExpression) {
    int infixLen = strlen(infixExpression);
    int numCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < infixLen; i++) {
        char ch = infixExpression[i];
        if (isdigit(ch))
            numCount++;
        else if (isOperator(ch))
            operatorCount++;
    }

    if (numCount == infixLen || operatorCount == infixLen) {
        printf("Invalid infix expression\n");
        strcpy(postfixExpression, "*");
        return;
    }

    Stack stack;
    initialize(&stack);

    int postfixIndex = 0;

    for (int i = 0; i < infixLen; i++) {
        char ch = infixExpression[i];

        if (isalpha(ch) || isdigit(ch)) {
            postfixExpression[postfixIndex++] = ch;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (stack.top != -1 && stack.stack[stack.top] != '(') {
                postfixExpression[postfixIndex++] = pop(&stack);
            }
            if (stack.top != -1 && stack.stack[stack.top] == '(') {
                pop(&stack);
            } else {
                printf("Invalid infix expression\n");
                strcpy(postfixExpression, "*");
                return;
            }
        } else if (isOperator(ch)) {
            while (stack.top != -1 && stack.stack[stack.top] != '(' && precedence(ch) <= precedence(stack.stack[stack.top])) {
                postfixExpression[postfixIndex++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (stack.top != -1 && stack.stack[stack.top] != '(') {
        postfixExpression[postfixIndex++] = pop(&stack);
    }

    postfixExpression[postfixIndex] = '\0';
}

void infixToPrefix(char* infixExpression, char* prefixExpression) {
    int infixLen = strlen(infixExpression);
    int numCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < infixLen; i++) {
        char ch = infixExpression[i];
        if (isdigit(ch))
            numCount++;
        else if (isOperator(ch))
            operatorCount++;
    }

    if (numCount == infixLen || operatorCount == infixLen) {
        printf("Invalid infix expression\n");
        strcpy(prefixExpression, "*");
        return;
    }

    Stack stack;
    initialize(&stack);

    int prefixIndex = 0;

    reverseString(infixExpression);

    for (int i = 0; i < infixLen; i++) {
        char ch = infixExpression[i];

        if (isalpha(ch) || isdigit(ch)) {
            prefixExpression[prefixIndex++] = ch;
        } else if (ch == ')') {
            push(&stack, ch);
        } else if (ch == '(') {
            while (stack.top != -1 && stack.stack[stack.top] != ')') {
                prefixExpression[prefixIndex++] = pop(&stack);
            }
            if (stack.top != -1 && stack.stack[stack.top] == ')') {
                pop(&stack);
            } else {
                printf("Invalid infix expression\n");
                strcpy(prefixExpression, "*");
                return;
            }
        } else if (isOperator(ch)) {
            while (stack.top != -1 && stack.stack[stack.top] != ')' && precedence(ch) < precedence(stack.stack[stack.top])) {
                prefixExpression[prefixIndex++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (stack.top != -1 && stack.stack[stack.top] != ')') {
        prefixExpression[prefixIndex++] = pop(&stack);
    }

    prefixExpression[prefixIndex] = '\0';
    reverseString(prefixExpression);
}

int evaluatePrefix(char* expression) {
    int len = strlen(expression);
    int numCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < len; i++) {
        char ch = expression[i];
        if (isdigit(ch))
            numCount++;
        else if (isOperator(ch))
            operatorCount++;
    }

    if (numCount == len || operatorCount == len) {
        printf("Invalid prefix expression\n");
        return 0;
    }

    Stack stack;
    initialize(&stack);

    for (int i = len - 1; i >= 0; i--) {
        if (isdigit(expression[i])) {
            int num = expression[i] - '0';
            push(&stack, num);
        } else if (isOperator(expression[i])) {
            int num1 = pop(&stack);
            int num2 = pop(&stack);
            switch (expression[i]) {
                case '+':
                    push(&stack, num1 + num2);
                    break;
                case '-':
                    push(&stack, num1 - num2);
                    break;
                case '*':
                    push(&stack, num1 * num2);
                    break;
                case '/':
                    push(&stack, num1 / num2);
                    break;
            }
        }
    }

    int result = pop(&stack);

    if (stack.top != -1) {
        printf("Invalid prefix expression\n");
        return 0;
    }

    return result;
}

int evaluatePostfix(char* expression) {
    int len = strlen(expression);
    int numCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < len; i++) {
        char ch = expression[i];
        if (isdigit(ch))
            numCount++;
        else if (isOperator(ch))
            operatorCount++;
    }

    if (numCount == len || operatorCount == len) {
        printf("Invalid postfix expression\n");
        return 0;
    }

    Stack stack;
    initialize(&stack);

    for (int i = 0; i < len; i++) {
        if (isdigit(expression[i])) {
            int num = expression[i] - '0';
            push(&stack, num);
        } else if (isOperator(expression[i])) {
            int num2 = pop(&stack);
            int num1 = pop(&stack);
            switch (expression[i]) {
                case '+':
                    push(&stack, num1 + num2);
                    break;
                case '-':
                    push(&stack, num1 - num2);
                    break;
                case '*':
                    push(&stack, num1 * num2);
                    break;
                case '/':
                    push(&stack, num1 / num2);
                    break;
            }
        }
    }

    if (stack.top != 0) {
        printf("Invalid postfix expression\n");
        return 0;
    }

    return pop(&stack);
}

int evaluateInfix(char* expression) {
    int len = strlen(expression);
    int numCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < len; i++) {
        char ch = expression[i];
        if (isdigit(ch))
            numCount++;
        else if (isOperator(ch))
            operatorCount++;
    }

    if (numCount == len || operatorCount == len) {
        printf("Invalid infix expression\n");
        return 0;
    }

    Stack operandStack;
    Stack operatorStack;
    initialize(&operandStack);
    initialize(&operatorStack);

    for (int i = 0; i < len; i++) {
        char ch = expression[i];

        if (isdigit(ch)) {
            int operand = ch - '0';
            push(&operandStack, operand);
        } else if (isOperator(ch)) {
            while (operatorStack.top != -1 && operatorStack.stack[operatorStack.top] != '(' &&
                   precedence(ch) <= precedence(operatorStack.stack[operatorStack.top])) {
                char op = pop(&operatorStack);
                int operand2 = pop(&operandStack);
                int operand1 = pop(&operandStack);
                int result = 0;

                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        result = operand1 / operand2;
                        break;
                }

                push(&operandStack, result);
            }

            push(&operatorStack, ch);
        } else if (ch == '(') {
            push(&operatorStack, ch);
        } else if (ch == ')') {
            while (operatorStack.top != -1 && operatorStack.stack[operatorStack.top] != '(') {
                char op = pop(&operatorStack);
                int operand2 = pop(&operandStack);
                int operand1 = pop(&operandStack);
                int result = 0;

                switch (op) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        result = operand1 / operand2;
                        break;
                }

                push(&operandStack, result);
            }

            if (operatorStack.top != -1 && operatorStack.stack[operatorStack.top] == '(') {
                pop(&operatorStack);
            } else {
                printf("Invalid infix expression\n");
                return 0;
            }
        }
    }

    while (operatorStack.top != -1) {
        char op = pop(&operatorStack);
        int operand2 = pop(&operandStack);
        int operand1 = pop(&operandStack);
        int result = 0;

        switch (op) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
        }

        push(&operandStack, result);
    }

    if (operandStack.top != 0) {
        printf("Invalid infix expression\n");
        return 0;
    }

    return pop(&operandStack);
}

int main() {
    int choice;
    char infixExpression[STACK_SIZE];
    char postfixExpression[STACK_SIZE];
    char prefixExpression[STACK_SIZE];

    while (1) {
        system("cls");
        printf("Arithmetic Expression Evaluator\n");
        printf("\n");
        printf("Select an option:\n");
        printf("1. Convert infix to postfix\n");
        printf("2. Convert infix to prefix\n");
        printf("3. Evaluate prefix expression\n");
        printf("4. Evaluate postfix expression\n");
        printf("5. Evaluate infix expression\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                do {
                    system("cls");
                    printf("Enter an infix expression: ");
                    fgets(infixExpression, STACK_SIZE, stdin);
                    int len = strlen(infixExpression);
                    if (infixExpression[len - 1] == '\n') {
                    infixExpression[len - 1] = '\0';
                    }
                    infixToPostfix(infixExpression, postfixExpression);
                    printf("Postfix expression: %s\n", postfixExpression);

                    printf("\nChoose an option:\n");
                    printf("1. Convert another infix expression to postfix\n");
                    printf("2. Go back to the main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    getchar();

                    while (choice != 1 && choice != 2) {
                            system("cls");
                            printf("Invalid choice. Please enter a valid option.\n");
                            printf("1. Convert another infix expression to postfix\n");
                            printf("2. Go back to the main menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            getchar();
                    }

                    } while (choice == 1);
                break;
            case 2:
                do {
                    system("cls");
                    printf("Enter an infix expression: ");
                    fgets(infixExpression, STACK_SIZE, stdin);
                    int len = strlen(infixExpression);
                    if (infixExpression[len - 1] == '\n') {
                        infixExpression[len - 1] = '\0';
                    }
                    infixToPrefix(infixExpression, prefixExpression);
                    printf("Prefix expression: %s\n", prefixExpression);

                    printf("\nChoose an option:\n");
                    printf("1. Convert another infix expression to prefix\n");
                    printf("2. Go back to the main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    getchar();

                    while (choice != 1 && choice != 2) {
                            system("cls");
                            printf("Invalid choice. Please enter a valid option.\n");
                            printf("1. Convert another infix expression to postfix\n");
                            printf("2. Go back to the main menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            getchar();
                    }

                    } while (choice == 1);
                break;
            case 3:
                do {
                    system("cls");
                    printf("Enter a prefix expression: ");
                    fgets(prefixExpression, STACK_SIZE, stdin);
                    int len = strlen(prefixExpression);
                    if (prefixExpression[len - 1] == '\n') {
                        prefixExpression[len - 1] = '\0';
                    }
                    int prefixResult = evaluatePrefix(prefixExpression);
                    printf("Result: %d\n", prefixResult);

                    printf("\nChoose an option:\n");
                    printf("1. Evaluate another prefix expression\n");
                    printf("2. Go back to the main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    getchar();

                    while (choice != 1 && choice != 2) {
                            system("cls");
                            printf("Invalid choice. Please enter a valid option.\n");
                            printf("1. Convert another infix expression to postfix\n");
                            printf("2. Go back to the main menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            getchar();
                    }

                    } while (choice == 1);
                break;
            case 4:
                do {
                    system("cls");
                    printf("Enter a postfix expression: ");
                    fgets(postfixExpression, STACK_SIZE, stdin);
                    int len = strlen(postfixExpression);
                    if (postfixExpression[len - 1] == '\n') {
                        postfixExpression[len - 1] = '\0';
                    }
                    int postfixResult = evaluatePostfix(postfixExpression);
                    printf("Result: %d\n", postfixResult);

                    printf("\nChoose an option:\n");
                    printf("1. Evaluate another postfix expression\n");
                    printf("2. Go back to the main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    getchar();

                    while (choice != 1 && choice != 2) {
                            system("cls");
                            printf("Invalid choice. Please enter a valid option.\n");
                            printf("1. Convert another infix expression to postfix\n");
                            printf("2. Go back to the main menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            getchar();
                    }

                    } while (choice == 1);
                break;
            case 5:
                do {
                    system("cls");
                    printf("Enter an infix expression: ");
                    fgets(infixExpression, STACK_SIZE, stdin);
                    int len = strlen(infixExpression);
                    if (infixExpression[len - 1] == '\n') {
                        infixExpression[len - 1] = '\0';
                    } else {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) {
                        }
                    }
                    int infixResult = evaluateInfix(infixExpression);
                    printf("Result: %d\n", infixResult);

                    printf("\nChoose an option:\n");
                    printf("1. Evaluate another infix expression\n");
                    printf("2. Go back to the main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    getchar();

                    while (choice != 1 && choice != 2) {
                            system("cls");
                            printf("Invalid choice. Please enter a valid option.\n");
                            printf("1. Convert another infix expression to postfix\n");
                            printf("2. Go back to the main menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            getchar();
                    }

                    } while (choice == 1);
                    break;
            case 6:
                printf("\n");
                printf("\n");
                printf("Presented by: Group 5\n");
                printf("Exiting the program...");
                return 0;
            default:
                system("cls");
                printf("Invalid choice\n");
        }

        printf("Returning to the main menu...\n");
        sleep(2);
        printf("\n");
    }
    return 0;
}

