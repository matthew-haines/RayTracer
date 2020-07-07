CXX := g++

SRCDIR := src
LIBDIR := lib
OBJDIR := obj
BINDIR := bin
TARGET := tracer
CPPFLAGS := -c -g -std=c++17
LDLIBS := -lm -lpthread

SOURCES :=  $(shell find $(SRCDIR) -name "*.cpp")
LIBSOURCES := $(shell find $(LIBDIR) -name "*.cpp")
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
LIBOBJECTS := $(patsubst $(LIBDIR)/%.cpp,$(OBJDIR)/%.o, $(LIBSOURCES))

$(BINDIR)/$(TARGET): $(OBJECTS) $(LIBOBJECTS)
	$(CXX) -o $@ $+ $(LDLIBS)

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -o $@ $^

$(LIBOBJECTS): $(OBJDIR)/%.o: $(LIBDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -o $@ $^

.PHONY: build clean

clean:
	rm -rf $(OBJDIR)/*