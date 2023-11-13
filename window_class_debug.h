#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include "p_windows_simple.h"

class WindowMessageMap {
public:
    WindowMessageMap();
    std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const;
private:
    std::unordered_map<DWORD, std::string> map_;
};