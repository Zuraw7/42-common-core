/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_array_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:32:20 by rkobelie          #+#    #+#             */
/*   Updated: 2024/12/23 10:39:22 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double_array(char **array)
{
	size_t	i;

	i = 1;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

// char	**copy_double_array(char **src)
// {
// 	int		count;
// 	char	**dest;
// 	int		i;
// 	int		j;

// 	if (!src)
// 		return (NULL);
// 	count = 0;
// 	while (src[count])
// 		count++;
// 	dest = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!dest)
// 	{
// 		perror("malloc failed");
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < count)
// 	{
// 		dest[i] = strdup(src[i]);
// 		if (!dest[i])
// 		{
// 			perror("strdup failed");
// 			j = 0;
// 			while (j < i)
// 			{
// 				free(dest[j]);
// 				j++;
// 			}
// 			free(dest);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	dest[count] = NULL;
// 	return (dest);
// }
