#include <stdint.h>
#include "gdt.h"
#include <stdio.h>

gdt_entry_t gdt_e[5];
gdt_descriptor_t gdt_d;

gdt_entry_t set_gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entry_t temp_gdt;
    
    temp_gdt.base_low = (base & 0xFFFF);
    temp_gdt.base_mid = (base >> 16) & 0xFF;
    temp_gdt.base_high = (base >> 24) & 0xFF;

    temp_gdt.limit_low = (limit & 0xFFFF);
    
    temp_gdt.granularity = ((limit >> 16) & 0x0F);
    temp_gdt.granularity |= (granularity & 0xF0);
    
    temp_gdt.access = access;

    return temp_gdt;
}

void gdt_init(void) {
    printf("Setting up the GDT: ");

    gdt_d.base = (uint64_t)&gdt_e;
    gdt_d.limit = (uint16_t)(sizeof(gdt_entry_t) * 3) - 1;

    gdt_e[0] = set_gdt_entry(0, 0, 0, 0); //NULL segment
    gdt_e[1] = set_gdt_entry(0, 0xFFFFFFFF, 0b10011010, 0b11000000); //Kernel code segment
    gdt_e[2] = set_gdt_entry(0, 0xFFFFFFFF, 0b10011010, 0b11000000); //Kernel data segment
    gdt_e[3] = set_gdt_entry(0, 0xFFFFFFFF, 0b11111010, 0b11000000); //Usermode code segment
    gdt_e[4] = set_gdt_entry(0, 0xFFFFFFFF, 0b11110010, 0b11000000); //Usermode date segment

    asm volatile("lgdt %0" : : "m"(gdt_d));

    printf("[DONE]\n");
}