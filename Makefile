PROJECT := linux_loader
TARGETS := $(PROJECT).elf $(PROJECT).bin

all: $(TARGETS)

#PREFIX:=riscv64-unknown-elf-
#CFLAGS:=-I/usr/include

PREFIX := ccache riscv64-unknown-elf-
CFLAGS := -fno-stack-protector
CFLAGS += -static-libgcc -fdata-sections -ffunction-sections -Wbuiltin-declaration-mismatch
CFLAGS += -g -Os -march=rv32ima -mabi=ilp32 -static
LDFLAGS:= -T linker.lds -nostdlib -Wl,--gc-sections

C_TARGETS := main.c loader.c utils.c fat.c

$(PROJECT).elf: $(C_TARGETS) entry.S
	$(PREFIX)gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(PROJECT).bin: $(PROJECT).elf
	$(PREFIX)objcopy $^ -O binary $@

test: $(PROJECT).bin
	cd ../mini-rv32ima/mini-rv32ima; make mini-rv32ima
	../mini-rv32ima/mini-rv32ima/mini-rv32ima -f $< -z ../disk_img

clean :
	rm -rf $(TARGETS)