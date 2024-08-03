#include "Locator.h"

std::unordered_map<std::type_index, std::weak_ptr<void>> Locator::instances;