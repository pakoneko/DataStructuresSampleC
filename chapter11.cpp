#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

//无序线性搜索 O(n) O(1)
int UnOrderdLinearSearch(int A[], int n, int data)
{
    for (int i = 0; i < n; i++)
    {
        if (A[i] == data)
            return i;
    }
    return -1;
}

//排序/有序线性搜索 O(n) O(1)
int OrderedLinearSearch(int A[], int n, int data)
{
    for (int i = 0; i < n; i++)
    {
        if (A[i] == data)
            return i;
        else if (A[i] > data)
            return -1;
    }
    return -1;
}

//二分搜索
//迭代版二分搜索算法
int BinarySearchIterative(int A[], int n, int data)
{
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2; //为了避免上溢出错
        if (A[mid] == data)
            return mid;
        else if (A[mid] < data)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

//递归版二分搜索法 O(logn)
int BinarySearchRecursive(int A[], int low, int high, int data)
{
    int mid = low + (high - low) / 2;
    if (A[mid] == data)
        return mid;
    else if (A[mid] < data)
        return BinarySearchRecursive(A, mid + 1, high, data);
    else
        return BinarySearchRecursive(A, low, mid - 1, data);
    return -1;
}

//插值搜索算法 O(logn)
int InterpolationSearch(int A[], int data)
{
    int low = 0, mid, high = sizeof(A - 1);
    while (low <= high)
    {
        mid = low + (((data - A[low]) * (high - low)) / (A[high] - A[low]));
        if (data == A[mid])
            return mid + 1;
        if (data < A[mid])
            high = mid - 1;
        else
        {
            low = mid + 1;
        }
    }
}

//Q1 检查数组重复元素 O(n²)

void CheckDuplicatesBruteForce(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (A[i] == A[j])
            {
                printf("Duplicates exist:%d", A[i]);
                return;
            }
        }
    }
    printf("No duplicates in given array.");
}

//Q2 改善复杂度 (先排序再查找) O(nlogn)
void CheckDuplicatesSorting(int A[], int n)
{
    Sort(A, n);
    for (int i = 0; i < n - 1; i++)
    {
        if (A[i] == A[i + 1])
        {
            printf("Duplicates exist:%d", A[i]);
            return;
        }
    }
    printf("No duplicates in given array.");
}

//Q4 使用负数来降低Q1复杂度 O(n) 空O(1)
//前提:数组元素全是正数,且不是只读数组,元素范围必须在0~ n-1之间
void CheckDuplicates(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (A[abs(A[i])] < 0)
        {
            printf("Duplicates exists %d", A[i]);
            return;
        }
        else
            A[A[i]] = -A[A[i]];
    }
    printf("No duplicates in given array.");
}

//Q5 给出算法找出数组中出现次数最多的元素O(n²)
int MaxRepititionsBruteForce(int A[], int n)
{
    int counter = 0, max = 0;
    for (int i = 0; i < n; i++)
    {
        counter = 0;
        for (int j = 0; j < n; j++)
        {
            if (A[i] == A[j])
                counter++;
        }
        if (counter > max)
            max = counter;
    }
    return max;
}

//Q6 排序后统计来降低Q5复杂度

//Q7使用散列表解决Q5

//Q8 假设元素在0~n-1内 扫描两次解决Q5 前提数组不是只读且所有元素为正数
int MaxRepititions(int A[], int n)
{
    int counter = 0, max = 0, maxIndex;
    for (int i = 0; i < n; i++)
    {
        A[A[i] % n] += n;
    }
    for (int i = 0; i < n; i++)
    {
        if (A[i] / n > max)
        {
            max = A[i] / n;
            maxIndex = i;
        }
    }
    return maxIndex;
}

//Q13找到缺失数字 一个列表包含n-1个整数, 数字取值范围1~n 列表无重复项, 列表中缺少一个取值范围内整数找到这个丢失的整数

int FindMissingNumber(int A[], int n)
{
    int i, j, found = 0;
    for (i = 1; i <= n; i++)
    {
        found = 0;
        for (j = 0; j < n; j++)
            if (A[j] == i)
                found = 1;
        if (!found)
            return i;
    }
    return -1;
}

//Q14 使用排序技术降低复杂度 O(nlogn) O(1)

//Q15 使用散列表降低Q13复杂度

//Q16 使用求和公式 取值范围中所有整数的和 sum=n(n+1)/2 再减去所有元素,得到缺失整数
//Q17 如果Q16所有整数总和超出计算机最大整数
//对数组所有元素XOR 令结果为X 对1~n所有整数XOR 结果为Y 然后对X,Y 进行XOR 结果是缺失整数
//O(n)
int FindMissingNumber(int A[], int n)
{
    int i, X, Y;
    for (i = 0; i < n; i++)
        X ^= A[i];
    for (i = 1; i <= n; i++)
        Y ^= i;
    //实际上一个变量就够了
    return X ^ Y;
}

//Q18 查找出现次数为奇数的元素
//全部按位XOR 最后结果就是出现次数为奇数的整数 O(n) O(1)

//Q19 查找给定数组中的两个重复出现的元素 n+2个元素的数组, 元素取值范围 1~n, 只有2个元素出现两次
//O(n²)
void PrintRepeatedElements(int A[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; i < n; j++)
            if (A[i] == A[j])
                printf("%d", A[i]);
}

//Q20 基于比较的排序算法排序后再查找连续重复值可以把Q19的 时间复杂度降低到O(nlogn)

//Q21 使用计数数组来改善Q19
void PrintRepeatedElements(int A[], int size)
{
    int *count = (int *)calloc(sizeof(int), (size - 2));
    for (int i = 0; i < size; i++)
    {
        count[A[i]]++;
        if (count[A[i]] == 2)
            printf("%d", A[i]);
    }
}

//Q22 Q19中的执行数组所有元素取值范围1~n 使用异或来解决
void PrintRepeatedElements(int A[], int size)
{
    int XOR = A[0];
    int i, right_most_set_bit_no, X = 0, Y = 0;
    for (i = 1; i < size; i++) // 计算A[]所有元素XOR结果
        XOR ^= A[i];
    for (i = 1; i <= size; i++)
        XOR ^= i;                             //计算1...n所有整数XOR运算结果
    right_most_set_bit_no = XOR & ~(XOR - 1); //right_most_set_bit_no 除了保留XOR最右为1的位之外,其余位为0
    //根据XOR最右为1的位对数组进行划分,该位为1的一组,为0的一组
    for (i = 0; i < size; i++)
    {
        if (A[i] & right_most_set_bit_no)
            X = X ^ A[i]; //A[]中第一组进行异或
        else
            Y = Y ^ A[i]; //A[]中第二组进行异或
    }
    for (i = 1; i <= size; i++)
    {
        if (i & right_most_set_bit_no)
            X = X ^ i; //*A[]第一组的异或结果和{1,2...n}进行异或
        else
        {
            Y = Y ^ i; //第二组的抑或结果和{1,2...n}进行异或
        }
    }
    printf("%d and %d", X, Y);
}

//Q23 假设Q19所有元素取值范围1~n 还有其他解决方法
//求和和乘积,然后再解方程

//Q24 假设所有元素取值范围1~n ,n-1个元素重复3次,其余元素重复2次,找重复2次的元素
//全部进行异或运算,重复3次的元素将变成0 ,最后得到所有重复2次的元素

//Q25 给定n个元素数组,数组找出2个元素使和等于给定值K
//蛮力 每个输入元素都检查 O(n²)
void BruteForceSearch(int A[], int n, int K)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (A[i] + A[j] == K)
                printf("Items Found %d %d", i, j);
            return;
        }
    }
    printf("Items not found : no such Items");
}

//Q26 改善复杂度 用O(nlogn) 排序,维护2个索引变量 loIndex=0, hiIndex=n-1 计算A[loIndex]+A[hiIndex]
void Search(int A[], int n, int K)
{
    int i, j, temp;
    Sort(A, n);
    for (i = 0, j = n - 1; i < j;)
    {
        temp = A[i] + A[j];
        if (temp == K)
        {
            printf("Items Found %d %d", i, j);
            return;
        }
        else if (temp < K)
            i = i + 1;
        else
            j = j - 1;
    }
    return;
}

//Q28 如果没有排序如何解决Q25
//使用散列表(hashTable)所有数组插入散列表, 检查散列表是否存在元素K-A[X],存在则解出 时间复杂度O(n) 空间复杂度O(n)

//Q29 给定n个元素数组A, 找出三个索引i,j k 使得A[i]²+A[j]²=A[k]²
//先排序,再每个数组计算为平方并存储,搜索0~i-1范围2个元素让他们的和等于A[i]
//这里不知道他在写什么,因为排序了以后整个索引都变化了,个人认为这不是解法
void FindSumSquares(int A[], int n)
{
    Sort(A);
    for (int i = 0; i < n; i++)
        A[i] = A[i] * A[i];
    for (int i = n; i > 0; i--)
        res = false;
    if (res)
    {
        //问题26/27的解决方案
    }
}

//Q30 总和最接近于0的两个元素 包含正数和负数的数组,查找总和最接近0的元素
//蛮力 ,每个元素分别计算总和 比较后 返回最小总和
void TwoElementsWithMinSum(int A[], int n)
{
    int i, j, min_sum, sum, min_i, min_j, inv_count = 0;
    if (n < 2)
    {
        printf("Invalid Input");
        return;
    }
    /*值的初始化*/
    min_i = 0;
    min_j = 1;
    min_sum = A[0] + A[1];
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            sum = A[i] + A[j];
            if (abs(min_sum) > abs(sum))
            {
                min_sum = sum;
                min_i = i;
                min_j = j;
            }
        }
    }
    printf("The two elements are %d and %d", A[min_i], A[min_j]);
}

//Q31 改善Q30的复杂度
//对数组排序, 2个索引变量扫描数组,指向头和尾,再使用2个变量跟踪接近0的最小正和和最小负和
//i<j时 当前对的和>0小于最小正和,则更新最小正和并减少j
//当前对的和<0 大于最小负和,则更新最小负和并增加i
//否则打印当前对 O(nlogn) 用于排序 空间复杂度O(1)
int TwoElementsWithMinSumSorted(int A[], int n)
{
    int i = 0, j = n - 1, temp, positiveClosest = INT_MAX, negativeClosest = INT_MIN;
    Sort(A, n);
    while (i < j)
    {
        temp = A[i] + A[j];
        if (temp > 0)
        {
            if (temp < positiveClosest)
                positiveClosest = temp;
            j--;
        }
        else if (temp < 0)
        {
            if (temp > negativeClosest)
                negativeClosest = temp;
            i++;
        }
        else
            printf("Closest Sum: %d", A[i] + A[j]);
    }
    return (abs(negativeClosest) > positiveClosest ? positiveClosest : negativeClosest);
}

//Q32 给定n个元素数组, 在数组中找到3个元素使它们的和等于给定元素K  时间复杂度 O(n³)
void BruteForceSearch(int A[], int n, int data)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (A[i] + A[j] + A[k] == data)
                {
                    printf("Items Found: %d %d %d", i, j, k);
                    return;
                }
            }
        }
    }
    printf("Items not found: No such elements");
}

//Q34 排序技术求解Q32
//O(nlogn)+O(n²)
int Search(int A[], int n, int data)
{
    Sort(A, n);
    for (int k = 0; k < n; k++)
    {
        for (int i = k + 1, j = n - 1; i < j;)
        {
            if (A[k] + A[i] + A[j] == data)
            {
                printf("Items Found:%d %d %d", i, j, k);
                return;
            }
            else if (A[k] + A[i] + A[j] < data)
                i = i + 1;
            else
                j = j - 1;
        }
    }
    return;
}

//Q35 散列技术解决Q32
//能解决但是复杂度也不会比排序后处理效果好

//Q36 给定一个具有n个整数的数组,3-sum问题是指查找3个总和最接近0的整数
//当K为0时与Q32相同

//Q37 A包含n个不同整数的数组 索引1<=k<=n 使A[1]...A[k] 递增序列,A[k+1]...A[n] 递减序列 找到索引k (双调数组)
//假定有序数组,负数开始正数结束,(单调递增函数)找到正数起始索引, 假设我们知道输入数组长度,设计一个O(logn)算法
int Search(int A[], int n, int first, int last)
{
    int mid, first = 0, last = n - 1;
    while (first <= last)
    {
        //如果当前数组的大小为1
        if (first == last)
            return A[first];
        //如果当前数组的大小为2
        else if (first == last - 1)
            return __max(A[first], A[last]);
        //如果当前数组的大小大于等于3
        else
        {
            mid = first + (last - first) / 2;

            if (A[mid - 1] < A[mid] && A[mid] > A[mid + 1])
                return A[mid];
            else if (A[mid - 1] < A[mid] && A[mid] > A[mid + 1])
                return A[mid];
            else if (A[mid - 1] < A[mid] && A[mid] > A[mid + 1])
                return A[mid];

            else
                return INT_MIN;
        } //else结束
    }     //while结束
}
//Q38 不知道数组大小如何求解Q37
//查找A[i²]的速度移动 直到找到A[n]>0的n为止

//Q40 给定一个已经旋转位置次数有序数组, 包含n个整数,给一个O(logn)时间内在数组查找元素算法
//找到分界点,调用二分搜索算法

//查找分界点
int FindPivot(int A[], int start, int finish)
{
    if (finish - start == 0)
        return start;
    else if (start == finish - 1)
    {
        if (A[start] >= A[finish])
            return start;
        else
            return finish;
    }
    else
    {
        int mid = start + (finish - start) / 2;
        if (A[start] >= A[mid])
            return FindPivot(A, start, mid);
        else
            return FindPivot(A, mid, finish);
    }
}

//主函数
int Search(int A[], int n, int x)
{
    int pivot = FindPivot(A, 0, n - 1);
    if (A[pivot] == x)
        return pivot;
    if (A[pivot <= x])
        return BinarySearch(A, 0, pivot - 1, x);
    else
        return BinarySearch(A, pivot + 1, n - 1, x);
}

int BinarySearch(int A[], int low, int high, int x)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;
        if (x == A[mid])
            return mid;
        if (x > A[mid])
            return BinarySearch(A, (mid + 1), high, x);
        else
            return BinarySearch(A, low, (mid - 1), x);
    }
    return -1; //搜索失败则返回-1
}

//41 可以在一次扫面描完成Q40的元素搜索吗? O(logn)
int BinarySearchRotated(int A[], int start, int finish, int data)
{
    int mid = start + (finish - start) / 2;
    if (start > finish)
        return -1;
    if (data == A[mid])
        return mid;
    else if (A[start] <= A[mid])
    {
        //前半部分是有序序列
        if (data >= A[start] && data < A[mid])
            return BinarySearchRotated(A, start, mid - 1, data);
        else
            return BinarySearchRotated(A, mid + 1, finish, data);
    }
    else
    {
        //A[mid]<= A[finish] 后半部分是有序序列
        if (data > A[mid] && data <= A[finish])
            return BinarySearchRotated(A, mid + 1, finish, data);
        else
            return BinarySearchRotated(A, start, mid - 1, data);
    }
}

//Q46 给定一个由n个元素组成有序数组A(可能有重复元素)O(logn)时间给出待搜索元素在数组中第一次出现的位置索引
//查找data在数组第一次出现的位置索引要进行条件判断, 如果符合条件返回该位置mid
//mid ==low && A[mid] == data || A[mid] == data && A[mid-1]<data
int BinarySearchFirstOccurrence(int A[], int low, int high, int data)
{
    int mid;
    if (high > low)
    {
        mid = low + (high - low) / 2;
        if ((mid == low && A[mid] == data) || (A[mid] == data && A[mid - 1] < data))
            return mid;
        //优先选择数组左半部分
        else if (A[mid] >= data)
            return BinarySearchFirstOccurrence(A, low, mid - 1, data);
        else
            return BinarySearchFirstOccurrence(A, mid + 1, high, data);
    }
    return -1;
}

//Q47 给定一个由n个元素组成有序数组A(可能有重复元素)O(logn)时间给出待搜索元素在数组中  最后次出现的位置索引

//mid == high && A[mid] == data || A[mid] == data && A[mid+1]>data

int BinarySearchLastOccurrence(int A[], int low, int high, int data)
{
    int mid;
    if (high > low)
    {
        mid = low + (high - low) / 2;
        if ((mid == high && A[mid] == data) || (A[mid] == data && A[mid + 1] > data))
            return mid;
        //优先选择数组右半部分
        else if (A[mid] >= data)
            return BinarySearchFirstOccurrence(A, mid + 1, high, data);
        else
            return BinarySearchFirstOccurrence(A, low, mid - 1, data);
    }
    return -1;
}

//Q48 给定n个元素有序数组,可能有重复元素,给出指定元素出现次数
//蛮力 线性搜索 搜索过程中指定元素计数器+1 O(n)

int LinearSearchCount(int A[], int n, int data)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        if (A[i] == data)
            count++;
    return count;
}

//Q49 改善Q48
//二分搜索法 O(logn+S)

//Q50 其他方法 查找data第一次出现索引(Q46) 最后一次出现索引(Q47) 返回lastOccurrence - firstOccurrence+1  O(logn+ logn) =O(logn)

//Q52 有效找到第二小的元素
//参考第七章 构建元素对应的堆,然后GetMax的logn次比较 找到第二小

//Q54 一个元素出现次数超过n/2 次 那么它是主元素, 给出一个算法其以一个具有n个元素的数组作为参数,确定其中主元素
//2个循环跟踪不同元素最大出现次数,如果最大出现次数大于n/2 则终止循环并返回元素 如果没有元素都没超过n/2次出现说明主元素不存在 O(n²)
//Q55 把问题54解决方案时间复杂度改善到O(logn)
//二分搜索实现,然后用二叉搜索树 逐个插入BST 如果元素已经存在就增加计数
//Q56 其他方法
//排序
//Q57 改进Q54
int CheckMajority(int A[], int n)
{
    //使用先行选择算法查找A的中位数m
    //再次扫描A并统计m的出现次数
    //如果m的出现次数超过n/2次, 则返回true
    //否则返回false
}

//Q58 其他Q54方法 扫描输入数组的过程跟踪每个元素计数 如果计数0可以确定第一次到达,否则就是结果元素 O(n) O(1)
int MajorityNum(int A[], int n)
{
    int count = 0, element = -1;
    for (int i = 0; i < n; i++)
    {
        //如果计数器为0, 则当前候选人设置为主元素并将计数器设置为1
        if (count == 0)
        {
            element = A[i];
            count = 1;
        }
        else if (element == A[i])
        {
            //如果计数器不是0且元素与当前候选者相同,则递增计数器
            count++;
        }
        else
        {
            //如果计数器不是0且元素与当前候选者不同,则递减计数器
            count--;
        }
    }
    return element;
}

//Q59 给定一个包含2n个元素的数组,其中有n个元素相同,其余n个元素互不相同,找出主元素
//重复元素相对距离2, 至少2个重复元素彼此相邻 扫描数组两次 比较A[i] A[i+1], 第二次比较A[i] A[i+2]

//Q60 给定一个2n+1个整数的数组, n个整数在任意位置出现2次,1个整数只在数组某处出现1次 O(n)个操作, O(1)个辅助空间找到孤独的整数
//A XOR A =0 全部异或运算即可找到
int Solution(int A[], int n)
{
    int i, res;
    for (i = res = 0; i < (2 * n + 1); i++)
        res = res ^ A[i];
    return res;
}

// Q67 分离偶数和奇数 写出一个分离其中偶数和奇数的算法 前面放置所有偶数 后面放置所有奇数
//荷兰国旗问题
//快速排序 left= 0 ,right =n-1
//增加左索引 直到遇到奇数
//递减右索引 直到遇到偶数
//如果left<right 交换A[left]和A[right]

void DutchNationalFlag(int A[], int n)
{
    //初始化left 和right两个索引变量
    int left = 0, right = n - 1;
    while (left < right)
    {
        //持续增加left索引,直到在左边遇到奇数
        while (A[left] % 2 == 0 && left < right)
            left++;
        //持续减少right索引,直到在右边遇到偶数
        while (A[right] % 2 == 1 && left < right)
            right--;
        if (left < right)
        {
            //交换A[left]和A[right]
            swap(&A[left], &A[right]);
            left++;
            right--;
        }
    }
}

//Q68 在数组中分离0元素和1元素
//0在左侧1在右侧 只遍历一次 输入[0,1,0,1,0,0,1,1,1,0] 输出 [0,0,0,0,0,1,1,1,1,1]
//一次扫描
void Separate0and1(int A[], int n)
{
    //初始化left 和right两个索引变量
    int left = 0, right = n - 1;
    while (left < right)
    {
        //持续增加left索引,直到在左边遇到1
        while (A[left] == 0 && left < right)
            left++;
        //持续减少right索引,直到在右边遇到0
        while (A[right] == 1 && left < right)
            right--;
        //如果left小于right 则左边有一个1,右边有一个0,交换A[left]和A[right]
        if (left < right)
        {
            //交换A[left]和A[right]
            A[left] = 0;
            A[right] = 1;
            left++;
            right--;
        }
    }
}

//Q70 对包含若干0 若干1 若干2的数组排序(OR RGB元素)
void Sorting012sDutchFlagProblem(int A[], int n)
{
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high)
    {
        switch (A[mid])
        {
        case 0:
            swap(A[low], A[mid]);
            low++;
            mid++;
            break;
        case 1:
            mid++;
            break;
        case 2:
            swap(A[mid], A[high]);
            high--;
            break;
        }
    }
}
//Q73 给定n 求n!尾数为0的个数
int NumberrOfTrailingZerosInNumber(int n)
{
    int i, count = 0;
    if (n < 0)
        return -1;
    for (i = 5; n / i > 0; i *= 5)
        count += n / i;
    return count;
}

//Q74 给定2n个整数数组, a1a2a3...anb1b2b3...bn 修改为a1b2a2b2a3b3...anbn
//蛮力法2个嵌套循环
void ShuffleArray()
{
    int n = 4;
    int A[] = {1, 3, 5, 7, 2, 4, 6, 8};
    for (int i = 0, q = 1, k = n; i < n; i++, k++, q++)
    {
        for (int j = k; j > i + q; j--)
        {
            int tmp = A[j - 1];
            A[j - 1] = A[j];
            A[j] = tmp;
        }
    }
    for (int i = 0; i < 2 * n; i++)
        printf("%d", A[i]);
}
//Q75 分治技术改进Q74
//分为a1a2a3a4, b1 b2 b3 b4
//交换中心周围元素
//a3a4 b1b2 交换 a1a2 b1b2 a3a4 b3b4
//再次交换每个子数组中心周围元素 a1b1 a2b2  a3b3 a4b4

//Q76给定数组A[] 找到最大的j-i, 使得A[j]>A[i]
//输入{34,8,10,3,2,80,35,33,1} 输出6(j=7,i=1)
//O(n²)
int maxIndexDiff(int A[], int n)
{
    int maxDiff = -1;
    int i, j;
    for (i = 0; i < n; ++i)
    {
        for (j = n - 1; j > i; --j)
        {
            if (A[j] > A[i] && maxDiff < (j - i))
                maxDiff = j - i;
        }
    }
    return maxDiff;
}

//Q77 改善Q76的复杂度
//获取A[]2个最优索引, 左索引i和右索引j
//创造2个数组LeftMins, RightMaxs[] LeftMins[i]持有A[i]左侧的最小元素 RightMaxs[j]是A[j]右侧的最大元素
//如果LeftMins[i]>RightMaxs[j] LeftMins[] i++,
int maxIndexDiff(int A[], int n)
{
    int maxDiff;
    int i, j;
    int *LeftMins = (int *)malloc(sizeof(int) * n);
    int *RightMaxs = (int *)malloc(sizeof(int) * n);
    LeftMins[0] = A[0];
    for (i = 1; i < n; ++i)
    {
        LeftMins[i] = __min(A[i], LeftMins[i - 1]); //LeftMins[i]存储最小值
    }
    RightMaxs[n - 1] = A[n - 1];
    for (j = n - 2; j >= 0; --j)
        RightMaxs[j] = __max(A[j], RightMaxs[j + 1]); //RightMaxs[j]存储最大值
    i = 0, j = 0, maxDiff = -1;
    while (j < n && i < n)
    {
        if (LeftMins[i] < RightMaxs[j])
        {
            maxDiff = __max(maxDiff, j - i);
            j = j + 1;
        }
        else
        {
            i = i + 1;
        }
    }
    return maxDiff;
}
//Q78 一组元素如何判断列表是否成对有序?如果列表连续两个元素构成的元素对 都是非递减有序的 那么列表认为是成对有序的(pairwise sorted)

int checkPairwiseSorted(int A[], int n)
{
    if (n == 0 || n == 1)
        return 1;
    for (int i = 0; i < n - 1; i += 2)
    {
        if (A[i] > A[i + 1])
            return 0;
    }
    return 1;
}

//Q79 包含n个元素数组 不使用额外空间情况下打印元素的出现频率 假设都是可编辑小于n的正数
//取负技术
void frequencyCounter(int A[], int n) //数组取值范围[1,n] n是数组的大小
{
    int pos = 0;
    while (pos < n)
    {
        int expectedPos = A[pos] - 1; //获取A[pos]的值给expectedPos ,-1是表示从0开始计数
        if (A[pos] > 0 && A[expectedPos] > 0) //这个时候 pos和expectPos存储数组元素的值 不是频率
        {
            swap(A[pos], A[expectedPos]); //交换两方的值, 让A[expectedPos]获取到A[pos]的值 而A[pos]存储原来expectedPos的值(为了不使用额外的开销)
            A[expectedPos] = -1; //A[expectedPos] 计数第一次 用负数1记录频率数
        }
        else if (A[pos] > 0) //pos位置的值再次出现且expectedPos的计数<0(也就是有了计数以后A[expectedPos]存了频率)
        {
            A[expectedPos]--; //负数的计数增加1
            A[pos++] = 0; //清空pos的值并进到下一位  也可以写为A[pos] = 0; pos++;
        }
        else //在pos没有出现元素就进下一位
        {
            pos++;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        printf("%d frequency is %d\n", i + 1, abs(A[i])); //使用绝对值打印出所有的频率
    }
}
int main(int argc, char *argv[])
{
    int A[] = {10, 10, 9, 4, 7, 6, 5, 2, 3, 2, 1};
    frequencyCounter(A, sizeof(A) / sizeof(A[0]));
    return 0;
}