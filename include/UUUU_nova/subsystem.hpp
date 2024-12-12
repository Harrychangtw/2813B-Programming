#pragma once
#include "UUUU_nova/intake.hpp"
#include "UUUU_nova/pneumatics.hpp"
#include "UUUU_nova/arm.hpp"

namespace subsystem{
    //intake的函式庫
    static Intake intake(20, 9, 2, 'C', 11);//{-13,14}, 

    //氣動的函式庫
    static Pneumatics pneumatics('G', 'B', 'A', 'D');

    //手臂的函式庫
    static Arm arm(13, 1);
}