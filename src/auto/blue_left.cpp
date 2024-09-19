#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "pros/rtos.hpp"

//關掉自動時執行的task
extern bool off;

ASSET(t1_txt);
void Blue::left() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });



    subsystem::intake.auto_spin(Intake::mode::INTAKE, false, 600);
    pros::delay(1000);
    subsystem::intake.auto_spin(Intake::mode::STOP);
    subsystem::intake.auto_spin(Intake::mode::OUTTAKE, false, 600);
    pros::delay(1000);
    subsystem::intake.auto_spin(Intake::mode::STOP);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);
    pros::delay(5000);
    subsystem::intake.auto_spin(Intake::mode::STOP);
    pros::delay(10);

    // subsystem::arm.pid_arm(Arm::position::UP, 15, 5, 350);
    // printf("done");
    // controller.rumble("..");
    // pros::delay(5000);
    // subsystem::arm.pid_arm(Arm::position::MID, 15, 5, 350);
    controller.rumble(".");
    // chassis.setPose(-48, -60, 0);
    // chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    // chassis.follow(t1_txt, 15, 100000);
    // chassis.waitUntilDone();
    // chassis.moveToPose(60, 0, 90,10000,{.maxSpeed = 87});


}