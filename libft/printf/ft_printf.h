/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:24:49 by zfarah            #+#    #+#             */
/*   Updated: 2025/06/02 13:05:39 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft.h"

// main function
int		ft_printf(const char *str, ...);

// format handlers
int		print_c(int c);
int		print_str(char *str, bool should_free);
int		print_ptr(void *ptr);
int		print_int(int num);
int		print_unsigned_int(unsigned int num);
int		print_hex_case(unsigned long num, bool capitalized);
void	rev_hex_str(char *str);

#endif
