/*
file  :  Prim.java
author:  <your name here>
desc. :  this file contains the definition of the Prim class.
         an outline of this algorithm from the Cormen book follows.
         \TODOs: process, getMSTCost

MST-PRIM ( G, w, r )
    1 foreach u in G.V
    2     u.key = inf
    3     u.p = null
    4 r.key = 0
    5 Q = G.V
    6 while !empty( Q )
    7     u = EXTRACT_MIN( Q )
    8     foreach v in G.Adj[ u ]
    9         if v in Q and w(u,v) < v.key
   10             v.p = u
   11             v.key = w(u,v)

Copyright (c) George J. Grevera, 2022.  All rights reserved.
*/
import java.io.File;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Prim {

    public boolean verbose = false;   //turn info messages on/off
    private int    mVertexCount = 0;  //number of nodes/vertices (0..mVertexCount-1)
    private double mW[][];  //matrix of weights:  mW[u][v] = mW[v][u] = weight value for edge (u,v)

    //'new Vertex()' appears below because PriorityQueue needs a comparator
    // and Vertex implements Comparator<Vertex>.
    private PriorityQueue< Vertex > mQ = new PriorityQueue<>( new Vertex() );  //edges sorted by weight
    //the following are subscripted by vertex number (one for each vertex):
    private boolean mIsInQ[];         //is it in the q or not?
    private double  mBestKeyValue[];  //best assigned key value so far
    int[] mBestParent;    //the resulting MST (keep track of best parent)
    private int     mRoot = -1;       //root node
    //-----------------------------------------------------------------------
    //perform initialization/allocation
    private void init ( int vCount, int root ) {
        mVertexCount  = vCount;
        mIsInQ        = new boolean[ mVertexCount ];
        mBestKeyValue = new double[ mVertexCount ];
        mBestParent   = new int[ mVertexCount ];
        //init 1d arrays (in q, best key value, best parent)
        for (int i=0; i < mVertexCount; i++) {
            mIsInQ[i]        = false;
            mBestKeyValue[i] = Float.MAX_VALUE;
            mBestParent[i]   = -1;
        }
        //init 2d matrix of weights
        mW = new double[ mVertexCount ][ mVertexCount ];
        for (int r=0; r < mVertexCount; r++) {
            for (int c=0; c < mVertexCount; c++) {
                mW[r][c] = Float.MAX_VALUE;
            }
        }

        //init queue

        //init root vertex
        assert( 0 <= root && root < mVertexCount);
        mRoot = root;
        Vertex r = new Vertex( root, 0.0, -1 );
        mQ.add( r );
        mIsInQ[ r.getI() ] = true;
        //init the remaining vertices
        for (int i=0; i < mVertexCount; i++) {
            if (i==root)    continue;  //skip root (already added)
            Vertex v = new Vertex( i, Float.MAX_VALUE, -1 );
            mQ.add( v );
            mIsInQ[ v.getI() ] = true;
        }
    }
    //-----------------------------------------------------------------------
    //add the edge  with its weight to the automagically sorted set of edges.
    public void addEdge ( int u, int v, double w ) {
        if (u < 0 || u >= mVertexCount)
        {
            if(verbose)
            {
                System.err.println("Prim:addEdge(u,v,w): bad u " + u + "\n");
                return;
            }
        }
        if (v < 0 || v >= mVertexCount)
        {
            if(verbose)
            {
                System.err.println("Prim:addEdge(u,v,w): bad v " + v + "\n");
                return;
            }
        }
        this.mW[ u ][ v ] = this.mW[ v ][ u ] = w;
    }
    //-----------------------------------------------------------------------
    //ctor which simply sets the numbers of vertices. if you use this, you
    // will have to add edges on your own and one at a time.
    public Prim ( int vCount, int root ) {
        assert( vCount > 0 );
        if (vCount < 1)    return;
        init( vCount, root );
    }
    public Prim ( int vCount ) {
        this( vCount, 0 );
    }
    //-----------------------------------------------------------------------
    //ctor which loads vertices and edges (and their weights) from an input
    // file.
    public Prim ( String fname, int root ) {
        if (verbose)
            System.out.println( "reading input from: " + fname );
        //open the input file
        Scanner in;
        try {
            in = new Scanner( new File(fname) );
        } catch (Exception e) {
            System.err.println( "Prim: can't read input file " + fname );
            System.err.println( "  current dir: " + System.getProperty("user.dir") );
            return;
        }
        //read the number of vertices
        int vertices = in.nextInt();
        //read the number of edges
        int edges = in.nextInt();
        if (verbose)
            System.out.println( "  vertices=" + vertices + ", edges=" + edges );

        init( vertices, root );

        //load the edges and their weights
        for (int i = 0; i < edges; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            double w = in.nextDouble();
            addEdge( u, v, w );
            //print something every once in a while when processing large
            // input files.
            if (verbose && i>0) {
                if (i % 1000000 == 0) {
                    System.out.print( "!" );
                    System.out.flush();
                } else if (i %  100000 == 0) {
                    System.out.print( "*" );
                    System.out.flush();
                } else if (i %   10000 == 0) {
                    System.out.print( "." );
                    System.out.flush();
                }
            }
        }

        in.close();
        if (verbose)
            System.out.println( "finished reading input from: " + fname );
    }
    //-----------------------------------------------------------------------
    public Prim ( String fname ) {
        this( fname, 0 );
    }
    //-----------------------------------------------------------------------
    //(public for testing.)
    //implement the algorithm (lines 6 through 11):
    //     6 while !empty( Q )
    //     7     u = EXTRACT_MIN( Q )
    //     8     foreach v in G.Adj[ u ]
    //     9         if v in Q and w( u, v ) < v.key
    //    10             v.p = u
    //    11             v.key = w( u, v )
    public void process ( )
    {
        assert( 0 <= mRoot && mRoot < mVertexCount);

        while (!mQ.isEmpty()) {
            // Extracting the minimum vertex based on the key value.
            Vertex i = mQ.poll();
            int uIndex = i.getI();
            mIsInQ[uIndex] = false;

            //iterating through all of the vertices
            for (int v = 0; v < mVertexCount; v++) {
                //checking if the vertex is in the queue, and if the weight associated with v is less than the best key value
                if (mIsInQ[v] && mW[uIndex][v] < mBestKeyValue[v])
                {
                    // Update the best parent and key for vertex v
                    mBestKeyValue[v] = mW[uIndex][v];
                    mBestParent[v] = uIndex;

                    //remove and then reinsert vertex to update value
                    mQ.remove(new Vertex(v, mBestKeyValue[v], mBestParent[v]));
                    mQ.add(new Vertex(v, mBestKeyValue[v], mBestParent[v]));
                }
            }
        }
    }
    //-----------------------------------------------------------------------
    // calc and return the sum of edge weights in the MST.
    // hint: see toString.
    public double getMSTCost ( )
    {
        double  sum = 0;

        for (int i = 0; i < mVertexCount; i++)
        {
            //adding the element's best parent only if it exists
            if (mBestParent[i] != -1)
            {
                sum += mBestKeyValue[i]; //adding the sum fom the best key values
            }
        }

        return sum;
    }
    //-----------------------------------------------------------------------
    //returns a string (that is typically printed) that is a pretty-print
    // version of the contents of this object.
    @Override public String toString ( ) {
        String s = "Prim: [";
        s += "root:" + mRoot + ", ";
        //edges
        s += "MSTEdges:[ ";
        for (int i=0; i < this.mVertexCount; i++) {
            if (this.mBestParent[ i ] != -1) {
                s += "(" + i + "," + this.mBestParent[ i ] + "," + this.mBestKeyValue[ i ] + ") ";
            }
        }
        s += "]";

        s += ", MSTCost:" + this.getMSTCost();

        s += "]";
        return s;
    }

}