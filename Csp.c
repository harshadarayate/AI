#include <stdio.h>
#include <stdbool.h>

#define N 5      // Number of nodes (0 to 4)
#define COLORS 3 // Number of colors (1,2,3)

// Graph as adjacency matrix (1=adjacent, 0=not)
int graph[N][N] = {
    {0, 1, 1, 0, 0}, // Node 0 connected to 1,2
    {1, 0, 1, 1, 0}, // Node 1 to 0,2,3
    {1, 1, 0, 1, 0}, // Node 2 to 0,1,3
    {0, 1, 1, 0, 1}, // Node 3 to 1,2,4
    {0, 0, 0, 1, 0}  // Node 4 to 3
};

int color[N]; // color[i] = color of node i (0=uncolored)

// Check if safe to assign color 'c' to node 'v'
bool is_safe(int v, int c)
{
    for (int i = 0; i < N; i++)
    {
        if (graph[v][i] && color[i] == c)
        {
            return false; // Adjacent node has same color
        }
    }
    return true;
}

// Recursive backtracking: Try to color node 'v'
bool solve(int v)
{
    if (v == N)
        return true; // All nodes colored

    for (int c = 1; c <= COLORS; c++)
    { // Try colors 1 to 3
        if (is_safe(v, c))
        {
            color[v] = c;
            if (solve(v + 1))
                return true; // Recurse to next node
            color[v] = 0;    // Backtrack: Remove color
        }
    }
    return false; // No color works
}

int main()
{
    if (solve(0))
    { // Start coloring from node 0
        printf("Graph Coloring Solution:\n");
        for (int i = 0; i < N; i++)
        {
            printf("Node %d: Color %d\n", i, color[i]);
        }
    }
    else
    {
        printf("No solution exists with %d colors!\n", COLORS);
    }
    return 0;
}