#pragma once

struct Time
{
    int hours;
    int minutes;

    Time()
    {
        hours = -1;
        minutes = -1;
    }
};

class Node
{
public:
    Time key;
    int balance;
    int count;
    Node *left;
    Node *right;
    int height;

    Node(Time key = Time(),
        Node *left = nullptr, 
        Node *right = nullptr, 
        int height = 1, 
        int count = 1, 
        int balance = 0)
    {
        this->key = key;
    }
};