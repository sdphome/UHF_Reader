#ifndef __SECURITY_H
#define __SECURITY_H

#define SECURITY_DEV        "/dev/uhf-security"

#define false                           0
#define true                            1

/* ---------- Response Result ---------- */
#define NO_ERROR                        0
#define FAILED                          1

typedef struct security_info {
    int fd;
} security_info_t;

#endif
