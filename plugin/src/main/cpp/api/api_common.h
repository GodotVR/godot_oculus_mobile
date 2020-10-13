/**
 * Created by Fredia Huya-Kouadio.
 */

#ifndef API_COMMON_H
#define API_COMMON_H

namespace ovrmobile {

// Checks that the ovr mobile session is valid and initialized prior to running the requested logic.
template <typename T, typename TrueFunc>
inline T check_session_initialized(OvrMobileSession *session, TrueFunc true_branch) {
    if (session && session->is_initialized()) {
        return true_branch();
    } else {
        return T{};
    }
}

// Checks that the ovr mobile session is valid and initialized prior to running the requested logic.
template <typename T, typename TrueFunc, typename FalseFunc>
inline T
check_session_initialized(OvrMobileSession *session, TrueFunc true_branch, FalseFunc false_branch) {
    if (session && session->is_initialized()) {
        return true_branch();
    } else {
        return false_branch();
    }
}

// Checks that the ovr mobile session is valid and NOT initialized prior to running the requested
// logic.
template <typename T, typename TrueFunc>
inline T check_session_not_initialized(OvrMobileSession *session, TrueFunc true_branch) {
    if (session && !session->is_initialized()) {
        return true_branch();
    } else {
        return T{};
    }
}

// Checks that the ovr mobile session is valid and NOT initialized prior to running the requested
// logic.
template <typename T, typename TrueFunc, typename FalseFunc>
inline T check_session_not_initialized(OvrMobileSession *session,
                                       TrueFunc true_branch,
                                       FalseFunc false_branch) {
    if (session && !session->is_initialized()) {
        return true_branch();
    } else {
        return false_branch();
    }
}

} // namespace ovrmobile

#endif // API_COMMON_H
