#include "memory.hpp"

#include <stb/stb.hh>

#define LOG_RESULT(src) LOG("memory::%s found at -> %p\n", #src, src)

void memory::Initialize() {
    CModule client(CLIENT_DLL, true);
    CModule schemasystem(SCHEMASYSTEM_DLL, true);
    CModule sdl2(SDL2_DLL, true);

    fnGetBaseEntity = client.FindPattern(GET_BASE_ENTITY)
                          .ToAbsolute(3, 0)
                          .GetAs<decltype(fnGetBaseEntity)>();
    LOG_RESULT(fnGetBaseEntity);
    fnGetBaseEntityFromHandle =
        client.FindPattern(GET_BASE_ENTITY_FROM_HANDLE)
            .ToAbsolute(1, 0)
            .GetAs<decltype(fnGetBaseEntityFromHandle)>();
    LOG_RESULT(fnGetBaseEntityFromHandle);
    fnGetHighestEntityIndex = client.FindPattern(GET_HIGHEST_ENTITY_INDEX)
                                  .ToAbsolute(3, 0)
                                  .GetAs<decltype(fnGetHighestEntityIndex)>();
    LOG_RESULT(fnGetHighestEntityIndex);
    schema_detailed_class_layout =
        schemasystem.FindPattern(PRINT_SCHEMA_DETAILED_CLASS_LAYOUT)
            .GetAs<decltype(schema_detailed_class_layout)>();
    LOG_RESULT(schema_detailed_class_layout);
    fnScreenTransform = client.FindPattern(SCREEN_TRANSFORM)
                            .ToAbsolute(1, 0)
                            .GetAs<decltype(fnScreenTransform)>();
    LOG_RESULT(fnScreenTransform);
    fnMouseInputEnabled =
        client.FindPattern(MOUSE_INPUT_ENABLED).GetAs<void*>();
    LOG_RESULT(fnMouseInputEnabled);

    // SDL Functions:
    fnSDL_SetRelativeMouseMode =
        sdl2.GetProcAddress<decltype(fnSDL_SetRelativeMouseMode)>(
            "SDL_SetRelativeMouseMode");
    LOG_RESULT(fnSDL_SetRelativeMouseMode);
    fnSDL_SetWindowGrab =
        sdl2.GetProcAddress<decltype(fnSDL_SetWindowGrab)>("SDL_SetWindowGrab");
    LOG_RESULT(fnSDL_SetWindowGrab);
    fnSDL_WarpMouseInWindow =
        sdl2.GetProcAddress<decltype(fnSDL_WarpMouseInWindow)>(
            "SDL_WarpMouseInWindow");
    LOG_RESULT(fnSDL_WarpMouseInWindow);
}

void memory::Shutdown() {}
