#include "tree.h"
#include "rbtree.h"
#include <vector>
using namespace std;


int main(int argc, char const *argv[])
{
	std::vector<int> v{1,2,3,47,5,9,-1};
	rbtree rb;

	for(int i: v)
	{
		rb.insert(i);
	}
	for(int i:v)
	{
		if(rb.root!=rb.NIL)
		{
			rb.delete_node(rb.root);
		}
		
	}
	return 0;
}