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

// Sleep_until GameLoop
#include <chrono>
#include <thread>

// Stoi and etc
#include <cstdlib>

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

using namespace std::string_view_literals;
using namespace std::string_literals;

#include "BattleCityEnums.h"
#include "magic_enum.hpp"
