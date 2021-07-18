/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graceful.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarolei <pcarolei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 06:12:20 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/04 15:05:31 by pcarolei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRACEFUL_H
# define GRACEFUL_H

# include <stdlib.h>
# include "libft.h"

/**
 *	Макросы ошибок
 */
# define ERR_OPEN_MSG			"Can't open."
# define ERR_READ_MSG			"Can't read."
# define ERR_MEM_MSG			"Memory error."
# define ERR_INVALID_DEFINE_MSG	"Invalid defines."

void	graceful(size_t reason, const char *msg);
void	check(_Bool status, size_t reason, const char *msg);

#endif
