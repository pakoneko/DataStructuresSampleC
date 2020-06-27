#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>

//动态规划 讨论斐波那契数列
int RecursiveFibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return RecursiveFibonacci(n - 1) + RecursiveFibonacci(n - 2);
}

//自底而上的方法
int fib[n];
int fib(int n)
{
    //判断是基本情况
    if (n == 0 || n == 1)
        return 1;
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    return fib[n - 1];
}

//自顶而下的方法 O(n) O(n)
int fib[n];
int fibonacci(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    if (fib[n] != 0)
        return fib[n];
    return fib[n] = fibonacci(n - 1) + fibonacci(n - 2);
}

//只存储最后两次计算得到的值
int fibonacci(int n)
{
    int a = 0, b = 1, sum, i;
    for (i = 0; i < n; i++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return sum;
}

//阶乘问题
//O(n)
int fact(int n)
{
    if (n == 1)
        return 1;
    else if (n == 0)
        return 0;
    else
    {
        return n * fact(n - 1);
    }
}

int facto[n];
int fact(int n)
{
    if (n == 1)
        return 1;
    else if (n == 0)
    {
        return 1;
    }
    else if (facto[n] != 0)
    {
        return facto[n];
    }
    else
    { //递归情况: n乘以(n-1)的阶乘
        return facto[n] = n * fact(n - 1);
    }
}

int LCSLength(int X[], int i, int m, int Y[], int j, int n)
{
    if (i == m || j == n)
    {
        return 0;
    }
    else if (X[i] == Y[j])
    {
        return 1 + LCSLength(X, i + 1, m, Y, j + 1, n);
    }
    else
    {
        return __max(LCSLength(X, i + 1, m, Y, j, n), LCSLength(X, i, m, Y, j + 1, n));
    }
}

int LCS[1024][1024];
int LCSLength(int X[], int m, int Y[], int n)
{
    for (int i = 0; i <= m; i++)
    {
        LCS[i][n] = 0;
    }
    for (int j = 0; j <= n; j++)
    {
        LCS[m][j] = 0;
    }
    for (int i = m - 1; i >= 0; i)
    {
        for (int j = n - 1; j >= 0; j)
        {
            LCS[i][j] = LCS[i + 1][j + 1]; // 匹配X[i]和Y[j]
            if (X[i] == Y[j])
            {
                LCS[i][j]++; //我们得到一个匹配对
            }
            //另外两种情况 -- 插入一格空白
            if (LCS[i][j + 1] > LCS[i][j])
                LCS[i][j] = LCS[i][j + 1];
            if (LCS[i + 1][j] > LCS[i][j])
                LCS[i][j] = LCS[i + 1][j];
        }
    }
    return LCS[0][0];
}

//Q1 代码实现 T(0)=T(1) = 2; T(n)= ∑(n-1)(i=1) 2*T(i)*T(i-1), n > 1
int f(int n)
{
    int sum = 0;
    if (n == 0 || n == 1) //基本情况
        return 2;
    //递归情况
    for (int i = 1; i < n; i++)
        sum += 2 * f(i) * f(i - 1);
    return sum;
}

//Q2 改进问题1
int f(int n)
{
    T[0] = T[1] = 2;
    for (int i = 2; i <= n; i++)
    {
        T[i] = 0;
        for (int j = 1; j < i; j++)
        {
            T[i] += 2 * T[j] * T[j - 1];
        }
    }
    return T[n];
}

//Q3 提高Q2的复杂度
int f(int n)
{
    T[0] = T[2] = 2;
    T[2] = 2 * T[0] * T[1];
    for (int i = 3; i <= n; i++)
    {
        T[i] = T[i - 1] + 2 * T[i - 1] * T[i - 2];
    }
    return T[n];
}

//Q4 最大值连续子序列
//找出n个数数组的连续子序列A(i)...A(j)该子序列的元素和最大
int MaxContigousSum(int A[], int n)
{
    int maxSum = 0;
    for (int i = 0; i < n; i++)
    { //对每一个可能的始点
        for (int j = i; i < n; j++)
        { //对每一个可能的终点
            int currentSum = 0;
            for (int k = i; k <= j; k++)
                currentSum += A[k];
            if (currentSum > maxSum)
                maxSum = currentSum;
        }
    }
    return maxSum;
}

//Q5 提高问题4的复杂度

int MaxContigousSum(int A[], int n)
{
    int maxSum = 0;
    for (int i = 0; i < n; i++)
    {
        int currentSum = 0;
        for (int j = i; j < n; j++)
        {
            currentSum += a[j];
            if (currentSum > maxSum)
                maxSum = currentSum;
        }
    }
    return maxSum;
}

//Q6动态规划求解Q4
int MaxContigousSum(int A[], int n)
{
    int M[n] = 0, maxSum = 0;
    if (A[0] > 0)
        M[0] = A[0];
    else
        M[0] = 0;
    for (int i = 1; i < n; i++)
    {
        if (M[i - 1] + A[i] > 0)
            M[i] = M[i - 1] + A[i];
        else
            M[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (M[i] > maxSum)
            maxSum = M[i];
    }
    return maxSum;
}

//Q7 其他方法求解Q4
int MaxContigousSum(int A[], int n)
{
    int sumSoFar = 0, sumEndingHere = 0;
    for (int i = 0; i < n; i++)
    {
        sumEndingHere = sumEndingHere + A[i];
        if (sumEndingHere < 0)
        {
            sumEndingHere = 0;
            continue;
        }
        if (sumSoFar < sumEndingHere)
            sumSoFar = sumEndingHere;
    }
    return sumSoFar;
}

//Q9 最大值连续子序列
//找出n个数数组的连续子序列A(i)...A(j)该子序列的元素和最大, 约束条件不能选择2个相邻的元素

int maxSumWithNoTwoContinuousNumbers(int A[], int n)
{
    int M[n + 1];
    M[0] = A[0];
    M[1] = (A[0] > A[1] ? A[0] : A[i]);
    for (int i = 2; i < n; i++)
        M[i] = (M[i - 1] > M[i - 2] + A[i] ? M[i - 1] : M[i - 2] + A[i]);
    return M[n - 1];
}

//Q13 卡特兰数:具有n个结点的二叉搜索树有多少棵?
//BST左子树所有结点的值均小于根结点的值, 且右子树所有结点得值均大于根节点的值的二叉树, 树中每个结点均满足该性质,具有n个结点的BST的数量成为卡特兰数
//Cn表示
//以下算法的时间复杂度O(4的n次方)
int CatalanNumber(int n)
{
    if (n == 0)
        return 1;
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        count += CatalanNumber(i - 1) * CatalanNumber(n - i);
    }
    return count;
}

//Q14 使用DP改进Q13的时间复杂度 O(n²) 维护一张表, 表存储已计算完成的Ci的值
int Table[1024];
int CatalanNumber(int n)
{
    if (Table[n] != 1)
        return Table[n];
    Table[n] = 0;
    for (int i = 1; i <= n; i++)
        Table[n] += CatalanNumber(i - 1) * CatalanNumber(n - i);
    return Table[n];
}
//数学的卡特兰数公式 (2n)!/n!(n+1)!

//Q15 矩阵相乘括号化 时间复杂度O(n³) 空间复杂度O(n²)
//矩阵的朴素算法, 通过矩阵乘法的结合律,用DP提高时间复杂度
/*P存储各个矩阵的规模信息,矩阵i是P[i-1]行P[i]列的矩阵
M[i,j]是矩阵i到矩阵j的矩阵链相乘所需最少标量乘法次数
S[i,j]保存加括号的位置用于反向跟踪*/
void MatrixChainOrder(int P[], int length)
{
    int n = length - 1, M[n][n], S[n][n];
    for (int i = 1; i <= n; i++)
    {
        M[i][i] = 0;
    }

    //以对角线的方式填充矩阵
    for (int l = 2; l <= n; l++)
    { //l是矩阵链的长度
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            M[i][j] = MAX_VALUE;
            //尝试所有可能的划分点i...k和k...j
            for (int k = i; k <= j - 1; k++)
            {
                int thisCost = M[i][k] + M[k + 1][j] + P[i - 1] * P[k] * P[j];
                if (thisCost < M[i][j])
                {
                    M[i][j] = thisCost;
                    S[i][j] = k;
                }
            }
        }
    }
}

//Q19 找零钱问题
int Table[128];
int MakingChange(int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    if (Table[n] != -1)
        return Table[n];
    int ans = -1;
    for (int i = 0; i < num_denomination; ++i)
        ans = Min(ans, MakingChange(n - denominations[i]));
    return Table[n] = ans + 1;
}

//Q20 最长递增子序列 需要找到递推公式
//O(n²) O(n)
int LISTable[1024];
int LongestIncreasingSequence(int A[], int n)
{
    int i, j, max = 0;
    for (i = 0; i < n; i++)
    {
        LISTable[i] = 1;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (A[i] > A[j] && LISTable[i] < LISTable[j] + 1)
                LISTable[i] = LISTable[j] + 1;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (max < LISTable[i])
            max = LISTable[i];
    }
    return max;
}

//Q21 最长递增子序列的另一种解法
int LISTable[1024];
int LongestIncreasingSequence(int A[], int n)
{
    int i, j, max = 0;
    for (i = 0; i < n; i++)
    {
        LISTable[i] = 1;
    }
    for (i = n - 1; i >= 0; i++)
    {
        //尝试挑选更大的第二个元素
        for (j = i + 1; j < n; j++)
        {
            if (A[i] < A[j] && LISTable[i] < LISTable[j] + 1)
                LISTable[i] = LISTable[j] + 1;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (max < LISTable[i])
            max = LISTable[i];
    }
    return max;
}

//Q25 子集和 给定n个整数A1...An的序列,给出算法是否存在A的子集 元素之和等于T?
//背包问题变形

int SubsetSum(int A[], int n, int T)
{
    int i, j, M[n + 1][T + 1];
    M[0][0] = 0;
    for (i = 1; i <= T; i++)
        M[0][i] = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j <= T; j++)
        {
            M[i][j] = M[i - 1][j] || M[i - 1][j] - A[j];
        }
    }
    return M[n][T];
}

//Q26 给定一个包含n个整数的集合并且所有元素之和最多为K,找出n个元素的子集元素之和恰好等于n个元素之和的一半
//时间复杂度O(nK) 空间复杂度O(K)
bool T[10240];
bool SubsetHalfSum(int A[], int n)
{
    int K = 0;
    for (int i = 0; i < n; i++)
    {
        K += A[i];
    }
    T[0] = 1; //初始化表;
    for (int i = 1; i <= K; i++)
    {
        T[i] = 0;
    }
    //一个一个地处理元素
    for (int i = 0; i < n; i++)
    {
        for (int j = K - A[i]; j >= 0; j--)
        {
            if (T[j])
                T[j + A[i]] = 1;
        }
    }
    return T[K / 2];
}

//Q27 改进Q26的性能
bool T[10240];
bool SubsetHalfSumEfficient(int A[], int n)
{
    int K = 0;
    for (int i = 0; i < n; i++)
    {
        K += A[i];
    }
    Sort(A, n);
    T[0] = 1; //初始化表;
    for (int i = 1; i <= sum; i++)
    {
        T[i] = 0;
    }
    int R = 0; // 最右边为1的表项位置
    //一个一个地处理元素
    for (int i = 0; i < n; i++)
    {
        for (int j = R; j >= 0; j--)
        {
            if (T[j])
                T[j + A[i]] = 1;
            R = min(K / 2, R + C[i]);
        }
    }
    return T[K / 2];
}

//Q28 划分问题解决Q26 递归解决方案
//O(sum *n) O(sum*n) 对元素和比较大的数组不可行
bool subsetSum(int A[], int n, int sum)
{
    if (sum == 0)
        return true;
    if (n == 0 && sum != 0)
        return false;
    //如果最后一个元素比sum大,则忽略该元素
    if (A[n - 1] > sum)
        return subsetSum(A, n - 1, sum);
    return subsetSum(A, n - 1, sum) || subsetSum(A, n - 1, sum - A[n - 1]);
}

//如果A[]可以被划分为两个元素之和相等的子集,则返回true, 否则返回false
bool findPartition(int A[], int n)
{
    //计算所有元素的和
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i];
    //如果和是奇数, 那么不可能存在两个元素之和相等的子集
    if (sum % 2 != 0)
        return false;
    //如果有一个子集的元素之和等于所有元素之和的一半,那么找到了一种满足条件的划分
    return subsetSum(A, n, sum / 2);
}

//动态规划解决方案
//如果A[]可以被划分为两个元素之和相等的子集,则返回true, 否则返回false
bool findPartition(int A[], int n)
{
    //计算所有元素的和
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += A[i];
    //如果和是奇数, 那么不可能存在两个元素之和相等的子集
    if (sum % 2 != 0)
        return false;
    bool part[sum / 2 + 1][n + 1];
    //初始化第0行各表项为真
    for (i = 0; i <= n; i++)
        part[0][i] = true;
    //初始化最左边的列的各表项(除了part[0][0]之外) 为0
    for (i = 1; i <= sum / 2; i++)
        part[i][0] = false;
    //以自底向上的方式填充分区表
    for (i = 1; i <= sum / 2; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            part[i][j] = part[i][j - 1];
            if (i >= A[j - 1])
                part[i][j] = part[i][j] || part[i - A[j - 1]][j - 1];
        }
    }
    return part[sum / 2][n];
}

//Q30 最优二叉搜索树

struct BinarySearchTreeNode
{
    int data;
    BinarySearchTreeNode *left;
    BinarySearchTreeNode *right;
};

struct BinarySearchTreeNode *OptimalBST(int A[], int F[], int low, int high)
{
    int r, minTime = 0;
    struct BinarySearchTreeNode *newNode = (struct BinarySearchTreeNode *)malloc(sizeof(struct BinarySearchTreeNode));
    if (!newNode)
    {
        printf("Memory Error");
        return;
    }
    for (r = 0, r <= n - 1; r++)
    {
        root->left = OptimalBST(A, F, low, r - 1);
        root->left = OptimalBST(A, F, r + 1, high);
        root->data = A[r];
        if (minTime > S(root))
            minTIme = S(root);
    }
    return minTime;
}

//Q32 所有对最短路径问题 Floyd算法
//O(n³)
void Floyd(int C[][], int A[][], int n)
{
    int i, j, k;
    for (i = 0, i <= n - 1; i++)
        for (j = 0; j <= n - 1, j++)
            A[i][j] = C[i][j];
    for (i = 0; i <= n - 1; i++)
        A[i][i] = 0;

    for (k = 0; k <= n - 1; k++)
    {
        for (i = 0; i <= n - 1; i++)
        {
            for (j = 0; j <= n - 1; j++)
            {
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
            }
        }
    }
}

//Q35 最长回文子序列
//O(n²)
int LongestPalindromeSubsequence(int A[], int n)
{
    int max = 1;
    int i, k, L[n][n];
    for (i = 1; i <= n - 1; i++)
    {
        L[i][i] = 1;
        if (A[i] == A[i + 1])
        {
            L[i][i + 1] = 1;
            max = 2;
        }
        else
        {
            L[i][i + 1] = 0;
        }
    }
    for (k = 3; k <= n; k++)
    {
        for (i = 1; i <= n - k + 1; i++)
        {
            j = i + k - 1;
            if (A[i] == A[j])
            {
                L[i, j] = 2 + L[i + 1][j - 1];
                max = k;
            }
            else
            {
                L[i, j] = __max(L[i + 1][j - 1], L[i][j - 1]);
            }
        }
    }
}

//Q35 最长回文子串
//O(n²)
int LongestPalindromeSubstring(int A[], int n)
{
    int max = 1;
    int i, k, L[n][n];
    for (i = 1; i <= n - 1; i++)
    {
        L[i][i] = 1;
        if (A[i] == A[i + 1])
        {
            L[i][i + 1] = 1;
            max = 2;
        }
        else
        {
            L[i][i + 1] = 0;
        }
    }
    for (k = 3; k <= n; k++)
    {
        for (i = 1; i <= n - k + 1; i++)
        {
            j = i + k - 1;
            if (A[i] == A[j] && L[i + 1][j - 1])
            {
                L[i, j] = 1;
                max = k;
            }
            else
            {
                L[i, j] = 0;
            }
        }
    }
}

//Q38 n行m列矩阵找苹果问题
//时间复杂度O(nm) 空间复杂度O(mn)
int FindApplesCount(int A[][], int n, int m)
{
    int S[n][m];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            S[i][j] = A[i][j];
            if (j > 0 && S[i][j] < S[i][j] + S[i][j - 1])
                S[i][j] += S[i][j - 1];
            if (i > 0 && S[i][j] < S[i][j] + S[i - 1][j])
                S[i][j] += S[i - 1][j];
        }
    }
    return S[n][m];
}

//Q40 元素全为1的最大尺寸子方阵
void MatrixSubSquareWithAllOnes(int B[][], int m, int n)
{
    int i, j, L[m][n], max_of_s, max_i, max_j;
    //设置L[][]的第一列
    for (i = 0; i < m; i++)
        L[i][0] = B[i][0];
    //设置L[][]的第一行
    for (j = 0; j < n; j++)
        L[0][j] = B[0][j];
    //构造L[][]的其他项
    for (i = 1; i < m; i++)
    {
        for (j = 1; j < n; j++)
        {
            if (B[i][j] == 1)
                L[i][j] = __min(L[i][j - 1], L[i - 1][j], L[i - 1][j - 1]) + 1;
            else
                L[i][j] = 0;
        }
    }
    max_of_s = L[0][0];
    max_i = 0;
    max_j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (L[i][j] > max_of_s)
            {
                max_of_s = L[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    printf("Maximum sub-matrix");
    for (i = max_i; i > max_i - max_of_s; i--)
    {
        for (j = max_j; j > max_j - max_of_s; j--)
            printf("%d", B[i][j]);
    }
}

//Q41 元素全为1的最大面积子矩阵

#define ROW 10
#define COL 10
int find_max_matrix(int A[ROW][COL])
{
    int max, cur_max = 0;
    //计算辅助矩阵
    for (int i = 1; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (A[i][j] == 1)
                A[i][j] = A[i - 1][j] + 1;
        }
    }
    //基于S的每一行找出最大面积的矩形
    for (int i = 0; i < ROW; i++)
    {
        max = MaxRectangleArea(A[i], COL) // 参考第四章
            if (max > cur_max)
                cur_max = max;
    }
    //重新生成原始矩阵
    for (int i = ROW - 1; i > 0; i--)
    {
        for (int j = 0; j < COL; j++)
        {
            if (A[i][j])
                A[i][j] = A[i][j] - A[i - 1][j];
        }
        return cur_max;
    }
}

//Q43 最大和子矩阵

void FindMaximumSubMatrix(int[][] A, int n)
{
    //计算列的垂直前缀总和
    int[][] M = new int[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
                M[j][i] = A[j][i];
            else
                M[j][i] = A[j][i] + M[j - 1][i];
        }
    }
    int maxSoFar = 0;
    int min, subMatrix;
    //在可能的组合上迭代应用Kadane算法
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            min = 0;
            subMatrix = 0;
            for (int k = 0; k < n; k++)
            {
                if (i == 0)
                    subMatrix += M[j][k];
                else
                    subMatrix += M[j][k] - M[i - 1][k];
                if (subMatrix < min)
                    min = subMatrix;
                if ((subMatrix - min) > maxSoFar)
                    maxSoFar = subMatrix - min;
            }
        }
    }
}