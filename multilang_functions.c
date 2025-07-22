#include "greenhouse_advanced_features.h"
#include <windows.h>

// Global variables untuk multi-bahasa
static KonfigurasiBahasa bahasaAktif = {"id", "Indonesia", 1};
static char teksBahasa[1000][2][200]; // [kunci][bahasa][teks]
static int jumlahTeks = 0;

// Struktur teks untuk ID dan EN
typedef struct {
    char kunci[50];
    char indonesia[200];
    char english[200];
} TeksBahasa;

// Database teks multi-bahasa
static TeksBahasa databaseTeks[] = {
    {"menu_utama", "MENU UTAMA", "MAIN MENU"},
    {"manajemen_tanaman", "Manajemen Tanaman", "Plant Management"},
    {"manajemen_peralatan", "Manajemen Peralatan", "Equipment Management"},
    {"monitoring_sensor", "Monitoring Sensor", "Sensor Monitoring"},
    {"notifikasi", "Notifikasi & Peringatan", "Notifications & Alerts"},
    {"dashboard_web", "Dashboard Web", "Web Dashboard"},
    {"ekspor_laporan", "Ekspor & Laporan", "Export & Reports"},
    {"pengaturan_sistem", "Pengaturan Sistem", "System Settings"},
    {"keluar", "Keluar", "Exit"},
    
    // Menu tanaman
    {"pantau_kesehatan", "Pantau Kesehatan", "Monitor Health"},
    {"riwayat_siram", "Lihat Riwayat Siram", "View Watering History"},
    {"catat_penyiraman", "Catat Penyiraman", "Record Watering"},
    {"statistik_tanaman", "Statistik Tanaman", "Plant Statistics"},
    {"tambah_tanaman", "Tambah Tanaman Baru", "Add New Plant"},
    {"lihat_tanaman", "Lihat Semua Tanaman", "View All Plants"},
    {"hapus_tanaman", "Hapus Data Tanaman", "Delete Plant Data"},
    {"pengingat_perawatan", "Pengingat Perawatan", "Care Reminder"},
    
    // Status dan kondisi
    {"suhu", "Suhu", "Temperature"},
    {"kelembaban", "Kelembaban", "Humidity"},
    {"kelembaban_tanah", "Kelembaban Tanah", "Soil Moisture"},
    {"intensitas_cahaya", "Intensitas Cahaya", "Light Intensity"},
    {"normal", "Normal", "Normal"},
    {"peringatan", "Peringatan", "Warning"},
    {"bahaya", "Bahaya", "Danger"},
    
    // Notifikasi
    {"notif_suhu_tinggi", "PERINGATAN: Suhu greenhouse terlalu tinggi!", "WARNING: Greenhouse temperature too high!"},
    {"notif_suhu_rendah", "PERINGATAN: Suhu greenhouse terlalu rendah!", "WARNING: Greenhouse temperature too low!"},
    {"notif_tanah_kering", "PERINGATAN: Kelembaban tanah sangat rendah!", "WARNING: Soil moisture very low!"},
    {"notif_siram_tanaman", "INFO: Tanaman perlu disiram dalam waktu dekat.", "INFO: Plants need watering soon."},
    
    // Pesan sistem
    {"berhasil_simpan", "Data berhasil disimpan", "Data saved successfully"},
    {"gagal_simpan", "Gagal menyimpan data", "Failed to save data"},
    {"database_error", "Error koneksi database", "Database connection error"},
    {"file_tidak_ditemukan", "File tidak ditemukan", "File not found"},
    {"input_tidak_valid", "Input tidak valid", "Invalid input"},
    
    // Dashboard web
    {"dashboard_title", "Dashboard Monitoring Greenhouse ITTS", "ITTS Greenhouse Monitoring Dashboard"},
    {"realtime_monitoring", "Real-time monitoring sistem greenhouse", "Real-time greenhouse system monitoring"},
    {"suhu_lingkungan", "Suhu Lingkungan", "Environment Temperature"},
    {"kelembaban_udara", "Kelembaban Udara", "Air Humidity"},
    {"status", "Status", "Status"},
    {"refresh_data", "Refresh Data", "Refresh Data"},
    {"ekspor_data", "Ekspor Data", "Export Data"},
    
    // Pengaturan
    {"pilih_bahasa", "Pilih Bahasa", "Select Language"},
    {"bahasa_indonesia", "Bahasa Indonesia", "Indonesian Language"},
    {"bahasa_inggris", "English Language", "English Language"},
    {"pengaturan_berhasil", "Pengaturan berhasil disimpan", "Settings saved successfully"},
    
    // Laporan
    {"laporan_harian", "Laporan Harian", "Daily Report"},
    {"laporan_mingguan", "Laporan Mingguan", "Weekly Report"},
    {"ekspor_csv", "Ekspor ke CSV", "Export to CSV"},
    {"ekspor_excel", "Ekspor ke Excel", "Export to Excel"},
    
    // Sensor
    {"sensor_aktif", "Aktif", "Active"},
    {"sensor_nonaktif", "Nonaktif", "Inactive"},
    {"pembacaan_sensor", "Pembacaan Sensor", "Sensor Reading"},
    {"kalibrasi_sensor", "Kalibrasi Sensor", "Sensor Calibration"},
    
    // Waktu
    {"hari_ini", "Hari Ini", "Today"},
    {"kemarin", "Kemarin", "Yesterday"},
    {"minggu_ini", "Minggu Ini", "This Week"},
    {"bulan_ini", "Bulan Ini", "This Month"}
};

// Inisialisasi sistem multi-bahasa
int muatBahasa(char* kodeBahasa) {
    strcpy(bahasaAktif.kodeBahasa, kodeBahasa);
    
    if (strcmp(kodeBahasa, "en") == 0) {
        strcpy(bahasaAktif.namaBahasa, "English");
    } else {
        strcpy(bahasaAktif.namaBahasa, "Indonesia");
        strcpy(bahasaAktif.kodeBahasa, "id"); // Default ke Indonesia
    }
    
    bahasaAktif.statusAktif = 1;
    
    printf("Bahasa berhasil diubah ke: %s\n", bahasaAktif.namaBahasa);
    return 0;
}

// Dapatkan teks berdasarkan kunci dan bahasa aktif
char* dapatkanTeks(char* kunci) {
    int jumlahEntri = sizeof(databaseTeks) / sizeof(TeksBahasa);
    
    for (int i = 0; i < jumlahEntri; i++) {
        if (strcmp(databaseTeks[i].kunci, kunci) == 0) {
            if (strcmp(bahasaAktif.kodeBahasa, "en") == 0) {
                return databaseTeks[i].english;
            } else {
                return databaseTeks[i].indonesia;
            }
        }
    }
    
    // Jika tidak ditemukan, kembalikan kunci asli
    return kunci;
}

// Menu pengaturan bahasa
void menuPengaturanBahasa() {
    int pilihan;
    
    bersihkanLayar();
    printf("═══════════════════════════════════════════════════════════\n");
    printf("               %s\n", dapatkanTeks("pilih_bahasa"));
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Bahasa saat ini: %s\n\n", bahasaAktif.namaBahasa);
    
    printf("1. %s\n", dapatkanTeks("bahasa_indonesia"));
    printf("2. %s\n", dapatkanTeks("bahasa_inggris"));
    printf("3. Kembali\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    printf("Pilih bahasa (1-3): ");
    scanf("%d", &pilihan);
    
    switch (pilihan) {
        case 1:
            muatBahasa("id");
            simpanKonfigurasi();
            printf("\n%s\n", dapatkanTeks("pengaturan_berhasil"));
            break;
            
        case 2:
            muatBahasa("en");
            simpanKonfigurasi();
            printf("\n%s\n", dapatkanTeks("pengaturan_berhasil"));
            break;
            
        case 3:
            return;
            
        default:
            printf("%s\n", dapatkanTeks("input_tidak_valid"));
    }
    
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Simpan konfigurasi bahasa ke file
int simpanKonfigurasi() {
    FILE* file = fopen("config_bahasa.txt", "w");
    if (!file) {
        printf("Gagal menyimpan konfigurasi bahasa\n");
        return 1;
    }
    
    fprintf(file, "KODE_BAHASA=%s\n", bahasaAktif.kodeBahasa);
    fprintf(file, "NAMA_BAHASA=%s\n", bahasaAktif.namaBahasa);
    fprintf(file, "STATUS_AKTIF=%d\n", bahasaAktif.statusAktif);
    
    fclose(file);
    return 0;
}

// Muat konfigurasi bahasa dari file
int muatKonfigurasi() {
    FILE* file = fopen("config_bahasa.txt", "r");
    if (!file) {
        // File tidak ada, gunakan default Indonesia
        muatBahasa("id");
        return 0;
    }
    
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "KODE_BAHASA=", 12) == 0) {
            sscanf(line, "KODE_BAHASA=%s", bahasaAktif.kodeBahasa);
        } else if (strncmp(line, "NAMA_BAHASA=", 12) == 0) {
            sscanf(line, "NAMA_BAHASA=%s", bahasaAktif.namaBahasa);
        } else if (strncmp(line, "STATUS_AKTIF=", 13) == 0) {
            sscanf(line, "STATUS_AKTIF=%d", &bahasaAktif.statusAktif);
        }
    }
    
    fclose(file);
    return 0;
}

// Fungsi untuk mendapatkan teks notifikasi
char* dapatkanTeksNotifikasi(char* jenisNotifikasi, float nilai) {
    static char pesanLengkap[300];
    
    if (strcmp(jenisNotifikasi, "suhu_tinggi") == 0) {
        if (strcmp(bahasaAktif.kodeBahasa, "en") == 0) {
            snprintf(pesanLengkap, sizeof(pesanLengkap), 
                    "WARNING: Temperature too high (%.1f°C)! Activate ventilation immediately.", nilai);
        } else {
            snprintf(pesanLengkap, sizeof(pesanLengkap), 
                    "PERINGATAN: Suhu terlalu tinggi (%.1f°C)! Segera aktifkan ventilasi.", nilai);
        }
    } else if (strcmp(jenisNotifikasi, "tanah_kering") == 0) {
        if (strcmp(bahasaAktif.kodeBahasa, "en") == 0) {
            snprintf(pesanLengkap, sizeof(pesanLengkap), 
                    "WARNING: Soil moisture very low (%.1f%%)! Water the plants immediately.", nilai);
        } else {
            snprintf(pesanLengkap, sizeof(pesanLengkap), 
                    "PERINGATAN: Kelembaban tanah sangat rendah (%.1f%%)! Segera siram tanaman.", nilai);
        }
    } else {
        strcpy(pesanLengkap, dapatkanTeks(jenisNotifikasi));
    }
    
    return pesanLengkap;
}

// Update halaman web dengan bahasa yang dipilih
int updateWebPageLanguage() {
    // Fungsi ini akan mengupdate konten halaman web berdasarkan bahasa aktif
    // Implementasi akan mengubah template HTML sesuai bahasa
    
    char* judulDashboard = dapatkanTeks("dashboard_title");
    char* monitoring = dapatkanTeks("realtime_monitoring");
    
    printf("Web dashboard updated to language: %s\n", bahasaAktif.namaBahasa);
    printf("Title: %s\n", judulDashboard);
    printf("Subtitle: %s\n", monitoring);
    
    return 0;
}

// Fungsi untuk menampilkan menu dalam bahasa yang dipilih
void tampilkanMenuMultiBahasa() {
    printf("═══════════════════════════════════════════════════════════\n");
    printf("                    %s\n", dapatkanTeks("menu_utama"));
    printf("═══════════════════════════════════════════════════════════\n");
    printf("1. %s\n", dapatkanTeks("manajemen_tanaman"));
    printf("2. %s\n", dapatkanTeks("manajemen_peralatan"));
    printf("3. %s\n", dapatkanTeks("monitoring_sensor"));
    printf("4. %s\n", dapatkanTeks("notifikasi"));
    printf("5. %s\n", dapatkanTeks("dashboard_web"));
    printf("6. %s\n", dapatkanTeks("ekspor_laporan"));
    printf("7. %s\n", dapatkanTeks("pengaturan_sistem"));
    printf("8. %s\n", dapatkanTeks("keluar"));
    printf("═══════════════════════════════════════════════════════════\n");
}

// Test fungsi multi-bahasa
void testMultiBahasa() {
    printf("\n=== TEST MULTI-BAHASA ===\n");
    
    // Test Indonesia
    muatBahasa("id");
    printf("\nBahasa Indonesia:\n");
    printf("- %s\n", dapatkanTeks("menu_utama"));
    printf("- %s\n", dapatkanTeks("manajemen_tanaman"));
    printf("- %s\n", dapatkanTeks("notif_suhu_tinggi"));
    
    // Test English
    muatBahasa("en");
    printf("\nEnglish Language:\n");
    printf("- %s\n", dapatkanTeks("menu_utama"));
    printf("- %s\n", dapatkanTeks("manajemen_tanaman"));
    printf("- %s\n", dapatkanTeks("notif_suhu_tinggi"));
    
    // Kembali ke Indonesia
    muatBahasa("id");
    
    printf("\nTest multi-bahasa selesai.\n");
}

// Inisialisasi sistem multi-bahasa saat startup
int inisialisasiMultiBahasa() {
    printf("Menginisialisasi sistem multi-bahasa...\n");
    
    // Muat konfigurasi yang tersimpan
    muatKonfigurasi();
    
    printf("Bahasa aktif: %s (%s)\n", bahasaAktif.namaBahasa, bahasaAktif.kodeBahasa);
    return 0;
}
