#include "shell.h"

/**
 * my_exit - function to exit from the shell
 * @info: structure input
 * Return: int
 */
int my_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = err_atoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - function to changes the current directory
 * @info: Structure input
 * Return: Always 0
 */
int my_cd(info_t *info)
{
	char *s, *dirc, buffer[1024];
	int chdir_rett;

	s = getcwd(buffer, 1024);
	if (!s)
		inputString("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirc = get_env(info, "HOME=");
		if (!dirc)
			chdir_rett =
				chdir((dirc = get_env(info, "PWD=")) ? dirc : "/");
		else
			chdir_rett = chdir(dirc);
	}
	else if (copyString(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			inputString(s);
			inputChar('\n');
			return (1);
		}
		inputString(get_env(info, "OLDPWD=")), inputChar('\n');
		chdir_rett =
			chdir((dirc = get_env(info, "OLDPWD=")) ? dirc : "/");
	}
	else
		chdir_rett = chdir(info->argv[1]);
	if (chdir_rett == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - function that changes directory
 * @info: structure input
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	inputString("help call works, function not implemented \n");
	if (0)
		inputString(*arg_arr);
	return (0);
}
