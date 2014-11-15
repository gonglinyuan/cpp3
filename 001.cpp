/* 强联通分量缩点 tarjan算法 14.11.10*/

#include <cstdio>
#include <algorithm>
using namespace std;

struct adlist
{
    int u[1010],v[10010],p[10010],m;
    void insert(int x,int y)
    {++m; v[m]=y; p[m]=u[x]; u[x]=m;}
}g;

int n,m,i,dfn[1010],low[1010],blo[1010],s[1010],sz[1010],idx,cnt;
bool in[1010];

void tarjan(int x)
{
    int i,y; dfn[x]=low[x]=++idx;
    s[++s[0]]=x; in[x]=1;
    for (i=g.u[x];i;i=g.p[i])
    {
        y=g.v[i];
        if (!dfn[y])
        {tarjan(y); low[x]=min(low[x],low[y]);}
        else if (in[y])
            low[x]=min(low[x],dfn[y]);
    }
    if (dfn[x]==low[x])
    {
        ++cnt;
        do
        {y=s[s[0]--]; in[y]=0; blo[y]=cnt; ++sz[cnt];}
        while (x!=y);
    }
}

int main()
{
    freopen("messagez.in","r",stdin);
    freopen("messagez.out","w",stdout);
    scanf("%d%d",&n,&m);
    while (m--)
    {int x,y; scanf("%d%d",&x,&y); g.insert(x,y);}
    for (i=1;i<=n;++i) if (!dfn[i]) tarjan(i);
    for (i=1;i<=n;++i)
        if (sz[blo[i]]>1) printf("T\n");
        else printf("F\n");
    fclose(stdin); fclose(stdout);
    return 0;
}

