#include "tree.h"
#include "rbtree.h"
#include <vector>
using namespace std;


int main(int argc, char const *argv[])
{
	std::vector<int> v{1,2,3,47,8,5};
	tree search_tree;
	for(int i: v)
	{
		search_tree.insert(i);
	}
	rbtree rb;
	for(int i: v)
	{
		rb.insert(i);
	}
	return 0;
}