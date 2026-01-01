//
// Created by Euan Jones on 31/12/2025.
//

#ifndef F1_STRATEGY_SIM_SIMULATION_HPP
#define F1_STRATEGY_SIM_SIMULATION_HPP
#include "CarState.hpp"
#include <vector>
#include "RaceState.hpp"

double calculate_lap_time(const CarState& car);

struct Strategy {
    double pit_time_seconds = 2.5;
    std::vector<int> pit_laps_ = {10, 40};
    std::vector<TyreCompound> compounds_ = {TyreCompound::Soft, TyreCompound::Medium, TyreCompound::Hard};
};

void advance_lap(RaceState& race);

void simulate_race(RaceState& race, const Strategy& strategy);

#endif //F1_STRATEGY_SIM_SIMULATION_HPP