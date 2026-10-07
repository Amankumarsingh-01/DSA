# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>

# define PORT 8082
# define BUFFER_SIZE 1024

int main () {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];

    // 1. Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 2. Change IP here if using different machine
    // "127.0.0.1" = localhost. No spaces inside IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    // 3. MISSING: Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    printf("Connected to server.\n");

    while(1) {
        printf("\nEnter command (UP|text, LOW|text, REV|text) or 'bye': ");
        fgets(input, BUFFER_SIZE, stdin);
        
        // Remove \n from fgets
        input[strcspn(input, "\n")] = 0;

        // Exit condition
        if(strcmp(input, "bye") == 0) {
            printf("Closing connection...\n");
            break;
        }

        send(sock, input, strlen(input), 0);

        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(sock, buffer, BUFFER_SIZE);
        if(bytes_read <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        
        printf("Server response: %s\n", buffer);
    }

    close(sock);
    return 0;
}