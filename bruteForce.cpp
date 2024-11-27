// file  : bruteForce.cpp
// author: ...
// desc. : this file contains brute force implementations for the max sub
//         array problem in N^2.
//
#include <ioStream>
#include <limits.h> //needed for the INT_MIN sentinel value
using namespace std;
const char* bruAuthor = "Sean Gor";
//---------------------------------------------------------------------------
//A[] is an array of deltas.
void bruteForce_n2(int A[], int N, int& bestStart, int& bestEnd, int& bestSum)
{
    bestSum = INT_MIN;
    
    //checking if an array is null or empty and handling it gracefully
    if (A == NULL)
    {
      cout << "Null array." << endl;
      return;
    }
    //outer loop 
    for (int i = 0; i < N; i++)
    {
      int sum = 0;
      //inner loop
      for (int j = i; j < N; j++)
      {
        //checking if an element already has INT_MAX as its value 
        if (A[j] == INT_MAX)
        {
          bestSum = A[j];
          bestStart = j;
          bestEnd = j;
          return;
        }
        sum += A[j];
        if (sum > bestSum) //updating the highest sum, start and end if the current sum is greater than the previous one
        {
          bestSum = sum;
          bestStart = i;
          bestEnd = j;
        }
      }
    }
}
