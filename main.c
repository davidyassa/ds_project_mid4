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
    if (l->head == NULL)
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

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%';
}

int precedence(char op)
{
    switch (op)
    {
    case '^':
        return 4;
    case '*':
    case '/':
    case '%':
        return 3;
    case '+':
    case '-':
        return 2;
    default:
        return 0;
    }
}

char *infixTopostfix(char *infix)
{
    Stack *opStack = initialize();
    char *post = malloc(strlen(infix) * 4);
    char *token = strtok(infix, " ");
    int pos = 0;

    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && strlen(token) > 1))
            pos += sprintf(post + pos, "%s ", token);

        else if (token[0] == '(')
        {
            push(opStack, '(');
        }
        else if (token[0] == ')')
        {
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
            if (token[0] == '-' && (strlen(token) > 1 || pos == 0 || post[pos - 2] == '('))
                pos += sprintf(post + pos, "%s ", token);

            else
            {
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
    while (!isEmpty(opStack))
    {
        char op = (char)pop(opStack);
        pos += sprintf(post + pos, "%c ", op);
    }
    post[pos] = '\0';
    while (!isEmpty(opStack))
        pop(opStack);
    free(opStack->l);
    free(opStack);
    return post;
}

float evaluatePostfix(char *postfix)
{
    Stack *evalStack = initialize();
    char *token = strtok(postfix, " ");

    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && token[1] != '\0'))
        {
            float num = atof(token);
            push(evalStack, num);
        }
        else if (isOperator(token[0]))
        {
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

    float fres = pop(evalStack);
    free(evalStack);
    return fres;
}

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
