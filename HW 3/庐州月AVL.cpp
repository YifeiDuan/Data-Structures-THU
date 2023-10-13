#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct lz //��¼��/ʯ�ĵĽṹ�� 
{
	int x;
	int y;
};

long long int totalCost;

int cmpfunc (const void * a, const void * b);

template <typename T> struct BinNode { //�������ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
   T data; //��ֵ
   BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //���ڵ㼰���Һ���
   int height; //�߶ȣ�ͨ�ã�
   int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
   RBColor color; //��ɫ���������
// ���캯��
   BinNode() :
      parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { }
   BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
             int h = 0, int l = 1, RBColor c = RB_RED ) :
      data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { }
// �����ӿ�
   int size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
   BinNodePosi(T) insertAsLC ( T const& ); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
   BinNodePosi(T) insertAsRC ( T const& ); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
   BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
   template <typename VST> void travLevel ( VST& ); //������α���
   template <typename VST> void travPre ( VST& ); //�����������
   template <typename VST> void travIn ( VST& ); //�����������
   template <typename VST> void travPost ( VST& ); //�����������
// �Ƚ������е�����������һ���������в��䣩
   bool operator< ( BinNode const& bn ) { return data < bn.data; } //С��
   bool operator== ( BinNode const& bn ) { return data == bn.data; } //����
   /*DSA*/
   /*DSA*/BinNodePosi(T) zig(); //˳ʱ����ת
   /*DSA*/BinNodePosi(T) zag(); //��ʱ����ת
   /*DSA*/BinNodePosi(T) balance(); //��ȫƽ�⻯
   /*DSA*/BinNodePosi(T) imitate( const BinNodePosi(T) );
};

template <typename T> class BinTree { //������ģ����
protected:
   int _size; BinNodePosi(T) _root; //��ģ�����ڵ�
   virtual int updateHeight ( BinNodePosi(T) x ); //���½ڵ�x�ĸ߶�
   void updateHeightAbove ( BinNodePosi(T) x ); //���½ڵ�x�������ȵĸ߶�
public:
   BinTree() : _size ( 0 ), _root ( NULL ) { } //���캯��
   ~BinTree() { if ( 0 < _size ) remove ( _root ); } //��������
   int size() const { return _size; } //��ģ
   bool empty() const { return !_root; } //�п�
   BinNodePosi(T) root() const { return _root; } //����
   BinNodePosi(T) insertAsRoot ( T const& e ); //������ڵ�
   BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e��Ϊx�����ӣ�ԭ�ޣ�����
   BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
   BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &T ); //T��Ϊx����������
   BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &T ); //T��Ϊx����������
   int remove ( BinNodePosi(T) x ); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
   BinTree<T>* secede ( BinNodePosi(T) x ); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
   template <typename VST> //������
   void travLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit ); } //��α���
   template <typename VST> //������
   void travPre ( VST& visit ) { if ( _root ) _root->travPre ( visit ); } //�������
   template <typename VST> //������
   void travIn ( VST& visit ) { if ( _root ) _root->travIn ( visit ); } //�������
   template <typename VST> //������
   void travPost ( VST& visit ) { if ( _root ) _root->travPost ( visit ); } //�������
   bool operator< ( BinTree<T> const& t ) //�Ƚ������������в��䣩
   { return _root && t._root && lt ( _root, t._root ); }
   bool operator== ( BinTree<T> const& t ) //�е���
   { return _root && t._root && ( _root == t._root ); }
}; 

template <typename T> class BST : public BinTree<T> { //��BinTree����BSTģ����
protected:
   BinNodePosi(T) _hot; //�����С��ڵ�ĸ���
   BinNodePosi(T) connect34 ( //���ա�3 + 4���ṹ������3���ڵ㼰�Ŀ�����
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) );
   BinNodePosi(T) rotateAt ( BinNodePosi(T) x ); //��x���丸�ס��游��ͳһ��ת����
public: //�����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д
   virtual BinNodePosi(T) & search ( const T& e ); //����
   virtual BinNodePosi(T) insert ( const T& e ); //����
   virtual bool remove ( const T& e ); //ɾ��
   /*DSA*/
   /*DSA*/void stretchToLPath() { stretchByZag ( _root ); } //����zag��ת��ת��Ϊ������
   /*DSA*/void stretchToRPath() { stretchByZig ( _root ); } //����zig��ת��ת��Ϊ������
   /*DSA*/void stretch();
};

template <typename T> BinNodePosi(T) BST<T>::connect34 (
   BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
   BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
   //*DSA*/print(a); print(b); print(c); printf("\n");
   a->lc = T0; if ( T0 ) T0->parent = a;
   a->rc = T1; if ( T1 ) T1->parent = a; updateHeight ( a );
   c->lc = T2; if ( T2 ) T2->parent = c;
   c->rc = T3; if ( T3 ) T3->parent = c; updateHeight ( c );
   b->lc = a; a->parent = b;
   b->rc = c; c->parent = b; updateHeight ( b );
   return b; //�������µĸ��ڵ�
}

template <typename T> BinNodePosi(T) BST<T>::rotateAt ( BinNodePosi(T) v ) { //vΪ�ǿ��ﱲ�ڵ�
   /*DSA*/if ( !v ) { printf ( "\a\nFail to rotate a null node\n" ); exit ( -1 ); }
   BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //��v��p��g���λ�÷��������
   if ( IsLChild ( *p ) ) /* zig */
      if ( IsLChild ( *v ) ) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
         p->parent = g->parent; //��������
         return connect34 ( v, p, g, v->lc, v->rc, p->rc, g->rc );
      } else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
         v->parent = g->parent; //��������
         return connect34 ( p, v, g, p->lc, v->lc, v->rc, g->rc );
      }
   else  /* zag */
      if ( IsRChild ( *v ) ) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
         p->parent = g->parent; //��������
         return connect34 ( g, p, v, g->lc, p->lc, v->lc, v->rc );
      } else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
         v->parent = g->parent; //��������
         return connect34 ( g, v, p, g->lc, v->lc, v->rc, p->rc );
      }
}

template <typename T> BinNodePosi(T) & BST<T>::search ( const T & e ) { //��BST�в��ҹؼ���e
   if ( !_root || e == _root->data ) { _hot = NULL; return _root; } //������v������
   for ( _hot = _root; ; ) { //�Զ�����
      BinNodePosi(T) & c = ( e < _hot->data ) ? _hot->lc : _hot->rc; //ȷ������
      if ( !c || e == c->data ) return c; _hot = c; //���з��أ���������һ��
   } //�������л�ʧ�ܣ�hot��ָ��v֮���ף���ΪNULL��
} //����Ŀ��ڵ�λ�õ����ã��Ա�������롢ɾ������

template <typename T> class AVL : public BST<T> { //��BST����AVL��ģ����
public:
   BinNodePosi(T) insert ( const T& e ); //���루��д��
   bool remove ( const T& e ); //ɾ������д��
// BST::search()������ӿڿ�ֱ������
};

template <typename T> BinNodePosi(T) AVL<T>::insert ( const T& e ) { //���ؼ���e����AVL����
   BinNodePosi(T) & x = search ( e ); if ( x ) return x; //ȷ��Ŀ��ڵ㲻����
   BinNodePosi(T) xx = x = new BinNode<T> ( e, _hot ); _size++; //�����½ڵ�x
// ��ʱ��x�ĸ���_hot�����ߣ������游�п���ʧ��
   for ( BinNodePosi(T) g = _hot; g; g = g->parent ) { //��x֮���������ϣ�������������g
      if ( !AvlBalanced ( *g ) ) { //һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������
         FromParentTo ( *g ) = rotateAt ( tallerChild ( tallerChild ( g ) ) ); //���½���ԭ��
         break; //g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����
      } else //����g��Ȼƽ�⣩��ֻ��򵥵�
         updateHeight ( g ); //������߶ȣ�ע�⣺����gδʧ�⣬�߶���������ӣ�
   } //����ֻ��һ�ε�����������������������ȫ���߶ȱ�Ȼ��ԭ
   return xx; //�����½ڵ�λ��
} //����e�Ƿ������ԭ���У�����AVL::insert(e)->data == e

template <typename T> bool AVL<T>::remove ( const T& e ) { //��AVL����ɾ���ؼ���e
   BinNodePosi(T) & x = search ( e ); if ( !x ) return false; //ȷ��Ŀ����ڣ�����_hot�����ã�
   removeAt ( x, _hot ); _size--; //�Ȱ�BST����ɾ��֮���˺�ԭ�ڵ�֮��_hot�������Ⱦ�����ʧ�⣩
   for ( BinNodePosi(T) g = _hot; g; g = g->parent ) { //��_hot�������ϣ�������������g
      if ( !AvlBalanced ( *g ) ) //һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������������
         g = FromParentTo ( *g ) = rotateAt ( tallerChild ( tallerChild ( g ) ) ); //ԭ����
      updateHeight ( g ); //��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ�
   } //��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
   return true; //ɾ���ɹ�
} //��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false

int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct lz *bridge = new struct lz[n];
	struct lz *material = new struct lz[m];
	
	int i , j;
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &bridge[i].x , &bridge[i].y);
	for(i = 0 ; i < m ; i ++)
	{
		if(i == m - 1) scanf("%d %d" , &material[i].x , &material[i].y);
		else  scanf("%d %d\n" , &material[i].x , &material[i].y);
	}
	
	qsort(bridge , n , sizeof(bridge[0]) , cmpfunc);
	qsort(material , m , sizeof(material[0]) , cmpfunc);
	
	totalCost = 0;
	
	int index;
	root = 0;
	p = 0;
	
	for(i = n - 1 , j = m - 1 ; i >= 0 ; i --)
	{
		while((j >= 0)&&(material[j].y >= bridge[i].y))
		{
			insert(root , 0 , material[j].x);
			splay(p);
			j --;
		}
		index = findM(bridge[i].x);
		totalCost += (long long int) key[index];
		remove(index);
	}
	
	printf("%lld" , totalCost);
}

int cmpfunc (const void * a, const void * b)
{
   return (*(lz *)a).y > (*(lz *)b).y ? 1 : -1;
}


