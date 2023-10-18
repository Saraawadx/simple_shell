#include "shell.h"

/**
 * isExec_cmd - function that determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExec_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupChars - function that helps duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupChars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int u = 0, l = 0;

	for (l = 0, u = start; u < stop; u++)
		if (pathstr[u] != ':')
			buff[l++] = pathstr[u];
	buff[l] = 0;
	return (buff);
}

/**
 * findPath - function that helps finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *findPath(info_t *info, char *pathstr, char *cmd)
{
	int u = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((stringLen(cmd) > 2) && needleStart(cmd, "./"))
	{
		if (isExec_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[u] || pathstr[u] == ':')
		{
			path = dupChars(pathstr, curr_pos, u);
			if (!*path)
				concatString(path, cmd);
			else
			{
				concatString(path, "/");
				concatString(path, cmd);
			}
			if (isExec_cmd(info, path))
				return (path);
			if (!pathstr[u])
				break;
			curr_pos = u;
		}
		u++;
	}
	return (NULL);
}
