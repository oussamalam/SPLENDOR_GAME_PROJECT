#include <stdio.h>
#include <stdlib.h>
#include "color.h"

char* str[MAX_COLORS]={"BLACK","BLUE","GREEN","RED","WHITE","GOLD","PEARL","AQUAMARINE","OCTARINE","CHESTNUT"};
const char* color_to_string(enum color_t c)
{
  if (c>=0 && c< MAX_COLORS)
    return str[c];
  return NULL;
}
char* str1[MAX_COLORS]={
  "\033[%30mN\033[m",
  "\033[%34mB\033[m",
  "\033[%32mG\033[m",
  "\033[%31mR\033[m",
  "\033[%97mW\033[m",
  "\033[%33mO\033[m",
  "\033[%37mP\033[m",
  "\033[%36mA\033[m",
  "\033[%35mV\033[m",
  "\033[%31mM\033[m",
};
const char* color_to_short_string(enum color_t c)
{
  if (c>=0 && c<MAX_COLORS)
    return str1[c];
  return NULL;
}

