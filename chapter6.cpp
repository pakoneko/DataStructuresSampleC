#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chapter5.h>

//二叉树的结构
struct BinaryTreeNode
{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

/*
主要操作
插入元素到二叉树
删除元素
搜索元素
遍历

辅助操作
求大小
求高度
求结点最多层
求一对结点或更多结点的最早共同祖先
*/

//树的遍历可以有不同于线性结构的多种节点访问次序

//分为先序遍历DLR，中序遍历LDR，后序遍历LRD
//先序遍历
void PreOrder(struct BinaryTreeNode *root)
{
    if (root)
    {
        printf("%d", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

//非递归先序遍历 使用栈来记住当前结点，完成左子树遍历后能返回右子树
//访问当前结点，遍历左子树之前把当前结点压入栈进行保存，遍历完以后弹出栈顶结点，再遍历右子树，直到栈为空

void PreOrderNonRecursive(struct BinaryTreeNode *root)
{
    struct Stack *S = CreateStack();
    while (1)
    {
        while (root)
        {
            //处理当前结点
            printf("%d", root->data);
            Push(S, root);
            //如果左子树存在，就将其压入栈
            root = root->left;
        }
        if (IsEmptyStack(S))
            break;
        root = Pop(S);
        root = root->right;
    }
    DeleteStack(S);
}

//中序遍历 先遍历左子树，再访问根节点，再遍历右子树

void InOrder(struct BinaryTreeNode *root)
{
    if (root)
    {
        InOrder(root->left);
        printf("%d", root->data);
        InOrder(root->right);
    }
}

//非递归。与先序遍历非递归类似，不同点在于节点访问是发生在结点出栈时

void InOrderNonRecursive(struct BinaryTreeNode *root)
{
    struct Stack *S = CreateStack();
    while (1)
    {
        while (root)
        {
            Push(S, root);
            //如果左子树存在，就将其压入栈
            root = root->left;
        }
        if (IsEmptyStack(S))
            break;
        root = Pop(S);
        //处理当前结点
        printf("%d", root->data);
        root = root->right;
    }
    DeleteStack(S);
}

//后序遍历，先遍历左子树，再遍历右子树，访问根结点
//我们返回当前结点的时候，需要判断是从遍历左子树返回还是右子树返回的。

void PostOrder(struct BinaryTreeNode *root)
{
    if (root)
    {
        InOrder(root->left);
        InOrder(root->right);
        printf("%d", root->data);
    }
}
//第五版更新了LRD非递归算法
void PostOrderNonRecursive(struct BinaryTreeNode *root)
{
    struct SimpleArrayStack *S = CreateStack(); //创建一个栈
    struct BinaryTreeNode *previous = NULL;     //设置一个previous结点
    do
    {
        while (root != NULL)
        {
            Push(S, root);     //把根结点压入栈
            root = root->left; //指向左孩子，如果还有左孩子就继续把当前结点压入栈直到找不到左孩子
        }

        while (root == NULL && !IsEmptyStack(S))
        {                  //所有根结点和左子结点都进入了栈
            root = Top(S); //弹出栈顶的结点
            if (root->right == NULL || root->right == previous)
            { //如果右子结点不存在或者这是个根节点（刚从右结点遍历回来）就打印当前结点
                printf("%d", root->data);
                Pop(S);
                previous = root; //把当前结点设置为上一个结点
                root = NULL;
            }
            else
            {
                root = root->right; //右子结点存在或者之前是从左节点回来则遍历到右结点
            }
        }
    } while (!IsEmptyStack(S));
} 

//层次遍历 访问根节点
//遍历l层结点同事将l+1层结点插入队列
//访问下一层所有节点
//重复直到所有层结点都被访问 时间和空间复杂度都为O(n) 最坏情况最后一层所有结点都进入队列

void LevelOrder(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q = CreateQueue();
    if (!root)
        return;
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        //处理当前结点
        printf("%d", temp->data);
        if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
}

//Q1 找出二叉树最大元素

//找出左子树最大值，找右子树最大值，与根结点指比较，三个值中的最大值 时间复杂度和空间复杂度O(n)

int FindMax(struct BinaryTreeNode *root) {
    int root_val, left, right, max = INT_MIN;
    if(root !=NULL){
        root_val = root->data;
        left = FindMax(root->left);
        right = FindMax(root->right);
        //查找树的最大元素
        if(left>right)
            max = left;
        else max = right;
        if(root_val >max)
            max = root_val;
    }
}

//Q2 非递归找出二叉树最大元素
//利用队列和层级遍历 时间复杂度和空间复杂度O(n)

int FindeMaxUsingLevelOrder（struct BinaryTreeNode *root){
    struct BinaryTreeNode *temp;
    int max = INT_MIN;
    struct Queue *Q = CreateQueue();
    EnQueue(Q, root);
    while(!IsEmptyQueue(Q)){
        temp = DeQueue(Q);
        if(max<temp->data)
            max = temp->data;
        if(temp->left)
            EnQueue(Q, temp->left);
        if(temp->right)
            EnQueue(Q,temp->right);
    }
    DeleteQueue(Q);
    return max;
}

//Q3 算法：在二叉树中搜索指定元素
//向下递归进行比较
int FindInBinaryTreeUsingRecursion(struct BinaryTreeNode *root, int data) {
    int temp;
    //基本情况--空树 搜索失败返回false
    if(root == NULL)
        return 0;
    else {
        if(data == root->data)
            return 1;
        else {
            //否则在相应的子树进行递归
            temp  = FindInBinaryTreeUsingRecursion(root->left, data);
            if(temp!=0)
                return temp;
            else return(FindInBinaryTreeUsingRecursion(root->right, data));
        }
    }
    return 0;
}

//Q4 在二叉树搜索指定元素（非递归算法） 时间复杂度O(n) ,空间复杂度O(n)

int SearchUsingLevelOrder(struct BinaryTreeNode *root, int data){
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    if(!root)
        return -1;
    Q = CreateQueue();
    EnQueue(Q, root);
    while(!IsEmptyQueue(Q)){
        temp = DeQueue(Q);
        if(data == root->data)
            return 1;
        if(temp->left)
            EnQueue(Q, temp->left);
        if(temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return 0;
}

//Q5 给出一个算法，将一个元素插入二叉树中。
//给定二叉树，我们可以把元素插入任何想要插入的位置，需要用到层次遍历，插入遍历过程中遇到的第一个无左孩子或无右孩子的结点的左指针域或右指针域中
void InsertInBinaryTree(struct BinaryTreeNode *root, int data) {
    struct Queue *Q;
    struct BinaryTreeNode *temp;
    struct BinaryTreeNode *newNode;
    newNode = (struct BinaryTreeNode *) malloc(sizeof(struct BinaryTreeNode)); //内存分配
    newNode->left = newNode->right = NULL; //设置左右指针
    if(!newNode){
        printf("Memory Error");
        return;
    }
    if(!root) {
        root = newNode;
        return;
    }
    Q = CreateQueue();
    EnQueue(Q, root); //层级遍历
    while(!IsEmptyQueue(Q)) {
        temp = DeQueue(Q);
        if(temp->left) //找到左孩子则压入队列
            EnQueue(Q, temp->left);
        else {
            temp->left = newNode; //找不到左孩子就插入左孩子位置
            DeleteQueue(Q);
            return;
        }
    }
    DeleteQueue(Q);
}

//Q6 给出一个算法，求二叉树的大小 时间复杂度O(n) ,空间复杂度O(n)

int SizeOfBinaryTree(struct BinaryTreeNode *root) {
    if(root == NULL)
        return 0;
    else return (SizeOfBinaryTree(root->left))+ 1 +SizeOfBinaryTree(root->right);
}

//Q7 Q6的非递归解决方案
//依然是层次遍历

int SizeOfBTUsingLevelOrder(struct BinaryTreeNode *root){
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    int count = 0;
    if(!root)
        return -1;
    Q = CreateQueue();
    EnQueue(Q, root);
    while(!IsEmptyQueue(Q)){
        temp = DeQueue(Q);
        count++
        if(temp->left)
            EnQueue(Q, temp->left);
        if(temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return count;

}

//Q8 给出一个算法，按层次逆序方式打印二叉树层次遍历序列 O(n),O(n)
//这里用到了层次遍历和使用堆来逆置队列的算法 1234567 最后打印4567231
void LevelOrderTraversalInReverse(struct BinaryTreeNode *root) {
    struct Queue *Q; //定义队列
    struct Stack *s = CreateStack(); //创建一个堆
    struct BinaryTreeNode *temp; //一个临时变量
    if(!root) //如果没有根结点则返回
        return;
    Q = CreateQueue(); //创建队列
    EnQueue(Q, root); //把root压入队列
    while(!IsEmptyQueue(Q)) { //如果队列不为空 开始循环处理队列
        temp = DeQueue(Q); //出列赋值给temp
        if(temp->right) //如果有右子结点
            EnQueue(Q, temp->right); //压入队列（右结点会在左结点的下面）
        if(temp->left)  //如果有左子结点
            EnQueue(Q, temp->left); //压入队列
        Push(s, temp); //把temp压入栈(这样root就会在最下面)
    }
    while(!IsEmptyStack(s)) //循环处理栈中的信息，每个打印出来
        printf("%d", Pop(s)->data);
}

//Q9给出一个算法删除一棵二叉树
//遍历所有结点并且挨个删除LDR,DLR,LRD和层次遍历选哪个？
//必须要优先删除子结点，所以用LRD算法，使用层次遍历还需要其他开销，不做最优选了
void DeleteBinaryTree(struct BinaryTreeNode *root) {
    if(root == NULL) {
        
    }
}
