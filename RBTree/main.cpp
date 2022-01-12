/*
Реализовать бинарное красно-черное дерево, элементы которого это списки
ключ должен быть уникальный (элементы без повторов)

Написать основыные операции:
1 Создать
2 Очистить
3 Добавить
4 Удалить, при удалении заменять на max слева элемент
5 Найти элемент по значению
6 Найти max элемент
7 Обход (прямой, обратный, симметричный)
*/

#include <iostream>
#include "RedBlackTree.h"
#include "RedBlackTree.cpp"

using namespace std;


bool checkTime(Time key)
{
    if (key.hour > 24 || key.hour < 0)
    {
        cout << "Time is entered incorrectly" << endl;
        return false;
    }
    else if (key.minutes > 60 || key.minutes < 0)
    {
        return false;
    }
    else
        return true;
}



int main()
{
	RBTree Tree1; // По возрастанию

    // ================================== Inserts values in tree ====================================

    // Auto input
    /*for (int i = 0; i < 10; i++)
    {
        Time time;
        time.hour = rand() % 24;
        time.minutes = rand() % 60;
        Tree.Insert(time, Tree.TNill);
    }
    Time key;
    key.hour = 10;
    key.minutes = 44;
    Tree.Insert(key, Tree.TNill);*/

    // Keyboard input
    /*int n;
    cout << "Enter count of nods: ";
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        Time time;
        //cout << "Enter hour and minutes: ";
        //cin >> time.hour >> time.minutes;
        time.hour = 0;
        time.minutes = i;
        Tree1.Insert(time, Tree1.TNill);
    }*/
    Time time;
    time.minutes = 0;

    time.hour = 10;
    Tree1.Insert(time, Tree1.TNill);
    time.hour = 8;
    Tree1.Insert(time, Tree1.TNill);
    time.hour = 12;
    Tree1.Insert(time, Tree1.TNill);
    time.hour = 7;
    Tree1.Insert(time, Tree1.TNill);
    time.hour = 11;
    Tree1.Insert(time, Tree1.TNill);
    time.hour = 14;
    Tree1.Insert(time, Tree1.TNill);
    time.hour = 15;
    Tree1.Insert(time, Tree1.TNill);


    Tree1.PrintTree(Tree1.root);
    cout << endl;
    cout << "======================================================================" << endl;

    /*Tree.PrintTree(Tree.root);
    cout << endl;
    cout << "======================================================================" << endl;*/

    // =================================== Delete nods of tree ====================================

    /*Time k;

        cout << "Enter value of the element to delete: ";
        cin >> k.hour >> k.minutes;

        Tree2.Delete(k, Tree2.TNill);
        Tree2.PrintTree(Tree2.root);
        cout << endl;
        cout << "======================================================================" << endl;*/
    time.hour = 8;
    Tree1.Delete(time, Tree1.TNill);
    Tree1.PrintTree(Tree1.root);
    cout << endl;
    cout << "======================================================================" << endl;
    time.hour = 7;
    Tree1.Delete(time, Tree1.TNill);
    Tree1.PrintTree(Tree1.root);
    cout << endl;
    cout << "======================================================================" << endl;
    time.hour = 10;
    Tree1.Delete(time, Tree1.TNill);
    Tree1.PrintTree(Tree1.root);
    cout << endl;



   /* // ============================ Search maximum in tree ==================================

    cout << endl;
    Node *maxnode = Tree.FindMax(Tree.TNill);

    if (maxnode != Tree.TNill)
        cout << "Maximum element: " << "[" << maxnode->key.hour << ";" << maxnode->key.minutes << "]" << endl;
    else
        cout << "There is no maximum element";
    cout << endl;

    // ============================ Search for a node by a given value ==================================
    Time value;
    cout << "Enter the value of the desired element: ";
    cin >> value.hour >> value.minutes;

    Node *node = Tree.FindNode(value,Tree.TNill);
    if (node != Tree.TNill)
    {
        cout << "Element is found: ";
        Tree.SetColor(node->color);
        cout << "[" << node->key.hour << ":" << node->key.minutes << "]" << endl;
        Tree.SetColor(Color::White);
    }
    else
        cout << "There is no node with this value in the tree" << endl;
    cout << endl;*/

   // ============================ Tree traversals =====================================

   /*cout << "Direct tree traversal: ";
   Tree1.PrintPreOrder(Tree1.root);
   cout << endl;

   cout << "Symmetric tree traversal: ";
   Tree1.PrintInOrder(Tree1.root);
   cout << endl;

   cout << "Reverse tree traversal: ";
   Tree1.PrintPostOrder(Tree1.root);
   cout << endl;*/


   // ============================= Delete tree =========================================
	cout << endl;
	Tree1.DeleteRBTree(Tree1.root);
	return 0;
}


