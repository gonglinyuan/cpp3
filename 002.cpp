/* 求无向图割点 tarjan算法 14.11.11*/

#include <cstdio>
#include <algorithm>
using namespace std;

struct adlist
{
    int u[110],v[20010],p[20010],m;
    void insert(int x,int y)
    {++m; v[m]=y; p[m]=u[x]; u[x]=m;}
}g;

int n,x,y,i,tot,ans,fa[110],dfn[110],low[110],idx;
bool cut[110];

void tarjan(int x)
{
    //printf("tarjan(%d)\n",x);
    int i,y; dfn[x]=low[x]=++idx;
    for (i=g.u[x];i;i=g.p[i])
    {
        y=g.v[i];
        if (!dfn[y])
        {
            fa[y]=x; tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if (fa[x]!=y)
            low[x]=min(low[x],dfn[y]);
    }
    if (fa[x]>1&&dfn[fa[x]]<=low[x]) cut[fa[x]]=1; 
}

int main()
{
    freopen("gd.in","r",stdin);
    freopen("gd.out","w",stdout);
    scanf("%d",&n);
    while (scanf("%d%d",&x,&y)==2)
    {g.insert(x,y); g.insert(y,x);}
    tarjan(1);
    //for (i=1;i<=n;++i)
    //    printf("dfn[%d]=%d low[%d]=%d fa[%d]=%d cut[%d]=%d\n",i,dfn[i],i,low[i],i,fa[i],i,cut[i]);
    for (i=1;i<=n;++i)
        if (fa[i]==1) ++tot;
    if (tot>1) cut[1]=1;
    for (i=1;i<=n;++i) ans+=cut[i];
    printf("%d\n",ans);
    for (i=1;i<=n;++i)
        if (cut[i])
            printf("%d\n",i);
    fclose(stdin); fclose(stdout);
    return 0;
}

