#ifndef ANDROID_HARDWARE_GNSS_V1_1_GNSS_H
#define ANDROID_HARDWARE_GNSS_V1_1_GNSS_H

#include <android/hardware/gnss/1.1/IGnss.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace gnss {
namespace V1_1 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Gnss : public IGnss {
    // Methods from ::android::hardware::gnss::V1_0::IGnss follow.
    Return<bool> setCallback(
        const sp<::android::hardware::gnss::V1_0::IGnssCallback>& callback) override;
    Return<bool> start() override;
    Return<bool> stop() override;
    Return<void> cleanup() override;
    Return<bool> injectTime(int64_t timeMs, int64_t timeReferenceMs,
                            int32_t uncertaintyMs) override;
    Return<bool> injectLocation(double latitudeDegrees, double longitudeDegrees,
                                float accuracyMeters) override;
    Return<void> deleteAidingData(
        ::android::hardware::gnss::V1_0::IGnss::GnssAidingData aidingDataFlags) override;
    Return<bool> setPositionMode(
        ::android::hardware::gnss::V1_0::IGnss::GnssPositionMode mode,
        ::android::hardware::gnss::V1_0::IGnss::GnssPositionRecurrence recurrence,
        uint32_t minIntervalMs, uint32_t preferredAccuracyMeters,
        uint32_t preferredTimeMs) override;
    Return<sp<::android::hardware::gnss::V1_0::IAGnssRil>> getExtensionAGnssRil() override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssGeofencing>> getExtensionGnssGeofencing()
        override;
    Return<sp<::android::hardware::gnss::V1_0::IAGnss>> getExtensionAGnss() override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssNi>> getExtensionGnssNi() override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssMeasurement>> getExtensionGnssMeasurement()
        override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssNavigationMessage>>
    getExtensionGnssNavigationMessage() override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssXtra>> getExtensionXtra() override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssConfiguration>> getExtensionGnssConfiguration()
        override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssDebug>> getExtensionGnssDebug() override;
    Return<sp<::android::hardware::gnss::V1_0::IGnssBatching>> getExtensionGnssBatching() override;

    // Methods from ::android::hardware::gnss::V1_1::IGnss follow.
    Return<bool> setCallback_1_1(
        const sp<::android::hardware::gnss::V1_1::IGnssCallback>& callback) override;
    Return<bool> setPositionMode_1_1(
        ::android::hardware::gnss::V1_0::IGnss::GnssPositionMode mode,
        ::android::hardware::gnss::V1_0::IGnss::GnssPositionRecurrence recurrence,
        uint32_t minIntervalMs, uint32_t preferredAccuracyMeters, uint32_t preferredTimeMs,
        bool lowPowerMode) override;
    Return<sp<::android::hardware::gnss::V1_1::IGnssConfiguration>>
    getExtensionGnssConfiguration_1_1() override;
    Return<sp<::android::hardware::gnss::V1_1::IGnssMeasurement>> getExtensionGnssMeasurement_1_1()
        override;
    Return<bool> injectBestLocation(
        const ::android::hardware::gnss::V1_0::GnssLocation& location) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
};

}  // namespace implementation
}  // namespace V1_1
}  // namespace gnss
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_GNSS_V1_1_GNSS_H
