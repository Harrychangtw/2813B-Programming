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


//std::uint8_t pto_port,
class Pneumatics{
public:
    Pneumatics(std::uint8_t ele_port, std::uint8_t intakeup_port, std::uint8_t hook_port, std::uint8_t hand_port);
    
    //intake氣動抬升，true(抬升), false(放下)
    void intake_auto(bool sta);

    //hook氣動，true(夾), false(鬆開)
    void hook_auto(bool sta);

    //招財貓手段氣動，true(放下), false(收起)
    void hand_auto(bool sta);

    //氣動遙控程式
    void remote(pros::Controller Controller);

    //intake氣動位置，true(上), false(下)
    static bool intake_pne;

    //intake收起時，手臂是否需要做動
    static bool state;

private:
    

    // std::unique_ptr<pros::MotorGroup> intake_motors;
    // pros::adi::Pneumatics pto {0,false};
    pros::adi::Pneumatics ele {0,false};
    pros::adi::Pneumatics intake_up {0,false};
    pros::adi::Pneumatics hook {0,false};
    // pros::adi::Pneumatics color_air {0,false};
    pros::adi::Pneumatics hand {0,false};
    // std::unique_ptr<pros::Optical> color;

};