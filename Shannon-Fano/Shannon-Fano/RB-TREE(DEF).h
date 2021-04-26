#pragma once
#include "LinkedList.h"
#include <iostream>

enum NodeColor { BLACK, RED };

template<class NODE_TYPE_1, class NODE_TYPE_2>
class RB_TREE_Node
{
public:
	//desturctor
	~RB_TREE_Node();

	//creates a NIL ans sets the root to the NIL
	void NIL_N_Root();

	//rotation operations for balancing the RB tree
	void Left_Rotate(RB_TREE_Node* node_x);
	void Right_Rotate(RB_TREE_Node* node_y);

	//inserting a node into the RB Tree
	void Insert(NODE_TYPE_1 key, NODE_TYPE_2 data);
	void Insert_Fixup(RB_TREE_Node* node_z);

	//removing a node from the RB Tree
	void Transplant(RB_TREE_Node* u, RB_TREE_Node* v);
	void Remove(NODE_TYPE_1 key);
	void Remove_Fixup(RB_TREE_Node* node_x);

	//searches for an element by key
	RB_TREE_Node* Find(NODE_TYPE_1 key, RB_TREE_Node* node_x);

	//clears an associative array
	void Clear(RB_TREE_Node* tree);

	//returns a list of keys
	void Get_Keys(RB_TREE_Node* node_x, LinkedList<NODE_TYPE_1>* List_of_Keys);

	//returns a list of values
	void Get_Values(RB_TREE_Node* node_x, LinkedList<NODE_TYPE_2>* List_of_Values);

	//print the tree in the following order: first the left subtree, then the right subtree
	void Print(RB_TREE_Node* node_x);

	//getter that returns the root
	RB_TREE_Node* Get_Root() { return root; }

	//getter that returns pointer to the parent element
	RB_TREE_Node* Get_Parent() { return parent; }

	template<class ARRAY_TYPE>
	void Fill_Array(RB_TREE_Node* node_x, ARRAY_TYPE* array, const char* key_or_data)
	{
		static int i = 0;
		if (key_or_data == "data")
		{
			if (node_x->Get_Parent() == NULL)
				throw "RB Tree is empty";
			if (node_x == NIL)
				return;
			else
			{
				array[i++] = node_x->data;
				if (node_x->left != NIL)
					Fill_Array(node_x->left, array, key_or_data);
			}
			if (node_x->right != NIL)
				Fill_Array(node_x->right, array, key_or_data);
		}
		else if (key_or_data == "key")
		{
			if (node_x->Get_Parent() == NULL)
				throw "RB Tree is empty";
			if (node_x == NIL)
				return;
			else
			{
				array[i++] = node_x->key;
				if (node_x->left != NIL)
					Fill_Array(node_x->left, array, key_or_data);
			}
			if (node_x->right != NIL)
				Fill_Array(node_x->right, array, key_or_data);
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Перегрузка операторов [], = и ++ для более удобного взаимодействия с красно-черным деревом, как с map в общем

	//operator [] overload
	NODE_TYPE_2& operator[] (const NODE_TYPE_1 key)
	{
		RB_TREE_Node* node = Find(key, root);
		return node->data;
	}

	//operator = overload
	void operator = (NODE_TYPE_2 new_data)
	{
		data = new_data;
	}

	//operator ++ overload
	void operator ++ () { ++data; }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//getter that returns size of RB-Tree
	unsigned Get_Size() { return size; }

	//returns a pointer to the minimal element of the subtree with the root at the given node_x
	RB_TREE_Node* Tree_Minimum(RB_TREE_Node* node_x);

private:

	//pointers to the left, right and parent elements of the node
	RB_TREE_Node* left, * right, * parent;

	//pointer to the root of the tree
	RB_TREE_Node* root;

	//pointer to an object with the same attributes as a normal tree node. The color value is BLACK, the rest is optional
	RB_TREE_Node* NIL;

	//color of the node (black or red)
	NodeColor color;

	//key and data of a node
	NODE_TYPE_1 key;
	NODE_TYPE_2 data;

	//size of RB-Tree
	unsigned size;
};

#include "RB-TREE(CON).inl"