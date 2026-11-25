#include <mutex>

#include <koalabox/hook.hpp>
#include <koalabox/logger.hpp>

#include "sm0k3_4P1/steamclient/steamclient.hpp"
#include "sm0k3_4P1/sm0k3_4P1.hpp"
#include "sm0k3_4P1/types.hpp"

#include "steam_api/steam_client.hpp"

/**
 * sm0k34P1 implementation
 */
C_DECL(void*) CreateInterface(const char* interface_version, create_interface_result* out_result) {
    // Mutex here helps us detect unintended recursion early on by throwing an exception.
    static std::mutex section;
    const std::lock_guard lock(section);

    static std::once_flag once_flag;
    std::call_once(once_flag, sm0k3_4P1::post_init);

    return steam_client::GetGenericInterface(
        __func__,
        interface_version,
        [&] {
            static const auto CreateInterface$ = KB_HOOK_GET_HOOKED_FN(CreateInterface);
            return CreateInterface$(interface_version, out_result);
        }
    );
}
