#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"

//關掉自動時執行的task
extern bool off;

ASSET(RL1_txt);
ASSET(RL2_txt);
ASSET(RL3_txt);
void Red::solo() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });

    
    chassis.setPose(-60, 10, 0);
    chassis.moveToPoint(-60, 4.5, 1000);

    chassis.swingToHeading(90, DriveSide::LEFT, 800, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 80});
    chassis.waitUntilDone();
    // chassis.moveToPoint(-5, 0, 1000);
    subsystem::intake.spin_for(600, 1300);//掛起始紅色
    // chassis.moveToPoint(-55, 0, 1000);
    //chassis.waitUntilDone();
    chassis.turnToHeading(35, 1000);
    //chassis.waitUntilDone();

    // printf("x:%f - y:%f - t:%f\n",chassis.getPose().x,chassis.getPose().y,chassis.getPose().theta);

    subsystem::intake.intake();//西第二顆
    chassis.follow(RL1_txt, 50, 10000);
    //chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
    //chassis.waitUntilDone();
    subsystem::intake.stop();

    // pros::delay(500);
    // subsystem::intake.stop();

    chassis.follow(RL2_txt, 35, 5000, false);
    chassis.moveToPoint(-24, 27.5, 1500, {.forwards = false});
    // //chassis.waitUntilDone();
    // pros::delay(500);
    subsystem::pneumatics.hook_auto(true);
    chassis.turnToHeading(45, 1000);//面向八科
    subsystem::intake.intake();//西兩顆
    chassis.moveToPoint(-11,40, 1500 );
    chassis.moveToPoint(-16,30, 1500 ,{.forwards = false});

    chassis.turnToHeading(25, 1000);
    chassis.moveToPoint(-11,48, 1500 );
    chassis.moveToPoint(-16,40, 1500 ,{.forwards = false});
    chassis.turnToHeading(315, 1000);//面向角落生物

    // Arm::position::DOWN;
    subsystem::arm.pid_arm(Arm::position::UP, 50, 5, 350);
    subsystem::pneumatics.intake_auto(true);

    chassis.moveToPoint(-60,60, 2000 );








    printf("X: %.2f", chassis.getPose().x);
    printf("  Y: %.2f", chassis.getPose().y);
	printf("  Deg; %.2f\n", chassis.getPose().theta);

    // chassis.moveToPoint(-8,50, 1500 );


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
}