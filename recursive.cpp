// file  : recursive.cpp
// author: ...
// desc. : this file contains the entry point (and helper functions) for 
//         the recursive max subarray problem/solution.
#include <iostream>
#include <limits.h>

using namespace std;

const char* recAuthor = "Sean Gor";

static int find_max_subarray(int A[], int low, int high, int& bestStart, int& bestEnd);

static int find_Max_Crossing_Subarray(int A[], int low, int  mid, int high, int& bestStart, int& bestEnd);
//---------------------------------------------------------------------------
//.
//. //(insert helper function(s) here, if any.they should all be static.)
//. 
//---------------------------------------------------------------------------
//A[] is an array of deltas.
void find_maximum_subarray(int A[], int N, int& bestStart, int& bestEnd, int& bestSum) 
{
    int maxSum = find_max_subarray(A, 0, N-1, bestStart, bestEnd);
    bestSum = maxSum; //bestSum is the highest overall computed sum 
}
static int find_max_subarray(int A[], int low, int high, int& bestStart, int& bestEnd)
{
    if (A == NULL)
    {
      cout << "Null array." << endl;
      return INT_MIN;
    }
    //check if an element is the maximum value for an integer, and return that as the sum if true
    else if (A[low] == INT_MAX)
    {
      bestStart = low, bestEnd = low;
      return A[low];
    }
    else if (A[high] == INT_MAX)
    {
      bestStart = high, bestEnd = high;
      return A[high];
    }
    //swapping low and high values if low passed in is > high
    else if (low > high)
    {
      int temp = low; //temp has original value
      low = high;
      high = temp;
    }
    if (low < high)
    {
      int mid = (low + high) / 2; //calculating min
        
      int leftStart, leftEnd, rightStart, rightEnd, crossStart, crossEnd;
        
      int leftSum = find_max_subarray(A, low, mid, leftStart, leftEnd); //finding the best sum, start and end in left half

      int rightSum = find_max_subarray(A, mid + 1, high, rightStart, rightEnd); //finding the best sum, start and end in right half

      int crossSum = find_Max_Crossing_Subarray(A, low, mid, high, crossStart, crossEnd); //finding the best crossing sum, start and end

      //finds the greatest sum out of the left, right and end and returns that sum
      if (leftSum > rightSum && leftSum > crossSum)
      {
        bestStart = leftStart;
        bestEnd = leftEnd;
        return leftSum;
      }
      else if (rightSum > leftSum && rightSum > crossSum)
      {   
        bestStart = rightStart;
        bestEnd = rightEnd;
        return rightSum;
      }
      //if program reaches this point it means crossSum is the highest
      bestStart = crossStart;
      bestEnd = crossEnd;
      return crossSum;
    }
    //base case result in the instance of low = high
    bestStart = low;
    bestEnd = high;
    return A[low];
}

static int find_Max_Crossing_Subarray(int A[], int low, int mid, int high, int& bestStart, int& bestEnd)
{
    int left_sum = INT_MIN;

    int sum = 0;

    int max_left = 0;

    //finding max Sum in left half
    for (int i = mid; i >= low; i--)
    {
      sum += A[i];
      if (sum > left_sum)
      {
        left_sum = sum;
        max_left = i;
      }
    }
    int max_right = 0;
    
    int right_sum = INT_MIN;  
    
    sum = 0; 

    //finding the max sum in right half
    for (int j = mid + 1; j <= high; j++)
    {
      sum += A[j];
      if (sum > right_sum)
      {
        right_sum = sum;
        max_right = j;
      }
    }
    
    bestStart = max_left;
    
    bestEnd = max_right;
    
    return left_sum + right_sum; //returning the combination of the left and right sum (ie. the cross sum)
}

