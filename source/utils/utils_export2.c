#include "../../include/minishell.h"

// validates variable names
// checks for empty string or null
// first char must be letter or underscore
// rest of string must be alphanumeric of underscore
static int	export_valid(const char *string)
{
	if (!string || !*string)
		return (0);
	if (!ft_isalpha(*string) && *string != '_')
		return (0);
	string++;
	while (*string)
	{
		if (!ft_isalnum(*string) && *string != '_')
			return (0);
		string++;
	}
	return (1);
}

// prints error message for invalid identifiers
static	void	export_error(const char *key)
{
	if (*key == '\0')
		ft_putstr_fd("minishell: export: `=': not a valid identifier\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd((char *)key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
}

// updates and adds env with value expansion
// handle case with no value
// expand any variables in the value
void export_update(t_program *minishell, char *key, char *value, int sign)
{
	char *expand;

	export_remove(minishell, key);
	if (!value || ft_strcmp(value, "") == 0)
	{
		add_env(minishell, key, "", sign);
		return;
	}
	expand = quote_expand(value, minishell);
	if (!expand)
	{
		add_env(minishell, key, "", sign);
		return;
	}
	add_env(minishell, key, expand, sign);
	free(expand);
}

// extracts key and value from argument
// handles special case where argument is "="
void export_extract(const char *argument, char **key, char **value, int *sign)
{
	char *equals;

	equals = ft_strchr(argument, '=');
	if (equals)
	{
		*key = ft_strndup(argument, equals - argument);
		*value = ft_strdup(equals + 1);
		*sign = 0;
	}
	else
	{
		*key = ft_strdup(argument);
		*value = NULL;
		*sign = 1;
	}
}

void	free_key_value(char *key, char *value)
{
	if (key)
		free (key);
	if (value)
		free (value);
}
// extracts key and value from argument
// validates the key
// process if valid key
int export_process(const char *argument, t_program *minishell)
{
	char *key;
	char *value;
	int sign;

	export_extract(argument, &key, &value, &sign);
	if (!export_valid(key))
	{
		export_error(key);
		minishell->status = 1;
		free_key_value(key, value);
		return 1;
	}
	if (key && *key)
	{
		export_update(minishell, key, value, sign);
		minishell->status = 0;
	}
	free_key_value(key, value);
	return 0;
}
