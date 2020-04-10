#include "ovr_mobile_session.h"
#include "jni_common.h"

ovrmobile::OvrMobileSession* get_session() {
    return ovrmobile::OvrMobileSession::get_singleton_instance();
}

jfloatArray from_ovrVector2f(JNIEnv *env, ovrVector2f vector) {
    jfloatArray result = env->NewFloatArray(2);
    if (result) {
        float vector_data[2];
        vector_data[0] = vector.x;
        vector_data[1] = vector.y;

        env->SetFloatArrayRegion(result, 0, 2, vector_data);
    }

    return result;
}

jfloatArray from_ovrVector3f(JNIEnv *env, ovrVector3f vector) {
    jfloatArray result = env->NewFloatArray(3);
    if (result) {
        float vector_data[3];
        vector_data[0] = vector.x;
        vector_data[1] = vector.y;
        vector_data[2] = vector.z;

        env->SetFloatArrayRegion(result, 0, 3, vector_data);
    }

    return result;
}

jfloatArray from_ovrVector4f(JNIEnv *env, ovrVector4f vector) {
    jfloatArray result = env->NewFloatArray(4);
    if (result) {
        float vector_data[4];
        vector_data[0] = vector.x;
        vector_data[1] = vector.y;
        vector_data[2] = vector.z;
        vector_data[3] = vector.w;

        env->SetFloatArrayRegion(result, 0, 4, vector_data);
    }
    return result;
}
