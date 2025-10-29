#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define N 6
#define INF 99999 // Represents no edge

// Global arrays for the algorithm
int g[N];        // g_score: cost from start to node
int parent[N];   // Parent pointers for path
int open_set[N]; // Open set (nodes to explore)
int open_size;   // Size of open_set
bool in_open[N]; // Flag: node in open set?
bool closed[N];  // Flag: node already processed?

int graph[N][N];        // Adjacency matrix: graph[u][v] = weight
int x_pos[N], y_pos[N]; // Positions for heuristic

// Heuristic: Manhattan distance from node u to goal
double heuristic(int u, int goal)
{
    return fabs(x_pos[u] - x_pos[goal]) + fabs(y_pos[u] - y_pos[goal]);
}

// Find node in open_set with minimum f = g[u] + h(u)
int find_min_f(int goal)
{
    int min_node = -1;
    double min_f = 10000; // Large number
    for (int i = 0; i < open_size; i++)
    {
        int u = open_set[i];
        if (closed[u])
            continue; // Skip processed nodes
        double f = g[u] + heuristic(u, goal);
        if (f < min_f)
        {
            min_f = f;
            min_node = u;
        }
    }
    return min_node;
}

// Main A* function
void a_star(int start, int goal)
{
    // Initialize arrays
    for (int i = 0; i < N; i++)
    {
        g[i] = INF;
        parent[i] = -1;
        closed[i] = false;
        in_open[i] = false;
    }
    g[start] = 0;
    open_size = 0;
    open_set[open_size++] = start;
    in_open[start] = true;

    while (open_size > 0)
    {
        int current = find_min_f(goal);
        if (current == -1)
            break; // No path

        // Remove current from open_set
        for (int i = 0; i < open_size; i++)
        {
            if (open_set[i] == current)
            {
                open_set[i] = open_set[--open_size];
                break;
            }
        }
        in_open[current] = false;
        closed[current] = true;

        if (current == goal)
            break; // Found goal

        // Explore neighbors
        for (int v = 0; v < N; v++)
        {
            if (graph[current][v] == INF)
                continue; // No edge
            int tent_g = g[current] + graph[current][v];
            if (closed[v])
                continue; // Already processed
            if (tent_g < g[v])
            { // Better path
                g[v] = tent_g;
                parent[v] = current;
                if (!in_open[v])
                { // Add to open if not there
                    open_set[open_size++] = v;
                    in_open[v] = true;
                }
            }
        }
    }
}

// Print the path and cost
void print_path(int goal)
{
    if (g[goal] == INF)
    {
        printf("No path found!\n");
        return;
    }
    int path[N];
    int len = 0;
    int cur = goal;
    while (cur != -1)
    {
        path[len++] = cur;
        cur = parent[cur];
    }
    printf("Path: ");
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%d ", path[i]);
    }
    printf("\nTotal Cost: %d\n", g[goal]);
}

int main()
{
    // Initialize graph (sample chain: 0-1-2-3-4-5)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            graph[i][j] = INF;
        }
    }
    // Add edges (bidirectional)
    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 8;
    graph[2][3] = graph[3][2] = 3;
    graph[3][4] = graph[4][3] = 5;
    graph[4][5] = graph[5][4] = 70;
    // graph[0][3] = graph[3][0] = 3;   //for testing

    // Assign positions (simple grid for heuristic)
    for (int i = 0; i < N; i++)
    {
        x_pos[i] = i % 3;
        y_pos[i] = i / 3;
    }

    // Run A* from 0 to 5
    printf("A* Shortest Path (Start 0 to Goal 5)\n");
    a_star(0, 5);
    print_path(5);

    return 0;
}