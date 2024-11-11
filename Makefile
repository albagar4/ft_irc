#Variables

NAME = ircserv
INCLUDE = include/
SRC_DIR = src/
OBJ_DIR = obj/
CC = clang++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g
AR = ar rcs

# Colors

DEF_COLOR = $(shell tput sgr0)
GRAY = $(shell tput setaf 0)
RED = $(shell tput setaf 1)
GREEN = $(shell tput setaf 2)
YELLOW = $(shell tput setaf 3)
BLUE = $(shell tput setaf 4)
MAGENTA = $(shell tput setaf 5)
CYAN = $(shell tput setaf 6)
WHITE = $(shell tput setaf 7)

#Sources
	
SRC_FILES = main _aux Server Client Channel bot \
						commands/cap commands/user commands/nick commands/pass commands/join commands/invite commands/kick commands/quit commands/mode commands/topic commands/privmsg commands/part

SRC = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJF = .cache_exists

###

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) -I./$(INCLUDE) $(CFLAGS) $(OBJ) -o $(NAME)
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) -I./$(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/commands
			@touch $(OBJF)

clean:
			@rm $(OBJF)
			@rm -rf $(OBJ_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		
			@rm $(OBJF)
			@rm -rf $(OBJ_DIR)
			@rm -f $(NAME)
			@echo "$(BLUE)$(NAME) executable cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(MAGENTA)$(NAME) recompiled!$(DEF_COLOR)"

.PHONY: all clean fclean re
