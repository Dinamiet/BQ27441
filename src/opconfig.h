#ifndef _OPCONFIG_H_
#define _OPCONFIG_H_

#include "bq27441.h"
#include <stdint.h>

typedef struct _OpConfig_
{
	uint16_t TemperatureDevice      : 1;
	uint16_t                        : 1;
	uint16_t BatteryLowEnable       : 1;
	uint16_t                        : 1;
	uint16_t RMFCC                  : 1;
	uint16_t Sleep                  : 1;
	uint16_t                        : 1;
	uint16_t                        : 1;
	uint16_t                        : 1;
	uint16_t                        : 1;
	uint16_t                        : 1;
	uint16_t GPOUTPolarity          : 1;
	uint16_t PullUpEnabled          : 1;
	uint16_t BatteryInsertionEnable : 1;
	uint16_t                        : 1;
	uint16_t                        : 1;
} OpConfig;

bool opconfig_Read(BQ27441* bq, OpConfig* config);
bool opconfig_Write(BQ27441* bq, OpConfig* config);

#endif
