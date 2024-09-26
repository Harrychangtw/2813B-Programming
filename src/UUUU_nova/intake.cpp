#include "UUUU_nova/intake.hpp"
#include "UUUU_nova/pneumatics.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "UUUU_nova/arm.hpp"
#include "pros/rtos.hpp"
#include <cstdio>
#include "setup.hpp"

extern bool team;

//std::initializer_list<int8_t> ports,
Intake::Intake( std::uint8_t intake_port, std::uint8_t pto_port, std::int8_t distance_port, std::uint8_t color_air_port, std::uint8_t color_port) {
    // intake_motors = std::make_unique<pros::MotorGroup>(ports);
    intake_motor = std::make_unique<pros::Motor>(intake_port);
    intake_motor->set_gearing(pros::E_MOTOR_GEAR_BLUE);
    intake_motor->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intake_motor->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    distance = std::make_unique<pros::Distance>(distance_port);

    this->color_air = pros::adi::Pneumatics{color_air_port, false};

    color = std::make_unique<pros::Optical>(color_port);

    this->pto = pros::adi::Pneumatics{pto_port, false};

    this->color->set_led_pwm(100);
}

//Intake正轉，預設600rpm 包含卡住反轉
void Intake::intake(int rpm, bool stuck) { 
// printf("vel:%f - ti:%d\n",intake_motor->get_actual_velocity(),ti);
    if(fabs(intake_motor->get_actual_velocity()) < 20 && stuck) {
        if(ti > 50) {
            ti = 0;
            this->stop();
            this->outtake();
            pros::delay(300);
            this->stop();
        }
        else {
            ti++;
            intake_motor->move_velocity(rpm);
        }
    }
    else {
        ti = 0;
        intake_motor->move_velocity(rpm);
    }
    pros::delay(1);

}

//Intake反轉，預設600rpm
void Intake::outtake(int rpm){
    intake_motor->move_velocity(rpm * -1);
}

//排除藍色或紅色ring
void Intake::SWColor() {
    pros::c::optical_raw_s_t raw = color->get_raw();
    if(team == true) {//teamRed
        //printf("val:%d \n", raw.blue);//顯示ＲＧＢ值
        if(this->dis_check(10) || t + 15 < pros::millis()) {//
            // printf("time:%u - t:%u\n", pros::millis(), t);

            if(raw.blue > 300&&raw.red<800) {//看到藍色的數值
                this->color_air.extend();
            }
            
            if((pros::millis() - t) > 500) {
                // printf("%u - t:%u\n",pros::millis(),t);
                t = pros::millis();
            }
        }
        else {
            this->color_air.retract();
            // printf("state:non\n");
            t = pros::millis();
        }
    }
    else if(team == false) {//teamBlue
        // printf("val:%d \n", raw.red);
        if(this->dis_check(50) || t + 15 < pros::millis()) {//
            // printf("time:%u - t:%u\n", pros::millis(), t);
            
            if(raw.red > 500&&raw.blue<500) {//看到紅色的數值
                this->color_air.extend();
            }
            
            if((pros::millis() - t) > 500) {
                // printf("%u - t:%u\n",pros::millis(),t);
                t = pros::millis();
            }
        }
        else {
            this->color_air.retract();
            // printf("state:non\n");
            t = pros::millis();
        }
    }
}

//自動時，給予intake作動，mode : INTAKE(正轉), STOP(停止), OUTTAKE(反轉), SPINFOR(固定角度)
//colorSW : 預設false(單純intake), true(排除錯誤顏色)，val 旋轉速度 預設600RPM，deg(旋轉角度),count(顆數)0一顆
void Intake::auto_spin(Intake::mode mode, bool colorSW, int val, int deg, int count) {
    on_off = mode;
    look = colorSW;
    auto_val = val;
    auto_deg = deg;
    auto_countin = count;
}

//intake自動時的動作程式
void Intake::auto_run() {
    if(on_off == Intake::mode::INTAKE) {
        this->intake(auto_val);
        if(look) {
            this->SWColor();
        }
    }
    else if(on_off == Intake::mode::OUTTAKE) {
        this->outtake(auto_val);
    }
    else if(on_off == Intake::mode::STOP) {
        this->stop();
    }
    else if(on_off == Intake::mode::SPINFOR) {
        spindone = true;
        this->spin_for(auto_val, auto_deg, true, look);
        spindone = false;
        on_off = Intake::mode::STOP;
    }
    else if(on_off == Intake::mode::SPINcount) {
        spindone = true;
        int i = 0;
        while((auto_countin - i) > 1) {
            if(this->distance->get_distance() < 40) {
                while(this->distance->get_distance() < 40) {
                    this->intake(auto_val);
                }
                i++;
            }
            this->intake(auto_val);
        }
        printf("1\n");
        while(i < auto_countin) {
            if(this->distance->get_distance() < 40) {
                i++;
            }
            this->intake(auto_val);
        }
        on_off = Intake::mode::STOP;
        spindone = false;
    }
    else if(on_off == Intake::mode::INTAKEtoARM) {
        this->intake_to_arm(auto_val);
    }
    else if(on_off == Intake::mode::INTAKEtoARM_deg) {
        spindone = true;
        intake_motor->tare_position();
        while(fabs(intake_motor->get_position()) <= auto_deg) {
            this->intake_to_arm(auto_val);
            pros::delay(1);
        }
        spindone = false;
        on_off = Intake::mode::STOP;
    }
    else if(on_off == Intake::mode::INTAKEtoARM_count) {
        spindone = true;
        this->intake_to_arm_count(auto_val, auto_countin);
        spindone = false;
        on_off = Intake::mode::STOP;
    }
}

//intake自動時等待spin_for結束
void Intake::waitIntakeDone() {
    while(spindone) {
        pros::delay(10);
    }
}

//intake旋轉角度，val(旋轉速度，單位RPM), deg(旋轉角度), SW(是否需要判斷顏色)
void Intake::spin_for(int val, int deg, bool stop, bool SW) {
    int i = 0;
    int timeout = deg * 50;
    intake_motor->tare_position();
    while(fabs(intake_motor->get_position()) <= deg && i < timeout) {
        i++;
        intake_motor->move_velocity(val);
        pros::delay(1);
        if(SW) {
            this->SWColor();
        }
    }
    if(stop) {
        this->stop();
    }
}

//intake停止
void Intake::stop(){
    intake_motor->brake();
}

//distance判斷是否小於數值
bool Intake::dis_check(int dis) {
    // printf("%d\n",this->distance->get_distance());
    return this->distance->get_distance() <= dis;
}

//吸ring進入到手臂前端動作
void Intake::intake_move_reverse() {
    this->spin_for(600, 850, true);
    // this->spin_for(200, 70);
    pros::delay(50);
    this->spin_for(-600, 1300);
}

//吸ring進入到手臂前端
void Intake::intake_to_arm(int rpm) {//void* param
    // Intake* intake = static_cast<Intake*>(param);

    if(this->distance->get_distance() < 40) {
        this->intake_move_reverse();
    }
    else {
        this->intake();
    }
}

//吸ring進入到手臂前端，吸入count顆
void Intake::intake_to_arm_count(int rpm, int count) {
    int i = 0;
    while(i < count) {
        if(this->distance->get_distance() < 40) {
            this->intake_move_reverse();
            i++;
        }
        else {
            this->intake();
        }
    }
}

//intake遙控
Pneumatics pneumaticsI('D', 'C', 'A', 'H');
Arm armI(9, 8);
void Intake::remote(pros::Controller Controller) {
    pros::c::optical_raw_s_t raw1 = color->get_raw();
    printf("Red:%d - Blue:%d \n", raw1.red, raw1.blue);
    if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        t = pros::millis();
        // controller.print(1,0,"Ring Up Mode");

        if(armI.not_down()) {
            controller.rumble(".");
            pneumaticsI.intake_auto(false);
            Pneumatics::intake_pne = false;
            Arm::move_break = true;
            Pneumatics::state = true;
            armI.pid_arm(Arm::position::DOWN);
            Pneumatics::state = false;
        }

        this->intake_to_arm();
    }
    else if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        // controller.print(1,0,"Intake Sort Mode");
        this->SWColor();
        this->intake();
    }
    else if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        // controller.print(1,0,"Intake Mode");
        t = pros::millis();
        this->intake();
    }
    else if(Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        // controller.print(1,0,"Outtake Mode");
        t = pros::millis();
        this->outtake();
    }
    else {
        // controller.print(1,0,"Stop");
        this->color_air.retract();
        t = pros::millis();
        this->stop();
    }
};