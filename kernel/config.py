ARCH = "x86_64"
BOOTLOADER = "limine"
CC = "x86_64-elf-gcc"
CCFLAGS = f'-O2 -Iinclude -D{BOOTLOADER}_BOOTLOADER -Wall -Wextra -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -fPIE -m64 -march=x86-64 -mabi=sysv -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone'
LD = "x86_64-elf-ld"
LDFLAGS = "-m elf_x86_64 -nostdlib -static -pie --no-dynamic-linker -z text -z max-page-size=0x1000 -T linker.ld"
