#include "inter.h"




int fullp(prozesu *p[8]){
  int i;
  int full=1;
  for (i=0;i<8;i++)
    if(p[i]==NULL) full=0;
  return full;

}

