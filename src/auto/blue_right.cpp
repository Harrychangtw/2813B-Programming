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




    // pros::delay(200000);

    int goalx,goaly,startx,starty;
    startx=58;
    starty=47;

    //-----------------------------------------
    chassis.setPose(startx, starty, 90);//-53, 24, 270
    chassis.follow(blueright1v1_txt, 12, 4000,false,false);
    subsystem::pneumatics.hook_auto(true);
    



    // -----------------------------------------first ring
    pros::delay(500);
    chassis.turnToPoint(23, 47, 3000);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    chassis.moveToPoint(23,48,2000,{true},true);
    // -----------------------------------------
    // subsystem::pneumatics.hook_auto(false);
    pros::delay(3000);
    subsystem::pneumatics.hook_auto(false);
    subsystem::intake.stop();

    
    // chassis.moveToPoint(4, 43, 2000,{true},true);


    // chassis.waitUntilDone();
    // pros::delay(500);
    // //-----------------------------------------
    // chassis.moveToPose(4,40,270,2000,{true},false);
    // pros::delay(3000);
    // subsystem::intake.stop();

    // chassis.follow(blueright3v1_txt, 12, 4000,false,false);
    
    //-----------------------------------------

    /*
    //-----------------------------------------third ring
    chassis.turnToPoint(23, 48, 3000);
    chassis.moveToPoint(23,48,2000,{true},false);
    //-----------------------------------------

    //-----------------------------------------AWP
    pros::delay(1000);
    chassis.moveToPoint(23,1,3000,{true},false);
    //-----------------------------------------
    */

}