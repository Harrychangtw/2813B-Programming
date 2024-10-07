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
    //-----------------------------------------first ring
    // pros::delay(500);
    chassis.turnToPoint(-23, 47, 3000);
    
    chassis.moveToPoint(-23,48,2000,{true},true);
    chassis.turnToHeading(90,500); 
    pros::delay(2000);
    chassis.moveToPose(-1,40,100,1000,{true},true);
    pros::delay(1500);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(-20, 0, 1000, {false}, true);
    //3 rings and exit
    //退出來
    chassis.turnToHeading(60,500);
    pros::delay(500);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(20, 0, 1000, {true}, true);
    pros::delay(500);
    chassis.moveToPoint(0, 0, 1000, {false}, false);
    pros::delay(500);
    chassis.setPose(0,0,90);
    pros::delay(500);
    // chassis.turnToHeading(180,500);
    // pros::delay(500);
    // chassis.setPose(0,0,180);
    // chassis.moveToPoint(0, -120, 1000, {true}, false);
    // pros::delay(1000);
    subsystem::pneumatics.hook_auto(false);
    subsystem::intake.stop();




    

}