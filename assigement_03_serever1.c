# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <ctype.h>

# define PORT 8082
# define BUFFER_SIZE 1024

// Convert to uppercase using ASCII
void to_upper(char *str) {
    for(int i = 0; str[i]!= '\0'; i++) {
        if(str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // ASCII: a=97, A=65, diff=32
        }
    }
}

// Convert to lowercase using ASCII
void to_lower(char *str) {
    for(int i = 0; str[i]!= '\0'; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32; // ASCII: A=65, a=97, diff=32
        }
    }
}

// Function to reverse string
void reverse(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 2. Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 3. Listen
    if (listen(server_fd, 3) < 0) { // 3 = max pending connections
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 4. Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    while(1) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) break;

        // Remove newline if present
        buffer[strcspn(buffer, "\n")] = 0;

        char command[10], text[BUFFER_SIZE];
        memset(command, 0, sizeof(command));
        memset(text, 0, sizeof(text));

        // Parse input: format = COMMAND|TEXT
        sscanf(buffer, "%[^|]|%[^\n]", command, text);

        if (strcmp(command, "UP") == 0) {
            to_upper(text);
        } else if (strcmp(command, "LOW") == 0) {
            to_lower(text);
        } else if (strcmp(command, "REV") == 0) {
            reverse(text);
        } else {
            strcpy(text, "Invalid Command");
        }

        send(new_socket, text, strlen(text), 0);
    }

    close(new_socket);
    close(server_fd);
    printf("Server terminated.\n");
    return 0;
}
