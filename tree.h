#ifndef TREE
#define TREE
#include <iostream>
using namespace std;

enum rbcolor
{
	black,
	red
};
struct node
{
	node * parent;
	node * lchild;
	node * rchild;
	int key;
	rbcolor color;
	node(int a){key =a; this->color = black;};
	node(int a,node * NIL){key =a; parent = NIL;lchild = NIL;rchild = NIL; this->color = black;};
	void print_node();
};

void node::print_node()
{
	cout<<"node key: "<<key<<" color:"<<color<<" rchild:"<<rchild->key<<" rchild color:"<<rchild->color<<" lchild:"<<lchild->key<<" lchild color:"<<lchild->color<<endl;
}


class tree
{
private:

public:
	node * NIL;
	node * root;
	tree(){NIL = new node(0);NIL->rchild = NIL;NIL->lchild = NIL; root = NIL;root->parent = NIL;};
	~tree(){};
	void insert(int a);
	void inorder(node *r);
	void preorder(node *r);
	void afterorder(node *r);
	node * search(int x,node * k);
	node * maxmum(node *k);
	node * minmun(node *k);
	node * successor(node *k);
	void delete_node(node *k);
	void  transplant(node *x,node *y);
	node * get_uncle(node *k);

};


node* tree::get_uncle(node *k)
{
	node *parent = k->parent;
	node *grand_parent = k->parent->parent;
	if(parent == grand_parent->lchild)
	{
		return grand_parent->rchild;
	}
	else
	{
		return grand_parent->lchild;
	}
}

void tree::transplant(node *x,node *y)
{
	if(x->parent ==NIL)
	{
		root = y;
	}
	else if(x->parent->lchild == x)
	{
		x->parent->lchild = y;
	}
	else
	{
		x->parent->rchild = y;
	}
	y->parent = x->parent;
}

void tree::delete_node(node *k)
{
	node *x;
	if(k->lchild==NIL)
	{
		transplant(k,k->rchild);
	}
	else if(k->rchild ==NIL)
	{
		transplant(k,k->lchild);
	}
	else
	{
		x=minmun(k->rchild);
		if(x->parent == k)
		{
			transplant(k,x);
			k->lchild->parent = x;
			x->lchild = k->lchild;
		}
		else
		{
			transplant(x,x->rchild);
			transplant(k,x);
			x->rchild = k->rchild;
			x->rchild->parent = x;
			x->lchild = k->lchild;
			x->lchild->parent = x;
		}

	}
	delete(k);
}

node *tree::successor(node *k)
{
	if(k->rchild!=NIL)
	{
		return minmun(k->rchild);
	}
	node *y;
	y = k->parent;
	while((y!=NIL)&&(k==y->rchild))
	{
		k=y;
		y=y->parent;
	}
	return y;
}

node * tree::minmun(node *k)
{
	node *y;
	while(k!=NIL)
	{
		y = k;
		k = k->lchild;
	}
	return y;
}


node * tree::maxmum(node *k)
{
	node *y;
	while(k!=NIL)
	{
		y = k;
		k = k->rchild;
	}
	return y;
}

node * tree::search(int x,node *k)
{
	if(x< k->key)
	{
		k = k->lchild;
		return search(x,k);
	}
	if(x> k->key)
	{
		k = k->rchild;
		return search(x,k);
	}
	return k;
}

void tree::afterorder(node * r)
{
	if(r!=NIL)
	{
		afterorder(r->lchild);
		afterorder(r->rchild);
		// r->print_node();
	}
}

void tree::preorder(node * r)
{
	if(r!=NIL)
	{
		r->print_node();
		preorder(r->lchild);
		preorder(r->rchild);
	}
}

void tree::inorder(node * r)
{
	if(r!=NIL)
	{
		inorder(r->lchild);
		r->print_node();
		inorder(r->rchild);
	}
}

void tree::insert(int a)
{
	node *z = new node(a,NIL);
	node *x = root;
	node *y = NIL;
	while(x!=NIL)
	{
		y = x;
		if(a<x->key)
		{
			x = x->lchild;
		}
		else
		{
			x = x->rchild;
		}
	}
	if(y==NIL)
	{
		root = z;
	}
	else if(a<y->key)
	{
		y->lchild = z;
		z->parent = y;
	}
	else
	{
		y->rchild = z;
		z->parent = y;
	}
}
#endif



