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
ASSET(blueright1v3_txt);
void Blue::right() {
    // intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });

    int goalx,goaly,startx,starty;
    startx=58;
    starty=47;
    //-----------------------------------------
    chassis.setPose(startx, starty, 90);//53, 24, 270
    chassis.follow(blueright1v3_txt, 12, 4000,false,false);
    subsystem::pneumatics.hook_auto(true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    pros::delay(500);
    //take first yellow
    chassis.turnToHeading(315,1000);
    pros::delay(1000);
<<<<<<< Updated upstream
    chassis.setPose(0,0,270);
    chassis.moveToPoint(-23, 0, 1000, {true}, false);
    pros::delay(1000);
    //take first blue
    chassis.setPose(0,0,310);
    pros::delay(1000);
=======
    chassis.setPose(0,0,90);
    chassis.moveToPoint(23, 0, 1000, {true}, false);
    //take first red
    chassis.setPose(0,0,310);
    pros::delay(1000);
>>>>>>> Stashed changes
    chassis.turnToHeading(340,700);
    pros::delay(1000);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(9, 0, 700, {true}, false);
    //take second blue
    pros::delay(2000);
    chassis.moveToPoint(-10, 0, 1000, {false}, false);
    //back off
    pros::delay(500);
    chassis.setPose(0,0,0);
<<<<<<< Updated upstream
    chassis.turnToHeading(50,500);
=======
    chassis.turnToHeading(45,500);
>>>>>>> Stashed changes
    pros::delay(500);
    chassis.setPose(0,0,90);
    chassis.moveToPoint(15, 0, 1000, {true}, false);
    // //take third blue
    pros::delay(500);
<<<<<<< Updated upstream
    chassis.moveToPoint(-17, 0, 2000, {false}, false);
    subsystem::pneumatics.hook_auto(false);
=======
    chassis.moveToPoint(-15, 0, 2000, {false}, false);
    subsystem::pneumatics.hook_auto(false);
    // subsystem::intake.stop();
>>>>>>> Stashed changes

}