#ifndef SBSWITCH_H_INCLUDED
#define SBSWITCH_H_INCLUDED

extern const char *subbus_svc;
extern const char *subbus_subsvc;
extern const char *subbus_addr;
extern const char *switch_mask;
extern bool quit_if_nonzero;
void sbswitch_args(const char *arg);

#endif
