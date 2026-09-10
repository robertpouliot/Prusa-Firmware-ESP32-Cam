/**
   @file variable.h

   @brief Library with global variables

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug
*/

#pragma once

#include <Arduino.h>
#include "mcu_cfg.h"

struct WebBasicAuth_struct {
  bool EnableAuth;                        ///< user definition for enable/disable basic auth
  String UserName;                        ///< login name for basic auth
  String Password;                        ///< password for basic auth
};

/* The scalar flags are volatile: written by one task and polled by another, and without
   it the compiler may cache them in a register. Aligned bool/int accesses are single
   instructions on Xtensa, so stale reads were the risk, not tearing.
   The String members are NOT covered -- a String is a pointer plus length and can still
   race -- but they are only touched during an OTA update. */
struct FirmwareUpdate_struct {
  String UpdatingStatus;                  ///< Updateing status
  volatile bool Processing;               ///< status abour processing firmware update
  volatile uint8_t PercentProcess;        ///< processed firmware update
  volatile int TransferedBytes;           ///< transfered bytes

  volatile int FirmwareSize;              ///< uploaded firmware size

  volatile bool StartOtaUpdate;           ///< Start OTA update process
  volatile bool CheckNewVersionAfterBoot; ///< Check new version OTA update after MCU boot
  volatile bool RequestNewVersionCheck;   ///< web UI asked for a re-check; serviced by System_Main, never inline in the handler
  String NewVersionFw;                    ///< New FW version
  String CheckNewVersionFwStatus;         ///< connection status from checking new OTA update version
  String OtaUpdateFwUrl;                  ///< URL for OTA update
  volatile bool OtaUpdateFwAvailable;     ///< flag for available new FW version
};

struct McuTemperature_struct {
  float TemperatureCelsius;               ///< MCU temperature
};

extern struct WebBasicAuth_struct WebBasicAuth;      ///< structure with configuration for basic auth
extern struct FirmwareUpdate_struct FirmwareUpdate;  ///< firmware update status and process
extern struct McuTemperature_struct McuTemperature;  ///< MCU temperature

extern TaskHandle_t Task_CapturePhotoAndSend;        ///< task handle for capture photo and send
extern TaskHandle_t Task_WiFiManagement;             ///< task handle for wifi management
extern TaskHandle_t Task_SystemMain;                 ///< task handle for system main
extern TaskHandle_t Task_SdCardCheck;                ///< task handle for sd card check  
extern TaskHandle_t Task_SerialCfg;                  ///< task handle for serial configuration
extern TaskHandle_t Task_SystemTelemetry;            ///< task handle for system telemetry
extern TaskHandle_t Task_SysLed;                     ///< task handle for system led
extern TaskHandle_t Task_WiFiWatchdog;               ///< task handle for wifi watchdog
//extern TaskHandle_t Task_SdCardFileRemove;           ///< task handle for remove file from sd card  

extern uint8_t StartRemoveSdCard;
extern uint32_t SdCardRemoveTime;

/* EOF */