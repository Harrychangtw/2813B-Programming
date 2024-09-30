#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"
#include <future>

//關掉自動時執行的task
extern bool off;
ASSET(RL11_txt);
ASSET(RL1_txt);
ASSET(RL2_txt);
ASSET(RL3_txt);
void Red::left() {
    // intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });





    // chassis.setPose(-53, 12, 233);
    // chassis.moveToPoint(-63, 5, 1000,{true,50});
    // subsystem::arm.pid_arm(Arm::position::MID, 50, 5, 350);
    // pros::delay(500);
    // subsystem::arm.pid_arm(Arm::position::MID_IN, 50, 5, 350);
    // chassis.turnToHeading(250, 1000);
    // chassis.moveToPoint(-29, 18, 1000,{false,75});









    // pros::delay(200000);

    int goalx,goaly,startx,starty;
    goalx=-24;
    goaly=24;
    startx=-60;
    starty=50;
    //-----------------------------------------
    chassis.setPose(startx, starty, 270);//-53, 24, 270
    chassis.turnToPoint(startx-goalx+startx, starty-goaly+starty, 1000);//need change
    chassis.moveToPoint(-goalx, goaly, 1000);//need change
    subsystem::pneumatics.hook_auto(true);
    //get first stack--------------------------


    /*
    //-----------------------------------------
    goalx=-3;
    goaly=44;//first ring

    pros::delay(100);
    chassis.turnToPoint(goalx,goaly, 1000);
    chassis.moveToPoint(goalx, goaly, 1000,{true});
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    pros::delay(1000);
    //get first ring--------------------------


    //-----------------------------------------
    goalx=-3;
    goaly=50;//second ring

    pros::delay(100);
    chassis.moveToPoint(goalx, goaly, 1000,{true});
    chassis.turnToPoint(goalx,goaly, 1000);
    chassis.moveToPoint(goalx, goaly, 1000,{true});
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    pros::delay(1000);
    //get second ring--------------------------


    
    //-----------------------------------------
    goalx=-24;
    goaly=48;//third ring

    pros::delay(100);

    chassis.turnToPoint(goalx,goaly, 1000);
    chassis.moveToPoint(goalx, goaly, 1000,{true});
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    pros::delay(200);
    //get third ring--------------------------


    //-----------------------------------------

    chassis.turnToHeading(0,1000);
    chassis.moveToPoint(-24, 3, 1000,{false},true);
    subsystem::intake.auto_spin(Intake::mode::STOP, true, 600);
    //AWP-------------------------------------


    // chassis.follow(RL3_txt, 15, 5000);
    //chassis.waitUntilDone();
    pros::delay(500);
    // chassis.swingToHeading(0, DriveSide::LEFT, 1000);
    // chassis.waitUntilDone();
    // chassis.moveToPoint(-6, 55, 3000);
    // chassis.waitUntilDone();
    // subsystem::intake.stop();



    controller.rumble(".");



    // chassis.setPose(-48, -60, 0);
    // chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    // chassis.follow(t1_txt, 15, 100000);
    // chassis.waitUntilDone();
    // chassis.moveToPose(60, 0, 90,10000,{.maxSpeed = 87});
*/
}