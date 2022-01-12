#include "RedBlackTree.h"
#include <iostream>
#include <Windows.h>

using namespace std;

RBTree::RBTree()
{
	root = new Node();
	TNill = new Node();

	TNill->color = Color::White;
	root = TNill;
}


RBTree::~RBTree()
{
}


void RBTree::DeleteRBTree(Node *node)
{
	if (node != TNill)
	{
		DeleteRBTree(node->leftchild);
		DeleteRBTree(node->rightchild);
		if (node == root)
		{
			delete TNill;
			delete node;
		}
		else
			delete node;
	}
}


void RBTree::PrintTree(Node *r, int space)
{
	if (r == TNill)
		return;
	space += 2;

	PrintTree(r->rightchild, space);

	cout << endl;
	for (int i = 0; i < space; i++)
		cout << "    ";
	SetColor(r->color);
	cout << "[" << r->key.hour << ":" << r->key.minutes << "]";
	SetColor(Color::White);

	PrintTree(r->leftchild, space);
}


void RBTree::PrintPreOrder (Node *r)
{
    if (r == TNill)
        return;

    cout << "[" << r->key.hour << ":" << r->key.minutes << "]" << " ";
    PrintPreOrder(r->leftchild);
    PrintPreOrder(r->rightchild);
}


void RBTree::PrintInOrder (Node *r)
{
    if (r == TNill)
        return;

    PrintInOrder(r->leftchild);
    cout << "[" << r->key.hour << ":" << r->key.minutes << "]" << " ";
    PrintInOrder(r->rightchild);
}


void RBTree::PrintPostOrder (Node *r)
{
    if (r == TNill)
        return;

    PrintPostOrder(r->leftchild);
    PrintPostOrder(r->rightchild);
    cout << "[" << r->key.hour << ":" << r->key.minutes << "]" << " ";
}


void RBTree::Insert(Time key, Node *Tnill)
{
	Node *curnode = root; // x
	Node *prnt = Tnill;
	Node *newnode = new Node(key); // newx

	while (curnode != Tnill)
	{
		prnt = curnode;
        if (key.hour < curnode->key.hour)
            curnode = curnode->leftchild;
        else if (key.hour > curnode->key.hour)
            curnode = curnode->rightchild;
        else if (key.minutes < curnode->key.minutes)
            curnode = curnode->leftchild;
        else if (key.minutes > curnode->key.minutes)
            curnode = curnode->rightchild;
        else
            return;
	}
	newnode->parent = prnt;

	if (prnt == Tnill)
		root = newnode;
	else if (key.hour < prnt->key.hour)
		prnt->leftchild = newnode;
    else if (key.hour > prnt->key.hour)
        prnt->rightchild = newnode;
    else if (key.minutes < prnt->key.minutes)
        prnt->leftchild = newnode;
	else
		prnt->rightchild = newnode;

	newnode->leftchild = Tnill;
	newnode->rightchild = Tnill;

	FixupInsert(newnode, TNill);
}


void RBTree::FixupInsert(Node *node, Node *Tnill)
{
	while (node->parent->color == Color::Red)
	{
		if (node->parent == node->parent->parent->leftchild)
		{
			if (node->parent->parent->rightchild->color == Color::Red)
			{
				node->parent->color = Color::White;
				node->parent->parent->rightchild->color = Color::White;
				node->parent->parent->color = Color::Red;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->rightchild)
				{
					node = node->parent;
					LeftRotate(node, TNill);
				}
				node->parent->color = Color::White;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent, TNill);
			}
		}
		else
		{
			if (node->parent->parent->leftchild->color == Color::Red)
			{
				node->parent->color = Color::White;
				node->parent->parent->leftchild->color = Color::White;
				node->parent->parent->color = Color::Red;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->leftchild)
				{
					node = node->parent;
					RightRotate(node, TNill);
				}
				node->parent->color = Color::White;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent, TNill);
			}
		}
	}
	root->color = Color::White;
}


Node *RBTree::FindMaxOnLeft (Node *node, Node *Tnill)
{
    while (node->rightchild != Tnill)
        node = node->rightchild;
    return node;
}


Node *RBTree::FindNode (Time key, Node *Tnill)
{
    Node *curnode = root;
    while (curnode != Tnill)
    {
        if (key.hour < curnode->key.hour)
            curnode = curnode->leftchild;
        else if (key.hour > curnode->key.hour)
            curnode = curnode->rightchild;
        else if (key.minutes < curnode->key.minutes)
            curnode = curnode->leftchild;
        else if (key.minutes > curnode->key.minutes)
            curnode = curnode->rightchild;
        else
            return curnode;
    }
}


void RBTree::Transplant(Node *node1, Node *node2, Node *Tnill)
{
	if (node1->parent == Tnill)
		root = node2;
	else if (node1 == node1->parent->leftchild)
		node1->parent->leftchild = node2;
	else
		node1->parent->rightchild = node2;

	node2->parent = node1->parent;
}


bool RBTree::Delete(Time key, Node *Tnill)
{
	Node *currentnode = FindNode(key, Tnill);
    Node *nodeForFixup;
    Color originalColor;

	if (currentnode != Tnill)
	{
		Node *auxnode = currentnode;
		originalColor = auxnode->color;

		if (currentnode->leftchild == Tnill)
		{
			nodeForFixup = currentnode->rightchild; //
			Transplant(currentnode, currentnode->rightchild, TNill);
		}
		else
		{
			if (currentnode->rightchild == Tnill)
			{
				nodeForFixup = currentnode->leftchild;
				Transplant(currentnode, currentnode->leftchild, Tnill);
			}
			else
			{
				auxnode = FindMaxOnLeft(currentnode->leftchild, Tnill);
				originalColor = auxnode->color;
				nodeForFixup = auxnode->leftchild;

				if (auxnode->parent == currentnode)
					nodeForFixup->parent = auxnode;
				else
				{
					Transplant(auxnode, auxnode->leftchild, Tnill); //
					auxnode->leftchild = currentnode->leftchild; //
					auxnode->leftchild->parent = auxnode; //
				}

				Transplant(currentnode, auxnode, Tnill);
				auxnode->rightchild = currentnode->rightchild; //
				auxnode->rightchild->parent = auxnode; //
				auxnode->color = currentnode->color;
			}
		}
		if (originalColor == Color::White)
			FixupDelete(nodeForFixup, Tnill);
		return true;
	}
	else
		return false;
}


void RBTree::FixupDelete(Node *node, Node *Tnill)
{
	while (node != root && node->color == Color::White)
	{
		if (node == node->parent->leftchild)
		{
			Node *auxnode = node->parent->rightchild;
			if (auxnode->color == Color::Red)
			{
				auxnode->color = Color::White;
				node->parent->color = Color::Red;

				LeftRotate(node->parent, Tnill);
				auxnode = node->parent->rightchild;
			}
			if (auxnode->leftchild->color == Color::White && auxnode->rightchild->color == Color::White)
			{
				auxnode->color = Color::Red;
				node = node->parent;
			}
			else
			{
				if (auxnode->rightchild->color == Color::White)
				{
					auxnode->leftchild->color = Color::White;
					auxnode->color = Color::Red;

					RightRotate(auxnode, Tnill);
					auxnode = node->parent->rightchild;
				}
				auxnode->color = node->parent->color;
				node->parent->color = Color::White;
				auxnode->rightchild->color = Color::White;

				LeftRotate(node->parent, Tnill);
				node = root;
			}
		}
		else
		{
			Node *auxnode = node->parent->leftchild;
			if (auxnode->color == Color::Red)
			{
				auxnode->color = Color::White;
				node->parent->color = Color::Red;

				RightRotate(node->parent, Tnill);
				auxnode = node->parent->leftchild;
			}
			if (auxnode->rightchild->color == Color::White && auxnode->leftchild->color == Color::White)
			{
				auxnode->color = Color::Red;
				node = node->parent;
			}
			else
			{
				if (auxnode->leftchild->color == Color::White)
				{
					auxnode->rightchild->color = Color::White;
					auxnode->color = Color::Red;

					LeftRotate(auxnode, Tnill);
					auxnode = node->parent->leftchild;
				}
				auxnode->color = node->parent->color;
				node->parent->color = Color::White;
				auxnode->leftchild->color = Color::White;

				RightRotate(node->parent, Tnill);
				node = root;
			}
		}
	}
    node->color = Color::White;
}


void RBTree::RightRotate(Node *node, Node *Tnill)
{
	Node *auxnode = node->leftchild;
	node->leftchild = auxnode->rightchild;

	if (auxnode->rightchild != Tnill)
		auxnode->rightchild->parent = node;

	auxnode->parent = node->parent;

	if (node->parent == Tnill)
		root = auxnode;
	else if (node == node->parent->rightchild)
		node->parent->rightchild = auxnode;
	else
		node->parent->leftchild = auxnode;

	auxnode->rightchild = node;
	node->parent = auxnode;
}


void RBTree::LeftRotate(Node *node, Node *Tnill)
{
	Node *auxnode = node->rightchild;
	node->rightchild = auxnode->leftchild;

	if (auxnode->leftchild != Tnill)
		auxnode->leftchild->parent = node;

	auxnode->parent = node->parent;

	if (node->parent == Tnill)
		root = auxnode;
	else if (node == node->parent->leftchild)
		node->parent->leftchild = auxnode;
	else
		node->parent->rightchild = auxnode;

	auxnode->leftchild = node;
	node->parent = auxnode;
}


void RBTree::SetColor(Color color)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, (WORD)color);
}


Node *RBTree::FindMax (Node *Tnill)
{
    Node *curnode = root;
    if (curnode != Tnill)
    {
        while (curnode->rightchild != Tnill)
            curnode = curnode->rightchild;
        return curnode;
    }
    else
        return curnode; // Это возращение TNill, в случае не найденного элемента
}


