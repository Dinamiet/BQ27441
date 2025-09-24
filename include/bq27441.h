#ifndef _BQ27441_H_
#define _BQ27441_H_

#include <stddef.h>
#include <stdint.h>

typedef struct _I2CDevice_ I2CDevice;

typedef size_t (*BQ27441_ReadInterface)(const I2CDevice* device, void* data, const size_t size);
typedef size_t (*BQ27441_WriteInterface)(const I2CDevice* device, const void* data, const size_t size);
typedef size_t (*BQ27441_MemReadInterface)(const I2CDevice* device, uint16_t address, void* data, const size_t size);
typedef size_t (*BQ27441_MemWriteInterface)(const I2CDevice* device, const uint16_t address, const void* data, const size_t size);

typedef struct _BQ27441_
{
	const I2CDevice*          Device;
	BQ27441_ReadInterface     Read;
	BQ27441_WriteInterface    Write;
	BQ27441_MemReadInterface  MemRead;
	BQ27441_MemWriteInterface MemWrite;
} BQ27441;

void BQ27441_Init(
		BQ27441*                        bq,
		const I2CDevice*                device,
		const BQ27441_ReadInterface     read_interface,
		const BQ27441_WriteInterface    write_interface,
		const BQ27441_MemReadInterface  mem_read_interface,
		const BQ27441_MemWriteInterface mem_write_interface);

#endif
