#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

int main(int argc, char const *argv[])
{
	tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));
    tree_t t43 = tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make());
    tree_t t4 = tree_make(4, tree_make(), tree_make());
    tree_t t2 = tree_make(2, tree_make(), tree_make());
    cout<< "tree_start:\n";
    tree_print(start);
    cout << "\ntree_end:\n";
    tree_print(end);
    cout << endl;
    cout<< "insert_tree(4, start) "<<endl;
    //tree_print(tree_make(tree_elt(t2), tree_make(), tree_make(4, tree_make(), tree_make())));
    //cout<<endl;
    tree_t new_tree = insert_tree(4, end);
    tree_print(new_tree);
    cout<<endl;
    cout << "tree_sum(start)" << tree_sum(start) << endl;
    cout << "tree_sum(end)" << tree_sum(end) << endl;
    cout << "Is 3 in start ? " << tree_search(start, 3)<<endl;
    cout << "Is 3 in end ? " << tree_search(end, 3)<<endl;
    cout << "depth of start = " << depth(start)<<endl;
    cout << "depth of end = " << depth(end)<<endl;
    cout << "min int in start is: " << tree_min(start)<<endl;
    cout << "traversal(start) = ";
    list_print(traversal(start));
    cout<<endl;
    cout << "traversal(end) = ";
    list_print(traversal(end));
    cout<<endl;
    //cout << "The left most of start is: "<< tree_elt(tree_left(start))<<endl;
	cout << "tree_hasPathSum(start, 3) = "<<tree_hasPathSum(start, 3)<<endl;
	cout << "covered_by(start, end) = "<< covered_by(start, end) << endl;
	cout << "covered_by(end, start) = "<< covered_by(end, start) << endl;
	cout << "covered_by(t2, end) = "<< covered_by(t2, end) << endl;
	cout << "covered_by(t2, start) = "<< covered_by(t2, start) << endl;


	cout << "\ncontained_by(start, end) = "<< contained_by(start, end) << endl;
	cout << "contained_by(end, start) = "<< contained_by(end, start) << endl;
	cout << "contained_by(t43, end) = "<< contained_by(t43, end) << endl;
	cout << "contained_by(t43, start) = "<< contained_by(t43, start) << endl;
	cout << "contained_by(t4, end) = "<< contained_by(t4, end) << endl;
	cout << "contained_by(t4, start) = "<< contained_by(t4, start) << endl;

	return 0;
}