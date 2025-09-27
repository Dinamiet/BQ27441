#include "bq27441.h"
#include "commands.h"
#include "extended.h"

bool BQ27441_Configure(BQ27441* bq, uint16_t capacity, uint16_t terminateVoltage, uint16_t taperCurrent)
{
	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_DESIGN_CAPACITY_OFFSET, &capacity, sizeof(capacity)))
		return false;

	uint16_t energy = capacity * 3.7f;
	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_DESIGN_ENERGY_OFFSET, &energy, sizeof(energy)))
		return false;

	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_TERMINATE_VOLTAGE_OFFSET, &terminateVoltage, sizeof(terminateVoltage)))
		return false;

	uint16_t taperRate = 10 * capacity / taperCurrent;
	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_TAPER_RATE_OFFSET, &taperRate, sizeof(taperRate)))
		return false;

	return true;
}
