#include "auto/auto.hpp"

//關掉自動時執行的task
extern bool off;

void Skill::auto1() {
    //intake自動時的動作程式
    pros::Task intake_run([&]() {
        while(off) {
            subsystem::intake.auto_run();
            pros::delay(10);
        }
    });

    
}
