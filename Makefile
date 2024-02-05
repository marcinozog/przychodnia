TARGET = przychodnia
BUILD_DIR = build
SRCS = main.cpp przychodnia.cpp connectorDB.cpp response.cpp
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.cpp=.o)))
GCC = g++
LFLAGS = -l sqlite3

all: $(OBJS)
	$(GCC) $(OBJS) $(LFLAGS) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp
	$(GCC) -c $< -o $@

clean:
	rm $(BUILD_DIR)/*.o $(TARGET)