#include <DailyTask/daily_task_01.h>
#include <DailyTask/daily_task_02.h>

int main() {
    DailyTask01 dt1("Day 1: Sonar Sweep");
    dt1.part1();
    dt1.part2();
    DailyTask02 dt2("Day 2: Dive!");
    dt2.part1();
    dt2.part2();

    return 0;
}