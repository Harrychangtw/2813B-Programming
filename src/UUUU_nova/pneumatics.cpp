#include "UUUU_nova/pneumatics.hpp"
#include "pros/misc.h"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include <cstdio>
#include "setup.hpp"

bool Pneumatics::intake_pne = false;
bool Pneumatics::state = false;

extern bool team;

//std::uint8_t pto_port,
Pneumatics::Pneumatics(std::uint8_t ele_port, std::uint8_t intakeup_port, std::uint8_t hook_port, std::uint8_t hand_port) {
    // this->pto = pros::adi::Pneumatics{pto_port,false};
    this->ele = pros::adi::Pneumatics{ele_port,false};
    this->intake_up = pros::adi::Pneumatics{intakeup_port,false};
    this->hook = pros::adi::Pneumatics{hook_port,false};
    this->hand = pros::adi::Pneumatics{hand_port,false};
}
Arm armP(9, 8);

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

//氣動遙控程式
void Pneumatics::remote(pros::Controller Controller) {
    if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        this->hook.toggle();
    }
    if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) && (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == false)) {
        intake_pne = !intake_pne;
        if(intake_pne) {
            this->intake_up.extend();//intake抬升
            if(armP.lower_intake()) {
                Arm::move_break = true;
                state = true;
                armP.pid_arm(Arm::position::INTAKE);
                state = false;
            }
        }
        else {
            this->intake_up.retract();//intake下降
        }
    }
    if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        this->ele.toggle();
    }
    if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        this->hand.toggle();
    }
};
