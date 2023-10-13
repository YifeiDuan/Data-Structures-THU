#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
struct data
{
    int x,y;
}a[N],b[N];
int root,tot;
int s[N][2],fa[N],key[N];
long long ans;
inline int read()
{
    int data=0; char ch=0;
    while(ch<'0' || ch>'9') ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data;
}
inline bool cmp(data a,data b)
{
    return a.y>b.y;
}
inline bool pd(int x)
{
    return x==s[fa[x]][1];
}
inline void rotate(int x)
{
    int y=fa[x],w=pd(x);
    if(fa[x]=fa[y]) s[fa[y]][pd(y)]=x;
    fa[s[y][w]=s[x][w^1]]=y;
    s[fa[y]=x][w^1]=y;
}
inline void splay(int x)
{
    for(int y;y=fa[x];rotate(x))
        if(fa[y]) rotate(pd(x)==pd(y)?y:x);
    root=x;
}
inline int search(int x,int v)
{
    while(key[x]!=v)
        if(v<key[x])
        {
            if(!s[x][0]) break;
            x=s[x][0];
        }else
        {
            if(!s[x][1]) break;
            x=s[x][1];
        }
    return x;
}
inline void ins(int &x,int y,int v)
{
    if(!x)
    {
        x=++tot;
        key[x]=v;
        fa[x]=y;
        return;
    }
    ins(s[x][key[x]<=v],x,v);
}
inline void del(int v)
{
    int k=search(root,v);
    splay(k);
    if(!s[k][0])
    {
        fa[root=s[k][1]]=0;
        key[k]=s[k][1]=0;
        return;
    }
    fa[s[k][0]]=0;
    splay(search(s[k][0],1e9));
    if(s[root][1]=s[k][1]) fa[s[root][1]]=root;
    key[k]=s[k][0]=s[k][1]=0;
}
inline int find(int v)
{
    if(!root) return 0;
    int x=root;
    while(true)
    {
        if(key[x]<v)
        {
            if(!s[x][1]) return 0;
            x=s[x][1];
            continue;
        }
        if(s[x][0])
        {
            int y=s[x][0];
            while(key[y]<v && s[y][1]) y=s[y][1];
            if(key[y]>=v)
            {
                x=y;
                continue;
            }
        }
        return x;
    }
}
int main()
{
    int n=read(),m=read();
    for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
    for(int i=1;i<=m;i++) b[i].x=read(),b[i].y=read();
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+m,cmp);
    for(int i=1,j=1;i<=n;i++)
    {
        while(j<=m && b[j].y>=a[i].y)
        {
            ins(root,0,b[j++].x);
            splay(tot);
        }
        int k=find(a[i].x);
        if(!k)
        {
            printf("-1");
            return 0;
        }
        ans+=key[k];
        del(key[k]);
    }
    printf("%lld",ans);
    return 0;
}
