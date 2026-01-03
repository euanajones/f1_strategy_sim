//
// Created by Euan Jones on 31/12/2025.
//

#ifndef F1_STRATEGY_SIM_SIMULATION_HPP
#define F1_STRATEGY_SIM_SIMULATION_HPP
#include <map>
#include <random>

#include "CarState.hpp"
#include "RaceState.hpp"
#include "Strategy.hpp"

// Struct for Monte Carlo Simulation results
struct ResultStats {
    std::map<std::string, int> wins_;
    std::map<std::string, double> total_position_;
    int runs_ = 0;
};

double calculate_lap_time(const CarState& car, std::mt19937& rng);

void advance_lap(RaceState& race);

void simulate_race(RaceState& race, const Strategy& strategy, std::mt19937& rng);

ResultStats run_monte_carlo(const RaceState& base_race, const Strategy& strategy, int num_simulations);

#endif //F1_STRATEGY_SIM_SIMULATION_HPP