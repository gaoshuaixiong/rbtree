#ifndef RBTREE
#define RBTREE
#include "tree.h"


class rbtree : public tree
{
public:
	rbtree(){};
	~rbtree(){};
	void left_rotate(node *x);
	void right_rotate(node *x);
	void insert(int a);
	void insert_fixup(node *k);
	void get_brother(node *k);
};



void rbtree::insert_fixup(node  *k)
{
	while(k->parent->color == red)
	{
		node *uncle = get_uncle(k);
		if(k->parent == k->parent->parent->lchild)
		{
			if(uncle->color == red)
			{
				k->parent->color = black;
				uncle->color = black;
				k->parent->parent->color = red;
				k = k->parent->parent;
			}
			else if(k== k->parent->lchild)
			{
				k = k->parent;
				this->left_rotate(k);
			}
			else
			{
				k->parent->color = black;
				k->parent->parent->color = red;
				this->right_rotate(k->parent->parent);
			}
		}
		else
		{
			if(uncle->color == red)
			{
				uncle->color = black;
				k->parent->color = black;
				k->parent->parent->color = red;
				k = k->parent->parent;
			}
			else if (k == k->parent->rchild)
			{
				k->parent->color =  black;
				k->parent->parent->color =  red;
				this->left_rotate(k->parent->parent);
			}
			else
			{
				k = k->parent;
				this->right_rotate(k);
			}
		}
	}
	root->color =  black;
}

void rbtree::insert(int a)
{
	node *z = new node(a,NIL);
	node *x = root;
	node *y =NIL;
	while(x!=NIL)
	{
		y = x;
		if(a < x->key)
		{
			x = x->lchild;
		}
		else
		{
			x = x->rchild;
		}
	}
	if(y == NIL)
	{
		root = z;
	}
	if(a< y->key)
	{
		y->lchild = z;
	}
	else
	{
		y->rchild = z;
	}
	z->parent = y;
	z->color = red;
	this->insert_fixup(z);
	cout<<"test root:"<<root->key<<endl;
	this->preorder(root);
}

void rbtree::left_rotate(node *x)
{
	// cout<<"left_rotate: "<<endl;
	//  x->print_node();
	node *y = x->rchild;
	node *beta = y->lchild;
	if(x->parent ==NIL)
	{
		root = y;
	}
	else if(x==x->parent->lchild)
	{
		x->parent->lchild = y;
	}
	else
	{
		x->parent->rchild = y;
	}
	y->parent = x->parent;
	x->parent = y;
	y->lchild = x;
	x->rchild = NIL;
	if(beta!=NIL)
	{
		beta->parent = x;
		x->rchild = beta;
	}

}

void rbtree::right_rotate(node *x)
{
	// cout<<"right_rotate: "<<endl;
	node *y = x->lchild;	
	node *beta = y->rchild;
	if(x->parent ==NIL)
	{
		root = y;
	}
	else if(x->parent->lchild == x)
	{
		x->parent->lchild =y;
	}
	else
	{
		x->parent->rchild =y;
	}
	y->parent = x->parent;
	y->rchild = x;
	x->parent = y;
	x->lchild = NIL;
	if(beta!=NIL)
	{
		beta->parent = x;
		x->lchild = beta;
	}
}

#endif