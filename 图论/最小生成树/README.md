关于图的几个概念定义：

- **连通图**：在无向图中，若任意两个顶点vi与vj都有路径相通，则称该无向图为连通图。
- **强连通图**：在有向图中，若任意两个顶点vi与vj都有路径相通，则称该有向图为强连通图。
- **连通网**：在连通图中，若图的边具有一定的意义，每一条边都对应着一个数，称为权；权代表着连接连个顶点的代价，称这种连通图叫做连通网。
- **生成树**：一个连通图的生成树是指一个连通子图，它含有图中全部n个顶点，但只有足以构成一棵树的n-1条边。一颗有n个顶点的生成树有且仅有n-1条边，如果生成树中再添加一条边，则必定成环。
- **最小生成树**：在连通网的所有生成树中，所有边的代价和最小的生成树，称为最小生成树。 
  ![这里写图片描述](http://img.blog.csdn.net/20160714130435508)



下面介绍两种求最小生成树算法



## Kruskal算法

此算法可以称为“加边法”，初始最小生成树边数为0，每迭代一次就选择一条满足条件的最小代价边，加入到最小生成树的边集合里。 

1. 把图中的所有边按代价从小到大排序； 
2. 把图中的n个顶点看成独立的n棵树组成的森林； 
3. 按权值从小到大选择边，所选的边连接的两个顶点ui,vi,应属于两颗不同的树，则成为最小生成树的一条边，并将这两颗树合并作为一颗树。 
4. 重复(3),直到所有顶点都在一颗树内或者有n-1条边为止。

![这里写图片描述](http://img.blog.csdn.net/20160714144315409)

```c++
struct Edge{
int from,to,val;
bool operator < (const Edge &x)const{
return val < x.val;
}
}e[MAXN * MAXN];

int fa[MAXN],len=0;
int find(int cur){
    return cur==fa[cur]?cur:fa[cur]=find(fa[cur]);  
}

int kruskal()
{
    for(int i=0;i<n;i++) fa[i] = i;
    sort(e,e+len);
    int ans=0;
    for(int i = 0;i < len;i++){
        int rootx=find(e[i].from);
        int rooty=find(e[i].to);
        if(rootx==rooty) continue;
        fa[rootx]=rooty;
        ans += e[i].val;    
    }
    return ans;
}
```



## Prim算法

Prim算法是一种产生最小生成树的算法。该算法于`1930`年由捷克数学家沃伊捷赫·亚尔尼克（英语：`Vojtěch Jarník`）发现；并在`1957`年由美国计算机科学家罗伯特·普里姆（英语：`Robert C. Prim`）独立发现；`1959`年，艾兹格·迪科斯彻再次发现了该算法。

`Prim`算法从任意一个顶点开始，每次选择一个与当前顶点集最近的一个顶点，并将两顶点之间的边加入到树中。`Prim`算法在找当前最近顶点时使用到了贪婪算法。

算法描述：

1. 在一个加权连通图中，顶点集合`V`，边集合为`E`
2. 任意选出一个点作为初始顶点,标记为`visit`,计算所有与之相连接的点的距离，选择距离最短的，标记`visit`.
3. 重复以下操作，直到所有点都被标记为`visit`：

在剩下的点中，计算与已标记`visit`点距离最小的点，标记`visit`,证明加入了最小生成树。

![这里写图片描述](http://img.blog.csdn.net/20160714161107576)

```c++
int prim()
{
int dis[MAXN];
bool vis[MAXN]={0};
for(int i=0;i<n;i++) dis[i] = INF;
int cur = 0;
dis[cur]=0;vis[cur]=true;
for(int i=0;i<n;i++)
{
     for(int j=0;j<n;j++)
        if(!vis[j] && dis[j] > map[cur][j])
             dis[j] = map[cur][j];

        int mini = INF;
        for(int j=0;j<n;j++)
            if(!vis[j] && dis[j] < mini)
                mini = dis[cur = j];
        vis[cur] = true;
    }
    int ans=0;
    for(int i=0;i<n;i++) ans+=dis[i];
    return ans;
}
```



 > 本文参考整理自：
 > 勿在浮沙筑高台http://blog.csdn.net/luoshixian099/article/details/51908175
 >
 > https://www.hrwhisper.me/algorithm-graph-dijkstra-spfa-bellmanford-prim-kruskal/#_MST