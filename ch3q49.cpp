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

struct ListNode *AlternatMerge(struct ListNode *List1,struct ListNode *List2){
    struct ListNode *newNode = (struct ListNode*)(malloc(sizeof(struct ListNode)));
    struct ListNode *temp;
    newNode->next = NULL;
    temp = newNode;
    while(List1!=NULL && List2!=NULL){
        temp->next = List1;
        temp = temp->next;
        List1 = List1->next;
        temp->next = List2;
        List2 = List2->next;
        temp = temp->next;
    }
    if(List1!=NULL)
        temp->next = List1;
    else
        temp->next = List2;
    temp = newNode->next;
    free(newNode);
    return temp;
}


int main() 
{ 
    
    for(int i=1;i<=19;i++){
        addNode(i);
    }
    struct ListNode* A = start;

    start = NULL;

    for(int i=3;i<=22;i++){
        addNode(i);
    }
    struct ListNode* B = start;
    ListNode* newNode = AlternatMerge(A, B);
    print(newNode);
 
    return 0; 
} 
 