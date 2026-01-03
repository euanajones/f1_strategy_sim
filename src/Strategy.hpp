//
// Created by Euan Jones on 03/01/2026.
//

#ifndef F1_STRATEGY_SIM_STRATEGY_HPP
#define F1_STRATEGY_SIM_STRATEGY_HPP
#include <vector>
#include "TyreCompound.hpp"

// Generic driver pit and tyre strategy
struct Strategy {
    double pit_time_seconds_ = 2.5;
    std::vector<int> pit_laps_ = {10, 40};
    std::vector<TyreCompound> compounds_ = {TyreCompound::Soft, TyreCompound::Medium, TyreCompound::Hard};
};

#endif //F1_STRATEGY_SIM_STRATEGY_HPP