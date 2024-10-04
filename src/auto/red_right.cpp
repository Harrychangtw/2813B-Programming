#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"

//關掉自動時執行的task
extern bool off;
ASSET(blueright1v1_txt);
void Red::right() {
    // intake自動時的動作程式
    // pros::Task intake_run([&]() {
    //     while(off) {
    //         subsystem::intake.auto_run();
    //         pros::delay(10);
    //     }
    // });

    int goalx,goaly,startx,starty;
    startx=-60;
    starty=48;

    //-----------------------------------------
    chassis.setPose(startx, starty, 270);//-53, 24, 270
    chassis.follow(blueright1v1_txt, 12, 10000,false,false);
    subsystem::pneumatics.hook_auto(true);
    pros::delay(500);
    chassis.turnToPoint(53,24, 1000);
    chassis.moveToPoint(53, 24, 1000,{true},true);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    chassis.waitUntilDone();

    // chassis.follow(pid_txt, 15, 5000);
    // chassis.moveToPoint(52.7, 0, 500);
    // chassis.follow(pid_txt, 15, 5000,true,true);
    // subsystem::intake.auto_spin(Intake::mode::INTAKE, true,600,0,1);
    // subsystem::pneumatics.hand_auto(true);
    // pros::delay(100);
    // chassis.moveToPoint(0,5, 500 );
    // subsystem::intake.auto_spin(Intake::mode::OUTTAKE, false);
    // chassis.waitUntilDone();
    // chassis.turnToHeading(40, 1000, {.maxSpeed = 100});
    // chassis.waitUntilDone();
    // subsystem::intake.auto_spin(Intake::mode::INTAKE, true);
    // chassis.swingToHeading(105, DriveSide::RIGHT, 1000, {.maxSpeed = 100});
    // chassis.waitUntilDone();
    // chassis.turnToHeading(90, 1000, {.maxSpeed = 127});
    // chassis.waitUntilDone();
    // chassis.moveToPoint(48, 16, 3000, {.maxSpeed = 60});
    // chassis.waitUntilDone();
    chassis.setPose(-66.68,-55.5,65.8);


    

    subsystem::intake.auto_spin(Intake::mode::STOP);

    // subsystem::pneumatics.intake_auto(true);
    // // subsystem::intake.intake();//西兩顆
    // subsystem::intake.auto_spin(1, true);
    // pros::delay(1000);
    // chassis.moveToPoint(0,6, 500 );
    // subsystem::pneumatics.intake_auto(false);
    // chassis.moveToPoint(0,0, 1000 );
    // pros::delay(500);
    // subsystem::pneumatics.intake_auto(true);
    // pros::delay(400);
    // chassis.moveToPoint(0,6, 1000 );
    // subsystem::pneumatics.intake_auto(false);
    // pros::delay(150);
    // chassis.moveToPoint(0,1, 500 );
    // pros::delay(150);
    // chassis.moveToPoint(0,6, 500 );
    // chassis.moveToPoint(0,1, 500 );
    // pros::delay(150);
    // chassis.moveToPoint(0,6, 500 );

    // subsystem::intake.auto_spin(0, false);
    



    

    // subsystem::arm.pid_arm(Arm::position::UP, 15, 5, 350);
    printf("done");
    // controller.rumble("..");
    // pros::delay(5000);
    // subsystem::arm.pid_arm(Arm::position::MID, 15, 5, 350);
    // controller.rumble(".");
    // // chassis.setPose(-48, -60, 0);
    // // chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    // // chassis.follow(t1_txt, 15, 100000);
    // // chassis.waitUntilDone();
    // // chassis.moveToPose(60, 0, 90,10000,{.maxSpeed = 87});
}