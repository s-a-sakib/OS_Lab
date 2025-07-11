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

    // Generate the same unique key
    key = ftok("msgfile", 65);

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    // Receive the message
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("Received message: %s", message.msg_text);

    // Remove the message queue after use
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
