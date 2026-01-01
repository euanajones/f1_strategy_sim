#include <iostream>
#include <iomanip>
#include "RaceState.hpp"
#include "simulation.hpp"

int main() {
    std::cout << "=== F1 Strategy Sim ===\n\n";

    auto race = RaceState::make_demo_race();
    const auto& cars = race.cars();

    Strategy my_strategy;

    std::cout << "Car ID\tDriver\t\tLap Time (fresh)\n";
    std::cout << "------------------------------------\n";

    for (const auto & car : cars) {
        double lap_time = calculate_lap_time(car);

        std::cout << car.car_id() << "\t"
                  << car.driver()->driver_name() << "\t\t"
                  << std::fixed << std::setprecision(1) << lap_time << "s\n";
    }

    simulate_race(race, my_strategy);

    return 0;
}
