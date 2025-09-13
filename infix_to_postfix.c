#include <stdio.h>
#include <ctype.h>   // for isalnum()
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Push function
void push(char c) {
    if(top == MAX-1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = c;
    }
}

// Pop function
char pop() {
    if(top == -1) {
        return -1;  // return invalid
    } else {
        return stack[top--];
    }
}

// Function to check precedence of operators
int precedence(char c) {
    if(c == '^') return 3;
    if(c == '*' || c == '/') return 2;
    if(c == '+' || c == '-') return 1;
    return 0;
}

// Function to convert infix to postfix
void infixToPostfix(char infix[]) {
    char postfix[MAX];
    int k = 0;
    char ch;

    for(int i=0; infix[i] != '\0'; i++) {
        ch = infix[i];

        // If operand, add to postfix
        if(isalnum(ch)) {
            postfix[k++] = ch;
        }
        // If '(', push to stack
        else if(ch == '(') {
            push(ch);
        }
        // If ')', pop until '('
        else if(ch == ')') {
            while(top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        }
        // If operator
        else {
            while(top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[k++] = pop();
            }
            push(ch);
        }
    }

    // Pop remaining operators
    while(top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0';
    printf("Postfix Expression: %s\n", postfix);
}

// Main function
int main() {
    char infix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
