CC=g++
INCLUDE=lib/
EXTERN_LIBS=`pkg-config --cflags --libs opencv4`

source_files = $(wildcard src/*.cpp)
binary_files := $(patsubst src/%.cpp,bin/%,$(source_files))

all: $(binary_files)
	@echo $(binary_files)

$(binary_files): $(source_files)
	@mkdir -p $(dir $@)
	$(CC) -I $(INCLUDE) $(patsubst bin/%,src/%.cpp,$@) -o $@ $(EXTERN_LIBS)

.PHONY: clean
clean:
	rm -r bin

