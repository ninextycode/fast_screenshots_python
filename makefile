#### Compiler and tool definitions shared by all build targets #####
CXX = g++
COMP_FLAGS = -fPIC -g -c
LINK_FLAGS =  -shared

## Target: capturer


LIBS = -lXext -lX11 -lboost_python-py35 \
    $(shell pkg-config --libs python3) \
    $(shell pkg-config --libs opencv)

INCLUDE = $(shell pkg-config --cflags python3) \
    $(shell pkg-config --cflags opencv) \
    $(shell pkg-config --cflags x11)

TARGETDIR = build
CONVERTER_DIR = numpy_opencv_converter

SRC = $(wildcard $(CONVERTER_DIR)/utils/*.cpp) \
    $(wildcard $(CONVERTER_DIR)/*.cpp) $(wildcard *.cpp)


OBJS =  $(patsubst %.cpp, %.o, $(SRC))

TARGET = capturer.so

PACKAGEDIR = ~/.local/lib/python3.5/site-packages/

uninstall:
	rm -f $(PACKAGEDIR)/$(TARGET)

install: all $(PACKAGEDIR)
	cp $(TARGETDIR)/$(TARGET) $(PACKAGEDIR)/$(TARGET)


all: $(TARGETDIR)/$(TARGET)

$(TARGETDIR)/$(TARGET): $(TARGETDIR) $(OBJS)
	$(CXX) $(LINK_FLAGS) -o $@ $(OBJS) $(LIBS)


%.o: %.cpp stdafx.h
	$(CXX) $(COMP_FLAGS) -o $@ $< $(INCLUDE)

#### Clean target deletes all generated files ####
clean:
	rm -rf $(TARGETDIR) $(OBJS)


# Create the directory (if needed)
$(TARGETDIR):
	mkdir -p $(TARGETDIR)

$(PACKAGEDIR):
	mkdir -p $(PACKAGEDIR)
