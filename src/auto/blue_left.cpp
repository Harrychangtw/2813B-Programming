#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
//關掉自動時執行的task
extern bool off;

ASSET(bl1_v2_txt);
ASSET(rr1_v2_txt);
void Blue::left() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });
    chassis.setPose(50,-63,90);
    chassis.follow(bl1_v2_txt, 15, 2000,false,false);
    subsystem::pneumatics.hook_auto(true);


    
    subsystem::intake.auto_spin(Intake::mode::INTAKE, false,600,3000,0);
    chassis.swingToPoint(23, -42,DriveSide::LEFT,4500,{},true);

    chassis.waitUntilDone();
    pros::delay(400);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,2400,0);

    chassis.moveToPoint(30, -38, 2000,{true},false);
    pros::delay(200);
    chassis.moveToPoint(37, -34, 2000,{true},false);
    pros::delay(400);
    subsystem::pneumatics.hook_auto(false);
    
    chassis.turnToHeading(130, 2000);
    chassis.moveToPoint(23, -18, 2000,{false},false);
    subsystem::pneumatics.hook_auto(true);
    pros::delay(400);

    chassis.turnToPoint(40, 0, 1000);


    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,0);

    pros::delay(200);
    chassis.moveToPoint(40, 0, 3000,{.forwards=true});
    pros::delay(700);
    subsystem::pneumatics.intake_auto(false);
    chassis.moveToPoint(34, -6, 3000,{.forwards=false});
 
    chassis.moveToPose(23.5,-23.5,315,2000,{.forwards=false,.earlyExitRange=3},false);

    

     chassis.moveToPoint(13, -13, 3000,{});


}