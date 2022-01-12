#pragma once
// Двухсвязный_кольцевой_список.cpp : Этот файл содержит функцию "main"
// Задание: написать функции
// функция добавления в начало списка
// функция добавления и удаления перед каждым положительным
// функция удаление заданного элемента
// функция поиска по номеру

using namespace std;

template<typename T>
class List
{
public:
    List();

    void push_top(T data);
    bool del_specified(T data);

    void print();
    int searchByIndex(int index);

    int getSize();

    bool add_before_positive(T data);
    bool del_before_positive();

private:

    template<typename T>
    class Node
    {
    public:
        Node *pNext;
        Node *pPrev;
        T data;

        Node(T data = T(), Node *pNext = nullptr, Node *pPrev = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };

    Node<T> *head;
};

template<typename T>
List<T>::List()
{
    head = nullptr;
}

template<typename T>
void List<T>::push_top(T data)
{
    Node<T> *current = new Node<T>(data);

    if (head == nullptr)
    {
        head = current;
        head->pNext = head;
        head->pPrev = head;
    }
    else if (head->pNext == head && head->pPrev == head)
    {
        head->pNext = current;
        current->pPrev = head;

        current->pNext = head;
        head->pPrev = current;

        head = current;
    }
    else
    {
        head->pNext->pPrev = current;
        current->pNext = head->pNext;

        head->pNext = current;
        current->pPrev = head;

        head = current;
    }
}

template<typename T>
bool List<T>::del_specified(T data)
{
    Node<T> *current = head;

    if (current != nullptr)
    {
        if (head->data == data)
        {
            Node<T> *right = head->pNext;

            head->pPrev->pNext = right;
            right->pPrev = head->pPrev;

            delete head;

            head = right;

            return true;
        }
        else
        {
            do
            {
                current = current->pPrev;
            } while (current->data != data && current != head);

            if (current != head)
            {
                Node<T> *right = current->pNext;

                current->pPrev->pNext = right;
                right->pPrev = current->pPrev;

                delete current;

                return true;
            }
            else
                return false;
        }
    }
    else
        return false;
}

template<typename T>
void List<T>::print()
{
    Node<T> *current = head;

    if (current != nullptr)
    {
        do
        {
            cout << current->data << endl;
            current = current->pPrev;
        } while (current != head);
    }
    else
        cout << "Список пуст" << endl;
}

template<typename T>
int List<T>::searchByIndex(int index)
{
    Node<T> *current = head;
    int curindex = 1;

    if (index > 0 && index <= getSize() + 1)
    {
        while (curindex != index)
        {
            current = current->pPrev;
            curindex++;
        }

        return current->data;
    }
    else
        return -1;
}

template<typename T>
int List<T>::getSize()
{
    Node<T> *current = head;
    int size = 0;

    if (current != nullptr)
    {
        do
        {
            size += 1;
            current = current->pNext;
        } while (current != head);

        return size;
    }
    else
        return -1;
}

template<typename T>
bool List<T>::add_before_positive(T data)
{
    Node<T> *current = head;

    if (current != nullptr)
    {
        do
        {
            if (current->data > 0)
            {
                Node<T> *newNode = new Node<T>(data);

                current->pNext->pPrev = newNode;
                newNode->pNext = current->pNext;

                current->pNext = newNode;
                newNode->pPrev = current;

                current = current->pNext->pNext;
            }
            else
                current = current->pNext;

        } while (current != head);

        return true;
    }
    else
        return false;
}

template<typename T>
bool List<T>::del_before_positive()
{
    Node<T> *current = head;

    if (head != nullptr)
    {
        do
        {
            if (current->data > 0)
            {
                if (current->pPrev == head)
                {
                    Node<T> *left = current->pPrev;

                    left->pPrev->pNext = current;
                    current->pPrev = left->pPrev;

                    head = current;

                    delete left;
                }
                else
                {
                    Node<T> *left = current->pPrev;

                    left->pPrev->pNext = current;
                    current->pPrev = left->pPrev;

                    delete left;
                }
            }
            current = current->pNext;

        } while (current != head);

        return true;
    }
    else
        return false;
}
