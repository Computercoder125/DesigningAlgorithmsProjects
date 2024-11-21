//file:   graphUtes.cpp
//author: Sean Gor
//desc.:  graph processing utilities

#include <iostream>  //optional
#include <stack> // for stack to be used
using namespace std; 

#define N 100  //max no. of nodes in graph
//----------------------------------------------------------------------
// This function returns true if G has at least one self loop; false
// otherwise.
bool hasSelfLoops(bool G[N][N]) 
{
    //checking for edge cases
    if (G == NULL || N < 1)
    {
      return false;
    }
    for (int i = 0; i < N; i++)
    {
      if (G[i][i])
      {
        return true;
      }
    }
    return false;
}
//----------------------------------------------------------------------
// This function returns true if G is empty (null graph); false otherwise.
bool isEmpty(bool G[N][N]) 
{
    //checking for edge cases
    if (G == NULL || N < 1)
    {
      return true;
    }
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        if (G[i][j]) //this means that the graph has an edge from i to j, and is therefore not empty
        {
          return false;
        }
      }
    }
    return true;
}
//----------------------------------------------------------------------
// Define a digraph as a graph that has at least one asymmetry (i.e., it 
// contains at least one edge  but no corresponding edge 
// . (By this definition, a null or empty graph is not a 
// digraph, and a graph that only contains self loops is also not a 
// digraph.)
//
// This function returns true if the graph G is a digraph; false otherwise.
bool isDigraph(bool G[N][N])
{
    //checking for edge cases
    if (N < 1 || G == NULL)
    {
      cout << "Invalid length" << endl;
      return false;
    }

    if (G == NULL)
    {
      return false;
    }

    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        if (G[i][j]) //graph must have at least one edge to be considered
        {
          if (!(G[j][i]) && j != i) //graph is a digraph if it has an edge that is not symmetric and a non-self connection
          {
            return true;
          }
        }
      }
    }
    return false;
}
//----------------------------------------------------------------------
// This function returns true if the graph G contains at least one cycle;
// false otherwise.
// (You are not required to output any or all of the cycles; you are not
// required to count them.)
bool hasCycle(bool G[N][N]) 
{
    //checking for edge cases
    if (N < 1 || G == NULL)
    {
      return false;
    }
    else if (G == NULL)
    {
      return false;
    }
    
    bool visited[N] = {}; //keeping track of visited nodes

    for (int i = 0; i < N; i++)
    {
      visited[i] = false;
    }
    
    bool recursiveStack[N] = {};  // Keeping track of recursed nodes

    for (int i = 0; i < N; i++)
    {
      recursiveStack[i] = false;
    }
    
    for (int i = 0; i < N; ++i) {
      if (!visited[i]) {
        stack<int> Nodes; //stack which contains the processed Nodes
        Nodes.push(i); 

        while (!Nodes.empty()) 
        {
          int node = Nodes.top();

          if (!visited[node])  //checking if the index of the top element of the stack is visited
          {
            visited[node] = true;
            recursiveStack[node] = true;
          }
          else 
          {
            recursiveStack[node] = false;
            Nodes.pop(); 
            continue;
          }

          for (int v = 0; v < N; ++v) 
          {
            if (G[node][v]) 
            { 
              if (!visited[v]) //meaning that the Node was already visited
              {
                 Nodes.push(v); 
              }
              else if (recursiveStack[v]) { 
                 return true;
              }
            }
          }
        }
      }
    }
    return false;
}
