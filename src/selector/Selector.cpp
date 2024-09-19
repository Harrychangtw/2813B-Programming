#include "selector/Selector.hpp"
#include "liblvgl/lvgl.h"
#include "pros/rtos.hpp"
#include "setup.hpp"
#include "pros/screen.hpp"

extern bool team;

namespace Teamselector {

pros::Mutex auton_mtx;

lv_obj_t* redBtnm;
lv_obj_t* blueBtnm;
lv_obj_t* skillsBtnm;

// Add the list of autonomous routines buttons here
int auton;
const char* btnmMap[11] = {"", "", "", "", "", "", "", "", "", "", ""};
const char* skillsMap[] = {"Skills", ""};

// Rendering the buttons for the autonomous routines
// Add logic that if the button is pressed, that autonomous routine is selected
void render() {
    lv_btnmatrix_clear_btn_ctrl_all(redBtnm, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_clear_btn_ctrl_all(blueBtnm, LV_BTNMATRIX_CTRL_CHECKED);
    lv_btnmatrix_clear_btn_ctrl_all(skillsBtnm, LV_BTNMATRIX_CTRL_CHECKED);
    if (auton == 0) { // skills
        lv_btnmatrix_set_btn_ctrl(skillsBtnm, 0, LV_BTNMATRIX_CTRL_CHECKED);
    } else if (auton > 0) { // red
        lv_btnmatrix_set_btn_ctrl(redBtnm, auton - 1,
                                  LV_BTNMATRIX_CTRL_CHECKED);
    } else { // blue
        lv_btnmatrix_set_btn_ctrl(blueBtnm, -auton - 1,
                                  LV_BTNMATRIX_CTRL_CHECKED);
    }
}

// Initializing the autonomous selector screen
void init(int default_auton, const char** autons) {

    int ptr = 0;
    int i = 0;
    do {
        memcpy(&btnmMap[ptr], &autons[ptr], sizeof(&autons));
        ptr++;
    } while (strcmp(autons[ptr], "") != 0);

    // Lock mutex while constructing selector
    auton_mtx.take();

    auton = default_auton;

    lv_theme_t* th =
        lv_theme_default_init(lv_disp_get_default(), lv_color_hex(0xCFB53B),
                              lv_color_hex(0xCFB53B), true, LV_FONT_DEFAULT);

    redBtnm = lv_btnmatrix_create(lv_scr_act());
    lv_btnmatrix_set_map(redBtnm, btnmMap);
    lv_obj_set_size(redBtnm, 480, 70);
    lv_obj_align(redBtnm, LV_ALIGN_CENTER, 0, -70);
    lv_obj_add_event_cb(
        redBtnm,
        [](lv_event_t* e) {
            auton_mtx.take();
            auton = lv_btnmatrix_get_selected_btn(redBtnm) + 1;
            render();
            auton_mtx.give();
        },
        LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_style_pad_all(redBtnm, 6, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(redBtnm, 6, LV_PART_MAIN);
    lv_obj_set_style_bg_color(redBtnm, lv_color_hex(0xF44336),
                              LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(redBtnm, 3, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(redBtnm, lv_color_white(),
                                  LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(redBtnm, lv_color_hex(0xB71C1C), LV_PART_ITEMS);

    /*Add content to the tabs*/
    blueBtnm = lv_btnmatrix_create(lv_scr_act());
    lv_btnmatrix_set_map(blueBtnm, btnmMap);
    lv_obj_set_size(blueBtnm, 480, 70);
    lv_obj_align(blueBtnm, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(
        blueBtnm,
        [](lv_event_t* e) {
            auton_mtx.take();
            auton = -lv_btnmatrix_get_selected_btn(blueBtnm) - 1;
            render();
            auton_mtx.give();
        },
        LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_style_pad_all(blueBtnm, 6, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(blueBtnm, 6, LV_PART_MAIN);
    lv_obj_set_style_bg_color(blueBtnm, lv_color_hex(0x2196F3),
                              LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(blueBtnm, 3,
                                  LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(blueBtnm, lv_color_white(),
                                  LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(blueBtnm, lv_color_hex(0x0D47A1), LV_PART_ITEMS);

    skillsBtnm = lv_btnmatrix_create(lv_scr_act());
    lv_btnmatrix_set_map(skillsBtnm, skillsMap);
    lv_obj_set_size(skillsBtnm, 480, 70);
    lv_obj_align(skillsBtnm, LV_ALIGN_CENTER, 0, 70);
    lv_obj_add_event_cb(
        skillsBtnm,
        [](lv_event_t* e) {
            auton_mtx.take();
            auton = 0;
            render();
            auton_mtx.give();
        },
        LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_style_pad_all(skillsBtnm, 6, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(skillsBtnm, 6, LV_PART_MAIN);
    lv_obj_set_style_bg_color(skillsBtnm, lv_color_hex(0x64C466),//0xFFEB38
                              LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(skillsBtnm, 3,
                                  LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(skillsBtnm, lv_color_white(),
                                  LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(skillsBtnm, lv_color_hex(0x587934),//0xF57F17
                              LV_PART_ITEMS);

    render();

    // Release mutex
    auton_mtx.give();
}
// What is envoked to get the value of the selected autonomous routine so it can
// be used in the main.cpp file
int get_auton() {
    auton_mtx.take();
    int ret = auton;
    auton_mtx.give();
    return ret;
}

void teamSW(bool screen_display) {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        team = !team;
        while((controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) && (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))) {
            pros::delay(10);
        }
    }
    
    if(team) {
        controller.print(0, 0, "Team:Red");//搖桿顯示
        pros::screen::set_pen(pros::c::COLOR_RED);//螢幕顯示紅
    }
    else {
        controller.print(0, 0, "Team:Blue");//搖桿顯示
        pros::screen::set_pen(pros::c::COLOR_BLUE);//螢幕顯示藍
    }

    if(screen_display) {
        pros::screen::fill_rect(0,0,480,272);//螢幕顯示
    }
}

} // namespace Teamselector