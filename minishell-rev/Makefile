PROGRAM		= minishell

SYSTEM		= $(shell uname -s)

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g

HOME_DIR	:= $(shell echo ~)

ifeq ($(SYSTEM), Linux)
	CFLAGS	+= -lreadline
else ifeq ($(SYSTEM), Darwin)
	CFLAGS	+= -I$(HOME_DIR)/.brew/opt/readline/include
endif

ifeq ($(SYSTEM), Darwin)
	LDFLAGS		= -L$(HOME_DIR)/.brew/opt/readline/lib -lreadline
endif

REMOVE		= rm -rf

SRCDIR		= src/
OBJDIR		= obj/
MAIN_DIR	= $(SRCDIR)main/
PARS_DIR	= $(SRCDIR)pars/
EXEC_DIR	= $(SRCDIR)exec/
UTIL_DIR	= $(SRCDIR)util/
BLTN_DIR	= $(SRCDIR)bltn/

MAIN_SRC	= environment.c \
			  signal.c \
			  main.c 
PARS_SRC	= token3.c \
			  token2.c \
			  token1.c \
			  parser3.c \
			  parser2.c \
			  parser1.c
EXEC_SRC	= exit.c \
			  exec7.c \
			  exec6.c \
			  exec5.c \
			  exec4.c \
			  exec3.c \
			  exec2.c \
			  exec1.c
UTIL_SRC	= list.c \
		  strutil1.c \
		  strutil2.c
BLTN_SRC	= cd_util.c \
			  cd.c \
			  env.c \
			  pwd.c \
			  echo.c \
			  unset.c \
			  export.c
SRCFILES	= $(addprefix $(MAIN_DIR), $(MAIN_SRC)) \
			  $(addprefix $(PARS_DIR), $(PARS_SRC)) \
			  $(addprefix $(EXEC_DIR), $(EXEC_SRC)) \
			  $(addprefix $(UTIL_DIR), $(UTIL_SRC)) \
			  $(addprefix $(BLTN_DIR), $(BLTN_SRC)) 
OBJFILES	= $(SRCFILES:.c=.o)

.PHONY:	all clean fclean re

all: $(PROGRAM)

$(PROGRAM): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJFILES) -o $(PROGRAM)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(REMOVE) $(OBJFILES)

fclean: clean
	$(REMOVE) $(PROGRAM)

re: fclean all
