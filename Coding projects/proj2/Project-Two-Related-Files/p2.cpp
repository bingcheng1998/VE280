//
//  p2.cpp
//  Project 2
//
//  516021910219 VE280
//
//  Created by Bingcheng on 2018/6/7.
//  Copyright © 2018 Bingcheng. All rights reserved.
//
#include <iostream>
#include "p2.h"

using namespace std;


static int size_helper(list_t list, int size)
// REQUEST: list can not be empty
// EFFECTS: return the size of the unempty 
// list_t list if it remains just one
{
	if (list_isEmpty(list_rest(list))) return size;
	return size_helper(list_rest(list), size+1);
}

int size(list_t list)
{
	if (list_isEmpty(list)) return 0;
	return size_helper(list, 1);
}

static int sum_helper(list_t list, int sum)
// REQUEST: list can not be empty, sum must
// larger than 0
// EFFECTS: return the sum of the unempty 
// list_t list if it remains just one integer
{
	if (list_isEmpty(list_rest(list))) return sum+list_first(list);
	return sum_helper(list_rest(list), (sum+list_first(list)));
}

int sum(list_t list)
/* 
// EFFECTS: Returns the sum of each element in "list".
//          Returns zero if "list" is empty.
*/ 
{
	if (list_isEmpty(list)) return 0;
 	return sum_helper(list, 0);
}

static int product_helper(list_t list, int product)
// REQUEST: list can not be empty, product must
// larger than 1
// EFFECTS: return the product of the unempty 
// list_t list if it remains just one integer
{
	if (list_isEmpty(list_rest(list))) return product*list_first(list);
	return product_helper(list_rest(list), (product*list_first(list)));
}

int product(list_t list)
{
	if (list_isEmpty(list)) return 1;
	return product_helper(list, 1);
}

int accumulate(list_t list, int (*fn)(int, int), int base)
{
	if (list_isEmpty(list)) return base;
	return fn(list_first(list), accumulate(list_rest(list), fn, base));
}

static list_t reverse_helper(list_t list, list_t list_origin)
// REQUEST: list_origin can not be empty
// EFFECTS: return the reverse of the unempty 
// list_t list if it remains just one integer
{
	if (list_isEmpty(list_rest(list_origin))) return list_make(list_first(list_origin), list);
	return reverse_helper(list_make(list_first(list_origin), list), list_rest(list_origin));
}

list_t reverse(list_t list){
	if (list_isEmpty(list) || list_isEmpty(list_rest(list))) return list;
	list_t list_new = list_make();
	return reverse_helper(list_new, list);
}

static list_t append_helper(list_t first, list_t second)
// REQUEST: first can not be empty
// EFFECTS: return the append of two unempty 
// if it the first remains just one integer
{
	if (list_isEmpty(list_rest(first))) return list_make(list_first(first), second);
	return append_helper(list_rest(first), list_make(list_first(first), second));
}

list_t append(list_t first, list_t second)
{
	if (list_isEmpty(first)) return second;
	return append_helper(reverse(first), second);
}

static bool is_odd(int odd)
// EFFECTS: return ture if odd is odd
{
	if (odd%2 == 0) return false;
	return true;
}

static list_t filter_odd_helper(list_t list, list_t list_origin)
// REQUEST: list_origin can not be empty
// EFFECTS: return the one odd list from the unempty 
// list_t list if it remains just one integer
{
	if (list_isEmpty(list_rest(list_origin))){
		if (is_odd(list_first(list_origin))) return list_make(list_first(list_origin), list);
		return list;
	}
	if (is_odd(list_first(list_origin))){
		return filter_odd_helper(list_make(list_first(list_origin), list), list_rest(list_origin));
	}
	return filter_odd_helper(list, list_rest(list_origin));
}

list_t filter_odd(list_t list){
	if (list_isEmpty(list)) return list;
	list_t list_new = list_make();
	return filter_odd_helper(list_new, reverse(list));
}

static list_t filter_even_helper(list_t list, list_t list_origin)
// REQUEST: list_origin can not be empty
// EFFECTS: return the one even list from the unempty 
// list_t list if it remains just one integer
{
	if (list_isEmpty(list_rest(list_origin))){
		if (!is_odd(list_first(list_origin))){
			return list_make(list_first(list_origin), list);
		}
		return list;
	}
	if (!is_odd(list_first(list_origin))){
		return filter_even_helper(list_make(list_first(list_origin), list), list_rest(list_origin));
	}
	return filter_even_helper(list, list_rest(list_origin));
}

list_t filter_even(list_t list){
	if (list_isEmpty(list)) return list;
	list_t list_new = list_make();
	return filter_even_helper(list_new, reverse(list));
}

static list_t filter_helper(list_t list, list_t list_origin, bool (*fn)(int))
// REQUEST: list_origin can not be empty
// EFFECTS: return the one odd or even list from  
// the unempty list_t list if it remains just one integer
{
	if (list_isEmpty(list_rest(list_origin))){
		if (fn(list_first(list_origin))){
			return list_make(list_first(list_origin), list);
		}
		return list;
	}
	if (fn(list_first(list_origin))){
		return filter_helper(list_make(list_first(list_origin), list), list_rest(list_origin), fn);
	}
	return filter_helper(list, list_rest(list_origin), fn);
}

list_t filter(list_t list, bool (*fn)(int))
{
	if (list_isEmpty(list)) return list;
	list_t list_new = list_make();
	return filter_helper(list_new, reverse(list), fn);
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
	if (size(first) < n) return list_make();
	return append(append(chop(first, size(first)-n), second), reverse(chop(reverse(first),n)));
}

static list_t chop_helper(list_t list, list_t list_origin, unsigned int n)
// EFFECTS: cut the first element of list_origin and
//past it on the begining of list
{
	if (n == 0) return reverse(list);
	return chop_helper(list_make(list_first(list_origin), list), list_rest(list_origin), n-1);
}

list_t chop(list_t list, unsigned int n)
{
	if (size(list) < n) return list_make();
	if (list_isEmpty(list) || n == 0) return list;
	list_t list_new = list_make();
	return chop_helper(list_new , list, size(list) - n);
}


//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

static int tree_sum_helper(tree_t tree){
	// REQUIRES: tree is not empty
    // EFFECTS: returns the sum of element of tree.
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
		return tree_elt(tree);
	if (tree_isEmpty(tree_left(tree)))
		return tree_elt(tree) + tree_sum_helper(tree_right(tree));
	if (tree_isEmpty(tree_right(tree)))
		return tree_elt(tree) + tree_sum_helper(tree_left(tree));
	return tree_elt(tree) + tree_sum_helper(tree_right(tree)) + tree_sum_helper(tree_left(tree));
}

int tree_sum(tree_t tree)
{
	if (tree_isEmpty(tree)) return 0;
	return tree_sum_helper(tree);
}

static bool tree_search_helper(tree_t tree, int key){
	// REQUIRES: tree is not empty
    // EFFECTS: Returns true if there exists any element in "tree"
	//          whose value is "key". Otherwise, return "false".
	if (tree_elt(tree) == key) return true;
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return false;
	if (tree_isEmpty(tree_left(tree))) return tree_search_helper(tree_right(tree),key);
	if (tree_isEmpty(tree_right(tree))) return tree_search_helper(tree_left(tree),key);
	return (tree_search_helper(tree_right(tree), key) || tree_search_helper(tree_left(tree), key));
}

bool tree_search(tree_t tree, int key)
{
	if (tree_isEmpty(tree)) return false;
	return tree_search_helper(tree, key);
}



static int depth_helper(tree_t tree, int dep)
// REQUIRES: tree is not empty
// EFFECTS: Returns the depth of non-empty "tree", which equals the number of
//          layers of nodes in the tree.
{
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return dep+1;
	if (tree_isEmpty(tree_left(tree))) return depth_helper(tree_right(tree), dep+1);
	if (tree_isEmpty(tree_right(tree))) return depth_helper(tree_left(tree), dep+1);
	return max(depth_helper(tree_right(tree), dep+1), depth_helper(tree_left(tree), dep+1));
}

int depth(tree_t tree)
{
if (tree_isEmpty(tree)) return 0;
return depth_helper(tree, 0);
}

static int tree_min_helper(tree_t tree, int min_int)
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree" if it's
// smaller than min_int
{
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return tree_elt(tree);
	if (tree_isEmpty(tree_left(tree))) return min(min_int, tree_min_helper(tree_right(tree), min_int));
	if (tree_isEmpty(tree_right(tree))) return min(min_int, tree_min_helper(tree_left(tree), min_int));
	return min(tree_min_helper(tree_right(tree), min_int), tree_min_helper(tree_left(tree), min_int));
}

int tree_min(tree_t tree)
{
	if(tree_isEmpty(tree)) return -1;
	return tree_min_helper(tree, tree_elt(tree));
}

static list_t traversal_helper(tree_t tree)
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the elements of "tree" in a list that's not empty 
//          using an in-order traversal. An in-order traversal prints 
//          the "left most" element first, then the second-left-most, 
//          and so on, until the right-most element is printed
{
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) 
		return list_make(tree_elt(tree), list_make());
	if (tree_isEmpty(tree_left(tree))) 
		return append(list_make(tree_elt(tree),list_make()), traversal_helper(tree_right(tree)));
	if (tree_isEmpty(tree_right(tree))) 
		return append(traversal_helper(tree_left(tree)), list_make(tree_elt(tree),list_make()));
	return append(append(traversal_helper(tree_left(tree)), list_make(tree_elt(tree),list_make())), traversal_helper(tree_right(tree)));
}

list_t traversal(tree_t tree)
{
	if (tree_isEmpty(tree)) return list_make();
	return traversal_helper(tree);
}

static bool tree_hasPathSum_helper(tree_t tree,int current_sum, int sum)
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns true if and only if non-empty "tree" has at least one 
// root-to-leaf path such that adding all elements along the path equals "sum".
{
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return (sum == (current_sum + tree_elt(tree)));
	if (tree_isEmpty(tree_left(tree))) return tree_hasPathSum_helper(tree_right(tree), current_sum + tree_elt(tree), sum);
	if (tree_isEmpty(tree_right(tree))) return tree_hasPathSum_helper(tree_left(tree), current_sum + tree_elt(tree), sum);
	return tree_hasPathSum_helper(tree_right(tree), current_sum + tree_elt(tree), sum) || 
		tree_hasPathSum_helper(tree_left(tree), current_sum + tree_elt(tree), sum);
}

bool tree_hasPathSum(tree_t tree, int sum)
{
	if (tree_isEmpty(tree)) return false;
	return tree_hasPathSum_helper(tree, 0, sum);
}

static bool tree_elt_equal(tree_t A, tree_t B)
// REQUIRES: "A" and "B" are non-empty.
// EFFECTS: Returns true if tree A is equal to tree B.
{
	if (tree_elt(A) == tree_elt(B)) return true;
	return false;
}

static bool covered_by_helper(tree_t tree, tree_t B)
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns true if tree A is covered by tree B.
{
	if (tree_isEmpty(B)) return false;
	if (!tree_elt_equal(tree, B)) return false;
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return true;
	if (tree_isEmpty(tree_left(tree))) return covered_by_helper(tree_right(tree), tree_right(B));
	if (tree_isEmpty(tree_right(tree))) return covered_by_helper(tree_left(tree), tree_left(B));
	return covered_by_helper(tree_right(tree), tree_right(B)) && covered_by_helper(tree_left(tree), tree_left(B));
}

bool covered_by(tree_t A, tree_t B)
{  
	if (tree_isEmpty(A)) return true;
	if (tree_isEmpty(B)) return false;
	return covered_by_helper(A, B);
}

static bool contained_by_helper(tree_t A, tree_t tree)
// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
{
	if (covered_by(A, tree)) return true;
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return covered_by(A, tree);
	if (tree_isEmpty(tree_left(tree))) return contained_by_helper(A, tree_right(tree));
	if (tree_isEmpty(tree_right(tree))) return contained_by_helper(A, tree_left(tree));
	return contained_by_helper(A, tree_right(tree)) || contained_by_helper(A, tree_left(tree));
}

bool contained_by(tree_t A, tree_t B)      
{
	return contained_by_helper(A, B);
}

static tree_t insert_tree_helper(int elt, tree_t tree, bool this_sub_tree)
// REQUIRES: "tree" is a sorted binary tree.
// EFFECTS: Returns a new tree with elt inserted at a leaf such that 
//          the resulting tree is also a sorted binary tree.
{
	if (!this_sub_tree) return tree;
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
			if (elt < tree_elt(tree)) return tree_make(tree_elt(tree), tree_make(elt, tree_make(), tree_make()), tree_make());
			return tree_make(tree_elt(tree), tree_make(), tree_make(elt, tree_make(), tree_make()));
	}
	if (tree_isEmpty(tree_left(tree))) {
			if (elt < tree_elt(tree)) return tree_make(tree_elt(tree), tree_make(elt, tree_make(), tree_make()), insert_tree_helper(elt, tree_right(tree), !this_sub_tree));
			return tree_make(tree_elt(tree), tree_make(), insert_tree_helper(elt, tree_right(tree), this_sub_tree));
	}
	if (tree_isEmpty(tree_right(tree))){
			if (elt < tree_elt(tree)) return tree_make(tree_elt(tree), insert_tree_helper(elt, tree_left(tree), this_sub_tree), tree_make());
			return tree_make(tree_elt(tree), insert_tree_helper(elt, tree_right(tree), !this_sub_tree), tree_make(elt, tree_make(), tree_make()));
	}
	if (elt < tree_elt(tree)) return tree_make(tree_elt(tree), insert_tree_helper(elt, tree_left(tree), this_sub_tree), insert_tree_helper(elt, tree_right(tree), !this_sub_tree));
	return tree_make(tree_elt(tree), insert_tree_helper(elt, tree_left(tree), !this_sub_tree), insert_tree_helper(elt, tree_right(tree), this_sub_tree));
}


tree_t insert_tree(int elt, tree_t tree)
{
	return insert_tree_helper(elt, tree, true);
}
