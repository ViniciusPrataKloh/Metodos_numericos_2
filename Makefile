CC := cc
CFLAGS := -g -Wall -Wextra -lm -w#-ansi
CPPFLAGS := #-DDEBUG
LD := cc
LDFLAGS := -g
MAIN := implementacao_2.c
LIBS :=

PROG := 2

${PROG}: ${OBJS}
	${LD} ${LDFLAGS} ${MAIN} ${CFLAGS} -o ${PROG} ${LIBS}

clean:
	rm -f ${PROG} ${OBJS}

.PHONY: clean
