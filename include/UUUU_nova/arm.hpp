#pragma once
#include "pros/motor_group.hpp"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include <atomic>
#include <cstdint>
#include <memory>
#include <initializer_list>
#include <sys/_stdint.h>
#include <type_traits>
#include "pros/distance.hpp"
#include "PID/PID.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include <cstdio>
#include "UUUU_nova/pneumatics.hpp"


class Arm {
public:
    Arm(std::uint8_t arm_port, std::uint8_t rotation_port);

    //手臂目標位置
    enum position {
        //put low
        UP = 21418,
        MID = 20727,
        MID_IN = 14300, 
        INTAKE = 3178,
        DOWN = 1088
    };

    //手臂遙控抬升
    void up();

    //手臂遙控下降
    void down();

    //手臂停止
    void stop();

    //判斷手臂的位置是否在DOWN的位置
    bool not_down();

    //判斷手臂的位置是否低於INTAKE
    bool lower_intake();

    //手臂PID作動，position(目標位置), ess(誤差值，預設為30), stabletime(穩定後跳出時間，預設為50), outtime(卡住強制跳出時間，預設為1500)
    void pid_arm(Arm::position position, int ess = 30, int stabletime = 5,int outtime = 150);

    //遙控時手臂動作程式
    void arm_move();

    //遙控手臂程式
    void remote(pros::Controller Controller);

    //將正在執行的手臂PID動作取消
    static bool move_break;

private:
    bool new_control = false;
    Arm::position state;
    double error_up;
    double error_down;

    // std::unique_ptr<pros::MotorGroup> intake_motors;
    std::unique_ptr<pros::Motor> arm_motor;
    std::unique_ptr<pros::Rotation> rotation;
    pid::PID arm_pid;
    
    // std::unique_ptr<pros::Distance> distance;
    // pros::adi::Pneumatics pto {0,false};
};