#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Debug/Log.h"
#include "Debug/Assert.h"

#define SBR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
