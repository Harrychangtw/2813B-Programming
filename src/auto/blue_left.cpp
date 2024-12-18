//no tracking wheel          

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
    chassis.setPose(58, -13, 90);
    chassis.turnToPoint(68, 0,1000);
    pros::delay(200);
    subsystem::arm.pid_arm(Arm::position::MID, 200, 1, 100);

    
    chassis.moveToPoint(47,-20,1200,{.forwards=false,.maxSpeed=100},true);
    
    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);

    chassis.waitUntilDone();
    chassis.turnToPoint(44,0,700);
    chassis.moveToPoint(44,0,1500,{.forwards=true,.maxSpeed=70},true);
    subsystem::arm.pid_arm(Arm::position::DOWN, 200, 1, 50);
    chassis.waitUntilDone();


    subsystem::pneumatics.intake_auto(false);
    chassis.moveToPoint(44,-6,2200,{.forwards=false,.maxSpeed=100},false);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,360,1);
    pros::delay(500);
   chassis.turnToHeading(60,600);

    chassis.moveToPoint(23.5,-21.5,2200,{.forwards=false,.maxSpeed=70},false);
    subsystem::pneumatics.hook_auto(true);
    pros::delay(300);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,1);

    pros::delay(800);

    chassis.turnToPoint(23.5, -47.5,2000);
    chassis.moveToPoint(23.5,-47.5,2000,{.forwards=true,.maxSpeed=100},false);

    pros::delay(300);

    chassis.swingToPoint(12.5, -12.5, DriveSide::LEFT, 1200);
    chassis.moveToPoint(12.5, -12.5,2000);

}