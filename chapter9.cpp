#include <stdlib.h>
#include <stdio.h>
//注:本章主要实现用的是伪代码, 如果需要具体的实现代码可以参考其他书籍的数据结构C++版,这里写的非常简略
//Graph
//图的邻接矩阵
struct Graph
{
    int V;
    int E;
    int **Adj; //二维矩阵
};

//基于邻接矩阵表示法创建一个图
struct Graph *adjMatrixOfGraph()
{
    int i, u, v;
    struct Graph *G = (struct Graph *)malloc(sizeof(struct Graph));
    if (!G)
    {
        printf("Memory Error");
        return;
    }

    scanf("Number of Vertices:%d, Number of Edges:%d", &G->V, &G->E);
    G->Adj = malloc(sizeof(G->V * G->V));
    for (u = 0; u < G->V; u++)
        for (v = 0; v < G->V; v++)
            G->Adj[v][v] = 0;
    for (i = 0; i < G->E; i++)
    {
        //读取一条边的信息
        scanf("Reading Edge: %d %d", &u, &v);
        //对无向图而言，需要设置两个位
        G->Adj[u][v] = 1;
        G->Adj[v][u] = 1;
    }
    return G;
}

//图的邻接表
struct Graph
{
    int V;
    int E;
    int *Adj; //指向链表的头指针
};

//链表的结点结构
struct ListNode
{
    int vertexNumber;      //顶点数字
    struct ListNode *next; //链表的下一结点指针
};

//基于邻接表表示法创建图
struct Graph *adjListOfGraph()
{
    int i, x, y;
    struct ListNode *temp;
    struct Graph *G = (struct Graph *)malloc(sizeof(struct Graph));
    if (!G)
    {
        printf("Memory Error");
        return;
    }
    scanf("Number of Vertices:%d, Number of Edges:%d", &G->V, &G->E); //几个点,几个边
    G->Adj = malloc(sizeof(struct ListNode));
    for (i = 0; i < G->V; i++)
    {
        G->Adj[i] = (struct ListNode *)malloc(sizeof(struct ListNode));
        G->Adj[i]->vertexNumber = i;
        G->Adj[i]->next = G->Adj[i]; //初始邻接表 next都指向自己
    }
    for (i = 0; i < G->E; i++)
    {
        //读取一条边的信息
        scanf("Reading Edge: %d %d", &x, &y); //x到y点的边
        temp = (struct ListNode *)malloc(sizeof(struct ListNode));
        temp->vertexNumber = y; //??
        temp->next = G->Adj[x];
        G->Adj[x]->next = temp;

        temp = (struct ListNode *)malloc(sizeof(struct ListNode));
        temp->vertexNumber = y;
        temp->next = G->Adj[y];
        G->Adj[y]->next = temp;
    }
    return G;
}

//设置一个全局数组
int Visited[G->V]; //图的顶点值
void DFS(struct Graph *G, int u)
{
    Visited[u] = 1; //已访问的设为1
    for (int v = 0; v < G->V; v++)
    {
        /*
        例如 如果邻接矩阵被用来表示图,那么查找u的尚未被访问过的邻接顶点的条件是: if(!Visited[v] && G->Adj[u][v])
        */
        for (each unvisited adjacent node v of u) //伪代码
        {
            DFS(G, v);
        }
    }
}

void DFSTraversal(struct Graph *G)
{
    for (int i = 0; i < G->V; i++)
        Visited[i] = 0;
    //如果图有不止一个连通分量,那么这个循环是必要的
    for (int i = 0; i < G->V; i++)
        if (!Visited[i])
            DFS(G, i);
}

//广度优先搜索BFS

void BFS(struct Graph *G, int u)
{
    int v;
    struct Queue *Q = CreateQueue();
    EnQueue(Q, u);
    while (!IsEmptyQueue(Q))
    {
        u = DeQueue(Q);
        printf("vertex u: %d", u); //
        Visited[s] = 1;
        /*
            如果用邻接矩阵表示图,那么查找u的未被访问邻接顶点的条件是 if(Visited[v] && G->Adj[u][v])
        */
        for (each unvisited adjacent node v of u) //伪代码
        {
            EnQueue(Q, v);
        }
    }
}

void BFSTraversal(struct Graph *G)
{
    for (int i = 0; i < G->V; i++)
        Visited[i] = 0;
    //如果图有不止一个连通分量,那么这个循环是必要的
    for (int i = 0; i < G->V; i++)
        if (!Visited[i])
            BFS(G, i);
}

//拓扑排序
void TopologicalSort(struct Graph *G)
{
    struct Queue *Q;
    int counter;
    int v, w;
    Q = CreateQueue();
    counter = 0;
    for (v = 0; v < G->V; v++)
        if (indegree[v] == 0)
            EnQueue(Q, v);
    while (!IsEmptyQueue(Q))
    {
        v = DeQueue(Q);
        topologicalOrder[v] = ++counter;
        for
            each w adjacent to v //伪代码
                if (--indegree[w] == 0)
                    EnQueue(Q, w);
    }
    if (counter != G->V)
        print("Graph has cycle");
    DeleteQueue(Q);
}

//无权图的最短路径
void UnweightedShortestPath(struct Graph *G, int s)
{
    struct Queue *Q = CreateQueue();
    int v, w;
    EnQueue(Q, s);
    for (int i = 0; i < G->V; i++)
        Distance[i] = -1;
    Distance[s] = 0;
    while (!IsEmptyQueue(Q))
    {
        v = DeQueue(Q);
        for (each w adjacent to v)
            if (Distance[w] == -1) //每个顶点最多判断一次
            {
                Distance[w] = Distance[v] + 1;
                Path[w] = v;
                EnQueue(Q, w); //每个顶点最多入列一次
            }
    }
    DeleteQueue(Q);
}

//有权图的最短路径 Dijkstra's
void Dijkstra(struct Graph *G, int s)
{
    struct PriorityQueue *PQ = CreatePriorityQueue();
    int v, w;
    EnQueue(PQ, s);
    for (int i = 0; i < G->V; i++)
        Distance[i] = -1;
    Distance[s] = 0;
    while (!IsEmptyQueue(PQ))
    {
        v = DeleteMin(PQ);
        for (each w adjacent to v)
        {
            compute new distance d = Distance[v] + weight[v][w];
            if (Distance[w] == -1)
            {
                Distance[w] = new distance d;
                //将w的优先级更新为d
                Path[w] = v;
            }
        }
    }
}

//负权重边的最短路径 Bellman-Ford算法

void BellmanFordAlgorithm(struct Graph *G, int s)
{
    struct Queue *PQ = CreateQueue();
    int v, w;
    EnQueue(PQ, s);
    for (int i = 0; i < G->V; i++)
        Distance[i] = -1;
    Distance[s] = 0;
    while (!IsEmptyQueue(Q))
    {
        v = DeQueuek(PQ);
        for (all adjacent vertices w of v)
        { //对顶点的所有邻接结点w
            compute new distance d = Distance[v] + weight[v][w];
            if (old distance to w > new distance d)
            { //如果到v顶点w的旧距离大于新距离d
                Distance[v] = (到顶点v的距离) + weight[v][w];
                Path[w] = v;
                if (w is there in queue) //如果w在队列中
                    EnQueue(Q, w);
            }
        }
    }
}

//最小生成树, 图的生成树是图的一个子图,包含图的所有顶点 且是一棵树
//无向图的最小生成树算法
//Prim 算法 大致与Dijkstra算法相同 ,距离定义和更新语句会不同

void Prim(struct Graph *G, int s)
{
    struct PriorityQueue *PQ = CreatePriorityQueue();
    int v, w;
    EnQueue(PQ, s);
    for (int i = 0; i < G->V; i++)
        Distance[i] = -1;
    Distance[s] = 0;
    while (!IsEmptyQueue(PQ))
    {
        v = DeleteMin(PQ);
        for (each w adjacent to v)
        {
            compute new distance d = Distance[v] + weight[v][w];
            if (Distance[w] == -1)
            {
                Distance[w] = weight[v][w];
                //将顶点w以d为优先级插入优先队列中
                Path[w] = v;
            }
            if (Distance[w] > new distance d)
            {
                Distance[w] = weight[v][w];
                将顶点w的优先级更新的d;
                Path[w] = v;
            }
        }
    }
}

//Kruskal算法,使用不相交集实现:利用UNION操作和FIND操作
//优先队列实现:在优先队列维持权重 最坏运行O(|E|log|E|)
void Kruskal(struct Graph *G)
{
    S = Φ; //最后s将包含最小生成树的所有边
    for (int v = 0; v < G->V; v++)
        MakeSet(v);
    //按权重w递增的顺序对边集E进行排序
        for
            each edge(u, v) in E
            { //从有序列表
                if (FIND(u) ≠ FIND(v))
                {
                    S = S ∪ {(u, v)};
                    UNION(u, v);
                }
            }
        return S;
}

//Q10 给出一个算法用于检测在给定图G种是否存在从源点s到目的点d的简单路径,假设图G用邻接矩阵表示
struct Graph
{
    int V;
    int E;
    int **adjMatrix;
};

//对每个顶点调用DFS的算法并检查当前顶点是否与目标顶点相同,相同则返回1,否则就对邻接顶点调用DFS(未被访问的顶点)

void HasSimplePath(struct Graph *G, int s, int d)
{
    int t;
    Visited[s] = 1;
    for (t = 0; t < G->V; t++)
    {
        if (G->adjMatrix[s][t] && !Visited[t])
            if (DFS(G, t, d))
                return 1;
    }
    return 0;
}

//Q11 从一个顶点开始作为出发点调用DFS,在每个连通分量中首次调用DFS前,增加连通分量的计数,实现逻辑
void CountSimplePaths(struct Graph *G, int s, int d)
{
    int t;
    Visited[s] = 1;
    if (s == d)
    {
        count++;
        Visited[s] = 0;
        return;
    }
    for (t = 0; t < G->V; t++)
    {
        if (G->adjMatrix[s][t] && !Visited[t])
        {
            DFS(G, t, d);
            Visited[t] = 0;
        }
    }
}

//Q12 所有顶点对最短路径问题:给定图中每对顶点之间的最短距离,假设给定图没有负权重边
//调用n次Dijkstra算法
//Q13 如果有负权重的边?
//Floyd-Warshall算法 属于动态规划例子

//Q14 DFS应用:切割顶点(cut vertex)或关节点(articulation point)
//* 如果删除一个连通无向图中的任何一个顶点, 该图仍然是连统的,那该图是双连通的(bi-connected)
int adjMatrix[256][256];
int dfsnum[256], num = 0, low[256];
void CutVertices(int u)
{
    low[u] = dfsnum[u] = num++;
    for (int v = 0; v < 256; ++v)
    {
        if (adjMatrix[u][v] && dfsnum[v] == -1)
        {
            CutVertices(v);
            if (low[v] > dfsnum[u])
                printf("Cut Vertex: %d", u);
            low[u] = __min(low[u], low[v]);
        }
        else //(u, v)是反向边
        {
            low[u] = __min(low[u], dfsnum[v]);
        }
    }
}

//Q16 DFS应用:切割桥/边(cut bridge/edge)
int dfsnum[256], num = 0, low[256];
void Bridges(struct Graph *G, int u)
{
    low[u] = dfsnum[u] = num++;
    for (int v = 0; v < G->V; ++v)
    {
        if (G->adjMatrix[u][v] && dfsnum[v] == -1)
        {
            Bridges(v);
            if (low[v] > dfsnum[u])
                printf("Cut Bridge: %d %d", u, v); //作为一个桥
            low[u] = __min(low[u], low[v]);
        }
        else
        { //(u, v)是反向边
            low[u] = __min(low[u], dfsnum[v]);
        }
    }
}

//Q18 DFS影用: 查找强连通分量 ...这段已经不知道作者在写什么了 大概是伪代码混合java
int adjMatrix[256][256], table[256];
vector<int> st;
int counter = 0;
//此表包含DFS搜索编号
int dfsnum[256], num = 0, low[256];
void StronglyConnectedComponents(int u)
{
    low[u] = dfsnum[u] = num++;
    Push(st, u);
    for (int v = 0; v < 256; ++v)
    {
        if (graph[u][v] && table[v] == -1)
        {
            if (dfsnum[v] == -1)
                StronglyConnectedComponents(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == dfsnum[u])
    {
        while (table[u] != counter)
        {
            table[st.back()] = counter;
            Push(st);
        }
    }
    ++counter;
}

//Q19 统计用邻接矩阵表示的图G的连接分量的数量
//DFS增加一个额外的计数器
//Visited[]是一个全局数组
int Visited[G->V];
void DFS(struct Graph *G, int u)
{
    Visited[u] = 1;
    for (int v = 0; v < G->V; v++)
    {
        /*
            例如 如果邻接矩阵表视图 ,那么查找顶点u的尚未被访问的邻接顶点的条件是 if(!Visited[v]&&G->Adj[u][v])
        */
       for
           each unvisited adjacent node v of u
           {
               DFS(G, v);
           }
    }
}

void DFSTraversal(struct Graph *G)
{
    int count = 0;
    for (int i = 0; i < G->V; i++)
        Visited[i] = 0;
    //如果图具有不止一个连通分量,那么这个循环是需要的
    for (int i = 0; i < G->V; i++)
        if (!Visited[i])
        {
            DFS(G, i);
            count++;
        }
}

//Q20 使用BFS解求解Q19
//BFS加计数器解决

void BFS(struct Graph *G, int u)
{
    int v;
    Queue Q = CreateQueue();
    EnQueue(Q, u);
    while (!IsEmptyQueue(Q))
    {
        u = DeQueue(Q);
        Process u; //例如打印
        Visited[s] = 1;

        /*
            例如 如果邻接矩阵表视图 ,那么查找顶点u的尚未被访问的邻接顶点的条件是 if(!Visited[v]&&G->Adj[u][v])
        */
       for
           each unvisited adjacent node v of u
           {
               EnQueue(Q, v);
           }
    }
}

void BFSTraversal(struct Graph *G)
{
    for (int i = 0; i < G->V; i++)
        Visited[i] = 0;
    //如果图具有不止一个连通分量,那么这个循环是需要的
    for (int i = 0; i < G->V; i++)
        if (!Visited[i])
        {
            BFS(G, i);
        }
}
//时间复杂度 使用邻接表 O(|E|+|V|) 使用邻接矩阵O(|V|²)

//Q21假设G(V,E)是一个无向图, 请给出一个时间复杂度为O(|E|)的查找生成树的算法, 不一定是最小生成树
//标记已经添加到集合S中的顶点使得循环的测试可以在常量级时间内完成,如果与边关联的两个顶点都已被标记,那么该边将引入一个环
S = {}; //假设S是个集合
for
    each edge e ∈E
    { //对E中的每条边
        if (将e加入S不会构成回路)
        {
            add e to S;
            mark e;
        }
    }

//Q22 求解21其他方法
//使用BFS 找到BFS树
//Q23 如何判断无向图是否存在回路?
//DFS不产生反向边,执行DFS,如果存在反向边则图存在环

//Q24 DAG(有向无环图)中判断是否存在回路
//图的回路检测比起树来说,顶点可以有多个父节点,书中用于检测回路的方法在DFS标记遇到结点,再次遇到已标记结点则说明存在回路,但不适用于图
int DetectCycle(struct Graph *G)
{
    for (int i = 0; i < G->V; i++)
    {
        Visited[s] = 0;
        Predecessor[i] = 0;
    }
    for (int i = 0; i < G->V; i++)
    {
        if (!Visited[i] && HasSycle(G, i))
            return 1;
    }
    return false;
}

int HasCycle(struct Graph *G, int u)
{
    Visited[u] = 1;
    for (int i = 0; i < G->V; i++)
    {
        if (G->Adj[s][i])
        {
            if (Predecessor[i] != u && Visited[i])
                return 1;
            else
            {
                Predecessor[i] = u;
                return HasCycle(G, i);
            }
        }
    }
    return 0;
}

//Q25 给定一个有向无环图 求解它的深度的算法
//层次遍历 使用特殊符号表示层次结束
int DepthInDAG(struct Graph *G)
{
    struct Queue *Q;
    int counter;
    int v, w;
    Q = CreateQueue();
    counter = 0;
    for (v = 0; v < G->V; v++)
    {
        if (indegree[v] == 0)
            EnQueue(Q, v);
    }
    EnQueue(Q, '$');
    while (!IsEmptyQueue(Q))
    {
        v = DeQueue(Q);
        if (v == '$')
        {
            counter++;
            if (!IsEmptyQueue(Q))
                EnQueue(Q, '$');
        }
        for each w adjacent to v if (--indegree[w] == 0){
                EnQueue(Q, w);
            }
    }
    DeleteQueue(Q);
    return counter;
}

//Q27 唯一的拓扑排序  当且仅当拓扑排序中每对连续顶点之间存在有向边(该图具有哈密尔顿路径)

//Q35 DAG中的哈密尔顿路径:设计一个线性时间算法判断是否存在一条路斤访问且只访问一次图中的每个顶点
//NP完整的问题参考chapter20,使用近似算法(能解决但不总市最优解)
//近似算法(approximation algorithm) 计算一个拓扑排序, 并检查拓扑排序中的每个连续的定点对之间是否存在边
//从s开始尝试所有邻接顶点,确保不会同一个顶点访问2次
bool seenTable[32];
void HamiltonianPath(struct Graph *G, int u) {
    if(u==t)
        /*检查我们已经看到所有顶点*/
    else {
        for(int v=0; v<n; v++)
            if(!seenTable[v] && G->Adj[u][v]) {
                seenTable[v] = true;
                HamiltonianPath(v);
                seenTable[v] = false;
            }
    }
}

//Q36 给定具有n个顶点的图G 可以构造多少棵树
// Arthur Cayley 算法 n^(n-2)个

//Q40 反转图 给出返回有向图的反转图的算法

Graph ReverseTheDirectedGraph(struct Graph *G) {
    //创建新图ReversedGraph 并且假设其将包含反转图信息
    //反转图包含与原图相同数量的顶和边
    //对于图G的每个顶点 {
        //对于每个邻接到v的顶点w {
            //将从w到v的边添加到ReversedGraph中
            //意味着我们仅仅需要反转邻接矩阵中的位
        //}
    //}
    return ReversedGraph;
}