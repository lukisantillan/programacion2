#include <stdio.h>
#include <stdlib.h>

int producto(int n1, int n2)
{
  if (n1 == 0 || n2 == 0)
  {
    return 0;
  }

  if ((n1 > 0 && n2 > 0) || (n1 < 0 && n2 < 0))
  {
    return abs(n1) + producto(abs(n1), abs(n2) - 1);
  }
  else
  {
    return producto(abs(n1), abs(n2) + 1) - abs(n1);
  }
}