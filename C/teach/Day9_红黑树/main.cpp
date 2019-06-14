/**
 * C����ʵ�ֵĺ����(Red Black Tree)
 *
 * @author skywang
 * @date 2013/11/18
 */

#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

/*
 * ���������������"������ĸ�"��
 */
RBRoot* create_rbtree()
{
    RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
    root->node = NULL;

    return root;
}

/*
 * ǰ�����"�����"
 */
static void preorder(RBTree tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->key);
        preorder(tree->left);
        preorder(tree->right);
    }
}
void preorder_rbtree(RBRoot *root) 
{
    if (root)
        preorder(root->node);
}

/*
 * �������"�����"
 */
static void inorder(RBTree tree)
{
    if(tree != NULL)
    {
        inorder(tree->left);
        printf("%d ", tree->key);
        inorder(tree->right);
    }
}

void inorder_rbtree(RBRoot *root) 
{
    if (root)
        inorder(root->node);
}

/*
 * �������"�����"
 */
static void postorder(RBTree tree)
{
    if(tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->key);
    }
}

void postorder_rbtree(RBRoot *root)
{
    if (root)
        postorder(root->node);
}

/*
 * (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
 */
static Node* search(RBTree x, Type key)
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}
int rbtree_search(RBRoot *root, Type key)
{
    if (root)
        return search(root->node, key)? 0 : -1;
}

/*
 * (�ǵݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
 */
static Node* iterative_search(RBTree x, Type key)
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}
int iterative_rbtree_search(RBRoot *root, Type key)
{
    if (root)
        return iterative_search(root->node, key) ? 0 : -1;
}

/* 
 * ������С��㣺����treeΪ�����ĺ��������С��㡣
 */
static Node* minimum(RBTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

int rbtree_minimum(RBRoot *root, int *val)
{
    Node *node;

    if (root)
        node = minimum(root->node);

    if (node == NULL)
        return -1;

    *val = node->key;
    return 0;
}
 
/* 
 * ��������㣺����treeΪ�����ĺ����������㡣
 */
static Node* maximum(RBTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

int rbtree_maximum(RBRoot *root, int *val)
{
    Node *node;

    if (root)
        node = maximum(root->node);

    if (node == NULL)
        return -1;

    *val = node->key;
    return 0;
}

/* 
 * �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
 */
static Node* rbtree_successor(RBTree x)
{
    // ���x�����Һ��ӣ���"x�ĺ�̽��"Ϊ "�����Һ���Ϊ������������С���"��
    if (x->right != NULL)
        return minimum(x->right);

    // ���xû���Һ��ӡ���x���������ֿ��ܣ�
    // (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
    // (02) x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}
 
/* 
 * �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
 */
static Node* rbtree_predecessor(RBTree x)
{
    // ���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ���������������"��
    if (x->left != NULL)
        return maximum(x->left);

    // ���xû�����ӡ���x���������ֿ��ܣ�
    // (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
    // (01) x��"һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/* 
 * �Ժ�����Ľڵ�(x)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y                
 *   /  \      --(����)-->           / \                #
 *  lx   y                          x  ry     
 *     /   \                       /  \
 *    ly   ry                     lx  ly  
 *
 *
 */
static void rbtree_left_rotate(RBRoot *root, Node *x)
{
    // ����x���Һ���Ϊy
    Node *y = x->right;

    // �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
    // ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    // �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
    y->parent = x->parent;

    if (x->parent == NULL)//�޸ĺ�����ĸ��ڵ�
    {
        //tree = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
        root->node = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
    }
    else
    {
        if (x->parent->left == x) 
            x->parent->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
        else
            x->parent->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
    }
    
    // �� ��x�� ��Ϊ ��y�����ӡ�
    y->left = x;
    // �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
    x->parent = y;
}

/* 
 * �Ժ�����Ľڵ�(y)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�y��������)��
 *            py                               py
 *           /                                /
 *          y                                x                  
 *         /  \      --(����)-->            /  \                     #
 *        x   ry                           lx   y  
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 * 
 */
static void rbtree_right_rotate(RBRoot *root, Node *y)
{
    // ����x�ǵ�ǰ�ڵ�����ӡ�
    Node *x = y->left;

    // �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
    // ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    // �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
    x->parent = y->parent;

    if (y->parent == NULL) 
    {
        //tree = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
        root->node = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
        else
            y->parent->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
    }

    // �� ��y�� ��Ϊ ��x���Һ��ӡ�
    x->right = y;

    // �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
    y->parent = x;
}

/*
 * �����������������
 *
 * ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */
static void rbtree_insert_fixup(RBRoot *root, Node *node)
{
    Node *parent, *gparent;		//����㣬�游���

    // �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //�������ڵ㡱�ǡ��游�ڵ�����ӡ�
        if (parent == gparent->left)
        {
            // Case 1����������ڵ��Ǻ�ɫ
            {
                Node *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))//û�нڵ����÷�֧����ι��죿
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���,���岻���ڣ�Ҳ��Ϊ�Ǻ�ɫ
            if (parent->right == node)//����80�ڵ�ʱ����������������
            {
                Node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
            rb_set_black(parent);//��תǰ���ú���ɫ
            rb_set_red(gparent);//��תǰ���ú���ɫ
            rbtree_right_rotate(root, gparent);
        } 
        else//�����ڵ����游�ڵ���Һ���
        {
            // Case 1����������ڵ��Ǻ�ɫ
            {
                Node *uncle = gparent->left;//������60ʱ��������ɫ���ɣ�������ɫ�󲻷��Ϻ�������ݹ����
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;//���游��Ϊ���ӣ��������е���
                }
            }

            // Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӣ�����30ʱ����������������
            if (parent->left == node)
            {
                Node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
            rb_set_black(parent);//��תǰ���ú���ɫ��������Ϊ��ɫ
            rb_set_red(gparent);//��תǰ���ú���ɫ���游��Ϊ��ɫ
            rbtree_left_rotate(root, gparent);
        }
    }

    // �����ڵ���Ϊ��ɫ
    rb_set_black(root->node);
}

/*
 * ��ӽڵ㣺���ڵ�(node)���뵽�������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */
static void rbtree_insert(RBRoot *root, Node *node)
{
    Node *y = NULL;
    Node *x = root->node;

    // 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    rb_parent(node) = y;//�ҵ����ڵ㲢��Ҫ����ڵ�ĸ��ڵ��ָ���޸�
	//�޸ĸ��ڵ���ӽڵ�ָ��
    if (y != NULL)
    {
        if (node->key < y->key)
            y->left = node;                // ���2������node��������ֵ�� < ��y��������ֵ������node��Ϊ��y�����ӡ�
        else
            y->right = node;            // ���3��(��node��������ֵ�� >= ��y��������ֵ��)��node��Ϊ��y���Һ��ӡ� 
    }
    else
    {
        root->node = node;                // ���1����y�ǿսڵ㣬��node��Ϊ��
    }

    // 2. ���ýڵ����ɫΪ��ɫ
    node->color = RED;

    // 3. ������������Ϊһ��rb��
    rbtree_insert_fixup(root, node);
}

/*
 * �������
 *
 * ����˵����
 *     key �Ǽ�ֵ��
 *     parent �Ǹ���㡣
 *     left �����ӡ�
 *     right ���Һ��ӡ�
 */
static Node* create_rbtree_node(Type key, Node *parent, Node *left, Node* right)
{
    Node* p;

    if ((p = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK; // Ĭ��Ϊ��ɫ

    return p;
}

/* 
 * �½����(�ڵ��ֵΪkey)����������뵽�������
 *
 * ����˵����
 *     root ������ĸ�
 *     key ������ļ�ֵ
 * ����ֵ��
 *     0������ɹ�
 *     -1������ʧ��
 */
int insert_rbtree(RBRoot *root, Type key)
{
    Node *node;    // �½����

    // �����������ͬ��ֵ�Ľڵ㡣
    // (�������������ͬ��ֵ�Ľڵ㣬ע�͵��������仰���ɣ�)
    if (search(root->node, key) != NULL)
        return -1;

    // ����½����ʧ�ܣ��򷵻ء�
    if ((node=create_rbtree_node(key, NULL, NULL, NULL)) == NULL)
        return -1;

    rbtree_insert(root, node);

    return 0;
}

/*
 * �����ɾ����������
 *
 * �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node �������Ľڵ�
 */
static void rbtree_delete_fixup(RBRoot *root, Node *node, Node *parent)
{
    Node *other;
	//�����x˵����node
    while ((!node || rb_is_black(node)) && node != root->node)
    {
        if (parent->left == node)
        {
			//ɾ��
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x���ֵ�w�Ǻ�ɫ��,ɾ��77  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��,ɾ��65ʱ��ɾ��82ʱ����������ѭ��
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ���Ϊ��ɫ��  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                // Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {//ɾ��
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x���ֵ�w�Ǻ�ɫ��  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ�ģ�ɾ��77 
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
					//ɾ��99ʱ��Ӧ����w�������Ǻ�ɫ
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w��������Ϊ��ɫ��  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                // Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

/* 
 * ɾ�����
 *
 * ����˵����
 *     tree ������ĸ����
 *     node ɾ���Ľ��
 */
void rbtree_delete(RBRoot *root, Node *node)
{
    Node *child, *parent;
    int color;

    // ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
        // ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
        Node *replace = node;

        // ��ȡ��̽ڵ�,�ҷ�֧����Ľ���������Ҫ�ҵ�
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)����ʼ�滻
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        } 
        else 
            // "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣ɾ��60������
            root->node = replace;

        // child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
        // "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
        child = replace->right;
        parent = rb_parent(replace);
        // ����"ȡ���ڵ�"����ɫ
        color = rb_color(replace);

        // "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child��Ϊ��
            if (child)
                rb_set_parent(child, parent);
            //��Ϊ���Ҫ�Ƶ�ɾ��λ�����������ҽڵ㣬��Ϊ�丸�׵�����
			parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
		//�Ƴ�һ����ɫ��㲻��Ҫ�����������Ƴ�һ����ɫ��㣬�����ƽ��ͻ����
        if (color == BLACK)
            rbtree_delete_fixup(root, child, parent);
        free(node);

        return ;
    }
	//ɾ�������һ����NULL
    if (node->left !=NULL)
        child = node->left;
    else 
        child = node->right;
	//��ȡɾ�����ĸ���
    parent = node->parent;
    // ����"ȡ���ڵ�"����ɫ
    color = node->color;

    if (child)
        child->parent = parent;

    // "node�ڵ�"���Ǹ��ڵ�
    if (parent)
    {
		//�ڸ��׵���ߣ��Ͱ��Լ����ӷ���ߣ����ұߣ��Ͱ��Լ����ӷ��ұ�
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;//����Ǹ������Ӿͱ�Ϊ��

    if (color == BLACK)
        rbtree_delete_fixup(root, child, parent);
    free(node);
}

/* 
 * ɾ����ֵΪkey�Ľ��
 *
 * ����˵����
 *     tree ������ĸ����
 *     key ��ֵ
 */
void delete_rbtree(RBRoot *root, Type key)
{
    Node *z, *node; 

    if ((z = search(root->node, key)) != NULL)
        rbtree_delete(root, z);
}

/*
 * ���ٺ����
 */
static void rbtree_destroy(RBTree tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        rbtree_destroy(tree->left);
    if (tree->right != NULL)
        rbtree_destroy(tree->right);

    free(tree);
}

void destroy_rbtree(RBRoot *root)
{
    if (root != NULL)
        rbtree_destroy(root->node);

    free(root);
}

/*
 * ��ӡ"�����"
 *
 * tree       -- ������Ľڵ�
 * key        -- �ڵ�ļ�ֵ 
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
static void rbtree_print(RBTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree�Ǹ��ڵ�
            printf("%2d(B) is root\n", tree->key);
        else                // tree�Ƿ�֧�ڵ�
            printf("%2d(%s) is %2d's %6s child\n", tree->key, rb_is_red(tree)?"R":"B", key, direction==1?"right" : "left");

        rbtree_print(tree->left, tree->key, -1);
        rbtree_print(tree->right,tree->key,  1);
    }
}

void print_rbtree(RBRoot *root)
{
    if (root!=NULL && root->node!=NULL)
        rbtree_print(root->node, root->node->key, 0);
}

/**
 * C����ʵ�ֵĺ����(Red Black Tree)
 *
 * @author skywang
 * @date 2013/11/18
 */


#define CHECK_INSERT 1    // "����"�����ļ�⿪��(0���رգ�1����)
#define CHECK_DELETE 1    // "ɾ��"�����ļ�⿪��(0���رգ�1����)
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
    int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80,65};
	//int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80,65,66,45,77,99,82,23,55,88,33,47};
    int i, ilen=LENGTH(a);
    RBRoot *root=NULL;

    root = create_rbtree();//��ָ�������Ӧ�Ľṹ��ռ�
    printf("== ԭʼ����: ");
    for(i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");

    for(i=0; i<ilen; i++)
    {
        insert_rbtree(root, a[i]);
#if CHECK_INSERT
        printf("== ��ӽڵ�: %d\n", a[i]);
        printf("== ������ϸ��Ϣ: \n");
        print_rbtree(root);
        printf("\n");
#endif
    }

    printf("== ǰ�����: ");
    preorder_rbtree(root);

    printf("\n== �������: ");
    inorder_rbtree(root);

    printf("\n== �������: ");
    postorder_rbtree(root);
    printf("\n");

    if (rbtree_minimum(root, &i)==0)
        printf("== ��Сֵ: %d\n", i);
    if (rbtree_maximum(root, &i)==0)
        printf("== ���ֵ: %d\n", i);
    printf("== ������ϸ��Ϣ: \n");
    print_rbtree(root);
    printf("\n");

#if CHECK_DELETE
    for(i=0; i<ilen; i++)
    {
		printf("== ɾ���ڵ�: %d\n", a[i]);
        delete_rbtree(root, a[i]);
        if (root)
        {
            printf("== ������ϸ��Ϣ: \n");
            print_rbtree(root);
            printf("\n");
        }
    }
#endif

    destroy_rbtree(root);
}