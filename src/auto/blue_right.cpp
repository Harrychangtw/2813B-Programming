#include "auto/auto.hpp"
#include "setup.hpp"


//關掉自動時執行的task
extern bool off;

ASSET(BR1_txt);
void Blue::right() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });
    chassis.setPose(52, 40, 55);//-53, 24, 270
    chassis.moveToPoint(26, 21, 1000,{false,75},false);
    subsystem::pneumatics.hook_auto(true);

    pros::delay(200);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);//西兩顆
    chassis.turnToHeading(295, 1000);//轉向8顆
    chassis.follow(BR1_txt, 12, 5000,true,false);
    chassis.turnToHeading(110, 1000);//轉向8顆

    // // chassis.follow(RL11_txt, 35, 5000,true,false);
    // chassis.moveToPoint(12, 38, 1000,{true});//吸1
    // // chassis.turnToHeading(336, 1000);
    // chassis.swingToHeading(336, DriveSide::LEFT,1000);

    // // chassis.moveToPose(-6, 49.5,0,3000,{.forwards=true,.minSpeed=30, .earlyExitRange=0.5},false);//吸2
    // // chassis.moveToPose(-26, 21,0,3000,{.forwards=false,.minSpeed=20, .earlyExitRange=0.5},false);//吸2

    // chassis.moveToPoint(8, 49.5,3000,{true},false);//吸2

    // subsystem::arm.pid_arm(Arm::position::UP, 15, 5, 350);
    // printf("done");
    // controller.rumble("..");
    // pros::delay(5000);
    // subsystem::arm.pid_arm(Arm::position::MID, 15, 5, 350);
    // controller.rumble(".");
    // chassis.setPose(-48, -60, 0);
    // chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    // chassis.follow(t1_txt, 15, 100000);
    // chassis.waitUntilDone();
    // chassis.moveToPose(60, 0, 90,10000,{.maxSpeed = 87});
}