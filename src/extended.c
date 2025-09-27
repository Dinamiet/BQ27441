#include "extended.h"

#include "commands.h"

#define BLOCK_SIZE 32

static bool blockData_Control(BQ27441* bq);
static bool blockData_Class(BQ27441* bq, uint8_t id);
static bool blockData_Offset(BQ27441* bq, uint8_t offset);
static bool blockData_WriteChecksum(BQ27441* bq, uint8_t checksum);
static bool blockData_Read(BQ27441* bq, uint8_t offset, void* data, size_t size);
static bool blockData_Write(BQ27441* bq, uint8_t offset, void* data, size_t size);

bool extended_Write(BQ27441* bq, uint8_t classID, uint8_t offset, void* data, size_t size)
{
	if (!blockData_Control(bq))
		return false;

	if (!blockData_Class(bq, classID))
		return false;

	if (!blockData_Offset(bq, offset / BLOCK_SIZE))
		return false;

	if (!blockData_Write(bq, offset % BLOCK_SIZE, data, size))
		return false;

	uint8_t blockData[BLOCK_SIZE];
	if (!blockData_Read(bq, 0, blockData, sizeof(blockData)))
		return false;

	uint8_t checksum = 0;
	for (uint8_t i = 0; i < BLOCK_SIZE; i++) { checksum += blockData[i]; }
	checksum = 255 - checksum;

	if (!blockData_WriteChecksum(bq, checksum))
		return false;

	return true;
}

bool extended_Read(BQ27441* bq, uint8_t classID, uint8_t offset, void* data, size_t size)
{
	if (!blockData_Control(bq))
		return false;

	if (!blockData_Class(bq, classID))
		return false;

	if (!blockData_Offset(bq, offset / BLOCK_SIZE))
		return false;

	return blockData_Read(bq, offset % BLOCK_SIZE, data, size);
}

static bool blockData_Control(BQ27441* bq)
{
	BQ27441Address address = {.Memory = EXTENDED_DATA_CONTROL, .Mode = ADDRESS_MEMORY_8};
	uint8_t        data    = 0x00;
	return bq->Write(bq->Device, address, &data, sizeof(data)) == sizeof(data);
}

static bool blockData_Class(BQ27441* bq, uint8_t id)
{
	BQ27441Address address = {.Memory = EXTENDED_DATA_CLASS, .Mode = ADDRESS_MEMORY_8};
	return bq->Write(bq->Device, address, &id, sizeof(id)) == sizeof(id);
}

static bool blockData_Offset(BQ27441* bq, uint8_t offset)
{
	BQ27441Address address = {.Memory = EXTENDED_DATA_BLOCK, .Mode = ADDRESS_MEMORY_8};
	return bq->Write(bq->Device, address, &offset, sizeof(offset)) == sizeof(offset);
}

static bool blockData_WriteChecksum(BQ27441* bq, uint8_t checksum)
{
	BQ27441Address address = {.Memory = EXTENDED_DATA_CHECKSUM, .Mode = ADDRESS_MEMORY_8};
	return bq->Write(bq->Device, address, &checksum, sizeof(checksum)) == sizeof(checksum);
}

static bool blockData_Read(BQ27441* bq, uint8_t offset, void* data, size_t size)
{
	BQ27441Address address = {.Memory = EXTENDED_DATA_DATA + offset, .Mode = ADDRESS_MEMORY_8};
	return bq->Read(bq->Device, address, data, size) == size;
}

static bool blockData_Write(BQ27441* bq, uint8_t offset, void* data, size_t size)
{
	BQ27441Address address = {.Memory = EXTENDED_DATA_DATA + offset, .Mode = ADDRESS_MEMORY_8};
	return bq->Write(bq->Device, address, data, size) == size;
}
