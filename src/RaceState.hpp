//
// Created by Euan Jones on 31/12/2025.
//

#ifndef F1_STRATEGY_SIM_RACESTATE_HPP
#define F1_STRATEGY_SIM_RACESTATE_HPP
#include <vector>
#include "CarState.hpp"
#include "Driver.hpp"


class RaceState {
    public:
        RaceState(int total_laps_);

        [[nodiscard]] const std::vector<Driver>& drivers() const {return drivers_;}
        [[nodiscard]] const std::vector<CarState>& cars() const {return cars_;}
        [[nodiscard]] std::vector<CarState>& cars() {return cars_;}
        [[nodiscard]] int current_lap() const {return current_lap_;}
        [[nodiscard]] int total_laps() const {return total_laps_;}
        [[nodiscard]] bool safety_car_active() const {return safety_car_active_;}

        static RaceState make_demo_race();

        void set_current_lap(int current_lap) {current_lap_ = current_lap;}

    private:
        std::vector<Driver> drivers_;
        std::vector<CarState> cars_;
        int current_lap_;
        int total_laps_;
        bool safety_car_active_;
        // double safety_car_gain_;
};


#endif //F1_STRATEGY_SIM_RACESTATE_HPP