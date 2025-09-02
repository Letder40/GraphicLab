CC = g++
CFLAGS = -g -pedantic -Wall -Wextra --std=c++20
LIBS = -lglfw -lGLEW -lGL 

SRCDIR = src
BUILDDIR = build

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

TARGET = $(BUILDDIR)/test_game

.PHONY: run

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $^

$(OBJECTS): $(SOURCES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -r build
