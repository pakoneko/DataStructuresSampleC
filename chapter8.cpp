//slow Union
void MAKESET(int S[], int size)
{
    for (int i = size - 1; i >= 0; i--)
        S[i] = i;
}

int FIND(int S[], int size, int X)
{
    if (!(X >= 0 && X < size))
        return -1;
    if (S[X] == X)
        return X;
    else
        return FIND(S, size, S[X]);
}

void UNION(int S[], int size, int root1, int root2)
{
    if (FIND(S, size, root1) == FIND(S, size, root2))
        return;
    if (!((root1 >= 0 && root1 < size) && (root2 >= 0 && root2 < size)))
        return;
    S[root1] = root2;
}

//quick Union
void MAKESET(int S[], int size)
{
    for (int i = size - 1; i >= 0; i--)
        S[i] = -1;
}

int FIND(int S[], int size, int X)
{
    if (!(X >= 0 && X < size))
        return;
    if (S[X] == -1)
        return X;
    else
        return FIND(S, size, S[X]);
}

void UNIONBySize(int S[], int size, int root1, int root2)
{
    if (FIND(S, size, root1) == FIND(S, size, root2))
        return;
    if (S[root2] < S[root1])
    {                         //如果root2的结点数较多
        S[root1] = root2;     //将root2作为根
        S[root2] += S[root1]; //root1合并到root2上
    }
    else
    {
        S[root2] = root1;     //将root1作为根
        S[root1] += S[root2]; //root2合并到root1上
    }
}

void UNIONByHeight(int S[], int size, int root1, int root2)
{
    if (FIND(S, size, root1) == FIND(S, size, root2))
        return;
    if (S[root2] < S[root1]) //如果root2的高度较高
    {                     
        S[root1] = root2; //将root2作为根
    }
    else
    {
        if (S[root2] == S[root1]) //如果高度相等
        {
            S[root1]--;     
            S[root2] = root1; //root1作为根
        }
    }
}


//Q1 城市列表c1,c2 .... cn 有关系R 对于任意i，j 城市ci,cj属于一个州 R(ci,cj)=1 否则R(ci, cj) = 0 如果R存储一张表，需要的空间
//每个城市在R中有一项，空间复杂度O(n²)

//Q2 对Q1给出一个不相交集算法，每个城市放到一个集合，当且仅当ci,cj在同一个州被置于相同集合
/* 伪代码
for(int i=1;i<=n;i++){
    MAKESET(ci);
    for(int j=1;j<=i-1;j++) {
        if(R(ci, cj)){
            UNION(cj, ci);
            break;
        }
    }
}
*/

//Q3 对Q1 城市存储到不相交集ADT，给定2个城市Ci Cj 如何判断同属一个州? ONLY FIND(Ci) = FIND(Cj)的时候

//Q4 对Q1 利用支持按大小合并的链表实现UNION/FIND ADT 需要多少空间 ？ O(n)

//Q5 针对问题1 利用支持按秩合并的树 那么问题2的算法在最坏情况的时间 O(n²)

//Q6 利用不支持按秩合并的树 Q2的算法最坏时间？ 比Q5更坏吗？ 不会造成差别 跟Q5相同