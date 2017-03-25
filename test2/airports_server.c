/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "places.h"
#include "airports.h"
#include "kdtree/kdtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#define pi 3.14159265358979323846


/* Distance functions */
double deg2rad(double deg) {
  return (deg * pi / 180);
}

double rad2deg(double rad) {
  return (rad * 180 / pi);
}

double distance(double lat1, double lon1, double lat2, double lon2, char unit) {
  double theta, dist;
  theta = lon1 - lon2;
  dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) *
	cos(deg2rad(lat2)) * cos(deg2rad(theta)); dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515;
  switch(unit) {
  case 'M':
	break;
  case 'K':
	dist = dist * 1.609344;
	break;
  case 'N':
	dist = dist * 0.8684;
	break;
  }
  return (dist);
}

/* Airports server functionalist*/
airport_ret *
airports_1_svc(airportdata *argp, struct svc_req *rqstp)
{
  const int NUM_RESULTS = 5;
  airportdata* p = argp;
  double latitude_in = (double) p -> latitude;
  double longitude_in = (double) p -> longitude;
  
  struct nodedata {
	char city[40];
	char code[4];
  };
  typedef struct nodedata nodedata;
  struct nodedata data[1200];
	
  static airport_ret result;
  FILE *fp;
  char line[200];
  void* tree = kd_create(2); /* Create kd tree with 2 dimensions */
  void* res;
  int i = 0;
  double la;
  double lo;
  nodedata *node;

  /* Free existing memory */
  xdr_free ((xdrproc_t) xdr_airport_ret, (char *) &res);

  /* Open and read airport locations file */
  fp = fopen("airport-locations.txt", "r");
  if (fp == NULL) {
	result.err = errno;
	return &result;
  }

  while(fgets(line, 200, fp) != NULL) {
	char *comma = strchr(line, ',');
	char *tab = strchr(line, '\t');
	char latitude[6];
	char longitude[8];
	int comma_pos = comma - tab - 1;
	int tab_pos = tab - line + 1;
	
	if(comma) {
	  strncpy(data[i].code, line + 1, 3);
	  data[i].code[3] = '\0';
	  
	  strncpy(latitude, line + 6, 5);
	  latitude[5] = '\0';
	  la = (double)atof(latitude);
	  
	  strncpy(longitude, line + 12, 7);
	  longitude[7] = '\0';
	  lo = (double)atof(longitude);

	  strncpy(data[i].city, line + tab_pos, comma_pos);
	  data[i].city[comma_pos] = '\0';

	  /* Insert into kd tree */
	  kd_insert2(tree, la, lo, &data[i]);
	  i += 1;
	}
  }
  fclose(fp);

  /* Get pointer to return data structure */
  airportlist newitem;
  airportlist *ptr;
  ptr = &result.airport_ret_u.list;

  /* Find nearest airports */
  res = kd_nearest_n2(tree, latitude_in, longitude_in, NUM_RESULTS);
  while(!kd_res_end(res)) {
	*ptr = (airportnode *) malloc (sizeof(airportnode));
	newitem = *ptr;

	if (newitem != (airportnode *)NULL) {
	  kd_res_item2(res, &la, &lo);
	  /* Append airport value to return list */
	  node = (nodedata*)kd_res_item_data(res);
	  newitem -> code = node -> code;
	  newitem -> name = node -> city;
	  newitem -> latitude = la;
	  newitem -> longitude = lo;
	  newitem -> distance = distance(latitude_in, longitude_in, la, lo, 'M');
	  ptr = &newitem -> next;
	}
	
	kd_res_next(res);
  }

  /* Free kd tree memory */
  kd_res_free(res);
  kd_free(tree);
  *ptr = (airportlist)NULL;
  result.err = 0;
  return &result;
}