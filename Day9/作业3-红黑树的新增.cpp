#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED		0		//��ɫ
#define BLACK	1		//��ɫ

#define GrandFather pNew->parent->parent

//�������㶨��
typedef struct red_black_tree_node
{
	int num;
	bool color;
	struct red_black_tree_node* parent, * lchild, * rchild;
}RBtree_node_t, * pRBtree_node_t;

//����
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

//����
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

//����һ���½��
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
		//�ҵ�����λ��
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
		//�����½��
		while (pNew->parent && RED == pNew->parent->color)	//ֻ�и�����Ǻ�ɫʱ������Ҫ����
		{
			if (GrandFather->lchild == pNew->parent)//��������游��������
			{
				if (GrandFather->rchild && GrandFather->rchild->color == RED)//������Ҳ�Ǻ�ɫ
				{
					GrandFather->color = RED;	//�游������Ϊ��ɫ
					GrandFather->lchild->color = BLACK;
					GrandFather->rchild->color = BLACK;	//������͸��׽�����Ϊ��ɫ
					pNew = GrandFather;
				}
				else//�������Ǻ�ɫ��û��������
				{
					if (pNew == pNew->parent->rchild)	//�½���Ǹ������Һ���
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
			else//��������游�����Һ���
			{
				if (GrandFather->lchild && GrandFather->lchild->color == RED)//������Ҳ�Ǻ�ɫ
				{
					GrandFather->color = RED;	//�游������Ϊ��ɫ
					GrandFather->lchild->color = BLACK;
					GrandFather->rchild->color = BLACK;	//������͸��׽�����Ϊ��ɫ
					pNew = GrandFather;
				}
				else//�������Ǻ�ɫ��û��������
				{
					if (pNew == pNew->parent->lchild)	//�½���Ǹ���������
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

//ǰ�������������
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
	int a[] = { 10,40,30,60,90,70,20,50,80,65 };	//��ʦ�ṩ�Ĳ���������
	pRBtree_node_t rbtree_root = NULL;
	int i;
	for (i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		Insert_RBtree_Node(&rbtree_root, a[i]);
		PreOrder_Print_RBtree(rbtree_root);		//�����ã�ǰ��������
		putchar('\n');
	}
	system("pause");
}