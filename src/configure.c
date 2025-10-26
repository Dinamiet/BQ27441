#include "bq27441.h"
#include "commands.h"
#include "endianness.h"
#include "extended.h"

bool BQ27441_Configure(BQ27441* bq, uint16_t capacity, uint16_t terminateVoltage, uint16_t taperCurrent)
{
	uint16_t energy    = capacity * 3.7f;
	uint16_t taperRate = 10 * capacity / taperCurrent;

	uint16_t writeValue = BIG_ENDIAN_16(capacity);
	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_DESIGN_CAPACITY_OFFSET, &writeValue, sizeof(writeValue)))
		return false;

	writeValue = BIG_ENDIAN_16(energy);
	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_DESIGN_ENERGY_OFFSET, &writeValue, sizeof(writeValue)))
		return false;

	writeValue = BIG_ENDIAN_16(terminateVoltage);
	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_TERMINATE_VOLTAGE_OFFSET, &writeValue, sizeof(writeValue)))
		return false;

	writeValue = BIG_ENDIAN_16(taperRate);
	if (!extended_Write(bq, EXTENDED_STATE_CLASSID, EXTENDED_STATE_TAPER_RATE_OFFSET, &writeValue, sizeof(writeValue)))
		return false;

	return true;
}
