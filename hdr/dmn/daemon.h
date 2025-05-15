#ifndef DAEMON_H
#define DAEMON_H

typedef struct daemon {

        void (*daemonize)(struct daemon* self);
        void (*prioritize)(struct daemon* self, int8_t value);
        pid_t pid;
} Daemon;

Daemon* newDaemon(void);
void initDaemon(Daemon* self);
void deleteDaemon(Daemon* self);
void daemonize(Daemon* self);
void prioritize(Daemon* self, int8_t value);
#endif
