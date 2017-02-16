/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "places.h"
#include "airports.h"

void
placesprog_1(char *host, char *city, char *state)
{
	CLIENT *clnt;
	places_ret  *result_1;
	placedata  places_1_arg;
	places_1_arg.name = city;
	places_1_arg.state = state;
	
#ifndef	DEBUG
	clnt = clnt_create (host, PLACESPROG, PLACES_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = places_1(&places_1_arg, clnt);
	if (result_1 == (places_ret *) NULL) {
		clnt_perror (clnt, "call failed here\n");
	} else {
	  printf("call successful\n");
	
	  placelist list;
	  list = result_1 -> places_ret_u.list;
	  printf("We found these airports near you: ");
	  while(list != NULL) {
	    printf("%s\n", list->placename);
		list = list -> next;
	  }
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
  char *host;
  char *city;
  char *state;

  if (argc < 4){
	printf ("usage: %s server_host city state\n", argv[0]);
	exit (1);
  }

  host = argv[1];
  city = argv[2];
  state = argv[3];
  placesprog_1(host, city, state);
  exit(0);
}
