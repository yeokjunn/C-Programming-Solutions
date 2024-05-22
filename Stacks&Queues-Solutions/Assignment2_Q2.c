///////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define SIZE 1000 //The limit of expression length

/////////////////////////////////////////////////

typedef struct _listnode{
   char item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
 } LinkedList;

////////////////////////////////// stack    ///////////////////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////// function prototypes //////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void infixtoPrefix(char* infix, char* prefix);
int precedence(char op); // you may use this function
void infixtoPostfix(char*, char*);

///////////////////////////////////////////////////////////////////////////////////////////////
void push(Stack *s, char item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

///////////////////////////////////////////////////////////////////////////////////////////////////
void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, char item);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    infixtoPrefix(infix, prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);
    return 0;
}

void infixtoPrefix(char* infix, char* prefix)
{
    //Stack Initialisation//
    Stack s;
    s.ll.head = NULL;
    s.ll.size = 0;

    int i, j = 0;
    char symbol;
    char reversedInfix[SIZE];

    //Loop to reverse the infix expression//
    for (i = strlen(infix)-1; i >= 0; i--)
    {
        symbol = infix[i];

        switch (symbol)
        {
        case '(':
            symbol = ')';
            reversedInfix[j++] = symbol; //Flipping ) operator//
            break;

        case ')':
            symbol = '(';
            reversedInfix[j++] = symbol; //Flipping ( operator//
            break;

        case '*':
        case '/':
        case '+':
        case '-':
            reversedInfix[j++] = symbol; //Putting all operators into reversedInfix//
            break;        
        default:
            reversedInfix[j++] = symbol; //Putting all operands into reversedInfix//
            break;
        }
    }
    reversedInfix[j] = '\0';
    
    //Converting reversedInfix array to Postfix form//
    char reversedPostfix[SIZE];
    infixtoPostfix(reversedInfix, reversedPostfix);

    //Reversing reversedPostfix to obtain prefix expression//
    j = 0;
    for (i = strlen(reversedPostfix)-1; i >= 0; i--)
    {
        symbol = reversedPostfix[i];

        switch (symbol)
        {
        case '(':
            symbol = ')';
            prefix[j++] = symbol; //Flipping ) operator//
            break;

        case ')':
            symbol = '(';
            prefix[j++] = symbol; //Flipping ( operator//
            break;

        case '*':
        case '/':
        case '+':
        case '-':
            prefix[j++] = symbol; //Putting all operators into reversedInfix//
            break;        
        default:
            prefix[j++] = symbol; //Putting all operands into reversedInfix//
            break;
        }        
    }
    prefix[j] = '\0';

}

void infixtoPostfix(char* infix, char* postfix)
{
    //Initialising Stack//
    Stack s;
    s.ll.head = NULL;
    s.ll.size = 0;

    //Reading the infix expression//
    int i, j = 0;
    for (i = 0; i < strlen(infix); i++)
    {
        char character;
        char operators;
        character = infix[i]; 

        switch (character)
        {
        case '(':
            push(&s, character);
            break;

        case ')':
            while (!isEmptyStack(&s) && peek(&s) != '(') 
            {
                operators = pop(&s);
                postfix[j++] = operators;
            }
            pop(&s); //Discarding left parentheses//
            break;

        case '/':
        case '*':
        case '+':
        case '-':
            while (!isEmptyStack(&s) && peek(&s) != '(' && (precedence(peek(&s)) > precedence(character)))
            {
                operators = pop(&s);
                postfix[j++] = operators;
            }
			push(&s, character);
            break;
        
        default: //If character is an operand//
            postfix[j++] = character;
            break;
        }
    }

    while (!isEmptyStack(&s))
    {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
    
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, char item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   char item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%c ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, char value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}