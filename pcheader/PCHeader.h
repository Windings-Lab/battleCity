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
#include <stack>
#include <unordered_map>
#include <unordered_set>

// Exceptions
#include <exception>
#include <stdexcept>

// Timers, GameLoop, Random
#include <chrono>
#include <random>

// Stoi and etc
#include <cstdlib>

// Template related
#include <typeindex>
#include <type_traits>

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <utility>

using namespace std::string_view_literals;
using namespace std::string_literals;

#include "BattleCity/Enums.h"
#include "BattleCity/NamespaceAliases.h"

#include "BattleCity/Utility/BasicMacros.h"
#include "BattleCity/Utility/magic_enum.hpp"
#include "BattleCity/Utility/Vector2Int.h"
