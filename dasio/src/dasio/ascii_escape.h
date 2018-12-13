/** @file dasio/ascii_escape.h */

#ifndef DAS_IO_ASCII_ESCAPE_H_INCLUDED
#define DAS_IO_ASCII_ESCAPE_H_INCLUDED
#include <string>

extern const char *ascii_escape(const char *str, int len);
extern const char *ascii_escape(const std::string &s);
extern const char *ascii_esc(const char *str);

#endif
