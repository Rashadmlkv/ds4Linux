#include "ds4Linux.h"

controller_list* head;

void
main (void) {

	//prepeare to search
	short bt_dev_id = hci_get_route (NULL), bt_dev_sock = hci_open_dev (bt_dev_id);

	if (bt_dev_id < 0 || bt_dev_sock < 0) {

		perror ("Bluetooth is propaply off");
		exit (errno);
	}

	inquiry_info* inq_info = NULL;
	short num_rsp = 0;

	if (!(inq_info = malloc (MAX_RSP * sizeof (inquiry_info)))) {

		perror("Failed to create memory");
		goto quit;
	}

	//search devices
	if ((num_rsp = hci_inquiry (bt_dev_id, LEN, MAX_RSP, NULL, &inq_info, IREQ_CACHE_FLUSH)) < 0) {

		perror ("Failed to search devices");
		goto quit;
	}

	//check device class
	uint32_t dev_class = 0;
	head = malloc (sizeof (controller_list));
	head->next = NULL;

	for (int i = 0 ; i < num_rsp ; i++) {

		//shifting values to correct position
		dev_class = ((inq_info+i)->dev_class[2] << 16) | \
			    ((inq_info+i)->dev_class[1] << 8) | \
			    (inq_info+i)->dev_class[0];

		if (dev_class == CLS_DEV) {

			//add to list, returns 1 on fail
			if (addController ((inq_info + i)->bdaddr)) goto quit;
		}
	}

	if (connectController ()) goto quit;
	readControllerInput ();

quit:
	hci_close_dev (bt_dev_sock);

	//preventing freeing from non allocated memory error
try:
	free (inq_info);
	freeControllerList ();
catch:


}

int addController (bdaddr_t addr) {

	controller_list* node = malloc (sizeof (controller_list)), *temp = head;
	node->controller.sock.l2_bdaddr = addr;

	if (node) {
		if (!(head->next)) {

			head->next = node;
			node->next = NULL;
			return (0);
		} else {

			node->next = NULL;
			while (temp->next) {

				temp = temp->next;
			}
			temp->next = node;
		}
		return (0);
	}
	return (1);
}

int connectController () {

	controller_list* temp = head;

	while (temp->next) {

		temp = temp->next;
		if ((temp->controller.portCTRL = socket (AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP)) < 0 | \
				(temp->controller.portITRP = socket (AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP)) < 0) {

			perror ("Failed to open port");
			return (1);
		}

		temp->controller.sock.l2_family = AF_BLUETOOTH;
		temp->controller.sock.l2_psm = htobs (HID_CTRL);

		if ( connect (temp->controller.portCTRL, (struct sockaddr *) &temp->controller.sock, sizeof (temp->controller.sock))) {

			perror ("Failed connection to control port");
			return (1);
		}

		temp->controller.sock.l2_psm = htobs (HID_ITRP);

		if ( connect (temp->controller.portITRP, (struct sockaddr *) &temp->controller.sock, sizeof (temp->controller.sock))) {

			perror ("Failed connection to interrupt port");
			return (1);
		}
	}
}

void freeControllerList () {

	controller_list* temp;

	while (head->next) {

		temp = head;
		head = head->next;
		close (head->controller.portCTRL);
		close (head->controller.portITRP);
		free (temp);
	}
}

int readControllerInput () {

	unsigned char buffer[11]; //controller sends 11 bytes
try :
	while (1) {

		recv(head->next->controller.portITRP, buffer, sizeof (buffer), 0);
		for (int i = 0; i < 11; i++) {

			printf ("%d:", buffer[i]);
		}
		printf ("\n");
	}
catch:
	return (0);
}
