#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//堆
struct Heap
{
    int *array;
    int count;     //大小(元素个数)
    int capacity;  //容量
    int heap_type; //堆类型（大顶小顶)
};
//创建堆
struct Heap *CreateHeap(int capacity, int heap_type)
{
    struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap));
    if (h == NULL)
    {
        printf("Memory Error");
        return;
    }
    h->heap_type = heap_type;
    h->count = 0;
    h->capacity = capacity;
    h->array = (int *)malloc(sizeof(int) * h->capacity);
    if (h->array == NULL)
    {
        printf("Memory Error");
        return;
    }
    return h;
}

//寻找堆的结点
//结点的parent
int Parent(struct Heap *h, int i)
{
    if (i <= 0 || i >= h->count)
        return -1;
    return i - 1 / 2;
}

//结点的孩子
//左子结点
int LeftChild(struct Heap *h, int i)
{
    int left = 2 * i + 1;
    if (left >= h->count)
        return -1;
    return left;
}

//右子结点
int RightChild(struct Heap *h, int i)
{
    int right = 2 * i + 2;
    if (right >= h->count)
        return -1;
    return right;
}

//获得最大值元素
int GetMaximum(Heap *h)
{
    if (h->count == 0)
        return -1;
    return h->array[0];
}

//堆调整第i个位置上的元素
//自顶向下进行调整所以是向下渗透 时间复杂度 O(logn) 空间复杂度O(1)
void PercolateDown(struct Heap *h, int i)
{
    int l, r, max, temp; //左值，右值， 最大值，临时
    l = LeftChild(h, i);
    r = RightChild(h, i);
    if (l != -1 && h->array[l] > h->array[i])
        max = l;
    else
        max = i;
    if (r != -1 && h->array[r] > h->array[max])
        max = r;
    if (max != i)
    {
        //互换h->array[i] 和 h->array[max];
        temp = h->array[i];
        h->array[i] = h->array[max];
        h->array[max] = temp;
    }
    PercolateDown(h, max);
}

//删除元素
int DeleteMax(struct Heap *h)
{
    int data;
    if (h->count == 0)
        return -1;
    data = h->array[0];
    h->array[0] = h->array[h->count - 1];
    h->count--; //堆中包含元素个数-1(堆大小-1)
    PercolateDown(h, 0);
    return data;
}

//插入元素， 堆大小+1， 元素放在堆末端，自底向上做堆调整
int Insert(struct Heap *h, int data)
{
    int i;
    if (h->count == h->capacity)
        ;
    ResizeHeap(h);
    h->count++;
    i = h->count - 1;
    while (i > 0 && data > h->array[(i - 1) / 2]) //如果插入的数据大于父节点
    {
        h->array[i] = h->array[(i - 1) / 2]; //把根节点下移到i位置
        i = (i - 1) / 2;                     //i的位置指向父节点
    }
    h->array[i] = data; //数据赋给父节点
}

void ResizeHeap(struct Heap *h)
{
    int *array_old = h->array;
    h->array = (int *)malloc(sizeof(int) * h->capacity * 2);
    if (h->array == NULL)
    {
        printf("Memory Error");
        return;
    }
    for (int i = 0; i < h->capacity; i++)
        h->array[i] = array_old[i];
    h->capacity *= 2;
    free(array_old);
}

//撤销堆
void DestroyHeap(struct Heap *h)
{
    if (h == NULL)
        return;
    free(h->array);
    free(h);
    h = NULL;
}

//将数组调整成堆，简单方法：n个数组进入空堆， 连续n个插入操作，最坏开销O(nlogn)

void BuildHeap(struct Heap *h, int A[], int n)
{
    if (h == NULL)
        return;
    while (n > h->capacity)
        ResizeHeap(h);
    for (int i = 0; i < n; i++)
        h->array[i] = A[i];
    h->count = n;
    for (int i = (n - 1) / 2; i >= 0; i++)
        PercolateDown(h, i);
}

//堆排序，插入所有元素进入堆，从根不断删除元素直到堆为空
void Heapsort(int A[], int n)
{
    struct Heap *h = CreateHeap(n, 0);
    int old_size, i, temp;
    BuildHeap(h, A, n);
    old_size = h->count;
    for (i = n - 1; i > 0; i--)
    {
        //h->array[0] 是最大的元素
        temp = h->array[0];
        h->array[0] = h->array[h->count - 1];
        h->array[0] = temp; //WTH?
        h->count--;
        PercolateDown(h, i);
    }
    h->count = old_size;
}

//Q1 高度h的堆中元素最小和最大个数多少？
//最小个数 2^h -1 + 1 = 2^h ,最大个数 2^(h+1) - 1

//Q2是否存在拥有7个不相同元素小顶堆，先序遍历序列为有序序列？ yes

//Q3 是否存在拥有7个不相同元素大顶堆，先序遍历序列为有序序列？ yes

//Q4 是否存在拥有7个不相同元素大/小顶堆，中序遍历序列为有序序列？ no

//Q5 是否存在拥有7个不相同元素大/小顶堆，后序遍历序列为有序序列？ yes

//Q6 证明具有n个元素的堆的高度为logn
//一个堆至少拥有2^h个元素 最多 2^(h+1) - 1 个算数 所以 2^h <=n <= 2^(h+1) - 1 => h<=logn<=h+1 所以 h = logn

//Q7 小顶堆给出算法查找其中最大元素
//最大元素总是在叶子结点中
//最后一个结点的双亲结点的下一个结点 就是第一个叶子结点
//最后一个结点总是位于 h->count-1个位置 双亲位于 (h->count-1)/2 的位置，下一个结点位置在于
//(h->count-1)/2 +1 ≈ (h->count+1)/2
//O(n/2) ≈ O(n)
int FindMaxInMinHeap(struct Heap *h)
{
    int Max = -1;
    for (int i = (h->count + 1) / 2; i < h->count; i++)
    {
        if (h->array[i] > Max)
            Max = h->array[i];
    }
}

//Q8 给出一个算法从小顶堆删除任意元素
//删除一个元素 需要搜索，使用层次遍历搜索然后执行DeleteMin

//Q9 删除小顶堆中第i个元素 Time Complexity = O(logn).

int Delete(struct Heap *h, int i)
{
    int key;
    if (n < i) //???
    {
        printf("Wrong position");
        return;
    }
    key = h->array[i];
    h->array[i] = h->array[h->count - 1];
    h->count--;
    PercolateDown(h, i);
    return key;
}

//Q10 证明高度为h的完全二叉树所有节点高度和O(n-h)
/*完全二叉树 在第i层有2^i 个结点， 第i层结点的深度为i，高度为h-i
假设S表示这些结点的高度之和 那么 S = h + 2(h-1)+4(h-2)+...+2^(h-1)(1)
2S = 2h + 4(h – 1) + 8(h – 2) + ···+ 2^h (1)
2S – S = – h + 2 + 4 + ··· + 2^h ⇒ S = (2^(h+1) – 1) – (h – 1)
n= 2^(h+1) – 1, h = log(n+1)
最后用2^(h+1)-1代替n， S=n-(h-1) = O(n-logn)=O(n-h)
*/

//Q11 在二项堆找出所有值小于给定值k的元素
//从堆根结点搜索，根小于k则打印，并对他左右孩子都递归调用算法，如果根大于等于k，不打印并终止

//Q12 合并2个二项大顶堆第一个堆的大小m+n，第二个堆大小n
/*
大小m+n的元素位于数组前面位置，则前m个已经填满，剩下n个位置空的
直接附加第二个堆，进行堆调整
O((m+n)log(m+n))
*/

//Q13 创建n个元素堆，合并Q12两个队时间开销O(m+n)

//Q14 高效算法合并2个大顶堆（基于数组存储）两个数组均有n个元素
//依赖于堆的类型，如果是标准对，每个结点最大2个孩子，叶子结点位于最多2个不同的层，不可能比O(n)更好
//入合并两个大小m，n的二项堆 O(logm * logn)算法 m=n 复杂度 O(log²n)
//斐波那契堆的合并开销 O(1)

//Q15 小顶堆查找第k小元素算法
//对小顶堆执行k次删除 O(klogn)
int FindKthLargestEle(struct Heap *h, int k)
{
    //仅删除前k-1个元素，返回第k个元素
    for (int i = 0; i < k - 1; i++)
        DeleteMin(h);
    return DeleteMin(h);
}

//Q16 改进Q15
//假设原始小顶堆HOrig,辅助小顶堆HAux 初始Horig堆顶元素是最小的，将其插入HAux 不执行DeleteMin
//这段代码完全是抄JAVA版抄错了的 第k次while循环迭代给出第k笑元素，辅助堆大小总市小于k，每次循环迭代 辅助堆大小增加1，算法执行事件O(klogk)
Heap HOrig;
Heap HAux;
int FindKthLagestEle(int k)
{
    int heapElement;
    int count = 1;
    HAux.Insert(HOrig.Min());
    while (true)
    {
        heapElement = HAux.DeletMin();
        if (++count == k)
        {
            return heapElement;
        }
        else
        {
            HAux.Insert(heapElement.LeftChild());
            HAux.Insert(heapElement.RightChild());
        }
    }
}

//Q17大顶堆查找K个最大元素
//构建大顶堆，执行k次删除
//Q18 其他方案解决17 参考Q16 使用辅助堆

//Q19 用堆实现栈 优先队列PQ(使用小顶堆)实现栈 假设正在使用一个额外的整型变量c，c的初始值为任何一个已知的值 如0，栈ADT的实现
//作者放弃人生了直接java代码抄过来了
void Push(int element)
{
    PQ.Insert(c, element);
    c--;
}

int Pop()
{
    return PQ.DeleteMin();
}

int Top()
{
    return PQ.Min();
}

int Size()
{
    return PQ.size();
}

int IsEmpty()
{
    return PQ.IsEmpty();
}
//使用负数的当前时间替代c 可以避免上溢
void Push(int element)
{
    PQ.insert(-gettime(), element);
}

//Q20 如何利用堆实现队列？和栈的模拟实现类似

void Push(int element)
{
    PQ.Insert(c, element)
        c++;
}

int Pop()
{
    return PQ.DeleteMin();
}

int Top()
{
    return PQ.Min();
}

int Size()
{
    return PQ.size();
}

int IsEmpty()
{
    return PQ.IsEmpty();
}

//使用正数的当前时间替代c 可以避免上溢
void Push(int element)
{
    PQ.insert(gettime(), element);
}

//Q21 给定一个包含数十亿数字大文件，找出10个最大元素？
//需要找需要最大n个元素，最佳数据结构是优先队列 ，划分1000个元素的堆集合，进行堆排序，依次选出第一个10个最大元素混入下一组990个元素中重新排序
//O(n) = n/1000 * (对1000个元素堆排序时间复杂度)

//Q22 合并总共有n个元素的k个有序序列：给定k个有序序列，共包含n个元素
//k个序列大小相同，总共n个元素，每个序列大小n/k O(nk)

//Q23 改进算法时间复杂度
/*
1处理序列对，然后归并，每次取出2个序列合并，22合并总共元素O(n)个，产生k/2个序列
2重复1直到序列个数为1
1执行logk次，我们有8个序列 解析n个元素则第一轮可以得到4个序列，第二轮2个，，第三轮合并1个序列，总时间复杂度O(nlogn) 空间复杂度O(n)
*/

//Q24  改进Q23的空间复杂度
// 用O(k)的空间代价构建包含所有序列的第一个元素的大顶堆
//堆中取出最大元素，添加到输出末尾
//被取出元素的序列的下一个元素插入堆
//重复2，3直到所有序列处理完成 时间O(nlogk) 空间O(k)

//Q25给定2个均包含n个元素的数组A和B 查找最大n堆 （A[i],B[j])算法
/*
对A,B进行堆调整， 花费O(2n)≈O(n)的时间代价
不断删除元素O(2logn)≈O(logn)
O(nlogn)
*/

//Q26 小顶-大顶堆 设计数据结构 O(1)返回最小和最大，O(logn)时间内插入元素，删除最小最大元素
//2个堆Hmin和Hmax 两个数组相互指向的指针， Hmin中有个指向Hmax相同元素的指针 Hmax中有个指向Hmin相同元素的指针

//Q27动态中位数查找，设计堆结构查找中位数
//中位数对 2个堆实现 每个堆包含一半元素， 大顶堆包含最小元素，小顶堆包含最大元素 偶数大顶堆大小小于小顶堆，中位数是大顶堆最大元素和小顶堆最小元素平均值
//奇数个元素 大顶堆比小顶堆多一个元素 中位数是大顶堆最大元素

//Q28 滑动窗口内最大和 给定数组A[]滑动窗口大小w，从左往右华东，只能看到窗口w个元素，每次滑动移动一个位置
//蛮力每次移动就搜索w个元素 时间复杂度O(nw)

//Q29 改进Q28 利用堆降低到O(nlogw) 获取最大值并插入堆

//Q30 改进算法复杂度
//使用双端队列 头尾进行插入/删除操作

void MaxSlidingWindw(int A[], int n, int w, int B[])
{
    struct DoubleEndQueue *Q = CreateDoubleEndQueue();
    for (int i = 0; i < w; i++)
    {
        while (!IsEmptyQueue(Q) && A[i] >= A[QBack(Q)])
            PopBack(Q);
        PushBack(Q, i);
    }
    for (int i = w; i < n; i++)
    {
        B[i - w] = A[QFront(Q)];
        while (!IsEmptyQueue(Q) && A[i] >= A[QBack(Q)])
            PopBack(Q);
        while (!IsEmptyQueue(Q) && QFront(Q) <= i - w)
            PopFront(Q);
        PushBack(Q, i);
    }
    B[n - w] = A[QFront(Q)];
}

//Q31 优先队列 元素具有优先级的列， 设计堆，具有中位数优先级的元素最先被删除，假设堆包含n个元素，n是奇数拿优先级比中位数优先级小的元素个数n/2，否则是n/2 +-1
//利用一个小顶堆，大顶堆，小顶堆的根>大于大顶堆根，小顶堆大小=大顶堆大小 或 =大顶堆大小-1 中位数元素总市大顶堆根
//插入操作 如果新元素比大顶堆根小就插入大顶堆，不然插入小顶堆

//Q32 合并2个堆
//二项堆快速实现 查找最小元素 插入减少key 2个小顶堆H1 H2 不存在有效方法合并为一个小顶堆
//利用可合并堆
//CreateHeap()
//Insert(H, X, K) 将key为K的元素X插入堆H 中
//FindMin(H)返回H中最小key的元素
//DeleteMin(H)
//Union(H1, H2)
///二项式堆
///斐波那契堆
////还支持DecreaseKey(H, X, K)给元素Y设置更小的key K
//Delete(H, X)删除元素X

//二项式堆binomial heap 只包含一棵树的binary heap 二项堆不统， 由一组成员数组成，合并的时候不用重新构造新东西，每个成员树具有特殊形式
//递归定义 B0具有一个结点，k>=1 Bk通过合并2棵B(k-1)得到 其中一棵树根是另一棵树根的最左子结点

//斐波那契堆 没有很好的最坏情况保证，但是实现每个操作具有好的平坦代价， 跟二项式堆类似由一组有序小顶堆成员树组成，成员树的数量和高度没有限制 所有操作均为最坏O(n)时间

//Q33 无限整数序列的中位数 
//2个堆 大顶堆小顶堆 
//MaxHeap包含接收到整数的最小一半， MinHeap包含接收到整数最大一半
//MaxHeap 总<=MinHeap中的整数，同时MaxHeap中的元素个数要么等于MinHeap中的元素个数，要么比它多一个
