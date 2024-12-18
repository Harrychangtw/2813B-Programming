#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
//關掉自動時執行的task
extern bool off;


ASSET(bl1_v2_txt);
ASSET(rr1_v2_txt);
void Red::right() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });
    chassis.setPose(-52, -63, 270.0);
    chassis.follow(rr1_v2_txt, 15, 2000,false,false);
    subsystem::pneumatics.hook_auto(true);


    
    subsystem::intake.auto_spin(Intake::mode::INTAKE, false,600,3000,0);
    chassis.swingToPoint(-23.0, -42, DriveSide::RIGHT,2200,{},true);

    chassis.waitUntilDone();
    pros::delay(400);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,2400,0);

    chassis.moveToPoint(-30.0, -45, 2000,{true},false);
    pros::delay(200);
    chassis.moveToPoint(-40.0, -33, 2000,{true},false);
    pros::delay(400);
    subsystem::pneumatics.hook_auto(false);
    
    chassis.turnToHeading(-130.0, 600);
    chassis.moveToPoint(-23.0, -25, 2000,{.forwards=false,.maxSpeed=90},true);
    pros::delay(800);
    subsystem::pneumatics.hook_auto(true);
    chassis.waitUntilDone();
    chassis.turnToPoint(-49.0, 0, 1000);


    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,0);

    pros::delay(200);
    chassis.moveToPoint(-53.0, 0, 3500,{.forwards=true,.maxSpeed=90});
    pros::delay(700);
    subsystem::pneumatics.intake_auto(false);
    chassis.moveToPoint(-40.0, -6, 2000,{.forwards=false},false);
 
    chassis.moveToPose(-30.5, -30.5, -315.0, 2000, {.forwards=false,.earlyExitRange=4}, false);

    

     chassis.moveToPoint(-16.0, -13, 3000,{});


}