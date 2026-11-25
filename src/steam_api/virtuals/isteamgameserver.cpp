#include <koalabox/logger.hpp>

#include "sm0k3_4P1/sm0k3_4P1.hpp"
#include "sm0k3_4P1/interfaces/steam_user.hpp"
#include "steam_api/virtuals/steam_api_virtuals.hpp"

VIRTUAL(EUserHasLicenseForAppResult) ISteamGameServer_UserHasLicenseForApp(
    PARAMS(const CSteamID steamID, const AppId_t dlc_id)
) noexcept {
    return sm0k3_4P1::steam_user::UserHasLicenseForApp(
        __func__,
        sm0k3_4P1::get_app_id(),
        dlc_id,
        SWAPPED_CALL_CLOSURE(ISteamGameServer_UserHasLicenseForApp, ARGS(steamID, dlc_id))
    );
}
