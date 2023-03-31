#pragma once

#include "../../schema/schema.hpp"

class C_EconItemView {
   public:
    SCHEMA_FIELD(m_iItemID, "C_EconItemView", "m_iItemID", uint64_t);
    SCHEMA_FIELD(m_iItemIDHigh, "C_EconItemView", "m_iItemIDHigh", uint32_t);
    SCHEMA_FIELD(m_iItemIDLow, "C_EconItemView", "m_iItemIDLow", uint32_t);
    SCHEMA_FIELD(m_iInventoryPosition, "C_EconItemView", "m_iInventoryPosition",
           uint32_t);
    SCHEMA_FIELD(m_iAccountID, "C_EconItemView", "m_iAccountID", uint32_t);
    SCHEMA_FIELD(m_szCustomName, "C_EconItemView", "m_szCustomName",
                 const char*);
};
