//
// Created by Euan Jones on 03/01/2026.
//

#ifndef F1_STRATEGY_SIM_TYRECOMPOUND_HPP
#define F1_STRATEGY_SIM_TYRECOMPOUND_HPP

enum class TyreCompound {Soft, Medium, Hard};

static double degradation_rate(TyreCompound compound) {
    switch (compound) {
        case TyreCompound::Soft: return  0.10;
        case TyreCompound::Medium: return  0.15;
        case TyreCompound::Hard: return  0.05;
    }
    return 0.0;
}

#endif //F1_STRATEGY_SIM_TYRECOMPOUND_HPP