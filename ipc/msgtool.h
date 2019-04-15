//
// Created by jason on 4/12/19.
//

#ifndef LINUXSP_MSGTOOL_H
#define LINUXSP_MSGTOOL_H

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

int create_msg_queue(key_t key);

int send_msg(int qid, const struct msgbuf *buf);

int read_msg(int qid, struct msgbuf *buf);

int peek_msg(int qid, long mtype);

int get_msg_queue_ds(int qid, struct msqid_ds *buf);

int chang_msg_queue_mode(int qid, char *mode);

int delete_msg(int qid);

#endif //LINUXSP_MSGTOOL_H
