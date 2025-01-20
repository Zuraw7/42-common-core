/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:03:32 by zuraw             #+#    #+#             */
/*   Updated: 2025/01/07 21:09:04 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main (int argc, char **argv)
{
	if (argc < 2)
		std::cout << "* LOUND AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		for (int i = 1; i < argc; i++)
			for (int j = 0; argv[i][j]; j++)
				std::cout << (char)toupper(argv[i][j]);
		std::cout << std::endl;
	}
	
	return 0;
}
