CC?=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -MMD -iquote includes $(shell sdl2-config --cflags) \
	$(shell pkg-config SDL2_image --cflags) \
	$(shell pkg-config SDL2_ttf --cflags)
BASE_LDLIBS = $(shell sdl2-config --libs) $(shell pkg-config SDL2_image --libs) \
	$(shell pkg-config SDL2_ttf --libs) -lm
LDLIBS = $(BASE_LDLIBS)

vpath %.c src

OBJS = he.o vect.o utils.o pixutils.o rectangulize.o map.o \
       game.o input.o sprite.o rect.o player.o renderer.o collision.o \
       walls.o enemy.o score.o game_over.o font.o
DEPS = $(OBJS:.o=.d)

BIN = he

all: lto

lto: CFLAGS += -flto
lto: LDFLAGS += -flto
lto: release


release: $(BIN)
release: CFLAGS += -O3


san: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
san: LDLIBS = -lasan -lubsan $(BASE_LDLIBS)
san: debug


debug: CFLAGS += -g3 -O0 -fstack-protector-all
debug: $(BIN)


$(BIN): $(OBJS)


-include $(DEPS)


clean:
	rm -f $(BIN) $(OBJS) $(DEPS)

.PHONY: clean debug all san release lto
