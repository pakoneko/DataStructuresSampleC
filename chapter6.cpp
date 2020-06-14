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
    struct Stack(int size)
    {
    }
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

int FindMin(struct BinaryTreeNode *root)
{
    int root_val, left, right, min = INT_MIN;
    if (root != NULL)
    {
        root_val = root->data;
        left = FindMin(root->left);
        right = FindMin(root->right);
        //查找树的最大元素
        if (left < right)
            min = left;
        else
            min = right;
        if (root_val < min)
            min = root_val;
    }
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
void PrintPathRecur(struct BinaryTreeNode *root, int path[], int pathLen)
{
    if (root == NULL)
        return;
    //将根结点添加到路径数组中
    path[pathLen] = root->data;
    pathLen++;
    //如果是叶子结点，则打印从根结点到该叶子结点的路径信息
    if (root->left == NULL && root->right == NULL)
        PrintArray(path, pathLen);
    else
    {
        PrintPathRecur(root->left, path, pathLen);
    }
}

void PrintArray(int ints[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d", ints[i]);
}

//Q21给出一个算法 判断二叉树中是否存在一条路径，路径上的结点值之和等于给定的路值sum。
//给定一个值sum，判断二叉树中是否存在一条从根结点到任何一个结点的路径，路径上的结点值之和等于sum
//解法：递归判断当前节点的左右孩子之前从sum减去当前结点的值，当达到二叉树的边界时判断sum是否为0，如果为0则找到了一条满足条件的路径
//时间复杂度O(n),空间复杂度O(n)
int HasPathSum(struct BinaryTreeNode *root, int sum)
{
    //如果我们访问完树且sum ==0, 那么我们返回true
    if (root == NULL)
        return (sum == 0);
    else
    {
        //否则判断两棵子树
        int remainingSum = sum - root->data;
        if ((root->left && root->right) || (!root->left && !root->right))
        {
            return (HasPathSum(root->left, remainingSum) || HasPathSum(root->right, remainingSum));
        }
        else if (root->left)
        {
            return HasPathSum(root->left, remainingSum);
        }
        else
        {
            return HasPathSum(root->right, remainingSum);
        }
    }
}

//Q22 给出一个算法，计算二叉树中所有结点的值之和
//递归算法很容易 时间复杂度O(n) 空间复杂度O(n)
int Add(struct BinaryTreeNode *root)
{
    if (root == NULL)
        return 0;
    else
        return (root->data + Add(root->left) + Add(root->right));
}

//Q23 非递归方式求解Q22
//使用层次遍历算法 时间复杂度O(n) 空间复杂度O(n)
int SumOfBTusingLevelOrder(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    int sum = 0;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        sum += temp->data;
        if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return sum;
}

//Q24 求二叉树的镜像 每个节点的左右孩子在镜像中都发生了交换
//时间复杂度O(n) 空间复杂度 O(n)
struct BinaryTreeNode *MirroerOfBinaryTree(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    if (root)
    {
        MirroerOfBinaryTree(root->left);
        MirroerOfBinaryTree(root->right);
        /*交换当前结点的指针*/
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    return root;
}

//Q25 判断两颗二叉树是否互为镜像

int AreMirrors(struct BinaryTreeNode *root1, struct BinaryTreeNode *root2)
{
    if (root1 == NULL && root2 == NULL)
        return 1;
    if (root1 == NULL || root2 == NULL)
        return 0;
    if (root1->data != root2->data)
        return 0;
    else
        return AreMirrors(root1->left, root2->right) && AreMirrors(root1->right, root2->left);
}

//Q26 求二叉树给定2个结点的最近共同祖先(Least Common Ancestor, LCA)
//时间复杂度O(n) 空间复杂度 O(n)
struct BinaryTreeNode *LCA(struct BinaryTreeNode *root, struct BinaryTreeNode *α, struct BinaryTreeNode *β)
{
    struct BinaryTreeNode *left, *right;
    if (root == NULL)
        return root;
    if (root == α || root == β)
        return root;
    left = LCA(root->left, α, β);
    if (left && right)
        return root;
    else
        return (left ? left : right);
}

//Q27 根据给定中序遍历序列和先序遍历序列构造二叉树
//LDR DBEAFC
//DLR ABDECF
/*
1.先序遍历选择一个元素，指示先序遍历序列下标变量加1指向下次递归调用时选择元素位置
2.上一步选中的元素创建一个新的结点newNode
3.中序遍历序列找到第一步被选择元素，用变量inOrderIndex表示该元素在中序遍历序列中位置
4.对位于inOrderIndex指示位置前面的元素调用BuildBinaryTree算法，创建newNode的左子树
5.对位于inOrderIndex指示位置后面的元素调用BuildBinaryTree算法，创建newNode的右子树
6.返回newNode 时间复杂度O(n) 空间复杂度 O(n)
*/

struct BinaryTreeNode *BuildBinaryTree(int inOrder[], int preOrder[], int inOrderStart, int inOrderEnd)
{
    static int preOrderIndex = 0;
    struct BinaryTreeNode *newNode;
    if (inOrderStart > inOrderEnd)
        return NULL;
    newNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    if (!newNode)
    {
        printf("Memory Error");
        return NULL;
    }
    //利用preOrderIndex从先序遍历序列中选出当前结点
    newNode->data = preOrder[preOrderIndex];
    preOrderIndex++;
    if (inOrderStart == inOrderEnd)
        return newNode;
    //查找该结点在中序遍历序列的位序
    int inOrderIndex = Search(inOrder, inOrderStart, inOrderEnd, newNode->data); //这里需要自己定义一个搜索方法
    //利用在中序遍历序列中的位序填充左右子树
    newNode->left = BuildBinaryTree(inOrder, preOrder, inOrderStart, inOrderIndex - 1);
    newNode->right = BuildBinaryTree(inOrder, preOrder, inOrderIndex + 1, inOrderEnd);
    return newNode;
}

//Q28根据两个给定二叉树的遍历序列唯一构造一颗二叉树
//必须含有中序遍历序列可以唯一构造一个二叉树

//Q29 打印二叉树指定节点所有祖先
int PrintAllAncestors(struct BinaryTreeNode *root, struct BinaryTreeNode *node)
{
    if (root == NULL)
        return 0;
    if (root->left == node || root->right == node || PrintAllAncestors(root->left, node) || PrintAllAncestors(root->right, node))
    {
        printf("%d", root->data);
        return 1;
    }
    return 0;
}

//Q30 锯齿形二叉树遍历 1324567
//使用两个栈，假设两个栈currentLevel nextLevel
//一个变量记录当前层的访问方向
//时间复杂度O(n) 空间 两个栈O(n)+O(n) = O(n)
void ZigZagTraversal(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    int leftToRight = 1;
    if (!root)
        return;
    struct Stack *currentLevel = CreateStack(), *nextLevel = CreateStack();
    Push(currentLevel, root);
    while (!IsEmptyStack(currentLevel))
    {
        temp = Pop(currentLevel);
        if (temp)
        {
            printf("%d", temp->data);
            if (leftToRight)
            {
                if (temp->left)
                    Push(nextLevel, temp->left);
                if (temp->right)
                    Push(nextLevel, temp->right);
            }
            else
            {
                if (temp->right)
                    Push(nextLevel, temp->right);
                if (temp->left)
                    Push(nextLevel, temp->left);
            }
        }
        if (IsEmptyStack(currentLevel))
        {
            leftToRight = 1 - leftToRight;
            swap(currentLevel, nextLevel);
        }
    }
}

//Q31找出二叉树的垂直和
//垂直和是在竖线列区域的结点值得和
/*
                 1
              2     3
            4    56    7

            第一列4
            第二列2
            第三列156
            第四列3
            第五列7
*/

void VerticalSumInBinaryTree(struct BinaryTreeNode *root, int column)
{
    if (root == NULL)
        return;
    VerticalSumInBinaryTree(root->left, column - 1);
    //散列表的实现看chapter14
    Hash[column] += root->data;
    VerticalSumInBinaryTree(root->right, column + 1);
}
//VerticalSumInBinaryTree(root, 0);
//print(Hash);

//Q32 具有n个结点的不同二叉树共有多少棵？
//2^n -n (2的n次方-n棵)

//Q33给定特殊性质的二叉树，这个二叉树的叶子结点用L表示，内部结点用I表示，假设每个节点要么没孩子要么2个孩子，根据二叉树的先序遍历序列(DLR)构造二叉树
//如ILILL

struct BinaryTreeNode *BuildTreeFromPreOrder(char *A, int *i)
{
    struct BinaryTreeNode *newNode;
    newNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    newNode->data = A[*i];
    newNode->left = newNode->right = NULL;
    if (A == NULL)
    { //边界条件
        free(newNode);
        return NULL;
    }
    if (A[*i] == 'L') //达到叶子结点返回
        return newNode;
    *i = *i + 1; //填充左子树
    newNode->left = BuildTreeFromPreOrder(A, i);
    *i = *i + 1;
    newNode->right = BuildTreeFromPreOrder(A, i);
    return newNode;
}

//Q34给定一棵二叉树，它的每个结点包括三个指针域，left right nextSibling，设计算法给二叉树中每个结点的nextSibling指针域赋值（每个结点的nextSibling域初始化为NULL）

//层级遍历又来啦！

struct BinaryTreeNode
{
    char data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    struct BinaryTreeNode *nextSibling;
};

int FillNextSiblings(struct BinaryTreeNode *root)
{
    struct BinaryTreeNode *temp;
    struct Queue *Q;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    EnQueue(Q, NULL);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        //当前层处理结束
        if (temp == NULL)
        {
            //插入下一层的结束状态
            if (!IsEmptyQueue(Q))
                EnQueue(Q, NULL);
        }
        else
        {
            temp->nextSibling = QueueFront(Q);
            if (temp->left)
                EnQueue(Q, temp->left);
            if (temp->right)
                EnQueue(Q, temp->right);
        }
    }
}

//Q35 其他方法求解Q34
//利用已赋值的nextSibling指针域，只需多一个步骤就可以解决，在对左子树和右子树递归求解之前
//将当前结点的右孩子的nextSibling链接到当前结点的nextSibling指针所指结点的左孩子，保证此时当前结点的nextSibling指针域已赋值
void FillNextSibling(struct BinaryTreeNode *root)
{
    if (!root)
        return;
    if (root->left)
        root->left->nextSibling = root->right;
    if (root->right)
        root->right->nextSibling = (root->nextSibling) ? root->nextSibling->left : NULL;
    FillNextSibling(root->left);
    FillNextSibling(root->right);
}

//一般树
struct TreeNode
{
    int data;
    struct TreeNode *firstChild;
    struct TreeNode *nextSibling;
};

//Q36 求树中所有结点之和

int FindSum(struct TreeNode *root)
{
    if (!root)
        return 0;
    return root->data + FindSum(root->firstChild) + FindSum(root->nextSibling);
}

//Q37 求一个100结点四叉树最大高度
//99个，每个结点只有一个孩子

//Q38 最小高度
//log4(3n+1)-1

//Q39双亲数组P，P[i]表示树中第i个结点的双亲，求树的高度或者深度
int FindDepthInGenericTree(int P[], int n)
{
    int maxDepth = -1, currentDepth = -1, j;
    for (int i = 0; i < n; i++)
    {
        currentDepth = 0;
        j = i;
        while (P[j] != -1)
        {
            currentDepth++;
            j = P[j];
        }
        if (currentDepth > maxDepth)
            maxDepth = currentDepth;
    }
    return maxDepth;
}

//Q40 计算普通树指定结点的兄弟个数
//时间复杂度 O(n) 空间复杂度 O(1)
int SiblingsCounts(struct TreeNode *current)
{
    int count = 0;
    while (current)
    {
        count++;
        current = current->nextSibling;
    }
    return count;
}

//Q41 计算普通树指定结点孩子个数
//时间复杂度 O(n) 空间复杂度 O(1)
int ChildCount(struct TreeNode *current)
{
    int count = 0;
    current = current->firstChild;
    while (current)
    {
        count++;
        current = current->nextSibling;
    }
    return count;
}
//Q42 判断给定的两棵树是否同构
int IsIsomorphic(struct TreeNode *root1, struct TreeNode *root2)
{
    if (!root1 && !root2)
        return 1;
    if ((!root1 && root2) || (root1 && !root2))
        return 0;
    return (IsIsomorphic(root1->firstChild, root2->firstChild) && IsIsomorphic(root1->nextSibling, root2->nextSibling));
}

//Q43 判断给定的两棵树是否准同构（左右翻转后结构可以相同
int IsIsomorphic(struct TreeNode *root1, struct TreeNode *root2)
{
    if (!root1 && !root2)
        return 1;
    if ((!root1 && root2) || (root1 && !root2))
        return 0;
    return (IsIsomorphic(root1->firstChild, root2->firstChild) && IsIsomorphic(root1->nextSibling, root2->nextSibling) || IsIsomorphic(root1->firstChild, root2->nextSibling) && IsIsomorphic(root1->nextSibling, root2->firstChild));
}

//Q44 满k叉树是每个结点有0个或者k个孩子的树，给出一个满k叉树的先序遍历序列构造满k叉树
//满k叉树中，第i个结点的孩子编号是从k*i+1到k*i+k
//这段代码错误太多了，建议参考build_full_k_arytree_preorder.cpp
struct K_aryTreeNode
{
    char data;
    struct K_aryTeeNode *child[];
};
int Ind = 0;

struct K_aryTreeNode *BuildK_aryTree(char A[], int n, int k)
{
    if (n <= 0)
        return NULL;
    struct K_aryTreeNode *newNode = (struct K_aryTreeNode *)malloc(sizeof(struct K_aryTreeNode));
    if (!newNode)
    {
        printf("Memory Error");
        return;
    }
    newNode->child = (struct K_aryTreeNode *)malloc(k * sizeof(struct K_aryTreeNode));
    if (!newNode->child)
    {
        printf("Memory Error");
        return;
    }
    newNode->data = A[Ind];
    for (int i = 0; i < k; i++)
    {
        if (k * Ind + i < n)
        {
            Ind++;
            newNode->child[i] = BuildK_aryTree(A, n, k, Ind);
        }
        else
            newNode->child[i] = NULL;
    }
    return newNode;
}

//线索二叉树
struct ThreadedBinaryTreeNode
{
    struct ThreadedBinaryTreeNode *left;
    int LTag;
    int data;
    int RTag;
    struct ThreadedBinaryTreeNode *right;
};

//中序线索二叉树指定结点查找中序后继结点
//如果P没有右子树则返回P的右子结点指针，如果有右子树则返回指向右子树最左下结点指针
struct ThreadedBinaryTreeNode *IndorderSuccessor(struct ThreadedBinaryTreeNode *P)
{
    struct ThreadedBinaryTreeNode *Position;
    if (P->RTag == 0)
        return P->right;
    else
    {
        Position = P->right;
        while (Position->LTag == 1)
            Position = Position->left;
        return Position;
    }
}

//中序线索二叉树的中序遍历
void InorderTraversal(struct ThreadedBinaryTreeNode *root)
{
    struct ThreadedBinaryTreeNode *P = IndorderSuccessor(root);
    while (P != root)
    {
        P = IndorderSuccessor(P);
        printf("%d", P->data);
    }
}
//替代写法
void InorderTraversal(struct ThreadedBinaryTreeNode *root)
{
    struct ThreadedBinaryTreeNode *P = IndorderSuccessor(root);
    while (1)
    {
        P = IndorderSuccessor(P);
        if (P == root)
            return;
        printf("%d", P->data);
    }
}

//中序线索二叉树中查找先序后继结点
//如果P有左子树，返回P的左孩子指针，如果没有左子树，返回右子树包含P最近结点的右孩子
struct ThreadedBinaryTreeNode *PreorderSuccessor(struct ThreadedBinaryTreeNode *P)
{
    struct ThreadedBinaryTreeNode *Position;
    if (P->LTag == 1)
        return P->left;
    else
    {
        Position = P;
        while (Position->RTag == 0)
            Position = Position->right;
        return Position->right;
    }
}

//中序线索二叉树的先序遍历
void PreorderTraversal(struct ThreadedBinaryTreeNode *root)
{
    struct ThreadedBinaryTreeNode *P = IndorderSuccessor(root);
    while (P != root)
    {
        P = PreorderSuccessor(P);
        printf("%d", P->data);
    }
}

//替代写法
void PreorderTraversal(struct ThreadedBinaryTreeNode *root)
{
    struct ThreadedBinaryTreeNode *P = IndorderSuccessor(root);
    while (1)
    {
        P = PreorderSuccessor(P);
        if (P == root)
            return;
        printf("%d", P->data);
    }
}

//不使用栈查找后序后继结点是很困难的

//中序线索二叉树插入结点
//P是二叉树当前结点，Q是要插入的那个结点 让它成为P的右孩子
//时间复杂度O(n) 空间复杂度O(1)
void InsertRightInInorderTBT(struct ThreadedBinaryTreeNode *P, struct ThreadedBinaryTreeNode *Q)
{
    struct ThreadedBinaryTreeNode *Temp;
    Q->right = P->right;
    Q->RTag = P->RTag;
    Q->left = P;
    Q->LTag = 0;
    P->right = Q;
    P->RTag = 1;
    if (Q->RTag == 1)
    { //第二种情况 结点P有右孩子，需要访问右孩子的左子树找到最左下结点，更新该结点的左右指针域
        Temp = Q->right;
        while (Temp->LTag)
            Temp = Temp->left;
        Temp->left = Q;
    }
}

//Q45 给定非线索化二叉树，实现查找先序后继结点操作
//使用辅助栈S，第一次调用参数node的值是树的根指针，之后调用参数值为NULL
//查找上次调用返回结点的后继结点，一次调用到下次函数的过程中，栈S的内容和指向刚刚呗访问结点得指针P是必须被保存的，因此将它们定义为静态变量
struct BinaryTreeNode *PreorderSuccessor(struct BinaryTreeNode *node)
{
    static struct BinaryTreeNode *P;
    static Stack *S = CreateStack();
    if (node != NULL)
        P = node;
    if (P->left != NULL)
    {
        Push(S, P);
        P = P->left;
    }
    else
    {
        while (P->right == NULL)
            P = Pop(S);
        P = P->right;
    }
    return P;
}

//Q46 给定非线索化二叉树，实现查找中序后继结点操作
struct BinaryTreeNode *PreorderSuccessor(struct BinaryTreeNode *node)
{
    static struct BinaryTreeNode *P;
    static Stack *S = CreateStack();
    if (node != NULL)
        P = node;
    if (P->right == NULL)
    {
        P = Pop(S);
    }
    else
    {
        while (P->left != NULL)
            Push(S, P);
        P = P->left;
    }
    return P;
}

//后缀表达式构建表达树

struct BinaryTreeNode *BuildExprTree(char postfixExpr[], int size)
{
    struct Stack *S = Stack(size);
    for (int i = 0; i < size; i++)
    {
        if (postfixExpr[i] is an operand)
        { //这里写的很莫名最好另外找个算法看看
            struct BinaryTreeNode *newNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
            if (!newNode)
            {
                printf("Memory Error");
                return NULL;
            }
            newNode->data = postfixExpr[i];
            newNode->left = newNode->right = NULL;
            Push(S, newNode);
        }
        else
        {
            struct BinaryTreeNode *T2 = Pop(S), *T1 = Pop(S);
            struct BinaryTreeNode *newNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
            if (!newNode)
            {
                printf("Memory Error");
                return NULL;
            }
            newNode->data = postfixExpr[i];
            newNode->left = T1;
            newNode->right = T2;
            Push(S, newNode);
        }
    }
}

//二叉搜索树
struct BinarySearchTreeNode : BinaryTreeNode
{
    /* data */
    int data;
    struct BinarySearchTreeNode *left;
    struct BinarySearchTreeNode *right;
};

//递归查找元素
struct BinarySearchTreeNode *Find(struct BinarySearchTreeNode *root, int data)
{
    if (root == NULL)
        return NULL;
    if (data < root->data)
        return Find(root->left, data);
    else if (data > root->data)
        return Find(root->right, data);
    return root;
}

//非递归查找元素
struct BinarySearchTreeNode *Find(struct BinarySearchTreeNode *root, int data)
{
    if (root == NULL)
        return NULL;
    while (root)
    {
        if (data == root->data)
            return root;
        else if (data > root->data)
            root = root->right;
        else
            root = root->left;
    }
    return NULL;
}

//查找最小元素 递归 时间和空间复杂度O(n)
struct BinarySearchTreeNode *FindMin(struct BinarySearchTreeNode *root)
{
    if (root == NULL)
        return NULL;
    else if (root->left == NULL)
        return root;
    return FindMin(root->left);
}
//非递归 时间O(n) 空间 O(1)
struct BinarySearchTreeNode *FindMin(struct BinarySearchTreeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

//查找最大元素 递归 时间和空间复杂度O(n)
struct BinarySearchTreeNode *FindMax(struct BinarySearchTreeNode *root)
{
    if (root == NULL)
        return NULL;
    else if (root->right == NULL)
        return root;
    return FindMax(root->right);
}
//非递归 时间O(n) 空间 O(1)
struct BinarySearchTreeNode *FindMax(struct BinarySearchTreeNode *root)
{
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

//插入元素data到二叉搜索树中
struct BinarySearchTreeNode *Insert(struct BinarySearchTreeNode *root, int data)
{
    if (root == NULL)
    {
        root = (struct BinarySearchTreeNode *)malloc(sizeof(struct BinarySearchTreeNode));
        if (root == NULL)
        {
            printf("Memory Error");
            return;
        }
        else
        {
            root->data = data;
            root->left = root->right = NULL;
        }
    }
    else
    {
        if (data < root->data)
            root->left = Insert(root->left, data);
        else if (data > root->data)
            root->right = Insert(root->right, data);
    }
}

//以上代码：子树插入一个元素，子树被返回给它的双亲结点，所以整个二叉树被更新。

//在二叉搜索树中删除元素
struct BinarySearchTreeNode *Delete(struct BinarySearchTreeNode *root, int data)
{
    struct BinarySearchTreeNode *temp;
    if (root == NULL)
        printf("Element not there in tree");
    else if (data < root->data)
        root->left = Delete(root->left, data);
    else
    {
        /* 查找元素 */
        if (root->left && root->right) //两个孩子
        {
            /*把要删除的结点替换为左子树中的最大值*/
            temp = FindMax(root->left);
            root->data = temp->data;
            root->left = Delete(root->left, root->data);
        }
        else
        {
            /*一个孩子*/
            temp = root;
            if (root->left == NULL)
                root = root->right;
            if (root->right == NULL)
                root = root->left;
            free(temp);
        }
    }
}

//Q47 给定指向二叉搜索树中2个结点的指针，找出这两个结点的最低共同祖先（Lowest Common Ancestor,LCA)
//先序遍历找到第一个结点的值在α和β之间
struct BinarySearchTreeNode *FindLCA(struct BinarySearchTreeNode *root, struct BinarySearchTreeNode *a, struct BinarySearchTreeNode *b)
{
    while (1)
    {
        if ((a->data < root->data && b->data > root->data) || (a->data > root->data && b->data < root->data))
            return root;
        if (a->data < root->data)
            root = root->left;
        else
            root = root->right;
    }
}

//Q48 求解BST中两个结点之间的最短路径
//找到这两个结点的LCA

//Q49 统计相同n个结点的所有可能的BST的个数
//动态规划 参考19章

//Q50 判断一颗给定二叉树是否BST
//简单算法 每个结点判断左孩子是否小于它且右孩子是否大于它 但是仅仅当前结点判断是不够的
int IsBST(struct BinaryTreeNode *root)
{
    if (root == NULL)
        return 1;
    //root左孩子大于root则返回false
    if (root->left != NULL && root->left->data > root->data)
        return 0;
    //root右孩子小于root则返回false
    if (root->right != NULL && root->right->data < root->data)
        ;
    return 0;
    //递归判断如果root的左子树或右子树不是BST则返回false
    if (!IsBST(root->left) || !IsBST(root->right))
        return 0;
    //上熟测试都通过则返回1；
    return 1;
}
//Q51 上面的简单判断是错误的，仅仅在当前结点判断是不够的 下面是正确的算法 O(n²) O(n)
//如果二叉树是一个BST则返回true
int IsBST(struct BinaryTreeNode *root)
{
    if (root == NULL)
        return 1;
    //如果左子树的最大值大于root的值则返回false；
    if (root->left != NULL && FindMax(root->left) > root->data)
        return 0;
    if (root->right != NULL && FindMin(root->right) < root->data)
        return 0;
    if (!IsBST(root->left) || !IsBST(root->right))
        return 0;
    return 1;
}

//Q52 改进51的复杂度

//写一个实用辅助程序IsBSTUtil(struct BinaryTreeNode * root, int min, int max)
//在遍历树的过程跟踪已访问结点的最小和最大值，其中每个结点只访问一次
//Initial call : IsBST（root, INT_MIN, INT_MAX)
//O(n) O(n) 用到一个栈
int IsBST(struct BinaryTreeNode *root, int min, int max)
{
    if (!root)
        return 1;
    return (root->data > min && root->data < max && IsBSTUtil(root->left, min, root->data) && IsBSTUtil(root->right, root->data, max));
}

//Q53 改进51的算法复杂度 使用LDR中序遍历， BST的中序遍历产生有序序列， 遍历BST时每个结点检查它的值大于前面访问结点值的条件 需要足够小的值初始化prev
int prev = INT_MIN;
int IsBST(struct BinaryTreeNode *root, int *prev)
{
    if (!root)
        return 1;
    if (!IsBST(root->left, prev))
        return 0;
    if (root->data < *prev)
        ;
    return 0;
    *prev = root->data;
    return IsBST(root->right, prev);
}

//Q54 将BST转换为DLL（双链表）的算法，需要空间复杂度O(1)
//将左右子树分别转为DLL，维持这些链表的表尾，调整指针
/*
算法/见解

我们递归地遍历叶子，然后创建从叶子到根向上的树。
步骤1.  计算链表的长度。
步骤 2. 递归的从前半结点创建左子树
步骤 3. 将中间结点作为根结点，将从前面调用(步骤2)返回的结点作为根的左子节点。
步骤 4. 移动头部到下一个节点.
步骤 5. 从后半节点递归地创建右子树.
步骤 6. 返回根.
*/

struct BinarySearchTreeNode *BST2DLL(struct BinarySearchTreeNode *root, struct BinarySearchTreeNode **Ltail)
{ //这段完全看不懂....
    struct BinarySearchTreeNode *left, *ltail, *right, *rtail;
    if (!root)
    {
        *Ltail = NULL;
        return NULL;
    }
    left = BST2DLL(root->right, &rtail);
    root->left = ltail;
    root->right = right;
    if (!right)
        *Ltail = root;
    else
    {
        right->left = root;
        *Ltail = rtail;
    }
    if (!left)
        return root;
    else
    {
        ltail->right = root;
        return left;
    }
}

//Q55 另一种求解上问题的方法
//基于分治法 有一个简洁的方法 时间复杂度是O(n)
struct BinarySearchTreeNode *Append(struct BinarySearchTreeNode *a, struct BinarySearchTreeNode *b)
{
    struct BinarySearchTreeNode *aLast, *bLast;
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    aLast = a->left;
    bLast = b->left;
    aLast->right = b;
    b->left = aLast; //把b链表连接到a后面
    bLast->right = a;
    a->left = bLast;
    return a;
}

struct BinarySearchTreeNode *TreeToList(struct BinarySearchTreeNode *root)
{
    struct BinarySearchTreeNode *aList, *bList;
    if (root == NULL)
        return NULL;
    aList = TreeToList(root->left);  //处理左子树
    bList = TreeToList(root->right); //处理右子树
    root->left = root;
    root->right = root;
    aList = Append(aList, root);
    aList = Append(aList, bList);
    return (aList);
}

//Q56 给出算法给定的有序双向链表转为平衡二叉搜索树
//找到中间结点然后调整指针， FindeMiddleNode参考chapter3
//时间复杂度: 2T(n/2) + O(n) [查找中点] = O(nlogn).
struct DLLNode *DLLtoBalancedBST(struct DLLNode *head)
{
    struct DLLNode *temp, *p, *q;
    if (!head || !head->next)
        return head;
    temp = FindeMiddleNode(head); //查找中点
    p = head;
    while (p->next != temp) //找到中点之前的那个点为p
        p = p->next;
    p->next = NULL;    //p作为子树尾部，next指针设为空
    q = temp->next;    //中点之后的那个点赋给q
    temp->next = NULL; //中点的next指针指向空
    temp->prev = DLLtoBalancedBST(head);
    temp->next = DLLtoBalancedBST(q);
    return temp;
}

//Q57 根据有序数组创建平衡BST 时间复杂度O(n) 因为使用递归堆栈
struct BinaryTreeNode *BuildBST(int A[], int left, int right)
{
    struct BinaryTreeNode *newNode;
    int mid;
    if (left > right)
        return NULL;
    newNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    if (!newNode)
    {
        printf("Memory Error");
        return;
    }
    if (left == right)
    {
        newNode->data = A[left];
        newNode->left = newNode->right = NULL;
    }
    else
    {
        mid = left + (right - left) / 2;
        newNode->data = A[mid];
        newNode->left = BuildBST(A, left, mid - 1);
        newNode->right = BuildBST(A, mid + 1, right);
    }
    return newNode;
}

//Q58 给定升序有序单链表转为平衡BST
//使用Q56的方法 每次递归调用需要遍历半个链表查找中间元素，时间复杂度O(nlogn)每层递归调用进行n/2个遍历步骤总共logn层 也就是平衡二叉树的高度

//Q59 降低Q58的时间复杂度
//解决按链表顺序插入结点，这样不用查找中间元素，在结点插入树过程遍历链表
//不再自顶向下创建树结点，而是自底向上
struct BinaryTreeNode *SortedListToBST(struct ListNode *&list, int start, int end)
{
    if (start > end)
        return NULL;
    //与(start+end)/2相同， 采用下面的形式是为了防止上溢
    int mid = start + (end - start) / 2;
    struct BinaryTreeNode *leftChild = SortedListToBST(list, start, mid - 1);
    struct BinaryTreeNode *parent;
    parent = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    if (!parent)
    {
        printf("Memory Error");
        return;
    }
    parent->data = list->data;
    parent->left = leftChild;
    list = list->next;
    parent->right = SortedListToBST(list, mid + 1, end);
    return parent;
}

struct BinaryTreeNode *SortedListToBST(struct ListNode *head, int n)
{
    return SortedListToBST(head, 0, n - 1);
}
//Q60 给出一个算法 查找BST中第k小的元素
/*
中序遍历BST 产生有序序列，中序遍历过程中跟踪被访问元素的个数 时间复杂度: O(n). 空间复杂度: O(1).
*/
struct BinarySearchTreeNode *kthSmallestInBST(struct BinarySearchTreeNode *root, int k, int count)
{
    if (!root)
        return NULL;
    struct BinarySearchTreeNode *left = kthSmallestInBST(root->left, k, count); //递归中序遍历先遍历左子树
    if (left)
        return left;
    if (++count == k)
        return root;
    return kthSmallestInBST(root->right, k, count);
}

//Q61 底和顶Floor and ceiling，
/*
如果给定的键值小于BST根节点的键值，则键(BST中小于或等于该键的最大键)的底必须在左边子树。
如果键值大于根结点的键值，则键的底可能在右子树，但只有当右子树中存在小于或等于该键的键值才成立;
反之(或者如果键值等于根节点的键值)，那么根节点的键值就是该键值的底。
寻找顶也是类似的，可以将上述过程左右子树互换。
输入有序数组{1,2,8,10,10,12,19}
x=0,它的底在数组不存在 ceil=1,x=1时 floor=1 ceil = 1
x = 5 ,floor = 2, ceil = 8, x=20, floor=19 顶不存在于这个数组

解决思路:中序遍历BST 生产有序序列，BST的中序遍历中跟踪刚刚访问的值，如果根节点大于给定值，则返回遍历过程中保存的访问过的值，如果根节点等于给定值返回根节点值
Time Complexity: O(n). Space Complexity: O(n), for stack space.
*/
struct BinaryTreeNode *FloorInBST(struct BinaryTreeNode *root, int data)
{
    struct BinaryTreeNode *prev = NULL;
    return FloorInBSTUtil(root, prev, data);
}
struct BinaryTreeNode *FloorInBSTUtil(struct BinaryTreeNode *root, struct BinaryTreeNode *prev, int data)
{
    if (!root)
        return NULL;
    if (!FloorInBSTUtil(root->left, prev, data)) //在左子树中递归寻找
        return 0;
    if (root->data == data) //值等于根节点
        return root;
    if (root->data > data) //值小于根节点 返回遍历过程中保存访问过的值
        return prev;
    prev = root;                                    //保存访问的根节点值
    return FloorInBSTUtil(root->right, prev, data); //在右子树中递归寻找
}

struct BinaryTreeNode *CeilingInBST(struct BinaryTreeNode *root, int data)
{
    struct BinaryTreeNode *prev = NULL;
    return CeilingInBSTUtil(root, prev, data);
}

struct BinaryTreeNode *CeilingInBSTUtil(struct BinaryTreeNode *root, struct BinaryTreeNode *prev, int data)
{
    if (!root)
        return NULL;
    if (!CeilingInBSTUtil(root->right, prev, data))
        return 0;
    if (root->data == data)
        return root;
    if (root->data < data)
        return prev;
    prev = root;
    return CeilingInBSTUtil(root->left, prev, data);
}

//Q62 找出BST的合集与交集，假设指向parent的指针可以访问（比如线索二叉树)，假设两个BST长度为m和n
//指向双亲的指针可以访问，则合并两个有序序列，调用查找中序后继结点算法，得到下一个最高元素, 这只是InorderSuccessor（中序后继）调用的问题 时间复杂度O(m+n) 空间复杂度O(1)

//Q63 对Q62 如果双亲指针不能访问怎么办
//把BST转为链表，然后合并链表
/*
1)在O(m+n)内将2个BST转为有序双向链表，产生2个有序序列
2)在O(m+n)内合并两个有序双向链表为一个有序双向链表，同时记录总的结点个数
3)在O(m+n)内将合并后的有序双向链表转换为高度平衡二叉树
*/
//Q64 另一种解决Q62的方法
//对其中一个BST中序遍历
//将访问的元素存到一个hash表
//第一个BST遍历好再遍历第二个BST 然后与hash表的元素进行比较
//时间O(m+n) 空间O(Max(m,n))

//Q65 给一棵BST ,两个元素K1,K2 设计算法，打印出BST所有介于K1,K2之间的元素
//递归中序遍历 时间复杂度O(n) 空间复杂度O(n) 递归堆栈
void RangePrinter(struct BinarySearchTreeNode *root, int K1, int K2)
{
    if (root == NULL)
        return;
    if (root->data >= K1)
        RangePrinter(root->left, K1, K2);
    if (root->data >= K1 && root->data <= K2)
        printf("%d", root->data);
    if (root->data <= K2)
        RangePrinter(root->right, K1, K2);
}

//Q66 另一种求解方法
//层次遍历
void RangeSearchLevelOrder(struct BinarySearchTreeNode *root, int K1, int K2)
{
    struct BinarySearchTreeNode *temp;
    struct Queue *Q = CreateQueue();
    if (!root)
        return NULL;
    Q = EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (temp->data >= K1 && temp->data <= K2) //符合区间的打印
            printf("%d", temp->data);
        if (temp->left && temp->data >= K1) //左子结点符合条件的压入队列
            EnQueue(Q, temp->left);
        if (temp->right && temp->data <= K2) //右子结点符合条件的压入队列
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return NULL;
}

//Q67 针对65其他方法
/*
基于通常二分搜索定位K1，调用查找中序后继结点算法 直到遇到K2 查看线索二叉树部分
*/
//Q68 给定二叉搜索树根指针， 修剪树使返回新树元素均介于参数A,B之间
//求解Q65的另一种方法

//Q69 给定两个BST，判断元素是否相同
// 10 5 20 15 30, 10 20 15 30 5  算法返回true
/*
            10
          5    20
              15  30  

如果数据集为 10 5 20 15 30 和 10 15 30 20 5 返回false
                                
                                 10
                               5    15
                                       30
                                    20
****BST数据可以是任何顺序
简单方法 第一棵树中序遍历，访问的元素存入hash表
第二棵树中序遍历 判断元素是否在hash表中如果在则将散列表的对应值设为-1或其他特殊值
如果发现不匹配返回false，如果hash表中所有值都是-1，则为true
时间复杂度O(max(m, n))空间复杂度O(max(m, n))
*/

//Q70 针对Q69 降低时间复杂度
//并行同时中序遍历2棵树，产生有序序列，可以判断两棵树是否产生相同序列 时间复杂度O(max(m, n))空间复杂度O(1)

//Q71 对键值 1...n 有多少结构不同的BST能存储这些键值？
//认为每个都可以为根，递归找左右子树大小
int CountTrees(int n)
{
    if (n <= 1)
        return 1;
    else
    {
        //一个值作为根，其余的值形成根的左右子树，对所有可能成为根的值进行迭代
        int sum = 0;
        int left, right, root;
        for (root = 1; root <= n; root++)
        {
            left = CountTrees(root - 1);
            right = CountTrees(numKeys - root);
            //继续该根结点的所有可能BST有left*right 个
            sum += left * right;
        }
    }
}

//AVL树声明
struct AVLTreeNode
{
    struct AVLTreeNode *left;
    int data;
    struct AVLTreeNode *right;
    int height;
};

int Height(struct AVLTreeNode *root)
{
    if (!root)
        return -1;
    else
        return root->height;
}

//左左旋转，时间复杂度O(1)，空间复杂度O(1) 情况1 插入X左孩子的左子树
struct AVLTreeNode *SingleRotateLeft(struct AVLTreeNode *X)
{
    struct AVLTreeNode *W = X->left;                        //W是X的左子结点
    X->left = W->right;                                     //W的右结点(B)给X做左子结点
    W->right = X;                                           //X给W做右子结点
    X->height = max(Height(X->left), Height(X->right)) + 1; //X高度为（X左子结点和X右子结点中最大的那个结点的高度+1）
    W->height = max(Height(W->left), X->height) + 1;        //W高度为W的左子结点跟X的高度中最大的高度+1
    return W;                                               //返回新的根W
}

//右右旋转，时间复杂度O(1)，空间复杂度O(1) 情况4 插入X右孩子的右子树
struct AVLTreeNode *SingleRotateRight(struct AVLTreeNode *W)
{
    struct AVLTreeNode *X = W->right;                       //X是W的右子结点
    W->right = X->left;                                     //X的的左子结点(B)给W做右子结点
    X->left = W;                                            //W给X做左子结点
    W->height = max(Height(W->right), Height(W->left)) + 1; //W高度为（W左子结点和W右子结点中最大的那个结点的高度+1）
    X->height = max(Height(X->right), W->height) + 1;       //X高度为X的右子结点跟W的高度中最大的高度+1
    return W;                                               //返回新的根W
}

//左右旋转，LR旋转 情况2 插入Z左孩子的右子树

struct AVLTreeNode *DoubleRotatewithLeft(struct AVLTreeNode *Z)
{
    Z->left = SingleRotateRight(Z->left);
    return SingleRotateLeft(Z);
}

//右左旋转，RL旋转 情况2 插入Z右孩子的左子树

struct AVLTreeNode *DoubleRotatewithRight(struct AVLTreeNode *X)
{
    X->right = SingleRotateLeft(X->right);
    return SingleRotateRight(X);
}

//AVL树的插入操作
//TC :O(n) ,SC: O(logn)
struct AVLTreeNode *Insert(struct AVLTreeNode *root, struct AVLTreeNode *parent, int data)
{
    if (!root)
    {
        root = (struct AVLTreeNode *)malloc(sizeof(struct AVLTreeNode *));
        if (!root)
        {
            printf("Memory Error");
            return NULL;
        }
        else
        {
            root->data = data;
            root->height = 0;
            root->left = root->right = NULL;
        }
    }
    else if (data < root->data)
    {
        root->left = Insert(root->left, root, data);
        if ((Height(root->left) - Height(root->right)) == 2)
        {
            if (data < root->left->data)
                root = SingleRotateLeft(root);
            else
                root = DoubleRotatewithLeft(root);
        }
    }
    else if (data > root->data)
    {
        root->right = Insert(root->right, root, data);
        if ((Height(root->right) - Height(root->left)) == 2)
        {
            if (data < root->right->data)
                root = SingleRotateRight(root);
            else
                root = DoubleRotatewithRight(root);
        }
    }
    //如果树中已经存在该数据则什么都不做
    root->height = max(Height(root->left), Height(root->right)) + 1;
    return root;
}

//Q72（第五版） 给定一棵具有n个结点的BST， 每个结点r可以有一个额外的值域 r->size
//基于r结点子树的键值个数(包含根结点r)，给定一个O(h)算法GreaterthanConstant(r, k)，h为BST的高度，找到严格大于k的键值的数量
int GreaterthanConstant(struct BinarySearchTreeNode *r, int k)
{
    int keysCount = 0;
    while (r != NULL)
    {
        if (k < r->data)
        {
            keysCount = keysCount + r->right->size + 1;
            r = r->left;
        }
        else if (k > r->data)
            r = r->right;
        else
        {
            keysCount = keysCount + r->right->size;
            break;
        }
    }
    return keysCount;
}
//Q72 给定高度h， 创建HB(0)算法
//HB(0)满二叉树，高度h满二叉树结点 2^(h+1) - 1 假设具有一个结点的树高度=0，结点可以从1~(2^(h+1) - 1)编号
//TC :O(n) ,SC: O(logn) logn表示栈最大大小 值等于树的高度
int count = 1;
struct BinarySearchTreeNode *BuildHB0(int h)
{
    struct BinarySearchTreeNode *temp;
    if (h == 0)
        return NULL;
    temp = (struct BinarySearchTreeNode *)malloc(sizeof(struct BinarySearchTreeNode));
    temp->left = BuildHB0(h - 1);
    temp->data = count++; //假设count是个全局变量
    temp->right = BuildHB0(h - 1);
    return temp;
}

//Q73 其他方法求Q72
//归并排序，从结点数范围入手，不从树高度入手，不用维护全局count变量
//初始调用函数可能是BuildHB0（1,1 << h) 1<<h是为了计算2^(h+1) - 1的位移操作
//TC :O(n) ,SC: O(logn) logn表示栈最大大小 值等于树的高度
struct BinarySearchTreeNode *BuildHB0(int l, int r)
{
    struct BinarySearchTreeNode *temp;
    int mid = l + (r - 1) / 2;
    if (l > r)
        return NULL;
    temp = (struct BinarySearchTreeNode *)malloc(sizeof(struct BinarySearchTreeNode));

    temp->data = mid;
    temp->left = BuildHB0(l, mid - 1);
    temp->right = BuildHB0(mid + 1, r);
    return temp;
}

//Q74 构建高度为0,1,2,3,4,5的最小AVL树，高度为6的最小AVL树的结点数是多少
/*
N(0) = 1
N(1) =2
N(h) = 1+N(h-1)+N(h-2)
N(2) = 1+N(1)+N(0) =1+2+1 =4
N(3) = 1+N(2)+N(1) = 1+4+2 = 7
N(4) = 1+N(3)+N(2) = 1+7+4 = 12
N(5) = 1+N(4)+N(3) = 1 +12+7 = 20
N(6) = 1+N(5)+N(4) = 1 +20 +12 +33
*/

//Q75 对Q72 高度h的最小AVL树有多少种形态
/*
NS(h)的最小AVL树不同形态的个数
NS(h) = 2*NS(h-1)*NS(h-2)
*/
//Q76 判断二叉搜索树是否AVL树
int IsAVL(struct BinarySearchTreeNode *root)
{
    int left, right;
    if (!root)
        return 0;
    left = IsAVL(root->left); //向左遍历
    if (left == -1)
        return left;
    right = IsAVL(root->right); //向右遍历
    if (right == -1)
        return right;
    if (abs(left - right) > 1) //判断高度差
        return -1;
    return __max(left, right) + 1;
}

//Q77 创建高度h拥有最少结点的AVL树
struct AVLTreeNode *GenerateAVLTree(int h)
{
    struct AVLTreeNode *temp;
    if (h == 0)
        return NULL;
    temp = (struct AVLTreeNode *)malloc(sizeof(struct AVLTreeNode));
    temp->left = GenerateAVLTree(h - 1);
    temp->data = count++; //假设count是全局变量
    temp->right = GenerateAVLTree(h - 2);
    temp->height = temp->left->height + 1; //或者temp->height = h;
    return temp;
}

//Q78 一棵n个值为整数的结点的AVL树和两个整数a,b，其中 a<=b，算法统计值在[a,b]范围内的结点个数
//利用二叉搜索树的递归属性，结点值是在[a,b]范围内 [a,b]左侧，[a,b]右侧 三种情况，只有第一种情况的子树需要处理
//类似中序遍历的时间复杂度，左子树右子树不包含目标就跳过 最坏时间O(n) 参考BST中类似的问题
int RangeCount(struct AVLTreeNode *root, int a, int b)
{
    if (root == NULL)
        return 0;
    else if (root->data > b)                  //判断是否在范围外，是则向左（更小方向搜索
        return RangeCount(root->left, a, b);  //L
    else if (root->data < a)                  //判断是否在范围外，是则向右（更大方向搜索
        return RangeCount(root->right, a, b); //R
    else if (root->data >= a & root->data <= b)
        return RangeCount(root->left, a, b) + RangeCount(root->right, a, b) + 1;
}

//Q79 BST/AVL树 其中每个结点包含2个数据元素，它的值和它子树结点个数 用中序遍历前驱结点值替换结点的第二个数据的方式 转换为另外一棵BST，每个结点合并中序前驱结点值
/*
        6|6                                     6|5
    4|2      9|2             =>             4|2      9|-
2|0    5|0 7|1                                     7|8
               8|0
*/
//最简单方法层次遍历，时间O(nlogn)空间O(n)

struct BinarySearchTree *TreeCompression(struct BinarySearchTree *root)
{
    struct BinarySearchTree *temp, *temp2;
    struct Queue *Q = CreateQueue();
    if (!root)
        return;
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (temp->left && temp->right && temp->left->data2 > temp->right->data2)
            temp2 = FindMax(temp);
        else
            temp2 = FindMin(temp);
        temp->data2 = temp2->data2 //处理当前结点
                          //删除结点temp2
                          DeleteNodeInBST(temp2);
        if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
}

//Q80 降低Q79的复杂度 中序遍历 时O(n)空O(1) 需要递归堆栈
struct BinarySearchTreeNode *TreeCompression(struct BinarySearchTreeNode *root, int *previousNodeData)
{
    if (!root)
        return NULL;
    TreeCompression(root->left, previousNodeData); //LDR先遍历L
    if (*previousNodeData == INT_MIN)
    {
        *previousNodeData = root->data; //记录当前遍历到的数据
        free(root);
    }
    if (*previousNodeData != INT_MIN)
    { //处理当前结点
        root->data2 = previousNodeData;
        *previousNodeData = INT_MIN;
    }
    return TreeCompression(root->right, previousNodeData);
}

//81 给一个BST和一个键值，找出值与给定键值最接近的元素
//层次遍历 对每个节点计算键值和结点值的差值，如果差值小于已保存最小差值，用新的最小值更新保存的最小差值遍历结束得到结果
//时间复杂度O(n) 空间复杂度O(n)
int ClosestInBST(struct BinaryTreeNode *root, int key)
{
    struct BinaryTreeNode *temp, *element;
    struct Queue *Q;
    int difference = INT_MAX;
    if (!root)
        return 0;
    Q = CreateQueue();
    EnQueue(Q, root);
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (difference > (abs(temp->data - key)))
        {
            difference = abs(temp->data - key);
            element = temp;
        }
        if (temp->left)
            EnQueue(Q, temp->left);
        if (temp->right)
            EnQueue(Q, temp->right);
    }
    DeleteQueue(Q);
    return element->data;
}

//Q82用递归方法求解
//类似Q18
struct BinaryTreeNode *ClosestInBST(struct BinaryTreeNode *root, int key)
{
    struct BinaryTreeNode *temp;
    if (root = NULL)
        return root;
    if (root->data == key)
        return root;
    if (key < root->data)
    {
        if (!root->left)
            return root;
        temp = ClosestInBST(root->left, key); //左子树递归遍历
        return abs(temp->data - key) > abs(root->data - key) ? root : temp;
    }
    else
    {
        if (!root->right)
            return root;
        temp = ClosestInBST(root->right, key);
        return abs(temp->data - key) > abs(root->data - key) ? root : temp;
    }
    return NULL;
}

//Q83 无限整数序列的中位数
//中位数是有序序列中间位置上的元素（如果序列为奇数个）如果偶数元素，中位数是中间两个元素的平均值
/*
BST每个结点左右子树结点数求解 时间O(logn)
使用平衡二叉搜索树，用左子树结点个数减去右子树结点个数，平衡因子为1 或0 奇数个数根节点为中位数，偶数个数中位数是根节点和中序后继结点（右子树最左下结点）平均值
插入并平衡调整平衡二叉搜索树，插入时间O(logn)查找中位数时间O(1)
参考第七章
*/
//Q84 给定一棵二叉树 消除所有半结点（只拥有一个孩子的结点）不碰叶子
//LRD后序遍历
//没看懂书里的内容，消除操作在哪？
struct BinaryTreeNode *removeHalfNodes(struct BinaryTreeNode *root)
{
    if (!root)
        return NULL;
    root->left = removeHalfNodes(root->left);
    root->right = removeHalfNodes(root->right);
    if (root->left == NULL && root->right == NULL)
        return root;
    if (root->left == NULL)
        return root->right;
    if (root->right == NULL)
        return root->left;
    return root;
}

//Q85 消除给定二叉树的叶子结点
//时间复杂度O(n)
struct BinaryTreeNode *removeLeaves(struct BinaryTreeNode *root)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else
        {
            root->left = removeLeaves(root->left);
            root->right = removeLeaves(root->right);
        }
    }
    return root;
}

//Q86 给定BST和两个整数，（最小和最大整数）作为参数，从树中删除不在两个整数参数限定范围内的元素
//LRD后序遍历， 子树改变影响双亲结点
//同样的 这个算法什么都没做，作者偷懒
//最坏O(n) 平均O(logn)
//如果给定BST是AVL树，那么O(n)为平均时间复杂度
struct BinarySearchTreeNode *PruneBST(struct BinarySearchTreeNode *root, int A, int B)
{
    if (!root)
        return NULL;
    root->left = PruneBST(root->left, A, B);
    root->right = PruneBST(root->right, A, B);
    if (A <= root->data && root->data <= B)
        return root;
    if (root->data < A)
        return root->right;
    if (root->data > B)
        return root->left;
}

//Q87 给定二叉树 连接同层所有相邻结点 每个结点有next和左右子指针
struct BinaryTreeNode
{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    struct BinaryTreeNode *next;
};

//简单方法 层次遍历更新next指针 遍历过程中链接下一层结点 如果结点有左右孩子则左孩子链接到右孩子 如果结点有next结点将当前结点最右孩子链接到next结点最左孩子
//时间复杂度
void linkingNodesOfSameLevel(struct BinaryTreeNode *root)
{
    struct Queue *Q = CreateQueue();
    struct BinaryTreeNode *prev;
    struct BinaryTreeNode *temp;
    int currentLevelNodeCount, nextLevelNodeCount;
    if (!root)
        return;
    EnQueue(Q, root);
    currentLevelNodeCount = 1;
    nextLevelNodeCount = 0;
    prev = NULL;
    while (!IsEmptyQueue(Q))
    {
        temp = DeQueue(Q);
        if (temp->left)
        {
            EnQueue(Q, temp->left);
            nextLevelNodeCount++;
        }
        if (temp->right)
        {
            EnQueue(Q, temp->right);
            nextLevelNodeCount++;
        }
        //将当前层的前一个结点链接到该结点
        if (prev)
            prev->next = temp;
        prev = temp;
        currentLevelNodeCount--;
        if (currentLevelNodeCount == 0)
        { //如果这是当前层的最后一个结点
            currentLevelNodeCount = nextLevelNodeCount;
            nextLevelNodeCount = 0;
            prev = NULL;
        }
    }
}

//Q88 降低87复杂度 逐层处理，处理下一层结点时确定当前层结点完成链接
//时间O(n) 空间O(树的深度) 用于递归堆栈
void linkingNodesOfSameLevel(struct BinaryTreeNode *root)
{
    if (!root)
        return;
    struct BinaryTreeNode *rightMostNode = NULL, *nextHead = NULL, *temp = root; //rightMostNode 当前最右结点， nextHead 下一层的头结点
    //链接当前根节点层的下一层
    while (temp != NULL)
    {
        if (temp->left != NULL) //处理左子树
        {
            if (rightMostNode == NULL) //设立最右结点指针
            {
                rightMostNode = temp->left;
                nextHead = temp->left;
            }
            else
            {
                rightMostNode->next = temp->left;    //最右结点和左子结点链接
                rightMostNode = rightMostNode->next; //指向同层下一个结点
            }
        }
        if (temp->right != NULL)
        {
            if (rightMostNode == NULL)
            {
                rightMostNode = temp->right;
                nextHead = temp->right;
            }
            else
            {
                rightMostNode->next = temp->right; //最右结点和右子结点链接
                rightMostNode = rightMostNode->next;
            }
            temp = temp->next;
        }
    }
    linkingNodesOfSameLevel(nextHead);
}

//增强树查找第K小元素操作定义
struct BinarySearchTreeNode *KthSmallest(struct BinarySearchTreeNode *X, int K)
{
    int r = size(X->left) + 1;
    if (K == r)
        return X;
    if (K < r)
        return KthSmallest(X->left, K);
    if (K > r)
        return KthSmallest(X->right, K - r);
}

