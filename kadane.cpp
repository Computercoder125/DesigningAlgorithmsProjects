//file  :  kadane.cpp
//author:  ...
//desc. :  implementation of kadane's linear time max sub array algorithm.
#include <iostream>
#include <limits.h>

using namespace std;

const char* kadSortAuthor = "Sean Gor";
//---------------------------------------------------------------------------
//A[] is an array of deltas.
void kadane(int A[], int N, int& bestStart, int& bestEnd, int& bestSum)
{
    if (A == NULL)
    {
      cout << "Null array." << endl;
      return;
    }
    else if (N < 0)
    {
      cout << "Length is out of bounds." << endl;
      return;
    }
    //keeping track of maxes and temporary start variable
    int maxSoFar = A[0], maxEndingHere = A[0], tempBegin = 0;

    for (int i = 1; i < N; i++) //starting at 1 since the maxes have been assigned to the 1st element
    {
      //checking if an element aleady has the maximum value stored as an integer
      if (A[i] == INT_MAX)
      {
        bestSum = INT_MAX;
        bestStart = i, bestEnd = i;
        return;
      }
      if (A[i] < maxEndingHere + A[i])
      {
        maxEndingHere += A[i]; //updating local max
      }
      else
      {
        maxEndingHere = A[i]; //updating local max and best start if necessary
        tempBegin = i;        //updating a possible start index
      }
      if (maxEndingHere > maxSoFar)
      {
        maxSoFar = maxEndingHere; //updating global max
        bestStart = tempBegin;    //updating start index
        bestEnd = i;              //updating end index
      }
    }
    bestSum = maxSoFar; //assigning the highest Sum to the final global max
}