#pragma once

#define FRAMEWORK_API extern "C" __declspec(dllimport)

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <magic_enum.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "BattleCityEnums.h"

using SpriteTypeBehaviourPair = std::pair<BattleCity::Manager::SpriteType, BattleCity::Object::Behaviour>;

#include "Hashes.h"
