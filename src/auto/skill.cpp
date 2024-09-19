#include "auto/auto.hpp"
#include "pros/rtos.hpp"

//關掉自動時執行的task
extern bool off;

ASSET(t1_txt);
void Skill::skill() {
    //intake自動時的動作程式
    // pros::Task intake_run([&]() {
    //     while(off) {
    //         subsystem::intake.auto_run();
    //     }
    // });


    // subsystem::arm.pid_arm(Arm::position::UP, 50, 5, 150);
    // subsystem::pneumatics.intake_auto(true);
    // pros::delay(50000);



    // subsystem::arm.pid_arm(Arm::position::UP, 15, 5, 350);
    // printf("done");
    // controller.rumble("..");
    // pros::delay(5000);
    // subsystem::arm.pid_arm(Arm::position::MID, 15, 5, 350);
    // controller.rumble(".");

    chassis.setPose(-56, 15.5, 180);
    subsystem::pneumatics.intake_auto(true);
    subsystem::arm.pid_arm(Arm::position::UP, 50, 3, 150);
    chassis.moveToPose(-55,7, 150,1500);

    chassis.waitUntilDone();
    pros::delay(50000);

    
    subsystem::pneumatics.intake_auto(false);
    // subsystem::intake.spin_for(600, 500,false);//掛起始紅色
    // subsystem::intake.intake();//西第二顆
    chassis.moveToPoint(-48,1, 1500 );
    chassis.turnToHeading(90, 400);
    chassis.moveToPoint(-63,0, 1500,{.forwards = false});
    chassis.waitUntilDone();
    // subsystem::intake.spin_for(600, 1500,false);//掛起始紅色





















    // chassis.setPose(-48, -60, 0);
    // chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    // chassis.follow(t1_txt, 15, 100000);
    // chassis.waitUntilDone();
    // chassis.moveToPose(60, 0, 90,10000,{.maxSpeed = 87});
}