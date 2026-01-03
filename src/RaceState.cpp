//
// Created by Euan Jones on 31/12/2025.
//

#include "RaceState.hpp"

RaceState::RaceState(int total_laps_)
    : current_lap_(0),
      total_laps_(total_laps_),
      safety_car_active_(false) {}

RaceState RaceState::make_demo_race() {
    RaceState race(58);

    race.drivers_.emplace_back("Norris", 90.0, 0.25);
    race.drivers_.emplace_back("Alonso", 110.0, 0.34);
    race.drivers_.emplace_back("Leclerc", 98.0, 0.23);
    race.drivers_.emplace_back("Sainz", 87.0, 0.22);

    race.cars_.emplace_back(
        "🟠 ML25",
        &race.drivers_[0],
        0,
        TyreCompound::Medium,
        0,
        100.0
    );
    race.cars_.emplace_back(
        "🟢 AM09",
        &race.drivers_[1],
        0,
        TyreCompound::Soft,
        0,
        100.0
    );
    race.cars_.emplace_back(
        "🔴 FR30",
        &race.drivers_[2],
        0,
        TyreCompound::Medium,
        0,
        100.0
    );
    race.cars_.emplace_back(
        "🔵 RB10",
        &race.drivers_[3],
        0,
        TyreCompound::Hard,
        0,
        100.0
    );

    return race;
}