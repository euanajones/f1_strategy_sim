# F1 Race Strategy Simulator (C++ Learning Project)
This repository contains a simple F1 style race strategy simulator written in C++.
It is not a realistic telemetry or physics based model, it is a structure project to learn and practice modern C++ from a beginner level.
## Project Goals
- Learn core C++ concepts: classes, references, headers/source separation, memory management and efficiency.
- Practice working with STL containers ('std::vector'), algorithms ('std::sort'), and ranges.
- Introduce basic simulation concepts: state update per lap, simple tyre degradation, pit-stop logic.
- Develop Object-Orientated Programming knowledge beyond academic studies.
- Later stage goals: Monte Carlo simulations, performance and design improvements.
## High Level Design
- **Driver**: name, base pace, consistency.
- **CarState**: driver reference, tracks mutable car state (lap, tyre compound, tyre age, total time, etc).
- **RaceState**: owns drivers and cars, and race wide metrics (current lap, total laps, etc).
- **Strategy**: pit-stop laps, stint length, and tyre compounds.
- **Simulation**: functions to advance lap, simulate full race, and run Monte Carlo batches.
Physics and strategy have been simplified to core components to maintain focus on C++ structure, code quality and OOP paradigm.
## Planned Learning Roadmap
1. Core model and deterministic race ✅
2. Introduce strategy handling, tyre compound changes and basic pit-stop logic ✅
3. Add randomness and Monte Carlo to estimate win probabilities ✅
4. Compare different strategies ✅
5. Optional: performance tuning, basic testing.
## Personal Outcomes
- Worked with C++ reference and pointers, bringing practical application to previously theoretical concepts.
- Built a greater understanding of memory management within C++, something new to me coming from higher level languages with automatic garbage collection.
- Explored and implemented a basic Monte Carlo Simulation, broadening my knowledge of computational statistics.
- Good introduction to C++ as a language, learning about its OOP system using .hpp and .cpp files, and its memory management logic.
