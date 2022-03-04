#pragma once
#include <iostream>
#include "Flight.h"
using namespace std;

//void insertionSortbyAirline(flight arr[], int n)
//{
//    for (int i = 1; i < n; i++)
//        for (int j = i; j > 0 && arr[j - 1].airline > arr[j].airline; j--)
//            swap(arr[j - 1], arr[j]);
//}

void insertionSort(flight arr[], int n)
{
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0; j--)
            if (arr[j - 1].time.hour > arr[j].time.hour)
                swap(arr[j - 1], arr[j]);
            else if (arr[j - 1].time.hour == arr[j].time.hour)
                if (arr[j - 1].time.minutes > arr[j].time.minutes)
                    swap(arr[j - 1], arr[j]);
                else if (arr[j - 1].time.minutes == arr[j].time.minutes)
                    if (arr[j - 1].airline > arr[j].airline)
                        swap(arr[j - 1], arr[j]);
}
