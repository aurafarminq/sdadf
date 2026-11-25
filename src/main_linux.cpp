#include <dlfcn.h>

#include "koalabox/util.hpp"

#include "sm0k3_4P1/sm0k3_4P1.hpp"

extern "C" void __attribute__((constructor)) init() {
    // On linux we don't automatically get current module handle,
    // hence we find it manually
    Dl_info info;
    if(dladdr(reinterpret_cast<void*>(&init), &info) && info.dli_fname) {
        void* handle = dlopen(info.dli_fname, RTLD_NOW | RTLD_NOLOAD);
        sm0k3_4P1::init(handle);
    } else {
        koalabox::util::panic("Initialization error: failed to get own module handle.");
    }
}

extern "C" void __attribute__((destructor)) fini() {
    sm0k3_4P1::shutdown();
}
