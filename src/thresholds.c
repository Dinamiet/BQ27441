#include "bq27441.h"
#include "commands.h"
#include "extended.h"

typedef struct _Threshold_
{
	uint8_t Set;
	uint8_t Clear;
} Threshold;

bool BQ27441_SetSOCLowThreshold(BQ27441* bq, uint8_t setValue, uint8_t clearValue)
{
	Threshold th = {.Set = setValue, .Clear = clearValue};
	return extended_Write(bq, EXTENDED_DISCHARGE_CLASSID, EXTENDED_DISCHARGE_SOC_LOW_OFFSET, &th, sizeof(th));
}

bool BQ27441_SetSOCCriticalThreshold(BQ27441* bq, uint8_t setValue, uint8_t clearValue)
{
	Threshold th = {.Set = setValue, .Clear = clearValue};
	return extended_Write(bq, EXTENDED_DISCHARGE_CLASSID, EXTENDED_DISCHARGE_SOC_CRITICAL_OFFSET, &th, sizeof(th));
}
