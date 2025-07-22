#ifndef GREENHOUSE_ADVANCED_FEATURES_H
#define GREENHOUSE_ADVANCED_FEATURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

// Konstanta untuk fitur advanced
#define DATABASE_NAME "greenhouse_data.db"
#define CSV_EXPORT_PATH "exports/"
#define WEB_PORT 8080
#define MAX_SENSORS 20
#define MAX_NOTIFICATIONS 100

// Struktur untuk sensor data
typedef struct {
    int id;
    char tipe[50];
    char lokasi[100];
    float nilai;
    char satuan[20];
    char waktuBaca[30];
    int statusAktif;
} SensorData;

// Struktur untuk konfigurasi jaringan
typedef struct {
    char ipAddress[16];
    int port;
    char ssid[50];
    char password[50];
    int statusKoneksi;
} KonfigurasiJaringan;

// Struktur untuk ekspor data
typedef struct {
    char formatFile[10];
    char namaFile[100];
    char tanggalMulai[20];
    char tanggalAkhir[20];
    int jenisData; // 1=Tanaman, 2=Sensor, 3=Inventaris
} ParameterEkspor;

// Struktur untuk pengaturan bahasa
typedef struct {
    char kodeBahasa[5];
    char namaBahasa[30];
    int statusAktif;
} KonfigurasiBahasa;

// Deklarasi fungsi database
int inisialisasiDatabase();
int simpanDataTanamanDB(DataTanaman* tanaman);
int simpanDataSensorDB(SensorData* sensor);
int ambilDataTanamanDB(DataTanaman* tanaman, int limit);
int tutupDatabase();

// Deklarasi fungsi jaringan
int inisialisasiJaringan();
int mulaiWebServer(int port);
int kirimDataKeServer(char* data);
int cekStatusKoneksi();

// Deklarasi fungsi sensor
int inisialisasiSensor();
int bacaSensorSuhu(int pinSensor);
int bacaSensorKelembaban(int pinSensor);
int bacaSensorKelembapanTanah(int pinSensor);
int bacaSensorCahaya(int pinSensor);
void updateDataSensorOtomatis();

// Deklarasi fungsi ekspor
int eksporKeCSV(ParameterEkspor* param);
int eksporKeExcel(ParameterEkspor* param);
int buatLaporanHarian();
int buatLaporanMingguan();

// Deklarasi fungsi notifikasi
int kirimNotifikasiPush(char* pesan, int prioritas);
int kirimNotifikasiEmail(char* email, char* subjek, char* pesan);
int kirimNotifikasiSMS(char* nomorHP, char* pesan);
void periksaPeningatanOtomatis();

// Deklarasi fungsi multi-bahasa
int muatBahasa(char* kodeBahasa);
char* dapatkanTeks(char* kunci);
int simpanKonfigurasi();

// Deklarasi fungsi dashboard web
int buatHalamanDashboard();
int updateDataRealtime();
int tanganiRequestWeb(char* request);

#endif
