#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define MAX_STRING_LENGTH 50
#define MAX_INVENTORY_ITEMS 100
#define FILENAME_INVENTORY "equipment_inventory.txt"
#define FILENAME_WATERED_DATE "last_watered_date.txt"
#define FILENAME_PLANT_DATA "plant_data.txt"

// Structures
typedef struct {
    char name[MAX_STRING_LENGTH];
    int quantity;
    char date[MAX_STRING_LENGTH];
    float price;
} InventoryItem;

typedef struct {
    char plantType[MAX_STRING_LENGTH];
    float temperature;
    float humidity;
    float soilMoisture;
    char lastWatered[MAX_STRING_LENGTH];
} PlantData;

// Function prototypes
void displayMainMenu();
void displayPlantsMenu();
void displayEquipmentMenu();
void clearScreen();
void pressEnterToContinue();

// Plant monitoring functions
void plantHealthMonitoring();
void viewLastWateredDate();
void updateLastWateredDate();
void viewPlantStatistics();
void addPlantData();

// Equipment functions
void checkInventory();
void updateInventory();
void searchInventoryItem();
void generateInventoryReport();

// Utility functions
void getCurrentDate(char *dateStr);
int validateDate(const char *date);
void displayHeader(const char *title);

int main() {
    int choice;
    
    displayHeader("GREENHOUSE MONITORING SYSTEM ITTS");
    printf("Welcome to the Greenhouse Monitoring System!\n");
    printf("This system helps you monitor plants and manage equipment.\n\n");
    pressEnterToContinue();
    
    do {
        clearScreen();
        displayMainMenu();
        
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            pressEnterToContinue();
            continue;
        }
        
        switch (choice) {
            case 1: {
                int plantsChoice;
                do {
                    clearScreen();
                    displayPlantsMenu();
                    printf("Enter your choice: ");
                    
                    if (scanf("%d", &plantsChoice) != 1) {
                        printf("Invalid input! Please enter a number.\n");
                        while (getchar() != '\n');
                        pressEnterToContinue();
                        continue;
                    }
                    
                    switch (plantsChoice) {
                        case 1:
                            plantHealthMonitoring();
                            break;
                        case 2:
                            viewLastWateredDate();
                            break;
                        case 3:
                            updateLastWateredDate();
                            break;
                        case 4:
                            viewPlantStatistics();
                            break;
                        case 5:
                            addPlantData();
                            break;
                        case 6:
                            printf("Returning to main menu...\n");
                            break;
                        default:
                            printf("Invalid choice! Please enter a number between 1-6.\n");
                            pressEnterToContinue();
                    }
                } while (plantsChoice != 6);
                break;
            }
            
            case 2: {
                int equipmentChoice;
                do {
                    clearScreen();
                    displayEquipmentMenu();
                    printf("Enter your choice: ");
                    
                    if (scanf("%d", &equipmentChoice) != 1) {
                        printf("Invalid input! Please enter a number.\n");
                        while (getchar() != '\n');
                        pressEnterToContinue();
                        continue;
                    }
                    
                    switch (equipmentChoice) {
                        case 1:
                            checkInventory();
                            break;
                        case 2:
                            updateInventory();
                            break;
                        case 3:
                            searchInventoryItem();
                            break;
                        case 4:
                            generateInventoryReport();
                            break;
                        case 5:
                            printf("Returning to main menu...\n");
                            break;
                        default:
                            printf("Invalid choice! Please enter a number between 1-5.\n");
                            pressEnterToContinue();
                    }
                } while (equipmentChoice != 5);
                break;
            }
            
            case 3:
                printf("\033[1;32mThank you for using Greenhouse Monitoring System ITTS!\033[0m\n");
                printf("Have a great day! 🌱\n");
                break;
                
            default:
                printf("Invalid choice! Please enter a number between 1-3.\n");
                pressEnterToContinue();
        }
    } while (choice != 3);
    
    return 0;
}

void displayMainMenu() {
    displayHeader("MAIN MENU");
    printf("🌱 \033[1;32m1. Plants Management\033[0m\n");
    printf("🔧 \033[1;34m2. Equipment Management\033[0m\n");
    printf("🚪 \033[1;35m3. Exit\033[0m\n");
    printf("═══════════════════════════════════════\n");
}

void displayPlantsMenu() {
    displayHeader("PLANTS MANAGEMENT");
    printf("🌿 1. Plant Health Monitoring\n");
    printf("💧 2. View Last Watered Date\n");
    printf("🗓️  3. Update Last Watered Date\n");
    printf("📊 4. View Plant Statistics\n");
    printf("➕ 5. Add Plant Data\n");
    printf("🔙 6. Go Back to Main Menu\n");
    printf("═══════════════════════════════════════\n");
}

void displayEquipmentMenu() {
    displayHeader("EQUIPMENT MANAGEMENT");
    printf("📋 1. Check Inventory\n");
    printf("➕ 2. Add/Update Inventory\n");
    printf("🔍 3. Search Inventory Item\n");
    printf("📊 4. Generate Inventory Report\n");
    printf("🔙 5. Go Back to Main Menu\n");
    printf("═══════════════════════════════════════\n");
}

void plantHealthMonitoring() {
    clearScreen();
    displayHeader("PLANT HEALTH MONITORING");
    
    srand(time(NULL));
    
    // Simulate sensor readings
    float temperature = 18.0 + (rand() % 150) / 10.0; // 18-33°C
    float humidity = 40.0 + (rand() % 400) / 10.0;    // 40-80%
    float soilMoisture = 20.0 + (rand() % 600) / 10.0; // 20-80%
    
    printf("Current Environmental Conditions:\n");
    printf("🌡️  Temperature: %.1f°C\n", temperature);
    printf("💨 Humidity: %.1f%%\n", humidity);
    printf("💧 Soil Moisture: %.1f%%\n", soilMoisture);
    printf("\n");
    
    // Health assessment
    int healthScore = 0;
    printf("Health Assessment:\n");
    
    if (temperature >= 20.0 && temperature <= 30.0) {
        printf("✅ Temperature: Optimal\n");
        healthScore++;
    } else {
        printf("⚠️  Temperature: %s\n", temperature < 20.0 ? "Too Cold" : "Too Hot");
    }
    
    if (humidity >= 50.0 && humidity <= 70.0) {
        printf("✅ Humidity: Optimal\n");
        healthScore++;
    } else {
        printf("⚠️  Humidity: %s\n", humidity < 50.0 ? "Too Low" : "Too High");
    }
    
    if (soilMoisture >= 40.0 && soilMoisture <= 70.0) {
        printf("✅ Soil Moisture: Optimal\n");
        healthScore++;
    } else {
        printf("⚠️  Soil Moisture: %s\n", soilMoisture < 40.0 ? "Too Dry" : "Too Wet");
    }
    
    printf("\n");
    if (healthScore == 3) {
        printf("🌟 \033[1;32mPlants are in excellent health!\033[0m\n");
    } else if (healthScore >= 2) {
        printf("😊 \033[1;33mPlants are generally healthy with minor concerns.\033[0m\n");
    } else {
        printf("⚠️  \033[1;31mPlants need attention! Please check environmental conditions.\033[0m\n");
    }
    
    pressEnterToContinue();
}

void viewLastWateredDate() {
    clearScreen();
    displayHeader("LAST WATERED DATE");
    
    FILE *fp = fopen(FILENAME_WATERED_DATE, "r");
    if (fp == NULL) {
        printf("❌ No watering record found.\n");
        printf("Please update the last watered date first.\n");
    } else {
        char date[MAX_STRING_LENGTH];
        if (fscanf(fp, "%s", date) == 1) {
            printf("💧 Last watered date: %s\n", date);
            
            // Calculate days since last watering (simplified)
            printf("💡 Tip: Regular watering schedule is important for plant health!\n");
        } else {
            printf("❌ Error reading watering record.\n");
        }
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void updateLastWateredDate() {
    clearScreen();
    displayHeader("UPDATE LAST WATERED DATE");
    
    char date[MAX_STRING_LENGTH];
    char currentDate[MAX_STRING_LENGTH];
    
    getCurrentDate(currentDate);
    printf("Current date: %s\n", currentDate);
    printf("Enter the last watered date (dd-mm-yyyy) or press Enter for today: ");
    
    getchar(); // Clear input buffer
    if (fgets(date, sizeof(date), stdin) != NULL) {
        // Remove newline character
        date[strcspn(date, "\n")] = 0;
        
        // If empty input, use current date
        if (strlen(date) == 0) {
            strcpy(date, currentDate);
        }
        
        if (validateDate(date)) {
            FILE *fp = fopen(FILENAME_WATERED_DATE, "w");
            if (fp != NULL) {
                fprintf(fp, "%s", date);
                fclose(fp);
                printf("✅ Last watered date updated successfully to: %s\n", date);
            } else {
                printf("❌ Error updating watered date.\n");
            }
        } else {
            printf("❌ Invalid date format. Please use dd-mm-yyyy format.\n");
        }
    }
    
    pressEnterToContinue();
}

void viewPlantStatistics() {
    clearScreen();
    displayHeader("PLANT STATISTICS");
    
    FILE *fp = fopen(FILENAME_PLANT_DATA, "r");
    if (fp == NULL) {
        printf("📊 No plant data available.\n");
        printf("Add some plant data first to view statistics.\n");
    } else {
        PlantData plant;
        int count = 0;
        float avgTemp = 0, avgHumidity = 0, avgSoilMoisture = 0;
        
        printf("Plant Data Records:\n");
        printf("═══════════════════════════════════════════════════════════\n");
        
        while (fscanf(fp, "%s %f %f %f %s", plant.plantType, &plant.temperature, 
                      &plant.humidity, &plant.soilMoisture, plant.lastWatered) == 5) {
            count++;
            printf("%d. %s - Temp: %.1f°C, Humidity: %.1f%%, Soil: %.1f%%, Watered: %s\n",
                   count, plant.plantType, plant.temperature, plant.humidity, 
                   plant.soilMoisture, plant.lastWatered);
            
            avgTemp += plant.temperature;
            avgHumidity += plant.humidity;
            avgSoilMoisture += plant.soilMoisture;
        }
        
        if (count > 0) {
            avgTemp /= count;
            avgHumidity /= count;
            avgSoilMoisture /= count;
            
            printf("\n📊 Average Conditions:\n");
            printf("🌡️  Temperature: %.1f°C\n", avgTemp);
            printf("💨 Humidity: %.1f%%\n", avgHumidity);
            printf("💧 Soil Moisture: %.1f%%\n", avgSoilMoisture);
        }
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void addPlantData() {
    clearScreen();
    displayHeader("ADD PLANT DATA");
    
    PlantData plant;
    char currentDate[MAX_STRING_LENGTH];
    getCurrentDate(currentDate);
    
    printf("Enter plant type: ");
    scanf("%s", plant.plantType);
    
    printf("Enter temperature (°C): ");
    scanf("%f", &plant.temperature);
    
    printf("Enter humidity (%%): ");
    scanf("%f", &plant.humidity);
    
    printf("Enter soil moisture (%%): ");
    scanf("%f", &plant.soilMoisture);
    
    strcpy(plant.lastWatered, currentDate);
    
    FILE *fp = fopen(FILENAME_PLANT_DATA, "a");
    if (fp != NULL) {
        fprintf(fp, "%s %.1f %.1f %.1f %s\n", plant.plantType, plant.temperature,
                plant.humidity, plant.soilMoisture, plant.lastWatered);
        fclose(fp);
        printf("✅ Plant data added successfully!\n");
    } else {
        printf("❌ Error adding plant data.\n");
    }
    
    pressEnterToContinue();
}

void checkInventory() {
    clearScreen();
    displayHeader("INVENTORY LIST");
    
    FILE *fp = fopen(FILENAME_INVENTORY, "r");
    if (fp == NULL) {
        printf("📦 No inventory data found.\n");
        printf("Add some items to the inventory first.\n");
    } else {
        char line[256];
        int itemCount = 0;
        
        printf("Current Inventory:\n");
        printf("═══════════════════════════════════════════════════════════\n");
        
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
    displayHeader("UPDATE INVENTORY");
    
    InventoryItem item;
    char currentDate[MAX_STRING_LENGTH];
    getCurrentDate(currentDate);
    
    printf("Enter item name: ");
    scanf("%s", item.name);
    
    printf("Enter quantity: ");
    scanf("%d", &item.quantity);
    
    printf("Enter price per unit: $");
    scanf("%f", &item.price);
    
    printf("Enter date (dd-mm-yyyy) or press Enter for today: ");
    getchar(); // Clear input buffer
    
    if (fgets(item.date, sizeof(item.date), stdin) != NULL) {
        item.date[strcspn(item.date, "\n")] = 0;
        
        if (strlen(item.date) == 0) {
            strcpy(item.date, currentDate);
        }
        
        FILE *fp = fopen(FILENAME_INVENTORY, "a");
        if (fp != NULL) {
            fprintf(fp, "Item: %s, Quantity: %d, Price: $%.2f, Date: %s\n",
                    item.name, item.quantity, item.price, item.date);
            fclose(fp);
            printf("✅ Inventory updated successfully!\n");
            printf("📦 Added: %s (Qty: %d, Price: $%.2f)\n", 
                   item.name, item.quantity, item.price);
        } else {
            printf("❌ Error updating inventory.\n");
        }
    }
    
    pressEnterToContinue();
}

void searchInventoryItem() {
    clearScreen();
    displayHeader("SEARCH INVENTORY");
    
    char searchTerm[MAX_STRING_LENGTH];
    char line[256];
    int found = 0;
    
    printf("Enter item name to search: ");
    scanf("%s", searchTerm);
    
    FILE *fp = fopen(FILENAME_INVENTORY, "r");
    if (fp == NULL) {
        printf("❌ No inventory file found.\n");
    } else {
        printf("\nSearch Results:\n");
        printf("═══════════════════════════════════════════════════════════\n");
        
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, searchTerm) != NULL) {
                printf("🔍 %s", line);
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
        
        printf("📊 INVENTORY SUMMARY REPORT\n");
        printf("Generated on: ");
        char currentDate[MAX_STRING_LENGTH];
        getCurrentDate(currentDate);
        printf("%s\n", currentDate);
        printf("═══════════════════════════════════════════════════════════\n");
        
        while (fgets(line, sizeof(line), fp)) {
            totalItems++;
            printf("%s", line);
            
            // Try to extract price for total value calculation
            char *priceStr = strstr(line, "Price: $");
            if (priceStr) {
                float price;
                if (sscanf(priceStr, "Price: $%f", &price) == 1) {
                    // Extract quantity
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
        
        printf("═══════════════════════════════════════════════════════════\n");
        printf("📦 Total Items: %d\n", totalItems);
        printf("💰 Total Inventory Value: $%.2f\n", totalValue);
        
        fclose(fp);
    }
    
    pressEnterToContinue();
}

void getCurrentDate(char *dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
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
    printf("═══════════════════════════════════════\n");
    printf("  \033[1;36m%s\033[0m\n", title);
    printf("═══════════════════════════════════════\n");
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar();
}
