#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
typedef struct Node
{
    float data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
} LinkedList;

typedef struct
{
    LinkedList *l;
} Stack;

LinkedList *init()
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head = NULL;
    return l;
}

Stack *initialize()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->l = init();
    return s;
}

Node *newNode(float x)
{
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->next = NULL;
    return n;
}

void insertAtBeginning(LinkedList *l, float x)
{
    Node *n = newNode(x);
    if (l->head == NULL) //if list empty
        l->head = n;
    else
    {
        n->next = l->head;
        l->head = n;
    }
}

void displayList(LinkedList *l)
{
    Node *temp = l->head;
    while (temp != NULL)
    {
        printf("%.2f ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void deleteFromBegining(LinkedList *l)
{
    if (l->head != NULL)
    {
        Node *temp = l->head;
        l->head = l->head->next;
        free(temp);
    }
}

//Stack Implementation Using Linked List

int isEmpty(Stack *s)
{
    int e = s->l->head == NULL;
    return e;
}

float pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Error: Stack underflow\n");
        exit(1);
    }
    float f = s->l->head->data;
    deleteFromBegining(s->l);
    return f;
}

void push(Stack *s, float value)
{
    insertAtBeginning(s->l, value);
}

float peek(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Error: Stack underflow\n");
        exit(1);
    }
    float f = s->l->head->data;
    return f;
}

void printStack(Stack *s)
{
    displayList(s->l);
}

// Helper function to check if a character is an operator
int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%';
}

// Helper function to get precedence of operators
int precedence(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

// Part 2: Infix to Postfix conversion
char *infixTopostfix(char *infix)
{
    Stack *opStack = initialize();
    char *post = malloc(strlen(infix) * 4);
    char *token = strtok(infix, " ");
    int pos = 0;

    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && strlen(token) > 1))
        {
            // It's a number (possibly negative or float)
            pos += sprintf(post + pos, "%s ", token);
        }

        else if (token[0] == '(')
        {
            push(opStack, '(');
        }
        else if (token[0] == ')')
        {
            // Pop until we find the opening parenthesis
            while (!isEmpty(opStack))
            {
                char op = (char)pop(opStack);
                if (op == '(')
                    break;
                pos += sprintf(post + pos, "%c ", op);
            }
        }
        else if (isOperator(token[0]))
        {
            // Handle negative numbers (unary minus)
            if (token[0] == '-' && (strlen(token) > 1 || pos == 0 || post[pos - 2] == '('))
            {
                // It's a negative number, not an operator
                pos += sprintf(post + pos, "%s ", token);
            }

            else
            {
                // It's an operator
                while (!isEmpty(opStack) && precedence((char)peek(opStack)) >= precedence(token[0]))
                {
                    char op = (char)pop(opStack);
                    pos += sprintf(post + pos, "%c ", op);
                }
                push(opStack, token[0]);
            }
        }
        token = strtok(NULL, " ");
    }

    // Pop all remaining operators
    while (!isEmpty(opStack))
    {
        char op = (char)pop(opStack);
        pos += sprintf(post + pos, "%c ", op);
    }

    post[pos] = '\0'; // Null-terminate the string

    // Cleanup
    while (!isEmpty(opStack))
        pop(opStack);
    free(opStack->l);
    free(opStack);
    return post;
}

// Evaluate a postfix expression and return the result
float evaluatePostfix(char *postfix)
{
    Stack *evalStack = initialize();
    char *token = strtok(postfix, " ");

    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && token[1] != '\0'))
        {
            // It's a number
            float num = atof(token);
            push(evalStack, num);
        }
        else if (isOperator(token[0]))
        {
            // It's an operator - pop two operands and apply the operation
            float op2 = pop(evalStack);
            float op1 = pop(evalStack);
            float res;

            switch (token[0])
            {
            case '+':
                res = op1 + op2;
                break;
            case '-':
                res = op1 - op2;
                break;
            case '*':
                res = op1 * op2;
                break;
            case '/':
                res = op1 / op2;
                break;
            case '%':
                res = fmod(op1, op2);
                break;
            case '^':
                res = pow(op1, op2);
                break;
            default:
                break;
            }
            push(evalStack, res);
        }
        token = strtok(NULL, " ");
    }

    float fres = pop(evalStack); // Final result
    free(evalStack);
    return fres;
}

// Wrapper function: convert infix to postfix, evaluate it, and print results
void Evaluate(char *infix)
{
    char *postfix = infixTopostfix(infix);
    printf("Output (Postfix): %s\n", postfix);
    float res = evaluatePostfix(postfix);
    printf("\nResult: %.4f\n", res);
    free(postfix);
}

int main()
{
    char infix[1000];
    printf("Welcome To The Fourth Assignment\n\n");
    printf("Enter infix expression (with spaces between tokens): ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';
    Evaluate(infix);
    return 0;
}
