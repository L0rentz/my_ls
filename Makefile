##
## EPITECH PROJECT, 2019
## PSU_my_ls_2019
## File description:
## Makefile
##

NAME	=	my_ls

SRCS	=	main.c \
		my_getopt.c \
		my_utils.c \
		push_pop_clear_list.c \
		create_print_list.c \
		sort_list.c \
		no_arg_no_flags.c \
		no_arg_no_flags2.c \
		d_flag.c \
		l_flag.c \
		l_flag2.c \
		l_flag3.c \
		l_flag_prints.c \
		t_flag.c \

OBJS	=	$(SRCS:.c=.o)

CFLAGS =	-lmy -L./ -Wall -Wextra -g3 -O2

CALLMAKE =	cd my_printf/ && make

all:	$(NAME)

$(NAME):	$(OBJS) $(SRCS)
		$(CALLMAKE)
		gcc -o $(NAME) $(OBJS) $(CFLAGS)
clean:
		rm $(OBJS)
		cd my_printf/ && make clean
fclean:
		rm $(NAME)
		rm $(OBJS)
		cd my_printf/ && make fclean

re: fclean all
