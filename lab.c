/* 	$Id: single.c,v 1.5 2018/02/07 15:06:32 michaelmcalpin Exp michaelmcalpin $	 */
/*
 * Lab 1
 *    The objective of this lab is to add the following
 * functionality to the code shown below.
 * 1) Insert a node after a specific data element in the 
 *    list. (This was implicit in the lecture this after-
 *    noon. It is now explicit.)
 * 2) Remove a node from the list.
 *
 * Note that both the insert and the removal (deletion)
 * would require that a node has been specified or
 * selected for insertion or removal.
 * Therefore the following functions would be needed.
 * A) Find, where the node's data would match the input
 *    data. 
 * B) There is an implication that the input file would
 *    be able to accept an insert, find, and delete command
 *    a specific node based on the input data value.
 * C) The input file specification should therefore be 
 *    modified to support the following input data format.
 *
 * Input data format:
 ** command value
 ** where a command is identified as follows:
 **   - i integerValue // i is the insert command
 **                    // where the node is inserted
 **                    // in a new node AFTER having
 **                    // "found" the node specified
 **                    // in the preceding "find"
 **   - f integerValue // f is the find command
 **   - d integerValue // d is the delete command
 **   - p              // p is the printAll command
 *
 * The function prototypes are:
 -> struct node * insert(struct node * start, int dataAfter, int newData);
 ***       returns the inserted node's address is successful 
 ***               NULL address if it fails.
 **** inserts newData in the created slot following first dataAfter
 **** if no dataAfter exists, add to the bottom of the list
 -> struct node * find(struct node * start, int data)
 ***       returns the found node's address is successful
 ***               NULL address if it fails to find the node.
 -> int delete(struct node * start, int data);
 ***       returns 0 if successful
 ***               1 if it fails.
 * See the sample input statements at the end of the source file.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node;


struct node * addToList(struct node *base, int data)
{
  struct node *newNode = NULL;

  if (base == NULL)
    {
      base = malloc( sizeof(struct node));
      // malloc defend
      base->data = data;
      base->next = NULL;
      return base;
    }
  //Find the bottom of the list starting from the base
  while (base->next != NULL)
    {
      base = base->next;
    }
  //Now at the end of the list
  newNode = malloc( sizeof(struct node)); //get memory for new node
  //Defend against bad malloc
  base->next = newNode; // add the new node to bottom of the list
  newNode->data = data; // slap the data into the list
  newNode->next = NULL; // terminate the list by setting next to NULL
  return base; //return the new end of the list to the caller

  //Shouldnt we return newNode?
}

/*
 * Walk the list and print the data
 */

void printList(struct node *list)
{
  while (list != NULL)
    {
      fprintf(stdout, "data: %3d\n", list->data);
      list = list->next;
    }
  return;
}
node * insert(node * start, int newData, int dataEventually) {
node * new = start;
node * n;
while(new != NULL && new->data != dataEventually) {
new = new->next;
}
if(new == NULL)
return NULL;
/*Found insert new node*/
n = (node*)malloc(sizeof(node));
n->data = newData;
n->next = new->next;
new->next = n;
return n;
}
node * find(node * start, int data) {
node * new = start;
for(; new != NULL; new = new->next) {
if(new->data == data)
return new;
}
/* Not found */
return NULL;
}
int delete(node * start, int data) {
node * new, * prev;
for(prev = NULL, new = start; new != NULL; new = new->next) {
/* node delete found */
if(new->data == data)
break;
prev = new;
}
if(new == NULL)
return 0;
if(prev != NULL) {
/* new list */
prev->next = new->next;
}
free(new); /* location */
return 0;
}

/*
 * pass the input file to main, then add the data from the input file
 * to the list. NB The list starts as an empty list.
 */
int main(int argc, char **argv)
{
  struct node *root = NULL; // The root of the list
  struct node *temp = NULL; 
  //  struct node *base = NULL; // Placeholder for current end of the list
  char *inBuf = NULL; // input buffer
  int data = 0;
  
  FILE * ifp;
  
  inBuf = malloc(100); //get a 100 character buffer for input data
  if (NULL == inBuf) // Check for success
    { //Let 'em know we failed to get a buffer
      fprintf(stderr, "No memory - good bye!\n");
      return -1;
    }
  ifp = fopen(argv[1], "rwb"); //Get the filename from the command line
  if (NULL == ifp) // Check for success
    { //Let 'em know the filename wasn't found
      fprintf(stderr, "%s file not found.\n", argv[1]);
      return -1;
    }

  /*
   * Read the file, then add the data to the list
   * All the while keep track of the last added node in temp
   */
  while (fscanf(ifp, "%s", inBuf) != EOF)
    {
      fprintf(stdout, "%s\n", inBuf);
      data = atoi(inBuf);
      
       //So add a new node & fill it with data
      if (NULL == root) // First node add to the list
	{
	  root = addToList(root, data);
	}
      else
	{ // add to the bottom of the list
	  temp = addToList(root, data);
	  if (NULL == temp)
	    {
	      printf("Failed to add - good bye\n");
	      return -1;
	    }
	}
  /*write out print list*/
  printf("1. insert 23 \n");
  printf("2. insert 78 \n");
  printf("3. insert 900 \n");
  printf("4. insert 42 after 23 \n");
  printf("5. find 78 \n");
  printf("6. delete 78 \n");
  printf("7. print");
  printf("8. insert 47 after 905 \n");
  printf("9/ find 901 \n");
  /*scanf("%d" , &choice); */
  /*switch(choice)*/ {
  	/* case 1: printf("\n Insert a number: ");
  	scanf("%s", number); */
  	printf("Insert Number: ");
  /*	scanf("%d" , &number); */
  /*	ptr = addToList(name, number); */
  	break;
  }
	  }
    printList(root);
    fclose(ifp);
    
    return 0;
}

/*
 * The sample input file is based on the included "booyah2.txt"
 * file.
 * New input file with commands. (Note the comments are for
 * clarification and are NOT a requirement for this program.)
---Begin sample booyah2.txt
i 23 // insert 23
i 78 // insert 78
i 900  // insert 900 //remember if not two number the first is addToList only
i 23 42 // insert 42 after 23
p  // print
f 78  // find 78
d 78 // delete 78
p  // print
i 905 47  // insert 47 after 905 (failure: no afterData)
f 901  // find 901 (failure case test)
p //print
---End sample booyah2.txt
*/
