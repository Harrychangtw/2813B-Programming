#pragma once
#include "UUUU_nova/intake.hpp"
#include "UUUU_nova/pneumatics.hpp"
#include "UUUU_nova/arm.hpp"

namespace subsystem{
    //intake的函式庫
    static Intake intake(20, 9, 14, 'C', 16);//{-13,14}, 

    //氣動的函式庫
    static Pneumatics pneumatics('D', 'F', 'A', 'H');

    //手臂的函式庫
    static Arm arm(-7, 8);
}