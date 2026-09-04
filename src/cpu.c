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
	return emu->memory[physical_address & 0xFFFFF];
};

void cpu_write_byte(Emulator8086 *emu, uint32_t physical_address, uint8_t val){
	emu->memory[physical_address & 0xFFFFF] = val;
};

void cpu_step(Emulator8086 *emu){
	uint32_t physical_addr = ((uint32_t)emu->cpu.cs << 4) + emu->cpu.ip;
	uint8_t opcode = cpu_read_byte(emu, physical_addr);
	switch (opcode){
		case 0x90:
			emu->cpu.ip++;
			break;
	
		default:
		emu->running = false;
		break;
	}
}
