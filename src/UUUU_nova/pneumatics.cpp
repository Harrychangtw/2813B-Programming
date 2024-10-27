#include "UUUU_nova/pneumatics.hpp"
#include "pros/misc.h"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include <cstdio>
#include "setup.hpp"

bool Pneumatics::intake_pne = false;
bool Pneumatics::state = false;

extern bool team;

Pneumatics::Pneumatics(std::uint8_t ele_port, std::uint8_t intakeup_port, std::uint8_t hook_port, std::uint8_t hand_port) {
    this->ele = pros::adi::Pneumatics{ele_port,false};
    this->intake_up = pros::adi::Pneumatics{intakeup_port,false};
    this->hook = pros::adi::Pneumatics{hook_port,false};
    this->hand = pros::adi::Pneumatics{hand_port,false};
    this->elevator_unlocked = false;
    this->elevator_unlock_time = 0;
}



//intake氣動抬升，true(抬升), false(放下)
void Pneumatics::intake_auto(bool sta) {
    if(sta) {
        this->intake_up.extend();
    }
    else {
        this->intake_up.retract();
    }
}

//hook氣動，true(夾), false(鬆開)
void Pneumatics::hook_auto(bool sta) {
    if(sta) {
        this->hook.extend();
    }
    else {
        this->hook.retract();
    }
}

//招財貓手段氣動，true(放下), false(收起)
void Pneumatics::hand_auto(bool sta) {
    if(sta) {
        this->hand.extend();
    }
    else {
        this->hand.retract();
    }
}
bool Pneumatics::is_elevator_unlocked() {
    if (!elevator_unlocked && pros::millis() >= elevator_unlock_time) {
        elevator_unlocked = true;
    }
    return elevator_unlocked;
}

void Pneumatics::start_elevator_unlock_timer() {
    elevator_unlock_time = pros::millis() + 85; // 90 seconds from now
    elevator_unlocked = false;
}


//氣動遙控程式
void Pneumatics::remote(pros::Controller Controller) {
    if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        this->hook.toggle();
    }
    
    // Only allow elevator toggle if it's unlocked
    if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) && is_elevator_unlocked()) {
        this->ele.toggle();
    }
}