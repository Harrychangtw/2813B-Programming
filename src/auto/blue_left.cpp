#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
//關掉自動時執行的task
extern bool off;


void Blue::left() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });
    chassis.setPose(58, -13, 90);
    chassis.turnToPoint(68, 0,1000);
    pros::delay(200);
    subsystem::arm.pid_arm(Arm::position::MID, 200, 1, 100);
    subsystem::arm.pid_arm(Arm::position::DOWN, 200, 1, 150);
    
    chassis.moveToPoint(23.5,-23.5,1200,{.forwards=false,.maxSpeed=100},true);
    subsystem::pneumatics.hook_auto(true);

    
}