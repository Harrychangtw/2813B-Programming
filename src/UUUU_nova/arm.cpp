
#include <cstdint>
#include <iostream>
#include "UUUU_nova/arm.hpp"

#include "pros/misc.h"
#include "pros/motors.h"
#include "setup.hpp"


bool Arm::move_break = false;

Arm::Arm(std::uint8_t arm_port, std::uint8_t rotation_port) {
    // intake_motors = std::make_unique<pros::MotorGroup>(ports);
    arm_motor = std::make_unique<pros::Motor>(arm_port);
    rotation = std::make_unique<pros::Rotation>(rotation_port);

    arm_motor->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    arm_motor->set_gearing(pros::E_MOTOR_GEAR_GREEN);
    arm_motor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    arm_pid.set_constants(0.05, 0.000001, 0);
    arm_pid.reset();
}

//手臂遙控抬升
void Arm::up() {
    error_up = Arm::position::UP - rotation->get_angle();
    arm_motor->move_velocity((arm_pid.update(error_up)));
    // arm_motor->move_voltage(12000);
}

//手臂遙控下降
void Arm::down() {
    if(Pneumatics::intake_pne) {
        error_down = Arm::position::INTAKE - rotation->get_angle();
    }
    else {
        error_down = Arm::position::DOWN - rotation->get_angle();
    }
    arm_motor->move_velocity((arm_pid.update(error_down)));
}
//手臂停止
void Arm::stop() {
    arm_motor->brake();
}

//判斷手臂的位置是否在DOWN的位置
bool Arm::not_down() {
    if(rotation->get_angle() > (Arm::position::DOWN + 300)) {
        return true;
    }
    else {
        return false;
    }
}

//判斷手臂的位置是否低於INTAKE
bool Arm::lower_intake() {
    if(rotation->get_angle() < Arm::position::INTAKE || state == Arm::position::DOWN) {
        return true;
    }
    else {
        return false;
    }
}

//手臂PID作動，position(目標位置), ess(誤差值，預設為30), stabletime(穩定後跳出時間，預設為50), outtime(卡住強制跳出時間，預設為1500)
void Arm::pid_arm(Arm::position position, int ess, int stabletime, int outtime) {    
    move_break = false;

    double error;
    int o = 0;
    int s = 0;
    while(o < outtime) {
        error = static_cast<double>(position) - rotation->get_angle();

        // printf("%d\n", rotation->get_angle());
        arm_motor->move_velocity((arm_pid.update(error))*0.5);
        pros::delay(10);
        // printf("time:%d\n",o);
        o++;

        if(fabs(static_cast<double>(position) - rotation->get_angle()) < ess) {
            s++;
            if(s > stabletime) {
                break;
            }
        }
        else {
            s = 0;
        }
        if(move_break) {
            break;
        }
    }
    // printf("done");
    // printf("%d\n", rotation->get_angle());
    // printf("time:%d\n",o);

    this->stop();
    new_control = false;
    Pneumatics::state = false;
}

//遙控時手臂動作程式
void Arm::arm_move() {
    if(new_control == true) {
        this->pid_arm(state);
        // printf("right here\n");
    }
}

//遙控手臂程式
void Arm::remote(pros::Controller Controller) {
    if(Pneumatics::state == false) {
        if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            move_break = true;
            pros::delay(10);
            new_control = false;
            this->up();
        }
        else if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            move_break = true;
            pros::delay(10);
            new_control = false;
            this->down();
        }
        else if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {//待測試
            move_break = true;
            pros::delay(10);
            new_control = true;
            state = Arm::position::INTAKE;
            arm_move();


     }
        // else if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {//待測試
        //     move_break = true;
        //     pros::delay(10);
        //     new_control = true;
        //     if(Pneumatics::intake_pne) {
        //         state = Arm::position::INTAKE;
        //     } 
        //     else {
        //         state = Arm::position::DOWN;
        //     }
        // }
        else {
            if(rotation->get_angle() < (Arm::position::INTAKE - 50)) {
                arm_motor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            }
            else {
                arm_motor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            }

            if(new_control == false || Pneumatics::state == false) {
                this->stop();
            }   
            
        }
    }
}



