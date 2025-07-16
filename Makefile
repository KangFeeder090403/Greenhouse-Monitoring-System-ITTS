# Enhanced Makefile for Greenhouse Monitoring System ITTS v2.0
# Supports multiple compilers and build configurations

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c99 -O2
DEBUG_FLAGS = -g -DDEBUG
TARGET = greenhouse_system
ADVANCED_TARGET = greenhouse_advanced
SOURCES = greenhouse_monitoring.c
ADVANCED_SOURCES = greenhouse_system_advanced.c

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m # No Color

# Default target
all: $(TARGET) $(ADVANCED_TARGET)
	@echo "$(GREEN)✅ Build completed successfully!$(NC)"
	@echo "$(CYAN)🌱 Run with: ./$(TARGET) or ./$(ADVANCED_TARGET)$(NC)"

# Compile basic version
$(TARGET): $(SOURCES)
	@echo "$(YELLOW)🔨 Compiling basic greenhouse monitoring system...$(NC)"
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
	@echo "$(GREEN)✅ Basic version compiled: $(TARGET)$(NC)"

# Compile advanced version
$(ADVANCED_TARGET): $(ADVANCED_SOURCES)
	@echo "$(YELLOW)🔨 Compiling advanced greenhouse monitoring system...$(NC)"
	$(CC) $(CFLAGS) -o $(ADVANCED_TARGET) $(ADVANCED_SOURCES)
	@echo "$(GREEN)✅ Advanced version compiled: $(ADVANCED_TARGET)$(NC)"

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET) $(ADVANCED_TARGET)
	@echo "$(PURPLE)🐛 Debug builds completed$(NC)"

# Run basic version
run: $(TARGET)
	@echo "$(CYAN)🚀 Starting basic greenhouse monitoring system...$(NC)"
	./$(TARGET)

# Run advanced version  
run-advanced: $(ADVANCED_TARGET)
	@echo "$(CYAN)🚀 Starting advanced greenhouse monitoring system...$(NC)"
	./$(ADVANCED_TARGET)

# Clean compiled files
clean:
	@echo "$(RED)🧹 Cleaning build files...$(NC)"
	rm -f $(TARGET) $(ADVANCED_TARGET) $(TARGET).exe $(ADVANCED_TARGET).exe
	rm -f *.o *.obj
	@echo "$(GREEN)✅ Clean completed$(NC)"

# Clean data files (use with caution!)
clean-data:
	@echo "$(RED)⚠️  Cleaning data files...$(NC)"
	rm -f equipment_inventory.txt last_watered_date.txt plant_data.txt alerts.txt monitoring_log.txt
	@echo "$(YELLOW)🗑️  Data files removed$(NC)"

# Install to system (Unix/Linux/macOS)
install: $(ADVANCED_TARGET)
	@echo "$(BLUE)📦 Installing to system...$(NC)"
	sudo cp $(ADVANCED_TARGET) /usr/local/bin/greenhouse-monitor
	@echo "$(GREEN)✅ Installed as 'greenhouse-monitor'$(NC)"

# Show help
help:
	@echo "$(CYAN)🌱 Greenhouse Monitoring System - Build Help$(NC)"
	@echo ""
	@echo "$(YELLOW)Available targets:$(NC)"
	@echo "  $(GREEN)all$(NC)              - Build both basic and advanced versions"
	@echo "  $(GREEN)$(TARGET)$(NC)   - Build basic version only"
	@echo "  $(GREEN)$(ADVANCED_TARGET)$(NC) - Build advanced version only"
	@echo "  $(GREEN)debug$(NC)            - Build with debug symbols"
	@echo "  $(GREEN)run$(NC)              - Run basic version"
	@echo "  $(GREEN)run-advanced$(NC)     - Run advanced version"
	@echo "  $(GREEN)clean$(NC)            - Remove compiled files"
	@echo "  $(GREEN)clean-data$(NC)       - Remove all data files (⚠️  destructive)"
	@echo "  $(GREEN)install$(NC)          - Install to system (requires sudo)"
	@echo "  $(GREEN)help$(NC)             - Show this help"

.PHONY: all clean clean-data run run-advanced debug install help
