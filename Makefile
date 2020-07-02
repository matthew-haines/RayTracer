CXX := g++

SRCDIR := src
OBJDIR := obj
BINDIR := bin
TARGET := tracer
CPPFLAGS := -c -g
LDLIBS := -lm -lpthread

SOURCES :=  $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $+ $(LDLIBS)

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^

.PHONY: build clean

clean:
	rm -f $(OBJDIR)/*