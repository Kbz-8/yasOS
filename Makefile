LD = ld
CC = gcc
ASM = fasm
QEMU = qemu-system-x86_64

CFLAGS = -m32 -ffreestanding -fno-pie -Isrc/impl/x86_64/

OBJ_DIR = obj
BIN_DIR = bin

KERNEL_SRCS = $(wildcard $(addsuffix /*.c, src/impl/x86_64/kernel))
LIBC_SRCS = $(wildcard $(addsuffix /*.c, src/impl/x86_64/libc))

SRCS = $(KERNEL_SRCS) $(LIBC_SRCS)

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

NAME = yasOS-img.bin

obj/%.o: %.c
	@echo "\e[1;32m[compiling... "$(CC)"]\e[1;00m "$<
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS) bootloader kernel
	@echo "\e[1;32m[linking ...]\e[1;00m "$@
	@cat bin/boot.bin bin/kernel.bin > bin/yasOS-img.bin
	@echo "\e[1;32m[build finished]\e[1;00m"

$(OBJ_DIR):
	@mkdir -p $(sort $(addprefix $(OBJ_DIR)/, $(dir $(SRCS))))

run:
	@$(QEMU) -fda bin/yasOS-img.bin

bootloader:
	@mkdir -p $(BIN_DIR)
	@echo "\e[1;32m[building bootloader...]\e[1;00m "$<
	@$(ASM) src/impl/x86_64/boot/bootsect.asm $(addsuffix /boot.bin, $(BIN_DIR))

kernel:
	@echo "\e[1;32m[compiling 32-bit kernel entry code...]\e[1;00m "$<
	@$(ASM) src/impl/x86_64/kernel/entry.asm $(addsuffix /kernel_entry.o, $(OBJ_DIR))
	@echo "\e[1;32m[linking 32-bit kernel...]\e[1;00m "$<
	@$(LD) -o bin/kernel.bin -Ttext 0x1000 $(OBJS) --oformat binary -m elf_i386

.PHONY: all $(NAME) run bootloader kernel
