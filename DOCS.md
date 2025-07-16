# 🌱 Greenhouse Monitoring System ITTS - Project Documentation

## 📖 Table of Contents
1. [Project Overview](#project-overview)
2. [Features Comparison](#features-comparison)
3. [Installation Guide](#installation-guide)
4. [Usage Instructions](#usage-instructions)
5. [File Structure](#file-structure)
6. [Development Notes](#development-notes)
7. [API Reference](#api-reference)
8. [Troubleshooting](#troubleshooting)

## 🎯 Project Overview

The Greenhouse Monitoring System ITTS is a comprehensive C-based application designed to help greenhouse owners and operators monitor plant health, manage equipment inventory, and maintain optimal growing conditions.

### 🌟 Key Improvements Made

**Original Issues Fixed:**
- ❌ **Case 2 Missing**: Fixed broken menu structure in original code
- ❌ **Logic Error**: Corrected equipment menu loop condition (`!= 2` instead of `!= 3`)
- ❌ **Poor Error Handling**: Added comprehensive input validation
- ❌ **Limited Features**: Basic plant monitoring only
- ❌ **No Data Persistence**: Minimal file operations

**New Enhancements:**
- ✅ **Complete Menu System**: All menu options functional
- ✅ **Advanced Health Monitoring**: Multi-parameter plant assessment  
- ✅ **Smart Alert System**: Automated notifications and warnings
- ✅ **Comprehensive Inventory**: Full equipment management
- ✅ **Data Analytics**: Statistics and reporting features
- ✅ **Cross-Platform Support**: Windows, Linux, macOS compatibility
- ✅ **Professional UI**: Colorful, user-friendly interface
- ✅ **Robust Error Handling**: Input validation and file error management

## 📊 Features Comparison

| Feature | Original Version | Enhanced Version |
|---------|-----------------|------------------|
| Menu System | ❌ Broken (Case 2 missing) | ✅ Complete with 5 main sections |
| Plant Health | ⚠️ Basic (random health) | ✅ Multi-parameter analysis |
| Watering Tracking | ✅ Basic date tracking | ✅ Enhanced with plant names |
| Inventory Management | ⚠️ Basic add/view | ✅ Full CRUD operations |
| Data Validation | ❌ None | ✅ Comprehensive validation |
| Error Handling | ❌ Minimal | ✅ Robust error management |
| User Interface | ⚠️ Plain text | ✅ Colorful with emojis |
| Alert System | ❌ None | ✅ Smart notifications |
| Statistics | ❌ None | ✅ Analytics and reporting |
| Search Functions | ❌ None | ✅ Advanced search capabilities |
| Data Export | ❌ None | ✅ Export/Import/Backup |
| Cross-Platform | ⚠️ Limited | ✅ Full support |

## 🛠️ Installation Guide

### Prerequisites
- **GCC Compiler** (C99 standard support)
- **Windows**: MinGW-w64, MSYS2, or Visual Studio
- **Linux**: GCC package (`sudo apt install gcc` on Ubuntu)
- **macOS**: Xcode Command Line Tools or Homebrew GCC

### Quick Installation

#### Windows (Using build.bat)
```batch
# Double-click build.bat or run in Command Prompt
build.bat

# Or manually compile:
gcc -Wall -Wextra -std=c99 -O2 -o greenhouse_advanced.exe greenhouse_system_advanced.c
```

#### Linux/macOS (Using Makefile)
```bash
# Build everything
make all

# Build and run advanced version
make run-advanced

# Build with debug symbols
make debug

# Install to system
sudo make install
```

#### Manual Compilation
```bash
# Basic version
gcc -Wall -Wextra -std=c99 -O2 -o greenhouse_system greenhouse_monitoring.c

# Advanced version  
gcc -Wall -Wextra -std=c99 -O2 -o greenhouse_advanced greenhouse_system_advanced.c
```

## 🚀 Usage Instructions

### First Time Setup
1. **Compile** the program using preferred method above
2. **Run** the advanced version: `./greenhouse_advanced` (Linux/macOS) or `greenhouse_advanced.exe` (Windows)
3. **Explore** the welcome screen and main menu
4. **Add** some initial plant data to get started

### Main Menu Navigation

#### 🌿 Plants Management (Option 1)
- **Health Monitoring**: Real-time environmental assessment
- **Watering Records**: Track when plants were watered
- **Plant Database**: Add, view, and manage plant information
- **Statistics**: Analyze growth trends and conditions
- **Care Reminders**: Get maintenance suggestions

#### 🔧 Equipment Management (Option 2)  
- **Inventory Tracking**: Add, view, search equipment
- **Stock Management**: Monitor quantities and prices
- **Low Stock Alerts**: Automatic warnings for supplies
- **Reports**: Generate detailed inventory summaries
- **Categories**: Organize equipment by type

#### 🔔 Alerts & Notifications (Option 3)
- **View Alerts**: Check system notifications
- **Priority Levels**: High, Medium, Low priority alerts
- **Alert Types**: Health, Inventory, Watering, System alerts
- **Timestamp Tracking**: When alerts were generated

#### ⚙️ System Settings (Option 4)
- **Data Management**: Export, Import, Backup functions
- **System Maintenance**: Clear alerts, reset data
- **About Information**: Version and feature details

### 📊 Understanding Health Scores

The system calculates plant health based on four parameters:

| Parameter | Optimal Range | Scoring Impact |
|-----------|--------------|----------------|
| 🌡️ Temperature | 20-28°C | 30 points max |
| 💨 Humidity | 50-70% | 25 points max |
| 💧 Soil Moisture | 40-70% | 25 points max |
| ☀️ Light Level | 500-1500 lux | 20 points max |

**Health Score Interpretation:**
- **85-100**: 🌟 Excellent - Plants thriving
- **70-84**: 😊 Good - Minor improvements needed  
- **50-69**: 😐 Fair - Some attention required
- **0-49**: 😟 Poor - Immediate action needed

### 💡 Best Practices

1. **Regular Monitoring**: Check plant health daily
2. **Consistent Watering**: Update watering records after each session
3. **Inventory Management**: Keep equipment stock levels current
4. **Alert Response**: Address high-priority alerts promptly
5. **Data Backup**: Export data regularly for safety
6. **Environmental Control**: Maintain optimal growing conditions

## 📁 File Structure

### Source Code Files
```
greenhouse_monitoring.c          # Basic version (original improved)
greenhouse_system_advanced.c     # Advanced version (full features)
```

### Build Files
```
Makefile                        # Linux/macOS build configuration
build.bat                       # Windows build script
```

### Data Files (Auto-Generated)
```
equipment_inventory.txt         # Equipment and supplies database
last_watered_date.txt          # Watering history records
plant_data.txt                 # Plant information and statistics
alerts.txt                     # System notifications
monitoring_log.txt             # Environmental monitoring history
```

### Documentation
```
README.md                      # Main project documentation
DOCS.md                        # This detailed documentation
```

## 👨‍💻 Development Notes

### Code Architecture

#### Function Organization
```c
// Main Program Flow
main() -> Menu Systems -> Feature Functions -> Utility Functions

// Key Modules
- Menu Display Functions (displayMainMenu, displayPlantsMenu, etc.)
- Plant Management (plantHealthMonitoring, addPlantData, etc.)  
- Equipment Management (checkInventory, updateInventory, etc.)
- Alert System (addAlert, checkAlerts, viewAlerts)
- Utilities (getCurrentDate, validateDate, displayHeader, etc.)
```

#### Data Structures
```c
typedef struct {
    char plantName[MAX_STRING_LENGTH];
    char plantType[MAX_STRING_LENGTH];
    float temperature;
    float humidity;
    float soilMoisture;
    float lightLevel;
    char lastWatered[MAX_STRING_LENGTH];
    char plantedDate[MAX_STRING_LENGTH];
    int healthScore;
} PlantData;

typedef struct {
    char name[MAX_STRING_LENGTH];
    int quantity;
    char date[MAX_STRING_LENGTH];
    float price;
    char category[MAX_STRING_LENGTH];
    int minStock;
} InventoryItem;

typedef struct {
    char alertType[MAX_STRING_LENGTH];
    char message[MAX_STRING_LENGTH];
    char timestamp[MAX_STRING_LENGTH];
    int priority; // 1=Low, 2=Medium, 3=High
} Alert;
```

### Programming Techniques Used

1. **Modular Design**: Functions organized by feature area
2. **Error Handling**: Comprehensive input validation and file error checking
3. **Memory Safety**: Proper string handling with bounds checking
4. **Cross-Platform**: Conditional compilation for different operating systems
5. **User Experience**: Clear feedback, colorful output, intuitive navigation
6. **Data Persistence**: File-based storage with human-readable formats
7. **Algorithm Design**: Health scoring system with weighted parameters

### Compilation Flags Explained
```bash
-Wall          # Enable all common warnings
-Wextra        # Enable extra warning flags
-std=c99       # Use C99 standard (modern C features)
-O2            # Optimization level 2 (performance)
-g             # Include debug symbols (debug builds)
```

## 🔧 API Reference

### Core Functions

#### Display Functions
```c
void displayMainMenu()           # Show main menu options
void displayPlantsMenu()         # Show plant management options  
void displayEquipmentMenu()      # Show equipment management options
void displayHeader(const char*)  # Display formatted section header
void clearScreen()               # Clear terminal screen
```

#### Plant Management
```c
void plantHealthMonitoring()     # Perform environmental assessment
void addPlantData()              # Add new plant to database
void viewPlantStatistics()       # Show plant analytics
void updateLastWateredDate()     # Update watering records
```

#### Equipment Management  
```c
void checkInventory()            # Display inventory list
void updateInventory()           # Add/update equipment
void searchInventoryItem()       # Search equipment database
void generateInventoryReport()   # Create detailed reports
```

#### Alert System
```c
void addAlert(type, msg, priority) # Create new alert
void checkAlerts()               # Display all alerts
void viewAlerts()                # Browse alert history
```

#### Utility Functions
```c
void getCurrentDate(char*)       # Get current date string
int validateDate(const char*)    # Validate date format
float generateSensorReading(min,max) # Simulate sensor data
int calculateHealthScore(...)    # Compute plant health score
void trimString(char*)           # Remove whitespace from string
```

## 🚨 Troubleshooting

### Common Issues and Solutions

#### Compilation Problems

**Issue**: `gcc: command not found`
```bash
# Linux (Ubuntu/Debian)
sudo apt update && sudo apt install gcc

# Linux (CentOS/RHEL)  
sudo yum install gcc

# macOS
xcode-select --install

# Windows
# Install MinGW-w64 or MSYS2
```

**Issue**: `Error: undefined reference to 'function'`
```bash
# Make sure all source files are included
gcc -o program file1.c file2.c file3.c

# Check for missing libraries
gcc -lm program.c  # for math library
```

#### Runtime Issues

**Issue**: Files not found / Permission denied
```bash
# Check file permissions
ls -la *.txt

# Fix permissions (Linux/macOS)
chmod 644 *.txt

# Run with proper permissions
sudo ./program  # if system files needed
```

**Issue**: Garbled output / No colors
```bash
# Windows Command Prompt
chcp 65001  # Enable UTF-8

# Use Windows Terminal or PowerShell for best results
# Linux/macOS terminals support colors by default
```

#### Data Issues

**Issue**: Lost data files
```bash
# Data files are plain text and can be manually recreated:
# equipment_inventory.txt - inventory records
# plant_data.txt - plant information  
# alerts.txt - system alerts
# last_watered_date.txt - watering history

# Always backup important data before cleaning
```

**Issue**: Corrupted data files
```bash
# Remove corrupted files to reset
rm equipment_inventory.txt plant_data.txt

# Or use clean-data option in build script
make clean-data  # Linux/macOS
# Select option 7 in build.bat (Windows)
```

### Performance Optimization

#### For Large Datasets
```c
// If managing many plants/equipment items:
// 1. Consider increasing buffer sizes
#define MAX_STRING_LENGTH 200  // Instead of 100

// 2. Implement binary search for large inventories
// 3. Add pagination for large lists
// 4. Consider database integration for very large operations
```

#### Memory Management
```c
// The current system uses static allocation
// For very large operations, consider dynamic allocation:
PlantData* plants = malloc(sizeof(PlantData) * num_plants);
// Remember to free() when done
```

### Advanced Configuration

#### Customizing Health Score Algorithm
```c
// Modify calculateHealthScore() function to adjust scoring:
int calculateHealthScore(float temp, float humidity, float soil, float light) {
    int score = 100;
    
    // Adjust temperature scoring weights
    if (temp < 15.0 || temp > 35.0) score -= 40;  // More strict
    else if (temp < 20.0 || temp > 28.0) score -= 20;  // Moderate penalty
    
    // Customize other parameters similarly
    return (score < 0) ? 0 : score;
}
```

#### Adding New Alert Types
```c
// Add to alert system:
addAlert("Custom", "Your custom message", 2);

// Extend alert categories:
// "Health", "Inventory", "Watering", "System", "Security", "Maintenance"
```

## 📞 Support and Contributing

### Getting Help
1. **Documentation**: Check this file and README.md first
2. **Code Comments**: Source code is well-commented
3. **Issues**: Create GitHub issue for bugs or feature requests
4. **Discussions**: Use GitHub Discussions for questions

### Contributing Guidelines
1. **Fork** the repository
2. **Create** feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** changes (`git commit -m 'Add amazing feature'`)
4. **Push** to branch (`git push origin feature/amazing-feature`)
5. **Open** Pull Request

### Development Setup
```bash
# Clone repository
git clone https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS.git
cd Greenhouse-Monitoring-System-ITTS

# Build and test
make all
make run-advanced

# Create feature branch
git checkout -b feature/new-feature
```

---

**🌱 Happy Greenhouse Monitoring! 🌿**
