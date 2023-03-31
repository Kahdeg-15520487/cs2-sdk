#pragma once

#include "c_baseplayerpawn.hpp"
#include "cplayer_weaponservices.hpp"

class C_CSPlayerPawn : public C_BasePlayerPawn {
   public:
    bool IsEnemyToLocalPlayer(int lpTeam);
    SCHEMA_FIELD(m_pWeaponServices, "C_BasePlayerPawn", "m_pWeaponServices",
           CPlayer_WeaponServices*);
};
