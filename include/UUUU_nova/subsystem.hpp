#pragma once
#include "UUUU_nova/intake.hpp"
#include "UUUU_nova/pneumatics.hpp"
#include "UUUU_nova/arm.hpp"

namespace subsystem{
    //intake的函式庫
    static Intake intake(20, 9, 2, 'H', 4);//{-13,14}, 

    //氣動的函式庫
    static Pneumatics pneumatics('C', 'F', 'A', 'B');//ele:left hand hand: right hand

    //手臂的函式庫
    static Arm arm(-13, 1);
}