/* 边双连通分量缩点 tarjan算法 14.11.12 */

#include <cstdio>
#include <algorithm>
using namespace std;

struct adlist
{
    int u[5010],v[20010],p[20010],m;
    adlist():m(2) {}
    void insert(int x,int y)
    {v[m]=y; p[m]=u[x]; u[x]=m; m++;}
}g;

int n,m,i,dfn[5010],low[5010],col[5010],deg[5010],idx,cnt,leaf;
bool bri[20010],vis[20010];

void tarjan(int x)
{
    int i,y; dfn[x]=low[x]=++idx;
    for (i=g.u[x];i;i=g.p[i])
    {
        y=g.v[i];
        if (vis[i]) continue;
        vis[i]=vis[i^1]=1;
        if (!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if (dfn[x]<low[y])
                bri[i]=bri[i^1]=1;
        }
        else low[x]=min(low[x],dfn[y]);
    }
}

void floodfill(int x)
{
    int i; col[x]=cnt;
    for (i=g.u[x];i;i=g.p[i])
        if (!col[g.v[i]]&&!bri[i])
            floodfill(g.v[i]);
}

void makeTree(int x)
{
    for (int i=g.u[x];i;i=g.p[i])
        if (bri[i])
        {
            ++deg[col[x]];
            ++deg[col[g.v[i]]];
        }
}

int main()
{
    scanf("%d%d",&n,&m);
    while (m--)
    {
        int x,y; scanf("%d%d",&x,&y);
        g.insert(x,y); g.insert(y,x);
    }
    tarjan(1);
    for (i=1;i<=n;++i)
        if (!col[i]) {++cnt; floodfill(i);}
    for (i=1;i<=n;++i) makeTree(i);
    for (i=1;i<=cnt;++i) leaf+=(deg[i]==2);
    if (leaf>1) printf("%d\n",(leaf+1)>>1);
    else printf("0\n");
    return 0;
}

