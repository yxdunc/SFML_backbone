CC = g++
MODE=release
CMODE = -O3
ifeq ($(MODE), debug)
	CMODE = -g
endif
CFLAGS = -Werror -Wextra -Wall $(CMODE) $(CPP11)
CPP11 = -std=c++11
TARGET = rename_me_in_the_Makefile_rguignar
SRC_DIR = ./src
INCLUDE_DIR = ./includes
BUILD_DIR = ./builds

SRC = main.cpp

ifeq ($(MODE), debug)
	COLOR_ID = \033[0;32m
else
	COLOR_ID = \033[0;34m
endif

COLOR_NO = \033[0m
OBJS = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
INCLUDES = -I$(INCLUDE_DIR) -I/usr/local/include
LIBS = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system 

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	@echo " - Building $(COLOR_ID)$(TARGET)$(COLOR_NO)..."
	@$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

$(addprefix $(BUILD_DIR)/, %.o): $(addprefix $(SRC_DIR)/, %.cpp)
	@echo " - Building: $(COLOR_ID)$(@:.cpp=.o)$(COLOR_NO)..."
	@$(CC)  $(INCLUDES) $(CFLAGS)  -c $< -o $@ 

re: fclean $(BUILD_DIR) $(TARGET)

clean:
	@echo " - Removing objects files:"
	@rm -fr $(OBJS)

fclean: clean
	@echo " - Removing $(COLOR_ID)$(TARGET)$(COLOR_NO)..."
	@rm -rf $(TARGET)
	@echo " - Removing $(COLOR_ID)$(BUILD_DIR)$(COLOR_NO)..."
	@rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	@echo " - Creating build directory '$(COLOR_ID)$(BUILD_DIR)$(COLOR_NO)'..."
	@mkdir $(BUILD_DIR)
