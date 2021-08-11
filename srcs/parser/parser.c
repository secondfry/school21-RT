/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 21:05:52 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/08/11 21:05:52 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_arguments(int argc, char **argv)
{
	int	fd;
	int	len;

	check(argc != 2, 1, ERR_PARSER_ARGC);
	fd = open(argv[argc - 1], O_RDONLY);
	check(fd < 0, 1, ERR_PARSER_OPEN);
	len = read(fd, 0, 0);
	check(len < 0, 1, ERR_PARSER_READ);
	return (fd);
}

void	parser(t_rtv *rtv, int argc, char **argv)
{
	int		fd;
	t_level	*root;
	char	*memory;

	fd = check_arguments(argc, argv);
	memory = 0;
	root = parse(fd, &memory);
	validate(rtv, root);
	free_parsed_struct(root);
	free(memory);
}
