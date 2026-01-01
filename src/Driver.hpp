//
// Created by Euan Jones on 31/12/2025.
//

#ifndef F1_STRATEGY_SIM_DRIVER_HPP
#define F1_STRATEGY_SIM_DRIVER_HPP
#include <string>


class Driver {
    public:
        Driver(std::string driver_name, double base_pace_seconds, double consistency)
            :   driver_name_(std::move(driver_name)),
                base_pace_seconds_(base_pace_seconds),
                consistency_(consistency) {}

        const std::string& driver_name() const {return driver_name_;};
        double base_pace() const {return base_pace_seconds_;}
        double consistency() const {return consistency_;}
    private:
        std::string driver_name_;
        double base_pace_seconds_;
        double consistency_;
};


#endif //F1_STRATEGY_SIM_DRIVER_HPP