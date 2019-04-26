#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0

typedef struct threadedTree * threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
} threadedTree;

threadedPointer head;
threadedPointer find;
int findflag = 0;

threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void tpreorder(threadedPointer tree);
void tpostorder(threadedPointer tree);
void insertRight(char target1, threadedPointer target2);
void insertLeft(char target1, threadedPointer target2);
void printall(void);
threadedPointer getNewNode(char data);
void menu(void);

int main(void){
	menu();
	return 0;
}

void findata(threadedPointer head, char target){
	if (head != NULL){
		if (head->leftThread == FALSE)					// until reach the left leaf end of the tree.
			findata(head->leftChild, target);			// recursively call the leftChild findata function.
		if (head->data == target){
			find = head;								// find pointer points to the target node.
			findflag = 1;								// set the findflag = 1.
		}
		if (head->rightThread == FALSE)					// until reach the right leaf end of the tree.
			findata(head->rightChild, target);			// recursively call the rightChild findata function.
	}
}

threadedPointer insucc(threadedPointer tree){
	threadedPointer temp;
	temp = tree->rightChild;
	if (tree->rightThread == FALSE)				// if the node is not a right end leaf node.
		while (temp->leftThread == FALSE)		//  until reach the left end leaf node.
			temp = temp->leftChild;				// temp points to leftchild.
	return temp;
}

void tinorder(threadedPointer target){
	threadedPointer temp = target;
	for (;;){
		temp = insucc(temp);
		if (temp == target) break;
		printf("%3c", temp->data);
	}
}

void tpreorder(threadedPointer target){
	if(target != NULL) {
		printf ("%3c", target->data);
		if(target->leftThread == FALSE) tpreorder (target->leftChild);
		if(target->rightThread == FALSE) tpreorder (target->rightChild);
	}
}

void tpostorder(threadedPointer target){
	if(target != NULL) {
		if(target->leftThread == FALSE) tpostorder (target->leftChild);
		if(target->rightThread == FALSE) tpostorder (target->rightChild);
		printf ("%3c", target->data);
	}
}

void insertRight(char target1, threadedPointer target2){
	threadedPointer parent, child, temp;
	temp = head;
	findata(temp, target1);								// find target1 data.
	if (findflag == 0){
		printf("%c doen't exist! Retry..\n", target1);	// just exit the function and get another command.
		return;
	}
	else												// if found, initialize the findflag.
		findflag = 0;
	parent = find;										// parent  == find (target1)
	
	child = target2;
	child->rightChild = parent->rightChild;
	child->rightThread = parent->rightThread;

	child->leftChild = parent;
	child->leftThread = TRUE;

	parent->rightChild = child;
	parent->rightThread = FALSE;

	if(!child->rightThread) {
		temp = insucc(child);
		temp->leftChild = child;
	}
}

void insertLeft(char target1, threadedPointer target2){
	threadedPointer parent, child, temp;
	temp = head;
	findata(temp, target1);									// find target1 data.
	if (findflag == 0){
		printf("%c doen't exist! Retry..\n", target1);		// just exit the function and get another command.
		return;
	}
	else
		findflag = 0;										// if found, initialize the findflag.
	parent = find;											// parent  == find (target1)
	
	child = target2;
	child->leftChild = parent->leftChild;
	child->leftThread = parent->leftThread;

	child->rightChild = parent;
	child->rightThread = TRUE;

	parent->leftChild = child;
	parent->leftThread = FALSE;

	if(!child->leftThread) {
		temp = insucc(child);
		temp->rightChild = child;
	}
}

threadedPointer getNewNode(char data){
	threadedPointer temp;
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftChild = temp->rightChild = NULL;
	temp->rightThread = FALSE; temp->leftThread = TRUE;
	temp->data = data;
	return temp;
}

void printall(void){
	threadedPointer temp = head;
	temp = temp->leftChild;
	printf("preorder : ");
	tpreorder(temp);				// print preorder.
	printf("\n");
	temp = head; head->rightChild = head;
	printf("inorder : ");
	tinorder(temp);					// print inorder.
	printf("\n");
	temp = head;
	temp = temp->leftChild;
	printf("postorder : ");
	tpostorder(temp);				// print postorder.
	printf("\n");
}

void menu(void){
	FILE* fp = NULL;
	char buffer[10], *parent, *child;
	int  command;
	head = (threadedPointer)malloc(sizeof(threadedTree));	// initialize the root of tree.
	head->data = '-'; head->leftChild = NULL; head->rightChild = NULL; head->leftThread = TRUE; head->rightThread = FALSE;
	fp = fopen("input.txt", "r");
	while (1){
		fgets(buffer, sizeof(buffer), fp);								// get a string.
		command = atoi(strtok(buffer, " "));	// command = 0 or 1 or 2 each respectively implies insert left, insert right, end the process and print. 
		parent = strtok(NULL, " ");
		child = strtok(NULL, " ");
		if (command == 0){
			insertLeft(*parent, getNewNode(*child));
		}
		else if (command == 1){
			insertRight(*parent, getNewNode(*child));
		}
		else if (command == 2){
			printall();
			break;
		}
		else continue;
	}
	fclose(fp);
}
