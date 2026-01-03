//
// Created by Euan Jones on 31/12/2025.
//

#ifndef F1_STRATEGY_SIM_CARSTATE_HPP
#define F1_STRATEGY_SIM_CARSTATE_HPP
#include "Driver.hpp"
#include "TyreCompound.hpp"

class CarState {
    public:
        CarState(std::string car_id, const Driver* driver, int current_lap, TyreCompound current_compound, int tyre_age_laps,
            double fuel_load)
            : car_id_(std::move(car_id)),
              driver_(driver),
              current_lap_(current_lap),
              current_compound_(current_compound),
              tyre_age_laps_(tyre_age_laps),
              fuel_load_(fuel_load),
              total_lap_time_(0),
              current_stint_index_(0) {}

        [[nodiscard]] const std::string& car_id() const {return car_id_;}
        [[nodiscard]] const Driver* driver() const {return driver_;}
        [[nodiscard]] int current_lap() const {return current_lap_;}
        [[nodiscard]] TyreCompound current_compound() const {return current_compound_;}
        [[nodiscard]] int tyre_age_laps() const {return tyre_age_laps_;}
        [[nodiscard]] double fuel_load() const {return fuel_load_;}
        [[nodiscard]] double total_lap_time() const {return total_lap_time_;}
        [[nodiscard]] int current_stint_index() const {return current_stint_index_;}

        void set_current_lap(int current_lap) {current_lap_ = current_lap;}
        void set_current_compound(TyreCompound current_compound) {current_compound_ = current_compound;}
        void set_tyre_age_laps(int tyre_age_laps) {tyre_age_laps_ = tyre_age_laps;}
        void set_fuel_load(double fuel_load) {fuel_load_ = fuel_load;}
        void set_total_lap_time(double new_total_lap_time) {total_lap_time_ = new_total_lap_time;}
        void set_stint_index(int stint_index) {current_stint_index_ = stint_index;}
    private:
            std::string car_id_;
            const Driver *driver_;
            int current_lap_;
            TyreCompound current_compound_;
            int tyre_age_laps_;
            double fuel_load_;
            double total_lap_time_;
            int current_stint_index_;
};


#endif //F1_STRATEGY_SIM_CARSTATE_HPP