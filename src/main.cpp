#include "main.h"
#include "UUUU_nova/subsystem.hpp"
#include "auto/auto.hpp"
#include "pros/adi.hpp"
#include "pros/device.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "selector/Selector.hpp"
#include "setup.hpp"
#include <cstdio>
#include "liblvgl/draw/lv_draw_img.h"
#include "pros/apix.h"

lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

//true(紅隊、skill) & falses(藍隊)
bool team;

//關掉自動時執行的task
bool off = true;


void initialize() {
    printf("initialize\n");
	// pros::lcd::initialize();
	chassis.calibrate();
    chassis.setPose(0, 0, 0);

    pros::Task task([&]() {
        while (true) {
            printf("X: %.2f", chassis.getPose().x);
            printf("  Y: %.2f", chassis.getPose().y);
            printf("  Deg: %.2f\n", chassis.getPose().theta);
            fflush(stdout);
            pros::delay(50);
        }
    });


    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}


void disabled() {
    printf("disabled\n");
}


void competition_initialize() {
    printf("competition_initialize\n");
    const char* autons[] = {"Left","Solo","Right","test",""};
	Teamselector::init(-3, autons);
}


void autonomous() {
   team = false;//true(紅隊、skill) & falses(藍隊)
   Blue::left();
   off = true;
   
    // team = true;
    // Skill::skill();//Skill 
    // off = true;
    /*
    switch(Teamselector::get_auton()) {
		case 0:
            printf("Skill\n");
            team = true;
            Skill::skill();//Skill 
			break;
		case 1:
			printf("Red1\n");
            team = true;
            Red::left();//Red Left
			break;
		case 2:
			printf("Red2\n");
            team = true;
            Red::solo();//Red Solo
			break;
		case 3:
			printf("Red3\n");
            team = true;
            Red::right();//Red Right
			break;
		case 4:
			printf("Red4\n");
            team = true;
            Skill::auto1();//auto test
			break;
		case -1:
			printf("Blue1\n");
            team = false;
            Blue::left();//Blue Left
			break;
		case -2:
			printf("Blue2\n");
            team = false;
            Blue::solo();//Blue Solo
			break;
		case -3:
			printf("Blue3\n");
            team = false;
            Blue::right();//Blue Left
			break;
		case -4:
			printf("Blue4\n");
            team = false;
            Skill::auto1();//auto test
			break;
		default:
			printf("Wrong");

			break;
        
    }
    */
    
}


void opcontrol() {
    printf("opcontrol\n");
   
    off = false;
    chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
    controller.clear();

    // Start the elevator unlock timer
    subsystem::pneumatics.start_elevator_unlock_timer();

    pros::Task teamSW([&](){
        while(true) {
            Teamselector::teamSW(false);
            pros::delay(10);
        }
    });
    pros::Task intake_remote([&](){
        while(true) {
            subsystem::intake.remote(controller);
            pros::delay(10);
        }
    });
    pros::Task pneumatics_remote([&](){
        while(true) {
            subsystem::pneumatics.remote(controller);
            pros::delay(10);
        }
    });
    pros::Task arm_pid_move([&](){
        while(true) {
            subsystem::arm.arm_move();
            pros::delay(10);
        }
    });
    pros::Task arm_remote([&](){
        while(true) {
            subsystem::arm.remote(controller);
            pros::delay(10);
        }
    });
    while(true) {
        chassis.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),false, 0.55);
        
        pros::delay(10);
    }
}