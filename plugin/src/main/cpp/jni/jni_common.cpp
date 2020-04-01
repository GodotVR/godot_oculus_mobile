#include "ovr_mobile_session.h"
#include "jni_common.h"

ovrmobile::OvrMobileSession* get_session() {
    return ovrmobile::OvrMobileSession::get_singleton_instance();
}