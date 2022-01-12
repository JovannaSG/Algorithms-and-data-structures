#pragma once
#include "Node.h"

using namespace std;

class RBTree
{
public:
	Node *root; // root of tree
	Node *TNill; // a black leaf на который завязываются все nullptr

	// RBTree() - create root of tree and leaf TNill (black color)
	RBTree();
	~RBTree();

	// DeleteRBTree - delete all nods of tree and leaf TNill
    void DeleteRBTree(Node *node);

    // PrintTree - выводит на консоль дерево положенное набок, корень слевой стороны
	void PrintTree(Node *r, int space = 0);

    //PrintPreOrder - прямой обход дерева, root - left subtree - right subtree
    void PrintPreOrder(Node *r);

	// PrintInOrder - симметричный обход дерева, left subtree - root - right subtree
    void PrintInOrder(Node *r);

	// PrintPostOrder - обратный обход дерева, left subtree - right subtree - root
    void PrintPostOrder(Node *r);

    /*
    * Insert - вставляет узел с уникальныйм узлом в дерево и
	* вызывает функцию FixupInsert()
	*/
    void Insert(Time key, Node *Tnill);

    /*
	* FixupInsert - balance tree and fix colors, after insert
	*/
	void FixupInsert(Node *node, Node *Tnill);

	//FindMaxOnLeft - search maximum element in left subtree
    Node *FindMaxOnLeft(Node *node, Node *Tnill);

	// FindNode - search node of tree by specified key
    Node *FindNode(Time key, Node *Tnill);

    /*
	* Transplant - replaces the subtree with the root in node node1
	* subtree with the root in node node2,
	* the parent of node node1 becomes the parent of node node2,
	* which becomes the corresponding child node of the parent
	* node with respect to node1 node
	*/
    void Transplant(Node *node1, Node *node2, Node *Tnill);

    /*
	* Delete - delete node with the specified key into the tree and
	* calls the FixupDelete() function, if node is delete then return true
	* else return false
	*/
    bool Delete(Time key, Node *Tnill);

    /*
	* FixupDelete - balance the tree and fix the colors of the tree nodes,
	* after delete node
	*/
	void FixupDelete(Node *node, Node *Tnill);

	// RightRotate - makes a right turn relative to the current root of the tree
    void RightRotate(Node *node, Node *Tnill);

	// LeftRotate - makes a left turn relative to the current root of the tree
    void LeftRotate(Node *node, Node *Tnill);

	// SetColor - sets the color of the tree node
	void SetColor(Color color);

    // FindMax - search maximum node of tree
    Node *FindMax(Node *Tnill);
};

