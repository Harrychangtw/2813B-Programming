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
    chassis.moveToPoint(0,-17,700,{.forwards=false,.minSpeed=70},true);
    subsystem::arm.pid_arm(Arm::position::DOWN,50,5,150);
    chassis.setPose(-41,20,225);
    chassis.moveToPose(-20,20,270,1500,{.forwards=false,.minSpeed=70},false);
    subsystem::pneumatics.hook_auto(true);
    chassis.setPose(-30,22,270);
    //mobile goal
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    subsystem::pneumatics.intake_auto(true);
    chassis.moveToPose(-47,0,180,3000,{.forwards=true,.minSpeed=70},false);
    subsystem::pneumatics.intake_auto(false);
    pros::delay(200);
    //first red
    chassis.moveToPose(-19,20,270,3000,{.forwards=false,.maxSpeed=60},false);
    chassis.turnToHeading(0,500);
    pros::delay(500);
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,20,1000,{.forwards=true},false);
    pros::delay(50);
    chassis.setPose(-23,47,0);
    pros::delay(50);
    //take first red
    chassis.turnToHeading(100,700);
    pros::delay(700);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(15,0,1000,{.forwards=true,.maxSpeed=60},false);
    pros::delay(100);
    chassis.moveToPoint(0,0,1000,{.forwards=false},false);
    //second red
    chassis.setPose(0,0,20);
    chassis.turnToHeading(0,500);
    pros::delay(500);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(15,0,1000,{.forwards=true,.maxSpeed=60},false);
    pros::delay(100);
    chassis.moveToPoint(0,0,1000,{.forwards=false},false);
    //third red
    chassis.turnToHeading(135,600);
    chassis.moveToPoint(0,-27,3000);

}