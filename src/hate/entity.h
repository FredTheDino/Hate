#pragma once
#include "system.h"
#include <vector>

//
// The Entity_System holds all active
// entities and removes the ones tagged
// as trash. 
// 
// The Entity_System works as a centrialized
// hub that can act out some form of control
// on other systems. All systems have to 
// register a delete callback which gets
// called when an entity is removed here.
//
// This is to prevent that the systems get 
// pulled for that information everytime.
// 
namespace hate {
    struct Entity {
        std::vector<bool> systems;
    }
}