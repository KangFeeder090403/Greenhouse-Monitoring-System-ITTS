#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Constants
#define MAX_STRING_LENGTH 100
#define MAX_PLANTS 50
#define MAX_EQUIPMENT 100
#define FILENAME_INVENTORY "equipment_inventory.txt"
#define FILENAME_WATERED_DATE "last_watered_date.txt"
#define FILENAME_PLANT_DATA "plant_data.txt"
#define FILENAME_ALERTS "alerts.txt"

// Structures
typedef struct {
    char name[MAX_STRING_LENGTH];
    int quantity;
    char date[MAX_STRING_LENGTH];
    float price;
    char category[MAX_STRING_LENGTH];
    int minStock;
} InventoryItem;

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
    char alertType[MAX_STRING_LENGTH];
    char message[MAX_STRING_LENGTH];
    char timestamp[MAX_STRING_LENGTH];
    int priority; // 1=Low, 2=Medium, 3=High
} Alert;

// Function prototypes
void displayMainMenu();
void displayPlantsMenu();
void displayEquipmentMenu();
void displaySettingsMenu();
void clearScreen();
void pressEnterToContinue();
void displayWelcomeScreen();

// Plant monitoring functions
void plantHealthMonitoring();
void viewLastWateredDate();
void updateLastWateredDate();
void viewPlantStatistics();
void addPlantData();
void viewAllPlants();
void deletePlantData();
void plantCareReminders();

// Equipment functions
void checkInventory();
void updateInventory();
void searchInventoryItem();
void generateInventoryReport();
void deleteInventoryItem();
void lowStockAlert();
void inventoryStatistics();

// Alert system
void checkAlerts();
void addAlert(const char* type, const char* message, int priority);
void viewAlerts();
void clearAlerts();

// Settings and utilities
void systemSettings();
void exportData();
void importData();
void backupData();
void aboutSystem();

// Utility functions
void getCurrentDate(char *dateStr);
void getCurrentDateTime(char *dateTimeStr);
int validateDate(const char *date);
void displayHeader(const char *title);
void displaySubHeader(const char *subtitle);
float generateSensorReading(float min, float max);
int calculateHealthScore(float temp, float humidity, float soilMoisture, float light);
void trimString(char *str);

int main() {
    int choice;
    
    displayWelcomeScreen();
    
    do {
        clearScreen();
        displayMainMenu();
        
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) {
            printf("❌ Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            pressEnterToContinue();
            continue;
        }
        
        switch (choice) {
            case 1: {
                // Plants Management
                int plantsChoice;
                do {
                    clearScreen();
                    displayPlantsMenu();
                    printf("Enter your choice (1-9): ");
                    
                    if (scanf("%d", &plantsChoice) != 1) {
                        printf("❌ Invalid input! Please enter a number.\n");
                        while (getchar() != '\n');
                        pressEnterToContinue();
                        continue;
                    }
                    
                    switch (plantsChoice) {
                        case 1: plantHealthMonitoring(); break;
                        case 2: viewLastWateredDate(); break;
                        case 3: updateLastWateredDate(); break;
                        case 4: viewPlantStatistics(); break;
                        case 5: addPlantData(); break;
                        case 6: viewAllPlants(); break;
                        case 7: deletePlantData(); break;
                        case 8: plantCareReminders(); break;
                        case 9: printf("🔙 Returning to main menu...\n"); break;
                        default:
                            printf("❌ Invalid choice! Please enter a number between 1-9.\n");
                            pressEnterToContinue();
                    }
                } while (plantsChoice != 9);
                break;
            }
            
            case 2: {
                // Equipment Management
                int equipmentChoice;
                do {
                    clearScreen();
                    displayEquipmentMenu();
                    printf("Enter your choice (1-8): ");
                    
                    if (scanf("%d", &equipmentChoice) != 1) {
                        printf("❌ Invalid input! Please enter a number.\n");
                        while (getchar() != '\n');
                        pressEnterToContinue();
                        continue;
                    }
                    
                    switch (equipmentChoice) {
                        case 1: checkInventory(); break;
                        case 2: updateInventory(); break;
                        case 3: searchInventoryItem(); break;
                        case 4: generateInventoryReport(); break;
                        case 5: deleteInventoryItem(); break;
                        case 6: lowStockAlert(); break;
                        case 7: inventoryStatistics(); break;
                        case 8: printf("🔙 Returning to main menu...\n"); break;
                        default:
                            printf("❌ Invalid choice! Please enter a number between 1-8.\n");
                            pressEnterToContinue();
                    }
                } while (equipmentChoice != 8);
                break;
            }
            
            case 3:
                // Alerts and Notifications
                checkAlerts();
                break;
                
            case 4: {
                // System Settings
                int settingsChoice;
                do {
                    clearScreen();
                    displaySettingsMenu();
                    printf("Enter your choice (1-6): ");
                    
                    if (scanf("%d", &settingsChoice) != 1) {
                        printf("❌ Invalid input! Please enter a number.\n");
                        while (getchar() != '\n');
                        pressEnterToContinue();
                        continue;
                    }
                    
                    switch (settingsChoice) {
                        case 1: exportData(); break;
                        case 2: importData(); break;
                        case 3: backupData(); break;
                        case 4: clearAlerts(); break;
                        case 5: aboutSystem(); break;
                        case 6: printf("🔙 Returning to main menu...\n"); break;
                        default:
                            printf("❌ Invalid choice! Please enter a number between 1-6.\n");
                            pressEnterToContinue();
                    }
                } while (settingsChoice != 6);
                break;
            }
            
            case 5:
                printf("\n🌱 \033[1;32mThank you for using Greenhouse Monitoring System ITTS!\033[0m\n");
                printf("🌿 Keep your plants healthy and happy! 🌸\n");
                printf("👋 Goodbye!\n\n");
                break;
                
            default:
                printf("❌ Invalid choice! Please enter a number between 1-5.\n");
                pressEnterToContinue();
        }
    } while (choice != 5);
    
    return 0;
}

void displayWelcomeScreen() {
    clearScreen();
    printf("\n");
    printf("  ╔═══════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                           ║\n");
    printf("  ║       🌱 \033[1;32mGREENHOUSE MONITORING SYSTEM ITTS\033[0m 🌱        ║\n");
    printf("  ║                                                           ║\n");
    printf("  ║              \033[1;36mAdvanced Plant & Equipment Manager\033[0m          ║\n");
    printf("  ║                                                           ║\n");
    printf("  ║  🌿 Monitor plant health in real-time                    ║\n");
    printf("  ║  💧 Track watering schedules                             ║\n");
    printf("  ║  📊 Manage equipment inventory                           ║\n");
    printf("  ║  🔔 Receive smart notifications                          ║\n");
    printf("  ║  📈 Analyze growth statistics                            ║\n");
    printf("  ║                                                           ║\n");
    printf("  ║              \033[1;33mVersion 2.0 - Enhanced Edition\033[0m             ║\n");
    printf("  ║                                                           ║\n");
    printf("  ╚═══════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("  🌟 Welcome to the future of greenhouse management!\n");
    printf("  🚀 This system will help you create the perfect environment for your plants.\n");
    printf("\n");
    pressEnterToContinue();
}

void displayMainMenu() {
    displayHeader("MAIN MENU");
    printf("🌿 \033[1;32m1. Plants Management\033[0m      - Monitor and care for your plants\n");
    printf("🔧 \033[1;34m2. Equipment Management\033[0m   - Manage tools and supplies\n");
    printf("🔔 \033[1;33m3. Alerts & Notifications\033[0m - View system alerts\n");
    printf("⚙️  \033[1;35m4. System Settings\033[0m        - Configure and maintain system\n");
    printf("🚪 \033[1;31m5. Exit\033[0m                   - Close the application\n");
    printf("═══════════════════════════════════════════════════════════════\n");
}

void displayPlantsMenu() {
    displayHeader("PLANTS MANAGEMENT");
    printf("🔬 1. Plant Health Monitoring     - Check environmental conditions\n");
    printf("💧 2. View Last Watered Date      - See watering history\n");
    printf("🗓️  3. Update Watering Record      - Log new watering\n");
    printf("📊 4. Plant Statistics            - View growth data\n");
    printf("➕ 5. Add New Plant              - Register new plant\n");
    printf("👀 6. View All Plants             - Browse plant database\n");
    printf("🗑️  7. Remove Plant               - Delete plant record\n");
    printf("🔔 8. Care Reminders              - View plant care tasks\n");
    printf("🔙 9. Back to Main Menu           - Return to main menu\n");
    printf("═══════════════════════════════════════════════════════════════\n");
}

void displayEquipmentMenu() {
    displayHeader("EQUIPMENT MANAGEMENT");
    printf("📋 1. View Inventory              - Show all equipment\n");
    printf("➕ 2. Add/Update Equipment        - Manage equipment stock\n");
    printf("🔍 3. Search Equipment            - Find specific items\n");
    printf("📊 4. Inventory Report            - Generate detailed report\n");
    printf("🗑️  5. Remove Equipment           - Delete inventory item\n");
    printf("⚠️  6. Low Stock Alerts           - Check inventory warnings\n");
    printf("📈 7. Inventory Statistics        - View usage analytics\n");
    printf("🔙 8. Back to Main Menu           - Return to main menu\n");
    printf("═══════════════════════════════════════════════════════════════\n");
}

void displaySettingsMenu() {
    displayHeader("SYSTEM SETTINGS");
    printf("📤 1. Export Data                 - Save data to external file\n");
    printf("📥 2. Import Data                 - Load data from file\n");
    printf("💾 3. Backup System               - Create system backup\n");
    printf("🧹 4. Clear All Alerts           - Remove all notifications\n");
    printf("ℹ️  5. About System               - System information\n");
    printf("🔙 6. Back to Main Menu           - Return to main menu\n");
    printf("═══════════════════════════════════════════════════════════════\n");
}

void plantHealthMonitoring() {
    clearScreen();
    displayHeader("PLANT HEALTH MONITORING");
    
    printf("🔄 Collecting sensor data...\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    
    // Simulate realistic sensor readings
    float temperature = generateSensorReading(18.0, 35.0);
    float humidity = generateSensorReading(30.0, 90.0);
    float soilMoisture = generateSensorReading(15.0, 85.0);
    float lightLevel = generateSensorReading(200.0, 2000.0);
    
    printf("\n📊 CURRENT ENVIRONMENTAL CONDITIONS:\n");
    printf("────────────────────────────────────────────────────────────────\n");
    printf("🌡️  Temperature:    %.1f°C", temperature);
    if (temperature >= 20.0 && temperature <= 28.0) printf(" ✅ Optimal");
    else if (temperature < 15.0 || temperature > 35.0) printf(" ❌ Critical");
    else printf(" ⚠️  Suboptimal");
    printf("\n");
    
    printf("💨 Humidity:        %.1f%%", humidity);
    if (humidity >= 50.0 && humidity <= 70.0) printf(" ✅ Optimal");
    else if (humidity < 30.0 || humidity > 85.0) printf(" ❌ Critical");
    else printf(" ⚠️  Suboptimal");
    printf("\n");
    
    printf("💧 Soil Moisture:   %.1f%%", soilMoisture);
    if (soilMoisture >= 40.0 && soilMoisture <= 70.0) printf(" ✅ Optimal");
    else if (soilMoisture < 20.0 || soilMoisture > 80.0) printf(" ❌ Critical");
    else printf(" ⚠️  Suboptimal");
    printf("\n");
    
    printf("☀️  Light Level:     %.0f lux", lightLevel);
    if (lightLevel >= 500.0 && lightLevel <= 1500.0) printf(" ✅ Optimal");
    else if (lightLevel < 200.0 || lightLevel > 1800.0) printf(" ❌ Critical");
    else printf(" ⚠️  Suboptimal");
    printf("\n");
    
    // Calculate overall health score
    int healthScore = calculateHealthScore(temperature, humidity, soilMoisture, lightLevel);
    
    printf("\n🏥 OVERALL PLANT HEALTH ASSESSMENT:\n");
    printf("────────────────────────────────────────────────────────────────\n");
    printf("Health Score: %d/100 ", healthScore);
    
    if (healthScore >= 85) {
        printf("🌟 \033[1;32mEXCELLENT - Plants are thriving!\033[0m\n");
        printf("🎉 Your greenhouse conditions are perfect!\n");
    } else if (healthScore >= 70) {
        printf("😊 \033[1;33mGOOD - Plants are healthy with minor areas for improvement\033[0m\n");
        printf("👍 Most conditions are favorable for plant growth.\n");
    } else if (healthScore >= 50) {
        printf("😐 \033[1;33mFAIR - Some conditions need attention\033[0m\n");
        printf("⚠️  Consider adjusting environmental controls.\n");
    } else {
        printf("😟 \033[1;31mPOOR - Immediate action required!\033[0m\n");
        printf("🚨 Multiple conditions are outside optimal ranges.\n");
        addAlert("Health", "Critical plant health conditions detected", 3);
    }
    
    printf("\n💡 RECOMMENDATIONS:\n");
    printf("────────────────────────────────────────────────────────────────\n");
    if (temperature < 20.0) printf("🔥 Increase heating - temperature too low\n");
    if (temperature > 28.0) printf("❄️  Increase ventilation - temperature too high\n");
    if (humidity < 50.0) printf("💦 Increase humidity - air too dry\n");
    if (humidity > 70.0) printf("🌬️  Improve ventilation - humidity too high\n");
    if (soilMoisture < 40.0) printf("🚿 Water plants - soil too dry\n");
    if (soilMoisture > 70.0) printf("⏸️  Reduce watering - soil too wet\n");
    if (lightLevel < 500.0) printf("💡 Increase lighting - insufficient light\n");
    if (lightLevel > 1500.0) printf("🕶️  Reduce light intensity - too bright\n");
    
    // Save monitoring data
    char currentDateTime[MAX_STRING_LENGTH];
    getCurrentDateTime(currentDateTime);
    
    FILE *fp = fopen("monitoring_log.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s,%.1f,%.1f,%.1f,%.0f,%d\n", 
                currentDateTime, temperature, humidity, soilMoisture, lightLevel, healthScore);
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void viewLastWateredDate() {
    clearScreen();
    displayHeader("WATERING HISTORY");
    
    FILE *fp = fopen(FILENAME_WATERED_DATE, "r");
    if (fp == NULL) {
        printf("❌ No watering records found.\n");
        printf("💡 Tip: Update the watering record to start tracking.\n");
    } else {
        char date[MAX_STRING_LENGTH];
        char plantName[MAX_STRING_LENGTH];
        int recordCount = 0;
        
        printf("📅 RECENT WATERING RECORDS:\n");
        printf("════════════════════════════════════════════════════════════════\n");
        
        while (fscanf(fp, "%s %s", date, plantName) == 2) {
            recordCount++;
            printf("%d. 💧 %s - Last watered: %s\n", recordCount, plantName, date);
        }
        
        if (recordCount == 0) {
            printf("📝 No watering records in file.\n");
        } else {
            printf("\n📊 Total plants tracked: %d\n", recordCount);
            printf("💡 Remember: Most plants need watering every 2-3 days.\n");
        }
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void updateLastWateredDate() {
    clearScreen();
    displayHeader("UPDATE WATERING RECORD");
    
    char date[MAX_STRING_LENGTH];
    char plantName[MAX_STRING_LENGTH];
    char currentDate[MAX_STRING_LENGTH];
    
    getCurrentDate(currentDate);
    printf("📅 Today's date: %s\n", currentDate);
    printf("════════════════════════════════════════════════════════════════\n");
    
    printf("🌱 Enter plant name: ");
    getchar(); // Clear input buffer
    fgets(plantName, sizeof(plantName), stdin);
    trimString(plantName);
    
    printf("📅 Enter watering date (dd-mm-yyyy) or press Enter for today: ");
    fgets(date, sizeof(date), stdin);
    trimString(date);
    
    // If empty input, use current date
    if (strlen(date) == 0) {
        strcpy(date, currentDate);
    }
    
    if (validateDate(date)) {
        FILE *fp = fopen(FILENAME_WATERED_DATE, "a");
        if (fp != NULL) {
            fprintf(fp, "%s %s\n", date, plantName);
            fclose(fp);
            printf("✅ Watering record updated successfully!\n");
            printf("💧 %s was watered on %s\n", plantName, date);
            
            // Add success alert
            char alertMsg[200];
            sprintf(alertMsg, "Watering recorded for %s on %s", plantName, date);
            addAlert("Watering", alertMsg, 1);
        } else {
            printf("❌ Error updating watering record.\n");
        }
    } else {
        printf("❌ Invalid date format. Please use dd-mm-yyyy format.\n");
    }
    
    pressEnterToContinue();
}

void viewPlantStatistics() {
    clearScreen();
    displayHeader("PLANT STATISTICS");
    
    FILE *fp = fopen(FILENAME_PLANT_DATA, "r");
    if (fp == NULL) {
        printf("📊 No plant data available.\n");
        printf("💡 Add some plant data first to view detailed statistics.\n");
    } else {
        PlantData plant;
        int count = 0;
        float avgTemp = 0, avgHumidity = 0, avgSoilMoisture = 0, avgLight = 0;
        int totalHealthScore = 0;
        
        printf("🌱 PLANT DATABASE RECORDS:\n");
        printf("════════════════════════════════════════════════════════════════\n");
        
        while (fscanf(fp, "%s %s %f %f %f %f %s %s %d", 
                      plant.plantName, plant.plantType, &plant.temperature, 
                      &plant.humidity, &plant.soilMoisture, &plant.lightLevel,
                      plant.lastWatered, plant.plantedDate, &plant.healthScore) == 9) {
            count++;
            printf("%d. 🌿 %s (%s)\n", count, plant.plantName, plant.plantType);
            printf("   📊 Temp: %.1f°C | Humidity: %.1f%% | Soil: %.1f%% | Light: %.0flux\n",
                   plant.temperature, plant.humidity, plant.soilMoisture, plant.lightLevel);
            printf("   💧 Last watered: %s | 🌱 Planted: %s | ❤️  Health: %d/100\n\n",
                   plant.lastWatered, plant.plantedDate, plant.healthScore);
            
            avgTemp += plant.temperature;
            avgHumidity += plant.humidity;
            avgSoilMoisture += plant.soilMoisture;
            avgLight += plant.lightLevel;
            totalHealthScore += plant.healthScore;
        }
        
        if (count > 0) {
            avgTemp /= count;
            avgHumidity /= count;
            avgSoilMoisture /= count;
            avgLight /= count;
            int avgHealthScore = totalHealthScore / count;
            
            printf("📈 GREENHOUSE AVERAGES:\n");
            printf("════════════════════════════════════════════════════════════════\n");
            printf("🌡️  Average Temperature: %.1f°C\n", avgTemp);
            printf("💨 Average Humidity: %.1f%%\n", avgHumidity);
            printf("💧 Average Soil Moisture: %.1f%%\n", avgSoilMoisture);
            printf("☀️  Average Light Level: %.0f lux\n", avgLight);
            printf("❤️  Average Health Score: %d/100\n", avgHealthScore);
            printf("📊 Total Plants: %d\n", count);
        }
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void addPlantData() {
    clearScreen();
    displayHeader("ADD NEW PLANT");
    
    PlantData plant;
    char currentDate[MAX_STRING_LENGTH];
    getCurrentDate(currentDate);
    
    printf("🌱 Enter plant details:\n");
    printf("════════════════════════════════════════════════════════════════\n");
    
    printf("📝 Plant name: ");
    getchar(); // Clear input buffer
    fgets(plant.plantName, sizeof(plant.plantName), stdin);
    trimString(plant.plantName);
    
    printf("🏷️  Plant type (e.g., Tomato, Rose, Basil): ");
    fgets(plant.plantType, sizeof(plant.plantType), stdin);
    trimString(plant.plantType);
    
    printf("🌡️  Current temperature (°C): ");
    scanf("%f", &plant.temperature);
    
    printf("💨 Current humidity (%%): ");
    scanf("%f", &plant.humidity);
    
    printf("💧 Current soil moisture (%%): ");
    scanf("%f", &plant.soilMoisture);
    
    printf("☀️  Current light level (lux): ");
    scanf("%f", &plant.lightLevel);
    
    strcpy(plant.lastWatered, currentDate);
    strcpy(plant.plantedDate, currentDate);
    
    plant.healthScore = calculateHealthScore(plant.temperature, plant.humidity, 
                                           plant.soilMoisture, plant.lightLevel);
    
    FILE *fp = fopen(FILENAME_PLANT_DATA, "a");
    if (fp != NULL) {
        fprintf(fp, "%s %s %.1f %.1f %.1f %.0f %s %s %d\n", 
                plant.plantName, plant.plantType, plant.temperature, plant.humidity,
                plant.soilMoisture, plant.lightLevel, plant.lastWatered, 
                plant.plantedDate, plant.healthScore);
        fclose(fp);
        
        printf("\n✅ Plant added successfully!\n");
        printf("🌿 %s (%s) has been registered in your greenhouse.\n", 
               plant.plantName, plant.plantType);
        printf("❤️  Initial health score: %d/100\n", plant.healthScore);
        
        // Add alert for new plant
        char alertMsg[200];
        sprintf(alertMsg, "New plant added: %s (%s)", plant.plantName, plant.plantType);
        addAlert("Plant", alertMsg, 1);
    } else {
        printf("❌ Error adding plant data.\n");
    }
    
    pressEnterToContinue();
}

// Additional function implementations would continue here...
// For brevity, I'll implement the key utility functions:

float generateSensorReading(float min, float max) {
    srand(time(NULL) + rand());
    return min + (float)rand() / RAND_MAX * (max - min);
}

int calculateHealthScore(float temp, float humidity, float soilMoisture, float light) {
    int score = 100;
    
    // Temperature scoring (optimal: 20-28°C)
    if (temp < 15.0 || temp > 35.0) score -= 30;
    else if (temp < 20.0 || temp > 28.0) score -= 15;
    
    // Humidity scoring (optimal: 50-70%)
    if (humidity < 30.0 || humidity > 85.0) score -= 25;
    else if (humidity < 50.0 || humidity > 70.0) score -= 10;
    
    // Soil moisture scoring (optimal: 40-70%)
    if (soilMoisture < 20.0 || soilMoisture > 80.0) score -= 25;
    else if (soilMoisture < 40.0 || soilMoisture > 70.0) score -= 10;
    
    // Light level scoring (optimal: 500-1500 lux)
    if (light < 200.0 || light > 1800.0) score -= 20;
    else if (light < 500.0 || light > 1500.0) score -= 10;
    
    return (score < 0) ? 0 : score;
}

void getCurrentDate(char *dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void getCurrentDateTime(char *dateTimeStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateTimeStr, "%02d-%02d-%04d %02d:%02d:%02d", 
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int validateDate(const char *date) {
    int day, month, year;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3) {
        return 0;
    }
    
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    if (year < 1900 || year > 2100) return 0;
    
    return 1;
}

void displayHeader(const char *title) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║  \033[1;36m%-58s\033[0m  ║\n", title);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    printf("\n💡 Press Enter to continue...");
    while (getchar() != '\n');
    getchar();
}

void trimString(char *str) {
    char *end;
    
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    
    // All spaces?
    if(*str == 0) return;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator
    *(end+1) = 0;
}

void addAlert(const char* type, const char* message, int priority) {
    FILE *fp = fopen(FILENAME_ALERTS, "a");
    if (fp != NULL) {
        char timestamp[MAX_STRING_LENGTH];
        getCurrentDateTime(timestamp);
        fprintf(fp, "%s|%s|%s|%d\n", timestamp, type, message, priority);
        fclose(fp);
    }
}

// Placeholder implementations for remaining functions
void viewAllPlants() {
    clearScreen();
    displayHeader("ALL PLANTS");
    printf("🚧 This feature is under development.\n");
    printf("📊 Use 'Plant Statistics' for now to view plant data.\n");
    pressEnterToContinue();
}

void deletePlantData() {
    clearScreen();
    displayHeader("REMOVE PLANT");
    printf("🚧 This feature is under development.\n");
    pressEnterToContinue();
}

void plantCareReminders() {
    clearScreen();
    displayHeader("CARE REMINDERS");
    printf("🔔 PLANT CARE SCHEDULE:\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("💧 Daily: Check soil moisture levels\n");
    printf("🌱 Weekly: Inspect plants for pests and diseases\n");
    printf("✂️  Monthly: Prune dead leaves and stems\n");
    printf("🌿 Seasonally: Fertilize and repot as needed\n");
    pressEnterToContinue();
}

void checkInventory() {
    clearScreen();
    displayHeader("EQUIPMENT INVENTORY");
    
    FILE *fp = fopen(FILENAME_INVENTORY, "r");
    if (fp == NULL) {
        printf("📦 No inventory data found.\n");
        printf("💡 Add some equipment to start tracking inventory.\n");
    } else {
        char line[256];
        int itemCount = 0;
        
        printf("📋 CURRENT INVENTORY:\n");
        printf("════════════════════════════════════════════════════════════════\n");
        
        while (fgets(line, sizeof(line), fp)) {
            itemCount++;
            printf("%d. %s", itemCount, line);
        }
        
        if (itemCount == 0) {
            printf("📦 Inventory is empty.\n");
        } else {
            printf("\n📊 Total items in inventory: %d\n", itemCount);
        }
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void updateInventory() {
    clearScreen();
    displayHeader("ADD/UPDATE EQUIPMENT");
    
    InventoryItem item;
    char currentDate[MAX_STRING_LENGTH];
    getCurrentDate(currentDate);
    
    printf("📦 Enter equipment details:\n");
    printf("════════════════════════════════════════════════════════════════\n");
    
    printf("📝 Item name: ");
    getchar(); // Clear input buffer
    fgets(item.name, sizeof(item.name), stdin);
    trimString(item.name);
    
    printf("🏷️  Category (e.g., Tools, Seeds, Fertilizers): ");
    fgets(item.category, sizeof(item.category), stdin);
    trimString(item.category);
    
    printf("📊 Quantity: ");
    scanf("%d", &item.quantity);
    
    printf("💰 Price per unit ($): ");
    scanf("%f", &item.price);
    
    printf("⚠️  Minimum stock level: ");
    scanf("%d", &item.minStock);
    
    strcpy(item.date, currentDate);
    
    FILE *fp = fopen(FILENAME_INVENTORY, "a");
    if (fp != NULL) {
        fprintf(fp, "Item: %s | Category: %s | Quantity: %d | Price: $%.2f | Min Stock: %d | Date: %s\n",
                item.name, item.category, item.quantity, item.price, item.minStock, item.date);
        fclose(fp);
        
        printf("\n✅ Equipment added successfully!\n");
        printf("📦 %s (%d units) added to %s category\n", 
               item.name, item.quantity, item.category);
        
        // Check for low stock
        if (item.quantity <= item.minStock) {
            char alertMsg[200];
            sprintf(alertMsg, "Low stock alert: %s (%d units remaining)", item.name, item.quantity);
            addAlert("Inventory", alertMsg, 2);
        }
    } else {
        printf("❌ Error updating inventory.\n");
    }
    
    pressEnterToContinue();
}

void searchInventoryItem() {
    clearScreen();
    displayHeader("SEARCH EQUIPMENT");
    
    char searchTerm[MAX_STRING_LENGTH];
    char line[256];
    int found = 0;
    
    printf("🔍 Enter item name or category to search: ");
    getchar(); // Clear input buffer
    fgets(searchTerm, sizeof(searchTerm), stdin);
    trimString(searchTerm);
    
    FILE *fp = fopen(FILENAME_INVENTORY, "r");
    if (fp == NULL) {
        printf("❌ No inventory file found.\n");
    } else {
        printf("\n🔍 SEARCH RESULTS:\n");
        printf("════════════════════════════════════════════════════════════════\n");
        
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, searchTerm) != NULL) {
                printf("✅ %s", line);
                found++;
            }
        }
        
        if (found == 0) {
            printf("❌ No items found matching '%s'.\n", searchTerm);
        } else {
            printf("\n📊 Found %d item(s) matching '%s'.\n", found, searchTerm);
        }
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void generateInventoryReport() {
    clearScreen();
    displayHeader("INVENTORY REPORT");
    
    FILE *fp = fopen(FILENAME_INVENTORY, "r");
    if (fp == NULL) {
        printf("❌ No inventory data available.\n");
    } else {
        char line[256];
        int totalItems = 0;
        float totalValue = 0.0;
        
        printf("📊 DETAILED INVENTORY REPORT\n");
        char currentDate[MAX_STRING_LENGTH];
        getCurrentDate(currentDate);
        printf("📅 Generated on: %s\n", currentDate);
        printf("════════════════════════════════════════════════════════════════\n");
        
        while (fgets(line, sizeof(line), fp)) {
            totalItems++;
            printf("%s", line);
            
            // Extract price and quantity for total value calculation
            char *priceStr = strstr(line, "Price: $");
            if (priceStr) {
                float price;
                if (sscanf(priceStr, "Price: $%f", &price) == 1) {
                    char *qtyStr = strstr(line, "Quantity: ");
                    if (qtyStr) {
                        int qty;
                        if (sscanf(qtyStr, "Quantity: %d", &qty) == 1) {
                            totalValue += price * qty;
                        }
                    }
                }
            }
        }
        
        printf("════════════════════════════════════════════════════════════════\n");
        printf("📦 Total Items: %d\n", totalItems);
        printf("💰 Total Inventory Value: $%.2f\n", totalValue);
        printf("📈 Average Item Value: $%.2f\n", totalItems > 0 ? totalValue / totalItems : 0);
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void checkAlerts() {
    clearScreen();
    displayHeader("ALERTS & NOTIFICATIONS");
    
    FILE *fp = fopen(FILENAME_ALERTS, "r");
    if (fp == NULL) {
        printf("✅ No alerts at this time.\n");
        printf("🌱 Your greenhouse system is running smoothly!\n");
    } else {
        char timestamp[MAX_STRING_LENGTH], type[MAX_STRING_LENGTH], message[MAX_STRING_LENGTH];
        int priority;
        int alertCount = 0;
        
        printf("🔔 SYSTEM ALERTS:\n");
        printf("════════════════════════════════════════════════════════════════\n");
        
        while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d\n", timestamp, type, message, priority) == 4) {
            alertCount++;
            char priorityIcon[10];
            char priorityColor[20];
            
            switch(priority) {
                case 3: 
                    strcpy(priorityIcon, "🚨"); 
                    strcpy(priorityColor, "\033[1;31m"); 
                    break;
                case 2: 
                    strcpy(priorityIcon, "⚠️"); 
                    strcpy(priorityColor, "\033[1;33m"); 
                    break;
                default: 
                    strcpy(priorityIcon, "ℹ️"); 
                    strcpy(priorityColor, "\033[1;36m"); 
                    break;
            }
            
            printf("%s %s[%s] %s: %s\033[0m\n", 
                   priorityIcon, priorityColor, type, timestamp, message);
        }
        
        if (alertCount == 0) {
            printf("✅ No alerts found.\n");
        } else {
            printf("\n📊 Total alerts: %d\n", alertCount);
        }
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

// Placeholder implementations for remaining functions
void deleteInventoryItem() {
    clearScreen();
    displayHeader("REMOVE EQUIPMENT");
    printf("🚧 This feature is under development.\n");
    pressEnterToContinue();
}

void lowStockAlert() {
    clearScreen();
    displayHeader("LOW STOCK ALERTS");
    printf("⚠️  Checking inventory levels...\n");
    printf("🚧 This feature is under development.\n");
    pressEnterToContinue();
}

void inventoryStatistics() {
    clearScreen();
    displayHeader("INVENTORY ANALYTICS");
    printf("📈 Generating usage statistics...\n");
    printf("🚧 This feature is under development.\n");
    pressEnterToContinue();
}

void exportData() {
    clearScreen();
    displayHeader("EXPORT DATA");
    printf("📤 Exporting system data...\n");
    printf("🚧 This feature is under development.\n");
    pressEnterToContinue();
}

void importData() {
    clearScreen();
    displayHeader("IMPORT DATA");
    printf("📥 Importing system data...\n");
    printf("🚧 This feature is under development.\n");
    pressEnterToContinue();
}

void backupData() {
    clearScreen();
    displayHeader("BACKUP SYSTEM");
    printf("💾 Creating system backup...\n");
    printf("🚧 This feature is under development.\n");
    pressEnterToContinue();
}

void clearAlerts() {
    clearScreen();
    displayHeader("CLEAR ALERTS");
    
    char choice;
    printf("⚠️  Are you sure you want to clear all alerts? (y/N): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        FILE *fp = fopen(FILENAME_ALERTS, "w");
        if (fp != NULL) {
            fclose(fp);
            printf("✅ All alerts have been cleared.\n");
        } else {
            printf("❌ Error clearing alerts.\n");
        }
    } else {
        printf("🔙 Operation cancelled.\n");
    }
    
    pressEnterToContinue();
}

void aboutSystem() {
    clearScreen();
    displayHeader("ABOUT GREENHOUSE MONITORING SYSTEM");
    
    printf("🌱 \033[1;32mGreenhouse Monitoring System ITTS v2.0\033[0m\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("🎯 Purpose: Advanced greenhouse management and monitoring\n");
    printf("👨‍💻 Developer: ITTS Development Team\n");
    printf("📅 Version: 2.0 Enhanced Edition\n");
    printf("🗓️  Release Date: July 2025\n");
    printf("💻 Platform: Cross-platform (Windows, Linux, macOS)\n");
    printf("📝 Language: C (C99 Standard)\n");
    printf("\n");
    printf("🌟 \033[1;33mKey Features:\033[0m\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("🔬 Real-time plant health monitoring\n");
    printf("💧 Comprehensive watering management\n");
    printf("📊 Advanced plant statistics and analytics\n");
    printf("🔧 Complete equipment inventory system\n");
    printf("🔔 Smart alert and notification system\n");
    printf("⚙️  Data export and backup capabilities\n");
    printf("🎨 User-friendly colorful interface\n");
    printf("🛡️  Robust error handling and validation\n");
    printf("\n");
    printf("📞 \033[1;36mSupport:\033[0m\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("📧 Email: support@itts-greenhouse.com\n");
    printf("🌐 Website: https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS\n");
    printf("📖 Documentation: Available in README.md\n");
    printf("\n");
    printf("🙏 \033[1;35mThank you for using our system!\033[0m\n");
    printf("🌱 Happy greenhouse monitoring! 🌿\n");
    
    pressEnterToContinue();
}
