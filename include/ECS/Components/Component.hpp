#pragma once

#include <bitset>
#include <cstdint>

#include "ECS/Entity/Entity.hpp";

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

struct Component {
	Entity entity;
};