#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#define COMMAND_CONTROL              0x00
#define COMMAND_TEMPERATURE_BATTERY  0x02
#define COMMAND_VOLTAGE              0x04
#define COMMAND_FLAGS                0x06
#define COMMAND_CAPACITY_REMAIN      0x08
#define COMMAND_CURRENT_AVG          0x10
#define COMMAND_CURRENT_STANDBY      0x12
#define COMMAND_CURRENT_MAX          0x14
#define COMMAND_CAPACITY_FULL        0x0A
#define COMMAND_CAPACITY_REMAIN_COMP 0x0C
#define COMMAND_CAPACITY_FULL_COMP   0x0E
#define COMMAND_POWER_AVG            0x18
#define COMMAND_SOC                  0x1C
#define COMMAND_TEMPERATURE_INTERNAL 0x1E
#define COMMAND_SOH                  0x20

#define SUB_STATUS         0x0000
#define SUB_SEAL           0x0020
#define SUB_SET_CFGUPDATE  0x0013
#define SUB_SOFT_RESET     0x0042
#define SUB_EXIT_CFGUPDATE 0x0043
#define SUB_UNSEAL         0x8000

#define EXTENDED_CAPACITY_DESIGNED 0x3C

#endif
