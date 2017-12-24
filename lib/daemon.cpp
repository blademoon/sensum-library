#include <fstream>
#include <string>
#include <unistd.h>
#include <ctime>

#include <syslog.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <signal.h>

// Функция запуска процесса в режиме демона UNIX.
// ВХОДНЫЕ ЗНАЧЕНИЯ:  Имя запускаемого демона UNIX.
// ВАЖНО!!! Имя демона используется для формирования имени файла блокировки и при открытии журнала syslog. Укажите имя маленькими буквами.
// ВАЖНО!!! Для перенастройки параметров открытия журнала syslog исправьте строку 37 указав в ней необходимые параметры.
void daemonize(const char *daemon_name)	{
	int			i, fd0, fd1, fd2;	// Переменные для хранения номеров дескрипторов
	pid_t			pid;
	struct rlimit		rl;			// Структура для хранения мягкого и жесткого пределов номеров для дескриптора файла.
	struct sigaction	sa;			// Структура для фукции sigastion.

	openlog(daemon_name,LOG_PID,LOG_DAEMON);

	umask(0);

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)	{
		syslog(LOG_ERR, "Function daemonize() ERROR: Can't get file limit.");
		exit(1);
	}

	if ((pid = fork()) < 0)	{	//
		syslog(LOG_ERR, "Function daemonize() ERROR: Error in first call of the FORK function - Can't fork.");
		exit(1);
	}
	else if (pid != 0)	{
		exit(0);
	}

	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGHUP, &sa, NULL) < 0)	{
		syslog(LOG_ERR, "Function daemonize() ERROR: Сan't ignore SIGHUP signal.");
		exit(1);
	}
	if ((pid = fork()) < 0)	{
		syslog(LOG_ERR, "Function daemonize() ERROR: Error in second call of the FORK function - Сan't fork");
		exit(1);
	}
	else if (pid != 0) {/* parent */
		//syslog(LOG_ERR, "Error in second call of the FORK function - This is a parent process...");
		exit(0);
	}

	if (chdir("/") < 0)	{
		syslog(LOG_ERR, "Function daemonize() ERROR: Сan't change current work directory to /");
		exit(1);
	}

	if (rl.rlim_max == RLIM_INFINITY) {
		rl.rlim_max = 1024;
	}
	for (i = 0; i < rl.rlim_max; i++) {
		close(i);
	}

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "Function daemonize() ERROR: Unexpected file descriptors fd0 = %d, fd1 = %d fd2 = %d",fd0,fd1,fd2,"."," But shoud be fd0 = 1,fd1 = 2, fd2 = 3.");
		exit(1);
	}
}

// Функция устанавливающая блокировку записи на файл. МОЖНО ИСПОЛЬЗОВАТЬ АНАЛОГ ИЗ БИБЛИОТЕКИ!
// Эта функция используется для гарантированного запуска одной копии демона.
// НА ВХОД ФУНКЦИИ ПОДАЁТСЯ ДЕСКРИПТОР ФАЙЛА БЛОКИРОВКИ.
int	lockfile(int lock_file_descriptor)	{

	struct flock fl;
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return (fcntl(lock_file_descriptor, F_SETLK, &fl));
}

// Функция проверки запущена ли ещё одна копия процесса - демона.
// НА ВХОД ПОДАЁТСЯ ИМЯ ПРОЦЕССА ДЕМОНА!
int	already_running(const char *daemon_name)	{

	int		lock_file_descriptor;
	char	buf[16], path_to_lockfile[20];

	snprintf(path_to_lockfile, sizeof(path_to_lockfile),"/var/run/%s.pid",daemon_name);

	lock_file_descriptor = open(path_to_lockfile, O_RDWR|O_CREAT, LOCKMODE);

	if (lock_file_descriptor < 0) {
		syslog(LOG_ERR, "Function daemonize() ERROR: Can't open %s: %s",path_to_lockfile, strerror(errno));
		exit(1);
	}

	if (lockfile(lock_file_descriptor) < 0) {
		if ((errno == EACCES) || (errno == EAGAIN)) {
			close(lock_file_descriptor);
			return(-1);
		}
		syslog(LOG_ERR, "Function already_running() ERROR: Can't lock file %s: %s",path_to_lockfile, strerror(errno));
		exit(1);
	}

	ftruncate(lock_file_descriptor, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(lock_file_descriptor, buf, strlen(buf)+1);
	return FUNCTION_SUCCESS;
}

// Функция восстанавливающая действие по умолчанию для сигнала SIGHUP.
int restore_sighup_signal(void)	{
	struct sigaction	sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)	{
		syslog(LOG_ERR, "Function restore_sighup_signal() ERROR: Can't restore default action for SIGHUP signal.");
		exit(1);
	}
	return FUNCTION_SUCCESS;
}

