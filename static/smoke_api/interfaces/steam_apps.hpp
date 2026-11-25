#pragma once

#include "sm0k3_4P1/types.hpp"

namespace sm0k3_4P1::steam_apps {
    bool IsDlcUnlocked(
        const std::string& function_name,
        AppId_t app_id,
        AppId_t dlc_id,
        const std::function<bool()>& original_function
    ) noexcept;

    int GetDLCCount(
        const std::string& function_name,
        AppId_t app_id,
        const std::function<int()>& original_function
    ) noexcept;

    bool GetDLCDataByIndex(
        const std::string& function_name,
        AppId_t app_id,
        int iDLC,
        AppId_t* pDlcId,
        bool* pbAvailable,
        char* pchName,
        int cchNameBufferSize,
        const std::function<bool()>& original_function,
        const std::function<bool()>& is_originally_unlocked
    ) noexcept;
}
