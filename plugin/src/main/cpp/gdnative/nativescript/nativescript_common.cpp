#include "nativescript_common.h"

void *init_ovr_config_data_struct() {
    ovr_config_data_struct *ovr_config_data;

    ovr_config_data = (ovr_config_data_struct *)godot::api->godot_alloc(sizeof(ovr_config_data_struct));
    if (ovr_config_data != nullptr) {
        ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
    }

    return ovr_config_data;
}

void reset_ovr_config_data_struct(ovr_config_data_struct *ovr_config_data) {
    if (ovr_config_data && ovr_config_data->ovr_mobile_session) {
        ovr_config_data->ovr_mobile_session = nullptr;
    }
}