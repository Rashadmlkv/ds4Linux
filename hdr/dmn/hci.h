#ifndef HCI_H
#define HCI_H

#define MAX_LEN 127
#define LEN 8

typedef struct hci {

        int8_t id,\
                num_rsp;
        inquiry_info* inq_info;
        void (*inquiry)();
} Hci;

Hci* newHCI (void);
void inquiry (Hci* bdev);

#endif
