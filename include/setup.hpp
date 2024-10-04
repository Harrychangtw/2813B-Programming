#pragma once
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <iostream>

static pros::Controller controller(pros::E_CONTROLLER_MASTER);

static pros::MotorGroup right_motors({1,2,3}, pros::MotorGearset::blue); 
static pros::MotorGroup left_motors({-18,-19,-10}, pros::MotorGearset::blue); 
static lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              11.417, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

static pros::Imu imu(12);

static pros::Rotation horizontal_encoder(13);//左右
static pros::Rotation vertical_encoder(13);//前後
// horizontal tracking wheel
static lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -2);
// vertical tracking wheel
static lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, 0.375);
static lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

static lemlib::ControllerSettings lateral_controller(
    8,     // proportional gain (kP) - further reduced from 15
    0,  // integral gain (kI) - further reduced
    0,    // derivative gain (kD) - increased from 200
    3,      // anti windup
    1,      // small error range, in inches
    100,    // small error range timeout, in milliseconds
    3,      // large error range, in inches
    500,    // large error range timeout, in milliseconds
    6       // maximum acceleration (slew) - further reduced from 8
);

// Angular PID controller
static lemlib::ControllerSettings angular_controller(
    8,    // proportional gain (kP) - further reduced from 7
    0, // integral gain (kI) - further reduced
    50,    // derivative gain (kD) - increased from 100
    3,      // anti windup
    1,      // small error range, in degrees
    100,    // small error range timeout, in milliseconds
    3,      // large error range, in degrees
    500,    // large error range timeout, in milliseconds
    0       // maximum acceleration (slew)
);
// create the chassis
static lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);