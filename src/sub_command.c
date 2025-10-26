#include "bq27441.h"
#include "commands.h"

static bool read_subcommand(BQ27441* bq, uint16_t command, uint16_t* data);
static bool execute_subcommand(BQ27441* bq, uint16_t command);

bool BQ27441_Status(BQ27441* bq, BQ27441Status* status) { return read_subcommand(bq, SUB_STATUS, &status->Value); }

bool BQ27441_Seal(BQ27441* bq)
{
	uint16_t success = 0;
	read_subcommand(bq, SUB_SEAL, &success);
	return success;
}

bool BQ27441_Unseal(BQ27441* bq)
{
	uint16_t success = 0;
	read_subcommand(bq, SUB_UNSEAL, &success);
	if (success)
	{
		success = false;
		read_subcommand(bq, SUB_UNSEAL, &success);
	}

	return success;
}

bool BQ27441_SoftReset(BQ27441* bq)
{
	return execute_subcommand(bq, SUB_SOFT_RESET);
}

bool BQ27441_EnterMode(BQ27441* bq, BQ27441ModeType mode)
{
	switch (mode)
	{
		case BQ27441_MODE_CONFIGURE:
			return execute_subcommand(bq, SUB_SET_CFGUPDATE);
			break;
	}

	return false;
}

static bool read_subcommand(BQ27441* bq, uint16_t command, uint16_t* data)
{
	BQ27441Address address = {.Memory = COMMAND_CONTROL, .Mode = ADDRESS_MEMORY_8};

	if (bq->Write(bq->Device, address, &command, sizeof(command)) == sizeof(command))
		return bq->Read(bq->Device, address, data, sizeof(*data)) == sizeof(*data);

	return false;
}

static bool execute_subcommand(BQ27441* bq, uint16_t command)
{
	BQ27441Address address = {.Memory = COMMAND_CONTROL, .Mode = ADDRESS_MEMORY_8};

	return bq->Write(bq->Device, address, &command, sizeof(command)) == sizeof(command);
}
