import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class PrimTest {

    @Test
    public void testMSTCostWithSingleVertex() {
        Prim prim = new Prim(1);
        assertEquals(0.0, prim.getMSTCost(), 0.001);
    }

    @Test
    public void testMSTCostWithNoEdges() {
        Prim prim = new Prim(5);
        assertEquals(0.0, prim.getMSTCost(), 0.001);
    }

    @Test
    public void testMSTCostWithSimpleGraph() {
        Prim p1 = new Prim(5, 2);
        p1.addEdge(0, 1, 2);
        p1.addEdge(0, 2, 4);
        p1.addEdge(1, 2, 1);
        p1.addEdge(1, 3, 5);
        p1.addEdge(2, 3, 3);
        p1.addEdge(2, 4, 6);

        p1.process();


        assertEquals(6.0, p1.getMSTCost(), 0.001);
    }

    @Test
    public void testMSTCostWithDisconnectedGraph() {
        Prim prim = new Prim(5);
        prim.addEdge(0, 1, 2);
        prim.addEdge(1, 2, 3);
        prim.addEdge(3, 4, 4);  // disconnected edge
        prim.process();
        assertEquals(5.0, prim.getMSTCost(), 0.001);
    }

    @Test
    public void testMSTCostWithNegativeWeights() {
        Prim prim = new Prim(3);
        prim.addEdge(0, 1, -2); // negative weight
        prim.addEdge(0, 2, 3);
        prim.addEdge(1, 2, 4);
        prim.process();
        assertEquals(1.0, prim.getMSTCost(), 0.001);
    }

    @Test
    public void testMSTCostWithLargeGraph() {
        // Consider a large graph with 10,000 vertices and 50,000 edges
        Prim prim = new Prim("largeGraph.txt");
        prim.process();
        assertEquals( prim.getMSTCost(), 0.001);
    }
}