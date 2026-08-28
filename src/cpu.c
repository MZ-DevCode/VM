#include "cpu.h"
#include <string.h>

void cpu_init(Emulator8086 *emu){
	memset(emu->memory, 0, sizeof(emu->memory));
	memset(&emu->cpu, 0, sizeof(Registers8086));	

	emu->cpu.cs = 0xF000;
	emu->cpu.ip = 0x0000;

	emu->running = true;
};

uint8_t cpu_read_byte(Emulator8086 *emu, uint32_t physical_address){

};

void cpu_write_byte(Emulator8086 *emu, uint32_t physical_address, uint8_t val){

};
