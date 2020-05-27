#include <iostream>

using namespace std; 

struct ListNode
{
    int data;
    struct ListNode *next;
};

struct ListNode *start, *tail = NULL;  

void print(ListNode *start) 
{ 
    ListNode *ptr = start; 
    while (ptr) 
    {
        printf("Data = %d\n", ptr->data); 
        ptr = ptr->next; 
    } 
} 

void addNode(int data) {  
    //Create a new node  
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));  
    newNode->data = data;  
    newNode->next = NULL;  
      
    //Checks if the list is empty  
    if(start == NULL) {  
        //If list is empty, both head and tail will point to new node  
        start = newNode;  
        tail = newNode;  
    }  
    else {  
        //newNode will be added after tail such that tail's next will point to newNode  
        tail->next = newNode;  
        //newNode will become new tail of the list  
        tail = newNode;  
    }  
}  

struct ListNode *modularNodeFromEnd(struct ListNode *head, int k ){
    struct ListNode * modularNode=NULL;
    int i=0;
    if(k<=0){
        return NULL;
    }

    for(i=0;i<k;i++){
        if(head){
                head = head->next;
        }
        else {
            return NULL;
        }        
    }
    while(head!=NULL){
        modularNode = modularNode->next;
        head = head->next;
    }
    return modularNode;

}

struct ListNode *modularNodeFromBegin(struct ListNode *head,int k){
    struct ListNode * modularNode;
    int i=1;
    if(k<=0)
        return NULL;
    for(;head!=NULL;head=head->next){
        if(i%k==0){
            modularNode=head;
        }
        i++;
    }
    return modularNode;
}

struct ListNode *fractionalNodes(struct ListNode *head,int k){
    struct ListNode *fractionalNode = NULL;
    int i=0;
    if(k<=0)
        return NULL;
    for(;head!=NULL;head=head->next){
        if(i%k==0){
            if(fractionalNode==NULL){
                fractionalNode = head;
            }
            else {
                fractionalNode = fractionalNode->next;
            }
        }
        i++;
    }
    return fractionalNode;
}

struct ListNode *sqrtNode(struct ListNode *head){
    struct ListNode *sqrtN = NULL;
    int i=1, j=1;
    for(;head!=NULL;head=head->next){
        if(i==j*j){
            if(sqrtN==NULL){
                sqrtN = head;
            }
            else {
                sqrtN = sqrtN->next;
            }
            j++;
        }
        i++;
    }
    return sqrtN;
}


int main() 
{ 
    for(int i=1;i<=19;i++){
        addNode(i);
    }
    
    ListNode* modularNode = modularNodeFromBegin(start, 3);
    cout << "Modular node is : \n" << modularNode->data << endl; 

    ListNode* fractionalNode = fractionalNodes(start, 2);
    cout << "Fractional node is : \n" << fractionalNode->data << endl; 

    ListNode* sqrtN = sqrtNode(start);
    cout << "square root node is : \n" << sqrtN->data << endl; 
 
    return 0; 
} 
 