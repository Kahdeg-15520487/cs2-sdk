#pragma once

#include "../../schema/schema.hpp"
#include "c_econitemview.hpp"

class C_AttributeContainer {
   public:
    SCHEMA_FIELD(m_Item, "C_AttributeContainer", "m_Item", C_EconItemView);
};
