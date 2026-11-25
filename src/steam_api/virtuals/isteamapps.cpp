#include <koalabox/logger.hpp>

#include "sm0k3_4P1/sm0k3_4P1.hpp"
#include "sm0k3_4P1/interfaces/steam_apps.hpp"
#include "steam_api/virtuals/steam_api_virtuals.hpp"

VIRTUAL(bool) ISteamApps_BIsSubscribedApp(PARAMS(const AppId_t dlc_id)) noexcept {
    return sm0k3_4P1::steam_apps::IsDlcUnlocked(
        __func__,
        sm0k3_4P1::get_app_id(),
        dlc_id,
        SWAPPED_CALL_CLOSURE(ISteamApps_BIsSubscribedApp, ARGS(dlc_id))
    );
}

VIRTUAL(bool) ISteamApps_BIsDlcInstalled(PARAMS(const AppId_t dlc_id)) noexcept {
    return sm0k3_4P1::steam_apps::IsDlcUnlocked(
        __func__,
        sm0k3_4P1::get_app_id(),
        dlc_id,
        SWAPPED_CALL_CLOSURE(ISteamApps_BIsDlcInstalled, ARGS(dlc_id))
    );
}

VIRTUAL(int) ISteamApps_GetDLCCount(PARAMS()) noexcept {
    return sm0k3_4P1::steam_apps::GetDLCCount(
        __func__,
        sm0k3_4P1::get_app_id(),
        SWAPPED_CALL_CLOSURE(ISteamApps_GetDLCCount, ARGS())
    );
}

VIRTUAL(bool) ISteamApps_BGetDLCDataByIndex(
    PARAMS(
        const int iDLC,
        AppId_t* p_dlc_id,
        bool* pbAvailable,
        char* pchName,
        const int cchNameBufferSize
    )
) noexcept {
    return sm0k3_4P1::steam_apps::GetDLCDataByIndex(
        __func__,
        sm0k3_4P1::get_app_id(),
        iDLC,
        p_dlc_id,
        pbAvailable,
        pchName,
        cchNameBufferSize,
        SWAPPED_CALL_CLOSURE(
            ISteamApps_BGetDLCDataByIndex,
            ARGS(iDLC, p_dlc_id, pbAvailable, pchName, cchNameBufferSize)
        ),
        SWAPPED_CALL_CLOSURE(
            ISteamApps_BIsSubscribedApp,
            ARGS(*p_dlc_id)
        )
    );
}
