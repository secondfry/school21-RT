/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:54:36 by oadhesiv          #+#    #+#             */
/*   Updated: 2021/09/05 14:07:07 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static void	route(const char *format, size_t *i, va_list *ap)
{
	if (format[*i + 1] == 'd')
		ft_putnbr(va_arg(*ap, int));
	if (format[*i + 1] == 's')
		ft_putstr(va_arg(*ap, char *));
	if (!ft_strncmp(format + *i + 1, "zu", 2))
	{
		ft_putstr(ft_ltoa_static(va_arg(*ap, long)));
		*i = *i + 1;
	}
	*i = *i + 1;
}

void	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			ft_putchar(format[i]);
		else
			route(format, &i, &ap);
		i++;
	}
	va_end(ap);
}
