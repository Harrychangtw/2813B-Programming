#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"

//關掉自動時執行的task
extern bool off;


ASSET(rr1_v2_txt);
ASSET(bl1_v2_txt);
void Blue::right() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });
    chassis.setPose(58, 10, 90);
    chassis.turnToPoint(68, 0,1000);
    pros::delay(200);
    subsystem::arm.pid_arm(Arm::position::MID, 200, 1, 70);

    
    //
    
    chassis.moveToPoint(47, 20,1200,{.forwards=false,.maxSpeed=100},true);

    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
    
    chassis.waitUntilDone();
    chassis.turnToPoint(44, 0,700);
    chassis.moveToPoint(44, 0,900,{.forwards=true,.maxSpeed=70},true);
    subsystem::arm.pid_arm(Arm::position::DOWN, 200, 1, 100);
    chassis.waitUntilDone();


    subsystem::pneumatics.intake_auto(false);
    
    chassis.moveToPoint(44, 14,1500,{.forwards=false,.maxSpeed=70},false);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,500,500,1);
    pros::delay(500);
    chassis.turnToHeading(120, 500);
    chassis.moveToPoint(20.5, 26, 1200,{false},true);
    pros::delay(600);
    subsystem::pneumatics.hook_auto(true);
        chassis.waitUntilDone();
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
    
    
    chassis.turnToPoint(23.5, 48.5, 600);
    chassis.moveToPoint(23.5, 47, 1200,{},false);
    pros::delay(200);
    chassis.turnToPoint(3, 53.5,700);
    
    chassis.moveToPoint(7, 52, 1500,{.maxSpeed=100},false);

    chassis.moveToPoint(20, 50.5, 600,{false},false);
    
    chassis.moveToPoint(7, 48.5, 1500,{.maxSpeed=100},false);
    chassis.swingToHeading(-90, DriveSide::RIGHT,500);

    pros::delay(200);

    //touch bar
    chassis.moveToPoint(20, 47.5, 600,{false},false);
    chassis.turnToPoint(15, 0, 700);
    chassis.moveToPoint(15, -25, 2200,{.forwards=true,.maxSpeed=100},false);

}