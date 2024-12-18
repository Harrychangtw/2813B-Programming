#include "UUUU_nova/subsystem.hpp"
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
    chassis.setPose(-61,0,90);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,720,1);
    pros::delay(400);

    //get stack 1
    chassis.moveToPoint(-50,0,1000,{.forwards=true,.maxSpeed=100},false);
    chassis.turnToHeading(0,1000);
    chassis.moveToPoint(-47,-23,10300,{.forwards=false,.maxSpeed=100},false);
    subsystem::pneumatics.hook_auto(true);

    //get ring 1->stack1
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
    chassis.turnToPoint(-27, -24.5,1200);
    chassis.moveToPoint(-27, -24.5, 1200,{.forwards=true,.maxSpeed=100},false);

    //get ring 2->stack1
    chassis.turnToPoint(23, -47,1200);
    chassis.moveToPoint(23, -47, 2200,{.forwards=true,.maxSpeed=100},false);


    chassis.turnToPoint(0, -54,800);
    chassis.moveToPoint(14, -54, 3200,{.forwards=true,.maxSpeed=60},true);
    subsystem::arm.pid_arm(Arm::position::INTAKE);
    chassis.waitUntilDone();
    chassis.swingToHeading(180,DriveSide::LEFT,2800,{.maxSpeed=80},false);
    pros::delay(800);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,100,-30,1);
    subsystem::arm.pid_arm(Arm::position::MID_IN,50,3,150);
    subsystem::arm.pid_arm(Arm::position::DOWN, 50, 3, 150);

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