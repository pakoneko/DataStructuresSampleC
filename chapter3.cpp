//关于链表的问题集
//问题1利用链表实现栈 查看chapter4
//问题2 查找链表从尾部开始数的第n个结点
//对链表一次扫描来解决问题2

//高效方法：用两个辅助指针pNthNode 和pTemp ，初始时两个指针均指向链表的投结点，指针pTemp向后移动n个位置后，指针pNthNode才开始向后移动
//时间复杂度O(n) 空间复杂度O(1)
#include <stdlib.h>
#include <stdio.h>
#include <hash_set>

struct ListNode
{
    int data;
    struct ListNode *next;
};

struct ListNode *NthNodeFromEnd(struct ListNode *head, int NthNode)
{
    struct ListNode *pNthNode = NULL, *pTemp = head;
    for (int count = 1; count < NthNode; count++)
    {
        if (pTemp)
            pTemp = pTemp->next;
    }
    while (pTemp)
    {
        if (pNthNode == NULL)
        {
            pNthNode = head;
        }
        else
        {
            pNthNode = pNthNode->next;
        }
        pTemp = pTemp->next;
        if (pNthNode)
        {
            return pNthNode;
        }
        return NULL;
    }
}

//Q6 如何判断给定链表是以指针域为NULL的结点结束还是以一个循环链表结束
//如果存在环，一定有2个结点的next指针域指向同一个结点，相同的next指针域的值在有序序列中是相邻的。
//使用弗洛伊德的方法来解决Floyd-cycle-finding 算法：不同速度的移动辅助指针求解问题，2个指针进入环一定会相遇，来证明链表存在环
//slowPtr 乌龟指针每次移动一个位置 fastPtr 兔子指针一次移动两个位置

int DoesLinkedListHasLoop(struct ListNode *head)
{
    struct ListNode *slowPtr = head, *fastPtr = head;
    while ((slowPtr && fastPtr && fastPtr->next))
    {
        /* code */
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        if (slowPtr == fastPtr)
        {
            return 1;
        }
        return 0;
    }
}

//Q9 在O(n)的时间内求解Q6
//Floyd-cycle-finding. 借助2个在链表以不同速度移动的辅助指针求解，2个指针进入环一定会相遇，如果相遇了表明链表存在环。
//slowPtr(乌龟)指针每次移动一个位置fastPtr(兔子)每次移动2个位置。 时间复杂度O(n) 空间复杂度O(1)
int DoesLinkedListHasLoop(struct ListNode * head){
    struct ListNode *slowPtr = head, *fastPtr=head;
    while(slowPtr && fastPtr && fastPtr->next){
        slowPtr =slowPtr->next;
        fastPtr = fastPtr->next->next;
        if(slowPtr == fastPtr)
            return 1;
    }
}

//Q10 给定一个指针指向链表L的首元结点，链表L有两种可能，它或者有尾部（蛇）或者它的最后一个结点指针域指向链表前面的某个结点（蜗牛））
//给出一个办法判断给定链表L是蛇还是蜗牛
//找到环以后重新设置指针slowPtr使其在此指向链表头部，然后每次同时将slowPtr和fastPtr向后移动一个位置，它们相遇的位置就是环的起始位置 ，通常这个方法用来消除环
//时间复杂度O(n) 空间复杂度O(1)

int FindBeginofLoop(struct ListNode *head)
{
    struct ListNode *slowPtr = head, *fastPtr = head;
    int loopExists = 0;
    while (slowPtr && fastPtr && fastPtr->next)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        if (slowPtr == fastPtr)
        {
            loopExists = 1;
            break;
        }
    }
    if (loopExists)
    {
        slowPtr = head;
        while (slowPtr != fastPtr)
        {
            fastPtr = fastPtr->next;
            slowPtr = slowPtr->next;
        }
        return (int)slowPtr;
    }
    return NULL;
}

//问题14：前面问题的扩展，求环的长度
//时间复杂度O(n) 空间复杂度O(1)
int FindLoopLength(struct ListNode *head)
{
    struct ListNode *slowPtr = head, *fastPtr = head;
    int loopExists = 0, counter = 0;
    while (slowPtr && fastPtr && fastPtr->next)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        if (slowPtr == fastPtr)
        {
            loopExists = 1;
            break;
        }
    }
    if (loopExists)
    {
        fastPtr = fastPtr->next;
        while (slowPtr != fastPtr)
        {
            fastPtr = fastPtr->next;
            counter++;
        }
        return counter;
    }
    return 0;
}

//Q15：在有序链表中插入一个结点
struct ListNode *InsertInSortedList(struct ListNode *head, struct ListNode *newNode)
{
    struct ListNode *current = head, *temp;
    if (!head) //有序列表为空
    {
        return newNode;
    }
    while (current != NULL && current->data < newNode->data)
    {
        temp = current;
        current = current->next;
    }
    newNode->next = current;
    temp->next = newNode;
}

//Q16 单链表的逆置reverse

//迭代版本 时间复杂度O(n) 空间复杂度O(1)
struct ListNode *ReverseList(struct ListNode *head)
{
    struct ListNode *temp = NULL, *nextNode = NULL;
    while (head)
    {
        nextNode = head->next;
        head->next = temp;
        temp = head;
        head = nextNode;
    }
    return temp;
}

//递归版本 时间复杂度O(n) 空间复杂度O(n)的递归栈的空间开销
struct ListNode *RecursiveReverse(struct ListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (head->next == NULL)
    {
        return head;
    }
    struct ListNode *secondElem = head->next;
    
    //第一个结点需要与其余节点断开链接，否则你会得到一个环
    head->next = NULL;
    //逆置除第一个结点之外的其余结点
    struct ListNode *reverseRest = RecursiveReverse(secondElem);
    secondElem->next = head;
    return reverseRest;
}

//Q17 假设2个单链表，在某个结点相交变成一个单链表。两个单链表的头指针已知，相交部分的起始结点位置，且2个弹量表中位于相交部分前面的结点数不知道。2个单链表相交部分前面的结点数可能不相同。
//List1 相交部分前面的结点数可能是n个，List2在相交部分前面的结点数可能是m个
//n m的关系可能是m=n或m<n或m>n 给出一个算法找出2个链表相交部分的起始结点。

//1.蛮力法，List1每个（指向）结点（的）指针依次与List2所有结点指针比较。时间复杂度O(mn)空间O(1)
//2.排序算法，不能使用
//3.散列表，用两个散列表存储2个链表每个结点指针信息进行比对。
//4.栈。用2个栈存储每个链表结点指针信息进行比对。弹出相同的那个元素，用辅助变量记住被弹出的栈。
//5.创建数组来存储结点指针然后找到重复元素。
//6.创建数组A存储第一个链表的指针，对A排序。然后第二个链表的每个指针在A中搜索。使用二分搜索。
//7.两个链表长度（L1 L2） O(n)+O(m)=O(max(m,n)),长度的差d——O(1)长链表的工作指针向后移动d个位置，比较2个工作指针是否相等，如果不相等就都向后移动1位置，然后重复前面的过程直到相等。
struct ListNode* FindIntersectingNode(struct ListNode* list1,struct ListNode* list2){
    int L1=0, L2=0, diff=0;
    struct ListNode *head1 = list1, *head2 = list2;
    while(head1!=NULL) {
        L1++;
        head1 = head1->next;
    }
    while(head2!=NULL) {
        L2++;
        head2 = head2->next;
    }
    if(L1<L2) {
        head1 = list2; head2=list1; diff = L2-L1;
    } else {
        head1 = list1; head2=list2; diff = L1-L2;
    }
    for(int i=0;i<diff; i++){
        head1 = head1->next;
    }
    while (head1 != NULL && head2 !=NULL)
    {
        if(head1 == head2)
            return head1;
        head1 = head1->next;
        head2 = head2->next;
    }
    return NULL;
    
}

//Q24 找到链表的中间位置
//1.蛮力法，每个结点统计结点总数，判断结点是否链表中心位置的结点。时间复杂度O(n²) 空间复杂度O(1)
//2.遍历链表，统计出链表的长度。
//3.找出链表长度后（假设长度为n），再次扫描链表，找出距离表头n/2个结点的中间位置 时间复杂度O(n)+O(n)≈O(n) 空间复杂度O(1)
//4.用散列表来解
//5.一次扫描高效解：2个指针P1,P2，分别以各自的速度向后移动，P1的移动速度是P2的两倍，P1到达表尾，P2指向节点就是中间位置。时间复杂度O(n) 空间复杂度O(1)

struct ListNode * FindMiddle(struct ListNode *head){
    struct ListNode *ptr1x, *ptr2x;
    ptr1x = ptr2x = head;
    int i=0;
    //持续循环过程知道ptr1x到达表尾为止（最后一个结点的next指针为NULL)
    while(ptr1x->next!=NULL){
        if(i==0){
            ptr1x = ptr1x->next; //仅仅第一个指针后移
            i=1;
        } else if(i==1){
            ptr1x=ptr1x->next; //两个指针均后移
            ptr2x=ptr2x->next;
            i=0;
        } 
    }
    return ptr2x; //返回指向中间结点的指针 ptr2x
}

//Q28 从表尾开始依次显示链表的所有结点的值
//递归遍历链表直到表尾，每次递归返回后再打印输出当前结点的值。

//下面将从表尾开始依次打印链表中所有结点的值
//（开始还没明白为什么这样写，后来发现printf放在调用的后面，OK）
void PrintListFromEnd(struct ListNode *head){
    if(!head)
        return;
    PrintListFromEnd(head->next);
    printf("%d", head->data);
}

//Q29 判断给定链表的长度是奇数还是偶数
//使用2x指针，就是一次移动2个结点的指针。指针移动结束时，表长偶数那么指针是空NULL，否则指针指向最后一个结点 O(floor(n/2)) ≈ O(n) 空间复杂度 O(1)
int IsLinkedListLengthEven(struct ListNode * listHead){
    while(listHead && listHead->next)
        listHead = listHead->next->next;
    if(!listHead)
        return 0;
    return 1;
}

//Q30 若一个链表的head指向第k个元素对应的结点，那么如何获得第k个元素之前的所有(1~k-1)元素的值？
//解：利用存储高效的链表(XOR链表) 

//Q31 给定2个有序链表，如何合并为一个有序链表？
//2个链表的长度 m，n
//recursive version 时间复杂度 O(n+m) 两个链表的长度。

struct ListNode *MergeSortedList(struct ListNode *a, struct ListNode *b) {
    struct ListNode *result = NULL;
    if(a == NULL)
        return b;
    if(b == NULL)
        return a;
    if(a->data <= b->data){
        result = a;
        result->next = MergeSortedList(a->next, b);
    } else {
        result = b;
        result->next = MergeSortedList(b, a->next);
    }
    return result;
}

//iterative version

struct ListNode *MergeSortedListIterative(struct ListNode *head1, struct ListNode *head2){
    struct  ListNode *newNode = (struct ListNode*)(malloc(sizeof(struct ListNode)));
    struct ListNode *temp;
    newNode = new ListNode;
    newNode->next=NULL;
    temp = newNode;
    while(head1!=NULL && head2!=NULL){
        if(head1->data<=head2->data){
            temp->next = head1;
            temp = temp->next;
            head1 = head1->next;
        } else{
            temp->next = head2;
            temp = temp->next;
            head2 = head2->next;
        }
    }
    if(head1!=NULL)
        temp->next = head1;
    else 
        temp->next = head2;
    temp = newNode->next;
    free(newNode);
    return temp;
}


//Q32 成对逆置链表结点 1->2->3->4 执行后 2->1->4->3
//recursive version

struct ListNode *ReversePairRcursive(struct ListNode *head) {
    struct ListNode *temp;
    if(head == NULL || head->next==NULL)
        return;
    else {
        //逆置第一对结点
        temp = head->next;
        head->next = temp->next;
        temp->next = head;
        head = temp;
        //对链表剩余部分递归调用该方法
        head->next->next = ReversePairRcursive(head->next->next);
        return head;
    }
}

//Iterative version 时间复杂度O(n),空间复杂度O(1)
struct ListNode *ReversePairIterative(struct ListNode *head) {
    struct ListNode *temp1 = NULL,*temp2= NULL, *current = head;
    while(current != NULL && current->next !=NULL) {
        if(temp1 != NULL ) {
            temp1->next->next = current->next;
        }
        temp1 = current->next;
        current->next = current->next->next;
        temp1->next = current;
        if(temp2 ==NULL)
            temp2 = temp1;
        current = current->next;
    }
    return temp2;
}

//Q33 给定一棵二叉树，将它转换为一个双向链表
//查看chapter6二叉树章节内容
//Q34 对链表排序
//查看chapter10

//Q35 将一个循环链表拆分成2个长度相等的循环链表，如果循环链表的结点数是奇数，那么拆分得到的第一个链表比第二个链表多一个结点。

//用Floyd环查找算法(Q9)找到循环链表的中间位置的结点和尾元结点，存储指向这两个结点的指针信息。
//循环链表的后半部分生成一个新的循环链表。
//循环链表的前半部分生成一个新的循环链表。
//设置两个新循环链表的头指针。

//结点结构的类型定义
struct ListNode {
    int data;
    struct ListNode *next;
};

void insertAtEndInList(struct ListNode **head, int data){
    struct ListNode *current = *head;
    struct ListNode *newNode = (struct ListNode *)(malloc(sizeof(struct ListNode)));
    if(!newNode) {
        printf("Memory Error");
        return;
    }

    newNode->data = data;
    while(current->next!= *head)
        current = current->next;
    newNode->next = newNode;
    if(*head == NULL)
        *head = newNode;
    else {
        newNode->next = *head;
        current->next = newNode;
    }
}

void SplitList(struct ListNode *head, struct ListNode **head1, struct ListNode **head2) {
    struct ListNode *slowPtr = head;
    struct ListNode *fastPtr = head;
    if(head == NULL)
        return;
    /*如果循环链表有奇数个结点，那么while循环结束时有fastPtr->next == head;
    如果偶数个结点，那么while循环结束时有fastPtr->next->next == head;*/
    while(fastPtr->next!=head && fastPtr->next->next!=head) {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
    }
    //如果被拆分链表有偶数个结点，那么向后移动fastPtr使其指向表尾
    if(fastPtr->next->next == head)
        fastPtr = fastPtr->next; //现在fastPtr在表尾
    //设置前半部分的头指针
    *head1 = head;
    //设置后半部分的头指针
    if(head->next!=head)
        *head2 = slowPtr->next;
    
    //生成由后半部分结点构成的新循环链表
    fastPtr->next = slowPtr->next;

    //生成由前半部分结点构成的新循环链表
    slowPtr->next = head;
}

//Q36 O(1)的时间复杂度内实现2个链表的首尾相连 ，下面哪种链表可以达到这个要求？
//循环双向链表 如果2个单链表或者双向链表的首尾相连需要遍历第一个链表找到表尾，把第二个链表链接到该表的表尾后，时间复杂度O(n)但2个循环双向链表是不需要遍历链表的。头指针访问表尾。

//Q37 判断一个链表是否回文(palindrome)？
//1.找到链表中间位置的节点 2.逆置链表后半部分 3.比较链表前半和后半部分，判断2个部分是否相同，4 再次逆置链表后半部分，把它附在前半部分的后面，得到原链表。 时间O(n) 空间O(1)

//Q38. 根据给定K值(K>0)，以K个结点构成块为单位逆置链表。
/*算法：逆置链表算法扩展
1)判断链表剩余部分（当前指针所指结点开始到表尾的部分）的结点数是否是大于等于K的。
a.如果是那获得并保持指向第K+1个结点的指针。
b.否则返回
2)逆置前K个结点。
3)设置逆置后第K个结点的next域使其指向第K+1个结点。
4)当前指针移动到第K+1个结点。
5)执行步骤1.
6)如果有前K个结点(即表长大于等于K),那么前K个结点中的第K个结点在逆置完成后成为新的头结点，否则可以直接返回原来的头指针。
*/
//该函数返回弟K个结点的直接后继结点的地址，即返回指向第K+1个结点的指针
struct ListNode * GetKPlusOneThNode(int K, struct ListNode *head){
    struct ListNode *Kth;
    int i = 0;
    if(!head)
        return head;
    for (i=0,Kth = head; Kth && (i<K); i++,Kth = Kth->next);
    if(i==K && Kth !=NULL)
        return Kth;
    return head->next;
}

//该函数判断链表head是否至少有K个结点
int HasKnodes(struct ListNode *head, int K){
    int i=0;
    for(i=0; head && (i<K);i++, head=head->next);
    if(i==K)
        return 1;
    return 0;
}

//对链表head前K个元素进行逆置
struct ListNode *ReverseBlockOfK_nodesInLinkedList(struct ListNode *head, int K){
    struct ListNode *cur = head, *temp, *next, *newHead;
    int i;
    if(K==0 || K==1)
        return head;
        if(HasKnodes(cur, K-1))
            newHead = GetKPlusOneThNode(K-1, cur);
        else
            newHead = head;
    while(cur && HasKnodes(cur, K)){
        temp = GetKPlusOneThNode(K, cur);
        i=0;
        while(i<K){
            next = cur->next;
            cur->next=temp;
            temp=cur;
            cur=next;
            i++;
        }
    }
    return newHead;
}

//Q39 链表能够获得O(1)的访问时间吗？
//可以 创建链表的的时候创建一个散列表，假设表长为n，n个结点指针信息保存到散列表的预处理时间是O(n),散列表创建好以后，访问链表任何一个结点时间是常数O(1),访问n个结点的时间是n*1个时间单位=n个时间单位
//平摊分析法可知访问节点的时间开销在O(1)时间内。空间复杂度是O(n)的散列表的空间开销。

//Q40 约瑟夫环（Josephus Circle） N个人决定通过下面的方式选出领导者：他们围成一个圈，依次排名，淘汰排在第M位的人，每当有人出局，排名重新开始（从1开始），哪一个人坚持到最后没有被淘汰。
//解：假设输入的循环链表N个结点，每个结点有一与之关联编号（1~N），头结点以编号1为data域的值。
struct ListNode *GetJosephusPosition(){
    struct ListNode *p, *q;
    int N, M;
    printf("Enter N(number of players):");
    scanf("%d", &N);

    printf("Enter M (every M-th player gets eliminated):");
    scanf("%d", &M);
    //创建包含所有参与游戏者的循环链表
    p = q = (struct  ListNode*)malloc(sizeof(struct ListNode));
    p->data = 1;
    for(int i=2;i<=N; ++i){
        p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        p = p->next;
        p->data = i;
    }
    //通过让最后一个结点的指针域指向第一个结点得到循环链表
    p->next = q;
    //淘汰第M个玩家直到最多剩下一位玩家为止
    for(int count=N;count>1; --count){
        for(int i=0;i< M-1;i++)
            p = p->next;
        p->next = p->next->next; //从循环链表中淘汰一位玩家
    }
    printf("Last player left standing (Josephus Position) is %d.\n", p->data);
}

//Q41 给定一个链表，链表中的结点有3个域，数据data，指针next，随即指针random（随机指向链表中的一个结点）给出克隆该链表算法。
//使用散列表保存新节点与链表中结点实例的对应关系。
//算法：扫描链表，对扫描到的每个结点X，创建一个新结点Y，用X的数据域对Y的数据域进行设置，将（X,Y)以X为关键字保存到散列表。
//第一次扫描时，Y的next域和random域被设置为NULL，值在链表第二次扫描确定。
//第一次扫描链表后在散列表保存链表每个结点X的副本Y。我们再次扫描链表，通过设置Y的两个指针域的值完成链表的克隆。
//时间复杂度O(n) 空间复杂度O(n)

struct ListNode {
    int data;
    struct ListNode *next;
    struct ListNode *random;
};
//假设HT是个HashTable(散列表) 这里struct没有提供
struct ListNode *Clone(struct ListNode *head){
    struct ListNode *X,*Y;
    struct HashTable *HT = CreateHashTable(); //创建散列表
    X = head;
    while (X != NULL) {
        Y = (struct ListNode *)malloc(sizeof(struct ListNode)); //第一次扫描表的时候创建新结点Y
        Y->data=X->data; //复制X的内容
        Y->next = NULL;
        Y->random = NULL;
        HT.insert(X,Y);   //X,Y对应关系放入散列表
        X = X->next;
    }
    X=head;
    while(X!=NULL){
        //从散列表中获得与X对应的新结点Y
        Y= HT.get(X);
        Y->next=HT.get(X->next); //复制X的其他值
        Y.setRandom = HT.get(X->random); //同上
        X = X->next;
    }
    //返回新链表的头指针，它是散列表中与head对应的那个Y
    return HT.get(head);
}
//Q42 不用额外空间解上题

void Clone_O1(struct ListNode *head){
    //temp 用来指向当前结点，temp2用来指向当前结点对应的新结点
    struct ListNode *temp, *temp2;
    //step1:第一次扫描用temp->random 设置temp2->next,
    //利用temp 的random域指向结点temp2
    //第一次扫描中利用新节点的next域保存当前结点的random域的信息
    //再利用当前结点的random域保存指向新结点的指针，以便能再次访问新结点。
    temp = head;
    while(temp!=NULL) {//假设temp中三个结点A B C, A{data:5,next:*B,random:*C},B{data:7,next:*C,random:*A},C{data:3,next:NULL,random:*B}
        temp2 = (struct ListNode *)malloc(sizeof(struct ListNode));
        temp2->data = temp->data; //A'->data = A->data = 5; B'->data= B->data = 7;  C'->data = C->data = 3; A'{data:5} B'{data:7} C'{data:3}
        temp2->next = temp->random; //A'->next = A->random = *C;B'->next = B->random= *A ; C'->next = C->random= *B;  A'{data:5,next:*C} B'{data:7,next:*A} C'{data:3,next:*B}
        temp->random = temp2; //A->random = A'{data:5,next:*C} ;B->random = B'{data:7,next:*A}; C->random = C'{data:3,next:*B}
        temp = temp->next;
    }


    //step2: 设置temp2->random，temp2->random是temp2->next应该指向的结点的旧副本。（旧副本依次为C B A）
    //因此temp->next->random是该结点的新副本

    //A'{data:5,next:*C} B'{data:7,next:*A} C'{data:3,next:*B}
    //A{data:5,next:B,random:A'{data:5,next:*C}},B{data:7,next:C,random:B'{data:7,next:*A}},C{data:3,next:NULL,random:C'{data:3,next:*B}}
    temp = head; 
    while(temp != NULL) {
        temp2 = temp->random; //A'{data:5,next:*C} B'{data:7,next:*A} C'{data:3,next:*B}
        temp2->random = temp->next->random; //A'->random = A->next->random = B->random = B'{data:7,next:*A};  B'->random = B->next->random = C->random = C'{data:3,next:*B}; C'->random = C->next->random = NULL;
        temp = temp->next;
    }

    
    //step3: 第三次扫描，还原链表结点random域的信息并设置新结点的next域,得到链表的克隆链表

    //A{data:5,next:B,random:A'{data:5,next:C}},    B{data:7,next:C,random:B'{data:7,next:A}},  C{data:3,next:NULL,random:C'{data:3,next:B}}
    //A'{data:5,next:*C,random:B'{data:7,next:*A}} B'{data:7,next:*A,random:C'{data:3,next:*B}} C'{data:3,next:*B,random:NULL}
    temp = head;
    while(temp!=NULL) { 
        temp2 = temp->random; //A'  B'  C' 
        temp->random = temp2->next; //A->random = A'->next = *C; B->random = B'->next = *A; C->random = C'->next = *B
        temp2->next = temp->next->random; //A'->next = A->next->random = B->random = B' , B'->next = B->next->random = C->random = C', C'->next = C->next->random = NULL;
        temp = temp->next;
    }
}
//A'{data:5,next:B',random:B'}

//Q43 如果链表的结点值不是奇数就是偶数，写一个算法保证奇数结点在偶数节点的后面
//A：把奇数结点都分到另一个链表，然后接到表尾 时间O(n) 空间O(1)

//Q44 在一个长度n的链表中，指定的某结点后面插入一个新结点的时间开销是
//A: O(1)

//Q45 查找模数结点，给定一个单链表，写一个程序找出该链表中最后一个编号满足n%k ==0的结点，这里的n是结点编号，k是一个整形的常量。如果表长n=19且k=3，那么应该返回第18个结点。

//事先不知道n, 时间复杂度O(n),空间复杂度O(1)

struct ListNode *modularNodeFromBegin(struct ListNode *head,int k){
    struct ListNode * modularNode;
    int i=0;
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

//Q46 从表尾开始查找模数结点：单链表，找到链表从表尾开始第一个编号满足n%k==0的结点，这里的n是结点编号，k是一个整形的常量。如果表长n=19且k=3，那么应该返回第18个结点。时间复杂度O(n) 空间复杂度O(1)

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

//Q47 查找分数结点：给一个单链表，编写程序找到第n/k个结点，n是链表长度。假设n未知。
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

//Q48 查找第√n 个结点：给一个单链表找出第√n个结点，n是链表长度。
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

//Q49 给定两个递增有序链表 List1={A1,A2,...,An} 和List2={B1,B2,...,Bm}合并他们得到新链表
//如果n>=m 那么新链表{A1,B1,A2,B2,...Am,Bm,Am+1,...An}
//如果m>=n 那么新链表{A1,B1,A2,B2,...An,Bn,An+1,...Bm}
//时间复杂度 O(min(n,m)) 空间复杂度 O(1)

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

//Q50 求无穷整数序列的中值 查看第七章 这里不能用二分搜索所以最小的时间开销是O(n)
//借助有序链表或者无需链表求解 灭有算法开销优势

//Q51 给定链表，如何修改使得这个链表的所有值为偶数结点都位于所有奇数节点的前面
//时间复杂度O(n) 空间复杂度O(1 )

struct ListNode *exchangeEvenOddList(struct ListNode *head) {
    //初始化odd list 和evenlist的头指针
    struct ListNode *oddList = NULL, *evenList = NULL;

    //用两个辅助指针始终分别指向odd list和even list的尾部
    struct ListNode *oddListEnd = NULL,*evenListEnd = NULL;
    struct ListNode *itr=head;
    if(head ==NULL){
        return;
    }
    else{
        while(itr !=NULL) {
            if(itr->data%2 ==0){
                if(evenList == NULL){
                    //第一个偶数结点
                    evenList = evenListEnd = itr;
                }
                else{
                    //将偶数结点插入even list的表尾
                    evenListEnd->next = itr;
                    evenListEnd = itr;
                }
            }
            else{
                if(oddList == NULL) {
                    //第一个奇数结点
                    oddList = oddListEnd = itr;
                }
                else {
                    //将技术节点插入oddlist的表尾
                    oddListEnd->next = itr;
                    oddListEnd = itr;
                }
            }
            itr = itr->next;
        }
        evenListEnd->next = oddList;
        return head;
    }
}
