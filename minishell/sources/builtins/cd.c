/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:13:07 by zuraw             #+#    #+#             */
/*   Updated: 2024/12/26 12:42:13 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Zwraca aktualną lokację w zależności od argumentów
static char	*cd_find_path(t_exec *exec, t_data *data)
{
	char	*target_path;

	if (!exec->args[1])
	{
		target_path = get_env_value("HOME", data->envp);
		if (target_path == NULL)
			return (printf("cd: HOME not set\n"), NULL);
	}
	else if (ft_strncmp(exec->args[1], "-", 1) == 0)
	{
		target_path = get_env_value("OLDPWD", data->envp);
		if (target_path == NULL)
			return (printf("cd: OLDPWD not set\n"), NULL);
		printf("%s\n", target_path);
	}
	else
		target_path = exec->args[1];
	return (target_path);
}

static char	**add_env_var(t_data *data, const char *key, const char *value)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (data->envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (perror("malloc"), NULL);
	i = 0;
	while (data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		if (!new_envp[i])
			return (free_double_array(new_envp), NULL);
		i++;
	}
	new_envp[i] = ft_strjoin(key, value);
	if (!new_envp[i])
		return (free_double_array(new_envp), NULL);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

static int	update_env_var(t_data *data, char *key, char *value)
{
	int		i;
	char	*new_value;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0)
		{
			free(data->envp[i]);
			new_value = ft_strjoin(key, value);
			if (!new_value)
				return (0);
			data->envp[i] = new_value;
			return (1);
		}
		i++;
	}
	return (0);
}

// Zmienia OLDPWD na poprzednią lokację oraz PWD na aktualną
static void	cd_change_envp(char *tp, char *cp, t_data *data)
{
	int		changed;
	char	**new_envp;

	changed = 0;
	changed += update_env_var(data, "OLDPWD=", cp);
	changed += update_env_var(data, "PWD=", tp);
	if (changed < 2)
	{
		new_envp = add_env_var(data, "OLDPWD=", cp);
		if (!new_envp)
			return ;
		else
		{
			free_data_envp(data);
			data->envp = new_envp;
			set_exec_envp(data->exec, data->envp);
		}
	}
}

/*
	1. Sprawdzenie liczby argumentów
		a. Jeżeli więcej niż jeden argument, to wypisz błąd
		b. Zwróć kod błędu 1
	2. Pobranie aktualnej ścieżki
		a. Wywołanie funkcji get_current_path, aby uzyskać aktualny katalog
	3. Znalezienie ścieżki docelowej
		a. Jeżeli nie podano argumentu, to pobierz zmienną HOME
		b. Jeżeli podano argument "-", to pobierz zmienną OLDPWD
		c. W przeciwnym wypadku pobierz pierwszy argument
	4. Tworzenie kopii ścieżki docelowej, dla bezpieczeństwa
		a. Skopiowanie target_path do temp_path
		b. Sprawdzenie błędu alokacji pamięci
	5. Zmiana katalogu
		a. Wywołanie funkcji change_dir z temp_path
		b. Zwrócenie błędu 1 w przypadku niepowodzenia
	6. Pobranie pełnej ścieżki po zmianie katalogu
		a. Wywołanie funkcji get_current_path, aby uzyskać pełną,
			rozwiniętą ścieżkę (resolved_path)
	7. Aktualizacja zmiennych środowiskowych
		a. Wywołanie funkcji cd_change_envp
			- Zmiana OLDPWD na poprzednią lokację (current_path)
			- Zmiana PWD na aktualną lokację (resolved_path)
	8. Zwolnienie pamięci
		a. Zwolnienie current_path, temp_path oraz resolved_path
	9. Zwrot wartości
		a. 0 - jeżeli wszystko przebiegło pomyślnie
		b. 1 - jeżeli wystąpił błąd
*/
int	builtin_cd(t_exec *exec, t_data *data)
{
	char	*target_path;
	char	*current_path;
	char	*temp_path;
	char	*resolved_path;

	if (is_correct(exec) == 1)
		return (1);
	current_path = get_current_path();
	target_path = cd_find_path(exec, data);
	if (target_path == NULL)
		return (free(current_path), 1);
	temp_path = ft_strdup(target_path);
	if (!temp_path)
	{
		perror("malloc");
		free(current_path);
		return (1);
	}
	if (change_dir(temp_path) == 1)
		return (free(current_path), 1);
	resolved_path = get_current_path();
	cd_change_envp(resolved_path, current_path, data);
	free(current_path);
	free(temp_path);
	return (free(resolved_path), 0);
}
