//
// Created by jason on 4/12/19.
//

#include "msgtool.h"

int main(int argc, char *argv[])
{
    key_t key;
    int qid;
    struct struct msgbuf;

    if (argc == 1) {
        printf("Not enough argument.");
    }

    key = ftok("./", 1);
    qid = create_msg_queue(key);
    if (qid == -1) {
        perror("create msg queue");
        exit(EXIT_FAILURE);
    }

    switch (tolower(argv[1][0])) {
        case 's':
            send_msg(qid,)
    }
}

int create_msg_queue(key_t key) {
    int ret;
    ret = msgget(key, IPC_CREAT | 0660);

    return ret;
}

int send_msg(int qid, const struct msgbuf *buf) {
    int ret;
    ret = msgsnd(qid, buf, sizeof(struct msgbuf), IPC_NOWAIT);

    return ret;
}

int read_msg(int qid, long mtype, struct msgbuf *buf) {
    int ret;

    ret = msgrcv(qid, buf, sizeof(struct msgbuf), mtype, IPC_NOWAIT);

    return ret;
}

int peek_msg(int qid, long mtype) {
    int ret;

    ret = msgrcv(qid, NULL, 0, mtype, 0);
    return ret;
}

int get_msg_queue_ds(int qid, struct msqid_ds *buf) {
    int ret;

    ret = msgctl(qid, IPC_STAT, buf);
    return ret;
}

int chang_msg_queue_mode(int qid, char *mode) {
    int ret;
    struct msqid_ds ds;
    ret = get_msg_queue_ds(qid, &ds);

    sscanf(mode, "%ho", &ds.msg_perm.mode);

    ret += msgctl(qid, IPC_SET, &ds);

    return ret;
}

int delete_msg(int qid) {
    int ret;

    ret = msgctl(qid, IPC_RMID, NULL);
    return ret;
}
