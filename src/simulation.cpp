//
// Created by Euan Jones on 31/12/2025.
//
#include "simulation.hpp"

#include "CarState.hpp"
#include "RaceState.hpp"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>

// Overloaded calculate_lap_time functions for regular use and Monte Carlo Simulation testing

// Calculate the lap time of the passed in CarState object
double calculate_lap_time(const CarState& car) {
    double base_time = car.driver()->base_pace();
    double degradation = degradation_rate(car.current_compound()) * car.tyre_age_laps();
    return base_time + degradation;
}

// Calculate the lap time of passed in CarState object with psuedo-random variance
double calculate_lap_time(const CarState& car, std::mt19937& rng) {
    double base_time = car.driver()->base_pace();
    double degradation = degradation_rate(car.current_compound()) * car.tyre_age_laps();
    double driver_consistency = car.driver()->consistency();

    // Lap Time Variation scaled to consistency with normal distribution
    std::normal_distribution<double> lap_variance(0.0, 1-driver_consistency);

    return base_time + degradation + lap_variance(rng);
}

// Advnace the lap of the passed in RaceState object
void advance_lap(RaceState& race) {
    // Update each CarState object
    for (std::vector<CarState>& cars = race.cars(); CarState& car : cars) {
        car.set_tyre_age_laps(car.tyre_age_laps() + 1); // Increase current tyre age

        car.set_current_lap(car.current_lap() + 1); // Increase current CarState lap number
    }
    race.set_current_lap(race.current_lap() + 1); // Increase global RaceState lap number
}

// Handles the simulation of a full race to completion
void simulate_race(RaceState& race, std::mt19937& rng) {
    for (int i = 0; i < race.total_laps(); i++) {
        auto& cars = race.cars();

        // Update each CarState object for each lap of the race
        for (auto& car : cars) {
            double lap_time = calculate_lap_time(car, rng);
            int current_car_lap = car.current_lap();

            auto current_strategy = car.driver()->strategy(); // Fetch current driver strategy

            if (std::ranges::find(current_strategy.pit_laps_, current_car_lap) != current_strategy.pit_laps_.end()) {
                car.set_tyre_age_laps(0);

                // Increment the tyre compound to next in strategy
                int stint_index = car.current_stint_index();
                if (stint_index < static_cast<int>(current_strategy.compounds_.size())) {
                    car.set_current_compound(current_strategy.compounds_[stint_index]);
                    car.set_stint_index(stint_index + 1);
                }

                // Pit time variance, 68% of pits will be +/- 1.0 second
                std::normal_distribution<double> pit_variance(0.0, 1.0);
                double pit_time = current_strategy.pit_time_seconds_ + pit_variance(rng);

                car.set_total_lap_time(car.total_lap_time() + pit_time);
            }

            // std::cout << car.driver()->driver_name() << " lap time: " << lap_time << "\n";
            car.set_total_lap_time(car.total_lap_time() + lap_time);
        }
        advance_lap(race);
    }

    // After the race: sort by total_lap_time and print order
    auto& cars = race.cars();

    std::ranges::sort(cars,[](const CarState& a, const CarState& b)
        {return a.total_lap_time() < b.total_lap_time(); });

    std::cout << "Finishing order:\n";
    int position = 1;
    for (const auto& car : cars) {
        std::cout << position << ". "
                  << car.car_id() << " - "
                  << car.driver()->driver_name()
                  << " - " << car.total_lap_time() << "s\n";
        ++position;
    }
}

ResultStats run_monte_carlo(const RaceState& base_race, const Strategy& strategy, int N) {
    ResultStats stats;

    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < N; i++) {
        std::cout << "=== SIMULATION " << i + 1 << " ===" << std::endl;
        RaceState race = base_race; // Copy of reset state, ensures statistical independence
        simulate_race(race, rng);

        const auto& cars = race.cars();

        stats.wins_[cars[0].driver()->driver_name()]++; // Determine P1 driver

        for (int pos = 0; pos < cars.size(); pos++) {
            stats.total_position_[cars[pos].driver()->driver_name()] += pos + 1;
        }

        stats.runs_++; // Increment stats struct run value
    }

    return stats;
}
