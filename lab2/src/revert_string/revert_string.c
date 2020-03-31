#include <string.h>
#include "revert_string.h"
#include "swap.c"

void RevertString(char *str)
{
    int length=strlen(str);
  
   for(int i=0; i<length/2; i++)
   {
        Swap(&str[length-i-1], &str[i]);
   }
}
