LD = ld
CC = gcc
ASM = fasm
QEMU = qemu-system-x86_64

ARCH := $(shell uname -m)

CFLAGS = -m32 -fstack-protector -ffreestanding -fno-pie -I src/impl/x86_64/ -D $(ARCH)

OBJ_DIR = obj
BIN_DIR = bin

KERNEL_SRCS_C =  $(wildcard src/impl/x86_64/kernel/*.c)
LIBC_SRCS_C =    $(wildcard src/impl/x86_64/libc/*.c)
LIBC_SRCS_C +=   $(wildcard src/impl/x86_64/libc/**/*.c)
LIBC_SRCS_C +=   $(wildcard src/impl/x86_64/libc/**/**/*.c)
LIBC_SRCS_C +=   $(wildcard src/impl/x86_64/libc/**/**/**/*.c)
#LIBC_SRCS_S =    $(wildcard src/impl/x86_64/libc/**/**/*.asm)
#LIBC_SRCS_S +=   $(wildcard src/impl/x86_64/libc/**/**/**/*.asm)
DRIVERS_SRCS_C = $(wildcard src/impl/x86_64/drivers/**/*.c)

SRCS_C = $(KERNEL_SRCS_C) $(LIBC_SRCS_C) $(DRIVERS_SRCS_C)
#SRCS_S = $(LIBC_SRCS_S)

OBJS_C = $(addprefix $(OBJ_DIR)/, $(SRCS_C:.c=.o))
#OBJS_S = $(addprefix $(OBJ_DIR)/, $(SRCS_S:.asm=.o))

NAME = yasOS-img.bin

obj/%.o: %.c
	@echo "[compiling... "$(CC)"] "$<
	@$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: %.asm
	@echo "[compiling... "$(ASM)"] "$<
	@$(ASM) $< $@ > /dev/null

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS_C) bootloader kernel
	@echo "[linking ...] "$@
	@cat bin/boot.bin bin/kernel.bin > bin/yasOS-img.bin
	@echo "[build finished]"

$(OBJ_DIR):
	@mkdir -p $(sort $(addprefix $(OBJ_DIR)/, $(dir $(SRCS_C))))
#	@mkdir -p $(sort $(addprefix $(OBJ_DIR)/, $(dir $(SRCS_S))))

run:
	@$(QEMU) -fda bin/yasOS-img.bin

bootloader:
	@mkdir -p $(BIN_DIR)
	@echo "[building bootloader...] "$<
	@$(ASM) src/impl/x86_64/boot/bootsect.asm $(addsuffix /boot.bin, $(BIN_DIR)) > /dev/null

kernel:
	@echo "[compiling 32-bit kernel entry code...] "$<
	@$(ASM) src/impl/x86_64/kernel/entry.asm $(addsuffix /kernel_entry.o, $(OBJ_DIR)) > /dev/null
	@echo "[linking 32-bit kernel...] "$<
	@$(LD) -o bin/kernel.bin -Ttext 0x1000 $(OBJS_C) --oformat binary -m elf_x86_64

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all $(NAME) fclean clean re run bootloader kernel
