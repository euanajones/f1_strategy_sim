//
// Created by Euan Jones on 31/12/2025.
//
#include "simulation.hpp"

#include "CarState.hpp"
#include "RaceState.hpp"
#include <algorithm>
#include <iostream>
#include <ostream>

double calculate_lap_time(const CarState& car) {
    double base_time = car.driver()->base_pace();
    double degradation = degradation_rate(car.current_compound()) * car.tyre_age_laps();
    return base_time + degradation;
}

void advance_lap(RaceState& race) {
    for (std::vector<CarState> cars = race.cars(); CarState& car : cars) {
        car.set_tyre_age_laps(car.tyre_age_laps() + 1);

        car.set_current_lap(car.current_lap() + 1);
    }
    race.set_current_lap(race.current_lap() + 1);
}

void simulate_race(RaceState& race, const Strategy& strategy) {
    for (int i = 0; i < race.total_laps(); i++) {
        auto& cars = race.cars();
        for (auto& car : cars) {
            double lap_time = calculate_lap_time(car);
            int current_car_lap = car.current_lap();

            if (std::ranges::find(strategy.pit_laps_, current_car_lap) != strategy.pit_laps_.end()) {
                car.set_tyre_age_laps(0);

                int stint_index = car.current_stint_index();
                if (stint_index < static_cast<int>(strategy.compounds_.size())) {
                    car.set_current_compound(strategy.compounds_[stint_index]);
                    car.set_stint_index(stint_index + 1);
                }

                car.set_total_lap_time(car.total_lap_time() + strategy.pit_time_seconds);
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
