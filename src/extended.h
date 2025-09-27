#ifndef _EXTENDED_H_
#define _EXTENDED_H_

#include "bq27441.h"

bool extended_Write(BQ27441* bq, uint8_t classID, uint8_t offset, void* data, size_t size);
bool extended_Read(BQ27441* bq, uint8_t classID, uint8_t offset, void* data, size_t size);

#endif
