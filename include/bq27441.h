#ifndef _BQ27441_H_
#define _BQ27441_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void BQ27441Device;
typedef struct _BQ27441Address_
{
	uint16_t Memory;
	enum
	{
		ADDRESS_MEMORY_NO_ADDRESS,
		ADDRESS_MEMORY_8,
		ADDRESS_MEMORY_16,
	} Mode;
} BQ27441Address;

typedef size_t (*BQ27441_ReadInterface)(const BQ27441Device* device, const BQ27441Address address, void* data, const size_t size);
typedef size_t (*BQ27441_WriteInterface)(const BQ27441Device* device, const BQ27441Address address, const void* data, const size_t size);

typedef enum _BQ27441CurrentType_
{
	BQ27441_CURRENT_AVG,
	BQ27441_CURRENT_STANDBY,
	BQ27441_CURRENT_MAX,
} BQ27441CurrentType;

typedef enum _BQ27441CapacityType_
{
	BQ27441_CAPACITY_REMAINING,             /** Remaining capacity  */
	BQ27441_CAPACITY_FULL,                  /** Fully charged capacity (regulary updated) */
	BQ27441_CAPACITY_REMAINING_COMPENSATED, /** Remaining capcacity compensated for load and temperature */
	BQ27441_CAPACITY_FULL_COMPENSATED,      /** Fully charged capacity compensated for load and temperature (regulary updated) */
	BQ27441_CAPACITY_DESIGNED,              /** Designed capacity */
} BQ27441CapacityType;

typedef enum _BQ27441TemperatureType_
{
	BQ27441_TEMPERATURE_BATTERY,
	BQ27441_TEMPERATURE_INTERNAL,
} BQ27441TemperatureType;

typedef enum _BQ27441StateOfHealthType_
{
	BQ27441_STATEOFHEALTH_PERCENTAGE,
	BQ27441_STATEOFHEALTH_STATUS,
} BQ27441StateOfHealthType;

typedef enum _BQ27441ModeType_
{
	BQ27441_MODE_CONFIGURE,
} BQ27441ModeType;

typedef enum _BQ27441GPOUTFunction_
{
	BQ27441_GPOUT_SOC_INT,
	BQ27441_GPOUT_BAT_LOW,
} BQ27441GPOUTFunction;

typedef enum _BQ27441GPOUTPolarity_
{
	BQ27441_GPOUT_POLARITY_ACTIVE_LOW,
	BQ27441_GPOUT_POLARITY_ACTIVE_HIGH,
} BQ27441GPOUTPolarity;

/** TODO: reference fields to datasheet, and comment each field in detail (same for other structures and enums) */
typedef union _BQ27441Flags_
{
	uint16_t Value;
	struct
	{
		uint16_t Discharging              : 1;
		uint16_t SOCFinalThreshold        : 1;
		uint16_t SOCSetThreshold          : 1;
		uint16_t BatteryDetected          : 1;
		uint16_t ConfigUpdateMode         : 1;
		uint16_t ResetOccured             : 1;
		uint16_t                          : 1;
		uint16_t OCVTaken                 : 1;
		uint16_t FastChargingAllowed      : 1;
		uint16_t FullChargeDetected       : 1;
		uint16_t                          : 4;
		uint16_t UnderTemperatureDetected : 1;
		uint16_t OverTemperatureDetected  : 1;
	};
} BQ27441Flags;

typedef union _BQ27441Status_
{
	uint16_t Value;
	struct
	{
		uint16_t                                 : 1;
		uint16_t VoltageOk                       : 1;
		uint16_t RaUpdateDisabled                : 1;
		uint16_t ConstantPowerModel              : 1;
		uint16_t SleepMode                       : 1;
		uint16_t                                 : 1;
		uint16_t HibernateRequested              : 1;
		uint16_t InitializationComplete          : 1;
		uint16_t ResistanceUpdated               : 1;
		uint16_t QMaxUpdated                     : 1;
		uint16_t CalibrationActive               : 1;
		uint16_t CoulombCounterCalibrationActive : 1;
		uint16_t CalibrationMode                 : 1;
		uint16_t Sealed                          : 1;
		uint16_t WatchdogReset                   : 1;
		uint16_t ShutdownEnable                  : 1;
	};
} BQ27441Status;

typedef struct _BQ27441_
{
	const BQ27441Device*   Device;
	BQ27441_ReadInterface  Read;
	BQ27441_WriteInterface Write;
} BQ27441;

void BQ27441_Init(BQ27441* bq, const BQ27441Device* device, const BQ27441_ReadInterface read_interface, const BQ27441_WriteInterface write_interface);

/** Standard commands */
bool BQ27441_Voltage(BQ27441* bq, uint16_t* voltage);
bool BQ27441_Current(BQ27441* bq, BQ27441CurrentType type, int16_t* current);
bool BQ27441_Capacity(BQ27441* bq, BQ27441CapacityType type, uint16_t* capacity);
bool BQ27441_Power(BQ27441* bq, int16_t* power);
bool BQ27441_StateOfCharge(BQ27441* bq, uint8_t* soc);
bool BQ27441_StateOfHealth(BQ27441* bq, BQ27441StateOfHealthType type, uint8_t* soh);
bool BQ27441_Temperature(BQ27441* bq, BQ27441TemperatureType type, uint16_t* temp);
bool BQ27441_Flags(BQ27441* bq, BQ27441Flags* flags);

/** Subcontrol commands */
bool BQ27441_Status(BQ27441* bq, BQ27441Status* status);
bool BQ27441_Seal(BQ27441* bq);
bool BQ27441_Unseal(BQ27441* bq);
bool BQ27441_SoftReset(BQ27441* bq);

/** Mode commands */
bool BQ27441_EnterMode(BQ27441* bq, BQ27441ModeType mode);

/** Configure commands */
bool BQ27441_Configure(BQ27441* bq, uint16_t capacity, uint16_t terminateVoltage, uint16_t taperCurrent);

/** GPIO Control commands */
bool BQ27441_SetGPOUTPolarity(BQ27441* bq, BQ27441GPOUTPolarity polarity);
bool BQ27441_SetGPOUT(BQ27441* bq, BQ27441GPOUTFunction func);

#endif
