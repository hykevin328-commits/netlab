#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;

    char choice[10];
    char num[100];
    char result[1000];

    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    while(1)
    {
        printf("\n1.Factorial\n2.Prime\n3.Table\n4.Exit\n");

        printf("Enter Choice: ");
        scanf("%s", choice);

        send(sockfd, choice, sizeof(choice), 0);

        if(strcmp(choice, "4") == 0)
            break;

        printf("Enter Number: ");
        scanf("%s", num);

        send(sockfd, num, sizeof(num), 0);

        recv(sockfd, result, sizeof(result), 0);

        printf("\n%s\n", result);
    }

    close(sockfd);

    return 0;
}          clent above 






#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, newsock;
    int i, n, fact, prime;

    char choice[10];
    char num[100];
    char result[1000];
    char temp[100];

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 5);

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);

    while(1)
    {
        recv(newsock, choice, sizeof(choice), 0);

        if(strcmp(choice, "4") == 0)
            break;

        recv(newsock, num, sizeof(num), 0);

        n = atoi(num);

        // Factorial
        if(strcmp(choice, "1") == 0)
        {
            fact = 1;

            for(i = 1; i <= n; i++)
            {
                fact = fact * i;
            }

            sprintf(result, "Factorial = %d", fact);
        }

        // Prime
        else if(strcmp(choice, "2") == 0)
        {
            prime = 1;

            for(i = 2; i < n; i++)
            {
                if(n % i == 0)
                {
                    prime = 0;
                }
            }

            if(prime == 1)
                strcpy(result, "Prime Number");
            else
                strcpy(result, "Not Prime Number");
        }

        // Table
        else if(strcmp(choice, "3") == 0)
        {
            result[0] = '\0';

            for(i = 1; i <= 10; i++)
            {
                sprintf(temp,
                        "%d x %d = %d\n",
                        n,
                        i,
                        n * i);

                strcat(result, temp);
            }
        }

        send(newsock, result, sizeof(result), 0);
    }

    close(newsock);
    close(sockfd);

    return 0;
}
