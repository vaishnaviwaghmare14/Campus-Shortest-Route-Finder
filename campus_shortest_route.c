#include <stdio.h>
#include <string.h>
#define MAX 20
#define INF 99999

int graph[MAX][MAX];
char location[MAX][50];
int n = 0;
int source = -1;
int distance[MAX];
int parent[MAX];
int shortestPathFound = 0;

void enterGraph()
{
    int i, j, dist;
	printf("\nEnter number of locations: ");
    scanf("%d", &n);
	if (n <= 0 || n > MAX)
    {
        printf("\nInvalid number of locations.\n");
        n = 0;
        return;
    }
	 printf("\nEnter location names:\n");
	for (i = 0; i < n; i++)
    {
        printf("Location %d: ", i + 1);
        scanf(" %[^\n]", location[i]);
    }
	for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }
	printf("\nEnter distance between connected locations.\n");
    printf("Enter 0 if there is no direct connection.\n");
	for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            printf("\nDistance between %s and %s: ",
                   location[i], location[j]);

            scanf("%d", &dist);

            if (dist > 0)
            {
                graph[i][j] = dist;
                graph[j][i] = dist;
            }
        }
    }
	source = -1;
    shortestPathFound = 0;
	printf("\nCampus graph entered successfully.\n");
}

void displayMatrix()
{
    int i, j;
	if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }
	printf("\n--- ADJACENCY MATRIX ---\n\n");
	printf("%-22s", "");
	for (i = 0; i < n; i++)
    {
        printf("%-20s", location[i]);
    }
	printf("\n");
	for (i = 0; i < n; i++)
    {
        printf("%-22s", location[i]);
		for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("%-20s", "INF");
            else
                printf("%-20d", graph[i][j]);
        }
		printf("\n");
    }
}

void selectSource()
{
    int choice;
	if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }
	printf("\n---SELECT SOURCE LOCATION---\n");
	for (int i = 0; i < n; i++)
    {
        printf("%d. %s\n", i + 1, location[i]);
    }
	printf("\nEnter source location number: ");
    scanf("%d", &choice);
	if (choice < 1 || choice > n)
    {
        printf("\nInvalid source location.\n");
        source = -1;
        return;
    }
	source = choice - 1;
    shortestPathFound = 0;
	printf("\nSelected Source: %s\n", location[source]);
}

int findMinimumVertex(int visited[])
{
    int minDistance = INF;
    int minVertex = -1;
	for (int i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < minDistance)
        {
            minDistance = distance[i];
            minVertex = i;
        }
    }
	return minVertex;
}

void dijkstra()
{
    int visited[MAX];
	for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
	distance[source] = 0;
	for (int count = 0; count < n; count++)
    {
        int current = findMinimumVertex(visited);
		if (current == -1)
            break;
		visited[current] = 1;
		for (int j = 0; j < n; j++)
        {
            if (!visited[j] &&
                graph[current][j] != INF)
            {
                int newDistance =
                    distance[current] + graph[current][j];

                if (newDistance < distance[j])
                {
                    distance[j] = newDistance;
                    parent[j] = current;
                }
            }
        }
    }
	 shortestPathFound = 1;
	printf("\nShortest paths calculated successfully.\n");
}

void printPath(int vertex)
{
    if (parent[vertex] == -1)
    {
        printf("%s", location[vertex]);
        return;
    }

    printPath(parent[vertex]);
	printf(" -> %s", location[vertex]);
}

void findShortestPath()
{
    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }
    if (source == -1)
    {
        printf("\nPlease select a source location first.\n");
        return;
    }
    dijkstra();
    printf("\nSource Location: %s\n", location[source]);
}

void displayShortestPath()
{
    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }
    if (source == -1)
    {
        printf("\nPlease select a source location first.\n");
        return;
    }

    if (!shortestPathFound)
    {
        printf("\nPlease find the shortest paths first.\n");
        return;
    }
    printf("\n--- SHORTEST PATHS ---\n\n");

    printf("Source: %s\n\n", location[source]);
	printf("%-25s %-20s %s\n",
           "Destination",
           "Shortest Distance",
           "Shortest Path");
	printf("----------------------------------------------------------------------\n");
	for (int i = 0; i < n; i++)
    {
        if (i == source)
            continue;
		printf("%-25s ", location[i]);
		if (distance[i] == INF)
        {
            printf("%-20s", "INF");
            printf("No path available");
        }
        else
        {
            printf("%-20d", distance[i]);
            printPath(i);
        }
		printf("\n");
    }
}

void displayDistance()
{
    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }
	if (source == -1)
    {
        printf("\nPlease select a source location first.\n");
        return;
    }
	if (!shortestPathFound)
    {
        printf("\nPlease find the shortest paths first.\n");
        return;
    }
	printf("\n--- DISTANCE FROM SOURCE ---\n\n");
	printf("Source: %s\n\n", location[source]);

    for (int i = 0; i < n; i++)
    {
        if (i == source)
            continue;
		if (distance[i] == INF)
        {
            printf("%-25s : No path\n",
                   location[i]);
        }
        else
        {
            printf("%-25s : %d\n",
                   location[i],
                   distance[i]);
        }
    }
}

int main()
{
    int choice;

    do
    {
        
        printf("\n\nCAMPUS SHORTEST ROUTE FINDER DIJKSTRA'S ALGORITHM\n");
        printf("===================================================\n");

        printf("\n1. Enter Campus Graph");
        printf("\n2. Display Adjacency Matrix");
        printf("\n3. Select Source Location");
        printf("\n4. Find Shortest Path");
        printf("\n5. Display Shortest Path");
        printf("\n6. Display Distance from Source to All Locations");
        printf("\n7. Exit");
		 printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                break;
			case 2:
                displayMatrix();
                break;
			case 3:
                selectSource();
                break;
			case 4:
                findShortestPath();
                break;
			case 5:
                displayShortestPath();
                break;
			case 6:
                displayDistance();
                break;
			case 7:
                printf("\nProgram terminated successfully.\n");
                break;
			default:
                printf("\nInvalid menu choice. Please try again.\n");
        }
    } while (choice != 7);
    return 0;
}
