# CoolMyPS3 project

# Define the variables
TARGET = CoolMyPS3
SELF_PATH = $(TARGET).self
SRC_PATH = main.c

# Set the paths
PS3SDK = /c/PSDK3v2
PS3_SYS_MODULES = $(PS3SDK)/ps3dev/lib/ppu

# Set the compiler and linker flags
CFLAGS = -O2 -Wall -DPRX_PATH="\"$(SELF_PATH)\""
LDFLAGS = -L$(PS3_SYS_MODULES) -Wl,-Bstatic -lpsl1ght -lps3sound -lTiny3D -Wl,-Bdynamic -Wl,--no-undefined

# Define the clean target
.PHONY: clean
clean:
	$(RM) $(SELF_PATH) $(TARGET).elf

# Define the default target
.PHONY: all
all: $(SELF_PATH)

# Define the .self target
$(SELF_PATH): $(TARGET).elf
	$(PS3SDK)/fake_scetool/fake_scetool -k $(PS3_SYS_MODULES) -k $(SELF_PATH)

# Define the .elf target
$(TARGET).elf: $(SRC_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH) $(LDFLAGS) -o $(TARGET).elf

# Set the default compiler
CC = gcc