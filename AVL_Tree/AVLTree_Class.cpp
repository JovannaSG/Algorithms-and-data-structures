#include "AVLTree_Class.h"

int indents = 0;
bool flag = false;

AVLTree_Class::AVLTree_Class()
{
    root = nullptr;
}

AVLTree_Class::~AVLTree_Class()
{
}

// Методы балансировки
void AVLTree_Class::BalanceR(Node *&node, bool &flag)
{
    Node *p1, *p2;

    // Уменьшилась правая ветвь
    if (node->balance == 1)
    {
        node->balance = 0;
    }
    else if (node->balance == 0)
    {
        node->balance = -1;
        flag = false;
    }
    else // balance == -1, балансируем
    {
        p1 = node->left;
        if (p1->balance <= 0) // Одиночная LL ротация
        {
            node->left = p1->right;
            p1->right = node;
            if (p1->balance == 0)
            {
                node->balance = -1;
                p1->balance = 1;
                flag = false;
            }
            else
            {
                node->balance = 0;
                p1->balance = 0;
            }
            node = p1;
        }
        else // Двойная LR ротация
        {
            p2 = p1->right;
            p1->right = p2->left;
            p2->left = p1;
            node->left = p2->right;
            p2->right = node;

            if (p2->balance == -1)
                node->balance = 1;
            else
                node->balance = 0;

            if (p2->balance == 1)
                node->balance = 1;
            else
                node->balance = 0;
            node = p2;
            p2->balance = 0;
        }
    }
}

void AVLTree_Class::BalanceL(Node *&node, bool &flag)
{
    Node *p1, *p2;

    // уменьшилась левая ветвь
    if (node->balance == -1)
    {
        node->balance = 0;
    }
    else if (node->balance == 0)
    {
        node->balance = 1;
        flag = false;
    }
    else // balance == 1, балансируем
    {
        p1 = node->right;
        if (p1->balance >= 0) // Одиночная RR ротация
        {
            node->right = p1->left;
            p1->left = node;

            if (p1->balance == 0)
            {
                node->balance = 1;
                p1->balance = -1;
                flag = false;
            }
            else
            {
                node->balance = 0;
                p1->balance = 0;
            }
            node = p1;
        }
        else // Двойная RL ротация
        {
            p2 = p1->left;
            p1->left = p2->right;
            p2->right = p1;
            node->right = p2->left;
            p2->left = node;

            if (p2->balance == 1)
                node->balance = -1;
            else
                node->balance = 0;

            if (p2->balance == -1)
                p1->balance = 1;
            else
                p1->balance = 0;
            node = p2;
            p2->balance = 0;
        }
    }
}

// Метод вставки в дерево
void AVLTree_Class::insertVirt(Node *&node, Time key)
{
    Node *p1, *p2;

    if (((key.hours >= 0) && (key.hours <= 23)) && ((key.minutes >= 0) && (key.minutes <= 59)))
    {
        // Находим место вставки
        if (node == NULL)
        {
            node = new Node(key);
            flag = true;
        }
        else if (node->key.hours > key.hours)
        {
            insertVirt(node->left, key);
            if (flag) // Выросла левая ветвь
            {
                if (node->balance == 1)
                {
                    node->balance = 0;
                    flag = false;
                }
                else if (node->balance == 0)
                {
                    node->balance = -1;
                }
                else // balance == -1, балансируем
                {
                    p1 = node->left;
                    if (p1->balance == -1) // Одиночная LL ротация
                    {
                        node->left = p1->right;
                        p1->right = node;
                        node->balance = 0;
                        node = p1;
                    }
                    else // Двойная LR ротация
                    {
                        p2 = p1->right;
                        p1->right = p2->left;
                        p2->left = p1;
                        node->left = p2->right;
                        p2->right = node;

                        if (p2->balance == -1)
                            node->balance = 1;
                        else
                            node->balance = 0;

                        if (p2->balance == 1)
                            p1->balance = -1;
                        else
                            p1->balance = 0;
                        node = p2;
                    }
                    node->balance = 0;
                    flag = false;
                }
            }
        }
        else if (node->key.hours < key.hours)
        {
            insertVirt(node->right, key);
            if (flag) // Выросла правая ветвь
            {
                if (node->balance == -1)
                {
                    node->balance = 0;
                    flag = false;
                }
                else if (node->balance == 0)
                {
                    node->balance = 1;
                }
                else // balance == 1, балансируем
                {
                    p1 = node->right;
                    if (p1->balance == 1) // Одиночная RR ротация
                    {
                        node->right = p1->left;
                        p1->left = node;
                        node->balance = 0;
                        node = p1;
                    }
                    else // Двойная RL ротация
                    {
                        p2 = p1->left;
                        p1->left = p2->right;
                        p2->right = p1;
                        node->right = p2->left;
                        p2->left = node;

                        if (p2->balance == 1)
                            node->balance = -1;
                        else
                            node->balance = 0;

                        if (p2->balance == -1)
                            p1->balance = 1;
                        else
                            p1->balance = 0;
                        node = p2;
                    }
                    node->balance = 0;
                    flag = false;
                }
            }
            else
                node->count = node->count + 1;
        }
    }
    else 
    std::cout << "Ошибка входных данных..." << std::endl;
}

// Методы удаления узла по Вирту
void AVLTree_Class::del(Node *&r, bool &flag, Node *&Q)
{
    if (r->left != NULL)
    {
        del(r->left, flag, Q);
        if (flag)
            BalanceL(r, flag);
    }
    else
    {
        Node *q;
        Q->key = r->key;
        Q->count = r->count;
        Q = r;
        q = r;
        r = r->right;
        delete q;
        q = nullptr;
        flag = true;
    }
}

void AVLTree_Class::deleteVirt(Node *&node, Time key, bool &flag)
{
    Node *q;

    if (node == NULL) // Ключа нет в дереве
        return; 
    else if (node->key.hours > key.hours)
    {
        deleteVirt(node->left, key, flag);
        if (flag)
            BalanceL(node, flag);
    }
    else if (node->key.hours < key.hours)
    {
        deleteVirt(node->right, key, flag);
        if (flag)
            BalanceR(node, flag);
    }
    else
    {
        q = node;
        if ((q->right == nullptr) && (q->left != nullptr))
        {
            node = q->left;
            delete q;
            q = nullptr;
            flag = true;
        }
        else if (((q->right != nullptr) || (q->right == nullptr)) && (q->left == NULL))
        {
            node = q->right;
            delete q;
            q = nullptr;
            flag = true;
        }
        else
        {
            del(q->right, flag, q);
            if (flag)
                BalanceR(node, flag);
        }
    }

}

// Метод вывода дерева
void AVLTree_Class::printTree(Node *root)
{
    if (!root) return;

    indents += 5; //Иначе увеличим счетчик рекурсивно вызванных процедур

    //Который будет считать нам отступы для красивого вывода
    printTree(root->right); //Выведем ветку и ее подветки слева

    for (int i = 0; i < indents; i++) std::cout << " "; //Потом отступы

    std::cout << root->key.hours << " [" << root->key.minutes << "]" << std::endl; //Данные этой ветки
    printTree(root->left);//И ветки, что справа
    indents -= 5; //После уменьшим кол-во отступов

    return;
}

// Обход ЛПК
void AVLTree_Class::printLeftRightRoot(Node *&node)
{
    if (node != NULL)
    {
        printLeftRightRoot(node->left);
        printLeftRightRoot(node->right);
        std::cout << node->key.hours << "[" << node->key.minutes << "] ";
    }
}

// Обход КЛП
void AVLTree_Class::printRootLeftRight(Node *&node)
{
    if (node != NULL)
    {
        std::cout << node->key.hours << "[" << node->key.minutes << "] ";
        printRootLeftRight(node->left);
        printRootLeftRight(node->right);
    }
}

// Метод освобождения памяти дерева
void AVLTree_Class::FreeTree(Node *node)
{
    if (!node) return;

    FreeTree(node->left);
    FreeTree(node->right);
    delete node;

    return;
}