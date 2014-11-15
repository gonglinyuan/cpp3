/* 边双连通分量缩点 tarjan算法 14.11.15 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct adlist
{
	int u[100010],v[400010],p[400010],m;
	bool f[400010],c[400010];
	void cls() {m=1; memset(u,0,sizeof(u));}
	void insert(int x,int y)
	{++m; v[m]=y; p[m]=u[x]; f[m]=c[m]=0; u[x]=m;}
}g,T;

int n,m,i,q,idx,cnt,ans,tot,dfn[100010],low[100010],col[100010],dep[100010],fa[100010],st[100010];

struct djset
{
	int f[100010];
	void init() {for (int i=1;i<=cnt;++i) f[i]=i;}
	int getf(int x)
	{if (f[x]!=x) f[x]=getf(f[x]); return f[x];}
}S;

void getbicon(int x)
{
	int i,y; dfn[x]=low[x]=++idx;
	for (i=g.u[x];i;i=g.p[i])
	{
		if (g.f[i]) continue;
		g.f[i]=g.f[i^1]=1; y=g.v[i];
		if (!dfn[y])
		{
			getbicon(y);
			low[x]=min(low[x],low[y]);
			g.c[i]=g.c[i^1]=(dfn[x]<low[y]);
		}
		else low[x]=min(low[x],dfn[y]);
	}
}

void floodfill(int x)
{
	int i; col[x]=cnt;
	for (i=g.u[x];i;i=g.p[i])
		if (!g.c[i]&&!col[g.v[i]])
			floodfill(g.v[i]);
}

void maketree(int x)
{
	int i;
	for (i=g.u[x];i;i=g.p[i])
		if (g.c[i])
			T.insert(col[x],col[g.v[i]]);
}

void treeinit(int x)
{
	for (int i=T.u[x];i;i=T.p[i])
		if (!dep[T.v[i]])
		{
			fa[T.v[i]]=x;
			dep[T.v[i]]=dep[x]+1;
			treeinit(T.v[i]);
		}
}

int main()
{
	while (scanf("%d%d",&n,&m),n||m)
	{
		printf("Case %d:\n",++tot);
		g.cls(); T.cls();
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(col,0,sizeof(col));
		memset(dep,0,sizeof(dep));
		idx=cnt=0;
		while (m--)
		{
			int x,y; scanf("%d%d",&x,&y);
			g.insert(x,y); g.insert(y,x);
		}
		getbicon(1);
		for (i=1;i<=n;++i)
			if (!col[i])
			{++cnt; floodfill(i);}
		for (i=1;i<=n;++i) maketree(i);
		dep[1]=1; treeinit(1); S.init(); ans=cnt-1;
		scanf("%d",&q);
		while (q--)
		{
			int x,y,z; scanf("%d%d",&x,&y);
			x=col[x]; y=col[y]; st[0]=0;
			while (dep[x]>dep[y])
			{st[++st[0]]=S.getf(x); x=fa[x];}
			while (dep[x]<dep[y])
			{st[++st[0]]=S.getf(y); y=fa[y];}
			while (x!=y)
			{
				st[++st[0]]=S.getf(x);
				st[++st[0]]=S.getf(y);
				x=fa[x]; y=fa[y];
			}
			z=S.getf(x); st[++st[0]]=S.getf(z);
			sort(st+1,st+st[0]+1);
			st[0]=unique(st+1,st+st[0]+1)-st-1;
			ans-=st[0]-1; printf("%d\n",ans);
			for (i=1;i<=st[0];++i) S.f[st[i]]=z;
		}
		putchar('\n');
	}
	return 0;
}
