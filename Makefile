CC=gcc


CFLAGS=
LDLIBS=gtk+-3.0

SRC_DIR=src/
BUILD_DIR=bin/
EXECUTABLE=sqledit

BUILD_OBJS=$(SRC_DIR)sqledit.c \
	$(SRC_DIR)logger.c

all: build

.PHONY: build

build:
	mkdir -p $(BUILD_DIR)
	$(CC) $(BUILD_OBJS) -o $(BUILD_DIR)$(EXECUTABLE) `pkg-config --cflags --libs $(LDLIBS)`

.PHONY: clean

clean:
	rm -f $(BUILD_DIR)$(EXECUTABLE)
