#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"

//關掉自動時執行的task
extern bool off;
ASSET(rr1_v2_txt);


void Red::right() {
    // intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });

    chassis.setPose(-50,-63,270);
    chassis.follow(rr1_v2_txt, 15, 5000,false,false);
    subsystem::pneumatics.hook_auto(true);


    
    
    chassis.swingToPoint(-23, -47,DriveSide::RIGHT,4000,{},true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,400,1);
    
    chassis.moveToPoint(-24, -47, 2000);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,400,300,0);
    subsystem::pneumatics.hook_auto(false);
    subsystem::intake.auto_spin(Intake::mode::STOP, false);
    pros::delay(200);
    chassis.moveToPoint(-24, -28, 2000,{false},false);
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
   
    chassis.turnToPoint(-48, 0, 1000);
    chassis.moveToPoint(-38, -10, 2000,{.forwards=true,.maxSpeed=100},true);
    pros::delay(900);
    chassis.moveToPoint(-48, -0, 2000,{.forwards=true,.maxSpeed=50});
    pros::delay(200);
    chassis.moveToPoint(-53, 7, 2000,{.forwards=true,.maxSpeed=60});
    pros::delay(2000);
    chassis.moveToPoint(-23, 0, 2000,{.forwards=true,.maxSpeed=100});

}