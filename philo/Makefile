.DEFAULT_GOAL : all

NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
RM			=	rm -rf

SRC	=	src/main.c \
		src/check_args.c \
		src/diner_routine.c \
		src/handle_errors.c \
		src/handle_mutex_and_thread.c \
		src/init_simulation.c \
		src/init_struct.c \
		src/monitor.c \
		src/mutex_access.c \
		src/struct_allocation.c \
		src/time.c \
		src/utils.c

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