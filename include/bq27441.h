#ifndef _BQ27441_H_
#define _BQ27441_H_

/**
 * \file
 * BQ27441 fuel gauge driver.
 *
 * This driver is designed to be used with the BQ27441 fuel gauge IC, but may be compatible with other similar ICs.
 * It provides an interface for reading various parameters such as voltage, current, capacity, power, state of charge, state of health, temperature, and flags.
 * It also includes functions for controlling the device's modes and GPIO settings.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void BQ27441Device; /**< I2C device forward declaration */

/**
 * Structure representing an address for reading/writing data from/to the BQ27441 device.
 * The Memory field specifies the memory address to access, while the Mode field indicates the addressing mode (no address, 8-bit, or 16-bit).
 */
typedef struct _BQ27441Address_
{
	uint16_t Memory; /**< Memory address to access */
	enum
	{
		ADDRESS_MEMORY_NO_ADDRESS, /**< Access without an address */
		ADDRESS_MEMORY_8,          /**< Access memory with an 8-bit address */
		ADDRESS_MEMORY_16,         /**< Access memory with a 16-bit address */
	} Mode;                        /**< Access mode */
} BQ27441Address;

/**
 * BQ27441 Read interface
 * \param device Pointer to the BQ27441 device
 * \param address Address structure specifying the memory address and access mode
 * \param data Pointer to the buffer where the read data will be stored
 * \param size Size of the data to read in bytes
 * \return Number of bytes read
 */
typedef size_t (*BQ27441_ReadInterface)(const BQ27441Device* device, const BQ27441Address address, void* data, const size_t size);

/**
 * BQ27441 Write interface
 * \param device Pointer to the BQ27441 device
 * \param address Address structure specifying the memory address and access mode
 * \param data Pointer to the buffer containing the data to write
 * \param size Size of the data to write in bytes
 * \return Number of bytes written
 */
typedef size_t (*BQ27441_WriteInterface)(const BQ27441Device* device, const BQ27441Address address, const void* data, const size_t size);

/**
 * BQ27441 Wait interface
 * \param us Number of microseconds to wait
 * This function is used to introduce a delay in the execution, which may be necessary for certain operations or timing requirements when communicating with the BQ27441 device.
 */
typedef void (*BQ27441_WaitInterface)(size_t us);

/**
 * Current types
 */
typedef enum _BQ27441CurrentType_
{
	BQ27441_CURRENT_AVG,     /**< Average current */
	BQ27441_CURRENT_STANDBY, /**< Standby current */
	BQ27441_CURRENT_MAX,     /**< Maximum current */
} BQ27441CurrentType;

/**
 * Capacity types
 */
typedef enum _BQ27441CapacityType_
{
	BQ27441_CAPACITY_REMAINING,             /**< Remaining capacity  */
	BQ27441_CAPACITY_FULL,                  /**< Fully charged capacity (regulary updated) */
	BQ27441_CAPACITY_REMAINING_COMPENSATED, /**< Remaining capcacity compensated for load and temperature */
	BQ27441_CAPACITY_FULL_COMPENSATED,      /**< Fully charged capacity compensated for load and temperature (regulary updated) */
	BQ27441_CAPACITY_DESIGNED,              /**< Designed capacity */
} BQ27441CapacityType;

/**
 * Temperature types
 */
typedef enum _BQ27441TemperatureType_
{
	BQ27441_TEMPERATURE_BATTERY,  /**< Battery temperature */
	BQ27441_TEMPERATURE_INTERNAL, /**< Internal temperature */
} BQ27441TemperatureType;

/**
 * State of health types
 */
typedef enum _BQ27441StateOfHealthType_
{
	BQ27441_STATEOFHEALTH_PERCENTAGE, /**< State of health as a percentage */
	BQ27441_STATEOFHEALTH_STATUS,     /**< State of health as a status */
} BQ27441StateOfHealthType;

/**
 * Mode types
 */
typedef enum _BQ27441ModeType_
{
	BQ27441_MODE_CONFIGURE, /**< Configure mode for setting parameters such as capacity, terminate voltage, and taper current */
} BQ27441ModeType;

/**
 * GPOUT modes
 */
typedef enum _BQ27441GPOUTFunction_
{
	BQ27441_GPOUT_SOC_INT, /**< State of charge interrupt */
	BQ27441_GPOUT_BAT_LOW, /**< Battery low interrupt */
} BQ27441GPOUTMode;

/**
 * GPOUT polarity options
 */
typedef enum _BQ27441GPOUTPolarity_
{
	BQ27441_GPOUT_POLARITY_ACTIVE_LOW,  /**< Active low polarity */
	BQ27441_GPOUT_POLARITY_ACTIVE_HIGH, /**< Active high polarity */
} BQ27441GPOUTPolarity;

/**
 * BQ27441 device flags
 */
typedef union _BQ27441Flags_
{
	uint16_t Value;
	struct
	{
		uint16_t Discharging              : 1;
		uint16_t SOCCriticalThreshold     : 1;
		uint16_t SOCLowThreshold          : 1;
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

/**
 * BQ27441 device status
 */
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

/** BQ27441 device */
typedef struct _BQ27441_
{
	const BQ27441Device*   Device;
	BQ27441_ReadInterface  Read;
	BQ27441_WriteInterface Write;
	BQ27441_WaitInterface  Wait;
} BQ27441;

/** Initialize the BQ27441 device
 * \param bq BQ27441 device to initialize
 * \param device I2C device to use for communication
 * \param read_interface Read interface for the device
 * \param write_interface Write interface for the device
 * \param wait_interface Wait interface for the device
 */
void BQ27441_Init(BQ27441* bq, const BQ27441Device* device, const BQ27441_ReadInterface read_interface, const BQ27441_WriteInterface write_interface, const BQ27441_WaitInterface wait_interface);

/**
 * Read voltage
 * \param bq BQ27441 device
 * \param voltage Read voltage value
 * \return true if the voltage was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Voltage(BQ27441* bq, uint16_t* voltage);

/**
 * Read current
 * \param bq BQ27441 device
 * \param type Type of current to read (average, standby, or maximum)
 * \param current Read current value
 * \return true if the current was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Current(BQ27441* bq, BQ27441CurrentType type, int16_t* current);

/** Read capacity
 * \param bq BQ27441 device
 * \param type Type of capacity to read (nominal, full, or remaining)
 * \param capacity Read capacity value
 * \return true if the capacity was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Capacity(BQ27441* bq, BQ27441CapacityType type, uint16_t* capacity);

/**
 * Read current power usage
 * \param bq BQ27441 device
 * \param power Read power value
 * \return true if the power was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Power(BQ27441* bq, int16_t* power);

/**
 * Read state of charge
 * \param bq BQ27441 device
 * \param soc Read state of charge value
 * \return true if the state of charge was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_StateOfCharge(BQ27441* bq, uint8_t* soc);

/**
 * Read state of health
 * \param bq BQ27441 device
 * \param type Type of state of health to read (percentage or status)
 * \param soh Read state of health value
 * \return true if the state of health was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_StateOfHealth(BQ27441* bq, BQ27441StateOfHealthType type, uint8_t* soh);

/**
 * Read temperature
 * \param bq BQ27441 device
 * \param type Type of temperature to read (battery or internal)
 * \param temp Read temperature value
 * \return true if the temperature was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Temperature(BQ27441* bq, BQ27441TemperatureType type, uint16_t* temp);

/**
 * Read flags
 * \param bq BQ27441 device
 * \param flags Read flags value
 * \return true if the flags were successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Flags(BQ27441* bq, BQ27441Flags* flags);

/**
 * Read status
 * \param bq BQ27441 device
 * \param status Read status value
 * \return true if the status was successfully read, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Status(BQ27441* bq, BQ27441Status* status);

/**
 * Seal the device
 * \param bq BQ27441 device
 * \return true if the device was successfully sealed, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Seal(BQ27441* bq);

/**
 * Unseal the device
 * \param bq BQ27441 device
 * \return true if the device was successfully unsealed, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Unseal(BQ27441* bq);

/**
 * Perform a soft reset on the device
 * \param bq BQ27441 device
 * \return true if the device was successfully reset, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_SoftReset(BQ27441* bq);

/**
 * Enter a specific mode
 * \param bq BQ27441 device
 * \param mode Mode to enter (e.g., configure mode)
 * \return true if the mode was successfully entered, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_EnterMode(BQ27441* bq, BQ27441ModeType mode);

/**
 * Configure the device with specific parameters such as capacity, terminate voltage, and taper current
 * \param bq BQ27441 device
 * \param capacity Design capacity of the battery in mAh
 * \param terminateVoltage Terminate voltage in mV
 * \param taperCurrent Taper current in mA
 * \return true if the device was successfully configured, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_Configure(BQ27441* bq, uint16_t capacity, uint16_t terminateVoltage, uint16_t taperCurrent);

/**
 * Set GPOUT polarity
 * \param bq BQ27441 device
 * \param polarity GPOUT polarity to set (active low or active high)
 * \return true if the GPOUT polarity was successfully set, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_SetGPOUTPolarity(BQ27441* bq, BQ27441GPOUTPolarity polarity);

/**
 * Set GPOUT mode
 * \param bq BQ27441 device
 * \param mode GPOUT mode to set (e.g., state of charge interrupt or battery low interrupt)
 * \return true if the GPOUT mode was successfully set, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_SetGPOUTMode(BQ27441* bq, BQ27441GPOUTMode mode);

/**
 * Set state of charge low
 * \param bq BQ27441 device
 * \param setValue State of charge low threshold value to set (in percentage)
 * \param clearValue State of charge low threshold value to clear (in percentage)
 * \return true if the state of charge low threshold was successfully set, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_SetSOCLowThreshold(BQ27441* bq, uint8_t setValue, uint8_t clearValue);

/**
 * Set critical state of charge threshold
 * \param bq BQ27441 device
 * \param setValue Critical state of charge threshold value to set (in percentage)
 * \param clearValue Critical state of charge threshold value to clear (in percentage)
 * \return true if the critical state of charge threshold was successfully set, false otherwise
 * \note The return value is depended on the read/write interface implementation
 */
bool BQ27441_SetSOCCriticalThreshold(BQ27441* bq, uint8_t setValue, uint8_t clearValue);

#endif
