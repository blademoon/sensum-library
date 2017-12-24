#include <iostream>
#include <sensus/bme280.h>
#include <sensus/additional.h>
#include <sensus/daemon.h>
#include <syslog.h>

using namespace std;

int main () {

	// Переменные для хранения текущих значений влажности, температуры, давления.
	float temperature = 0, pressure = 0, humidity = 0;

	// Переменные необходимые для работы демона
	// Имя демона.
	const	char *daemon_name = "TEST-DAEMON";

	// Переменные для хранения текущего дня недели, часа и минуты.
	int day_of_week = 0, cur_hour = 0, cur_minute = 0;

	// Переходим в состояние демона UNIX
	daemonize(daemon_name);

	// Проверяем запущена ли ещё одна копия демона, если да, то сообщаем об этом в журнал и заверщаем работу.
	if ((already_running(daemon_name)) != 1) {
		syslog(LOG_ERR,"Another copy of the daemon is already running. ");
		return 0;
	}

	// Сообщаем об успешном запуске демона.
	syslog(LOG_NOTICE,"Daemon successfully started ...");

	// Восстанавливаем действие по умолчанию для сигнала SIGHUP. В случае ошибки выход (и сообщение об ошибке в журнал) реализованы в самой функции.
	restore_sighup_signal();


// Основной цикл работы демона.

	for ( ; ; ) {

		// получаем текущее время (час и минуту) и день недели.
		cur_time(cur_hour,cur_minute,day_of_week);

		// Передаём в журнал информацию о текущем уровне освещения, влажности, давления, температуре 1 раз в 15 минут.
		if ((cur_minute % 15) == 0) {

			// Передаём текущие значения освещения, давления, температуры, влажности.
			read_bme280(humidity,temperature,pressure);
			syslog(LOG_NOTICE,"Current pressure: %.2f (hPa), temperature: %.2f (C), humidity: %.2f (%).", pressure,temperature,humidity);


			// Засыпаем на 1 минуту, чтобы гарантированно передать в лог только одну запись текущих параметрах среды.
			sleep(60);
	}
		// Делаем задержку в 1 секунду после каждого цикла, чтобы снизить нагрузку на процессор.
		sleep(1);

	}

	return 0;

}
