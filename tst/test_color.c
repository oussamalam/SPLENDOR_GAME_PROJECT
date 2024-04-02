#include "color.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h> 

const char * B = "BLUE";
const char * C ="\033[%34mB\033[m";

void test_color(){
  const char* a=color_to_string(BLUE);
  int n= strcmp(a,B);
  assert( n == 0);
  const char* b= color_to_short_string(BLUE);
  assert(strcmp(b,C) == 0);
}

