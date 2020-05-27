#include <stdlib.h>
#include <stdio.h>
#include <iostream>

struct ListNode
{
    int data;
    struct ListNode *next, *random;
    ListNode(int x) 
    { 
        data = x; 
        next = random = NULL; 
    } 
};

void print(ListNode *start) 
{ 
    ListNode *ptr = start; 
    while (ptr) 
    {
        printf("Data = %d , Random  = %d\n", ptr->data, ptr->random->data); 
        ptr = ptr->next; 
    } 
} 

ListNode* Clone(struct ListNode *head){
    //temp 用来指向当前结点，temp2用来指向当前结点对应的新结点
    struct ListNode *temp, *temp2;
    //step1:第一次扫描用temp->random 设置temp2->next,
    //利用temp 的random域指向结点temp2
    //第一次扫描中利用新节点的next域保存当前结点的random域的信息
    //再利用当前结点的random域保存指向新结点的指针，以便能再次访问新结点。
    temp = head;
    while(temp != NULL) {
        temp2 = (struct ListNode *)malloc(sizeof(struct ListNode));
        temp2->data = temp->data; 
        temp2->next = temp->random; 
        temp->random = temp2; 
        temp = temp->next;
    }

    //step2: 设置temp2->random，temp2->random是temp2->next应该指向的结点的旧副本。
    //因此temp->next->random是该结点的新副本
    temp = head; 
    while(temp != NULL) {
        temp2 = temp->random;
        temp2->random = temp->next->random; //这里根本跑不通 直接报错了 因为next不存在的情况下random无法复制
        temp = temp->next;
    }
    
    //step3: 第三次扫描，还原链表结点random域的信息并设置新结点的next域,得到链表的克隆链表
    temp = head;
    print(temp);
    while(temp != NULL) {
        printf("3\n");
        temp2 = temp->random;
        temp->random = temp2->next;  
        temp2->next = temp->next->random;  
        temp = temp->next;
        //printf("temp2->data=%d, temp2->next=%d,temp2->random=%d\n",temp2->data,temp2->next->data,temp2->random->data);
    }
    return temp2;
}



/*命令行: 复制一个链表 */
int main(int arg, char **argv)
{
    ListNode* T1 = new ListNode(1); 
    T1->next = new ListNode(2); 
    T1->next->next = new ListNode(3); 
  
    // 1's random points to 3 
    T1->random = T1->next->next; 
  
    // 2's random points to 1 
    T1->next->random = T1; 
  
    // 3's and 4's random points to 5 
    T1->next->next->random = T1->next; 
  
    printf("Original list : \n"); 
    print(T1); 
  
    printf("\nCloned list : \n"); 
    ListNode* T2 = Clone(T1); 
    print(T2); 
  
    return 0; 
}
 