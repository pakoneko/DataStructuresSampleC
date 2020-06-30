#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <locale.h>

//二进制数的逆置
//逆置每个位都需要一次迭代
unsigned int n, nReverse = n;
int s = sizeof(n);
for (; n; n >>= 1)
{
    nReverse <<= 1;
    nReverse |= n & 1;
    s--;
}
nReverse <<= s;

//统计定制n的二进制形式中1的个数
//逐位在行
unsigned int n;
unsigned int count = 0;
while (n)
{
    count += n & 1;
    n >>= 1;
}

//利用模取方法

unsigned int n;
unsigned int count = 0;
while (n)
{
    if (n % 2 == 1)
        count++;
    n = n / 2;
}

//利用翻转方法 n&n-1
unsigned int n;
unsigned int count = 0;
while (n)
{
    count++;
    n & = n - 1;
}

//利用预处理
int Table = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
int count = 0;
for (; n; n >> 4)
    count = count + Table(n & 0xF);
return count;

//Q1 给出一个算法按螺旋秩序打印矩阵元素
//O(n²) O(1)
void Spiral(int **A, int n)
{
    int rowStart = 0, columnStart = 0;
    int rowEnd = n - 1, columnEnd = n - 1;
    while (rowStart <= rowEnd && columnStart <= columnEnd)
    {
        int i = rowStart, j = columnStart;
        for (j = columnStart; j <= columnEnd; j++)
        {
            printf("%d", A[i][j]);
        }
        for (i = rowStart + 1, j--; i <= rowEnd; i++)
        {
            printf("%d", A[i][j]);
        }
        for (j = columnEnd - 1, i--; j >= columnStart; j--)
        {
            printf("%d", A[i][j]);
        }
        for (i = rowEnd - 1, j++; i >= rowStart + 1; i--)
        {
            printf("%d", A[i][j]);
        }
        rowStart++;
        columnStart++;
        rowEnd--;
        columnEnd--;
    }
}

//Q2 给出一个洗牌算法
//O(n) O(1)
void Shuffle(int cards[], int n)
{
    srand(time(0)); //初始化随机数种子
    for (int i = 0; i < n; i++)
    {
        cards[i] = i; //将卡片值存入数组
    }
    for (int i = 0; i < n; i++)
    {
        int r = i + (rand() % (52 - i)); //随机选择一个元素
        int temp = cards[i];
        cards[i] = cards[r];
        cards[r] = temp;
    }
    printf("Shuffled Cards:");
    for (int i = 0; i < n; i++)
        printf("%d", cards[i]);
}

//Q3 给出一个利用求逆运算实现数组旋转的算法
//rotate(A[],d,n) 将包含n个元素的A[]向后旋转d个元素
rotate(Array[], d, n);
reverse(Array[], 1, d);
reverse(Array[], d + 1, n);
reverse(Array[], 1, n);

void leftRotate(int Array[], int d, int n)
{
    reverseArray(Array, 0, d - 1);
    reverseArray(Array, d, n - 1);
    reverseArray(Array, 0, n - 1);
}

//公共函数:打印数组Array
void printArray(int Array[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d", Array[i]);
    printf("%\n");
}

//实现逆置数组Array[]从start下表开始到end下表位置范围内元素的函数
void reverseArray(int Array[], int start, int end)
{
    int i;
    int temp;
    while (start < end)
    {
        temp = Array[start];
        Array[start] = Array[end];
        Array[end] = temp;
        start++;
        end--;
    }
}

//Q5 字典中查找字谜 perl示例代码
#step 1
open("MYFILE", <dictionary.txt>);
while (<MYFILE>)
{
    $row = $_;
    chomp($row);
    push(@words, $row);
}
my % hashdic = ();

#step 2
foreach
    $words(@words)
    {
    @not_sorted=split(//, $words);
    @sorted=sort(@not_sorted);
    $name = join("", @sorted);
    if(exists $hashdic{$name}) {
            $hashdic{$name}.= "$words";
    }
    else
    {
            {
                $hashdic{$name} = $words;
            }
    }
    $size = keys%hashdic;
    }

#step 3
open("jumbled", <jumbles.txt>);
while (<jumbled>)
{
    $jum = $_;
    chomp($jum);
    @not_sored1=split(//, $jum);
    @sorted1 = sort(@not_sorted1);
    @name1 = join("", @sorted1);
    if(length($hashdic{$name1})<1){
        print "\n$jum: NO MATCHES";
    }
    else {
        @value = split(/ /, $hashdic{$name1});
        print "\n$jum:@values";
    }
}

//Q7 给定包含单词和空格的字符串,编写程序将空格移动到字符串的头部
//只能遍历数组一次,并就地调整字符串 O(n) O(1)

//2个索引i,j 从尾到头遍历数组
void mySwap(char A[], int i, int j)
{
    char temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void testCode(int argc, char *argv[])
{
    char sparr[] = "move these spaces to beginning";
    printf("Value of A is: %s\n", sparr);
    moveSpacesToBegin(sparr);
    printf("Value of A is:%s", sparr);
}

void moveSpacesToBegin(char A[])
{
    int i = strlen(A) - 1;
    int j = i;
    for (; j >= 0; j--)
    {
        if (!isspace(A[j]))
            mySwap(A, i--, j);
    }
}

//Q8 改善Q7的复杂度

void moveSpacesToBegin(char A[])
{
    int n = strlen(A) - 1, count = n;
    int i = n;
    for (; i >= 0; i--)
    {
        if (A[i] != "")
            A[count--] = A[i];
    }
    while (count >= 0)
        A[count--] = "";
}

int testCode()
{
    char sparr[] = "move these spaces to beginning";
    printf("Value of A is: %s\n", sparr);
    moveSpacesToBegin(sparr);
    printf("Value of A is %s", sparr);
}

//Q9 给定包含单词和空格的字符串,编写程序将空格移动到字符串的尾部
//只能遍历数组一次,并就地调整字符串 O(n) O(1)

void moveSpacesToEnd(char A[])
{
    int count = 0; //统计非空格字符
    int n = strlen(A) - 1;
    int i = 0;
    for (; i <= n; i++)
    {
        if (!isspace(A[i]))
            A[count++] = A[i];
    }
    while (count <= n)
        A[++count] = "";
}

void testCode()
{
    char sparr[] = "move these spaces to beginning";
    printf("Value of A is: %s\n", sparr);
    moveSpacesToEnd(sparr);
    printf("Value of A is %s", sparr);
}

//Q10 将0元素移动到结尾
//O(n) O(1)
void moveZeroToEnd(int A[], int size)
{

    int i = 0, j = 0;

    while (i <= size - 1)
    {
        if (A[i] != 0)
        {
            A[j++] = A[i];
        }
        i++;
    }
    while (j <= size - 1)
    {
        A[j++] = 0;
    }
}

int testCode()
{
    int A[] = {1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0};
    int i;
    int size = sizeof(A) / sizeof(A[0]);
    moveZeroToEnd(A, size);
    for (i = 0; i <= size - 1; i++)
    {
        printf("%d", A[i]);
    }
    return 0;
}

//Q11 对于O10的复杂度改进

void mySwap(int A[], int i, int j){
    int temp=A[i];
    A[i]= A[j];
    A[j]= temp;
}

void moveZerosToEnd(int A[], int len){
    int i, j;
    for(i=0,j=0;i<len;i++){
        if(A[i]!=0)
            mySwap(A,j++,i);
    }
}

//Q12 包含负数和正数的数组,分离正数和负数

void seperateNegPos(int A[], int len){
    int i, j;
    for(i=0,j=0;i<len;i++){
        if(A[i]<0)
            mySwap(A,j++,i);
    }
}