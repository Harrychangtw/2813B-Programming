#pragma once
#include "pros/motor_group.hpp"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include <atomic>
#include <memory>
#include <initializer_list>
#include <sys/_stdint.h>
#include "UUUU_nova/arm.hpp"
#include "UUUU_nova/intake.hpp"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "PID/PID.hpp"
#include "pros/optical.hpp"

class Pneumatics {
public:
    Pneumatics(std::uint8_t ele_port, std::uint8_t intakeup_port, std::uint8_t hook_port, std::uint8_t hand_port);
    
    void intake_auto(bool sta);
    void hook_auto(bool sta);
    void hand_auto(bool sta);
    void remote(pros::Controller Controller);
    
    static bool intake_pne;
    static bool state;

    // Updated method to check if elevator is unlocked (removed const qualifier)
    bool is_elevator_unlocked();

    // Method to start the elevator unlock timer
    void start_elevator_unlock_timer();

private:
    pros::adi::Pneumatics ele {0,false};
    pros::adi::Pneumatics intake_up {0,false};
    pros::adi::Pneumatics hook {0,false};
    pros::adi::Pneumatics hand {0,false};

    // Members for elevator time lock
    uint32_t elevator_unlock_time;
    bool elevator_unlocked;
};