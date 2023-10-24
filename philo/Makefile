# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 21:53:56 by dsilva-g          #+#    #+#              #
#    Updated: 2023/10/24 23:45:13 by dsilva-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	philo
NAME_BONUS		:=	philo_bonus

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

CC				:=	cc
#CFLAGS			:=	-Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS			:=	-Wall -Wextra -Werror -g

INCLUDE_PATH	:=	include/
INCLUDE			:=	$(INCLUDE_PATH)philosophers.h

INCLUDE_BPATH	:=	include_bonus/
INCLUDE_B		:=	$(INCLUDE_BPATH)philophoser_bonus.h

SRC_PATH		:=	src/
SRC				:=	\
					main.c \
					error.c \
					validate.c \
					philo_utils_1.c

SRC				:=	$(SRC:%=$(SRC_PATH)%)

SRC_BPATH		:=	src_bonus/
SRC_BONUS		:=	\
					main_bonus.c \
					error_bonus.c \
					validate_bonus.c 

SRC_BONUS		:=	$(SRC_BONUS:%=$(SRC_BPATH)%)

OBJ_PATH		:=	obj/
OBJ				:=	$(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

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

all				:	$(NAME)

$(NAME)			:	$(OBJ) 
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
					@echo -e "$(MAGENTA)File $(NAME)$(GREEN) compiled!$(WHITE)"

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

bonus			:	$(NAME_BONUS)

$(NAME_BONUS)	:	$(OBJ_BONUS)
					$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)
					@echo -e "$(MAGENTA)File $(NAME_BONUS)$(GREEN) compiled!$(WHITE)"


$(OBJ_BPATH)%.o	:	$(SRC_BPATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_BPATH) -c $< -o $@

clean			:
					$(RM) $(RMFLAG) $(OBJ_PATH)
					$(RM) $(RMFLAG) $(OBJ_BPATH)
					@echo -e "$(MAGENTA)Removing fdf files... $(GREEN)done!$(WHITE)"

fclean			:	clean
					$(RM) $(RMFLAG) $(NAME)
					$(RM) $(RMFLAG) $(NAME_BONUS)
					@echo -e "$(MAGENTA)Removing $(NAME) $(GREEN)done!$(WHITE)"

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
