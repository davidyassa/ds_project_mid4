#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
typedef struct
{
    char data;
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

Node *newNode(char x)
{
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->next = NULL;
    return n;
}

void insertAtBeginning(LinkedList *l, char x)
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
        printf("%c ", temp->data);
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

char pop(Stack *s)
{
    char f = s->l->head->data;
    deleteFromBegining(s->l);
    return f;
}

void push(Stack *s, char value)
{
    insertAtBeginning(s->l, value);
}

char peek(Stack *s)
{
    return s->l->head->data;
}

int isEmpty(Stack *s)
{
    return s->l->head == NULL;
}

void printStack(Stack *s)
{
    displayList(s->l);
}

typedef struct FloatNode
{
    float data;
    struct FloatNode *next;
} FloatNode;

typedef struct
{
    FloatNode *head;
} FloatStack;

FloatStack *initFloatStack()
{
    FloatStack *s = (FloatStack *)malloc(sizeof(FloatStack));
    s->head = NULL;
    return s;
}

void pushFloat(FloatStack *s, float value)
{
    FloatNode *n = (FloatNode *)malloc(sizeof(FloatNode));
    n->data = value;
    n->next = s->head;
    s->head = n;
}

float popFloat(FloatStack *s)
{
    if (isEmptyFloat(s))
    {
        return DBL_MIN;
    }
    float val = s->head->data;
    FloatNode *temp = s->head;
    s->head = s->head->next;
    free(temp);
    return val;
}

int isEmptyFloat(FloatStack *s)
{
    return s->head == NULL;
}

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

char *infixTopostfix(char *infix)
{
    int j = 0;
    char *post = malloc(strlen(infix) * 4);
    Stack *s = initialize();

    for (int i = 0; i < strlen(infix); i++)
    {
        if (isspace(infix[i]))
            continue;

        if (infix[i] == '-' && (i == 0 || infix[i - 1] == '(' || isOperator(infix[i - 1]) || isspace(infix[i - 1])))
        {
            post[j++] = infix[i++];
            while (i < strlen(infix) && (isdigit(infix[i]) || infix[i] == '.'))
            {
                post[j++] = infix[i++];
            }
            post[j++] = ' ';
            i--;
        }
        else if (isdigit(infix[i]))
        {
            while (i < strlen(infix) && (isdigit(infix[i]) || infix[i] == '.'))
            {
                post[j++] = infix[i++];
            }
            post[j++] = ' ';
            i--;
        }
        else if (infix[i] == '.')
        {
            post[j++] = '0';
            post[j++] = infix[i++];
            while (i < strlen(infix) && isdigit(infix[i]))
            {
                post[j++] = infix[i++];
            }
            post[j++] = ' ';
            i--;
        }
        else if (infix[i] == '(')
        {
            push(s, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty(s) && peek(s) != '(')
            {
                post[j++] = pop(s);
                post[j++] = ' ';
            }
            if (!isEmpty(s))
                pop(s);
        }
        else
        {
            while (!isEmpty(s) && priority(peek(s)) >= priority(infix[i]))
            {
                post[j++] = pop(s);
                post[j++] = ' ';
            }
            push(s, infix[i]);
        }
    }

    while (!isEmpty(s))
    {
        post[j++] = pop(s);
        post[j++] = ' ';
    }

    post[j] = '\0';
    return post;
}

float eval(char x, float op1, float op2)
{
    if (x == '+')
        return (op1 + op2);
    if (x == '-')
        return (op1 - op2);
    if (x == '*')
        return (op1 * op2);
    if (x == '/')
        return (op1 / op2);
}

float evaluatePostfix(char *postfix)
{
    FloatStack *s = initFloatStack();
    float op1, op2, val;
    char *token = strtok(postfix, " ");

    while (token != NULL)
    {
        if (isOperator(token[0]) && strlen(token) == 1)
        {
            op2 = popFloat(s);
            op1 = popFloat(s);
            val = eval(token[0], op1, op2);
            pushFloat(s, val);
        }
        else
        {
            float num = strtof(token, NULL);
            pushFloat(s, num);
        }

        token = strtok(NULL, " ");
    }

    return popFloat(s);
}

void Evaluate(char *infix)
{
    char *postfix = infixTopostfix(infix);
    printf("Postfix Expression: %s\n", postfix);
    float res = evaluatePostfix(postfix);
    printf("\nResult: %.2f\n", res);
    free(postfix);
}

int main()
{
    char infix[100];
    printf("Welcome To The Fourth Assignment\n\n");
    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    Evaluate(infix);
    return 0;
}
