#pragma once

#include "sm0k3_4P1/types.hpp"

namespace sm0k3_4P1::steam_user {
    EUserHasLicenseForAppResult UserHasLicenseForApp(
        const std::string& function_name,
        AppId_t appId,
        AppId_t dlcId,
        const std::function<EUserHasLicenseForAppResult()>& original_function
    ) noexcept;
}
