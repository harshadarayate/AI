#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int stack[MAX];
int top = -1;

int graph[MAX][MAX];
int visited[MAX];
void push(int vertex)
{
    if (top == MAX - 1)
        return;
    top++;
    stack[top] = vertex;
}
int pop()
{
    if (top == -1)
        return -1;
    int val = stack[top];
    top--;
    return val;
}

void dfs(int start, int nodes)
{
    push(start);
    visited[start] = 1;
    printf("Visited node: %d\n", start);
    while (top != -1)
    {
        int current = stack[top];
        int found = 0;

        for (int i = 0; i < nodes; i++)
        {
            if (graph[current][i] == 1 && !visited[i])
            {
                push(i);
                visited[i] = 1;
                printf("Visited node: %d\n", i);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            pop();
        }
    }
}

int main()
{
    int nodes, edges, isDirected;
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Is the graph directed? (1 for Yes, 0 for No): ");
    scanf("%d", &isDirected);

    for (int i = 0; i < nodes; i++)
        visited[i] = 0;
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            graph[i][j] = 0;
    printf("Enter edges (from to):\n");
    for (int i = 0; i < edges; i++)
    {
        int from, to;
        scanf("%d%d", &from, &to);
        graph[from][to] = 1;
        if (!isDirected)
            graph[to][from] = 1;
    }
    int start;
    printf("Enter starting node for DFS: ");
    scanf("%d", &start);
    printf("\nDepth-First Search (DFS) Traversal:\n");
    dfs(start, nodes);
    return 0;
}