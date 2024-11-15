#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
#include <future>

//關掉自動時執行的task
extern bool off;
ASSET(blueright1v1_txt);
ASSET(blueright2v1_txt);
ASSET(blueright3v1_txt);
void Blue::right() {
    // intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });

    chassis.setPose(58, 11, 90);
    chassis.swingToPoint(68, 0,DriveSide::LEFT,1000,{},true);
    pros::delay(200);
    subsystem::arm.pid_arm(Arm::position::MID, 50, 3, 150);
    
    chassis.moveToPoint(60,7,1000,{true},false);
    subsystem::arm.pid_arm(Arm::position::MID_IN, 100, 3, 50);
    
    chassis.moveToPoint(17,27,1200,{.forwards=false,.maxSpeed=100},false);
    subsystem::pneumatics.hook_auto(true);
    pros::delay(300);
        subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);





    chassis.moveToPoint(23.5,50,1200,{.forwards=true,.maxSpeed=100},true);

    subsystem::arm.pid_arm(Arm::position::DOWN, 50, 3, 150);
    chassis.waitUntilDone();
    pros::delay(300);

    chassis.turnToPoint(3.5, 43.5, 1200);

    chassis.moveToPose(4,43.5,270,1500,{.forwards=true,.maxSpeed=90},false);

    pros::delay(500);

    chassis.moveToPose(30,49,270,1000,{.forwards=false,.maxSpeed=90,.earlyExitRange=5},false);
    

    
    chassis.moveToPoint(6,50,1500,{.forwards=true,.maxSpeed=90},false);

    pros::delay(900);
    

    chassis.moveToPoint(23,7,2200,{.forwards=true,.maxSpeed=100},false);





    // chassis.moveToPose(23,47,290,1000,{.forwards=true,.earlyExitRange=5});
    // chassis.turnToPoint(3, 43, 1200);
    // chassis.moveToPoint(8, 41, 1200, {true}, true);
    
    // subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    // subsystem::arm.pid_arm(Arm::position::DOWN, 100, 3, 50);
    // chassis.waitUntilDone();
    // pros::delay(300);


    // chassis.moveToPose(9,41,325,1000,{.forwards=false,.maxSpeed=60,.earlyExitRange=3});

    // chassis.moveToPoint(4, 50, 1200, {true}, false);

    // chassis.turnToPoint(0.3, 51, 1200);




















    
    // pros::delay(500);
    // chassis.turnToPoint(23.5,47,1000);
    // chassis.moveToPoint(23,47,1500,{true},true);
    /*
    //-----------------------------------------
    int goalx,goaly,startx,starty;
    startx=58;
    starty=47;
    
    chassis.setPose(startx, starty, 90);//53, 24, 270
    chassis.follow(blueright1v1_txt, 12, 4000,false,false);
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    //take first yellow
    chassis.turnToHeading(315,1000);
    pros::delay(1000);
    chassis.setPose(0,0,270);
    chassis.moveToPoint(-23, 0, 1000, {true}, false);
    //take first blue
    chassis.setPose(0,0,310);
    pros::delay(1000);
    chassis.turnToHeading(340,700);

    //haven't tried 
    pros::delay(1000);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(7, 0, 700, {true}, false);
    //take second blue
    pros::delay(1500);
    chassis.moveToPoint(-10, 0, 1000, {false}, false);
    //back off
    pros::delay(500);
    chassis.setPose(0,0,0);
    chassis.turnToHeading(45,500);
    pros::delay(500);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(15, 0, 1000, {true}, false);
    // //take third blue
    pros::delay(500);
    chassis.moveToPoint(-17, 0, 2000, {false}, false);
    subsystem::pneumatics.hook_auto(false);

    */

}