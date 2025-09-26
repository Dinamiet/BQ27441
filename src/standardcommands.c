#include "bq27441.h"
#include "registers.h"

bool BQ27441_Voltage(BQ27441* bq, uint16_t* voltage) { return bq->MemRead(bq->Device, COMMAND_VOLTAGE, voltage, sizeof(*voltage)) == sizeof(*voltage); }

bool BQ27441_Current(BQ27441* bq, BQ27441CurrentType type, int16_t* current)
{
	uint8_t address;
	switch (type)
	{
		case BQ27441_CURRENT_AVG:
			address = COMMAND_CURRENT_AVG;
			break;

		case BQ27441_CURRENT_STANDBY:
			address = COMMAND_CURRENT_STANDBY;
			break;

		case BQ27441_CURRENT_MAX:
			address = COMMAND_CURRENT_MAX;
			break;
	}

	return bq->MemRead(bq->Device, address, current, sizeof(*current)) == sizeof(*current);
}

bool BQ27441_Capacity(BQ27441* bq, BQ27441CapacityType type, uint16_t* capacity)
{
	uint8_t address;
	switch (type)
	{
		case BQ27441_CAPACITY_REMAINING:
			address = COMMAND_CAPACITY_REMAIN;
			break;
		case BQ27441_CAPACITY_FULL:
			address = COMMAND_CAPACITY_FULL;
			break;
		case BQ27441_CAPACITY_REMAINING_COMPENSATED:
			address = COMMAND_CAPACITY_REMAIN_COMP;
			break;
		case BQ27441_CAPACITY_FULL_COMPENSATED:
			address = COMMAND_CAPACITY_FULL_COMP;
			break;
		case BQ27441_CAPACITY_DESIGNED:
			address = EXTENDED_CAPACITY_DESIGNED;
			break;
	}

	return bq->MemRead(bq->Device, address, capacity, sizeof(*capacity)) == sizeof(*capacity);
}

bool BQ27441_Power(BQ27441* bq, uint16_t* power) { return bq->MemRead(bq->Device, COMMAND_POWER_AVG, power, sizeof(*power)) == sizeof(*power); }

bool BQ27441_StateOfCharge(BQ27441* bq, uint16_t* soc) { return bq->MemRead(bq->Device, COMMAND_SOC, soc, sizeof(*soc)) == sizeof(*soc); }

bool BQ27441_StateOfHealth(BQ27441* bq, BQ27441StateOfHealth* soh)
{
	return bq->MemRead(bq->Device, COMMAND_SOH, soh, sizeof(*soh)) == sizeof(*soh);
}

bool BQ27441_Temperature(BQ27441* bq, BQ27441TemperatureType type, uint16_t* temp)
{
	uint8_t address;
	switch (type)
	{
		case BQ27441_TEMPERATURE_BATTERY:
		address = COMMAND_TEMPERATURE_BATTERY;
			break;
		case BQ27441_TEMPERATURE_INTERNAL:
		address = COMMAND_TEMPERATURE_INTERNAL;
			break;
	}

	return bq->MemRead(bq->Device, address, temp, sizeof(*temp)) == sizeof(*temp);
}

bool BQ27441_Flags(BQ27441* bq, BQ27441Flags* flags)
{
	return bq->MemRead(bq->Device, COMMAND_FLAGS, flags, sizeof(*flags)) == sizeof(*flags);
}
