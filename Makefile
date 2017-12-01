CC=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -MMD -iquote includes $(shell sdl2-config --cflags)
LDLIBS = $(shell sdl2-config --libs)

vpath %.c src

OBJS = he.o context.o
DEPS = $(OBJS:.o=.d)

BIN = he

all: lto

lto: CFLAGS += -flto
lto: LDFLAGS += -flto
lto: release


release: $(BIN)
release: CFLAGS += -O3


san: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
san: LDLIBS += -lasan -lubsan
san: debug


debug: CFLAGS += -ggdb -fstack-protector-all
debug: $(BIN)


$(BIN): $(OBJS)


-include $(DEPS)


clean:
	rm -f $(BIN) $(OBJS) $(DEPS)

.PHONY: clean debug all san release lto
