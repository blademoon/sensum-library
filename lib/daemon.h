#ifndef SENSUM_DAEMON_H
#define SENSUM_DAEMON_H

// Определяем необходимые константы для компилятора
#define _XOPEN_SOURCE 700													// Tell your compiler to include definitions for some extra functions that are defined in X/Open 7, incorporating POSIX 2008

// Объявление необходимые для работы функции already_running() значений.
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)							// Параметры блокировки файла /var/run/daemon.pid используются в функции already_running.
	// LOCKMODE устанавливает файлу следующие биты прав доступа:
	// S_IRUSR - Разрешает пользователю читать файл
	// S_IWUSR - Разрешает пользователю писать в файл
	// S_IRGRP - Разрешает группе читать файл
	// S_IROTH - Разрешает всем остальным читать файл

// Объявления Функций  используемых демонами UNIX.
void daemonize(const char *daemon_name);									// Функция для запуска процесса в режиме демона UNIX.
int	lockfile(int lock_file_descriptor);										// Функция для блокировки файла на запись. Необходима для корректной работы демона UNIX.
int	already_running(const char *daemon_name);								// Функция проверки запушена ли ещё одна копия процесса демона UNIX.
int resrote_sighup_signal (void);											// Функция для восстановления действия по-умолчанию для сигнала SIGHUP. Необходима для работы демона UNIX.

//  Значения возвращаемые функциями
#define	FUNCTION_SUCCESS    1		                                    	// Функция выполнена успешно. The function completed successfully.

// Подключаем файл с определениями функций библиотеки.
#include <sensum/daemon.cpp>

#endif  //  SENSUM_DAEMON_H
