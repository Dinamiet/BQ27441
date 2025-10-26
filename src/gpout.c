#include "bq27441.h"
#include "opconfig.h"

bool BQ27441_SetGPOUTPolarity(BQ27441* bq, BQ27441GPOUTPolarity polarity)
{
	OpConfig config;
	if (!opconfig_Read(bq, &config))
		return false;

	if (config.GPOUTPolarity == polarity)
		return true; // Already set

	config.GPOUTPolarity = polarity;
	return opconfig_Write(bq, config);
}

bool BQ27441_SetGPOUTMode(BQ27441* bq, BQ27441GPOUTMode mode)
{
	OpConfig config;
	if (!opconfig_Read(bq, &config))
		return false;

	if (config.BatteryLowEnable == mode)
		return true; // Already set

	config.BatteryLowEnable = mode;
	return opconfig_Write(bq, config);
}
