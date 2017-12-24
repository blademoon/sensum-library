﻿#ifndef SENSUM_ADDITIONAL_H
#define SENSUM_ADDITIONAL_H

// Объявление функций библиотеки Sensus additional.
int cur_time(int &current_hour, int &current_minute,int &current_week_day);		// Функция возвращяющая текущий час. Зависит от настроек NTP!

//  Значения возвращаемые функциями
#define	FUNCTION_SUCCESS    1                                                   // Функция выполнена успешно. The function completed successfully.

// Подключаем файл с определениями функций библиотеки.
#include <sensum/additional.cpp>

#endif  // SENSUM_ADDITIONAL_H
