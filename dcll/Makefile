CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra
LDFLAGS  := -L /usr/lib -lstdc++ -lm
INCLUDES := -I include -I /usr/local/include
LIBS     :=

TARGET   := demo
BUILD    := build
BIN      := ${BUILD}/bin
OBJ      := ${BUILD}/obj
SRC      := .

SOURCES  := $(wildcard ${SRC}/*.cpp)
OBJECTS  := $(SOURCES:${SRC}/%.cpp=${OBJ}/%.o)
DEPS     := $(OBJECTS:.o=.d)


.DEFAULT_GOAL := release

.PHONY: d debug
d: debug
debug: CXXFLAGS += -DDEBUG -g
debug: all

.PHONY: r release
r: release
release: CXXFLAGS += -O2
release: all

.PHONY: all
all: export CFLAGS := $(CFLAGS) $(CXXFLAGS)
all: dirs ${BIN}/${TARGET}

${BIN}/${TARGET}: $(OBJECTS)
	@echo -e "\n> Linking: $(TARGET)"
	$(CXX) $(LDFLAGS) $(LIBS) -o $@ $^

	@echo -e "\n> Symlink"
	@rm -f $(TARGET)
	@ln -vs ${BIN}/${TARGET} $(TARGET)

-include $(DEPS)

${OBJ}/%.o: ${SRC}/%.cpp
	@echo -e "\n> Compiling: $< -> $@"
	$(CXX) $(CFLAGS) $(INCLUDES) -MP -MMD -o $@ -c $<

.PHONY: dirs
dirs:
	@echo -e "\n> Creating directories"
	@mkdir -vp $(BIN)
	@mkdir -vp $(dir ${OBJECTS})

.PHONY: clean
clean:
	@echo -e "\n> Cleaning up"
	@rm -vf  $(TARGET)
	@rm -vfr $(BUILD)
