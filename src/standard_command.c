#include "bq27441.h"
#include "commands.h"

bool BQ27441_Voltage(BQ27441* bq, uint16_t* voltage)
{
	BQ27441Address address = {.Memory = COMMAND_VOLTAGE, .Mode = ADDRESS_MEMORY_8};
	return bq->Read(bq->Device, address, voltage, sizeof(*voltage)) == sizeof(*voltage);
}

bool BQ27441_Current(BQ27441* bq, BQ27441CurrentType type, int16_t* current)
{
	BQ27441Address address = {.Mode = ADDRESS_MEMORY_8};
	switch (type)
	{
		case BQ27441_CURRENT_AVG:
			address.Memory = COMMAND_CURRENT_AVG;
			break;

		case BQ27441_CURRENT_STANDBY:
			address.Memory = COMMAND_CURRENT_STANDBY;
			break;

		case BQ27441_CURRENT_MAX:
			address.Memory = COMMAND_CURRENT_MAX;
			break;
	}

	return bq->Read(bq->Device, address, current, sizeof(*current)) == sizeof(*current);
}

bool BQ27441_Capacity(BQ27441* bq, BQ27441CapacityType type, uint16_t* capacity)
{
	BQ27441Address address = {.Mode = ADDRESS_MEMORY_8};
	switch (type)
	{
		case BQ27441_CAPACITY_REMAINING:
			address.Memory = COMMAND_CAPACITY_REMAIN;
			break;
		case BQ27441_CAPACITY_FULL:
			address.Memory = COMMAND_CAPACITY_FULL;
			break;
		case BQ27441_CAPACITY_REMAINING_COMPENSATED:
			address.Memory = COMMAND_CAPACITY_REMAIN_COMP;
			break;
		case BQ27441_CAPACITY_FULL_COMPENSATED:
			address.Memory = COMMAND_CAPACITY_FULL_COMP;
			break;
		case BQ27441_CAPACITY_DESIGNED:
			address.Memory = EXTENDED_CAPACITY_DESIGNED;
			break;
	}

	return bq->Read(bq->Device, address, capacity, sizeof(*capacity)) == sizeof(*capacity);
}

bool BQ27441_Power(BQ27441* bq, uint16_t* power)
{
	BQ27441Address address = {.Memory = COMMAND_POWER_AVG, .Mode = ADDRESS_MEMORY_8};
	return bq->Read(bq->Device, address, power, sizeof(*power)) == sizeof(*power);
}

bool BQ27441_StateOfCharge(BQ27441* bq, uint8_t* soc)
{
	BQ27441Address address = {.Memory = COMMAND_SOC, .Mode = ADDRESS_MEMORY_8};
	return bq->Read(bq->Device, address, soc, sizeof(*soc)) == sizeof(*soc);
}

bool BQ27441_StateOfHealth(BQ27441* bq, BQ27441StateOfHealthType type, uint8_t* soh)
{
	BQ27441Address address = {.Memory = COMMAND_SOH + type, .Mode = ADDRESS_MEMORY_8};
	return bq->Read(bq->Device, address, soh, sizeof(*soh)) == sizeof(*soh);
}

bool BQ27441_Temperature(BQ27441* bq, BQ27441TemperatureType type, uint16_t* temp)
{
	BQ27441Address address = {.Mode = ADDRESS_MEMORY_8};
	switch (type)
	{
		case BQ27441_TEMPERATURE_BATTERY:
			address.Memory = COMMAND_TEMPERATURE_BATTERY;
			break;
		case BQ27441_TEMPERATURE_INTERNAL:
			address.Memory = COMMAND_TEMPERATURE_INTERNAL;
			break;
	}

	return bq->Read(bq->Device, address, temp, sizeof(*temp)) == sizeof(*temp);
}

bool BQ27441_Flags(BQ27441* bq, BQ27441Flags* flags)
{
	BQ27441Address address = {.Memory = COMMAND_FLAGS, .Mode = ADDRESS_MEMORY_8};
	return bq->Read(bq->Device, address, flags, sizeof(*flags)) == sizeof(*flags);
}
