#pragma once

#include <string>
#include <vector>

namespace HookEngine {

void init();
void hookAllModules(const std::string& packageName);
void hookModule(const std::string& packageName, const std::string& className);

} // namespace HookEngine
=== END FILE ===
