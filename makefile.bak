TARGET    = vpr-midas

CC        = x86_64-w64-mingw32-gcc-posix
CFLAGS    = -std=c17 -O2 -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion

LD        = x86_64-w64-mingw32-gcc-posix
LDFLAGS   = -nostdinc++

BIN       = bin
OBJ       = build
BUILD     = build
SOURCE    = src

SOURCES   = $(wildcard $(SOURCE)/*.c)
DEBUG     = $(patsubst $(SOURCE)/%.c,$(OBJ)/debug/%.obj,$(SOURCES))
RELEASE   = $(patsubst $(SOURCE)/%.c,$(OBJ)/release/%.obj,$(SOURCES))

INCLUDE   = Includes
INCLUDES  = $(addprefix -I,$(INCLUDE))

ifeq ($(PREFIX),)
PREFIX    = /usr/local
endif

MAKEFLAGS += -j$(shell nproc)

all: debug

debug:   CFLAGS  += -g
release: CFLAGS  += -DRELEASE -O3 -fno-ident -ffast-math -fvisibility=hidden
release: LDFLAGS += -s

debug:   $(BIN)/$(TARGET)_d
release: $(BIN)/$(TARGET)

$(BIN)/$(TARGET)_d: $(BIN) $(BUILD) $(DEBUG)
	$(LD) $(LDFLAGS) $(DEBUG) -o $(BIN)/$(TARGET)_d

$(BIN)/$(TARGET): $(BIN) $(BUILD) $(RELEASE)
	$(LD) $(LDFLAGS) $(RELEASE) -o $(BIN)/$(TARGET)

$(DEBUG): $(OBJ)/debug/%.obj : $(SOURCE)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(RELEASE): $(OBJ)/release/%.obj : $(SOURCE)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN):
	mkdir -p $@

$(BUILD):
	mkdir -p $@/debug
	mkdir -p $@/release

.PHONY: install
install: release
	cp $(BIN)/$(TARGET).exe $(BIN)/$(TARGET)
	install -d $(PREFIX)/bin
	install -m 555 $(BIN)/$(TARGET) $(PREFIX)/bin
	rm $(BIN)/$(TARGET)

.PHONY: clean
clean:
	rm -fr $(BIN)/*
	rm -fr $(BUILD)/debug/*
	rm -fr $(BUILD)/release/*

.PHONY: extra-clean
extra-clean:
	rm -fr $(BIN)
	rm -fr $(BUILD)
