#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/asset.hpp"
#include "../include/selector/Selector.hpp"
#include <cstddef>

ASSET(example_txt);

//initialize
pros::MotorGroup right_motor_group({12, 13, 14}, pros::MotorGears::blue);
pros::MotorGroup left_motor_group({-17, -18, -19}, pros::MotorGears::blue);
pros::MotorGroup intake({20});
pros::adi::Pneumatics hook{1,false};
pros::Controller controller(pros::E_CONTROLLER_MASTER);

lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                               10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);




// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              12, // 10 inch track width
                               lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
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
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(100, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              500, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(13, // proportional gain (kP)
                                              0.005, // integral gain (kI)
                                              70, // derivative gain (kD)
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
void initialize() {
    // pros::lcd::initialize();
    chassis.calibrate();

    const char* autons[] = {"Formula1","Formula2","Formula3","Super\nnova",""};
    SW::selector::init(0,autons);

    pros::Task task([&]() {
        while (true) {
            printf("X: %.2f", chassis.getPose().x);
            printf("  Y: %.2f", chassis.getPose().y);
            printf("  Deg; %.2f\n", chassis.getPose().theta);
            pros::delay(50);
        }
    });

    pros::delay(2000);
}
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
ASSET(one_txt);
ASSET(two_txt);
ASSET(pidTuning_txt);
ASSET(test1_txt);
void autonomous() {
    switch (SW::selector::get_auton()) {
        case 0:
            //path
            chassis.setPose(58, -58, 0);
            chassis.follow(test1_txt,15,3000);

            //anuglar tuning
            //chassis.turnToHeading(90, 99000);

            //lateral tuning
            // chassis.setPose(58, -58, 270);
            // chassis.moveToPose(0, -58, 270, 3000);
    
            break;
        case 1:
            printf("Red Auton 1\n");
            // chassis.turnToHeading(90, 99000);
            //havent tried, was told to write pneumatics code
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
  while (1) {
    //pneumatics
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      hook.toggle();
    }
    

    //intake
    int intakeButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    int outtakeButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
  
    if (intakeButton) {
      intake.move_velocity(200);
    } else if (outtakeButton) {
      intake.move_velocity(-200);
    } else {
      intake.move_velocity(0);
    }

    //arcade drive
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    chassis.arcade(leftY, rightX);

    // delay to save resources
    pros::delay(25);
  }
}