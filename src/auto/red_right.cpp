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


    
    
    chassis.swingToPoint(-24, -43,DriveSide::RIGHT,4000,{},true);
    pros::delay(200);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,800,0);
    pros::delay(500);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,0,1);
    chassis.moveToPoint(-24, -42, 2000);
    
    subsystem::pneumatics.hook_auto(false);
    subsystem::intake.auto_spin(Intake::mode::STOP, false);
    pros::delay(200);
    chassis.moveToPoint(-24, -26, 2000,{false},false);
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
   
    //strat: go to the middle
    chassis.turnToPoint(-48, 0, 1000);
    chassis.moveToPoint(-38, -10, 2000,{.forwards=true,.maxSpeed=100},true);
    pros::delay(1200);
    chassis.moveToPoint(-48, -0, 2000,{.forwards=true,.maxSpeed=60});
    pros::delay(800);
    chassis.moveToPoint(-53, 7, 2000,{.forwards=true,.maxSpeed=60});
    pros::delay(1500);
    chassis.moveToPose(-48,-18,0,1000,{.forwards=true,.earlyExitRange=1},false);
    
    chassis.moveToPoint(-3, -23, 2000,{.forwards=true,.maxSpeed=80});
    
    
    
    //------------------------
    /*
    //strat:go straigjt touch the latter

    chassis.moveToPoint(-24, -3, 2000,{false},false);
    //-------------------------
    */
}


