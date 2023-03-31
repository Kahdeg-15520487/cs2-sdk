#pragma once

#include <vector>
#include "../../schema/schema.hpp"
#include "chandle.hpp"

class CPlayer_WeaponServices {
   private:
    //std::vector<C_BasePlayerWeapon> weapons;

   public:
    //std::vector<C_BasePlayerWeapon> get_weapons();

    SCHEMA_FIELD(m_hMyWeapons, "CPlayer_WeaponServices", "m_hMyWeapons",
                 int32_t*);
    SCHEMA_FIELD_OFFSET(m_hMyWeapons1, "CPlayer_WeaponServices", "m_hMyWeapons",
                        0x8,
                  CHandle);
    SCHEMA_FIELD_OFFSET(m_hMyWeapons2, "CPlayer_WeaponServices", "m_hMyWeapons",
                  0x8 + 0x4, CHandle);
    SCHEMA_FIELD_OFFSET(m_hMyWeapons3, "CPlayer_WeaponServices", "m_hMyWeapons",
                  0x8 + 0x4 + 0x4, CHandle);
    SCHEMA_FIELD(m_hActiveWeapon, "CPlayer_WeaponServices", "m_hActiveWeapon",
           CHandle);
};
