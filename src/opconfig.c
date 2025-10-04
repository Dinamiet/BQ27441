#include "opconfig.h"

#include "commands.h"
#include "extended.h"

bool opconfig_Read(BQ27441* bq, OpConfig* config)
{
	BQ27441Address address = {.Memory = EXTENDED_OPCONFIG, .Mode = ADDRESS_MEMORY_8};
	return bq->Read(bq->Device, address, config, sizeof(*config)) == sizeof(*config);
}

bool opconfig_Write(BQ27441* bq, OpConfig* config) { return extended_Write(bq, EXTENDED_OPCONFIG_CLASSID, 0, config, sizeof(*config)); }
