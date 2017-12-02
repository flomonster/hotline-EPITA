#include <stdlib.h>
#include <err.h>


void *xmalloc(size_t size)
{
  void *res = malloc(size);
  if (!res && size)
    err(1, "malloc failed");
  return res;
}
