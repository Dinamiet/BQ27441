#ifndef _BQ27441_H_
#define _BQ27441_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct _I2CDevice_ I2CDevice;

typedef size_t (*BQ27441_ReadInterface)(const I2CDevice* device, void* data, const size_t size);
typedef size_t (*BQ27441_WriteInterface)(const I2CDevice* device, const void* data, const size_t size);
typedef size_t (*BQ27441_MemReadInterface)(const I2CDevice* device, uint8_t address, void* data, const size_t size);
typedef size_t (*BQ27441_MemWriteInterface)(const I2CDevice* device, const uint8_t address, const void* data, const size_t size);

typedef enum _BQ27441CurrentType_
{
	BQ27441_CURRENT_AVG,
	BQ27441_CURRENT_STANDBY,
	BQ27441_CURRENT_MAX,
} BQ27441CurrentType;

typedef enum _BQ27441CapacityType_
{
	BQ27441_CAPACITY_REMAINING,             /** Remaining capacity  */
	BQ27441_CAPACITY_FULL,                  /** Fully charged capacity (regulary updated) */
	BQ27441_CAPACITY_REMAINING_COMPENSATED, /** Remaining capcacity compensated for load and temperature */
	BQ27441_CAPACITY_FULL_COMPENSATED,      /** Fully charged capacity compensated for load and temperature (regulary updated) */
	BQ27411_CAPACITY_DESIGNED,              /** Designed capacity */
} BQ27441CapacityType;

typedef enum _BQ27441TemperatureType_
{
	BQ27411_TEMPERATURE_BATTERY,
	BQ27411_TEMPERATURE_INTERNAL,
} BQ27411TemperatureType;

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

/** Battery Parameter configuration */
bool BQ27441_SetDesignCapacity(BQ27441* bq, uint16_t capacity);

/** Battery Characteristics */
bool BQ27441_Voltage(BQ27441* bq, uint16_t* voltage);
bool BQ27441_Current(BQ27441* bq, BQ27441CurrentType type, int16_t* current);
bool BQ27441_Capacity(BQ27441* bq, BQ27441CapacityType type, uint16_t* capacity);
bool BQ27441_Power(BQ27441* bq, uint16_t* power);
bool BQ27441_StateOfCharge(BQ27441* bq, uint16_t* soc);
bool BQ27441_StateOfHealth(BQ27441* bq, uint16_t* soh);
bool BQ27441_Temperature(BQ27441* bq, uint16_t* temp);

/** GPIO Control commands */
/** TODO: GPIO control */

/** Control subcommands */
/** TODO: Control subcommands */

/** Extended Data Commands */
/** TODO: Extended Data Commands */

#endif
