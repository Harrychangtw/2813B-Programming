#include "main.h"
<<<<<<< Updated upstream
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/asset.hpp"
#include "../include/selector/Selector.hpp"
#include <cstddef>

ASSET(example_txt);

//motor set up
// left motor group
=======
#include "UUUU_nova/subsystem.hpp"
#include "pros/device.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "selector/Selector.hpp"
#include "setup.hpp"
#include <cstdio>
#include "liblvgl/draw/lv_draw_img.h"
#include "pros/apix.h"

>>>>>>> Stashed changes
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

<<<<<<< Updated upstream
// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

pros::MotorGroup left_motor_group({12, 13, 14}, pros::MotorGears::red);
// right motor group
pros::MotorGroup right_motor_group({-17, -18, -19}, pros::MotorGears::red);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              600, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(16);
// horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(19);
// vertical tracking wheel encoder
// horizontal tracking wheel
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors,
                        &throttle_curve, 
                        &steer_curve // odometry sensors
);

// initialize function. Runs on program startup


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
=======
//true(紅隊、skill) & falses(藍隊)
bool team;

//關掉自動時執行的task
bool off = true;


>>>>>>> Stashed changes
void initialize() {
    printf("initialize\n");
	// pros::lcd::initialize();
	chassis.calibrate();

	pros::Task task([&]() {
        while (true) {
            // printf("X: %.2f", chassis.getPose().x);
            // printf("  Y: %.2f", chassis.getPose().y);
			// printf("  Deg; %.2f\n", chassis.getPose().theta);
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


<<<<<<< Updated upstream
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
    switch (SW::selector::get_auton()) {
        case 0:
            break;
        case 1:
            printf("Red Auton 1\n");
            break;
        case 2:
            printf("Red Auton 2\n");
            break;
        case 3:
            printf("Red Auton 3\n");
            break;
        case 4:
            printf("Red Auton 4\n");
            break;
        case -1:
            printf("Blue Auton 1\n");
            break;
        case -2:
            printf("Blue Auton 2\n");
            break;
        case -3:
            printf("Blue Auton 3\n");
            break;
        case -4:
            printf("Blue Auton 4\n");
            break;
        default:
            printf("Wrong");
            break;
    }



}
    

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	while (true) {
        // get left y and right x positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX*-1,false, 0.55);

        // delay to save resources
        pros::delay(25);
=======
void autonomous() {
    printf("autonomous\n");
    off = true;
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
}


void opcontrol() {
    printf("opcontrol\n");
    off = false;
    chassis.setBrakeMode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
    controller.clear();
    // controller.print(0, 0, "autonomous testing");
    // printf("start");
	// controller.rumble("..");
    // pros::delay(1000);
	// autonomous();
	// pros::delay(10000);


	// loop forever 記得加delay
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
        chassis.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)*-1,false, 0.55);
        pros::delay(10);
>>>>>>> Stashed changes
    }
}