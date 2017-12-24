#ifndef SENSUS_TCS34725_H_INCLUDED
#define SENSUS_TCS34725_H_INCLUDED

// Объявления функций библиотеки Sensus sensor.
int read_tcs34725(int &red, int &green, int &blue, int &clear_color, int &ir_luminance);   	// Функция получения данных с сенсора TCS34725

// Значенрия передаваемые функциям.
// Здесь пока что пусто. )))

// Значения возвращаемые функциями.
#define	FUNCTION_SUCCESS                1			// Функция выполнена успешно. The function completed successfully.
#define FUNC_ERR_OPEN_I2C_BUS_FILE		-300		// Ошибка! Не могу открыть файл /dev/i2c-1. ERROR! Can't open I2C bus file /dev/i2c-1.
#define FUNC_ERR_ACQ_I2C_BUS			-301		// Ошибка! Не удаётся получить доступ к шине I2C или взаимодействовать с сенсором. ERROR! Failed to acquire bus access and / or talk to slave sensor.

// Подключае файл с определениями функций.
#include <sensus/tcs34725.cpp>

#endif // SENSUS_TCS34725_H_INCLUDED
