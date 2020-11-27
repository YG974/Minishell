/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:13:36 by pcoureau          #+#    #+#             */
/*   Updated: 2020/01/26 19:40:26 by pcoureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

typedef	struct	s_ftprintf
{
	char		*str_final;
	char		*tmp;
	char		*s;
	void		*arg_content;
	int			l_align;
	int			star;
	int			star_activ;
	int			zero;
	int			zero_activ;
	int			dot;
	int			dot_activ;
	int			neg;
	int			strlenfinal;
	int			len;
}				t_ftprintf;

char			*ft_joina(char *tampostr, char *tampospace, t_ftprintf *mas);
void			*ft_nn(char *ts, t_ftprintf *mas, int len, unsigned long pnum);
void			ft_printd_m(t_ftprintf *mas);
void			ft_printd_dot(int i, t_ftprintf *mas);
void			ft_printd_tmps(char *tampostr, t_ftprintf *mas);
void			ft_printd_star(int i, t_ftprintf *mas);
void			*ft_convp(va_list av, t_ftprintf *mas);
void			*ft_convc(va_list av, t_ftprintf *mas);
void			*ft_convs(va_list av, t_ftprintf *mas);
void			*ft_convu(va_list av, t_ftprintf *mas);
void			*ft_convd(va_list av, t_ftprintf *mas);
void			*ft_convx(va_list av, t_ftprintf *mas);
void			*ft_convxx(va_list av, t_ftprintf *mas);
void			*ft_convprc(t_ftprintf *mas);
int				ft_printf(const char *str, ...);
char			*ft_itoad(int n);
char			*ft_itoau(unsigned int n);
char			*ft_itoax(unsigned int n, char *base);
int				ft_flagalign(t_ftprintf *mas, const char *str, int n);
int				ft_flagzero(t_ftprintf *mas, const char *str, int n);
int				ft_flagwn(t_ftprintf *mas, const char *str, int n);
int				ft_flagws(va_list av, t_ftprintf *mas, const char *str, int n);
int				ft_flagdot(va_list av, t_ftprintf *mas, const char *str, int n);
int				ft_chkflgs(va_list av, t_ftprintf *mas, const char *str, int n);
void			*ft_cnvrt(va_list av, t_ftprintf *mas, const char *str, int n);
void			*ft_getstr(const char *str, t_ftprintf *mas, va_list av);
char			*ft_itoap(unsigned long n, char *base);

#endif
