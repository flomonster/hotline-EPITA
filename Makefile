CC?=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -MMD -iquote includes $(shell sdl2-config --cflags) \
	$(shell pkg-config SDL2_image --cflags)
LDLIBS = $(shell sdl2-config --libs) -lSDL2_image

vpath %.c src

OBJS = he.o context.o vect.o utils.o pixutils.o rectangulize.o map.o entity.o
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
