#include "sspint.h"

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  ssp_config.LE = 1; // Logging enabled by default
}
