#pragma once
#include <iostream>
#include "Flight.h"
using namespace std;

void heapify(flight arr[], int n, int i)
{
    int max = i; // Initialize max as root
    int l = 2 * i + 1; // left
    int r = 2 * i + 2; // right

    if (l < n && arr[l].time.hour > arr[max].time.hour)
        max = l;
    else if (l < n && arr[l].time.hour == arr[max].time.hour)
        if (arr[l].time.minutes > arr[max].time.minutes)
            max = l;
        else if (arr[l].time.minutes == arr[max].time.minutes)
            if (arr[l].airline > arr[max].airline)
                max = l;

    if (r < n && arr[r].time.hour > arr[max].time.hour)
        max = r;
    else if (r < n && arr[r].time.hour == arr[max].time.hour)
        if (arr[r].time.minutes > arr[max].time.minutes)
            max = r;
        else if (arr[r].time.minutes == arr[max].time.minutes)
            if (arr[r].airline > arr[max].airline)
                max = r;

    // If max is not root
    if (max != i)
    {
        swap(arr[i], arr[max]);

        // Recursively heapifybyAirline the affected sub-tree
        heapify(arr, n, max);
    }
}

void heapSort(flight arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapifybyAirline on the reduced heap
        heapify(arr, i, 0);
    }
}


//
//
//void heapifybyAirline(flight arr[], int n, int i)
//{
//    int max = i; // Initialize max as root
//    int l = 2 * i + 1; // left
//    int r = 2 * i + 2; // right
//
//    // If left child is larger than root
//    if (l < n && arr[l].airline > arr[max].airline)
//        max = l;
//
//    // If right child is larger than max so far
//    if (r < n && arr[r].airline > arr[max].airline)
//        max = r;
//
//    // If max is not root
//    if (max != i)
//    {
//        swap(arr[i], arr[max]);
//
//        // Recursively heapifybyAirline the affected sub-tree
//        heapifybyAirline(arr, n, max);
//    }
//}
//
//void heapSortbyAirline(flight arr[], int n)
//{
//    // Build heap (rearrange array)
//    for (int i = n / 2 - 1; i >= 0; i--)
//        heapifybyAirline(arr, n, i);
//
//    // One by one extract an element from heap
//    for (int i = n - 1; i >= 0; i--)
//    {
//        // Move current root to end
//        swap(arr[0], arr[i]);
//        // call max heapifybyAirline on the reduced heap
//        heapifybyAirline(arr, i, 0);
//    }
//}