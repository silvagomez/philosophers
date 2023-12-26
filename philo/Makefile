# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsilva-g <dsilva-g@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 21:53:56 by dsilva-g          #+#    #+#              #
#    Updated: 2023/12/26 13:29:51 by dsilva-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	philo
NAME_BONUS		:=	philo_bonus

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

CC				:=	cc
#CFLAGS			:=	-Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS			:=	-Wall -Wextra -Werror -fsanitize=thread -g3
#CFLAGS			:=	-Wall -Wextra -Werror -g

INCLUDE_PATH	:=	include/
INCLUDE			:=	$(INCLUDE_PATH)philosophers.h

SRC_PATH		:=	src/
SRC				:=	\
					main.c \
					error.c \
					validate.c \
					utils_1.c \
					utils_2.c \
					philosophers.c \
					setting_data.c \
					mutexing.c \
					threading.c \
					philosopher_routine.c \
					waiter_routine.c

SRC				:=	$(SRC:%=$(SRC_PATH)%)

OBJ_PATH		:=	obj/
OBJ				:=	$(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

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
					@echo -e "$(MAGENTA)Files of $(NAME)$(GREEN) compiled!$(WHITE)"

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

bonus			:	
					@echo -e "$(MAGENTA)Go to the philo_bonus directory$(WHITE)"

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
