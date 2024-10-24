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




    // pros::delay(200000);

    int goalx,goaly,startx,starty;
    startx=-58;
    starty=47;

    //-----------------------------------------
    chassis.setPose(startx, starty, 270);//-53, 24, 270
    chassis.follow(redleft1v3_txt, 12, 4000,false,false);
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    pros::delay(500);
    //take first yellow
    chassis.turnToHeading(45,1000);
    pros::delay(1000);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(23, 0, 1000, {true}, false);
    //take first red
    chassis.setPose(0,0,50);
    pros::delay(1000);
    chassis.turnToHeading(20,700);
    pros::delay(1000);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(7, 0, 700, {true}, false);
    //take second red
    pros::delay(1500);
    chassis.moveToPoint(-10, 0, 1000, {false}, false);
    //back off
    pros::delay(500);
    chassis.setPose(0,0,0);
    chassis.turnToHeading(-45,500);
    pros::delay(500);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(15, 0, 1000, {true}, false);
    //take third red
    pros::delay(500);
    chassis.moveToPoint(-15, 0, 2000, {false}, false);
    subsystem::pneumatics.hook_auto(false);
    // subsystem::intake.stop();





    //-----------------------------------------old
    //-----------------------------------------first ring
    // pros::delay(500);
    // chassis.turnToPoint(-23, 47, 3000);
    
    // chassis.moveToPoint(-23,48,2000,{true},true);
    // pros::delay(1500);
    // chassis.turnToHeading(90,500); 
    // pros::delay(2000);
    // chassis.moveToPose(-1,40,100,1000,{true},true);
    // pros::delay(1500);
    // chassis.setPose(0,0,90);
    // chassis.moveToPoint(-20, 0, 1000, {false}, true);
    // //退出來
    // chassis.turnToHeading(65,500);
    // pros::delay(500);
    // chassis.setPose(0,0,90);
    // chassis.moveToPoint(20, 0, 1000, {true}, true);
    // pros::delay(500);
    // chassis.moveToPoint(0, 0, 1000, {false}, false);
    // pros::delay(500);
    // chassis.setPose(0,0,90);
    // pros::delay(500);
    // //3 rings and exit
    // //-----------------------------------------third ring and exit
    // chassis.turnToHeading(180,500);
    // pros::delay(500);
    // chassis.setPose(0,0,180);
    // chassis.moveToPoint(0, -140, 1000, {true}, false);
    // pros::delay(1000);
    // subsystem::pneumatics.hook_auto(false);
    // subsystem::intake.stop();




    

}