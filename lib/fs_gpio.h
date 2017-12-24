#ifndef SENSUS_FS_GPIO_H
#define SENSUS_FS_GPIO_H

// Объявление функций библиотеки Sensus GPIO.
int calculate_pin_number(int pin_number);
int export_pin(int pin_number);
int unexport_pin(int pin_number);
int check_pin_direction(int pin_number);
int set_pin_direction(int pin_number, int direction);
int check_pin_value(int pin_number);
int set_pin_value(int pin_number, int pin_value);
int check_active_low_state(int pin_number);
int set_active_low_state(int pin_number, int active_low_state);


// Значения передаваемые функциям.
#define PIN_ON							1			// Логическая единица. Logical one (pin on).
#define PIN_OFF							0			// Логический ноль. Logical zero (pin off).
#define PIN_IN  						2			// Пин переведен в режим ВВОД. Pin in INPUT mode.
#define PIN_OUT 						3			// Пин переведен в режим ВЫВОД. Pin in OUTPUT mode.
#define PIN_ACTIVE_LOW_ON				4			// Режим ACTIVE_LOW включён для пина. ACTIVE_LOW operation mode on.
#define PIN_ACTIVE_LOW_OFF				5			// Режим ACTIVE_LOW выключен для пина. ACTIVE_LOW operation mode off.

// Значения возврашаемые функциями.

#define	FUNCTION_SUCCESS    1           			// Функция выполнена успешно. The function completed successfully.

#define	FUNC_ERR_PIN_NUM				-1			// Ошибка, не верный номер пина или данный пин не может быть использован. Error! The wrong pin number or given pin can not be used in programm!

#define	FUNC_ERR_OPEN_EXPORT_WR			-10			// Ошибка! Не могу открыть для записи файл export. ERROR! Can't open file "export" for write!
#define	FUNC_ERR_OPEN_EXPORT_RD			-11			// Ошибка! Не могу открыть для чтения файл export. ERROR! Can't open file "export" for read!
#define	FUNC_ERR_WR_TO_EXPORT			-12			// Ошибка! Не могу выполнить запись в файл export. ERROR! Can't write to file "export"!
#define FUNC_ERR_RD_FROM_EXPORT			-13			// Ошибка! Не могу выполнить чтение из файла export. ERROR! Can't read from file "export"!

#define	FUNC_ERR_OPEN_UNEXPORT_WR		-20			// Ошибка! Не могу открыть для записи файл unexport. ERROR! Can't open file "unexport" for write!
#define	FUNC_ERR_OPEN_UNEXPORT_RD		-21			// Ошибка! Не могу открыть для чтения файл unexport. ERROR! Can't open file "unexport" for read!
#define FUNC_ERR_WR_TO_UNEXPORT			-22			// Ошибка! Не могу выполнить запись в файл unexport. ERROR! Can't write to file "unexport"!
#define FUNC_ERR_RD_FROM_UNEXPORT		-23			// Ошибка! Не могу выполнить чтение из файла unexport. ERROR! Can't read from file "unexport"!

#define FUNC_ERR_OPEN_DIRECTION_WR		-30			// Ошибка! Не могу открыть для записи файл direction. ERROR! Can't open file "direction" for write!
#define	FUNC_ERR_OPEN_DIRECTION_RD		-31			// Ошибка! Не могу открыть для чтения файл direction. ERROR! Can't open file "direction" for read!
#define FUNC_ERR_WR_TO_DIRECTION		-32			// Ошибка! Не могу выполнить запись в файл direction. ERROR! Can't write to file "direction"!
#define FUNC_ERR_RD_FROM_DIRECTION		-33			// Ошибка! Не могу выполнить чтение из файла direction. ERROR! Can't read from file "direction"!
#define FUNC_ERR_UNK_DIR_RET			-34			// Ошибка! Из файла direction считанно не корректное значение. ERROR! Incorrect value readed from file "direction".
#define FUNC_ERR_UNK_DIR_SENT			-35			// Ошибка! В фунцию gpio_set_pin_direction передано не корректное значение.

#define	FUNC_ERR_OPEN_VALUE_WR			-40			// Ошибка! Не могу открыть для записи файл value. ERROR! Can't open file "value" for write!
#define FUNC_ERR_OPEN_VALUE_RD			-41			// Ошибка! Не могу открыть для чтения файл value. ERROR! Can't open file "value" for read!
#define FUNC_ERR_WR_TO_VALUE			-42			// Ошибка! Не могу выполнить запись в файл value. ERROR! Can't write to file "value"!
#define FUNC_ERR_RD_FROM_VALUE			-43			// Ошибка! Не могу выполнить чтение из файла value. ERROR! Can't read from file "value"!
#define FUNC_ERR_UNK_VAL_RET			-44			// Ошибка! Из файла value считанно не корректное значение. ERROR! Incorrect value readed from file "value".
#define FUNC_ERR_UNK_VAL_SENT			-45			// Ошибка! В фунцию gpio_set_pin_value передано не корректное значение. ERROR! An incorrect pin value was passed to function "gpio_set_pin_value".
#define FUNC_ERR_INC_PIN_DIR			-46			// Ошибка! Для пина задан не корректный режим ввода/вывода.

#define FUNC_ERR_OPEN_ACTIVE_LOW_WR		-50			// Ошибка! Не могу открыть для записи файл active_low. ERROR! Can't open file "active_low" for write!
#define FUNC_ERR_OPEN_ACTIVE_LOW_RD		-51			// Ошибка! Не могу открыть для чтения файл active_low. ERROR! Can't open file "active_low" for read!
#define FUNC_ERR_WR_TO_ACTIVE_LOW		-52			// Ошибка! Не могу выполнить запись в файл active_low. ERROR! Can't write to file "active_low"!
#define FUNC_ERR_RD_FROM_ACTIVE_LOW		-53			// Ошибка! Не могу выполнить чтение из файла active_low. ERROR! Can't read from file "active_low"!
#define FUNC_ERR_UNK_ACTIVE_LOW_RET 	-54			// Ошибка! Из файла active_low считанно не корректное значение. ERROR! Incorrect value readed from file "active_low".
#define FUNC_ERR_UNK_ACTIVE_LOW_SENT	-55			// Ошибка! В функцию gpio_set_active_low_state переданно некоректное значение режима работы пина. ERROR! An incorrect value of the pin operation mode was passed to function "gpio_set_active_low_state".

// Подключаем файл с определениями функций.
#include <sensus/fs_gpio.cpp>

#endif /* END OF DECLARATIONS SENSUS_FS_GPIO_H */
