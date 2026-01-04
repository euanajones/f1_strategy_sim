#include <iostream>
#include <iomanip>
#include "RaceState.hpp"
#include "simulation.hpp"

int main() {
    std::cout << "=== F1 Strategy Sim ===\n\n";

    auto race = RaceState::make_demo_race(); // Create a demo race state

    Strategy my_strategy;

    auto stats = run_monte_carlo(race, my_strategy, 10000); // Run 10,000 race simulations for Monte Carlo

    // Determine each driver number of wins and win rate
    for (const auto& [driver, wins] : stats.wins_) {
        double win_rate = static_cast<double>(wins) / stats.runs_;
        double avg_pos =
            stats.total_position_[driver] / stats.runs_;

        std::cout << driver
                  << " - Win %: " << win_rate * 100
                  << " - Avg Pos: " << avg_pos << "\n";
    }

    return 0;
}
