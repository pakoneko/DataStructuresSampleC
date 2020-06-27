#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>

//Q18
void StockStrategy(int A[], int n, int *buyDateIndex, int *sellDateIndex)
{
    int j, profit = 0;
    *buyDateIndex = 0;
    *sellDateIndex = 0;
    for (int i = 1; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            if (A[j] - A[i] > profit)
            {
                profit = A[j] - A[i];
                *buyDateIndex = i;
                *sellDateIndex = j;
            }
        }
    }
}

//Q19 改善Q18的复杂度

void StockStrategy(int A[], int left, int right)
{
    //声明必要的变量
    if (left + 1 = right)
        return (0, left, left);
    mid = left + (right - left) / 2;
    (profitLeft, buyDateIndexLeft, sellDateIndexLeft) = StockStrategy(A, left, mid);
    (profitRight, buyDateIndexRight, sellDateIndexRight) = StockStrategy(A, mid, right);
    minLeft = Min(A, left, mid);
    maxRight = Max(A, mid, right);
    profit = A[maxRight] - A[minLeft];
    if (profitLeft > max{profitRight, profit})
        return (profitLeft, buyDateIndexLeft, sellDateIndexLeft);
    else if (profitRight > max{profitLeft, profit})
        return (profitRight, buyDateIndexRight, sellDateIndexRigtht);
    else
        return (profit, minLeft, maxRight);
}

//Q23

void ShuffleArray(int A[], int l, int r)
{
    //数组的中心位置
    int c = l + (r - l) / 2, q = 1 + l + (c - l) / 2;
    if (l == r) //当数组只包含一个元素, 问题足够基本 可以直接求解
        return;
    for (int k = 1, i = q; i <= c; i++, k++)
    {
        //围绕着中心位置交换元素
        int tmp = A[i];
        A[i] = A[c + k];
        A[c + k] = tmp;
    }
    ShuffleArray(A, l, c);     //对左半数组递归调用函数
    ShuffleArray(A, c + 1, r); //对右半数组递归调用函数
}

//Q25 最大值连续子序列

int MaxSumRec(int A[], int left, int right)
{
    int MaxLeftBorderSum = 0, MaxRightBorderSum = 0, LeftBorderSum = 0, RightBorderSum = 0;
    int mid = left + (right - left) / 2;
    if (left == right) //基本情况
    {
        return A[left] > 0 ? A[left] : 0;
    }
    int MaxLeftSum = MaxSumRec(A, left, mid);
    int MaxRightSum = MaxSumRec(A, mid + 1, right);
    for (int i = mid; i >= left; i--)
    {
        LeftBorderSum += A[i];
        if (LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }
    for (int j = mid + 1; j <= right; j++)
    {
        RightBorderSum += A[j];
        if (RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    return Max(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubsequenceSum(int A[], int n)
{
    return n > 0 ? MaxSumRec(A, 0, n - 1) : 0;
}

//Q29 给出计算k的n次方的算法并讨论该算法的复杂度
int Exponential(int k, int n)
{
    if (k == 0)
        return 1;
    else
    {
        if (n % 2 == 1)
        {
            int a = Exponential(k, n - 1);
            return a * k;
        }
        else
        {
            int a = Exponential(k, n / 2);
            return a * a;
        }
    }
}