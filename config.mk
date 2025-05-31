PREFIX = /usr/local

X11INC = /usr/X11R7/include
X11LIB = /usr/X11R7/lib

INCS = -I${X11INC}
LIBS = -L${X11LIB} -lX11

CFLAGS = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS}
LDFLAGS = ${LIBS}

CC = gcc
