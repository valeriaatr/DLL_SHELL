#include<stdbool.h> // bool
#include<stdio.h> // printf()
#include<stdlib.h> // malloc()


struct node  {
    int data;
    struct node* next;
    struct node* prev;
} *initNode, *newNode;

//searches data value starting from the end of the list
struct node* findData(int data) {
    struct node *ref = initNode;
    while(ref!=NULL) {
		if (data==ref->data){
			return ref; //address return
		}
		else {
       			ref = ref->next;
		}
    }
	printf("Data not found");
    return ref;
}

// param n - is number of Nodes
// create_dll makes entire dl-list for n nodes
void create_dll(int n) {
	struct node *fin_node;
	
	int i=1;
	if (n>=1){
		initNode = (struct node*)malloc(sizeof(struct node));
		if (initNode==NULL){ //error --> terminate
			printf("Error - memory allocation");
			exit(1);
		}
		// put 1st node
		printf("Put number at node %d: ",i);
		int dat;
		scanf("%d",&dat);
		initNode->data = dat;
		initNode->prev = NULL;
		initNode->next = NULL;
		fin_node = initNode;

		for(i=2; i<=n; i++){
			newNode = (struct node*)malloc(sizeof(struct node));
			if (newNode==NULL){ //error --> terminate
				printf("Error - memory allocation");
				exit(1);
			}
			printf("Put number at node %d: ",i);
			scanf("%d",&dat);
			newNode->data = dat;
			newNode->prev = fin_node;
			newNode->next = NULL;
			
			fin_node->next = newNode;
			fin_node = newNode;
		}
	}
	else if (n<=1){//cannot create node
		printf("Unable to create node");
		exit(1);
	}
	
	
}

void list_content(){
	struct node * temp;
	temp = initNode; //start node ADDRESS 
	for(;temp != NULL;){ // traverse
		printf(" %d",temp->data);
     	   temp = temp->next; 
	}
}

void swap(struct node* ref1, struct node* ref2){
	struct node* temp=ref2;
	//------------if nodes are adjacent and both outer
	if(ref1->prev==NULL && ref2->next==NULL){
		ref1->next=NULL;
		ref2->prev=NULL;
		ref2->next=ref1;
		ref1->prev=ref2;
	}
	else if(ref1->next==NULL && ref2->prev==NULL){
		ref2->next=NULL;
		ref2->prev=ref1;
		ref1->next=ref2;
		ref1->prev=NULL;
	}
	//------------if nodes are adjacent and either one is head
	if(ref1->prev==NULL && ref1->next==ref2){
		temp->next = ref2->next;

		ref2->prev=NULL;
		ref2->next=ref1;
		ref1->prev=ref2;
		ref1->next=temp->next;
		ref1->next->prev=ref1;

	}
	else if(ref2->prev==NULL && ref2->next==ref1){
		temp->next = ref1->next;

		ref1->prev=NULL;
		ref1->next=ref2;
		ref2->prev=ref1;
		ref2->next=temp->next;
		ref2->next->prev=ref2;
	}
	//------------if nodes are adjacent and either one is tail
	if(ref2->next==NULL && ref2->prev==ref1){
		temp->prev = ref1->prev;

		ref1->prev=ref2;
		ref1->next=NULL;
		ref2->prev=temp->prev;
		ref2->next=ref1;
		ref2->prev->next=ref2;

	}
	else if(ref1->next==NULL && ref1->prev==ref2){
		temp->prev = ref2->prev;

		ref2->prev=ref1;
		ref2->next=NULL;
		ref1->prev=ref2;
		ref1->prev=temp->prev;
		ref1->prev->next=ref1;
	}
	
	//---------------if nodes are adjacent and neither is outer

	if ((ref2->next==ref1)&&(ref2->next!=NULL && ref2->prev!=NULL) && (ref1->next!=NULL && ref1->prev!=NULL)){
		temp->next = ref2->next;
		temp->prev = ref2->prev;

		ref2->next=ref1->next;
		ref2->prev=ref1;
		ref2->next->prev=ref2;

		ref1->next=ref2;
		ref1->prev->next=ref1;
		ref1->prev=temp->prev;
	}
	else if((ref2->prev==ref1)&&(ref2->next!=NULL && ref2->prev!=NULL) && (ref1->next!=NULL && ref1->prev!=NULL)){
		ref2->next=ref1;
		ref2->prev=ref1->prev;
		ref2->prev->next=ref2;

		ref1->next=temp->next;
		ref1->next->prev=ref1;
		ref1->prev=ref2;		
	}	
	//------------if nodes are NOT adjacent and both tail and head
	if((ref1->prev==NULL && ref2->next==NULL) && ref1->next!=ref2){
		temp->prev=ref2->prev;

		ref2->prev=NULL;
		ref2->next=ref1->next;
		ref2->next->prev=ref2;

		ref1->next=NULL;
		ref1->prev=temp->prev;
		ref1->prev->next=ref1;
	}
	else if((ref2->prev==NULL && ref1->next==NULL) && ref2->next!=ref1){
		temp->next=ref2->next;

		ref2->next=NULL;
		ref2->prev=ref1->prev;
		ref2->prev->next=ref2;

		ref1->prev=NULL;
		ref1->next=temp->next;
		ref1->next->prev=ref1;
	}

	
	//------------if nodes are NOT adjacent and either one is head
	if(ref2->prev!=ref1 && ref2->next!=NULL && ref1->prev==NULL){
		temp->next=ref1->next;
		
		ref1->next=ref2->next;
		ref1->prev=ref2->prev;
		ref1->next->prev=ref1;
		ref1->prev->next=ref1;

		ref2->prev=NULL;
		ref2->next=temp->next;
		ref2->next->prev=ref2;
	}
	else if(ref1->prev!=ref2 && ref1->next!=NULL && ref2->prev==NULL){
		temp->next=ref2->next;

		ref2->next=ref1->next;
		ref2->prev=ref1->prev;
		ref2->next->prev=ref2;
		ref2->prev->next=ref2;

		ref1->prev=NULL;
		ref1->next=temp->next;
		ref1->next->prev=ref1;
	}
	//------------if nodes are NOT adjacent and either one is tail
	if(ref2->prev!=ref1 && ref2->next==NULL && ref1->prev!=NULL){
		temp->prev=ref2->prev;

		ref2->next=ref1->next;
		ref2->prev=ref1->prev;
		ref2->next->prev=ref2;
		ref2->prev->next=ref2;

		ref1->next=NULL;
		ref1->prev=temp->prev;
		ref1->prev->next=ref1;
	}
	else if(ref1->prev!=ref2 && ref1->next==NULL && ref2->prev!=NULL){
		temp->prev=ref1->prev;

		ref1->next=ref2->next;
		ref1->prev=ref2->prev;
		ref1->next->prev=ref1;
		ref1->prev->next=ref1;

		ref2->next=NULL;
		ref2->prev=temp->prev;
		ref2->prev->next=ref2;
	}
	//------------if nodes are NOT adjacent and neither is outer
	if ((ref2->next!=ref1 && ref2->prev!=ref1)&&(ref2->next!=NULL && ref2->prev!=NULL) && (ref1->next!=NULL && ref1->prev!=NULL)){
		temp->next = ref2->next;
		temp->prev = ref2->prev;
		
		ref2->next = ref1->next;
		ref2->prev = ref1->prev;
		ref2->prev->next=ref2;
		ref2->next->prev=ref2;
			
		ref1->next = temp->next;
		ref1->prev = temp->prev;
		ref1->prev->next=ref1;
		ref1->next->prev=ref1;
	}
	//update starting node InitNode
	if(ref1->prev==NULL) {
		initNode=ref1;
		initNode->next=ref1->next;
	}
	else if(ref2->prev==NULL) {
		initNode=ref2;
		initNode->next=ref2->next;
	}
}
struct node* shift_left(struct node* ref, int n){
	struct node* temp=ref;
	if(temp==NULL) return ref;
	for(int i=1;i<=n && temp!=NULL;i++){
		temp=temp->next;
		free(temp->prev);
	}

	return temp; //updates head
}
int distance(struct node* ref1, struct node* ref2){
	struct node* temp=ref1;
	int i=0;
	while(temp->data!=ref2->data && temp->next!=NULL){
		temp = temp->next;
		i++;
	}
	if(temp->next==NULL) { //if reached the end, go back to search
		while(temp->data!=ref2->data){
		temp = temp->prev;
		i--;
		}
	}
	return i;
}
int main(){
	int n;
	printf("How many nodes? ");
	scanf("%d", &n);
	create_dll(n);
	printf("Initial list: ");
	list_content();
	printf("\nList size: %d",n);
	
	printf("\nShift by # of nodes: ");
	int shift;
	scanf("%d", &shift);
	if(shift>n){
		printf("Value too big. Enter new value: ");
		scanf("%d\n", &shift);
	}
	else{
	initNode=shift_left(initNode,shift);
	}

	printf("Shift left %d times: ", shift);
	list_content();

        printf("\nDistance between... ");
	int data1, data2;
	printf("\nNode 1: ");
	scanf("%d", &data1);
	printf("\nNode 2: ");
	scanf("%d", &data2);
	
	struct node* elem1, *elem2;
	elem1 = findData(data1);
	elem2 = findData(data2); 
	
	int dist = distance(elem1, elem2);
	printf("\nDistance between %d and %d: %d", data1, data2, dist);
	
	printf("\nSwap two nodes: ");
	printf("\nNode 1: ");
	scanf("%d", &data1);
	printf("\nNode 2: ");
	scanf("%d", &data2);
	swap(elem1, elem2);
	printf("\nList after swapping: ");
	list_content();
	
	return(0);
}

