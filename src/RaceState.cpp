//
// Created by Euan Jones on 31/12/2025.
//

#include "RaceState.hpp"
#include "simulation.hpp"

// Initialise a base race state
RaceState::RaceState(int total_laps_)
    : current_lap_(0),
      total_laps_(total_laps_),
      safety_car_active_(false) {}

RaceState RaceState::make_demo_race() {
    RaceState race(58); // Initialise race with 58 laps

    // Create Driver objects in RaceState
    race.drivers_.emplace_back("Norris", 80.344, 0.82,
        Strategy{
            2.7,
            {15, 35},
            {TyreCompound::Medium, TyreCompound::Soft, TyreCompound::Soft}
        });
    race.drivers_.emplace_back("Alonso", 81.744, 0.74,
        Strategy{
            2.9,
            {28, 45},
            {TyreCompound::Medium, TyreCompound::Soft, TyreCompound::Medium}
        });
    race.drivers_.emplace_back("Leclerc", 81.041, 0.72,
        Strategy{
            2.5,
            {20, 30},
            {TyreCompound::Hard, TyreCompound::Soft, TyreCompound::Medium}
        });
    race.drivers_.emplace_back("Sainz", 81.031, 0.87,
        Strategy{
            2.5,
            {20, 45},
            {TyreCompound::Hard, TyreCompound::Soft, TyreCompound::Medium}
        });

    // Create CarState objects in RaceState
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