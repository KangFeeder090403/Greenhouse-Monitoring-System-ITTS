#include "greenhouse_advanced_features.h"
#include <windows.h>

// Ekspor data ke format CSV
int eksporKeCSV(ParameterEkspor* param) {
    FILE* file;
    char namaFileLengkap[200];
    time_t rawtime;
    struct tm* timeinfo;
    char timestamp[50];
    
    // Buat nama file dengan timestamp
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", timeinfo);
    
    snprintf(namaFileLengkap, sizeof(namaFileLengkap), "%s%s_%s.csv", 
             CSV_EXPORT_PATH, param->namaFile, timestamp);
    
    // Buat direktori ekspor jika belum ada
    CreateDirectoryA(CSV_EXPORT_PATH, NULL);
    
    file = fopen(namaFileLengkap, "w");
    if (!file) {
        printf("Gagal membuat file ekspor: %s\n", namaFileLengkap);
        return 1;
    }
    
    // Tulis header CSV berdasarkan jenis data
    switch (param->jenisData) {
        case 1: // Data Tanaman
            fprintf(file, "Nama Tanaman,Jenis,Suhu,Kelembaban,Kelembaban Tanah,Intensitas Cahaya,Terakhir Disiram,Tanggal Tanam,Skor Kesehatan,Waktu Input\n");
            eksporDataTanamanCSV(file, param);
            break;
            
        case 2: // Data Sensor
            fprintf(file, "ID,Tipe Sensor,Lokasi,Nilai,Satuan,Waktu Baca,Status\n");
            eksporDataSensorCSV(file, param);
            break;
            
        case 3: // Data Inventaris
            fprintf(file, "Nama Item,Jumlah,Tanggal,Harga,Kategori,Stok Minimal,Waktu Update\n");
            eksporDataInventarisCSV(file, param);
            break;
            
        default:
            fprintf(file, "Jenis data tidak valid\n");
    }
    
    fclose(file);
    printf("Data berhasil diekspor ke: %s\n", namaFileLengkap);
    
    return 0;
}

// Ekspor data tanaman ke CSV
int eksporDataTanamanCSV(FILE* file, ParameterEkspor* param) {
    DataTanaman tanaman[TANAMAN_MAX];
    int jumlahData = ambilDataTanamanDB(tanaman, TANAMAN_MAX);
    
    for (int i = 0; i < jumlahData; i++) {
        fprintf(file, "\"%s\",\"%s\",%.1f,%.1f,%.1f,%.1f,\"%s\",\"%s\",%d,\"%s\"\n",
                tanaman[i].namaTanaman,
                tanaman[i].jenisTanaman,
                tanaman[i].suhu,
                tanaman[i].kelembaban,
                tanaman[i].kelembapanTanah,
                tanaman[i].intensitasCahaya,
                tanaman[i].terakhirDisiram,
                tanaman[i].tanggalTanam,
                tanaman[i].skorKesehatan,
                "2025-07-22 12:00:00"); // Placeholder timestamp
    }
    
    return 0;
}

// Ekspor data sensor ke CSV
int eksporDataSensorCSV(FILE* file, ParameterEkspor* param) {
    // Ambil data sensor dari array global atau database
    for (int i = 0; i < jumlahSensor; i++) {
        SensorData* sensor = &dataSensor[i];
        fprintf(file, "%d,\"%s\",\"%s\",%.2f,\"%s\",\"%s\",\"%s\"\n",
                sensor->id,
                sensor->tipe,
                sensor->lokasi,
                sensor->nilai,
                sensor->satuan,
                sensor->waktuBaca,
                sensor->statusAktif ? "Aktif" : "Nonaktif");
    }
    
    return 0;
}

// Ekspor data inventaris ke CSV
int eksporDataInventarisCSV(FILE* file, ParameterEkspor* param) {
    FILE* fileInventaris = fopen(FILE_INVENTARIS, "r");
    if (!fileInventaris) {
        printf("File inventaris tidak ditemukan\n");
        return 1;
    }
    
    char line[500];
    while (fgets(line, sizeof(line), fileInventaris)) {
        // Parse dan format ulang data inventaris
        ItemInventaris item;
        if (sscanf(line, "%99[^,],%d,%99[^,],%f,%99[^,],%d",
                   item.nama, &item.jumlah, item.tanggal, 
                   &item.harga, item.kategori, &item.stokMinimal) == 6) {
            
            fprintf(file, "\"%s\",%d,\"%s\",%.2f,\"%s\",%d,\"%s\"\n",
                    item.nama, item.jumlah, item.tanggal,
                    item.harga, item.kategori, item.stokMinimal,
                    "2025-07-22 12:00:00"); // Placeholder timestamp
        }
    }
    
    fclose(fileInventaris);
    return 0;
}

// Buat laporan harian
int buatLaporanHarian() {
    FILE* file;
    char namaFile[100];
    time_t rawtime;
    struct tm* timeinfo;
    char tanggal[20];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(tanggal, sizeof(tanggal), "%Y-%m-%d", timeinfo);
    
    snprintf(namaFile, sizeof(namaFile), "%slaporan_harian_%s.txt", 
             CSV_EXPORT_PATH, tanggal);
    
    CreateDirectoryA(CSV_EXPORT_PATH, NULL);
    
    file = fopen(namaFile, "w");
    if (!file) {
        printf("Gagal membuat laporan harian\n");
        return 1;
    }
    
    fprintf(file, "===========================================\n");
    fprintf(file, "     LAPORAN HARIAN GREENHOUSE ITTS\n");
    fprintf(file, "===========================================\n");
    fprintf(file, "Tanggal: %s\n\n", tanggal);
    
    // Ringkasan sensor
    fprintf(file, "RINGKASAN DATA SENSOR:\n");
    fprintf(file, "-----------------------------------------\n");
    
    for (int i = 0; i < jumlahSensor; i++) {
        SensorData* sensor = &dataSensor[i];
        fprintf(file, "%-20s: %.2f %s (%s)\n", 
                sensor->tipe, sensor->nilai, sensor->satuan, sensor->lokasi);
    }
    
    // Status peringatan
    fprintf(file, "\nSTATUS PERINGATAN:\n");
    fprintf(file, "-----------------------------------------\n");
    
    // Periksa kondisi bermasalah
    SensorData* suhu = dapatkanDataSensor("DHT22_SUHU");
    if (suhu && (suhu->nilai < 20 || suhu->nilai > 35)) {
        fprintf(file, "⚠️ PERINGATAN: Suhu di luar rentang optimal (%.1f°C)\n", suhu->nilai);
    }
    
    SensorData* kelembaban = dapatkanDataSensor("DHT22_KELEMBABAN");
    if (kelembaban && (kelembaban->nilai < 60 || kelembaban->nilai > 80)) {
        fprintf(file, "⚠️ PERINGATAN: Kelembaban di luar rentang optimal (%.1f%%)\n", kelembaban->nilai);
    }
    
    SensorData* tanah = dapatkanDataSensor("SOIL_MOISTURE");
    if (tanah && tanah->nilai < 40) {
        fprintf(file, "⚠️ PERINGATAN: Kelembaban tanah rendah (%.1f%%)\n", tanah->nilai);
    }
    
    fprintf(file, "\nLaporan dibuat otomatis oleh sistem\n");
    fprintf(file, "Waktu pembuatan: %s", ctime(&rawtime));
    
    fclose(file);
    printf("Laporan harian berhasil dibuat: %s\n", namaFile);
    
    return 0;
}

// Kirim notifikasi push (simulasi)
int kirimNotifikasiPush(char* pesan, int prioritas) {
    time_t rawtime;
    struct tm* timeinfo;
    char waktu[50];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(waktu, sizeof(waktu), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    printf("\n📱 NOTIFIKASI PUSH [Prioritas: %s]\n", 
           prioritas == 3 ? "TINGGI" : prioritas == 2 ? "SEDANG" : "RENDAH");
    printf("Waktu: %s\n", waktu);
    printf("Pesan: %s\n", pesan);
    printf("Status: Terkirim\n\n");
    
    // Simpan notifikasi ke file
    FILE* file = fopen(FILE_NOTIFIKASI, "a");
    if (file) {
        fprintf(file, "PUSH,%s,%s,%d\n", pesan, waktu, prioritas);
        fclose(file);
    }
    
    return 0;
}

// Kirim notifikasi email (simulasi)
int kirimNotifikasiEmail(char* email, char* subjek, char* pesan) {
    time_t rawtime;
    struct tm* timeinfo;
    char waktu[50];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(waktu, sizeof(waktu), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    printf("\n📧 EMAIL NOTIFICATION\n");
    printf("Kepada: %s\n", email);
    printf("Subjek: %s\n", subjek);
    printf("Pesan: %s\n", pesan);
    printf("Waktu: %s\n", waktu);
    printf("Status: Terkirim\n\n");
    
    // Simpan log email
    FILE* file = fopen(FILE_NOTIFIKASI, "a");
    if (file) {
        fprintf(file, "EMAIL,%s,%s,2\n", subjek, waktu);
        fclose(file);
    }
    
    return 0;
}

// Kirim notifikasi SMS (simulasi)
int kirimNotifikasiSMS(char* nomorHP, char* pesan) {
    time_t rawtime;
    struct tm* timeinfo;
    char waktu[50];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(waktu, sizeof(waktu), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    printf("\n📱 SMS NOTIFICATION\n");
    printf("Nomor: %s\n", nomorHP);
    printf("Pesan: %s\n", pesan);
    printf("Waktu: %s\n", waktu);
    printf("Status: Terkirim\n\n");
    
    // Simpan log SMS
    FILE* file = fopen(FILE_NOTIFIKASI, "a");
    if (file) {
        fprintf(file, "SMS,%s,%s,1\n", pesan, waktu);
        fclose(file);
    }
    
    return 0;
}

// Periksa peringatan otomatis
void periksaPeningatanOtomatis() {
    SensorData* suhu = dapatkanDataSensor("DHT22_SUHU");
    SensorData* kelembaban = dapatkanDataSensor("DHT22_KELEMBABAN");
    SensorData* tanah = dapatkanDataSensor("SOIL_MOISTURE");
    SensorData* cahaya = dapatkanDataSensor("LDR_CAHAYA");
    
    // Periksa suhu
    if (suhu) {
        if (suhu->nilai > 35) {
            kirimNotifikasiPush("PERINGATAN: Suhu greenhouse terlalu tinggi! Segera aktifkan ventilasi.", 3);
            kirimNotifikasiEmail("admin@greenhouse.com", "Suhu Tinggi", 
                               "Suhu greenhouse mencapai level berbahaya. Tindakan segera diperlukan.");
        } else if (suhu->nilai < 15) {
            kirimNotifikasiPush("PERINGATAN: Suhu greenhouse terlalu rendah! Periksa sistem pemanas.", 3);
        }
    }
    
    // Periksa kelembaban tanah
    if (tanah) {
        if (tanah->nilai < 30) {
            kirimNotifikasiPush("PERINGATAN: Kelembaban tanah sangat rendah! Segera lakukan penyiraman.", 3);
            kirimNotifikasiSMS("+6281234567890", "Kelembaban tanah kritikal. Segera siram tanaman!");
        } else if (tanah->nilai < 40) {
            kirimNotifikasiPush("INFO: Tanaman perlu disiram dalam waktu dekat.", 2);
        }
    }
    
    // Periksa kelembaban udara
    if (kelembaban) {
        if (kelembaban->nilai > 90) {
            kirimNotifikasiPush("PERINGATAN: Kelembaban udara terlalu tinggi! Risiko jamur meningkat.", 2);
        }
    }
    
    // Periksa cahaya (malam hari)
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    if (cahaya && timeinfo->tm_hour >= 6 && timeinfo->tm_hour <= 18) {
        if (cahaya->nilai < 200) {
            kirimNotifikasiPush("INFO: Intensitas cahaya rendah. Pertimbangkan lampu tambahan.", 1);
        }
    }
}

// Menu ekspor data interaktif
void menuEksporData() {
    int pilihan;
    ParameterEkspor param;
    
    bersihkanLayar();
    printf("===========================================\n");
    printf("           MENU EKSPOR DATA\n");
    printf("===========================================\n");
    printf("1. Ekspor Data Tanaman ke CSV\n");
    printf("2. Ekspor Data Sensor ke CSV\n");
    printf("3. Ekspor Data Inventaris ke CSV\n");
    printf("4. Buat Laporan Harian\n");
    printf("5. Buat Laporan Mingguan\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("===========================================\n");
    printf("Pilih opsi: ");
    
    scanf("%d", &pilihan);
    
    switch (pilihan) {
        case 1:
            strcpy(param.namaFile, "data_tanaman");
            param.jenisData = 1;
            eksporKeCSV(&param);
            break;
            
        case 2:
            strcpy(param.namaFile, "data_sensor");
            param.jenisData = 2;
            eksporKeCSV(&param);
            break;
            
        case 3:
            strcpy(param.namaFile, "data_inventaris");
            param.jenisData = 3;
            eksporKeCSV(&param);
            break;
            
        case 4:
            buatLaporanHarian();
            break;
            
        case 5:
            printf("Fitur laporan mingguan akan segera tersedia\n");
            break;
            
        case 0:
            return;
            
        default:
            printf("Pilihan tidak valid\n");
    }
    
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
    getchar();
}
