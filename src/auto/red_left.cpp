#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
#include <future>

//關掉自動時執行的task
extern bool off;
ASSET(redleft1v3_txt);
ASSET(redleft2v2_txt);
ASSET(redleft4v1_txt);

void Red::left() {
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,6,500,{true},true);
    //wall stake
    subsystem::arm.pid_arm(Arm::position::UP, 50, 5, 100);
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,-17,700,{false},true);
    subsystem::arm.pid_arm(Arm::position::DOWN,50,5,150);

    chassis.setPose(-46,22,225);
    chassis.moveToPose(-25,23,270,1000,{.forwards=false},false);
    subsystem::pneumatics.hook_auto(true);
    //mobile goal
    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    chassis.moveToPose(-47,0,180,1000,{.forwards=true},false);
    subsystem::pneumatics.intake_auto(false);
    //first red
    chassis.moveToPose(-20,23,270,2000,{.forwards=false},false);
    chassis.turnToHeading(0,1000);
    pros::delay(50);
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,20,1000,{.forwards=true},false);
    pros::delay(50);
    chassis.setPose(-23,47,0);
    pros::delay(50);
    //take first red

    chassis.turnToHeading(90,500);
    chassis.moveToPose(-6,50,120,3000,{.forwards=true},false);
    pros::delay(50);
    //take second red
    chassis.moveToPoint(-23,47,2500,{false},false);
    chassis.moveToPose(-6,40,90,2500,{.forwards=true},false);
    //take third red
    chassis.moveToPoint(-23,47,2500,{false},false);
    chassis.moveToPose(-3,20,90,3000,{true},false);


    
    
}