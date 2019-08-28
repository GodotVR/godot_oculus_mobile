////////////////////////////////////////////////////////////////
// Common helpers for the config classes implemented in this folder
// to expose part of Oculus VrAPI.h via GDScript classes

#ifndef OVRMOBILE_CONFIG_COMMON_H
#define OVRMOBILE_CONFIG_COMMON_H

#include "../ovr_mobile_session.h"
#include "../common.h"

typedef struct ovr_config_data_struct {
	ovrmobile::OvrMobileSession *ovr_mobile_session;
} ovr_config_data_struct;

void *init_ovr_config_data_struct();

void reset_ovr_config_data_struct(ovr_config_data_struct *ovr_config_data);

#endif