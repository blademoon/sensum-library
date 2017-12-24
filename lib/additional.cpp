#include <ctime>

// Функция возвращяющая текущй час, текущую минуту, текущий день недели (0 - воскресенье, 1 - понедельник и т.д. ).
int cur_time(int &current_hour,int &current_minute,int &current_week_day) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
		current_hour = ltm->tm_hour;
		current_minute = ltm->tm_min;
		current_week_day = ltm->tm_wday;
        return FUNCTION_SUCCESS;
}
