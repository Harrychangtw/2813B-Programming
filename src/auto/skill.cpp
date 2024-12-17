#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/extra/layouts/flex/lv_flex.h"
#include "pros/rtos.hpp"
#include "setup.hpp"

//關掉自動時執行的task
extern bool off;

ASSET(t1_txt);
void Skill::skill() {
    
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });

    //front:intake
    //back:hook
    chassis.setPose(-53,0,90);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,720,1);
    pros::delay(400);

    //get stack 1
    chassis.swingToHeading(357, DriveSide::LEFT, 1200);
    chassis.moveToPoint(-47,-17,1200,{false},false);
    subsystem::pneumatics.hook_auto(true);


    //ring 1->stack1
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
    chassis.turnToPoint(-23.5, -23.5, 500);
    chassis.moveToPoint(-23.5, -23.5, 1200,{true},false);

    //ring 2->stack1
    chassis.turnToPoint(23.5, -45.5, 500);
    chassis.moveToPoint(23.5, -45.5, 3200,{true},false);
    pros::delay(200);
    
    //ring below wall stack->arm
    chassis.turnToHeading(270,700);
    chassis.moveToPoint(12, -56.4, 1400,{true},true);
    subsystem::arm.pid_arm(Arm::position::INTAKE);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
    chassis.waitUntilDone();
    
    //ring on wall stack
    chassis.swingToHeading(180, DriveSide::LEFT, 1800);
    pros::delay(1200);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,100,-30,1);    
    subsystem::arm.pid_arm(Arm::position::MID_IN, 200, 30, 150);
    pros::delay(200);
        subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,180,1);    
    //bottom left 4 rings
    chassis.moveToPoint(3, -47, 1200,{false},true);
    subsystem::arm.pid_arm(Arm::position::DOWN, 200, 1, 100);

    chassis.waitUntilDone();
    chassis.turnToHeading(270,1200);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);

    chassis.moveToPoint(-10,-48, 500,{.maxSpeed=100});
    chassis.moveToPoint(-47,-50, 3200,{.maxSpeed=50});

    



    chassis.swingToHeading(180, DriveSide::RIGHT, 1200);
    chassis.moveToPoint(-40,-58, 3200,{.maxSpeed=60});

    chassis.swingToHeading(70, DriveSide::RIGHT, 1200);

    // subsystem::arm.pid_arm(Arm::position::MID, 50, 5, 150);
    // chassis.moveToPoint(-60.5,0,1000,{true},false);
    // subsystem::arm.pid_arm(Arm::position::MID_IN, 100, 3, 50);

    // chassis.moveToPoint(-47.5,0,1000,{false},true);
    
    // subsystem::arm.pid_arm(Arm::position::DOWN, 50, 3, 150);
    // chassis.waitUntilDone();
    // //get stack 1
    // chassis.turnToHeading(0,1000);

    
    // chassis.moveToPoint(-47.5,-23.25, 1000,{false},false);
    // subsystem::pneumatics.hook_auto(true);

    // //get ring 1->stack1
    // chassis.moveToPoint(-23.25,-23.25, 1000,{true},true);
    // subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
    // chassis.waitUntilDone();
    // //get ring 2->stack1
    // chassis.moveToPoint(23.25,-47.5, 3000,{true},false);
    // pros::delay(200);

    // chassis.moveToPoint(0,-47.5, 3000,{false},false);
    
    // //get ring 3->arm
    // chassis.turnToPoint(0,-59.75, 1000);    
    // chassis.moveToPoint(0,-59.75, 1000,{true},false);
    // subsystem::intake.auto_spin(Intake::mode::INTAKEtoARM,600);

    // //bottom wall stack
    // chassis.moveToPoint(0,-50.75, 1000,{false},false);
    // subsystem::arm.pid_arm(Arm::position::UP, 50, 3, 150);

    // chassis.moveToPoint(0,-60.5, 1000,{false},false);





    


















}