#ifndef HCI_H
#define HCI_H

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define MAX_RSP 127
#define LEN 8

typedef struct hci {

        inquiry_info* inq_info;
        void (*inquiry)(struct hci* self);
        int id;
        int8_t num_rsp;
} Hci;

Hci* newHci(void);
void initHci(Hci* self);
void deleteHci(Hci* self);
void inquiry(Hci* self);

#endif
