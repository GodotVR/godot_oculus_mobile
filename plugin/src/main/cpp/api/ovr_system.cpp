/**
 * Created by Fredia Huya-Kouadio.
 */

#include "ovr_system.h"
#include "api_common.h"

namespace ovrmobile {
OvrSystem::OvrSystem() = default;

OvrSystem::~OvrSystem() = default;

void OvrSystem::_init() {}

void OvrSystem::_register_methods() {
    register_method("get_device_type", &OvrSystem::get_device_type);
    register_method("get_driver_version", &OvrSystem::get_driver_version);
    register_method("is_oculus_quest_1_device", &OvrSystem::is_oculus_quest_1_device);
    register_method("is_oculus_quest_2_device", &OvrSystem::is_oculus_quest_2_device);
}

ovrDeviceType get_device_type(OvrMobileSession *session) {
    return check_session_initialized<ovrDeviceType>(
            session,
            [&]() {
                auto device_type = static_cast<ovrDeviceType>(vrapi_GetSystemPropertyInt(
                        session->get_ovr_java(), VRAPI_SYS_PROP_DEVICE_TYPE));
                return device_type;
            },
            []() { return VRAPI_DEVICE_TYPE_UNKNOWN; });
}

bool is_oculus_quest_1_device(OvrMobileSession *session) {
    ovrDeviceType device_type = get_device_type(session);
    return device_type >= VRAPI_DEVICE_TYPE_OCULUSQUEST_START &&
           device_type <= VRAPI_DEVICE_TYPE_OCULUSQUEST_END;
}

bool is_oculus_quest_2_device(OvrMobileSession *session) {
    ovrDeviceType device_type = get_device_type(session);
    return device_type >= VRAPI_DEVICE_TYPE_OCULUSQUEST2_START &&
           device_type <= VRAPI_DEVICE_TYPE_OCULUSQUEST2_END;
}

String get_driver_version() {
    return vrapi_GetVersionString();
}

} // namespace ovrmobile
