# 🌱 Greenhouse Monitoring System ITTS

A comprehensive greenhouse monitoring and management system written in C that helps you track plant health, environmental conditions, and equipment inventory.

## 🌟 Features

### 🌿 Plant Management
- **Real-time Plant Health Monitoring**: Simulates sensor readings for temperature, humidity, and soil moisture
- **Health Assessment**: Automated evaluation of plant conditions with color-coded feedback
- **Watering Schedule**: Track and update last watered dates
- **Plant Statistics**: View historical data and average environmental conditions
- **Data Logging**: Add and store plant data for analysis

### 🔧 Equipment Management
- **Inventory Tracking**: Comprehensive inventory management system
- **Item Search**: Quick search functionality for inventory items
- **Price Tracking**: Monitor equipment costs and total inventory value
- **Inventory Reports**: Generate detailed inventory summaries
- **Date Tracking**: Track when items were added or updated

### 💡 Additional Features
- **User-Friendly Interface**: Colorful, intuitive menu system
- **Input Validation**: Robust error handling and input validation
- **Cross-Platform**: Works on Windows, Linux, and macOS
- **File-Based Storage**: Persistent data storage using text files
- **Automated Date Handling**: Current date integration

## 🚀 Getting Started

### Prerequisites
- GCC compiler (MinGW on Windows)
- C99 standard support

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS.git
   cd Greenhouse-Monitoring-System-ITTS
   ```

2. **Compile the program**:
   ```bash
   # Using Makefile (recommended)
   make

   # Or compile manually
   gcc -Wall -Wextra -std=c99 -o greenhouse_monitoring greenhouse_monitoring.c
   ```

3. **Run the program**:
   ```bash
   # Using Makefile
   make run

   # Or run directly
   ./greenhouse_monitoring
   ```

## 📖 Usage Guide

### Main Menu
The system provides three main options:
1. **Plants Management** - Monitor and manage plant health
2. **Equipment Management** - Track and manage greenhouse equipment
3. **Exit** - Close the application

### Plant Management Features

#### Health Monitoring
- Displays simulated environmental readings
- Provides health assessment based on optimal ranges:
  - Temperature: 20-30°C (optimal)
  - Humidity: 50-70% (optimal)
  - Soil Moisture: 40-70% (optimal)

#### Watering Management
- View last watered date
- Update watering records
- Automatic date validation

#### Plant Statistics
- View all recorded plant data
- Calculate average environmental conditions
- Historical data analysis

### Equipment Management Features

#### Inventory Operations
- Add new items with quantity and price
- View complete inventory list
- Search for specific items
- Generate comprehensive reports

#### Data Fields
- Item name
- Quantity
- Price per unit
- Date added/updated

## 🗂️ File Structure

```
Greenhouse-Monitoring-System-ITTS/
├── greenhouse_monitoring.c     # Main source code
├── Makefile                   # Build configuration
├── README.md                  # Documentation
├── environment.yml            # Conda environment (optional)
├── equipment_inventory.txt    # Inventory data (generated)
├── last_watered_date.txt     # Watering records (generated)
└── plant_data.txt            # Plant statistics (generated)
```

## 🎨 User Interface

The system features a colorful, intuitive interface with:
- 🌱 Color-coded menu options
- ✅ Success indicators
- ⚠️ Warning messages
- ❌ Error notifications
- 📊 Data visualization elements

## 🔧 Technical Details

### Data Storage
- **Text Files**: All data is stored in human-readable text files
- **Persistent Storage**: Data survives program restarts
- **Portable Format**: Easy to backup and transfer

### Input Validation
- Date format validation (dd-mm-yyyy)
- Numeric input verification
- Buffer overflow protection
- Error handling for file operations

### Cross-Platform Compatibility
- Windows: Uses `cls` for screen clearing
- Linux/macOS: Uses `clear` for screen clearing
- Standard C library functions for maximum compatibility

## 🚧 Improvements from Original

### Code Quality
- ✅ Fixed menu structure bug (missing case 2)
- ✅ Added proper error handling
- ✅ Implemented input validation
- ✅ Modular function design
- ✅ Consistent code formatting

### New Features
- ✅ Plant statistics and data logging
- ✅ Advanced inventory management
- ✅ Search functionality
- ✅ Inventory reporting
- ✅ Price tracking
- ✅ Automated date handling

### User Experience
- ✅ Improved menu navigation
- ✅ Color-coded interface
- ✅ Better error messages
- ✅ Input validation feedback
- ✅ Progress indicators

## 🔮 Future Enhancements

- [ ] Database integration (SQLite)
- [ ] Network connectivity for remote monitoring
- [ ] Real sensor integration
- [ ] Web-based dashboard
- [ ] Mobile app companion
- [ ] Automated alerts and notifications
- [ ] Data export to CSV/Excel
- [ ] Multi-language support

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**KangFeeder090403**
- GitHub: [@KangFeeder090403](https://github.com/KangFeeder090403)

## 📞 Support

If you have any questions or need help with the system, please:
1. Check this README first
2. Look through existing [Issues](https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS/issues)
3. Create a new issue if needed

---

**Happy Greenhouse Monitoring! 🌱🌿🌺**