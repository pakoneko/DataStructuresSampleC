#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

//应用:自动完成高效存储,字符串匹配,搜索

//蛮力法
//O((n-m+1)*m) ≈ O(n*m) 空间复杂度O(1)
int BruteForceStringMatch(int T[], int n, int P[], int m)
{
    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m && P[j] == T[i + j])
            j = j + 1;
        if (j == m)
            return i;
    }
    return -1;
}

//Robin-Karp 字符串匹配算法 使用hash计数 不对T中每个可能位置判断,只有P的hash结果和T的m个字符的hash结果相同时判断
//选择hash函数 需要选择一个每个步骤只花费O(1)的时间计算T的m个字符的hash值, 否则效率不如蛮力法

// value = 0;
// for(int i=0; i<m-1;i++){
//     value = value*10;
//     value = value + P[i];
// }

//匹配算法
//Input:Pattern string P[0..m-1], δ和F
//目标:显示所有匹配的起始位置 时间复杂度O(m)
void FiniteAutomataStringMatcher(int P[], int m, int F, int δ)
{
    int q = 0;
    for (int i = 0; i < m; i++)
    {
        q = δ(q, T[i]);
        if (q == m)
            printf("Pattern occurs with shift:%d", i - m);
    }
}

//KMP算法
//假设T是被搜索字符串,P是需要匹配的模式串, 搜索模式串的时间复杂度是O(n)
//使用前缀函数, 前缀表, 失败函数

//前缀表

int F[];
//时间复杂度空间复杂度O(m)
void PrefixTable(int P[], int m)
{
    int i = 1, j = 0, F[0] = 0;
    while (i < m)
    {
        if (P[i] == P[j])
        {
            F[i] = j + 1;
            i++;
            j++;
        }
        else if (j > 0)
            j = F[j - 1]; //回溯
        else
        {
            F[i] = 0;
            i++;
        }
    }
}

//KMP搜索时间复杂度O(n+m)
int KMP(char T[], int n, int P[], int m)
{
    int i = 0, j = 0;
    PrefixTable(P, m);
    while (i < n)
    {
        if (T[i] == P[j])
        {
            if (j == m - 1)
                return i - j;
            else
            {
                i++;
                j++;
            }
        }
        else if (j > 0)
        {
            j = F[j - 1];
        }
        else
        {
            i++;
        }
    }
    return -1;
}

//字典树
struct TrieNode
{
    char data;                  //当前结点字符
    int is_End_Of_String;       //指示从根节点到当前结点形成的字符串是否为字符串
    struct TrieNode *child[26]; //指向其他trie结点的指针
};

struct TrieNode *subNode(struct TrieNode *root, char c)
{
    if (child ! = NULL)
    {
        for (int i = 0; i < 26; i++)
        {
            if (root->child[i]->data == c)
                return eachChild;
        }
    }
    return NULL;
}

//插入字典树

void InsertInTrie(struct TrieNode *root, char *word)
{
    if (!*word)
        return;
    if (!root)
    {
        struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode *));
        newNode->data = *word;
        for (int i = 0; i < 26; i++)
            newNode->child[i] = NULL;
        if (!*(word + 1))
            newNode->is_End_Of_String = 1;
        else
            newNode->child[*word] = InsertInTrie(newNode->child[*word], word + 1); //递归插入下一个字符
        return newNode;
    }
    root->child[*word] = InsertInTrie(root->child[*word], word + 1);
    return root;
}

//在字典树重搜索
int SearchInTrie(struct TrieNode *root, char *word)
{
    if (!root)
        return -1;
    if (!*word)
    {
        if (root->is_End_Of_String)
            return 1;
        else
            return -1;
    }
    if (root->data == *word)
        return SearchInTrie(root->child[*word], word + 1); //递归查找下一个
    else
        return -1;
}

//三叉搜索树
struct TSTNode
{
    char data;
    int is_End_Of_String;
    struct TSTNode *left;
    struct TSTNode *eq;
    struct TSTNode *right;
};

//三叉搜索树 递归插入
struct TSTNode *InsertInTST(struct TSTNode *root, char *word)
{
    if (root == NULL)
    {
        root = (struct TSTNode *)malloc(sizeof(struct TSTNode *));
        root->data = *word;
        root->is_End_Of_String = 1;
        root->left = root->eq = root->right = NULL;
    }
    if (*word < root->data)
        root->left = InsertInTST(root->left, word);
    else if (*word == root->data)
    {
        if (*(word + 1))
            root->eq = InsertInTST(root->eq, word + 1);
        else
            root->is_End_Of_String = 1;
    }
    else
        root->right = InsertInTST(root->right, word);
    return root;
}

//递归搜索三叉树
int SearchInTSTRecursive(struct TSTNode *root, char *word)
{
    if (!root)
        return -1;
    if (*word < root->data)
        return SearchInTSTRecursive(root->left, word);
    else if (*word > root->data)
        return SearchInTSTRecursive(root->right, word);
    else
    {
        if (root->is_End_Of_String && *(word + 1) == 0)
            return 1;
        return SearchInTSTRecursive(root->eq, ++word);
    }
}

//非递归搜索三叉树
int SearchInTSTNonRecursive(struct TSTNode *root, char *word)
{
    while (root)
    {
        if (*word < root->data)
            root = root->left;
        else if (*word == root->data)
        {
            if (root->is_End_Of_String && *(word + 1) == 0)
                return 1;
            word++;
            root = root->eq;
        }
        else
        {
            root = root->right;
        }
    }
    return -1;
}

//输出三叉搜索树的所有单词
char word[1024];
void DisplayAllWords(struct TSTNode *root)
{
    if (!root)
        return;
    DisplayAllWords(root->left);
    //蛮怪的, i哪里来的
    word[i] = root->data;
    if (root->is_End_Of_String)
    {
        word[i] = '\0';
        printf("%c", word);
    }
    i++;
    DisplayAllWords(root->eq);
    i--;
    DisplayAllWords(root->right);
}

//查找TST最长单词的长度
//与求BST高度相似
int MaxLengthOfLargestWordInTST(struct TSTNode *root)
{
    if (!root)
        return 0;
    return __max(MaxLengthOfLargestWordInTST(root->left), MaxLengthOfLargestWordInTST(root->eq) + 1, MaxLengthOfLargestWordInTST(root->right));
}

//Q5 给出一个反转字符串的算法

//如果str可编辑 O(n) O(n)
char *ReversingString(char str[])
{
    char temp, start, end;
    if (str == NULL || *str == '\n')
        return str;
    for (end = 0; str[end]; end++)
        ;
    end--;
    for (start = 0; start < end; start++, end--)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
    }
    return str;
}

//Q6 不可编辑的字符串反转
char *ReversingString(char *str)
{
    int start, end, len;
    char temp, *ptr = NULL;
    len = strlen(str);
    ptr = (char *)malloc(sizeof(char) * (len + 1));
    ptr = strcpy(ptr, str);
    for (start = 0, end = len - 1; start <= end; start++, end--)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
    }
}

//Q7 不使用临时变量反转字符串 XOR逻辑

char *ReversingString(char *str)
{
    int start = 0, end = strlen(str) - 1;
    while (start < end)
    {
        str[start] ^= str[end];
        str[end] ^= str[start];
        str[start] ^= str[end];
        ++start;
        --end;
    }
    return str;
}

//Q8 给定文本和一个模式, 给出在文本匹配模式的算法,假设?和*是通配符
//蛮力法 O(mn)
int PatternMatching(char *text, char *pattern)
{
    if (*pattern == 0)
        return 1;
    if (*text == 0)
        return *pattern == 0;
    if ('?' == *pattern)
        return PatternMatching(text + 1, pattern + 1) || PatternMatching(text, pattern + 1);
    if ('*' == *pattern)
        return PatternMatching(text + 1, pattern) || PatternMatching(text, pattern + 1);
    if (*text == *pattern)
        return PatternMatching(text + 1, pattern + 1);
    return -1;
}

//Q9 给一个算法翻转一个句子的单词 O(2n) ≈ O(n)
void ReverseWordsInSentence(char *text)
{
    int wordStart, wordEnd, length;
    length = strlen(text);
    ReversingString(text, 0, length - 1);
    for (wordStart = wordEnd = 0; wordEnd < length; wordEnd++)
    {
        if (text[wordEnd] !='')
        {
            wordStart = wordEnd;
            while (text[wordEnd] !='' && wordEnd < length)
                wordEnd++;
            wordEnd--;
            ReversingString(text, wordStart, wordEnd);
        }
    }
}

void ReversingString(char text[], int start, int end)
{
    for (char temp; start < end; start++, end--)
    {
        temp = text[end];
        text[end] = text[start];
        text[start] = temp;
    }
}

//Q10 字符串排列(anagrams) //生成字符串中所有可能的字符排列 生成n!个长度为n的字符串
void Permutation(int depth, char *permutation, int *used, char *original)
{
    int length = strlen(original);
    if (depth == length)
        printf("%c", permutation);
    else
    {
        for (int i = 0; i < length; i++)
        {
            if (!used[i])
            {
                used[i] = 1;
                permutation[depth] = original[i];
                Permutation(depth + 1, permutation, used, original);
                used[i] = 0;
            }
        }
    }
}

//Q11 字符串的组合: 2个组合不同顺序包含相同字符,则认为相同,给出一个算法打印字符串中所有可能字符组合
void Combinations(int depth, char *combination, int start, char *original)
{
    int length = strlen(original);
    for (int i = start; i < length; i++)
    {
        combination[depth] = original[i];
        combination[depth + 1] = '\0';
        printf("%c", combination);
        if (i < length - 1)
            Combinations(depth + 1, combination, start + 1, original);
    }
}

//Q12 给定字符串ABCCBCBA 递归删除相邻相同字符
//需要检查是否有相同字符构成字符对, 如果有则消除字符对

void RemoveAdjacentPairs(char *str)
{
    int len = strlen(str), i, j = 0;
    for (i = 1; i <= len; i++)
    {
        while ((str[i] == str[j]) && (j >= 0))
        { //消除字符对
            i++;
            j--;
        }
        str[++j] = str[i];
    }
    return;
}

//Q13 给定一组字符CHARS和输入串INPUT 在str找到最小窗口使其能在O(n)时间内包含CHARS中的所有字符
//类似滑动窗口方法
#define MAX 256
void MinLengthWindow(char input[], char chars[])
{
    int shouldfind[MAX] = {
        0,
    },
        hasfound[MAX] = {
            0,
        };
    int j = 0, cnt = 0, start = 0, finish, minwindow = INT_MAX;
    int charlen = strlen(chars), iplen = strlen(input); //获取CHARS的长度 charlen, INPUT的长度 iplen
    for (int i = 0; i < charlen; i++)
    {
        shouldfind[chars[i]] += 1; //把CHARS每个字符的计数放在shouldfind里
    }
    finish = iplen;
    for (int i = 0; i < iplen; i++)
    {
        if (!shouldfind[input[i]]) //没找到就继续
            continue;
        hasfound[input[i]] += 1; //input[i]是被需要的字符,计数+1
        if (shouldfind[input[i]] >= hasfound[input[i]])
            cnt++;
        if (cnt == charlen) //如果count是chars[]数组的长度,则尽可能多地滑动窗口
        {
            while (shouldfind[input[j]] == 0 || hasfound[input[j]] > shouldfind[input[j]])
            {
                if (hasfound[input[j]] > shouldfind[input[j]])
                    hasfound[input[j]]--;
                j++;
            }
            if (minwindow > (i - j + 1)) //如果当前窗口长度小于当前发现的最小窗口长度, 则更新最小窗口长度
            {
                minwindow = i - j + 1;
                finish = i;
                start = j;
            }
        }
    }
    printf("Start:%d and Finish:%d", start, finish);
}

//Q14 给定一个二维数组和一个字符串模式, 给出一个算法查找是否在二维数组中存在该字符串模式, 模式可以是任何方式
//mat:二维数组, pat 字符串pattern nrow:行号,ncol 列号
#define MAX 100
bool FindMatch_wrapper(char mat[MAX][MAX], char *pat, int nrow, int ncol)
{
    if (strlen(pat) > nrow * ncol)
        return false;
    int used[MAX][MAX] = {
        {
            0,
        },
    };
    return FindMatch(mat, pat, used, 0, 0, nrow, ncol, 0);
}

bool FindMatch(char mat[MAX][MAX], char *pat, int used[MAX][MAX], int x, int y, int nrow, int ncol, int level)
{
    if (level == strlen(pat)) //模式匹配 如果越过了模式的最后一格字符就返回true
    {
        return true;
    }
    if (nrow == x || nrow == y)
        return false;
    if (used[x][y])
        return false;
    if (mat[x][y] != pat[level] && level == 0)
    {
        if (x < (nrow - 1))
            return FindMatch(mat, pat, used, x + 1, y, nrow, ncol, level); //同行的下一个元素
        else if (y < (ncol - 1))
            return FindMatch(mat, pat, used, 0, y + 1, nrow, ncol, level); //来自同一列的第一个元素
        else
            return false;
    }
    else if (mat[x][y] == pat[level])
    {
        bool res;
        used[x][y] = 1; //标记该位置已访问过
        //在8个邻居中匹配子模式
        res = (x > 0 ? FindMatch(mat, pat, used, x - 1, y, nrow, ncol, level + 1) : false) ||                                      //如果x大于0 查找前一个元素
              (res = x < (nrow - 1) ? FindMatch(mat, pat, used, x + 1, y, nrow, ncol, level + 1) : false) ||                       //在行末之前持续找后一个元素
              (res = y > 0 ? FindMatch(mat, pat, used, x, y - 1, nrow, ncol, level + 1) : false) ||                                //在上一行查找元素
              (res = y < (ncol - 1) ? FindMatch(mat, pat, used, x, y + 1, nrow, ncol, level + 1) : false) ||                       //在下一行查找元素
              (res = x < (nrow - 1) && (y < ncol - 1) ? FindMatch(mat, pat, used, x + 1, y + 1, nrow, ncol, level + 1) : false) || //在右下一格查找元素
              (res = x < (nrow - 1) && y > 0 ? FindMatch(mat, pat, used, x + 1, y - 1, nrow, ncol, level + 1) : false) ||          //在右上一格查找元素
              (res = x > 0 && (y < ncol - 1) ? FindMatch(mat, pat, used, x - 1, y + 1, nrow, ncol, level + 1) : false) ||          //在左下一格查找元素
              (res = x > 0 && y > 0 ? FindMatch(mat, pat, used, x - 1, y - 1, nrow, ncol, level + 1) : false);                     //在左上一格查找元素
        used[x][y] = 0;                                                                                                            //标记该位置未被访问过
        return res;
    }
    else
    {
        return false;
    }
}

//Q15 给定2个字符串str1 str2 写一个算法打印输出他们所有的交错字符
//设str1的长度为m,str2的长度为n,count(m,n)为这两个字符串所有的交错字符串的计数
void PrintInterleavings(char *str1, char *str2, char *iStr, int m, int n, int i)
{
    //递归基础: 如果str1和str2中的所有字符均已包含在输出字符串中, 则打印输出字符串
    if (m == 0 && n == 0)
        printf("%s\n", iStr);
    //如果str1中的某些字符还未包含在输出字符串中, 那么包含剩下字符中的第一个字符, 然后对剩下的字符进行递归处理
    if (m != 0)
    {
        iStr[i] = str1[0];
        PrintInterleavings(str1 + 1, str2, iStr, m - 1, n, i + 1);
    }
    //如果str2中的某些字符还未包含在输出字符串中,那么包含剩下字符中的第一个字符,然后对剩下的字符进行递归处理.
    if (n != 0)
    {
        iStr[i] = str2[0];
        PrintInterleavings(str1, str2 + 1, iStr, m, n - 1, i + 1);
    }
}

void Print(char *str1, char *str2, int m, int n)
{
    //为输出字符串分配内存空间
    char *iStr = (char *)malloc((m + n + 1) * sizeof(char));
    //设置输出字符串的结束符号
    iStr[m + n] = '\0';
    //调用PrintInterleavings()输出所有的交错字符串
    PrintInterleavings(str1, str2, iStr, m, n, 0);
    free(iStr);
}

//Q17 编写一格方法,用'%20'替换字符串中的所有空格, 假设字符串在其末尾 有足够的空间来容纳额外的字符
void encodeSpaceWithString(char *A)
{
    char *space = "%20";
    int stringLength = strlen(A);
    if (stringLength == 0)
    {
        return;
    }
    int i, numberOfSpaces = 0;
    for (i = 0; i < stringLength; i++)
    {
        if (A[i] == ' ' || A[i] == '\t')
        {
            numberOfSpaces++;
        }
    }
    if (!numberOfSpaces)
        return;
    int newLength = stringLength + numberOfSpaces * 2; //增加字符串的长度
    A[newLength] = '\0';                               //在字符串尾设置完结字符
    for (i = stringLength - 1; i >= 0; i--)
    {
        if (A[i] == ' ' || A[i] == '\t')
        {
            A[newLength--] = '0';
            A[newLength--] = '2';
            A[newLength--] = '%';
        }
        else
        {
            A[newLength--] = A[i];
        }
    }
}