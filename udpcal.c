#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    char data[100], result[100];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1)
    {
        printf("\n1.Add\n2.Sub\n3.Mul\n4.Div\n5.Exit\n");

        printf("Enter Choice Operand1 Operand2: ");
        scanf("%s", data);

        if(strcmp(data, "5") == 0)
            break;

        sendto(sockfd, data, sizeof(data), 0, (struct sockaddr *)&server, len);

        recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr *)&server, &len);

        printf("Result = %s\n", result);
    }

    close(sockfd);

    return 0;
}





#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, ch;
    float a, b, ans;

    char data[100], result[100];

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Server Waiting...\n");

    while(1)
    {
        recvfrom(sockfd, data, sizeof(data), 0, (struct sockaddr *)&client, &len);

        sscanf(data, "%d %f %f", &ch, &a, &b);

        if(ch == 1)
            ans = a + b;

        else if(ch == 2)
            ans = a - b;

        else if(ch == 3)
            ans = a * b;

        else if(ch == 4)
            ans = a / b;

        sprintf(result, "%.2f", ans);

        sendto(sockfd, result, sizeof(result), 0, (struct sockaddr *)&client, len);
    }

    close(sockfd);

    return 0;
}
