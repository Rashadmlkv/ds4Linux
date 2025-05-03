#include "dmn.h"

void gamepadConnect() {

        //search bluetooth devices
        bdev.num_rsp = hci_inquiry( bdev.id,\
                        LEN,\
                        MAX_RSP,\
                        NULL,\
                        &bdev.inq_info,\
                        IREQ_CACHE_FLUSH);

        //if found anything
        if ( bdev.num_rsp > 0) {

                //check each device's class
                for ( uint8_t i = 0; i < bdev.num_rsp; i++) {

                        if ( GAMEPAD_CLASS == ( ( ( bdev.inq_info + i)->dev_class[2] << 16) |\
                                                ( ( bdev.inq_info + i)->dev_class[1] << 8) |\
                                                ( ( bdev.inq_info + i)->dev_class[0]))) {
                                gamepadsAppend(i);
                        }
                }
        }
}

int8_t gamepadsAppend (uint8_t i) {

        gamepad_list * node = NULL;
        if ( !(gamepads) && ( node = malloc( sizeof( gamepad_list)))) {

                node->sockCTRL = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
                node->sockITRP = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

                if ( node->sockCTRL && node->sockITRP && tryConnect( node, i)) {

                        ba2str( &(bdev.inq_info + i)->bdaddr, node->bdaddr);
                        node->next = NULL;
                        gamepads = node;
                } else
                        free( node);

        } else {

                gamepad_list * tmp = gamepads;
                char * tmpbdaddr;
                ba2str( &(bdev.inq_info + i)->bdaddr, tmpbdaddr);
                //check if gamepad already registered
                for ( ; tmp->next; tmp = tmp->next) {

                        if ( !(strcmp(node->bdaddr, tmpbdaddr)))
                                return (-1);
		}

		                //double check incase tmp is head
                if ( ( node = malloc( sizeof( gamepad_list))) &&\
                                ( strcmp(node->bdaddr, tmpbdaddr))) {

                        node->sockCTRL = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
                        node->sockITRP = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);

                        if ( node->sockCTRL && node->sockITRP && tryConnect( node, i)) {
                                ba2str( &(bdev.inq_info + i)->bdaddr, node->bdaddr);
                                node->next = NULL;
                                tmp->next = node;
                        } else
                                free( node);
                }

        }
}

int8_t tryConnect (gamepad_list * node, uint8_t i) {

        gamepad_sock.l2_bdaddr = (bdev.inq_info + i)->bdaddr;
        printf ("sa\n");
        gamepad_sock.l2_psm = htobs( HCI_CTRL);

        int8_t ctrl = connect( node->sockCTRL,\
                        (struct sockaddr *) &gamepad_sock,\
                        sizeof( gamepad_sock));

        gamepad_sock.l2_psm = htobs( HCI_ITRP);
        int8_t itrp = connect( node->sockITRP,\
                        (struct sockaddr *) &gamepad_sock,\
                        sizeof( gamepad_sock));

        if ( !(ctrl) && !(itrp)){
                printf ("oldu\n");
                return (1);

        }
        else{
                printf ("%d, %d olmadi\n", ctrl, itrp);
                return (0);

        }
}
