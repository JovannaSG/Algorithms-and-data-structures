//#include <iostream>
//using namespace  std;
//
//int indents = 0;
//bool flag;
//
//struct Node
//{
//	int key;
//	int count;
//	int balance; // -1, 0, 1
//	Node *left;
//	Node *right;
//};
//
//void insertVirt(Node *node, int key, bool &flag)
//{
//    Node *p1, *p2;
//
//    // Находим место вставки
//    if (node == NULL)
//    {
//        Node *node = new Node();
//        node->key = key;
//        node->left = NULL;
//        node->right = NULL;
//        node->count = 1;
//        node->balance = 0;
//    }
//    else if (node->key > key)
//    {
//        insertVirt(node, key, flag);
//        if (flag) // Выросла левая ветвь
//        {
//            if (node->balance == 1)
//            {
//                node->balance = 0;
//                flag = false;
//            }
//            else if (node->balance == 0)
//            {
//                node->balance = -1;
//            }
//            else // balance == -1, балансируем
//            {
//                p1 = node->left;
//                if (node->balance == -1) // Одиночная LL ротация
//                {
//                    node->left = p1->right;
//                    p1->right = node;
//                    node->balance = 0;
//                    node = p1;
//                }
//                else // Двойная LR ротация
//                {
//                    p2 = p1->right;
//                    p1->right = p2->left;
//                    p2->left = p1;
//                    node->left = p2->right;
//                    p2->right = node;
//
//                    if (p2->balance == -1)
//                        node->balance = 1;
//                    else
//                        node->balance = 0;
//
//                    if (p2->balance == 1)
//                        p1->balance = -1;
//                    else
//                        p1->balance = 0;
//                    node = p2;
//                }
//                node->balance = 0;
//                flag = false;
//            }
//        }
//    }
//    else if (node->key < key)
//    {
//        insertVirt(node, key, flag);
//        if (flag) // Выросла правая ветвь
//        {
//            if (node->balance == -1)
//            {
//                node->balance = 0;
//                flag = false;
//            }
//            else if (node->balance == 0)
//            {
//                node->balance = 1;
//            }
//            else // balance == 1, балансируем
//            {
//                p1 = node->right;
//                if (p1->balance == 1) // Одиночная RR ротация
//                {
//                    node->right = p1->left;
//                    p1->left = node;
//                    node->balance = 0;
//                    node = p1;
//                }
//                else // Двойная RL ротация
//                {
//                    p2 = p1->left;
//                    p1->left = p2->right;
//                    p2->right = p1;
//                    node->right = p2->left;
//                    p2->left = node;
//
//                    if (p2->balance == 1)
//                        node->balance = -1;
//                    else
//                        node->balance = 0;
//
//                    if (p2->balance == -1)
//                        p1->balance = 1;
//                    else
//                        p1->balance = 0;
//                    node = p2;
//                }
//                node->balance = 0;
//                flag = false;
//            }
//        }
//        else
//            node->count = node->count + 1;
//    }
//
//}
//
//void printTree(Node *root)
//{
//    if (!root) return;
//
//     indents += 5; //Иначе увеличим счетчик рекурсивно вызванных процедур
//
//    //Который будет считать нам отступы для красивого вывода
//    printTree(root->right); //Выведем ветку и ее подветки слева
//
//    for (int i = 0; i < indents; i++) std::cout << " "; //Потом отступы
//
//    std::cout << root->key << "[" << root->balance << "]" << std::endl; //Данные этой ветки
//    printTree(root->left);//И ветки, что справа
//    indents -= 5; //После уменьшим кол-во отступов
//
//    return;
//}
//
//
//int main()
//{
//    Node *root = nullptr;
//
//    insertVirt(root, 3, flag);
//    insertVirt(root, 4, flag);
//    insertVirt(root, 5, flag);
//    insertVirt(root, 2, flag);
//
//    printTree(root);
//
//	return 0;
//}