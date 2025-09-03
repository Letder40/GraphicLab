CC = g++
CFLAGS = -g -pedantic -Wall -Wextra --std=c++20 -Iinclude
LIBS = -lglfw -lGLEW -lGL

SRCDIR = src
BUILDDIR = build

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

TARGET = $(BUILDDIR)/test_game

all: $(TARGET)
	echo $(OBJECTS)

.PHONY: run

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@rm -r build
