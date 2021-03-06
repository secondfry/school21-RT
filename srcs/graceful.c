/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graceful.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 06:30:54 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/07/18 16:31:07 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graceful.h"

/**
 *	Функция, выводящая ошибку и завершающая работу приложения
 *	@param reason Код ошибки
 *	@param msg Сообщение об ошибке
 */
void	graceful(size_t reason, const char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(reason);
}

void	check(_Bool status, size_t reason, const char *msg)
/**
 *	Функция, проверяющее логическое условие
 *	Если условие ложно, то выводит ошибку и завершает работу приложения
 *	@param status Условие
 *	@param reason Код ошибки
 *	@param msg Сообщение об ошибке
 */
{
	if (!status)
		return ;
	graceful(reason, msg);
}
