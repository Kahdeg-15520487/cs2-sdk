#pragma once

#include "../../api/module/module.hpp"

class Vector;

namespace memory {
    void Initialize();
    void Shutdown();

    inline void*(__thiscall* fnGetBaseEntity)(void*, CEntityIndex);
    inline void*(__thiscall* fnGetBaseEntityFromHandle)(void*, CEntityHandle);
    inline int(__thiscall* fnGetHighestEntityIndex)(void*, int*);
    inline void*(__thiscall* schema_detailed_class_layout)(void*, const char*);
    inline bool(__thiscall* fnScreenTransform)(const Vector&, Vector&);
    inline void* fnMouseInputEnabled;

    // SDL2 Functions
    inline int(__stdcall* fnSDL_SetRelativeMouseMode)(int);
    inline int(__stdcall* fnSDL_SetWindowGrab)(void*, int);
    inline int(__stdcall* fnSDL_WarpMouseInWindow)(void*, int, int);
}  // namespace memory
