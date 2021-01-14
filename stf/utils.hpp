#include <sys/ioctl.h>

namespace stf {

winsize getws();
char *itostr(int n, char* b);
char *ftostr(const double n, char *b);
void set_mode(int want_key);
int get_key();

}