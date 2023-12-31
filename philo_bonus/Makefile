# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 21:53:56 by dsilva-g          #+#    #+#              #
#    Updated: 2023/12/26 13:52:47 by dsilva-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS		:=	philo_bonus

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

CC				:=	cc
#CFLAGS			:=	-Wall -Wextra -Werror -fsanitize=address -g3
#CFLAGS			:=	-Wall -Wextra -Werror -fsanitize=thread -g3
CFLAGS			:=	-Wall -Wextra -Werror -g

INCLUDE_BPATH	:=	include_bonus/
INCLUDE_B		:=	$(INCLUDE_BPATH)philophoser_bonus.h

SRC_BPATH		:=	src_bonus/
SRC_BONUS		:=	\
					main.c \
					error_bonus.c \
					validate_bonus.c \
					utils_bonus_1.c \
					utils_bonus_2.c \
					philosophers_bonus.c \
					setting_data_bonus.c \
					philosopher_routine_bonus.c \
					waiter_routine_bonus.c

SRC_BONUS		:=	$(SRC_BONUS:%=$(SRC_BPATH)%)

OBJ_BPATH		:=	obj_bonus/
OBJ_BONUS		:=	$(SRC_BONUS:$(SRC_BPATH)%.c=$(OBJ_BPATH)%.o)

#------------------------------------------------------------------------------#
#   UTENSILS                                                                   #
#------------------------------------------------------------------------------#

RM				:=	rm
RMFLAG			:=	-fr

DIR_DUP			=	mkdir -p $(@D)

#------------------------------------------------------------------------------#
#   RECIPES                                                                    #
#------------------------------------------------------------------------------#

all				:	$(NAME_BONUS)

bonus			:	all

$(NAME_BONUS)	:	$(OBJ_BONUS)
					$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)
					@echo -e "$(MAGENTA)Files of $(NAME_BONUS)$(GREEN) compiled!$(WHITE)"


$(OBJ_BPATH)%.o	:	$(SRC_BPATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_BPATH) -c $< -o $@

clean			:
					$(RM) $(RMFLAG) $(OBJ_PATH)
					$(RM) $(RMFLAG) $(OBJ_BPATH)
					@echo -e "$(MAGENTA)Removing $(NAME_BONUS) files... $(GREEN)done!$(WHITE)"

fclean			:	clean
					$(RM) $(RMFLAG) $(NAME)
					$(RM) $(RMFLAG) $(NAME_BONUS)
					@echo -e "$(MAGENTA)Removing $(NAME_BONUS) $(GREEN)done!$(WHITE)"

re				:	fclean all

norm			:
					norminette $(SRC_PATH) $(INCLUDE_PATH)

#------------------------------------------------------------------------------#
#   SPEC                                                                       #
#------------------------------------------------------------------------------#

.PHONY			:	all clean fclean re bonus

#------------------------------------------------------------------------------#
#   COLORS                                                                     #
#------------------------------------------------------------------------------#

GREEN			:=	\033[92m
BLUE			:=	\033[94m
MAGENTA			:=	\033[95m
WHITE			:=	\033[97m

#********************************************************************* END ****#
