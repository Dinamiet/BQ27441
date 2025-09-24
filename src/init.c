#include "bq27441.h"

void BQ27441_Init(
		BQ27441*                        bq,
		const I2CDevice*                      device,
		const BQ27441_ReadInterface     read_interface,
		const BQ27441_WriteInterface    write_interface,
		const BQ27441_MemReadInterface  mem_read_interface,
		const BQ27441_MemWriteInterface mem_write_interface)
{
	bq->Device = device;
	bq->Read = read_interface;
	bq->Write = write_interface;
	bq->MemRead = mem_read_interface;
	bq->MemWrite = mem_write_interface;
}
