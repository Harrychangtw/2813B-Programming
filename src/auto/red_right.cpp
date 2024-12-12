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
    chassis.follow(rr1_v2_txt, 15, 2000,false,false);
    subsystem::pneumatics.hook_auto(true);


    
    
    chassis.swingToPoint(-24, -47,DriveSide::RIGHT,4000,{},true);
    pros::delay(200);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,800,0);
    pros::delay(500);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,0,1);
    chassis.moveToPoint(-24, -45.5, 2000);
    
    subsystem::pneumatics.hook_auto(false);
    subsystem::intake.auto_spin(Intake::mode::STOP, false);
    pros::delay(200);
    chassis.moveToPoint(-24, -26, 2000,{false},false);
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
   
    //strat: go to the middle

    
    
    //------------------------
    
    //strat:go straigjt touch the latter
    pros::delay(1200);
    chassis.moveToPoint(-7, -24, 2000,{true},false);
    //-------------------------
    
}