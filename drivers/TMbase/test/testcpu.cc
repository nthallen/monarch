#include <unistd.h>
#include "dasio/cpu_usage.h"
#include "nl.h"

int main(int argc, char **argv) {
  DAS_IO::cpu_usage *cpu = new DAS_IO::cpu_usage;
  for (;;) {
    msg(0, "CPU: %3u %%", cpu->report());
    sleep(1);
  }
  return 0;
}
