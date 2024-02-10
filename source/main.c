#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <psl1ght/lv2.h>
#include <psl1ght/sysmodule.h>
#include <psl1ght/ctrl.h>

#define DEFAULT_TIME 1
#define MAX_TIME 99

int main(int argc, char *argv[])
{
    lv2_init();

    SysModule *sysmodule = sysModuleLoad(SYSMODULE_CTRL);
    if (!sysmodule)
    {
        printf("Failed to load SYSMODULE_CTRL\n");
        return -1;
    }

    int fan_speed = 0;
    int time_left = DEFAULT_TIME;
    int timer_running = 0;

    while (1)
    {
        sysModuleUpdate(sysmodule);

        u64 pad_data = padGetButtonsDown(0);

        if (pad_data & PAD_BUTTON_START)
        {
            break;
        }

        if (pad_data & PAD_BUTTON_X)
        {
            fan_speed = 85;
            timer_running = 1;
        }
        else if (pad_data & PAD_BUTTON_O)
        {
            fan_speed = 0;
            timer_running = 0;
            time_left = DEFAULT_TIME;
        }

        if (timer_running)
        {
            time_left--;
            if (time_left <= 0)
            {
                fan_speed = 0;
                timer_running = 0;
                time_left = DEFAULT_TIME;
            }
        }

        printf("\x1b[2J\x1b[0;0H");
        printf("Fan Speed: %d%%\n", fan_speed);
        printf("Time Left: %d minutes\n", time_left);
        printf("Start by pressing X\n");
        printf("Stop by pressing O\n");
        printf("Press Start to exit\n");

        usleep(100000);
    }

    sysModuleUnload(sysmodule);
    lv2_exit();

    return 0;
}
