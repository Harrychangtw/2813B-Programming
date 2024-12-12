#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
#include <future>

//關掉自動時執行的task
extern bool off;
ASSET(redleft1v3_txt);
ASSET(redleft2v2_txt);
ASSET(redleft4v1_txt);

void Red::left() {
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });

    chassis.setPose(-58, 11, 270);
    chassis.swingToPoint(-68, 0,DriveSide::RIGHT,1000,{},true);
    pros::delay(200);
    subsystem::arm.pid_arm(Arm::position::MID, 50, 3, 150);
    
    chassis.moveToPoint(-60,7,1000,{true},false);
    subsystem::arm.pid_arm(Arm::position::MID_IN, 100, 3, 50);
    
    chassis.moveToPoint(-17,27,1200,{.forwards=false,.maxSpeed=100},false);
    subsystem::pneumatics.hook_auto(true);
    pros::delay(300);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);





    chassis.moveToPoint(-23.5,50,1200,{.forwards=true,.maxSpeed=100},true);

    subsystem::arm.pid_arm(Arm::position::DOWN, 50, 3, 150);
    chassis.waitUntilDone();
    pros::delay(300);

    chassis.turnToPoint(-3.5, 43.5, 1200);

    chassis.moveToPose(-8,43.5,-270,1500,{.forwards=true,.maxSpeed=90},false);

    pros::delay(500);

    chassis.moveToPose(-30,49,-270,1000,{.forwards=false,.maxSpeed=90,.earlyExitRange=5},false);
    

    
    chassis.moveToPoint(-8,50,1500,{.forwards=true,.maxSpeed=90},false);

    pros::delay(900);
    

    chassis.moveToPoint(-23,7,2200,{.forwards=true,.maxSpeed=100},false);


}