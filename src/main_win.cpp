// ReSharper disable CppUnusedIncludeDirective
#include <koalabox/win.hpp>

#include "sm0k3_4P1/sm0k3_4P1.hpp"

// These headers will be populated at build time
#include "linker_exports_for_steam_api.h"
#include "linker_exports_for_windows_dlls.h"

DLL_MAIN(void* handle, const uint32_t reason, void*) {
    if(reason == DLL_PROCESS_ATTACH) {
        sm0k3_4P1::init(handle);
    } else if(reason == DLL_PROCESS_DETACH) {
        sm0k3_4P1::shutdown();
    }

    return TRUE;
}
