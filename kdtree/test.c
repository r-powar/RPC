#include <stdio.h>
#include "kdtree.h"


int main(void) {
  void* tree = kd_create(2);
  void* res;
  double la = 1.13;
  double lo=1.54;

  /*
  kd_insert2(tree, (double)47.122, (double)-122.34, NULL);
  kd_insert2(tree, (double)50.122, (double)-120.34, NULL);
  kd_insert2(tree, (double)45.134, (double)-100.34, NULL);
  kd_insert2(tree, (double)89.34, (double)-80.34, NULL);
  */

  int x = 0;
  
  while(x < 100) {
	kd_insert2(tree, (double)la, (double)lo, NULL);
	x +=1;
	la = la*2;
	lo = lo*1.6;
  }
  
  res = kd_nearest_n2(tree, (double)47.40, (double)92.25, 5);
  while(!kd_res_end(res)) {
	kd_res_item2(res, &la, &lo);
	printf("%f %f %f\n", la, lo, kd_res_dist(res));
	kd_res_next(res);
  }
  kd_res_free(res);
  kd_free(tree);
  return 0;
}
