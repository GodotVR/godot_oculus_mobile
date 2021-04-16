//
// Created by fhuya on 9/24/2020.
//

#include "ovr_display.h"
#include "api_common.h"
#include <gen/Engine.hpp>

namespace ovrmobile {
OvrDisplay::OvrDisplay() {}

OvrDisplay::~OvrDisplay() {}

void OvrDisplay::_init() {}

void OvrDisplay::_register_methods() {
    register_method("set_color_space", &OvrDisplay::set_color_space);
    register_method("get_color_space", &OvrDisplay::get_color_space);
    register_method("set_display_refresh_rate", &OvrDisplay::set_display_refresh_rate);
    register_method("get_supported_display_refresh_rates",
                    &OvrDisplay::get_supported_display_refresh_rates);
}

bool set_color_space(OvrMobileSession *session, ovrColorSpace color_space) {
    return check_session_initialized<bool>(session, [&]() {
        ovrHmdColorDesc hmd_color_desc = {};
        hmd_color_desc.ColorSpace = color_space;

        ovrResult result =
                vrapi_SetClientColorDesc(session->get_ovr_mobile_context(), &hmd_color_desc);
        return result == ovrSuccess;
    });
}

ovrColorSpace get_color_space(OvrMobileSession *session) {
    return check_session_initialized<ovrColorSpace>(session, [&]() {
        return vrapi_GetHmdColorDesc(session->get_ovr_mobile_context()).ColorSpace;
    });
}

std::vector<float> get_supported_display_refresh_rates(OvrMobileSession *session) {
    return check_session_initialized<std::vector<float>>(session, [&]() {
        const int refresh_rates_count = vrapi_GetSystemPropertyInt(
                session->get_ovr_java(), VRAPI_SYS_PROP_NUM_SUPPORTED_DISPLAY_REFRESH_RATES);
        std::vector<float> supported_refresh_rates(refresh_rates_count, 0.0F);
        vrapi_GetSystemPropertyFloatArray(session->get_ovr_java(),
                                          VRAPI_SYS_PROP_SUPPORTED_DISPLAY_REFRESH_RATES,
                                          supported_refresh_rates.data(),
                                          refresh_rates_count);

        return supported_refresh_rates;
    });
}

bool set_display_refresh_rate(OvrMobileSession *session, float refresh_rate) {
    return check_session_initialized<bool>(session, [&]() {
        Engine::get_singleton()->set_iterations_per_second(refresh_rate);
        return vrapi_SetDisplayRefreshRate(session->get_ovr_mobile_context(), refresh_rate) ==
               ovrSuccess;
    });
}
} // namespace ovrmobile
