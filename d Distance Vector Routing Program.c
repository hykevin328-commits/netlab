#include <stdio.h>

int main()
{
    int n, cost[20][20], via[20][20], mat[20][20];
    int i, j, k, change;

    printf("Enter number of routers: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &mat[i][j]);

            if(i == j)
                mat[i][j] = 0;

            cost[i][j] = mat[i][j];
            via[i][j] = j;
        }
    }

    do
    {
        change = 0;

        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                for(k = 0; k < n; k++)
                {
                    if(mat[i][k] + cost[k][j] < cost[i][j])
                    {
                        cost[i][j] = mat[i][k] + cost[k][j];

                        via[i][j] = k;

                        change = 1;
                    }
                }
            }
        }

    } while(change);

    for(i = 0; i < n; i++)
    {
        printf("\nFor Router %d\n", i + 1);

        for(j = 0; j < n; j++)
        {
            printf("To %d via %d Distance %d\n",
                   j + 1,
                   via[i][j] + 1,
                   cost[i][j]);
        }
    }

    return 0;
}
