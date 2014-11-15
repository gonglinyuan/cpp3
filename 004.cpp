/* 点双连通分量缩点+BFS tarjan算法 14.11.14 */

#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

const int dx[]={1,0,0,-1};
const int dy[]={0,-1,1,0};

struct point {int x,y;};
struct edge {int x1,y1,x2,y2;};
struct status {int x,y,z;}q[40010];

int n,m,i,j,k,mx,my,px,py,kx,ky,l,r,cnt,idx,top,flag,d[110][110][4],dfn[110][110],low[110][110];
char s[110];
bool a[110][110],cut[110][110],vis[110][110];
edge st[20010];
set<int> col[110][110];
set<int>::iterator it;

void tarjan(int x,int y,int fx,int fy)
{
    int xx,yy,k;
    dfn[x][y]=low[x][y]=++idx;
    for (k=0;k<4;++k)
    {
        xx=x+dx[k]; yy=y+dy[k];
        if (!a[xx][yy]) continue;
        if (xx==fx&&yy==fy) continue;
        if (dfn[xx][yy]>=dfn[x][y]) continue;
        if (!dfn[xx][yy])
        {
            ++top; st[top]=(edge){x,y,xx,yy};
            if (x==mx&&y==my) ++flag;
            tarjan(xx,yy,x,y);
            low[x][y]=min(low[x][y],low[xx][yy]);
            if (dfn[x][y]<=low[xx][yy])
            {
                cut[x][y]=1; ++cnt; int x1,x2,y1,y2;
                do
                {
                    x1=st[top].x1; y1=st[top].y1;
                    x2=st[top].x2; y2=st[top].y2;
                    --top;
                    col[x1][y1].insert(cnt);
                    col[x2][y2].insert(cnt);
                }
                while (!(x1==x&&y1==y));
            }
        }
        else low[x][y]=min(low[x][y],dfn[xx][yy]);
    }
}

void floodfill(int x,int y)
{
    vis[x][y]=1; int k;
    for (k=0;k<4;++k)
    {
        if (!a[x+dx[k]][y+dy[k]]) continue;
        if (vis[x+dx[k]][y+dy[k]]) continue;
        if (x+dx[k]==px&&y+dy[k]==py) continue;
        floodfill(x+dx[k],y+dy[k]);
    }
}

bool check(set<int> &S1,set<int> &S2)
{
    for (it=S1.begin();it!=S1.end();++it)
        if (S2.find(*it)!=S2.end()) return true;
    return false;
}

int main()
{
    freopen("mag.in","r",stdin);
    freopen("mag.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;++i)
    {
        scanf("%s",s+1);
        for (j=1;j<=m;++j)
        { 
            if (s[j]=='S') a[i][j]=0;
            else
            {
                a[i][j]=1;
                if (s[j]=='M') mx=i,my=j;
                else if (s[j]=='P') px=i,py=j;
                else if (s[j]=='K') kx=i,ky=j;
            }
        }
    }
    tarjan(mx,my,0,0); cut[mx][my]=(flag>1);
    memset(d,-1,sizeof(d));
    floodfill(mx,my);
    for (k=0;k<4;++k)
        if (vis[px+dx[k]][py+dy[k]])
        {
            d[px][py][k]=0;
            q[++r]=(status){px,py,k};
        }
    while (l<r)
    {
        int x0,y0,z0,x,y,z,xx,yy; ++l;
        x0=q[l].x; y0=q[l].y; z0=q[l].z;
        z=3-z0; x=x0+dx[z]; y=y0+dy[z];
        if (!a[x][y]) continue;
        for (k=0;k<4;++k)
        {
            xx=x+dx[k]; yy=y+dy[k];
            if (!a[xx][yy]) continue;
            if (!cut[x][y]||check(col[xx][yy],col[x0][y0]))
            {
                if (d[x][y][k]>=0) continue;
                if (x==kx&&y==ky)
                {
                    printf("%d\n",d[x0][y0][z0]+1);
                    fclose(stdin); fclose(stdout);
                    return 0;
                }
                d[x][y][k]=d[x0][y0][z0]+1;
                q[++r]=(status){x,y,k};
            }
        }
    }
    printf("NIE\n");
    fclose(stdin); fclose(stdout);
    return 0;
}
