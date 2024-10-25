# **************************************************************************** #
#                                  CONFIGURATION                               #
# **************************************************************************** #

# Nom de l'exécutable (la librairie statique)
NAME        := libftprintf.a

# Compilateur et options de compilation
CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# Commande pour créer l'archive de la librairie statique
AR          := ar rcs

# Commandes pour nettoyer
RM          := rm -f



# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

# Liste des fichiers sources (sans les bonus)
SRCS        :=

# Liste des fichiers sources pour les bonus
SRCS_BONUS  :=

# Transformation des fichiers sources en fichiers objets
OBJS        := $(SRCS:.c=.o)
OBJS_BONUS  := $(SRCS_BONUS:.c=.o)

# **************************************************************************** #
#                                 RÈGLES                                       #
# **************************************************************************** #

# Règle par défaut : compilation de la lib
all: $(NAME)

# Compilation de la librairie
$(NAME): $(OBJS)
	@echo " "
	@echo ">>>>> Création de $(NAME) ... <<<<<"
	@echo " "
	$(AR) $(NAME) $(OBJS)
	@echo " "
	@echo ">>>>> $(NAME) créé avec succès. <<<<<"
	@echo " "

# Compilation des fichiers bonus
bonus: $(OBJS) $(OBJS_BONUS)
	@echo " "
	@echo ">>>>> Ajout des bonus à $(NAME)... <<<<<"
	@echo " "
	$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)
	@echo " "
	@echo ">>>>> Bonus ajoutés avec succès. <<<<<"
	@echo " "

# Compilation des fichiers objets
%.o: %.c
	@echo ">>>>> Compilation de $< ... <<<<<"
	$(CC) $(CFLAGS) -c $< -o $@


# **************************************************************************** #
#                                 NETTOYAGE                                    #
# **************************************************************************** #

# Suppression des fichiers objets
clean:
	@echo " "
	@echo ">>>>> Nettoyage des fichiers objets... <<<<<"
	@echo " "
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo " "
	@echo ">>>>> Nettoyage terminé. <<<<<"
	@echo " "

# Suppression des fichiers objets et de la librairie
fclean: clean
	@echo " "
	@echo ">>>>> Suppression de $(NAME)... <<<<<"
	@echo " "
	$(RM) $(NAME)
	@echo " "
	@echo ">>>>> Suppression terminée. <<<<<"
	@echo " "

# Recompile tout depuis le début
re: fclean all

# **************************************************************************** #
#                                 UTILITAIRES                                  #
# **************************************************************************** #

# Indique que ces règles ne correspondent pas à des fichiers
.PHONY: all clean fclean re bonus
