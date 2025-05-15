#include "ds4linux.h"

sigjmp_buf jumpbuffer;

void sighandler(int signo) {

	(void)signo;
	siglongjmp(jumpbuffer, 1);
}

int
main (void) {

	if (sigsetjmp(jumpbuffer, 0) != 0)
                goto errexit;

	Daemon* daemon = newDaemon();

	daemon->daemonize(daemon);

	struct sigaction handler = {0};
	handler.sa_handler = &sighandler;
	sigaction(SIGTSTP, &handler, NULL);
	
	start:
		
		daemon->prioritize(daemon, 19);

		while (hci_get_route(NULL) == -1);

		daemon->prioritize(daemon, 0);
		
		Hci* hci = newHci();
		List* list = newList();

		do {
		
			//search
			hci->inquiry(hci);
			//append
			list->append(list, hci->inq_info, hci->num_rsp);	
		} while (hci_get_route(NULL) != -1);

		//cleanup
		deleteDaemon(daemon);
		deleteHci(hci);
		deleteList(list);

	goto start;

	errexit:
		deleteDaemon(daemon);
		deleteHci(hci);
		deleteList(list);
		exit(0);
}
