#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
//關掉自動時執行的task
extern bool off;

ASSET(bl1_v2_txt);
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


    
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,3000,0);
    chassis.swingToPoint(23, -42,DriveSide::LEFT,4000,{},true);

    chassis.waitUntilDone();
    pros::delay(400);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,300,7200,0);

    chassis.moveToPoint(30, -38, 2000,{true},false);
    pros::delay(200);
    chassis.moveToPoint(37, -34, 2000,{true},false);
    pros::delay(800);
    subsystem::pneumatics.hook_auto(false);
    
    chassis.turnToHeading(155, 2000);
    chassis.moveToPoint(23, -18, 2000,{false},false);
    subsystem::pneumatics.hook_auto(true);
    pros::delay(400);

    chassis.turnToPoint(40, 0, 1000);

    subsystem::pneumatics.intake_auto(true);
    pros::delay(200);
    chassis.moveToPoint(40, 0, 3000,{.forwards=true});
    pros::delay(200);
    subsystem::pneumatics.intake_auto(false);
    chassis.moveToPoint(36, -4, 3000,{.forwards=false});
    pros::delay(400);

    
    // pros::delay(1200);
    // chassis.moveToPoint(48, -0, 2000,{.forwards=true,.maxSpeed=60});
    // pros::delay(800);
    // chassis.moveToPoint(53, 7, 2000,{.forwards=true,.maxSpeed=60});
    // pros::delay(1500);
    // chassis.moveToPose(48,-18,270,1000,{.earlyExitRange=3},false);
    
    // chassis.moveToPoint(4, -20, 25000,{.forwards=true,.maxSpeed=80});
    

    


}