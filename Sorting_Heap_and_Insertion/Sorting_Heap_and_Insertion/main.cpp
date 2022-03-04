#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <time.h>

#include "Flight.h"
#include "HeapSort.h"
#include "InsertionSort.h"
using namespace std;


int main()
{
    fstream in("input.txt");
    ofstream out("output.txt");
    string line;
    int n;
    in >> n;
    flight* fl = new flight[n];

    //Get info from file
    getline(in, line);
    for (int i = 0; i < n; i++)
    {
        in >> fl[i].time.hour;
        in >> fl[i].time.minutes;
        in >> fl[i].airline;
        in >> fl[i].nflight;
        in >> fl[i].airport;
    }

    //Start Duration
    auto begin = chrono::steady_clock::now();

    //Write Type of Sort
    insertionSort(fl, n);

    //Calculate Duration 
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);


    //Write in file  
    out << "Duration: " << elapsed_ms.count() << "ms" << endl;
    out << "Time \t Airline \t Flight \t Airport" << endl;

    for (int i = 0; i < n; i++)
    {
        out << fl[i].time.hour << ":" << fl[i].time.minutes << "\t "
            << fl[i].airline << "\t\t "
            << fl[i].nflight << "\t\t "
            << fl[i].airport << endl;
    }

    in.close();


    // Generation input file in input.txt
    ofstream in1("input.txt");
    srand(time(NULL));
    in1 << n << endl;
    for (int i = 0; i < n; i++)
    {
        in1 << rand() % 24 << " "  // hour
            << rand() % 60 << " "  // minutes 
            << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << " "      // Airline 
            << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << rand() % 10000 << " "                         // Flight
            << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << endl;    // Airport
    }

    out.close();
    in1.close();
    cout << "End of program" << endl;
    return 0;
}