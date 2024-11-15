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
    /*
    chassis.setPose(50,-63,90);
    chassis.follow(bl1_v2_txt, 15, 2000,false,false);
    subsystem::pneumatics.hook_auto(true);


    
    
    chassis.swingToPoint(24, -43,DriveSide::LEFT,4000,{},true);
    pros::delay(200);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,800,0);
    pros::delay(400);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,0,1);
    chassis.moveToPoint(26.5, -42, 2000);
    
    subsystem::pneumatics.hook_auto(false);
    pros::delay(600);
    subsystem::intake.auto_spin(Intake::mode::STOP, false);
    
    chassis.moveToPoint(24, -26, 2000,{false},false);
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
   
    //strat: go to the middle
    chassis.turnToPoint(48, 0, 1000);
    chassis.moveToPoint(38, -10, 2000,{.forwards=true,.maxSpeed=100},true);
    pros::delay(1200);
    chassis.moveToPoint(48, -0, 2000,{.forwards=true,.maxSpeed=60});
    pros::delay(800);
    chassis.moveToPoint(53, 7, 2000,{.forwards=true,.maxSpeed=60});
    pros::delay(1500);
    chassis.moveToPose(48,-18,270,1000,{.earlyExitRange=3},false);
    
    chassis.moveToPoint(4, -20, 25000,{.forwards=true,.maxSpeed=80});
    
    
    //strat:go straigjt touch the latter

    // chassis.moveToPoint(24, -3, 2000,{false},false);
    
    */
    
    chassis.setPose(58, -11, 90);
    chassis.swingToPoint(68, 0,DriveSide::RIGHT,1000,{},true);
    pros::delay(200);
    subsystem::arm.pid_arm(Arm::position::MID, 100, 2, 150);
    
    chassis.moveToPoint(60,-7,800,{true},false);
    subsystem::arm.pid_arm(Arm::position::MID_IN, 200, 2, 50);
    
    chassis.moveToPoint(47,-15,1200,{.forwards=false,.maxSpeed=100},false);
    

    chassis.turnToPoint(47, 0, 700);

    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,0,1);
    chassis.moveToPoint(47,0,1200,{.forwards=true,.maxSpeed=100},false);
    pros::delay(300);

    chassis.moveToPoint(47,20,1200,{.forwards=true,.maxSpeed=60},false);

    subsystem::intake.auto_spin(Intake::mode::STOP, false);

    chassis.moveToPose(47, -3, 0,1200,{.forwards=false,.maxSpeed=100,.minSpeed=50,.earlyExitRange=5}, false);
    
    chassis.moveToPoint(27,-21,1800,{.forwards=false,.maxSpeed=100},true);
    subsystem::arm.pid_arm(Arm::position::DOWN, 50, 2, 150);
    chassis.waitUntilDone();
    
    
    subsystem::pneumatics.hook_auto(true);
    pros::delay(200);

    subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,2400,0);

    pros::delay(400);
    chassis.turnToHeading(180,400,{},true);
    pros::delay(400);

    subsystem::pneumatics.hook_auto(false);
    chassis.waitUntilDone();

    chassis.turnToPoint(45,-5,1200);    
    chassis.moveToPoint(8.5, -38.5,3200,{.forwards=false,.maxSpeed=50},false);
    chassis.swingToHeading(65,DriveSide::LEFT,2400,{.maxSpeed=40});

    pros::delay(1200);
    subsystem::pneumatics.hook_auto(true);
    
    
    // pros::delay(100);
    // chassis.turnToPoint(23.5, -47, 1200);

    // subsystem::intake.auto_spin(Intake::mode::INTAKE, true,500,2400,0);
    // chassis.moveToPoint(23.5,-47,1200,{.forwards=true,.maxSpeed=100},false);
    // pros::delay(300);

    // chassis.moveToPoint(26.5,-6,2200,{.forwards=false,.maxSpeed=100},false);

    


}