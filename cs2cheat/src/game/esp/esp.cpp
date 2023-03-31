#include "esp.hpp"

#include "../../sdk/interfaces/interfaces.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "../../sdk/source-sdk/classes/entity/c_baseplayerweapon.hpp"

void esp::skin() {
    LOG("skin\r\n");
    for (int i = 1; i <= MAX_PLAYERS; ++i) {
        CCSPlayerController* pPlayer =
            interfaces::pEntitySystem->GetBaseEntity<CCSPlayerController>(i);
        if (!pPlayer || !pPlayer->IsPlayerController() ||
            !pPlayer->m_bPawnIsAlive())
            continue;

        C_CSPlayerPawn* pPawn = pPlayer->m_hPawn().GetAs<C_CSPlayerPawn>();
        if (!pPawn) continue;

        if (pPlayer->m_bIsLocalPlayerController()) {
            auto weapon_services = pPawn->m_pWeaponServices();
            LOG("weapons count: %i\r\n", weapon_services->m_hMyWeapons());
            LOG("weapon <1>: %i\r\n",
                weapon_services->m_hMyWeapons1().GetEntryIndex());
            LOG("weapon <2>: %i\r\n",
                weapon_services->m_hMyWeapons2().GetEntryIndex());
            LOG("weapon <3>: %i\r\n",
                weapon_services->m_hMyWeapons3().GetEntryIndex());
            LOG("holding weapon: %i\r\n",
                weapon_services->m_hActiveWeapon().GetEntryIndex());
            auto weapon =
                weapon_services->m_hActiveWeapon().GetAs<C_BasePlayerWeapon>();
            weapon->m_AttributeManager().m_Item().m_iItemIDHigh() = -1;
            LOG("holding weapon id: %I64u\r\n",
                weapon->m_AttributeManager().m_Item().m_iItemID());
            LOG("weapon name: %s\r\n", weapon->m_pEntity()->m_designerName());
            LOG("account id: %i\r\n",
                weapon->m_AttributeManager().m_Item().m_iAccountID());
            LOG("holding weapon pos: %i\r\n",
                weapon->m_AttributeManager().m_Item().m_iInventoryPosition());
            weapon->m_flFallbackWear() = 0.00001f;
            weapon->m_nFallbackSeed() = 0;
            weapon->m_nFallbackPaintKit() = 38;
        }
    }
}

void esp::Render() {
    if (!interfaces::pEngine->IsInGame()) return;

    CCSPlayerController* pLocalPlayerController =
        interfaces::pEntitySystem->GetLocalPlayerController();
    if (!pLocalPlayerController) return;

    ImDrawList* pBackgroundDrawList = ImGui::GetBackgroundDrawList();
    for (int i = 1; i <= MAX_PLAYERS; ++i) {
        CCSPlayerController* pPlayerController =
            interfaces::pEntitySystem->GetBaseEntity<CCSPlayerController>(i);
        if (!pPlayerController || !pPlayerController->IsPlayerController() ||
            !pPlayerController->m_bPawnIsAlive())
            continue;

        C_CSPlayerPawn* pPawn =
            pPlayerController->m_hPawn().GetAs<C_CSPlayerPawn>();
        if (!pPawn) continue;

        if (bIgnoreTeammates &&
            !pPawn->IsEnemyToLocalPlayer(pLocalPlayerController->m_iTeamNum()))
            continue;

        BBox_t bBox;
        if (!pPawn->GetBoundingBox(bBox)) continue;

        const bool isLocalPlayer =
            pPlayerController->m_bIsLocalPlayerController();
        const ImVec2 min = {bBox.x, bBox.y};
        const ImVec2 max = {bBox.w, bBox.h};

        if (bBoxEsp) {
            pBackgroundDrawList->AddRect(
                min, max,
                pPawn->IsEnemyToLocalPlayer(
                    pLocalPlayerController->m_iTeamNum())
                    ? IM_COL32(255, 0, 0, 255)
                    : IM_COL32(0, 255, 0, 255));
            pBackgroundDrawList->AddRect(min - ImVec2{1.f, 1.f},
                                         max + ImVec2{1.f, 1.f},
                                         IM_COL32(0, 0, 0, 255));
            pBackgroundDrawList->AddRect(min + ImVec2{1.f, 1.f},
                                         max - ImVec2{1.f, 1.f},
                                         IM_COL32(0, 0, 0, 255));
        }
        if (bNameEsp) {
            const char* szName = pPlayerController->m_sSanitizedPlayerName();
            if (szName && strlen(szName) > 0) {
                const ImVec2 textSize = ImGui::CalcTextSize(szName);
                const ImVec2 textPos =
                    ImFloor({(min.x + max.x - textSize.x) / 2.f,
                             min.y - textSize.y - 2.f});
                pBackgroundDrawList->AddText(textPos + ImVec2{1, 1},
                                             IM_COL32(0, 0, 0, 255), szName);
                pBackgroundDrawList->AddText(
                    textPos, IM_COL32(255, 255, 255, 255), szName);
            }
        }
        if (bHealthbar) {
            const int iClampedHp =
                std::min(pPlayerController->m_iPawnHealth(), 100u);

            const ImVec2 barMin = min - ImVec2{5, 0};
            const ImVec2 barMax = ImVec2{min.x - 2, max.y};

            const float green = iClampedHp * 2.f * 2.55f;
            const float greenClamped = (std::min)(255.f, green);
            const float red = (std::min)(255.f, 510 - green);

            const float height = ((barMax.y - barMin.y) * iClampedHp) / 100.f;

            pBackgroundDrawList->AddRectFilled(barMin - ImVec2{0, 1},
                                               barMax + ImVec2{0, 1},
                                               IM_COL32(0, 0, 0, 255));
            if (iClampedHp > 0) {
                pBackgroundDrawList->AddRectFilled(
                    ImVec2{barMin.x + 1, barMax.y - (std::max)(1.f, height)},
                    ImVec2{barMax.x - 1, barMax.y},
                    IM_COL32(red, greenClamped, 0, 255));
            }
        }
    }
}
