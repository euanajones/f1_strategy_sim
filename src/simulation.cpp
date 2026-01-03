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

double calculate_lap_time(const CarState& car) {
    double base_time = car.driver()->base_pace();
    double degradation = degradation_rate(car.current_compound()) * car.tyre_age_laps();
    return base_time + degradation;
}

double calculate_lap_time(const CarState& car, std::mt19937& rng) {
    double base_time = car.driver()->base_pace();
    double degradation = degradation_rate(car.current_compound()) * car.tyre_age_laps();

    // Lap Time Variation (+/- 0.2s) with normal distribution
    std::normal_distribution<double> lap_variance(0.0, 0.3);

    return base_time + degradation + lap_variance(rng);
}

void advance_lap(RaceState& race) {
    for (std::vector<CarState> cars = race.cars(); CarState& car : cars) {
        car.set_tyre_age_laps(car.tyre_age_laps() + 1);

        car.set_current_lap(car.current_lap() + 1);
    }
    race.set_current_lap(race.current_lap() + 1);
}

void simulate_race(RaceState& race, const Strategy& strategy, std::mt19937& rng) {
    for (int i = 0; i < race.total_laps(); i++) {
        auto& cars = race.cars();
        for (auto& car : cars) {
            double lap_time = calculate_lap_time(car, rng);
            int current_car_lap = car.current_lap();

            auto current_strategy = car.driver()->strategy(); // Fetch current driver strategy

            if (std::ranges::find(strategy.pit_laps_, current_car_lap) != strategy.pit_laps_.end()) {
                car.set_tyre_age_laps(0);

                int stint_index = car.current_stint_index();
                if (stint_index < static_cast<int>(strategy.compounds_.size())) {
                    car.set_current_compound(strategy.compounds_[stint_index]);
                    car.set_stint_index(stint_index + 1);
                }

                // Pit time variance (+/- 0.3s) with normal distribution
                std::normal_distribution<double> pit_variance(0.0, 0.3);
                double pit_time = strategy.pit_time_seconds_ + pit_variance(rng);

                car.set_total_lap_time(car.total_lap_time() + pit_time);
            }


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
        RaceState race = base_race; // Copy of reset state, ensures statistical independence
        simulate_race(race, strategy, rng);

        const auto& cars = race.cars();

        stats.wins_[cars[0].driver()->driver_name()]++; // Determine P1 driver

        for (int pos = 0; pos < cars.size(); pos++) {
            stats.total_position_[cars[pos].driver()->driver_name()] += pos + 1;
        }

        stats.runs_++; // Increment stats struct run value
    }

    return stats;
}
