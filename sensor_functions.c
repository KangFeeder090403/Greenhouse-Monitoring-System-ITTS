#include "greenhouse_advanced_features.h"
#include <windows.h>
#include <math.h>

// Simulasi pin sensor (dalam implementasi nyata akan menggunakan GPIO)
#define PIN_SENSOR_SUHU 2
#define PIN_SENSOR_KELEMBABAN 3
#define PIN_SENSOR_KELEMBABAN_TANAH 4
#define PIN_SENSOR_CAHAYA 5

// Global variables untuk sensor
static int sensorTerinitialisasi = 0;
static SensorData dataSensor[MAX_SENSORS];
static int jumlahSensor = 0;

// Inisialisasi sistem sensor
int inisialisasiSensor() {
    printf("Menginisialisasi sistem sensor...\n");
    
    // Reset data sensor
    memset(dataSensor, 0, sizeof(dataSensor));
    jumlahSensor = 0;
    
    // Daftarkan sensor yang tersedia
    daftarkanSensor("DHT22_SUHU", "Greenhouse_Utama", "°C");
    daftarkanSensor("DHT22_KELEMBABAN", "Greenhouse_Utama", "%");
    daftarkanSensor("SOIL_MOISTURE", "Bedeng_A", "%");
    daftarkanSensor("LDR_CAHAYA", "Greenhouse_Utama", "lux");
    
    sensorTerinitialisasi = 1;
    printf("Sistem sensor berhasil diinisialisasi\n");
    printf("Total sensor terdaftar: %d\n", jumlahSensor);
    
    return 0;
}

// Daftarkan sensor baru
int daftarkanSensor(char* tipe, char* lokasi, char* satuan) {
    if (jumlahSensor >= MAX_SENSORS) {
        printf("Maksimal sensor tercapai\n");
        return 1;
    }
    
    SensorData* sensor = &dataSensor[jumlahSensor];
    sensor->id = jumlahSensor + 1;
    strcpy(sensor->tipe, tipe);
    strcpy(sensor->lokasi, lokasi);
    strcpy(sensor->satuan, satuan);
    sensor->statusAktif = 1;
    
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(sensor->waktuBaca, sizeof(sensor->waktuBaca), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    jumlahSensor++;
    printf("Sensor %s berhasil didaftarkan di %s\n", tipe, lokasi);
    
    return 0;
}

// Baca sensor suhu (simulasi)
int bacaSensorSuhu(int pinSensor) {
    if (!sensorTerinitialisasi) {
        printf("Sistem sensor belum diinisialisasi\n");
        return -1;
    }
    
    // Simulasi pembacaan sensor dengan variasi realistis
    static float suhuBase = 25.0;
    float noise = ((rand() % 100) - 50) / 100.0; // ±0.5°C noise
    float suhu = suhuBase + noise + sin(time(NULL) / 3600.0) * 3.0; // Variasi harian
    
    // Update data sensor
    for (int i = 0; i < jumlahSensor; i++) {
        if (strcmp(dataSensor[i].tipe, "DHT22_SUHU") == 0) {
            dataSensor[i].nilai = suhu;
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(dataSensor[i].waktuBaca, sizeof(dataSensor[i].waktuBaca), 
                    "%Y-%m-%d %H:%M:%S", timeinfo);
            break;
        }
    }
    
    printf("Suhu terbaca: %.1f°C\n", suhu);
    return (int)(suhu * 10); // Return dalam format integer (x10)
}

// Baca sensor kelembaban udara (simulasi)
int bacaSensorKelembaban(int pinSensor) {
    if (!sensorTerinitialisasi) {
        printf("Sistem sensor belum diinisialisasi\n");
        return -1;
    }
    
    static float kelembabanBase = 65.0;
    float noise = ((rand() % 100) - 50) / 50.0; // ±1% noise
    float kelembaban = kelembabanBase + noise + cos(time(NULL) / 3600.0) * 10.0;
    
    // Batasi nilai 0-100%
    if (kelembaban < 0) kelembaban = 0;
    if (kelembaban > 100) kelembaban = 100;
    
    // Update data sensor
    for (int i = 0; i < jumlahSensor; i++) {
        if (strcmp(dataSensor[i].tipe, "DHT22_KELEMBABAN") == 0) {
            dataSensor[i].nilai = kelembaban;
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(dataSensor[i].waktuBaca, sizeof(dataSensor[i].waktuBaca), 
                    "%Y-%m-%d %H:%M:%S", timeinfo);
            break;
        }
    }
    
    printf("Kelembaban udara terbaca: %.1f%%\n", kelembaban);
    return (int)(kelembaban * 10);
}

// Baca sensor kelembaban tanah (simulasi)
int bacaSensorKelembapanTanah(int pinSensor) {
    if (!sensorTerinitialisasi) {
        printf("Sistem sensor belum diinisialisasi\n");
        return -1;
    }
    
    static float kelembabanTanahBase = 50.0;
    float noise = ((rand() % 100) - 50) / 25.0; // ±2% noise
    float kelembabanTanah = kelembabanTanahBase + noise;
    
    // Simulasi penurunan kelembaban tanah seiring waktu
    static time_t waktuTerakhirDisiram = 0;
    if (waktuTerakhirDisiram == 0) waktuTerakhirDisiram = time(NULL);
    
    time_t sekarang = time(NULL);
    double jamSejakDisiram = difftime(sekarang, waktuTerakhirDisiram) / 3600.0;
    kelembabanTanah -= jamSejakDisiram * 0.5; // Turun 0.5% per jam
    
    if (kelembabanTanah < 0) kelembabanTanah = 0;
    if (kelembabanTanah > 100) kelembabanTanah = 100;
    
    // Update data sensor
    for (int i = 0; i < jumlahSensor; i++) {
        if (strcmp(dataSensor[i].tipe, "SOIL_MOISTURE") == 0) {
            dataSensor[i].nilai = kelembabanTanah;
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(dataSensor[i].waktuBaca, sizeof(dataSensor[i].waktuBaca), 
                    "%Y-%m-%d %H:%M:%S", timeinfo);
            break;
        }
    }
    
    printf("Kelembaban tanah terbaca: %.1f%%\n", kelembabanTanah);
    return (int)(kelembabanTanah * 10);
}

// Baca sensor cahaya (simulasi)
int bacaSensorCahaya(int pinSensor) {
    if (!sensorTerinitialisasi) {
        printf("Sistem sensor belum diinisialisasi\n");
        return -1;
    }
    
    // Simulasi intensitas cahaya berdasarkan waktu
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    int jam = timeinfo->tm_hour;
    float cahayaBase;
    
    // Simulasi siklus cahaya harian
    if (jam >= 6 && jam <= 18) {
        // Siang hari
        cahayaBase = 500 + (1000 * sin((jam - 6) * M_PI / 12));
    } else {
        // Malam hari
        cahayaBase = 10 + (rand() % 50); // Cahaya buatan minimal
    }
    
    float noise = ((rand() % 100) - 50) * 5.0; // ±250 lux noise
    float cahaya = cahayaBase + noise;
    
    if (cahaya < 0) cahaya = 0;
    
    // Update data sensor
    for (int i = 0; i < jumlahSensor; i++) {
        if (strcmp(dataSensor[i].tipe, "LDR_CAHAYA") == 0) {
            dataSensor[i].nilai = cahaya;
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(dataSensor[i].waktuBaca, sizeof(dataSensor[i].waktuBaca), 
                    "%Y-%m-%d %H:%M:%S", timeinfo);
            break;
        }
    }
    
    printf("Intensitas cahaya terbaca: %.0f lux\n", cahaya);
    return (int)cahaya;
}

// Update data sensor secara otomatis
void updateDataSensorOtomatis() {
    if (!sensorTerinitialisasi) {
        printf("Sistem sensor belum diinisialisasi\n");
        return;
    }
    
    printf("\n=== Update Data Sensor Otomatis ===\n");
    
    // Baca semua sensor
    bacaSensorSuhu(PIN_SENSOR_SUHU);
    Sleep(100); // Delay antar pembacaan
    
    bacaSensorKelembaban(PIN_SENSOR_KELEMBABAN);
    Sleep(100);
    
    bacaSensorKelembapanTanah(PIN_SENSOR_KELEMBABAN_TANAH);
    Sleep(100);
    
    bacaSensorCahaya(PIN_SENSOR_CAHAYA);
    
    // Simpan ke database jika tersedia
    for (int i = 0; i < jumlahSensor; i++) {
        if (dataSensor[i].statusAktif) {
            simpanDataSensorDB(&dataSensor[i]);
        }
    }
    
    // Periksa kondisi yang memerlukan peringatan
    periksaPeningatanOtomatis();
    
    printf("=== Update Selesai ===\n\n");
}

// Dapatkan data sensor terbaru
SensorData* dapatkanDataSensor(char* tipeSensor) {
    for (int i = 0; i < jumlahSensor; i++) {
        if (strcmp(dataSensor[i].tipe, tipeSensor) == 0) {
            return &dataSensor[i];
        }
    }
    return NULL;
}

// Tampilkan status semua sensor
void tampilkanStatusSensor() {
    if (!sensorTerinitialisasi) {
        printf("Sistem sensor belum diinisialisasi\n");
        return;
    }
    
    printf("\n=== Status Sensor Realtime ===\n");
    printf("%-20s %-20s %-10s %-10s %-20s %-10s\n", 
           "Tipe Sensor", "Lokasi", "Nilai", "Satuan", "Waktu Baca", "Status");
    printf("----------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < jumlahSensor; i++) {
        SensorData* sensor = &dataSensor[i];
        printf("%-20s %-20s %-10.1f %-10s %-20s %-10s\n",
               sensor->tipe,
               sensor->lokasi,
               sensor->nilai,
               sensor->satuan,
               sensor->waktuBaca,
               sensor->statusAktif ? "Aktif" : "Nonaktif");
    }
    
    printf("\n");
}

// Kalibrasi sensor
int kalibrasiSensor(char* tipeSensor, float nilaiReferensi) {
    SensorData* sensor = dapatkanDataSensor(tipeSensor);
    if (!sensor) {
        printf("Sensor %s tidak ditemukan\n", tipeSensor);
        return 1;
    }
    
    float selisih = nilaiReferensi - sensor->nilai;
    printf("Kalibrasi sensor %s:\n", tipeSensor);
    printf("Nilai saat ini: %.2f %s\n", sensor->nilai, sensor->satuan);
    printf("Nilai referensi: %.2f %s\n", nilaiReferensi, sensor->satuan);
    printf("Selisih: %.2f %s\n", selisih, sensor->satuan);
    
    // Simpan offset kalibrasi (implementasi sederhana)
    sensor->nilai = nilaiReferensi;
    printf("Sensor berhasil dikalibrasi\n");
    
    return 0;
}

// Thread untuk monitoring kontinu
DWORD WINAPI threadMonitoringSensor(LPVOID lpParam) {
    while (1) {
        updateDataSensorOtomatis();
        Sleep(30000); // Update setiap 30 detik
    }
    return 0;
}

// Mulai monitoring otomatis
HANDLE mulaiMonitoringOtomatis() {
    if (!sensorTerinitialisasi) {
        printf("Sistem sensor belum diinisialisasi\n");
        return NULL;
    }
    
    HANDLE threadHandle = CreateThread(NULL, 0, threadMonitoringSensor, NULL, 0, NULL);
    if (threadHandle == NULL) {
        printf("Gagal membuat thread monitoring\n");
        return NULL;
    }
    
    printf("Monitoring otomatis dimulai\n");
    return threadHandle;
}
