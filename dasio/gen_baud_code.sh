#! /bin/bash
baud_header=/usr/include/sys/termios.h

sed -ne 's/#define B\([0-9][0-9]*\).*$/\1/p' $baud_header >baudopts.txt

cat >get_baud_code.cc <<EOF
/** @file get_baud_code.cc
 * @brief Evaluate baud codes
 */
#include <termios.h>
#include "dasio/serial.h"
#include "nl.h"

speed_t DAS_IO::Serial::get_baud_code(int baud) {
  switch (baud) {
EOF

while read baud ; do
  # echo baud is $baud
  echo "#ifdef B$baud"
  echo "    case $baud: return B$baud;"
  echo "#endif"
done <baudopts.txt >>get_baud_code.cc

cat >>get_baud_code.cc <<EOF
    default: nl_error(3, "Invalid baud rate: %u", baud);
  }
}
EOF

rm baudopts.txt

