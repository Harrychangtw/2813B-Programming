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

    pros::delay(500);
    chassis.turnToHeading(150,600);
    subsystem::pneumatics.hook_auto(false);
    chassis.moveToPoint(24,-31,2200,{.forwards=true,.maxSpeed=100},false);

    chassis.turnToHeading(60,1200);

    chassis.moveToPoint(11,-36,900,{.forwards=false,.maxSpeed=100},false);
    chassis.moveToPoint(6,-41.3,1200,{.forwards=false,.maxSpeed=50},false);
    
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);

    pros::delay(200);

    chassis.swingToPoint(20,-47, DriveSide::RIGHT, 2000);

    pros::delay(200);

    chassis.swingToPoint(15,0, DriveSide::LEFT, 700);
    chassis.moveToPoint(15,-5,2200,{.forwards=true,.maxSpeed=100},false);


}