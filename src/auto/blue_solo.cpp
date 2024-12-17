    #include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"

//關掉自動時執行的task
extern bool off;

void Blue::solo() {
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
    subsystem::arm.pid_arm(Arm::position::MID, 200, 1, 70);
    subsystem::arm.pid_arm(Arm::position::DOWN, 200, 1, 100);
    
    chassis.moveToPoint(30,-20,900,{.forwards=false,.maxSpeed=100},false);
    chassis.moveToPoint(23.5,-23.5,400,{.forwards=false,.maxSpeed=50},false);

    subsystem::pneumatics.hook_auto(true);
    
    
    chassis.turnToPoint(45, -4, 400);
    chassis.moveToPoint(45, -4, 1600,{},true);
    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 500);
    chassis.waitUntilDone();
    subsystem::pneumatics.intake_auto(false);
    chassis.turnToHeading(120, 600);
    chassis.swingToHeading(260,DriveSide::LEFT, 800);

    pros::delay(1250);
    subsystem::pneumatics.hook_auto(false);
    chassis.turnToHeading(120, 500);
    chassis.moveToPoint(30, 21.5, 1200,{false},true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 500);
    chassis.waitUntilDone();
    subsystem::pneumatics.hook_auto(true);
    // pros::delay(200);
    chassis.turnToPoint(35, 47.5, 600);
    chassis.moveToPoint(34, 43, 1200,{},false);
    pros::delay(200);
    chassis.turnToPoint(3, 47.5,700);
    
    chassis.moveToPoint(20, 46.5, 1200,{},false);
    chassis.swingToHeading(270, DriveSide::LEFT,500);
    
    chassis.moveToPoint(40, 44.5, 600,{false},false);
    
    chassis.moveToPoint(20, 41.5, 1200,{},false);
    chassis.swingToHeading(270, DriveSide::RIGHT,500);

    chassis.swingToHeading(220, DriveSide::RIGHT,500);
    chassis.moveToPoint(13, 23.5, 600,{true},false);

    
    // chassis.moveToPoint(7, 48, 1200,{},false);
    


}