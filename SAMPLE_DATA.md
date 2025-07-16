# Sample Data Files for Greenhouse Monitoring System

This directory contains sample data files to help you get started with the Greenhouse Monitoring System.

## Quick Setup Instructions

1. **Copy sample files to main directory**:
   ```bash
   # Linux/macOS
   cp sample_data/* ../
   
   # Windows
   copy sample_data\* ..\
   ```

2. **Or manually create the files** using the content below.

## Sample Files Content

### equipment_inventory.txt
```
Item: Watering Can | Category: Tools | Quantity: 3 | Price: $15.99 | Min Stock: 1 | Date: 16-07-2025
Item: Fertilizer NPK | Category: Fertilizers | Quantity: 10 | Price: $8.50 | Min Stock: 2 | Date: 16-07-2025
Item: Tomato Seeds | Category: Seeds | Quantity: 25 | Price: $2.99 | Min Stock: 5 | Date: 16-07-2025
Item: Pruning Shears | Category: Tools | Quantity: 2 | Price: $22.99 | Min Stock: 1 | Date: 16-07-2025
Item: Plant Pots 6inch | Category: Containers | Quantity: 15 | Price: $3.49 | Min Stock: 5 | Date: 16-07-2025
Item: Soil pH Meter | Category: Instruments | Quantity: 1 | Price: $45.99 | Min Stock: 1 | Date: 16-07-2025
Item: Organic Compost | Category: Fertilizers | Quantity: 8 | Price: $12.99 | Min Stock: 3 | Date: 16-07-2025
```

### plant_data.txt
```
Tomato_Plant_1 Tomato 24.5 62.0 55.0 850 15-07-2025 10-07-2025 88
Basil_Herb_Garden Basil 22.8 58.0 48.0 920 16-07-2025 05-07-2025 82
Rose_Bush_1 Rose 26.2 65.0 52.0 780 14-07-2025 01-07-2025 85
Lettuce_Bed_A Lettuce 21.5 70.0 62.0 650 16-07-2025 12-07-2025 89
Pepper_Plant_Red Pepper 25.8 60.0 50.0 900 15-07-2025 08-07-2025 86
```

### last_watered_date.txt
```
16-07-2025 Tomato_Plant_1
16-07-2025 Basil_Herb_Garden
16-07-2025 Lettuce_Bed_A
15-07-2025 Tomato_Plant_1
15-07-2025 Pepper_Plant_Red
14-07-2025 Rose_Bush_1
```

### alerts.txt
```
15-07-2025 14:30:22|Health|Plant health monitoring completed - all systems normal|1
16-07-2025 08:15:45|Watering|Watering recorded for Tomato_Plant_1 on 16-07-2025|1
16-07-2025 09:22:10|Inventory|Low stock alert: Organic Compost (3 units remaining)|2
16-07-2025 10:45:33|Plant|New plant added: Lettuce_Bed_A (Lettuce)|1
16-07-2025 11:20:18|Health|Optimal conditions detected in greenhouse zone 1|1
```

## File Format Specifications

### Equipment Inventory Format
```
Item: [name] | Category: [category] | Quantity: [number] | Price: $[amount] | Min Stock: [number] | Date: [dd-mm-yyyy]
```

### Plant Data Format
```
[plant_name] [plant_type] [temperature] [humidity] [soil_moisture] [light_level] [last_watered] [planted_date] [health_score]
```

### Watering Records Format
```
[dd-mm-yyyy] [plant_name]
```

### Alerts Format
```
[dd-mm-yyyy hh:mm:ss]|[alert_type]|[message]|[priority_level]
```

## Tips for Using Sample Data

1. **Customize Names**: Change plant and equipment names to match your actual greenhouse
2. **Update Dates**: Modify dates to current or realistic timeframes
3. **Adjust Values**: Change quantities, prices, and measurements to match your situation
4. **Add More Entries**: Feel free to add more plants and equipment as needed
5. **Test Features**: Use this data to explore all system features

## Creating Your Own Data

### Starting Fresh
If you prefer to start with empty files, create these empty files:
- `equipment_inventory.txt` (empty)
- `plant_data.txt` (empty)  
- `last_watered_date.txt` (empty)
- `alerts.txt` (empty)

The system will populate them as you use the application.

### Data Validation
The system includes validation for:
- ✅ Date formats (dd-mm-yyyy)
- ✅ Numeric values (quantities, prices, measurements)
- ✅ Required fields
- ✅ File permissions and access

## Backup Recommendations

Always backup your data files before:
- 🔄 System updates
- 🧹 Cleaning operations  
- 🔧 Major configuration changes
- 📊 Large data imports

```bash
# Create backup directory
mkdir backup_$(date +%Y%m%d)

# Copy data files
cp *.txt backup_$(date +%Y%m%d)/
```

Happy greenhouse monitoring! 🌱
