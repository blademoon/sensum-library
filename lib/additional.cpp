#include <ctime>
#include <string>

// Функция возвращяющая текущй час, текущую минуту, текущий день недели (0 - воскресенье, 1 - понедельник и т.д. ).
int cur_time(int &current_hour,int &current_minute,int &current_week_day) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
	current_hour = ltm->tm_hour;
	current_minute = ltm->tm_min;
	current_week_day = ltm->tm_wday;
        return FUNCTION_SUCCESS;
}

// Функция возвращяющая текущую дату (день, месяц, число) в виде чисел в строковые переменные.
int cur_date(string &current_day,string &current_month,string &current_year) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
		int day = ltm->tm_mday;
		int month = ltm->tm_mon;
		int year = ltm->tm_year;

        //Преобразуем день
        if (day < 10) {
            current_day  = "0" + std::to_string(day);
        } else {
            current_day  = std::to_string(day);
        }
        // Так как месяц считается с января (а январь - 00), то делаем + 1 чтобы получить нужный нам формат месяца.
        month = month + 1;
	// Преобразуем месяц
	if (month < 10) {
            current_month = "0" + std::to_string(month);
	} else {
            current_month = std::to_string(month);
	}

        // Преобразуем год с 1900...
	current_year = std::to_string(year + 1900);

        return FUNCTION_SUCCESS;
}
