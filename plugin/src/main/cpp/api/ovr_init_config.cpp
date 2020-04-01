#include "ovr_init_config.h"
#include "api_common.h"

namespace ovrmobile {

    bool set_render_target_size_multiplier(OvrMobileSession *session, double multiplier) {
        return check_session_not_initialized<bool>(session, [&](){
            // Update the render target size.
            session->set_render_target_size_multiplier(multiplier);
            return true;
        }, []() { return false; });
    }

} // namespace ovrmobile