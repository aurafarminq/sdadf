#pragma once

#include "types.hpp"

namespace sm0k3_4P1::cache {
    std::vector<DLC> get_dlcs(AppId_t app_id) noexcept;

    bool save_dlcs(AppId_t app_id, const std::vector<DLC>& dlcs) noexcept;
}
