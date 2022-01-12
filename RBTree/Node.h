#pragma once

// Black it's white
enum class Color { Red = 4, White = 15 };

struct Time
{
public:
    int hour;
    int minutes;

    Time(int hour = -1, int minutes = -1)
    {
        this->hour = hour;
        this->minutes = minutes;
    }
};

class Node
{
public:
    Color color;
    Node *parent;
    Node *leftchild;
    Node *rightchild;
    Time key;

    // A tree node that contains: pointers to the left and right child, parent, key, node color
    Node(Time key = Time(),
         Node *parent = nullptr,
         Node *leftchild = nullptr,
         Node *rightchild = nullptr,
         Color color = Color::Red)
    {
        this->key = key;
        this->parent = parent;
        this->leftchild = leftchild;
        this->rightchild = rightchild;
        this->color = color;
    }
};
