//
// Created by Euan Jones on 31/12/2025.
//

#ifndef F1_STRATEGY_SIM_DRIVER_HPP
#define F1_STRATEGY_SIM_DRIVER_HPP
#include <string>

#include "simulation.hpp"


class Driver {
    public:
        Driver(std::string driver_name, double base_pace_seconds, double consistency, const Strategy& strategy)
            :   driver_name_(std::move(driver_name)),
                base_pace_seconds_(base_pace_seconds),
                consistency_(consistency),
                strategy_(std::move(strategy)) {}

        const std::string& driver_name() const {return driver_name_;};
        double base_pace() const {return base_pace_seconds_;}
        double consistency() const {return consistency_;}
        const Strategy& strategy() const {return strategy_;}
    private:
        std::string driver_name_;
        double base_pace_seconds_;
        double consistency_;
        Strategy strategy_;
};


#endif //F1_STRATEGY_SIM_DRIVER_HPP