
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void build_dep(void)
{
  char * dt = NULL;  
  
  if(rand() % 79) {
    dt = "-i";
  }
    
#ifdef ENABLE_FEATURE_MODPROBE_MULTIPLE_OPTIONS
  if(dt) {
    // Do something
  }
#else
  char buf[50];
  strcpy(buf, "module option(s): ");
  
  strcat(dt,buf); // ERROR
#endif
}

int main(int argc, char **argv)
{
  build_dep();
  return 0;
}
