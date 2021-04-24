#include "LinkedList.h"
#include "RB-TREE(DEF).h"
#include <iostream>

template<class NODE_TYPE_1, class NODE_TYPE_2>
RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::~RB_TREE_Node()
{
	Clear(root);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::NIL_N_Root()
{
	//NIL declaration
	NIL = new RB_TREE_Node;
	NIL->color = BLACK;

	//At the start of the program root equals NIL
	root = NIL;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Left_Rotate(RB_TREE_Node* node_x)
{
	RB_TREE_Node* node_y = node_x->right;
	node_x->right = node_y->left;
	if (node_y->left != NIL)
		node_y->left->parent = node_x;
	if (node_y != NIL)
		node_y->parent = node_x->parent;
	if (node_x->parent == NIL)
		root = node_y;
	else if (node_x == node_x->parent->left)
		node_x->parent->left = node_y;
	else
		node_x->parent->right = node_y;
	node_y->left = node_x;
	if (node_x != NIL)
		node_x->parent = node_y;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Right_Rotate(RB_TREE_Node* node_x)
{
	RB_TREE_Node* node_y = node_x->left;
	node_x->left = node_y->right;
	if (node_y->right != NIL)
		node_y->right->parent = node_x;
	if (node_y != NIL)
		node_y->parent = node_x->parent;
	if (node_x->parent == NIL)
		root = node_y;
	else if (node_x == node_x->parent->left)
		node_x->parent->left = node_y;
	else
		node_x->parent->right = node_y;
	node_y->right = node_x;
	if (node_x != NIL)
		node_x->parent = node_y;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Insert(NODE_TYPE_1 key, NODE_TYPE_2 data) 
{
	RB_TREE_Node* node_z = new RB_TREE_Node;
	node_z->key = key;
	node_z->data = data;
	RB_TREE_Node* node_x = root;
	RB_TREE_Node* node_y = NIL;
	while (node_x != NIL)
	{
		node_y = node_x;
		if (node_z->key == node_x->key)
			throw -1;
		if (node_z->key < node_x->key)
			node_x = node_x->left;
		else
			node_x = node_x->right;
	}
	node_z->parent = node_y;
	if (node_y == NIL)
		root = node_z;
	else if (node_z->key < node_y->key)
		node_y->left = node_z;
	else
		node_y->right = node_z;
	node_z->left = NIL;
	node_z->right = NIL;
	node_z->color = RED;
	Insert_Fixup(node_z);
	size++;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Insert_Fixup(RB_TREE_Node* node_z)
{
	while (node_z->parent->color == RED && node_z != root)
	{
		if (node_z->parent == node_z->parent->parent->left)
		{
			RB_TREE_Node* node_y = node_z->parent->parent->right;
			if (node_y->color == RED)
			{
				node_z->parent->color = BLACK;//////////////CASE 1
				node_y->color = BLACK;//////////////////////CASE 1
				node_z->parent->parent->color = RED;////////CASE 1
				node_z = node_z->parent->parent;////////////CASE 1
			}
			else
			{
				if (node_z == node_z->parent->right)
				{
					node_z = node_z->parent;///////////////CASE 2
					Left_Rotate(node_z);///////////////////CASE 2
				}
				node_z->parent->color = BLACK;/////////////CASE 3
				node_z->parent->parent->color = RED;///////CASE 3
				Right_Rotate(node_z->parent->parent);//////CASE 3
			}
		}
		else
		{
			RB_TREE_Node* node_y = node_z->parent->parent->left;
			if (node_y->color == RED)
			{
				node_z->parent->color = BLACK;
				node_y->color = BLACK;
				node_z->parent->parent->color = RED;
				node_z = node_z->parent->parent;
			}
			else
			{
				if (node_z == node_z->parent->left)
				{
					node_z = node_z->parent;
					Right_Rotate(node_z);
				}
				node_z->parent->color = BLACK;
				node_z->parent->parent->color = RED;
				Left_Rotate(node_z->parent->parent);

			}
		}
	}
	root->color = BLACK;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Transplant(RB_TREE_Node* node_u, RB_TREE_Node* node_v)
{
	if (node_u->parent == NIL)
		root = node_v;
	else if (node_u == node_u->parent->left)
		node_u->parent->left = node_v;
	else
		node_u->parent->right = node_v;
	node_v->parent = node_u->parent;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Remove(NODE_TYPE_1 key)
{
	RB_TREE_Node* node_z = Find(key, root);
	RB_TREE_Node* node_y = node_z, * node_x;
	NodeColor node_y_original_color = node_y->color;
	if (node_z->left == NIL)//node_z has only the right child node
	{
		node_x = node_z->right;
		Transplant(node_z, node_z->right);
	}
	else if (node_z->right == NIL)//node_z has only the left child node
	{
		node_x = node_z->left;
		Transplant(node_z, node_z->left);
	}
	else//node_z has both child nodes
	{
		node_y = Tree_Minimum(node_z->right);
		node_y_original_color = node_y->color;
		node_x = node_y->right;
		if (node_y->parent == node_z)
			node_x->parent = node_y;
		else
		{
			Transplant(node_y, node_y->right);
			node_y->right = node_z->right;
			node_y->right->parent = node_y;
		}
		Transplant(node_z, node_y);
		node_y->left = node_z->left;
		node_y->left->parent = node_y;
		node_y->color = node_z->color;
	}
	if (node_y_original_color == BLACK)
		Remove_Fixup(node_x);
	size--;
}

template <class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Remove_Fixup(RB_TREE_Node* node_x)
{
	while (node_x != root && node_x->color == BLACK)
	{
		if (node_x == node_x->parent->left)
		{
			RB_TREE_Node* node_w = node_x->parent->right;
			if (node_w->color == RED)
			{
				node_w->color = BLACK;////////////////////CASE 1
				node_x->parent->color = RED;//////////////CASE 1
				Left_Rotate(node_x->parent);//////////////CASE 1
				node_w = node_x->parent->right;///////////CASE 1
			}
			if (node_w->left->color == BLACK && node_w->right->color == BLACK)
			{
				node_w->color = RED;//////////////////////CASE 2
				node_x = node_x->parent;//////////////////CASE 2
			}
			else
			{
				if (node_w->right->color == BLACK)
				{
					node_w->left->color = BLACK;//////////CASE 3
					node_w->color = RED;//////////////////CASE 3
					Right_Rotate(node_w);/////////////////CASE 3
					node_w = node_x->parent->right;///////CASE 3
				}
				node_w->color = node_x->parent->color;////CASE 4
				node_x->parent->color = BLACK;////////////CASE 4
				node_w->right->color = BLACK;/////////////CASE 4
				Left_Rotate(node_x->parent);//////////////CASE 4
				node_x = root;////////////////////////////CASE 4
			}
		}
		else
		{
			RB_TREE_Node* node_w = node_x->parent->left;
			if (node_w->color == RED)
			{
				node_w->color = BLACK;
				node_x->parent->color = RED;
				Right_Rotate(node_x->parent);
				node_w = node_x->parent->left;
			}
			if (node_w->right->color == BLACK && node_w->left->color == BLACK)
			{
				node_w->color = RED;
				node_x = node_x->parent;
			}
			else
			{
				if (node_w->left->color == BLACK)
				{
					node_w->right->color = BLACK;
					node_w->color = RED;
					Left_Rotate(node_w);
					node_w = node_x->parent->left;
				}
				node_w->color = node_x->parent->color;
				node_x->parent->color = BLACK;
				node_w->left->color = BLACK;
				Right_Rotate(node_x->parent);
				node_x = root;
			}
		}
	}
	node_x->color = BLACK;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>* RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Find(NODE_TYPE_1 key, RB_TREE_Node* node_x)
{
	if (node_x->Get_Parent() == NULL)
		throw "Element not found";
	if (node_x == NIL || node_x->key == key)
		return node_x;
	if (key < node_x->key)
		return Find(key, node_x->left);
	else
		return Find(key, node_x->right);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Clear(RB_TREE_Node* tree)
{
	if (tree == NIL)
		return;
	else
	{
		if (tree->left)
			Clear(tree->left);
		if (tree->right)
			Clear(tree->right);
	}
	delete tree;
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Get_Keys(RB_TREE_Node* node_x, LinkedList<NODE_TYPE_1>* List_of_Keys)
{
	if (node_x->Get_Parent() == NULL)
		throw "RB Tree is empty";
	if (node_x == NIL)
		return;
	else
	{
		List_of_Keys->push_back(node_x->key);
		if (node_x->left != NIL)
			Get_Keys(node_x->left, List_of_Keys);
	}
	if (node_x->right != NIL)
		Get_Keys(node_x->right, List_of_Keys);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Get_Values(RB_TREE_Node* node_x, LinkedList<NODE_TYPE_2>* List_of_Values)
{
	if (node_x->Get_Parent() == NULL)
		throw "RB Tree is empty";
	if (node_x == NIL)
		return;
	else
	{
		List_of_Values->push_back(node_x->data);
		if (node_x->left != NIL)
			Get_Values(node_x->left, List_of_Values);
	}
	if (node_x->right != NIL)
		Get_Values(node_x->right, List_of_Values);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
void RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Print(RB_TREE_Node* node_x)
{
	if (node_x->Get_Parent() == NULL)
		throw "RB Tree is empty";
	if (node_x == NIL)
		return;
	else
	{
		std::cout << "Key = " << node_x->key << ", data = " << node_x->data << std::endl;
		if (node_x->left != NIL)
			Print(node_x->left);
	}
	if (node_x->right != NIL)
		Print(node_x->right);
}

template<class NODE_TYPE_1, class NODE_TYPE_2>
RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>* RB_TREE_Node<NODE_TYPE_1, NODE_TYPE_2>::Tree_Minimum(RB_TREE_Node* node_x)
{
	if (node_x->Get_Parent() == NULL)
		throw "RB Tree is empty";
	while (node_x->left != NIL)
		node_x = node_x->left;
	return node_x;
}
