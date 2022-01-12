#pragma once
#include <iostream>
#include "Node.h"

class AVLTree_Class
{
public:
    AVLTree_Class();
    ~AVLTree_Class();

    Node *root;

    // Методы балансировки
    void BalanceR(Node *&node, bool &flag);

    void BalanceL(Node *&node, bool &flag);

    // Метод вставки по Вирту
    void insertVirt(Node *&node, Time key);

    // Методы удаления узла по Вирту
    void del(Node *&r, bool &flag, Node *&q);

    void deleteVirt(Node *&node, Time key, bool &flag);

    // Метод вывода дерева
    void printTree(Node *root);

    // Обход лево-право-корень
    void printLeftRightRoot(Node *&node);

    // Обход корень-лево-право
    void printRootLeftRight(Node *&node);

    // Метод освобождения памяти
    void FreeTree(Node *node);
};