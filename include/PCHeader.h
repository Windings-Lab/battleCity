#pragma once

#define FRAMEWORK_API extern "C" __declspec(dllimport)

// String, Streams
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

// Containers
#include <array>
#include <unordered_map>
#include <unordered_set>

// Exceptions
#include <exception>
#include <stdexcept>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <memory>
#include <thread>
#include <type_traits>
#include <utility>

using namespace std::string_view_literals;
using namespace std::string_literals;

#include "BattleCityEnums.h"
#include "magic_enum.hpp"

using SpriteTypeBehaviourPair = std::pair<BattleCity::Manager::SpriteType, BattleCity::Object::Behaviour>;

#include "Hashes.h"
