#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSG_SIZE 100

// Define message structure
struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    key = ftok("msgfile", 65);

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child Process: Sends a message
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from child process!");

        // Send the message to the queue
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Child sent message: %s\n", message.msg_text);

        exit(0);
    } else {
        // Parent Process: Receives the message
        wait(NULL); // Wait for child to send message

        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Parent received message: %s\n", message.msg_text);

        // Remove the message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
