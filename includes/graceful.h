/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graceful.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 06:12:20 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/06 21:46:12 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRACEFUL_H
# define GRACEFUL_H

# include <stdlib.h>
# include "libft.h"

# define ERR_OPEN_MSG			"Can't open."
# define ERR_READ_MSG			"Can't read."
# define ERR_MEM_MSG			"Memory error."
# define ERR_INVALID_DEFINE_MSG	"Invalid defines."

void	graceful(size_t reason, const char *msg);
void	check(_Bool status, size_t reason, const char *msg);

#endif
