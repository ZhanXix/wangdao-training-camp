#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED		0		//红色
#define BLACK	1		//黑色

#define GrandFather pNew->parent->parent

//红黑树结点定义
typedef struct red_black_tree_node
{
	int num;
	bool color;
	struct red_black_tree_node* parent, * lchild, * rchild;
}RBtree_node_t, * pRBtree_node_t;

//左旋
void Left_Rotate_RBtree_Node(pRBtree_node_t p, pRBtree_node_t c, pRBtree_node_t* root)
{
	if (c != p->rchild)
	{
		printf("Left_Rotate_RBtree_Node ERROR");
		return;
	}
	if (p->parent)
	{
		c->parent = p->parent;
		if (p->parent->lchild == p)
		{
			p->parent->lchild = c;
		}
		else
		{
			p->parent->rchild = c;
		}
	}
	else
	{
		c->parent = NULL;
		*root = c;
	}
	p->rchild = c->lchild;
	if (p->rchild)
	{
		p->rchild->parent = p;
	}
	c->lchild = p;
	p->parent = c;
}

//右旋
void Right_Rotate_RBtree_Node(pRBtree_node_t p, pRBtree_node_t c, pRBtree_node_t* root)
{
	if (c != p->lchild)
	{
		printf("Right_Rotate_RBtree_Node ERROR");
		return;
	}
	if (p->parent)
	{
		c->parent = p->parent;
		if (p->parent->lchild == p)
		{
			p->parent->lchild = c;
		}
		else
		{
			p->parent->rchild = c;
		}
	}
	else
	{
		c->parent = NULL;
		*root = c;
	}
	p->lchild = c->rchild;
	if (p->lchild)
	{
		p->lchild->parent = p;
	}
	c->rchild = p;
	p->parent = c;
}

//插入一个新结点
void Insert_RBtree_Node(pRBtree_node_t* root, int insertNum)
{
	pRBtree_node_t pNew;
	pRBtree_node_t pParent = *root;
	pNew = (pRBtree_node_t)malloc(sizeof(RBtree_node_t));
	memset(pNew, 0, sizeof(RBtree_node_t));
	pNew->num = insertNum;
	if (NULL == pParent)
	{
		*root = pNew;
	}
	else
	{
		//找到插入位置
		while (pParent)
		{
			if (pParent->num > insertNum)
			{
				if (pParent->lchild == NULL)
				{
					pParent->lchild = pNew;
					pNew->parent = pParent;
					break;
				}
				else
				{
					pParent = pParent->lchild;
				}
			}
			else
			{
				if (pParent->rchild == NULL)
				{
					pParent->rchild = pNew;
					pNew->parent = pParent;
					break;
				}
				else
				{
					pParent = pParent->rchild;
				}
			}
		}
		//调节新结点
		while (pNew->parent && RED == pNew->parent->color)	//只有父结点是红色时，才需要调节
		{
			if (GrandFather->lchild == pNew->parent)//父结点是祖父结点的左孩子
			{
				if (GrandFather->rchild && GrandFather->rchild->color == RED)//叔叔结点也是红色
				{
					GrandFather->color = RED;	//祖父结点绘制为红色
					GrandFather->lchild->color = BLACK;
					GrandFather->rchild->color = BLACK;	//叔叔结点和父亲结点绘制为黑色
					pNew = GrandFather;
				}
				else//叔叔结点是黑色或没有叔叔结点
				{
					if (pNew == pNew->parent->rchild)	//新结点是父结点的右孩子
					{
						Left_Rotate_RBtree_Node(pNew->parent, pNew, root);
						pNew = pNew->lchild;
					}
					GrandFather->color = RED;
					pNew->parent->color = BLACK;
					Right_Rotate_RBtree_Node(GrandFather, pNew->parent, root);
					pNew = pNew->parent;
				}
			}
			else//父结点是祖父结点的右孩子
			{
				if (GrandFather->lchild && GrandFather->lchild->color == RED)//叔叔结点也是红色
				{
					GrandFather->color = RED;	//祖父结点绘制为红色
					GrandFather->lchild->color = BLACK;
					GrandFather->rchild->color = BLACK;	//叔叔结点和父亲结点绘制为黑色
					pNew = GrandFather;
				}
				else//叔叔结点是黑色或没有叔叔结点
				{
					if (pNew == pNew->parent->lchild)	//新结点是父结点的左孩子
					{
						Right_Rotate_RBtree_Node(pNew->parent, pNew, root);
						pNew = pNew->rchild;
					}
					GrandFather->color = RED;
					pNew->parent->color = BLACK;
					Left_Rotate_RBtree_Node(GrandFather, pNew->parent, root);
					pNew = pNew->parent;
				}
			}
		}
	}
	(*root)->color = BLACK;
}

//前序遍历输出红黑树
void PreOrder_Print_RBtree(pRBtree_node_t root)
{
	if (root)
	{
		printf("%d ", root->num);
		PreOrder_Print_RBtree(root->lchild);
		PreOrder_Print_RBtree(root->rchild);
	}
}

int main()
{
	int a[] = { 10,40,30,60,90,70,20,50,80,65 };	//老师提供的测试用数据
	pRBtree_node_t rbtree_root = NULL;
	int i;
	for (i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		Insert_RBtree_Node(&rbtree_root, a[i]);
		PreOrder_Print_RBtree(rbtree_root);		//调试用，前序输出结点
		putchar('\n');
	}
	system("pause");
}