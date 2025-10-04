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
	return opconfig_Write(bq, &config);
}

bool BQ27441_SetGPOUT(BQ27441* bq, BQ27441GPOUTFunction func)
{
	OpConfig config;
	if (!opconfig_Read(bq, &config))
		return false;

	if (config.BatteryLowEnable == func)
		return true; // Already set

	config.BatteryLowEnable = func;
	return opconfig_Write(bq, &config);
}
