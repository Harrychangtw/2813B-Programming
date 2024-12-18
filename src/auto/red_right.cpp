//no tracking wheel          
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
void Red::right() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });
    chassis.setPose(-58.0, -9, 270.0);
    chassis.turnToPoint(-68.0, 0,1000);
    pros::delay(200);
    subsystem::arm.pid_arm(Arm::position::MID, 200, 1, 100);

    
    chassis.moveToPoint(-47.0, -20,1500,{.forwards=false,.maxSpeed=100},true);
    
    subsystem::pneumatics.intake_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);

    chassis.waitUntilDone();
    chassis.turnToPoint(-44.0, 0,700);
    chassis.moveToPoint(-44.0, 0,1500,{.forwards=true,.maxSpeed=70},true);
    subsystem::arm.pid_arm(Arm::position::DOWN, 200, 1, 50);
    chassis.waitUntilDone();


    subsystem::pneumatics.intake_auto(false);
    chassis.moveToPoint(-44, -6,3200,{.forwards=false,.maxSpeed=100},false);
    subsystem::intake.auto_spin(Intake::mode::SPINFOR, true,600,360,1);
    pros::delay(500);
    chassis.turnToHeading(300,600);

    chassis.moveToPoint(-23.5, -24.5,2200,{.forwards=false,.maxSpeed=70},false);
    subsystem::pneumatics.hook_auto(true);
    pros::delay(300);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,1);

    pros::delay(900);
    chassis.turnToHeading(-150.0,600);
    subsystem::pneumatics.hook_auto(false);
    pros::delay(200);
    chassis.moveToPoint(-24.0, -33,2200,{.forwards=true,.maxSpeed=100},false);

    chassis.turnToHeading(-60.0,1200);

    chassis.moveToPoint(-13, -44,800,{.forwards=false,.maxSpeed=100},false);
    chassis.moveToPoint(-5.4, -49.3,3200,{.forwards=false,.maxSpeed=50},false);
    
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);

    pros::delay(200);

    chassis.swingToHeading(150, DriveSide::LEFT,2200);

    pros::delay(200);

    chassis.swingToPoint(-13.0, 0, DriveSide::RIGHT, 700);
    chassis.moveToPoint(-12.0, -10,2200,{.forwards=true,.maxSpeed=100},false);


}