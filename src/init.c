#include "bq27441.h"

void BQ27441_Init(BQ27441* bq, const BQ27441Device* device, const BQ27441_ReadInterface read_interface, const BQ27441_WriteInterface write_interface, const BQ27441_WaitInterface wait_interface)
{
	bq->Device = device;
	bq->Read   = read_interface;
	bq->Write  = write_interface;
	bq->Wait   = wait_interface;
}
