/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WIFI_H_
#define WIFI_H_

// HACK: NAN is a macro defined in math.h, which can be included in various
// headers. This wifi HAL uses an enum called NAN, which does not compile when
// the macro is defined. Undefine NAN to work around it.
#undef NAN
#include <android/hardware/wifi/1.6/IWifi.h>

#include <android-base/macros.h>
#include <utils/Looper.h>
#include <functional>

#include "hidl_callback_util.h"
#include "wifi_chip.h"
#include "wifi_feature_flags.h"
#include "wifi_legacy_hal.h"
#include "wifi_legacy_hal_factory.h"
#include "wifi_mode_controller.h"

namespace android {
namespace hardware {
namespace wifi {
namespace V1_6 {
namespace implementation {

/**
 * Root HIDL interface object used to control the Wifi HAL.
 */
class Wifi : public V1_6::IWifi {
  public:
    Wifi(const std::shared_ptr<wifi_system::InterfaceTool> iface_tool,
         const std::shared_ptr<legacy_hal::WifiLegacyHalFactory> legacy_hal_factory,
         const std::shared_ptr<mode_controller::WifiModeController> mode_controller,
         const std::shared_ptr<feature_flags::WifiFeatureFlags> feature_flags);

    bool isValid();

    // HIDL methods exposed.
    Return<void> registerEventCallback(const sp<V1_0::IWifiEventCallback>& event_callback,
                                       registerEventCallback_cb hidl_status_cb) override;
    Return<void> registerEventCallback_1_5(const sp<V1_5::IWifiEventCallback>& event_callback,
                                           registerEventCallback_1_5_cb hidl_status_cb) override;
    Return<bool> isStarted() override;
    Return<void> start(start_cb hidl_status_cb) override;
    Return<void> stop(stop_cb hidl_status_cb) override;
    Return<void> getChipIds(getChipIds_cb hidl_status_cb) override;
    Return<void> getChip(ChipId chip_id, getChip_cb hidl_status_cb) override;
    Return<void> debug(const hidl_handle& handle, const hidl_vec<hidl_string>& options) override;

  private:
    enum class RunState { STOPPED, STARTED, STOPPING };

    // Corresponding worker functions for the HIDL methods.
    WifiStatus registerEventCallbackInternal(
            const sp<V1_0::IWifiEventCallback>& event_callback __unused);
    WifiStatus registerEventCallbackInternal_1_5(
            const sp<V1_5::IWifiEventCallback>& event_callback);
    WifiStatus startInternal();
    WifiStatus stopInternal(std::unique_lock<std::recursive_mutex>* lock);
    std::pair<WifiStatus, std::vector<ChipId>> getChipIdsInternal();
    std::pair<WifiStatus, sp<V1_4::IWifiChip>> getChipInternal(ChipId chip_id);

    WifiStatus initializeModeControllerAndLegacyHal();
    WifiStatus stopLegacyHalAndDeinitializeModeController(
            std::unique_lock<std::recursive_mutex>* lock);
    ChipId getChipIdFromWifiChip(sp<WifiChip>& chip);

    // Instance is created in this root level |IWifi| HIDL interface object
    // and shared with all the child HIDL interface objects.
    std::shared_ptr<wifi_system::InterfaceTool> iface_tool_;
    std::shared_ptr<legacy_hal::WifiLegacyHalFactory> legacy_hal_factory_;
    std::shared_ptr<mode_controller::WifiModeController> mode_controller_;
    std::vector<std::shared_ptr<legacy_hal::WifiLegacyHal>> legacy_hals_;
    std::shared_ptr<feature_flags::WifiFeatureFlags> feature_flags_;
    RunState run_state_;
    std::vector<sp<WifiChip>> chips_;
    hidl_callback_util::HidlCallbackHandler<V1_5::IWifiEventCallback> event_cb_handler_;

    DISALLOW_COPY_AND_ASSIGN(Wifi);
};

}  // namespace implementation
}  // namespace V1_6
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // WIFI_H_
