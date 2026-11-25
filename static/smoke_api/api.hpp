#pragma once

#include "sm0k3_4P1/types.hpp"

namespace sm0k3_4P1::api {
    std::optional<std::vector<DLC>> fetch_dlcs_from_github(AppId_t app_id);

    std::optional<std::vector<DLC>> fetch_dlcs_from_steam(AppId_t app_id);
}
