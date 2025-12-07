#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

int graph[MAX][MAX];
int visited[MAX];

void enqueue(int vertex)
{
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    rear++;
    queue[rear] = vertex;
}

int dequeue()
{
    if (front == -1 || front > rear)
        return -1;
    int val = queue[front];
    front++;
    return val;
}

void bfs(int start, int nodes)
{
    enqueue(start);
    visited[start] = 1;

    while (front <= rear)
    {
        int current = dequeue();
        printf("Visited node: %d\n", current);

        for (int i = 0; i < nodes; i++)
        {
            if (graph[current][i] == 1 && !visited[i])
            {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}
int main()
{
    int nodes, edges;
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

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
        graph[to][from] = 1;
    }

    int start;
    printf("Enter starting node for BFS: ");
    scanf("%d", &start);

    printf("\nBreadth-First Search (BFS) Traversal:\n");
    bfs(start, nodes);

    return 0;
}
