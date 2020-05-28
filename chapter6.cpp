#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max __max
//二叉树的结构
struct BinaryTreeNode
{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    int nMaxLeft;
    int nMaxRight;
};

#pragma region Queue
struct ListNode
{
    struct BinaryTreeNode *data;
    struct ListNode *next;
};

struct Queue
{
    struct ListNode *front;
    struct ListNode *rear;
};

struct Queue *CreateQueue()
{
    struct Queue *Q;
    struct ListNode *temp;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    if (!Q)
        return NULL;
    temp = (struct ListNode *)malloc(sizeof(struct ListNode));
    Q->front = Q->rear = NULL;
    return Q;
}

int IsEmptyQueue(struct Queue *Q)
{
    return (Q->front == NULL);
}

void EnQueue(struct Queue *Q, struct BinaryTreeNode *data)
{
    struct ListNode *newNode;
    newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!newNode)
        return;
    newNode->data = data;
    newNode->next = NULL;
    if (Q->rear)
        Q->rear->next = newNode;
    Q->rear = newNode;
    if (Q->front == NULL)
        Q->front = Q->rear;
}

struct BinaryTreeNode *DeQueue(struct Queue *Q)
{
    struct BinaryTreeNode *data;
    struct ListNode *temp;
    if (IsEmptyQueue(Q))
    {
        printf("Queue is Empty");
        return 0;
    }
    else
    {
        temp = Q->front;
        data = Q->front->data;
        Q->front == Q->front->next;
        free(temp);
    }
    return data;
}

void DeleteQueue(struct Queue *Q)
{
    struct ListNode *temp;
    while (Q)
    {
        temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    }
    free(Q);
}

#pragma endregion

#pragma region Stack
struct Stack
{
    int top;
    int capacity;
    int *array;
};

int Top(struct Stack *S)
{
    /*S->top == -1 用来判断栈是否为空*/
    if (IsEmptyStack(S))
    {
        return INT_MIN;
    }
    return 0;
}

int IsEmptyStack(struct Stack *S)
{
    return (S->top == -1); //如果条件成立，则返回1，否则返回0
}

int IsFullStack(struct Stack *S)
{
    //如果条件成立，则返回1，否则返回0
    return (S->top == S->capacity - 1);
}

void Push(struct Stack *S, int data)
{
    /*S->top == capacity -1 用来判断栈是否已满 */
    if (IsFullStack(S))
        printf("Stack Overflow");
    else /*top增1，然后将元素存入top所指示的位置上*/
        S->array[++S->top] = data;
}

int Pop(struct Stack *S)
{
    /*S->top == -1 用来判断栈是否为空*/
    if (IsEmptyStack(S))
    {
        printf("Stack is Empty");
        return 0;
    }
    else /*返回top所指位置上的元素（即栈顶元素），然后top减1*/
        return S->array[S->top--];
}
#define MAXSIZE 50;

struct Stack *CreateStack()
{
    struct Stack *S = (struct Stack *)malloc(sizeof(struct Stack));
    if (!S)
        return NULL;
    S->capacity = MAXSIZE;
    S->top = -1;
    S->array = (int *)malloc(S->capacity * sizeof(int));
    if (!S->array)
        return NULL;
    return S;
}

void DeleteStack(struct Stack *S)
{
    if (S)
    {
        if (S->array)
            free(S->array);
        free(S);
    }
}
#pragma endregion

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
    struct Stack *S = CreateStack();        //创建一个栈
    struct BinaryTreeNode *previous = NULL; //设置一个previous结点
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

int FindMax(struct BinaryTreeNode *root)
{
    int root_val, left, right, max = INT_MIN;
    if (root != NULL)
    {
        root_val = root->data;
        left = FindMax(root->left);
        right = FindMax(root->right);
        //查找树的最大元素
        if (left > right)
            max = left;
        else
            max = right;
        if (root_val > max)
            max = root_val;
    }
}

//Q2 非递归找出二叉树最大元素
//利用队列和层级遍历 时间复杂度和空间复杂度O(n)

int FindeMaxUsingLevelOrder(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    int max = INT_MIN;
    struct Queue *Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (max < temp->data)
            max = temp->data;
        if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return max;
}

//Q3 算法：在二叉树中搜索指定元素
//向下递归进行比较
int FindInBinaryTreeUsingRecursion(struct BinaryTreeNode *root, int data)
{
    int temp;
    //基本情况--空树 搜索失败返回false
    if (root == NULL)
        return 0;
    else
    {
        if (data == root->data)
            return 1;
        else
        {
            //否则在相应的子树进行递归
            temp = FindInBinaryTreeUsingRecursion(root->left, data);
            if (temp != 0)
                return temp;
            else
                return (FindInBinaryTreeUsingRecursion(root->right, data));
        }
    }
    return 0;
}

//Q4 在二叉树搜索指定元素（非递归算法） 时间复杂度O(n) ,空间复杂度O(n)

int SearchUsingLevelOrder(struct BinaryTreeNode *root, int data)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    if (!root)
        return -1;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (data == root->data)
            return 1;
        if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return 0;
}

//Q5 给出一个算法，将一个元素插入二叉树中。
//给定二叉树，我们可以把元素插入任何想要插入的位置，需要用到层次遍历，插入遍历过程中遇到的第一个无左孩子或无右孩子的结点的左指针域或右指针域中
void InsertInBinaryTree(struct BinaryTreeNode *root, int data)
{
    struct Queue *Q;
    struct BinaryTreeNode *temp;
    struct BinaryTreeNode *newNode;
    newNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode)); //内存分配
    newNode->left = newNode->right = NULL;                                    //设置左右指针
    if (!newNode)
    {
        printf("Memory Error");
        return;
    }
    if (!root)
    {
        root = newNode;
        return;
    }
    Q = CreateQueue();
    EnQueue(Q, root); //层级遍历
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (temp->left) //找到左孩子则压入队列
        {
            EnQueue(Q, temp->left);
        }
        else
        {
            temp->left = newNode; //找不到左孩子就插入左孩子位置
            DeleteQueue(Q);
            return;
        }
    }
    DeleteQueue(Q);
}

//Q6 给出一个算法，求二叉树的大小 时间复杂度O(n) ,空间复杂度O(n)

int SizeOfBinaryTree(struct BinaryTreeNode *root)
{
    if (root == NULL)
        return 0;
    else
        return (SizeOfBinaryTree(root->left)) + 1 + SizeOfBinaryTree(root->right);
}

//Q7 Q6的非递归解决方案
//依然是层次遍历

int SizeOfBTUsingLevelOrder(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    int count = 0;
    if (!root)
        return -1;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        count++ if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return count;
}

//Q8 给出一个算法，按层次逆序方式打印二叉树层次遍历序列 O(n),O(n)
//这里用到了层次遍历和使用堆来逆置队列的算法 1234567 最后打印4567231
void LevelOrderTraversalInReverse(struct BinaryTreeNode *root)
{
    struct Queue *Q;                 //定义队列
    struct Stack *s = CreateStack(); //创建一个堆
    struct BinaryTreeNode *temp;     //一个临时变量
    if (!root)                       //如果没有根结点则返回
        return;
    Q = CreateQueue(); //创建队列
    EnQueue(Q, root);  //把root压入队列
    while (!IsEmptyQueue(Q))
    {                                //如果队列不为空 开始循环处理队列
        temp = DeQueue(Q);           //出列赋值给temp
        if (temp->right)             //如果有右子结点
            EnQueue(Q, temp->right); //压入队列（右结点会在左结点的下面）
        if (temp->left)              //如果有左子结点
            EnQueue(Q, temp->left);  //压入队列
        Push(s, temp);               //把temp压入栈(这样root就会在最下面)
    }
    while (!IsEmptyStack(s)) //循环处理栈中的信息，每个打印出来
        printf("%d", Pop(s)->data);
}

//Q9给出一个算法删除一棵二叉树
//遍历所有结点并且挨个删除LDR,DLR,LRD和层次遍历选哪个？
//必须要优先删除子结点，所以用LRD算法，使用层次遍历还需要其他开销，不做最优选了
void DeleteBinaryTree(struct BinaryTreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    /*首先删除两棵子树*/
    DeleteBinaryTree(root->left);
    DeleteBinaryTree(root->right);
    //删除子树后删除当前结点
    free(root);
}

//Q10 给出一个算法，求二叉树的高度（或深度）递归查找LRD
//递归计算左子树的高度和右子树的高度，高度等于左子树高度和右子树的大者+1，使用先序遍历或图的优先搜索DFS算法类似
int HeightOfBinaryTree(struct BinaryTreeNode *root)
{
    int leftHeight, rightHeight;
    if (root == NULL)
        return 0;
    else
    {
        /*计算每棵子树的深度*/
        leftHeight = HeightOfBinaryTree(root->left);
        rightHeight = HeightOfBinaryTree(root->right);
        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

//Q11 不递归来解Q10
//用层次遍历发， 类似图的广度优先搜索BFS算法，在队列用空指针NULL表示某层结点存储完毕
//时间和空间复杂度 O(n)
int FindHeightofBinaryTree(struct BinaryTreeNode *root)
{
    int level = 1;
    struct Queue *Q;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    //第一层结束
    EnQueue(Q, NULL);
    while (!IsEmptyQueue(Q))
    {
        root = DeQueue(Q);
        //当前层结束
        if (root == NULL)
        {
            //压入下一层的结束标记
            if (!IsEmptyQueue(Q))
                EnQueue(Q, NULL);
            level++;
        }
        else
        {
            if (root->left)
                EnQueue(Q, root->left);
            if (root->right)
                EnQueue(Q, root->right);
        }
    }
    return level;
}

//Q12 给出一个算法 找出二叉树最深结点
//还是用层级遍历，返回最后一个结点就是最深结点
//时间和空间复杂度 O(n)
struct BinaryTreeNode *DeepestNodeinBinaryTree(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    if (!root)
        return NULL;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return temp;
}

//Q13 给一个算法从二叉树删除指定结点
//从根节点开始找到想要删除的结点
//找到最深结点
//交换最深结点和目标删除的结点
//删除最深结点（总之还是用层级遍历）

//Q14 非递归算法计算二叉树的叶子结点个数
//左子指针域和右指针域都为NULL的结点叫叶子结点
//还是用层级遍历，找不到左右子指针就计数
//时间和空间复杂度 O(n)
int NumberOfLeavesInBTusingLeverOrder(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    int count = 0;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (!temp->left && !temp->right)
            count++;
        else
        {
            if (temp->left)
                EnQueue(Q, temp->left);
            if (temp->right)
                EnQueue(Q, temp->right);
        }
        DeleteQueue(Q);
        return count;
    }
}

//Q15 非递归算法计算二叉树的满结点个数。
//同时有左右子结点的结点叫满结点
//继续层级遍历 ，找倒左右子指针就技术
//时间和空间复杂度 O(n)
int NumberOfFullNodeInBTusingLeverOrder(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    int count = 0;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (temp->left && temp->right)
            count++;
        else
        {
            if (temp->left)
                EnQueue(Q, temp->left);
            if (temp->right)
                EnQueue(Q, temp->right);
        }
        DeleteQueue(Q);
        return count;
    }
}

//Q16 非递归算法统计二叉树半结点（只有一个孩子的结点）
//具有左孩子或右孩子，不具有左右孩子的结点
//时间和空间复杂度 O(n)
int NumberOfHalfNodeInBTusingLeverOrder(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    int count = 0;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (temp->left ^ temp->right) //(!temp->left && temp->right || temp->left &&!temp->right)
            count++;
        else
        {
            if (temp->left)
                EnQueue(Q, temp->left);
            if (temp->right)
                EnQueue(Q, temp->right);
        }
        DeleteQueue(Q);
        return count;
    }
}

//Q17 判断两颗二叉树是否结构相同 相同则返回true
//均为空则返回true
//不为空则比较根结点和递归判断左右子树结构 时间空间复杂度O(n)
int AreStructurullySameTrees(struct BinaryTreeNode *root1, struct BinaryTreeNode *root2)
{
    //均为空 返回1
    if (root1 == NULL && root2 == NULL)
        return 1;
    //一棵为空返回0
    if (root1 == NULL || root2 == NULL)
        return 0;
    //均不为空，比较
    return (root1->data == root2->data && AreStructurullySameTrees(root1->left, root2->left) && AreStructurullySameTrees(root1->right, root2->right));
}

//Q18 给一个算法求二叉树的直径(二叉树的宽度)两个叶子结点之间的最长路径上的结点个数 时间复杂度O(n) 空间复杂度O(n)
//左右子树高度和的最大值
int DiameterOfTree(struct BinaryTreeNode *root, int *ptr)
{
    int left, right;
    if (!root)
        return 0;
    left = DiameterOfTree(root->left, ptr); //ptr用来记录当前找到的结点左右子树高度和的最大值
    right = DiameterOfTree(root->right, ptr);
    if (left + right > *ptr)
        *ptr = left + right;
    return max(left, right) + 1; //返回值是以第一个参数为根的二叉树的高度
}

//另一种实现方法
static int diameter(struct BinaryTreeNode *root)
{
    if (root == NULL)
        return 0;
    int lHeight = height(root->left);
    int rHeight = height(root->right);
    int lDiameter = diameter(root->left);
    int rDiameter = diameter(root->right);
    return max(lHeight + rHeight + 1, max(lDiameter, rDiameter));
}

/*
这个函数计算树的高度，高度是从根结点到最远的叶子结点的路径距离
*/
static int height(struct BinaryTreeNode *root)
{
    if (root == NULL)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

//还有一个解决方法，主要的思路是如果结点的孩子是“根”，则结点存储它的左子结点和右子结点最大的直径，这样没必要递归调用height方法，
//缺点是我们需要添加节点结构中的两个额外变量。

int findMaxLen(struct BinaryTreeNode *root)
{
    int nMaxLen = 0;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        root->nMaxLeft = 0;
    if (root->right == NULL)
        root->nMaxRight = 0;
    if (root->left != NULL)
        findMaxLen(root->left);
    if (root->right != NULL)
        findMaxLen(root->right);
    if (root->left != NULL)
    {
        int nTempMaxLen = 0;
        nTempMaxLen = (root->left->nMaxLeft > root->left->nMaxRight) ? root->left->nMaxLeft : root->left->nMaxRight;
        root->nMaxLeft = nTempMaxLen + 1;
    }
    if (root->left != NULL)
    {
        int nTempMaxLen = 0;
        nTempMaxLen = (root->right->nMaxLeft > root->right->nMaxRight) ? root->right->nMaxLeft : root->right->nMaxRight;
        // root->nMaxRight = nTempMaxLen + 1;
    }

    if (root->nMaxLeft + root->nMaxRight > nMaxLen)
        nMaxLen = root->nMaxLeft + root->nMaxRight;
    return nMaxLen;
}

//Q19找出二叉树中结点值之和最大的层
//跟找二叉树层数的逻辑接近，需要保持对每层结点值之和的跟踪 时间复杂度O(n)空间复杂度O(n)
int FindLevelwithMaxSum(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    int level = 0, maxLevel = 0;
    struct Queue *Q;
    int currentSum = 0, maxSum = 0;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    EnQueue(Q, NULL);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        //如果当前层遍历完，则比较和
        if (temp == NULL)
        {
            if (currentSum > maxSum)
            {
                maxSum = currentSum;
                maxLevel = level;
            }
            currentSum = 0;
            //将下一层结束的标记插入队尾
            if (!IsEmptyQueue(Q))
                EnQueue(Q, NULL);
            level++;
        }
        else
        {
            currentSum += temp->data;
            if (temp->left)
                EnQueue(Q, temp->left);
            if (root->right)
                EnQueue(Q, temp->right);
        }
    }

    return maxLevel;
}

//Q20 输出二叉树所有根到叶子结点的路径信息 时间复杂度O(n) ，空间复杂度O(n) 递归栈的空间开销
void PrintPathRecur(struct BinaryTreeNode *root, int path[], int pathLen){
    if(root==NULL)
        return;
        //将根结点添加到路径数组中
        path[pathLen] = root->data;
        pathLen++;
        //如果是叶子结点，则打印从根结点到该叶子结点的路径信息
        if(root->left == NULL && root->right == NULL)
            PrintArray(path, pathLen);
        else{
            PrintPathRecur(root->left,path, pathLen);
        }
}

void PrintArray(int ints[], int len) {
    for(int i=0;i<len; i++)
        printf("%d", ints[i]);
}

//Q21