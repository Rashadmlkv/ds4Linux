#include "../../hdr/dmn/dmn.h"

int
main ( void) {

start:

	/*
	 * lower process priority until bluetooth is active
	 */
	errno = 0;
	if ( nice( 19) == -1 && errno != 0) {

		perror( "");
	}

	while ( hci_get_route( NULL) == -1);

	/*
	 * search for bluetooth devices until bluetooth is deactive
	 */
	errno = 0;
        if ( nice( 0) == -1 && errno != 0) {

                perror( "");
        }

	goto start;

	return (errno);
}
