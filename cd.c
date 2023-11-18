#include "shell.h"

/**
 * cd_pdir - changes to the parent directory
 *
 * @dataSh: relevant data (environ)
 *
 * Return: no return
 */
void cd_pdir(data_shell *dataSh)
{
	char pwd[PATH_MAX];
	char *dir, *cpr_pwd, *cpr_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cpr_pwd = _strdup(pwd);
	set_env("OLDPWD", cpr_pwd, dataSh);
	dir = dataSh->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cpr_pwd, dataSh);
		free(cpr_pwd);
		return;
	}
	if (_strcmp("/", cpr_pwd) == 0)
	{
		free(cpr_pwd);
		return;
	}
	cpr_strtok_pwd = cpr_pwd;
	rev_string(cpr_strtok_pwd);
	cpr_strtok_pwd = _strtok(cpr_strtok_pwd, "/");
	if (cpr_strtok_pwd != NULL)
	{
		cpr_strtok_pwd = _strtok(NULL, "\0");

		if (cpr_strtok_pwd != NULL)
			rev_string(cpr_strtok_pwd);
	}
	if (cpr_strtok_pwd != NULL)
	{
		chdir(cpr_strtok_pwd);
		set_env("PWD", cpr_strtok_pwd, dataSh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", dataSh);
	}
	dataSh->status = 0;
	free(cpr_pwd);
}

/**
 * cd_to_dir - changes to  given directory
 * by the user
 *
 * @datash: relevant data (directories)
 * Return: nothing to return
 */
void cd_to_dir(data_shell *dataSh)
{
	char pwd[PATH_MAX];
	char *dir, *cpr_pwd, *cpr_dir;

	getcwd(pwd, sizeof(pwd));

	dir = dataSh->args[1];
	if (chdir(dir) == -1)
	{
		get_error(dataSh, 2);
		return;
	}

	cpr_pwd = _strdup(pwd);
	set_env("OLDPWD", cpr_pwd, dataSh);

	cpr_dir = _strdup(dir);
	set_env("PWD", cpr_dir, dataSh);

	free(cpr_pwd);
	free(cpr_dir);

	dataSh->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to previous directory
 *
 * @datash: relevant data (environ)
 * Return: nothing to return
 */
void cd_previous(data_shell *dataSh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cpr_pwd, *cpr_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cpr_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", dataSh->_environ);

	if (p_oldpwd == NULL)
		cpr_oldpwd = cpr_pwd;
	else
		cpr_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cpr_pwd, dataSh);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, dataSh);
	else
		set_env("PWD", cpr_oldpwd, dataSh);

	p_pwd = _getenv("PWD", dataSh->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cpr_pwd);
	if (p_oldpwd)
		free(cpr_oldpwd);

	dataSh->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datash: relevant data (environ)
 * Return: nothing to return
 */
void cd_to_home(data_shell *dataSh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", dataSh->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, dataSh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(dataSh, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
