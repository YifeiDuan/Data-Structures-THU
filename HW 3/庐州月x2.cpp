#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int N=500001;
struct data
{
    int x,y;
}a[500001],b[500001];
int root,tot;
int s[500001][2],fa[500001],key[500001];
long long ans;

int cmpfunc (const void * a, const void * b)
{
	return (*(data *)a).y < (*(data *)b).y ? 1 : -1;
}
bool pd(int x)
{
    return x==s[fa[x]][1];
}
void rotate(int x)
{
    int y=fa[x],w=pd(x);
    if(fa[x]=fa[y]) s[fa[y]][pd(y)]=x;
    fa[s[y][w]=s[x][w^1]]=y;
    s[fa[y]=x][w^1]=y;
}
void splay(int x)
{
    for(int y;y=fa[x];rotate(x))
        if(fa[y]) rotate(pd(x)==pd(y)?y:x);
    root=x;
}
int search(int x,int v)
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
void ins(int &x,int y,int v)
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
void del(int v)
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
    splay(search(s[k][0],N-1));
    if(s[root][1]=s[k][1]) fa[s[root][1]]=root;
    key[k]=s[k][0]=s[k][1]=0;
}
int find(int v)
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
    int n,m;
    scanf("%d %d\n",&n,&m);
    int i;
    for(i = 1 ; i <= n ; i ++) scanf("%d %d\n" , &a[i].x , &a[i].y);
	for(i = 1 ; i <= m ; i ++)
	{
		if(i == m) scanf("%d %d" , &b[i].x , &b[i].y);
		else  scanf("%d %d\n" , &b[i].x , &b[i].y);
	}
	struct data *pa = &a[1];
	struct data *pb = &b[1];
    qsort(pa , n , sizeof(a[1]) , cmpfunc);
    qsort(pb , m , sizeof(b[1]) , cmpfunc);
    
	root=0;
	tot=0;
    for(int s=1,t=1;s<=n;s++)
    {
        while(t<=m && b[t].y>=a[s].y)
        {
            ins(root,0,b[t++].x);
            splay(tot);
        }
        int k=find(a[s].x);
        
        ans+=key[k];
        del(key[k]);
    }
    printf("%lld",ans);
    return 0;
}
