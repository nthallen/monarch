/* OUI output from the following packages:
   memo
*/
#include "oui.h"
#include "memo.h"
const char *opt_string = "o:V";

void oui_init_options(int argc, char **argv) {
	memo_init_options(argc, argv);
}

#ifdef __USAGE
%C    [options]
	-o <filename> Output file
	-V Output to stdout (default)
#endif
