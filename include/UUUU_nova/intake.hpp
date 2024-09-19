#pragma once
#include "pros/motor_group.hpp"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include <atomic>
#include <memory>
#include <initializer_list>
#include <sys/_stdint.h>
#include "pros/distance.hpp"
#include "pros/device.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include <cstdio>
#include "pros/optical.hpp"


//std::initializer_list<int8_t> ports, 
class Intake{
public:
    Intake(std::uint8_t intake_port, std::uint8_t pto_port, std::int8_t distance_port, std::uint8_t color_air_port, std::uint8_t color_port);

    //自動時auto_spin模式
    enum mode{
        INTAKE,
        OUTTAKE,
        STOP,
        SPINFOR,
        SPINcount,
        INTAKEtoARM,
        INTAKEtoARM_deg,
        INTAKEtoARM_count
    };

    //Intake正轉，預設600rpm，預設開啟卡住反轉
    void intake(int rpm = 600, bool stuck = true);

    //Intake反轉，預設600rpm(請填正值)
    void outtake(int rpm = 600);

    //排除藍色或紅色ring
    void SWColor();

    /**intake旋轉角度
     *
     * val(旋轉速度，單位RPM)
     *
     * deg(旋轉角度)
     *
     * SW(是否需要判斷顏色)
     *
     * 不需要加時間跳出(預設:角度 * 50 mSec)
     */
    void spin_for(int val, int deg, bool stop = true, bool SW = false);

    /**自動時，給予intake作動(沒有做動的變數可以隨意輸入)
     * 
     * mode : INTAKE(正轉)/STOP(停止)/OUTTAKE(反轉)/SPINFOR(固定角度)/INTAKEtoARM(吸ring至手臂，秒數控制)/INTAKEtoARM_deg(吸ring至手臂，角度控制)/INTAKEtoARM_count(吸ring至手臂，顆數控制)
     *
     * colorSW : 預設false(單純intake)/true(排除錯誤顏色)
     *
     * val : 旋轉速度 預設600RPM
     *
     * deg : 旋轉角度
     *
     * count : 吸ring至手臂前端的數量
     */
    void auto_spin(Intake::mode mode, bool colorSW = false, int val = 600, int deg = 0, int count = 0);

    //intake自動時的動作程式
    void auto_run();

    //intake自動時等待spin_for結束
    void waitIntakeDone();

    //intake停止
    void stop();

    //distance判斷是否小於數值
    bool dis_check(int dis);

    //吸ring進入到手臂前端動作
    void intake_move_reverse();

    //吸ring進入到手臂前端，速度預設600rpm
    void intake_to_arm(int rpm = 600);

    //吸ring進入到手臂前端，速度預設600rpm，吸入count顆 預設1顆
    void intake_to_arm_count(int rpm = 600, int count = 1);

    //intake遙控
    void remote(pros::Controller Controller);


private:
    //自動時，intake spinfor 結束
    bool spindone = true;

    //自動時，intake運作的模式
    Intake::mode on_off = Intake::mode::STOP;

    //自動時，intake是否需要分辨顏色
    bool look = false;

    //自動時，intake spinfor速度
    int auto_val = 0;

    //自動時，intake spinfor角度
    int auto_deg = 0;

    //自動時，吸ring進入到手臂前端顆數
    int auto_countin = 0;

    uint32_t t = 0;

    int ti = 0;

    // std::unique_ptr<pros::MotorGroup> intake_m tors;    

    std::unique_ptr<pros::Motor> intake_motor;

    std::unique_ptr<pros::Distance> distance;

    pros::adi::Pneumatics pto {0,false};

    pros::adi::Pneumatics color_air {0,false};

    std::unique_ptr<pros::Optical> color;
};