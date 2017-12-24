#ifndef SENSUS_TSL2561_H_INCLUDED
#define SENSUS_TSL2561_H_INCLUDED

// Объявления функций библиотеки Sensus sensor.
int read_tsl2561(float &visible_lux, float &ir_lux, float &total_lux); 											// Функция получения данных с сенсора TSL2561

// Значения возвращаемые функциями.
#define	FUNCTION_SUCCESS                1			// Функция выполнена успешно. The function completed successfully.
#define FUNC_ERR_OPEN_I2C_BUS_FILE		-300		// Ошибка! Не могу открыть файл /dev/i2c-1. ERROR! Can't open I2C bus file /dev/i2c-1.
#define FUNC_ERR_ACQ_I2C_BUS			-301		// Ошибка! Не удаётся получить доступ к шине I2C или взаимодействовать с сенсором. ERROR! Failed to acquire bus access and / or talk to slave sensor.

// Подключае файл с определениями функций.
#include <sensus/tsl2561.cpp>

#endif // SENSUS_TSL2561_H_INCLUDED
