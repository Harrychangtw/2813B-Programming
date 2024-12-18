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
    chassis.setPose(51,-63,90);
    chassis.follow(bl1_v2_txt, 15, 2000,false,false);
    subsystem::pneumatics.hook_auto(true);


    
    subsystem::intake.auto_spin(Intake::mode::INTAKE, false,600,3000,0);
    chassis.swingToPoint(23, -42,DriveSide::LEFT,2200,{},true);

    chassis.waitUntilDone();
    pros::delay(400);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,2400,0);

    chassis.moveToPoint(23, -40, 2000,{true},false);
    pros::delay(200);
    
    chassis.moveToPoint(37, -31, 2000,{true},true);
    pros::delay(500);
    subsystem::pneumatics.hook_auto(false);
    chassis.waitUntilDone();

  
    
    chassis.turnToHeading(130, 600);
    chassis.moveToPoint(23, -18, 2000,{.forwards=false,.maxSpeed=90},true);
    pros::delay(800);
    subsystem::pneumatics.hook_auto(true);
    chassis.waitUntilDone();
    chassis.turnToPoint(38, 0, 1000);


    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,0);

    pros::delay(200);
    chassis.moveToPoint(39.6, 3, 3000,{.forwards=true,.maxSpeed=90});
    pros::delay(400);
    subsystem::pneumatics.intake_auto(false);
    chassis.moveToPoint(36, -15, 3000,{.forwards=false});
 
    chassis.moveToPose(23.5,-23.5,315,2000,{.forwards=false,.earlyExitRange=4},false);

    

     chassis.moveToPoint(10, -10, 3000,{});


}