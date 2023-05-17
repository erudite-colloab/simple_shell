#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of current position in buf
 *
 * If chain delimeter return 1,otherwise return 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t z = *p;

	if (buf[z] == '|' && buf[z + 1] == '|')
	{
		buf[z] = 0;
		z++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[z] == '&' && buf[z + 1] == '&')
	{
		buf[z] = 0;
		z++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[z] == ';') 
	{
		buf[z] = 0; 
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = z;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: current position of the address should be in buf
 * @i: position should be started in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t z = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			z = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			z = len;
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int y;
	list_t *node;
	char *p;

	for (y = 0; y < 10; y++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int y = 0;
	list_t *node;

	for (y = 0; info->argv[y]; y++)
	{
		if (info->argv[i][0] != '$' || !info->argv[y][1])
			continue;

		if (!_strcmp(info->argv[y], "$?"))
		{
			replace_string(&(info->argv[y]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[y], "$$"))
		{
			replace_string(&(info->argv[y]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[y][1], '=');
		if (node)
		{
			replace_string(&(info->argv[y]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[y], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
