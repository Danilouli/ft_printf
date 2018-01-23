/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 17:23:19 by dsaadia           #+#    #+#             */
/*   Updated: 2018/01/23 14:16:51 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "ft_printf.h"

static void ft_printf_print_arg(int fd ,int dg[4], t_conv convs[17], va_list ap)
{
	wchar_t *res;

	res = convs[dg[2]].convertor(PFARGS(value), ap, &(dg[1]));
	((dg[2] = -1) && ((dg[0] = dg[0] + PFARGS(len)) >= 0) &&
	((dg[3] = dg[3] + (dg[1])) >= 0) && (ft_strchr("SC",PFARGS(type)) ||
	(ft_strchr("sc",PFARGS(type)) && ft_strchr(PFARGS(value),'l')))) ?
	ft_putwstr_fd(res, fd) : ft_putstr_fd((char*)res, fd);
}

static int ft_printf_loop(int fd, const char *fmt, va_list ap, t_conv convs[17])
{
	int dg[4];

	dg[0] = 0;
	dg[1] = 0;
	dg[2] = -1;
	dg[3] = 0;
	while (fmt[dg[0]])
	{
		if (g_pfargs && dg[0] == PFARGS(index))
		{
			while (++dg[2] < 17)
			{
				if (PFARGS(type) == convs[dg[2]].sign)
				{
					ft_printf_print_arg(fd, dg, convs, ap);
					break;
				}
			}
			g_pfargs = g_pfargs->next;
		}
		else if(dg[3]++ >= 0)
			ft_putchar_fd(fmt[dg[0]++], fd);
	}
	return (dg[3]);
}

static int ft_do_printf_loop(int fd, const char *format, va_list ap)
{
	t_conv convertors[] =
	{
		{'d', &numconv},
		{'i', &numconv},
		{'u', &numconv},
		{'U', &numconv},
		{'D', &numconv},
		{'x', &numconv},
		{'X', &numconv},
		{'o', &numconv},
		{'O', &numconv},
		{'b', &numconv},
		{'B', &numconv},
		{'p', &numconv},
		{'c', &charconv},
		{'C', &wcharconv},
		{'s', &strconv},
		{'S', &wstrconv},
		{'%', &perconv}
	};
	return (ft_printf_loop(fd, format, ap, convertors));
}

int ft_fprintf(int fd, const char *format, ...)
{
	int formlen = 0;
	va_list(ap);
	va_start(ap, format);

	if(!count_printf_args(format))
		return (-1);
	formlen = ft_do_printf_loop(fd, format, ap);
	va_end(ap);
	return (formlen);
}

int ft_printf(const char *format, ...)
{
	int formlen = 0;
	va_list(ap);
	va_start(ap, format);

	if(!count_printf_args(format))
		return (-1);
	formlen = ft_do_printf_loop(0, format, ap);
	va_end(ap);
	return (formlen);
}
