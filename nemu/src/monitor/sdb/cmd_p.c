#include "cmd_p.h"

int cmd_p(char *args) {
  word_t n;
  paddr_t expr;
  if (sscanf(args, "%d %x", &n, &expr) == 2) {
    // hex_dump(expr, n);
  }
  return 0;
}