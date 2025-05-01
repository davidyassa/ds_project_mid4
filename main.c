#include <stdio.h>
#include <stdlib.h>
typedef struct
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
    LinkedList*l;
}Stack;
LinkedList* init()
{
    LinkedList *l = (LinkedList*) malloc(sizeof(LinkedList));
    l->head = NULL;
    return l;
}
Stack* initialize ()
{
    Stack *s = (Stack*) malloc(sizeof(Stack));
    s->l = init();
    return s;
}
Node* newNode(float x)
{
    Node*n = malloc(sizeof(Node));
    n->data = x;
    n->next = NULL;
    return n;
}
void insertAtBeginning(LinkedList *l, float x)
{
    Node *n = newNode(x);
    if(l->head == NULL)
        l->head = n;
    else
    {
        n->next = l->head;
        l->head = n;
    }
}
void displayList (LinkedList *l)
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
    if(l->head != NULL)
    {
        Node *temp = l->head;
        l->head = l->head->next;
        free(temp);
    }
}
float pop (Stack *s)
{
    float f = s->l->head->data;
    deleteFromBegining(s->l);
    return f;
}
void push (Stack *s, float value)
{
    insertAtBeginning(s->l,value);
}
float peek (Stack *s)
{
    float f = s->l->head->data;
    return f;
}
int isEmpty(Stack *s)
{
    int e = s->l->head == NULL;
    return e;
}
void printStack(Stack*s)
{
    displayList(s->l);
}
char* infixTopostfix(char *infix)
{

}
float evaluatePostfix(char* postfix)
{

}
void Evaluate(char* infix)
{
    char* postfix = infixTopostfix(infix);
    float res = evaluatePostfix(postfix);
    printf("\nResult: %.2f\n",res);
}
int main()
{
    char infix[100];
    printf("Welcome To The Fourth Assignment\n\n");
    printf("Enter infix expression: ");
    scanf("%s",infix);
    Evaluate(infix);
    return 0;
}
