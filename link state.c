#include <stdio.h>

#define MAX 10
#define INF 9999

int main()
{
    int cost[MAX][MAX], dist[MAX], visit[MAX];
    int n, i, j, min, next, start;

    printf("Enter number of routers: ");
    scanf("%d", &n);

    printf("Enter cost matrix (0 = no link):\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);

            if(cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    printf("Enter starting router: ");
    scanf("%d", &start);
    start = start - 1;

    // initialization
    for(i = 0; i < n; i++)
    {
        dist[i] = cost[start][i];
        visit[i] = 0;
    }

    dist[start] = 0;
    visit[start] = 1;

    // main logic
    for(i = 0; i < n - 1; i++)
    {
        min = INF;
        next = -1;

        // find nearest unvisited node
        for(j = 0; j < n; j++)
        {
            if(visit[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                next = j;
            }
        }

        visit[next] = 1;

        // update distances
        for(j = 0; j < n; j++)
        {
            if(visit[j] == 0 && dist[next] + cost[next][j] < dist[j])
            {
                dist[j] = dist[next] + cost[next][j];
            }
        }
    }

    // output
    printf("\nShortest paths from router %d:\n", start + 1);
    printf("Router\tDistance\n");

    for(i = 0; i < n; i++)
    {
        if(i != start)
            printf("%d\t%d\n", i + 1, dist[i]);
    }

    return 0;
}
