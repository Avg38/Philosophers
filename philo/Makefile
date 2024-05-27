.DEFAULT_GOAL : all

NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
RM			=	rm -rf

SRC	=	main.c \
		check_args.c \
		diner_routine.c \
		handle_errors.c \
		handle_mutex_and_thread.c \
		init_simulation.c \
		init_struct.c \
		monitor.c \
		mutex_access.c \
		struct_allocation.c \
		time.c \
		utils.c

OBJS	=	${SRC:.c=.o}

RESET	= \033[0K\r\c
RESET_COLOR	= \033[0m
OK	= [\033[32mOK\033[0m]
RED	= \033[31m
GREEN	= \033[32m

all :  $(NAME)

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} -o $@ $^
	@echo "$(OK) $(NAME) compiled"

%.o: %.c  philo.h
	@echo "[..] $(NAME)... compiling $*.c\r\c"
	@${CC} ${CFLAGS} -c $< -o $@
	@echo "$(RESET)"
	
clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

NB_ERRORS = $(shell norminette | grep Error: | wc -l)

norm :
	@if norminette | grep -v OK; then \
		echo "$(RED)$(NB_ERRORS) norm issues$(RESET_COLOR)"; \
	else \
		echo "$(OK) No norm errors left"; \
	fi

.PHONY: all clean fclean re norm