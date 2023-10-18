#include "shell.h"

/**
 * shh - function for main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shh(info_t *info, char **av)
{
	ssize_t e = 0;
	int builtin_ret = 0;

	while (e != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			inputString("$ ");
		einputChar(BUF_FLUSH);
		e = get_input(info);
		if (e != -1)
		{
			set_info(info, av);
			builtin_ret = findBuiltin(info);
			if (builtin_ret == -1)
				cmdFind(info);
		}
		else if (interactive(info))
			inputChar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * findBuiltin - funcrtion that finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int findBuiltin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (u = 0; builtintbl[u].type; u++)
		if (stringComp(info->argv[0], builtintbl[u].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[u].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * cmdFind - function that finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmdFind(info_t *info)
{
	char *path = NULL;
	int u, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (u = 0, l = 0; info->arg[u]; u++)
		if (!is_delim(info->arg[u], " \t\n"))
			l++;
	if (!l)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		cmdFork(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			cmdFork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * cmdFork - function that forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmdFork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
