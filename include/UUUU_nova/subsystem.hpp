#pragma once
#include "UUUU_nova/intake.hpp"
#include "UUUU_nova/pneumatics.hpp"
#include "UUUU_nova/arm.hpp"

namespace subsystem{
    //intake的函式庫
    static Intake intake(14, 9, 11, 'G', 5);//{-13,14}, 

    //氣動的函式庫
    static Pneumatics pneumatics('B', 'D', 'A', 'H');

    //手臂的函式庫
    static Arm arm(9, 8);
}