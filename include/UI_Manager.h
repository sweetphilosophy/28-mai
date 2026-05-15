#pragma once

#include "InventoryManager.h"
#include "ObjectManager.h"
#include "DimensionManager.h"

struct UI_Manager {

private:
    void DrawHPbar(const ObjectManager& objectManager) const;

public:
    void draw(ObjectManager& objectManager, InventoryManager& InventoryManager, DimensionManager& dimensionManager);
};