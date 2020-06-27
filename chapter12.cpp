#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

//Q1 在大小为n的数组A查找最大元素
void FindLargestInArray(int A[], int n)
{
    int large = A[0];
    for (int i = 1; i <= n - 1; i++)
    {
        if (A[i] > large)
        {
            large = A[i];
        }
    }
    printf("Largest:%d", large);
}

//Q1 在大小为n的数组A查找最大和最小元素
void FindSmallestAndLargestInArray(int A[], int n)
{
    int small = A[0];
    int large = A[0];
    for (int i = 1; i <= n - 1; i++)
    {
        if (A[i] < small)
            small = A[i];
        else if (A[i] > large)
        {
            large = A[i];
        }
    }
    printf("Smallest:%d, Largest:%d", small, large);
}

//Q3 关键字比较方法对前面的算法进行改进

//假设n为偶数,关键字成对比较
void FindWithPairComparison(int A[], int n)
{
    int large = -1, small = -1;
    for (int i = 0; i <= n - 1; i = i + 2) //i的增加步长为2
    {
        if (A[i] < A[i + 1]) //两两对比
        {
            if (A[i] < small)
                small = A[i];
            if (A[i + 1] > large)
                large = A[i + 1];
        }
        else
        {
            if (A[i + 1] < small)
                small = A[i + 1];
            if (A[i] > large)
                large = A[i];
        }
    }
    printf("Smallest:%d, Largest: %d", small, large);
}

//Q6 用划分的方法 在包含n个元素的数组S中 查找前k小元素
//蛮力法对数组元素k次扫描得到目标元素, (冒泡排序,选择排序)复杂度O(n*k)
//Q10 划分技巧解Q6
//选择分界点pivot ,划分数组A[low...pivotpoint-1]<=pivotpoint<=A[pivotpoint+1...high] 小于分界点的第k小元素定位于分界点左边,递归处理,相等的就是分界点,大于的分配到右边递归处理
int S[];
int Selection(int low, int high, int k)
{
    int pivotpoint;
    if (low == high)
    {
        return S[low];
    }
    else
    {
        pivotpoint = Partition(low, high);
        if (k == pivotpoint)
        {
            return S[pivotpoint]; //也可以打印下标从low~pivotpoint的元素
        }
        else if (k < pivotpoint)
        {
            return Selection(low, pivotpoint - 1, k); //递归处理左侧的元素
        }
        else
        {
            return Selection(pivotpoint + 1, high, k); //递归处理右侧的元素
        }
    }
}

int Partition(int low, int high)
{
    int i, j, pivotitem;
    pivotitem = S[low];
    j = low;
    for (i = low + 1; i <= high; i++)
    {
        if (S[i] < pivotitem)
        {
            j++;
            swap(S[i], S[j]);
        }
    }
    int pivotpoint = j;
    swap(S[low], S[pivotpoint]);
    return pivotpoint;
}

//Q14 给定2个包含n个元素且排好序的数组, 给出一个O(logn)的算法找这2n个元素的中位数

void FindMedian(int A[], int alo, int ahi, int B[], int blo, int bhi)
{
    int amid = alo + (ahi - alo) / 2;
    int amed = A[amid];
    int bmid = blo + (bhi - blo) / 2;
    int bmed = B[bmid];
    if (ahi - alo + bhi - blo < 4)
    {
        //处理边界情况 并在O(1)时间内解决这个小问题
        return;
    }
    else if (amed < bmed)
    {
        FindMedian(A, amid, ahi, B, blo, bmid + 1);
    }
    else
    {
        FindMedian(A, alo, amid + 1, B, bmid + 1, bhi);
    }
}

