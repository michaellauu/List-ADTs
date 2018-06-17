// Michael Lau
// mlau10
// CMPS 101 - PA5

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

typedef struct NodeObj {
	// fields
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// newNode()
// Returns reference to newNode object. Initializes next and data fields.
// Private.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = N->prev = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pL, sets *pL to NULL.
// Private.
void freeNode(Node* pL){
	if( pL != NULL && *pL != NULL ){
		free(*pL);
		*pL = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
	if(pL != NULL && *pL != NULL) { 
		if(length(*pL) > 0) clear(*pL);	
		free(*pL);
		*pL = NULL;
	}
}
// Access functions
// Returns the number of elements in this List.
int length(List L) {
	if(L == NULL) {
		printf("List Error: length on NULL List\n");
		exit(1);
	}	
	return L->length;
}

// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L) {
	if(L == NULL) {
		printf("List Error: index on NULL List\n");
		exit(1);
	}	
	return L->index;
}

// Returns front element.
// Pre: length() > 0
int front(List L) {
	if(L == NULL) {
		printf("List Error: front on NULL List\n");
		exit(1);
	}	
	if(L->length < 1) {
		printf("List Error: length is less than 1.\n");
		exit(1);
	}
	return L->front->data;
}

// Returns back element.
// Pre: length() > 0
int back(List L) {
	if(L == NULL) {
		printf("List Error: back on NULL List\n");
		exit(1);
	}	
	if(L->length < 1) {
		printf("List Error: Length is less than 1.\n");
		exit(1);
	}
	return L->back->data;
}

// Returns cursor element.
// Pre: length() > 0
int get(List L) {
	if(L == NULL) {
		printf("List Error: get on NULL List\n");
		exit(1);
	}	
	if(L->length < 1) {
		printf("List Error: Length is less than 1a\n");
		exit(1);
	}
	else if(L->index < 0) {
		printf("List Error: get Cursor index is less than 0\n");
		exit(1);
	}
	return L->cursor->data;
}

// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B) { // Returns true if and only if this List and L are the same
	if(A == NULL || B == NULL) {
		printf("List Error: equals Null list\n");
		exit(1);
	}
	if(A->length != B->length) return 0;
	Node X = A->front;
	Node Y = B->front;
	while(X != NULL && Y != NULL) {
		if(X->data != Y->data) return 0;
		X = X->next;
		Y = Y->next;
	}
	return 1;
}
// Resets this List to its original empty state.
void clear(List L) {
	if(L == NULL) {
		printf("List Error: clear on NULL List\n");
		exit(1);
	}
	while(length(L) > 0) deleteFront(L);
	L->length = 0;
	L->index = -1;
}

// If List is non-empty, places the cursor under the front
// element, otherwise does nothing.
void moveFront(List L) {
	if(L == NULL) {
		printf("List Error: moveFront on NULL List\n");
		exit(1);
	}
	if(L->length > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

// If List is non-empty, places the cursor under the back
// element, otherwise does nothing.
void moveBack(List L) {
	if(L == NULL) {
		printf("List Error: get on NULL List\n");
		exit(1);
	}
	if(L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

// If cursor is defined and not at front, moves cursor one step
// toward front of this List, if cursor is defined and at front,
// cursor becomes undefined, if cursor is undefined does nothing.
void movePrev(List L) {
	if(L == NULL) {
		printf("List Error: movePrev on NULL List\n");
		exit(1);
	}
	if(L->cursor != NULL && L->index > 0) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else {
		L->cursor = NULL;
		L->index = -1;
	}
}

// If cursor is defined and not at back, moves cursor one step
// toward back of this List, if cursor is defined and at back,
// cursor becomes undefined, if cursor is undefined does nothing.
void moveNext(List L) {
	if(L == NULL) {
		printf("List Error: moveNext on NULL List\n");
		exit(1);
	}
	if(L->index < L->length-1 && L->cursor != NULL) {
		L->cursor = L->cursor->next;
		L->index++;
	}
	else {
		L->cursor = NULL;
		L->index = -1;
	}
}
// Insert new element into this List. If List is non-empty,
// insertion takes place before the front element.
void prepend(List L, int data) {
	if(L == NULL) {
		printf("List Error: prepend on NULL List\n");
		exit(1);
	}
	Node t = newNode(data);
	if (L->length == 0) L->front = L->back = t;
	else {
		t->next = L->front;
		L->front->prev = t;
		L->front = t;
	}
	L->length++;
	L->index++;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
	if(L == NULL) {
		printf("List Error: append on NULL List\n");
		exit(1);
	}
	Node t = newNode(data);
	if (L->length == 0) L->front = L->back = t;
	else {
		t->prev = L->back;
		L->back->next = t;
		L->back = t;
	}
	L->length++;
}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L,int data) {
	if(L == NULL) {
		printf("List Error: insertBefore on NULL List\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: Length is less than 0\n");
		exit(1);
	}
	if(L->index < 0) {
		printf("List Error: insertbefore Cursor index is less than 0\n");
		exit(1);
	}
	if(L->index == 0) prepend(L, data);
	else {
		Node t = newNode(data);
		t->prev = L->cursor->prev;
		t->next = L->cursor;
		L->cursor->prev->next = t;
		L->cursor->prev = t;
		L->length++;
		L->index++;
	}
}

// Inserts new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L,int data) {
	if(L == NULL) {
		printf("List Error: insertAfter on NULL List\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: Length is less than 0\n"); // Pre: length()>0, index()>=0
		exit(1);
	}
	if(L->index < 0) {
		printf("List Error: insertafter Cursor index is less than 0\n");
		exit(1);
	}
	if (L->index == L->length - 1) append(L,data);
	else {
		Node t = newNode(data);
		t->next  = L->cursor->next;
		t->prev = L->cursor;
		L->cursor->next->prev = t;
		L->cursor->next = t;
		L->length++;	
	}	
}

// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L) {
	Node N = NULL;
	if(L == NULL) {
		printf("List Error: deleteFront on NULL List\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: Length is less than 1b\n");
		exit(1);
	}
	N = L->front;
	if(length(L) == 1) {
		L->front = L->back = L->cursor = NULL;
		L->index = -1;
	}
	else {
		L->index--;
		L->front = L->front->next;
		L->front->prev = NULL;
	}
	L->length--;
	freeNode(&N);
}

// Deletes the back element.
// Pre: length() > 0
void deleteBack(List L) {
	Node N = NULL;
	if(L == NULL) {
		printf("List Error: deleteBack on NULL List\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: Length is less than 1c\n");
		exit(1);
	}
	N = L->back;
	if(length(L) == 1) {
		L->front = L->back = L->cursor = NULL;
		L->index = -1;
	}
	else {
		if((L->index) == (L->length-1)) L->index = -1;
		L->back = L->back->prev;
		L->back->next = NULL;
	}
	L->length--;
	freeNode(&N);
}

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L) {
	if(L == NULL) {
		printf("List Error: delete on NULL List\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: Length is less than 1d\n");	// Pre: length()>0, index()>=0
		exit(1);
	}
	if(L->index < 0) {
		printf("List Error: del Cursor index is less than 0\n");
		exit(1);
	}
	if(L->cursor == L->front) {
		deleteFront(L);
		return;
	}
	else if(L->cursor == L->back) {
		deleteBack(L);
		return;
	}
	else {
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->cursor = NULL;
		L->index = -1;
		L->length--;
	}
}

// Other methods
void printList(FILE* out, List L) { 
	Node t = L->front;	
	while(t != NULL) {
		fprintf(out, "%d", t->data);
		if(t->next != NULL) fprintf(out, " ");
		t = t->next;
	}
}

List copyList(List L) { // Returns a new List representing the same integer sequence as this
	List A = newList();   // List. The cursor in the new list is undefined, regardless of the
	Node t = L->front;   // state of the cursor in this List. This List is unchanged.
	while (t != NULL) {
		append(A,t->data);
		t = t->next;
	}
	return A;
}
