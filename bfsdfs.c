#include <stdio.h>
#include <string.h>

#define iMaxNodes 6  // Nodes A-F

// Adjacency matrix for the graph (1 if edge exists, 0 otherwise)
int iAdjMatrix[iMaxNodes][iMaxNodes] = {
    {0, 1, 1, 0, 0, 0},  // A: connected to B, C
    {1, 0, 0, 1, 1, 0},  // B: A, D, E
    {1, 0, 0, 0, 0, 1},  // C: A, F
    {0, 1, 0, 0, 0, 0},  // D: B
    {0, 1, 0, 0, 0, 1},  // E: B, F
    {0, 0, 1, 0, 1, 0}   // F: C, E
};

// Get index from node char (A=0, B=1, etc.)
int iGetIndex(char cNode) {
    return cNode - 'A';
}

// Bfs: Find path from start to goal using queue with detailed output
void Bfs(char cStart, char cGoal) {
    int iStartIdx = iGetIndex(cStart);
    int iGoalIdx = iGetIndex(cGoal);
    int iVisited[iMaxNodes] = {0};
    int iParent[iMaxNodes] = {-1};
    int iQueue[iMaxNodes];
    int iFront = 0, iRear = 0;

    printf("BFS Detailed Execution:\n");
    printf("Start Node: %c (Index: %d)\n", cStart, iStartIdx);
    printf("Goal Node: %c (Index: %d)\n\n", cGoal, iGoalIdx);

    iQueue[iRear++] = iStartIdx;
    iVisited[iStartIdx] = 1;
    printf("Initial Queue: [");
    printf("%c", 'A' + iQueue[0]);
    for (int i = 1; i < iRear; i++) {
        printf(", %c", 'A' + iQueue[i]);
    }
    printf("]\n");
    printf("Visited: %c\n\n", 'A' + iStartIdx);

    int iFound = 0;
    int iStep = 1;
    while (iFront < iRear && !iFound) {
        int iCurr = iQueue[iFront++];
        printf("Step %d: Dequeued %c (Index: %d)\n", iStep++, 'A' + iCurr, iCurr);

        for (int iNeighbor = 0; iNeighbor < iMaxNodes; iNeighbor++) {
            if (iAdjMatrix[iCurr][iNeighbor] && !iVisited[iNeighbor]) {
                iVisited[iNeighbor] = 1;
                iParent[iNeighbor] = iCurr;
                iQueue[iRear++] = iNeighbor;
                printf("  - Enqueued neighbor %c (Index: %d)\n", 'A' + iNeighbor, iNeighbor);
                if (iNeighbor == iGoalIdx) {
                    iFound = 1;
                    printf("  ** Goal %c found! **\n", cGoal);
                }
            }
        }

        // Print current queue and visited after this step
        printf("  Current Queue after step: [");
        if (iFront < iRear) {
            printf("%c", 'A' + iQueue[iFront]);
            for (int i = iFront + 1; i < iRear; i++) {
                printf(", %c", 'A' + iQueue[i]);
            }
        }
        printf("]\n");
        int iVisitedCount = 0;
        printf("  Visited so far: ");
        for (int j = 0; j < iMaxNodes; j++) {
            if (iVisited[j]) {
                printf("%c ", 'A' + j);
                iVisitedCount++;
            }
        }
        printf("(%d nodes)\n\n", iVisitedCount);
    }

    if (!iFound) {
        printf("Bfs: No path found.\n");
        return;
    }

    // Print path
    printf("\nFinal Path Reconstruction:\n");
    printf("Bfs Path: ");
    int iPath[iMaxNodes];
    int iPathLength = 0;
    int iTemp = iGoalIdx;
    while (iTemp != -1) {
        iPath[iPathLength++] = iTemp;
        iTemp = iParent[iTemp];
    }
    for (int iIdx = iPathLength - 1; iIdx >= 0; iIdx--) {
        printf("%c ", 'A' + iPath[iIdx]);
    }
    printf("\n");
}

// Dfs: Find path using recursion with detailed output
int iParent[iMaxNodes];
int iVisited[iMaxNodes];

void DfsUtil(int iCurr, int iGoal, int iStart, int iDepth) {
    printf("  %*cVisiting %c (Index: %d, Depth: %d)\n", iDepth * 2, ' ', 'A' + iCurr, iCurr, iDepth);
    iVisited[iCurr] = 1;

    if (iCurr == iGoal) {
        printf("  %*c** Goal %c reached! **\n", iDepth * 2, ' ', 'A' + iGoal);
        return;
    }

    for (int iNeighbor = 0; iNeighbor < iMaxNodes; iNeighbor++) {
        if (iAdjMatrix[iCurr][iNeighbor] && !iVisited[iNeighbor]) {
            iParent[iNeighbor] = iCurr;
            DfsUtil(iNeighbor, iGoal, iStart, iDepth + 1);
        }
    }
    printf("  %*cBacktracking from %c\n", iDepth * 2, ' ', 'A' + iCurr);
}

void Dfs(char cStart, char cGoal) {
    int iStartIdx = iGetIndex(cStart);
    int iGoalIdx = iGetIndex(cGoal);
    memset(iVisited, 0, sizeof(iVisited));
    memset(iParent, -1, sizeof(iParent));

    printf("DFS Detailed Execution:\n");
    printf("Start Node: %c (Index: %d)\n", cStart, iStartIdx);
    printf("Goal Node: %c (Index: %d)\n\n", cGoal, iGoalIdx);

    iParent[iStartIdx] = -1;
    DfsUtil(iStartIdx, iGoalIdx, iStartIdx, 0);

    if (!iVisited[iGoalIdx]) {
        printf("\nDfs: No path found.\n");
        return;
    }

    // Print path
    printf("\nFinal Path Reconstruction:\n");
    printf("Dfs Path: ");
    int iPath[iMaxNodes];
    int iPathLength = 0;
    int iTemp = iGoalIdx;
    while (iTemp != -1) {
        iPath[iPathLength++] = iTemp;
        iTemp = iParent[iTemp];
    }
    for (int iIdx = iPathLength - 1; iIdx >= 0; iIdx--) {
        printf("%c ", 'A' + iPath[iIdx]);
    }
    printf("\n");
}

int main() {
    int iChoice;
    printf("Choose algorithm:\n1. Bfs\n2. Dfs\nEnter choice: ");
    scanf("%d", &iChoice);

    char cStart = 'A';
    char cGoal = 'F';

    switch (iChoice) {
        case 1:
            Bfs(cStart, cGoal);
            break;
        case 2:
            Dfs(cStart, cGoal);
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}