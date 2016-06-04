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
	node * get_brother(node *k);
	void delete_node(node *k);
	void rb_delete_fix(node *k);
};

node * rbtree::get_brother(node *k)
{
	if(k==k->parent->lchild)
	{
		return k->parent->rchild;
	}
	else
	{
		return k->parent->lchild;
	}
}

void rbtree::rb_delete_fix(node *k)
{
	node *brother;
	while((k!= root)&&(k->color== black))
	{
		brother =  get_brother(k);
		if(k == k->parent->lchild)
		{
			if(brother->color = red)
			{
				brother->color = black;
				k->parent->color = red;
				left_rotate(k->parent);
			}
			else if((brother->lchild->color ==black)&&(brother->rchild->color ==black))
			{
				brother->color = red;
				k = k->parent;
			}
			else if((brother->lchild->color ==red)&&(brother->rchild->color ==black))
			{
				brother->color = red;
				brother->lchild->color = black;
				right_rotate(brother);
			}
			else if((brother->lchild->color ==black)&&(brother->rchild->color ==red))
			{
				brother->color = k->parent->color;
				k->parent->color = black;
				left_rotate(k->parent);
				brother->rchild->color =black;
			}
			else if((brother->lchild->color ==red)&&(brother->rchild->color ==red))
			{
				brother->color = k->parent->color;
				k->parent->color = black;
				left_rotate(k->parent);
				brother->rchild->color =black;
			}
			k = root;
		}
		if(k == k->parent->rchild)
		{
			if(brother->color == red)
			{
				brother->color = black;
				brother->parent->color = red;
				right_rotate(brother->parent);
				k = k->parent->parent;
			}
			else if((brother->lchild->color == black)&&(brother->rchild->color == black))
			{
				brother->color = red;
				k = k->parent;	
			}
			else if((brother->lchild->color == black)&&(brother->rchild->color == red))
			{
				brother->rchild->color = black;
				brother->color = red;
				left_rotate(brother);
			}
			else if((brother->lchild->color == red)&&(brother->rchild->color == black))
			{
				brother->color = brother->parent->color;
				brother->parent->color = black;
				right_rotate(brother->parent);
				brother->lchild->color = black;
			}
			else if((brother->lchild->color == red)&&(brother->rchild->color == red))
			{
				brother->color = brother->parent->color;
				brother->parent->color = black;
				right_rotate(brother->parent);
				brother->lchild->color = black;
			}
		}
	}
	k->color =black;
}

void rbtree::delete_node(node *k)
{
	cout<<"before delete root:"<<root->key<<endl;
	this->preorder(root);
	node * x;
	node *y;
	rbcolor origin_color;
	if(k->lchild == NIL)
	{
		x = k->rchild;
		transplant(k,k->rchild);
	}
	else if(k->rchild == NIL)
	{
		x =  k->lchild;
		transplant(k,k->lchild);
	}
	else
	{
		y = minmun(k->rchild);
		origin_color  = y->color;
		x =  y->rchild;
		if(y->parent == k)
		{
			transplant(k,y);
			y->lchild =  k->lchild;
			k->lchild->parent = y;
		}
		else
		{
			transplant(y,x);
			transplant(k,y);
			y->lchild = k->lchild;
			k->lchild->parent = y;
			y->rchild = k->rchild;
			k->rchild->parent = y;
		}
		y->color = k->color;
	}
	if(origin_color == black)
	{
		rb_delete_fix(x);
	}
}

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