include config.mk

SRC = getcp.c
OBJ = getcp.o

all: getcp

%.o: %.c
	${CC} -c ${CFLAGS} $<

${OBJ}:

getcp: ${OBJ}
	mkdir -p build
	${CC} -o build/$@ ${OBJ} ${LDFLAGS}

clean:
	rm -rf build ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f build/getcp ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/getcp

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/getcp

.PHONY: all clean install uninstall
