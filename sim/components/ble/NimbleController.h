#pragma once

#include <cstdint>

//#define min // workaround: nimble's min/max macros conflict with libstdc++
//#define max
//#include <host/ble_gap.h>
//#undef max
//#undef min
//#include "components/ble/AlertNotificationClient.h"
#include "components/ble/AlertNotificationService.h"
//#include "components/ble/BatteryInformationService.h"
//#include "components/ble/CurrentTimeClient.h"
//#include "components/ble/CurrentTimeService.h"
//#include "components/ble/DeviceInformationService.h"
//#include "components/ble/DfuService.h"
//#include "components/ble/HeartRateService.h"
//#include "components/ble/ImmediateAlertService.h"
#include "components/ble/MusicService.h"
#include "components/ble/NavigationService.h"
//#include "components/ble/ServiceDiscovery.h"
//#include "components/ble/MotionService.h"
#include "components/ble/weather/WeatherService.h"
#include "components/fs/FS.h"
//#include "components/ble/FSService.h"

namespace Pinetime {
  namespace Drivers {
    class SpiNorFlash;
  }

  namespace System {
    class SystemTask;
  }

  namespace Controllers {
    class Battery;
    class Ble;
    class DateTime;
    class FS;
    class HeartRateController;
    class MotionController;
    class NotificationManager;

    class NimbleController {

    public:
      NimbleController(Pinetime::System::SystemTask& systemTask,
                       Pinetime::Controllers::Ble& bleController,
                       DateTime& dateTimeController,
                       Pinetime::Controllers::NotificationManager& notificationManager,
                       Controllers::Battery& batteryController,
                       Pinetime::Drivers::SpiNorFlash& spiNorFlash,
                       Controllers::HeartRateController& heartRateController,
                       Controllers::MotionController& motionController,
                       Pinetime::Controllers::FS& fs);
      void Init();
      void StartAdvertising();
//      int OnGAPEvent(ble_gap_event* event);

//      int OnDiscoveryEvent(uint16_t i, const ble_gatt_error* pError, const ble_gatt_svc* pSvc);
//      int OnCTSCharacteristicDiscoveryEvent(uint16_t connectionHandle, const ble_gatt_error* error, const ble_gatt_chr* characteristic);
//      int OnANSCharacteristicDiscoveryEvent(uint16_t connectionHandle, const ble_gatt_error* error, const ble_gatt_chr* characteristic);
//      int OnCurrentTimeReadResult(uint16_t connectionHandle, const ble_gatt_error* error, ble_gatt_attr* attribute);
//      int OnANSDescriptorDiscoveryEventCallback(uint16_t connectionHandle,
//                                                const ble_gatt_error* error,
//                                                uint16_t characteristicValueHandle,
//                                                const ble_gatt_dsc* descriptor);

      void StartDiscovery();

      Pinetime::Controllers::MusicService& music() {
        return musicService;
      };
      Pinetime::Controllers::NavigationService& navigation() {
        return navService;
      };
      Pinetime::Controllers::AlertNotificationService& alertService() {
        return anService;
      };
      Pinetime::Controllers::WeatherService& weather() {
        return weatherService;
      };

      uint16_t connHandle();
      void NotifyBatteryLevel(uint8_t level);

      void RestartFastAdv() {
        fastAdvCount = 0;
      }

    private:
//      void PersistBond(struct ble_gap_conn_desc& desc);
//      void RestoreBond();

      static constexpr const char* deviceName = "InfiniTime";
      Pinetime::System::SystemTask& systemTask;
      Pinetime::Controllers::Ble& bleController;
      DateTime& dateTimeController;
      Pinetime::Controllers::NotificationManager& notificationManager;
      Pinetime::Drivers::SpiNorFlash& spiNorFlash;
      Pinetime::Controllers::FS& fs;
//      Pinetime::Controllers::DfuService dfuService;

//      DeviceInformationService deviceInformationService;
//      CurrentTimeClient currentTimeClient;
      AlertNotificationService anService;
//      AlertNotificationClient alertNotificationClient;
//      CurrentTimeService currentTimeService;
      MusicService musicService;
      WeatherService weatherService;
      NavigationService navService;
//      BatteryInformationService batteryInformationService;
//      ImmediateAlertService immediateAlertService;
//      HeartRateService heartRateService;
//      MotionService motionService;
//      FSService fsService;
//      ServiceDiscovery serviceDiscovery;

      uint8_t addrType;
//      uint16_t connectionHandle = BLE_HS_CONN_HANDLE_NONE;
      uint8_t fastAdvCount = 0;
      uint8_t bondId[16] = {0};

//      ble_uuid128_t dfuServiceUuid {
//        .u {.type = BLE_UUID_TYPE_128},
//        .value = {0x23, 0xD1, 0xBC, 0xEA, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x30, 0x15, 0x00, 0x00}};
    };

//    static NimbleController* nptr;
  }
}
