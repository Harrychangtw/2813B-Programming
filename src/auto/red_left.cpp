#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "setup.hpp"

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


    chassis.setPose(-52, 40, 305);//-53, 24, 270
    chassis.moveToPoint(-26, 21, 1000,{false,65},false);
    // pros::delay(100);
    subsystem::pneumatics.hook_auto(true);
    // chassis.moveToPoint(-27.2, 24, 1000,{false,30},false);
    pros::delay(200);
    subsystem::intake.auto_spin(Intake::mode::INTAKE, true, 600);//西兩顆
    chassis.turnToHeading(55, 1000);//轉向8顆
    // chassis.follow(RL11_txt, 35, 5000,true,false);
    chassis.moveToPoint(-12, 38, 1000,{true});//吸1
    chassis.turnToHeading(24, 1000);
    // chassis.moveToPose(-6, 49.5,0,3000,{.forwards=true,.minSpeed=30, .earlyExitRange=0.5},false);//吸2
    // chassis.moveToPose(-26, 21,0,3000,{.forwards=false,.minSpeed=20, .earlyExitRange=0.5},false);//吸2

    chassis.moveToPoint(-6, 49.5,3000,{true},false);//吸2


    // pros::delay(200000);


    pros::delay(150);
    chassis.moveToPoint(-24, 24,1500,{false},false);
    chassis.turnToHeading(0, 1000);//轉向2顆
    chassis.moveToPoint(-24, 46,1500,{true},false);
    chassis.turnToHeading(225, 1000);//轉向牆邊2顆
    chassis.moveToPoint(-40.8, 8,1500,{true,110},true);
    pros::delay(500);
    subsystem::intake.auto_spin(Intake::mode::INTAKEtoARM_count, true, 600,0,1);//吸一顆到手臂
    subsystem::pneumatics.intake_auto(true);
    chassis.waitUntilDone();
    // subsystem::pneumatics.intake_auto(false);
    // pros::delay(100);
    subsystem::arm.pid_arm(Arm::position::DOWN, 50, 5, 350);
    chassis.moveToPoint(-48, 0,1500,{true,110},true);
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-55, 0,1500,{true},false);
    subsystem::arm.pid_arm(Arm::position::MID, 50, 5, 350);
    chassis.waitUntilDone();
    subsystem::arm.pid_arm(Arm::position::MID_IN, 50, 5, 350);

    pros::delay(5000);



   











    pros::delay(200000);









    // subsystem::intake.auto_spin(Intake::SPINFOR,false,600,1300);
    // subsystem::arm.pid_arm(Arm::position::UP, 50, 5, 350);
   
    // pros::delay(200000);


    chassis.setPose(-60, 10, 0);
    chassis.moveToPoint(-60, 4.5, 1000);

    chassis.swingToHeading(90, DriveSide::LEFT, 800, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 80});
    chassis.waitUntilDone();
    // chassis.moveToPoint(-5, 0, 1000);
    subsystem::intake.auto_spin(Intake::SPINFOR,false,600,1300);
    subsystem::intake.waitIntakeDone();
    // subsystem::intake.spin_for(600, 1300);//掛起始紅色
    // chassis.moveToPoint(-55, 0, 1000);
    //chassis.waitUntilDone();
    chassis.turnToHeading(35, 1000);
    //chassis.waitUntilDone();

    // printf("x:%f - y:%f - t:%f\n",chassis.getPose().x,chassis.getPose().y,chassis.getPose().theta);
    subsystem::intake.auto_spin(Intake::INTAKE,false,600);
    chassis.follow(RL1_txt, 50, 10000);
    //chassis.waitUntilDone();
    chassis.turnToHeading(0, 1000);
    //chassis.waitUntilDone();
    subsystem::intake.auto_spin(Intake::STOP);

    // pros::delay(500);
    // subsystem::intake.stop();

    chassis.follow(RL2_txt, 35, 5000, false);
    chassis.moveToPoint(-24, 27.5, 1500, {.forwards = false});
    // //chassis.waitUntilDone();
    // pros::delay(500);
    subsystem::pneumatics.hook_auto(true);
    chassis.turnToHeading(45, 1000);//面向八科
    subsystem::intake.intake();//西兩顆
    // chassis.moveToPoint(-11,40, 1500 );
    // chassis.moveToPoint(-16,30, 1500 ,{.forwards = false});

    // chassis.turnToHeading(25, 1000);
    // chassis.moveToPoint(-11,48, 1500 );
    // chassis.moveToPoint(-16,40, 1500 ,{.forwards = false});
    // chassis.turnToHeading(315, 1000);//面向角落生物

    // // Arm::position::DOWN;
    // subsystem::arm.pid_arm(Arm::position::UP, 50, 5, 350);
    // subsystem::pneumatics.intake_auto(true);

    // chassis.moveToPoint(-60,60, 2000 );








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