#include <stdio.h>
#include <stdlib.h>

#define SIZE 3 


typedef struct
{
    int pos;     
    int f, g, h; 
    int parent;  
} Cell;

int grid[SIZE][SIZE];               
int visited[SIZE * SIZE];           
Cell open_list[SIZE * SIZE];        
int open_count = 0;                 // Open list size
int moves[] = {-SIZE, 1, SIZE, -1}; // Up, right, down, left

void pos_to_rowcol(int pos, int *row, int *col)
{
    *row = (pos - 1) / SIZE;
    *col = (pos - 1) % SIZE;
}

int rowcol_to_pos(int row, int col)
{
    return row * SIZE + col + 1;
}

int manhattan_distance(int pos1, int pos2)
{
    int r1, c1, r2, c2;
    pos_to_rowcol(pos1, &r1, &c1);
    pos_to_rowcol(pos2, &r2, &c2);
    return abs(r1 - r2) + abs(c1 - c2);
}

int is_valid(int pos)
{
    int row, col;
    pos_to_rowcol(pos, &row, &col);
    return pos >= 1 && pos <= SIZE * SIZE && row >= 0 && row < SIZE &&
           col >= 0 && col < SIZE && grid[row][col] == 1 && !visited[pos - 1];
}

void add_to_open(int pos, int g, int h, int parent)
{
    open_list[open_count].pos = pos;
    open_list[open_count].g = g;
    open_list[open_count].h = h;
    open_list[open_count].f = g + h;
    open_list[open_count].parent = parent;
    open_count++;
}

Cell get_best_node()
{
    int min_f = 1000, min_idx = 0; 
    for (int i = 0; i < open_count; i++)
    {
        if (open_list[i].f < min_f)
        {
            min_f = open_list[i].f;
            min_idx = i;
        }
    }
    Cell best = open_list[min_idx];
    for (int i = min_idx; i < open_count - 1; i++)
    {
        open_list[i] = open_list[i + 1];
    }
    open_count--;
    return best;
}

void print_grid(int sr, int sc, int dr, int dc)
{
    printf("\nGrid (S=start, G=goal, #=blocked, *=path):\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == sr && j == sc)
                printf("S ");
            else if (i == dr && j == dc)
                printf("G ");
            else if (grid[i][j] == 0)
                printf("# ");
            else if (grid[i][j] == 2)
                printf("* ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

void trace_path(Cell cellDetails[SIZE * SIZE], int goal_pos)
{
    printf("Path is: ");
    int path[SIZE * SIZE][2], length = 0;
    int pos = goal_pos;
    while (pos != -1)
    {
        int row, col;
        pos_to_rowcol(pos, &row, &col);
        path[length][0] = row;
        path[length][1] = col;
        length++;
        pos = cellDetails[pos - 1].parent;
    }
    for (int i = length - 1; i >= 0; i--)
    {
        printf("-> (%d,%d) ", path[i][0], path[i][1]);
    }
    printf("\n");
}
//a star logic
void aStarSearch(int start_pos, int goal_pos)
{
    int sr, sc, dr, dc;
    pos_to_rowcol(start_pos, &sr, &sc);
    pos_to_rowcol(goal_pos, &dr, &dc);
    if (sr < 0 || sr >= SIZE || sc < 0 || sc >= SIZE ||
        dr < 0 || dr >= SIZE || dc < 0 || dc >= SIZE)
    {
        printf("Invalid source or destination\n");
        return;
    }
    if (grid[sr][sc] == 0 || grid[dr][dc] == 0)
    {
        printf("Source or destination is blocked\n");
        return;
    }
    if (start_pos == goal_pos)
    {
        printf("Already at destination!\n");
        return;
    }

    Cell cellDetails[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        cellDetails[i].f = 1000; 
        cellDetails[i].g = 1000;
        cellDetails[i].h = 1000;
        cellDetails[i].parent = -1;
    }

    cellDetails[start_pos - 1].f = 0;
    cellDetails[start_pos - 1].g = 0;
    cellDetails[start_pos - 1].h = manhattan_distance(start_pos, goal_pos);
    cellDetails[start_pos - 1].parent = -1;
    add_to_open(start_pos, 0, manhattan_distance(start_pos, goal_pos), -1);
    visited[start_pos - 1] = 1;

    // A* loop
    while (open_count > 0)
    {
        Cell current = get_best_node();
        int pos = current.pos;
        if (pos == goal_pos)
        {
            
            int p = pos;
            while (p != start_pos)
            {
                int row, col;
                pos_to_rowcol(p, &row, &col);
                if (p != goal_pos)
                    grid[row][col] = 2; 
                p = cellDetails[p - 1].parent;
            }
            print_grid(sr, sc, dr, dc);
            trace_path(cellDetails, goal_pos);
            return;
        }

        // Check(up, right, down, left)
        for (int i = 0; i < 4; i++)
        {
            int new_pos = pos + moves[i];
            if (is_valid(new_pos))
            {
                visited[new_pos - 1] = 1;
                int g_new = current.g + 1;
                int h_new = manhattan_distance(new_pos, goal_pos);
                int f_new = g_new + h_new;
                if (cellDetails[new_pos - 1].f == 1000 || cellDetails[new_pos - 1].f > f_new)
                {
                    add_to_open(new_pos, g_new, h_new, pos);
                    cellDetails[new_pos - 1].f = f_new;
                    cellDetails[new_pos - 1].g = g_new;
                    cellDetails[new_pos - 1].h = h_new;
                    cellDetails[new_pos - 1].parent = pos;
                }
            }
        }
    }
    printf("No path found\n");
}


int main()
{
    int start_pos, goal_pos, obstacles;

    //  grid initialization where (1=free, 0=blocked)
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j] = 1;
            visited[i * SIZE + j] = 0;
        }
    }

    printf("A* Pathfinding on a 3x3 Grid\n");
    printf("Use numbers 1-9 (1=top-left, 9=bottom-right):\n");
    printf(" 1 2 3\n");
    printf(" 4 5 6\n");
    printf(" 7 8 9\n\n");

  
    printf("Enter start position (1-9): ");
    scanf("%d", &start_pos);
    while (start_pos < 1 || start_pos > SIZE * SIZE)
    {
        printf("Invalid! Enter 1-9: ");
        scanf("%d", &start_pos);
    }

  
    printf("Enter goal position (1-9): ");
    scanf("%d", &goal_pos);
    while (goal_pos < 1 || goal_pos > SIZE * SIZE || goal_pos == start_pos)
    {
        printf("Invalid! Enter 1-9, not start: ");
        scanf("%d", &goal_pos);
    }

    
    printf("Enter number of obstacles: ");
    scanf("%d", &obstacles);
    printf("Enter obstacle positions (1-9):\n");
    for (int i = 0; i < obstacles; i++)
    {
        int pos;
        scanf("%d", &pos);
        if (pos >= 1 && pos <= SIZE * SIZE && pos != start_pos && pos != goal_pos)
        {
            int row, col;
            pos_to_rowcol(pos, &row, &col);
            grid[row][col] = 0;
        }
        else
        {
            printf("Invalid obstacle, skipping!\n");
        }
    }

    
    printf("\nInitial Grid:\n");
    int sr, sc, dr, dc;
    pos_to_rowcol(start_pos, &sr, &sc);
    pos_to_rowcol(goal_pos, &dr, &dc);
    print_grid(sr, sc, dr, dc);
    printf("\nFinding Path...\n");
    aStarSearch(start_pos, goal_pos);

    return 0;
}