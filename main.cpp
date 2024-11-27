// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

// author: ...
// desc. : this file contains code that exercises the functions:
//         bruteForce_n2, find_maximum_subarray, and kadane.
//
#include <iostream>
#include <limits.h>

extern void bruteForce_n2(int A[], int N, int& bestStart, int& bestEnd, int& bestSum);

extern void find_maximum_subarray(int A[], int N, int& bestStart, int& bestEnd, int& bestSum);

//to make things simpler for kadane:
extern void kadane(int A[], int N, int& bestStart, int& bestEnd, int& bestSum);

using namespace std;
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    //test case
    int n = 0;

    int test[] = { -1, -2, 3, -4, -5, 10 };
    
    //computing array length
    for (int i : test)
    {
      n++;
    }
    
    int bestStart = INT_MAX, bestEnd = INT_MAX, bestSum = INT_MAX;

    //three methods to be run:
   
    //bruteForce_n2(test, n, bestStart, bestEnd, bestSum);

    //find_maximum_subarray(test, n, bestStart, bestEnd, bestSum);

     //kadane(test, n, bestStart, bestEnd, bestSum);
    
    //output necessary info
    cout << "Best Start = " << bestStart << ", ";

    cout << "Best End = " << bestEnd <<", ";

    cout << "Best Sum = " << bestSum << endl;
   
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
