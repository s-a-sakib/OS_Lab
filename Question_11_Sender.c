/*
    Write a C program to show how two unrelated processes can communicate
    with each other by a message queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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

    // Generate a unique key using ftok
    key = ftok("msgfile", 65);

    // Create or access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    // Prepare the message
    message.msg_type = 1;
    printf("Enter message to send: ");
    fgets(message.msg_text, MSG_SIZE, stdin);

    // Send the message
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) < 0) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent successfully.\n");
    return 0;
}
