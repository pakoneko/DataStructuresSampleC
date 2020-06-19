#include <stdlib.h>
#include <stdio.h>

//冒泡排序 O(n²)
void BubbleSort(int A[], int n)
{
    for (int pass = n - 1; pass >= 0; pass--)
    {
        for (int i = 0; i < pass - 1; i++)
        {
            if (A[i] > A[i + 1])
            {
                //交换元素
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
    }
}

//改进过的冒泡排序 O(n) 如果序列已经有序,则使用标签跳过剩下的排序过程
void BubbleSortImprove(int A[], int n)
{
    int pass, i, temp, swapped = 1;
    for (pass = n - 1; pass >= 0 && swapped; pass--)
    {
        swapped = 0;
        for (i = 0; i < pass - 1; i++)
        {
            if (A[i] > A[i + 1])
            {
                //交换元素
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                swapped = 1;
            }
        }
    }
}

//选择排序 O(n²)
void Selection(int A[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (A[j] < A[min])
                min = j;
        }
        //交换元素
        temp = A[min];
        A[min] = A[i];
        A[i] = temp;
    }
}

//插入排序 O(n+d) d是逆序次数
//最坏情况O(n²) 但实际比选择和冒泡更高效, 在规模不大数据情况下
//稳定算法, 就地算法O(1) 在线算法 可以在接收列表的同时对列表排序

void InsertionSort(int A[], int n)
{
    int i, j, v;
    for (i = 2; i <= n - 1; i++)
    {
        v = A[i];
        j = i;
        while (A[j - 1] > v && j >= 1)
        {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = v;
    }
}

//希尔排序 插入排序的扩展

void ShellSort(int A[], int array_size)
{
    int i, j, h, v;
    for (h = 1; h = array_size / 9; h = 3 * h + 1)
        ;
    for (; h > 0; h = h / 3)
    {
        for (i = h + 1; i = array_size; i += 1)
        {
            v = A[i];
            j = i;
            while (j > h && A[j - h] > v)
            {
                A[j] = A[j - h];
                j -= h;
            }
        }
    }
}

//归并排序 分治法
void Mergesort(int A[], int temp[], int left, int right)
{
    int mid;
    if (right > left)
    {
        mid = (right + left) / 2;
        Mergesort(A, temp, left, mid);
        Mergesort(A, temp, mid + 1, right);
        Merge(A, temp, mid + 1, right);
    }
}

void Merge(int A[], int temp[], int left, int mid, int right)
{
    int i, left_end, size, temp_pos;
    left_end = mid - 1;
    temp_pos = left;
    size = right - left + 1;
    while ((left <= left_end) && (mid <= right))
    {
        if (A[left] <= A[mid])
        {
            temp[temp_pos] = A[left];
            temp_pos = temp_pos + 1;
            left = left + 1;
        }
        else
        {
            temp[temp_pos] = A[mid];
            temp_pos = temp_pos + 1;
            mid = mid + 1;
        }
    }
    while (left <= left_end)
    {
        temp[temp_pos] = A[left];
        left = left + 1;
        temp_pos = temp_pos + 1;
    }
    while (mid <= right)
    {
        temp[temp_pos] = A[mid];
        mid = mid + 1;
        temp_pos = temp_pos + 1;
    }
    for (i = 0; i <= size; i++)
    {
        A[right] = temp[right];
        right = right - 1;
    }
}

//快速排序 quick sort 划分交换排序(partition exchange sort)
void Quicksort(int A[], int low, int high)
{
    int pivot;
    /*终止条件*/
    if (high > low)
    {
        pivot = Partition(A, low, high);
        Quicksort(A, low, pivot - 1);
        Quicksort(A, pivot + 1, high);
    }
}

int Partition(int A[], int low, int high)
{
    int left, right, pivot_item = A[low];
    left = low;
    right = high;
    while (left < right)
    {
        /*当item < pivot时, 向右移动left*/
        while (A[left] <= pivot_item)
            left++;
        /*当item>pivot时, 向左移动right*/
        while (A[right] > pivot_item)
            right--;
        if (left < right)
            swap(A, left, right);
    }
    /*right 所指的位置时分界点pivot的最终位置*/
    A[low] = A[right];
    A[right] = pivot_item;
    return right;
}

//树排序 使用数组创建BST二叉搜索树  中序遍历二叉搜索树产生有序数组

//线性排序算法: 计数排序, 桶排序 基数排序
//计数排序
void CountingSort(int A[], int n, int B[], int K)
{
    int C[K], i, j;
    //时间复杂度 O(K)
    for (i = 0; i < K; i++)
        C[i] = 0;
    //时间复杂度O(n)
    for (j = 0; j < n; j++)
        C[A[j]] = C[A[j]] + 1;
    //现在C[i]为数组A中值等于i的元素个数
    //时间复杂度为O(K)
    for (i = 1; i < K; i++)
        C[i] = C[i] + C[i - 1];
    //现在C[i]为数组A中值小于等于i的元素个数
    //时间复杂度为:O(n)
    for (j = n - 1; j >= 0; j--)
    {
        B[C[A[j]]] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }
}

//桶排序 对输入施加限制 提高算法性能

#define BUCKETS 10
void BucketSort(int A[], int array_size)
{
    int i, j, k;
    int buckets[BUCKETS];
    for (j = 0; j < BUCKETS; j++)
        buckets[j] = 0;
    for (i = 0; i < array_size; i++)
        ++buckets[A[i]];
    for (i = 0, j = 0; j < BUCKETS; j++)
        for (k = buckets[j]; k > 0; --k)
            A[i++] = j;
}

//Q1 判断数组是否存在重复元素, O(1)存储开销
//逐个扫描 时间复杂度O(n²)
int CheckDuplicatesInArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (A[i] == A[j])
                return true;
    return false;
}

//Q2 改善Q1时间复杂度
//使用堆排序
int CHeckDuplicatesInArray(int A[], int n)
{
    Heapsort(A, n);
    for (int i = 0; i < n - 1; i++)
        if (A[i] == A[i + 1])
            return true;
    return false;
}

//Q3 给定一个数组A[0...n-1] 每个数组元素表示选举投票,每个投票都是表示候选人ID的整数,确定哪位候选者赢得选举.
//查找重复次数最多的元素,跟踪计数器
int CheckWhoWinsTheElection(int A[], int n)
{
    int i, j, counter = 0, maxCounter = 0, candidate;
    candidate = A[0];
    for (i = 0; i < n; i++)
    {
        candidate = A[i];
        counter = 0;
        for (j = i + 1; j < n; j++)
        {
            if (A[i] == A[j])
                counter++;
        }
        if (counter > maxCounter)
        {
            maxCounter = counter;
            candidate = A[i];
        }
    }
    return candidate;
}

//Q4改善Q3复杂度
int CheckWhoWinsTheElection(int A[], int n)
{
    int i, j, currentCounter = 1, maxCounter = 1;
    int currentCandidate, maxCandidate;
    currentCandidate = maxCandidate = A[0];
    Heapsort(A, n); //O(nlogn)

    for (i = 1; i <= n; i++)
    {
        if (A[i] == currentCandidate)
            currentCounter++;
        else
        {
            currentCandidate = A[i];
            currentCounter = 1;
        }
        if (currentCounter > maxCounter)
            maxCounter = currentCounter;
        else
        {
            maxCandidate = currentCandidate;
            maxCounter = currentCounter;
        }
    }
    return maxCandidate;
}
//Q5 进一步改进Q3的时间复杂度 针对候选者少, 投票量大 使用计数排序 时间O(n)n是投票数 空间O(k)k是候选人数

//Q9 A B 分别包含n个元素的数组, 给定一个数K 在O(nlogn)时间 确定是否存在a∈A b∈B 使得a+b = K

int Find(int A[], int B[], int n, int K)
{
    int i, c;
    Heapsort(A, n); //O(nlogn)
    for (i = 0; i < n; i++)
    {                           //O(n)
        c = K - B[i];           //O(1)
        if (BinarySearch(A, c)) //O(logn)
            return 1;
    }
    return 0;
}

//Q18 找到出现次数最多的元素在数组中的出现次数
//排序后扫描排序后的数组
void CountMaxAppearance(int A[], int n)
{
    Quicksort(A, n);
    int i, j, count = 1, Number = A[0], j = 0;
    for (i = 0; i < n; i++)
    {
        if (A[j] == A)
        {
            count++;
            Number = A[j];
        }
        j = i;
    }
    printf("Number: %d,count: %d", Number, count);
}

//Q27 哪种排序更适合链表?
//归并排序
typedef struct ListNode
{
    int data;
    struct ListNode *next;
};
struct ListNode *LinkedListMergeSort(struct ListNode *first)
{
    struct ListNode *list1HEAD = NULL;
    struct ListNode *list1TAIL = NULL;
    struct ListNode *list2HEAD = NULL;
    struct ListNode *list2TAIL = NULL;
    if (first == NULL || first->next == NULL)
        return first;
    while (first != NULL)
    {
        Append(first, list1HEAD, list1TAIL);
        if (first != NULL)
            Append(first, list2HEAD, list2TAIL);
    }
    list1HEAD = LinkedListMergeSort(list1HEAD);
    list2HEAD = LinkedListMergeSort(list2HEAD);
    return Merge(list1HEAD, list2HEAD);
}

//Q28 对链表实行快速排序

void Qsort(struct ListNode *first, struct ListNode *last)
{
    struct ListNode *lesHEAD, *lesTAIL = NULL;
    struct ListNode *equHEAD, *equTAIL = NULL;
    struct ListNode *larHEAD, *larTAIL = NULL;
    struct ListNode *current = *first;
    int pivot, info;
    if (current == NULL)
        return;
    pivot = current->data;
    Append(current, equHEAD, equTAIL);
    while (current != NULL)
    {
        info = current->data;
        if (info < pivot)
            Append(current, lesHEAD, lesTAIL);
        else if (info > pivot)
            Append(current, larHEAD, larTAIL);
        else
            Append(current, equHEAD, equTAIL);
    }
    Quicksort(&lesHEAD, &lesTAIL);
    Quicksort(&larHEAD, &larTAIL);
    Join(lesHEAD, lesTAIL, equHEAD, equTAIL);
    Join(lesHEAD, equTAIL, larHEAD, larTAIL);
    first = lesHEAD;
    last = larTAIL;
}

//Q33 两个有序数组A,B 第一个数组大小m+n 只包含m个元素,另一个数组大小n ,包含n个元素, 合并为一个m+n的有序数组,结果存在第一个数组
void Merge(int A[], int m, int B[], int n)
{
    int count = m;
    int i = n - 1, j = count - 1, k = m - 1;
    for (; k >= 0; k--)
    {
        if (B[i] > A[j] || j < 0)
        {
            A[k] = B[i];
            i--;
            if (i < 0)
                break;
        }
        else
        {
            A[k] = A[j];
            j--;
        }
    }
}

