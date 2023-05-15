#include "../lib/unix.h"
#include "../lib/string.h"
#include "../lib/memory.h"


int execute(char** args);
int cmd_pwd(char** args);
int cmd_cd(char** args);
int cmd_help(char** args);
int cmd_exit(char** args);
int num_builtins();
int launch(char** args);
char** split_line(char* line);


static const char new_line[] = "\n";
static const char msg_help[] = "Shell version 2.0\nCopyright (c) 2023 Evgeny Goryachev Gor.Com\nType program names and arguments, and hit enter.\nThe following are built in:\n";
static const char msg_prompt[] = " $> ";
static const char msg_malloc_err[] = "Shell: allocation error\n";
static const char msg_cd_err[] = "Shell: expected argument to \"cd\"\n";
static const char msg_fork_err[] = "Error forking\n";


#define BUF_SIZE 256
#define TOK_BUFSIZE 64  // Размер буфера с указателями на токены
#define TOK_DELIM " \t\r\n\a" // Разделители для токенизации


// Массив имен встроенных команд
char* cmd_str[] = {
	"cd\0",           	// Поменять каталог
	"help\0",			// Справка
	"exit\0",			// Выход
	"pwd\0"
};

// Массив указателей на функции встроенных команд
int (*cmd_func[]) (char**) = {
	cmd_cd,
	cmd_help,
	cmd_exit,
	cmd_pwd
};


int main(int argc, char** argv){
	
	// Главный цикл
	char** args; // Указатель на указатель на аргументы
	int status = 0; // Статус завершения главного цикла
	
	do {
		
		char* buf_pwd = (char*)malloc(BUF_SIZE);
		char* line_buf = (char*)malloc(BUF_SIZE);

		getcwd(buf_pwd, 256);
		write(1, buf_pwd, strlen(buf_pwd));
		write(1, msg_prompt, sizeof(msg_prompt)-1); // Печатает приглашение ввода команды
		int count_char = read(0, line_buf, BUF_SIZE);
		line_buf[count_char-1] = '\0';
		
		// Извлекает аргументы
		args = split_line(line_buf);
		
		// Определяет завершение главного цикла
		status = execute(args);
		
		// Освобождает память
		free(buf_pwd);
		free(line_buf);
		free(args);
	} while (status);
	
	return 0;
}


// Извлекает аргументы
char** split_line(char* line){
	int bufsize = TOK_BUFSIZE;
	int position = 0;      // Позиция символа
	char** tokens = malloc(sizeof(char*) * bufsize);   // Выделяем память под указатель на указатели
	char* token;           // Указатель на текущий токен
	
	// Проверяет, выделилась ли память
	if (!tokens) {
		write(1, msg_malloc_err, sizeof(msg_malloc_err)-1);
		_exit(1);
	}
	
	// Получаем первый токен из буфера ввода
	token = strtok(line, TOK_DELIM);
	// Заполняем в цикле указатель на указатели на токены
	while (token != 0) {
		tokens[position] = token;
		position++;
		
		// Если буфер переполнен, выделяем еще столько же памяти
		if (position >= bufsize) {
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			
			// Проверяет, выделилась ли память
			if (!tokens) {
				write(1, msg_malloc_err, sizeof(msg_malloc_err)-1);
				_exit(1);
			}
		}
		
		// Получаем последующие токены (поэтому NULL)
		token = strtok(0, TOK_DELIM);
	}
	// Последний токен NULL
	tokens[position] = 0;
	return tokens;
}


// Запуск процессов
int launch(char** args) {
	pid_t pid, wpid;
  	int status;

  	pid = fork();
  	if (pid == 0) {
    		// Child process
    		if (execve(args[0], args, 0) == -1) {
      			write(1, msg_fork_err, sizeof(msg_fork_err)-1);
    		}
    		_exit(1);
  	} else if (pid < 0) {
    		// Error forking
    		write(1, msg_fork_err, sizeof(msg_fork_err)-1);
  	} else {
    		// Parent process
    		//do {
      			wpid = waitpid(pid, &status, 2); // #define WUNTRACED 2  #define WNOHANG 1
    		//} while (!WIFEXITED(status) && !WIFSIGNALED(status));
  	}

  return 1;
}


int num_builtins() {
	return sizeof(cmd_str) / sizeof(char*);
}


// Выполнение встроенных команд или запуск процессов
int execute(char** args) {
	int i;
	
	// Проверяем, не путая ли строка введена
	if (args[0] == '\0') {
		return 1;
	}
	
	for (i = 0; i < num_builtins(); i++) {
		if (strcmp(args[0], cmd_str[i]) == 0) {
			return (*cmd_func[i])(args);
		}
	}
	
	return launch(args);
}


// Команда get current directory
int cmd_pwd(char** args) {
	char buf_pwd[256];
	getcwd(buf_pwd, 256);
	write(1, buf_pwd, strlen(buf_pwd));
	write(1, new_line, sizeof(new_line)-1);
	return 1;
}


// Команда смены каталога
int cmd_cd(char** args) {
	// Проверяем, есть ли второй аргумент
	if (args[1] == 0) {
		// Сообщение об ошибке
		write(1, msg_cd_err, sizeof(msg_cd_err)-1);
	}
	else {
		// Вызываем функцию смены каталога
		if (chdir(args[1]) != 0) {
			write(1, msg_cd_err, sizeof(msg_cd_err)-1);
		}
	}
	return 1;
}


// Команда help
int cmd_help(char** args) {
	int i;
	write(1, msg_help, sizeof(msg_help)-1);
	
	// Выводим массив имен встроенных команд
	for (i = 0; i < num_builtins(); i++) {
		write(1, cmd_str[i], strlen(cmd_str[i]));
		write(1, new_line, sizeof(new_line)-1);
	}
	return 1;
}


// Команда выход
int cmd_exit(char** args) {
	return 0;
}
