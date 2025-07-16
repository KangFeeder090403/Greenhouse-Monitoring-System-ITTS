#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Konstanta sistem
#define PANJANG_STRING_MAX 100
#define TANAMAN_MAX 50
#define PERALATAN_MAX 100
#define FILE_INVENTARIS "data_inventaris.txt"
#define FILE_TERAKHIR_DISIRAM "tanggal_siram.txt"
#define FILE_DATA_TANAMAN "data_tanaman.txt"
#define FILE_NOTIFIKASI "notifikasi.txt"

// Struktur data sistem
typedef struct {
    char nama[PANJANG_STRING_MAX];
    int jumlah;
    char tanggal[PANJANG_STRING_MAX];
    float harga;
    char kategori[PANJANG_STRING_MAX];
    int stokMinimal;
} ItemInventaris;

typedef struct {
    char namaTanaman[PANJANG_STRING_MAX];
    char jenisTanaman[PANJANG_STRING_MAX];
    float suhu;
    float kelembaban;
    float kelembapanTanah;
    float intensitasCahaya;
    char terakhirDisiram[PANJANG_STRING_MAX];
    char tanggalTanam[PANJANG_STRING_MAX];
    int skorKesehatan;
} DataTanaman;

typedef struct {
    char jenisNotifikasi[PANJANG_STRING_MAX];
    char pesan[PANJANG_STRING_MAX];
    char waktu[PANJANG_STRING_MAX];
    int prioritas; // 1=Rendah, 2=Sedang, 3=Tinggi
} Notifikasi;

// Deklarasi fungsi utama
void tampilkanMenuUtama();
void tampilkanMenuTanaman();
void tampilkanMenuPeralatan();
void tampilkanMenuPengaturan();
void bersihkanLayar();
void tekanEnterUntukLanjut();
void tampilkanLayarSelamatDatang();

// Fungsi monitoring tanaman
void pantauKesehatanTanaman();
void lihatTanggalTerakhirDisiram();
void perbaruiTanggalSiram();
void lihatStatistikTanaman();
void tambahDataTanaman();
void lihatSemuaTanaman();
void hapusDataTanaman();
void pengingatPerawatan();

// Fungsi peralatan
void cekInventaris();
void perbaruiInventaris();
void cariItemInventaris();
void buatLaporanInventaris();
void hapusItemInventaris();
void notifikasiStokRendah();
void statistikInventaris();

// Sistem notifikasi
void cekNotifikasi();
void tambahNotifikasi(const char* jenis, const char* pesan, int prioritas);
void lihatNotifikasi();
void hapusNotifikasi();

// Pengaturan dan utilitas
void pengaturanSistem();
void eksporData();
void imporData();
void backupData();
void tentangSistem();

// Fungsi utilitas
void dapatkanTanggalSaatIni(char *stringTanggal);
void dapatkanWaktuSaatIni(char *stringWaktu);
int validasiTanggal(const char *tanggal);
void tampilkanHeader(const char *judul);
void tampilkanSubHeader(const char *subjudul);
float buatPembacaanSensor(float min, float max);
int hitungSkorKesehatan(float suhu, float kelembaban, float kelembapanTanah, float cahaya);
void bersihkanString(char *str);

int main() {
    int pilihan;
    
    tampilkanLayarSelamatDatang();
    
    do {
        bersihkanLayar();
        tampilkanMenuUtama();
        
        printf("Masukkan pilihan Anda (1-5): ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid! Harap masukkan angka.\n");
            while (getchar() != '\n'); // Bersihkan buffer input
            tekanEnterUntukLanjut();
            continue;
        }
        
        switch (pilihan) {
            case 1: {
                // Manajemen Tanaman
                int pilihanTanaman;
                do {
                    bersihkanLayar();
                    tampilkanMenuTanaman();
                    printf("Masukkan pilihan Anda (1-9): ");
                    
                    if (scanf("%d", &pilihanTanaman) != 1) {
                        printf("Input tidak valid! Harap masukkan angka.\n");
                        while (getchar() != '\n');
                        tekanEnterUntukLanjut();
                        continue;
                    }
                    
                    switch (pilihanTanaman) {
                        case 1: pantauKesehatanTanaman(); break;
                        case 2: lihatTanggalTerakhirDisiram(); break;
                        case 3: perbaruiTanggalSiram(); break;
                        case 4: lihatStatistikTanaman(); break;
                        case 5: tambahDataTanaman(); break;
                        case 6: lihatSemuaTanaman(); break;
                        case 7: hapusDataTanaman(); break;
                        case 8: pengingatPerawatan(); break;
                        case 9: printf("Kembali ke menu utama...\n"); break;
                        default:
                            printf("Pilihan tidak valid! Masukkan angka antara 1-9.\n");
                            tekanEnterUntukLanjut();
                    }
                } while (pilihanTanaman != 9);
                break;
            }
            
            case 2: {
                // Manajemen Peralatan
                int pilihanPeralatan;
                do {
                    bersihkanLayar();
                    tampilkanMenuPeralatan();
                    printf("Masukkan pilihan Anda (1-8): ");
                    
                    if (scanf("%d", &pilihanPeralatan) != 1) {
                        printf("Input tidak valid! Harap masukkan angka.\n");
                        while (getchar() != '\n');
                        tekanEnterUntukLanjut();
                        continue;
                    }
                    
                    switch (pilihanPeralatan) {
                        case 1: cekInventaris(); break;
                        case 2: perbaruiInventaris(); break;
                        case 3: cariItemInventaris(); break;
                        case 4: buatLaporanInventaris(); break;
                        case 5: hapusItemInventaris(); break;
                        case 6: notifikasiStokRendah(); break;
                        case 7: statistikInventaris(); break;
                        case 8: printf("Kembali ke menu utama...\n"); break;
                        default:
                            printf("Pilihan tidak valid! Masukkan angka antara 1-8.\n");
                            tekanEnterUntukLanjut();
                    }
                } while (pilihanPeralatan != 8);
                break;
            }
            
            case 3:
                // Notifikasi dan Peringatan
                cekNotifikasi();
                break;
                
            case 4: {
                // Pengaturan Sistem
                int pilihanPengaturan;
                do {
                    bersihkanLayar();
                    tampilkanMenuPengaturan();
                    printf("Masukkan pilihan Anda (1-6): ");
                    
                    if (scanf("%d", &pilihanPengaturan) != 1) {
                        printf("Input tidak valid! Harap masukkan angka.\n");
                        while (getchar() != '\n');
                        tekanEnterUntukLanjut();
                        continue;
                    }
                    
                    switch (pilihanPengaturan) {
                        case 1: eksporData(); break;
                        case 2: imporData(); break;
                        case 3: backupData(); break;
                        case 4: hapusNotifikasi(); break;
                        case 5: tentangSistem(); break;
                        case 6: printf("Kembali ke menu utama...\n"); break;
                        default:
                            printf("Pilihan tidak valid! Masukkan angka antara 1-6.\n");
                            tekanEnterUntukLanjut();
                    }
                } while (pilihanPengaturan != 6);
                break;
            }
            
            case 5:
                printf("\nTerima kasih telah menggunakan Sistem Monitoring Greenhouse!\n");
                printf("Semoga tanaman Anda selalu sehat dan subur!\n");
                printf("Sampai jumpa!\n\n");
                break;
                
            default:
                printf("Pilihan tidak valid! Masukkan angka antara 1-5.\n");
                tekanEnterUntukLanjut();
        }
    } while (pilihan != 5);
    
    return 0;
}

void tampilkanLayarSelamatDatang() {
    bersihkanLayar();
    printf("\n");
    printf("  ════════════════════════════════════════════════════════════\n");
    printf("  ||                                                       ||\n");
    printf("  ||       SISTEM MONITORING GREENHOUSE ITTS               ||\n");
    printf("  ||                                                       ||\n");
    printf("  ||           Pengelola Tanaman & Peralatan               ||\n");
    printf("  ||                                                       ||\n");
    printf("  ||  - Pantau kondisi tanaman secara real-time           ||\n");
    printf("  ||  - Kelola jadwal penyiraman                          ||\n");
    printf("  ||  - Atur inventaris peralatan                         ||\n");
    printf("  ||  - Terima notifikasi penting                         ||\n");
    printf("  ||  - Analisis statistik pertumbuhan                    ||\n");
    printf("  ||                                                       ||\n");
    printf("  ||              Versi 2.0 - Edisi Lengkap               ||\n");
    printf("  ||                                                       ||\n");
    printf("  ════════════════════════════════════════════════════════════\n");
    printf("\n");
    printf("  Selamat datang di masa depan pengelolaan greenhouse!\n");
    printf("  Sistem ini akan membantu Anda menciptakan lingkungan \n");
    printf("  yang sempurna untuk tanaman.\n");
    printf("\n");
    tekanEnterUntukLanjut();
}

void tampilkanMenuUtama() {
    tampilkanHeader("MENU UTAMA");
    printf("1. Manajemen Tanaman       - Pantau dan rawat tanaman Anda\n");
    printf("2. Manajemen Peralatan     - Kelola alat dan perlengkapan\n");
    printf("3. Notifikasi & Peringatan - Lihat pemberitahuan sistem\n");
    printf("4. Pengaturan Sistem       - Konfigurasi dan perawatan\n");
    printf("5. Keluar                  - Tutup aplikasi\n");
    printf("═══════════════════════════════════════════════════════════\n");
}

void tampilkanMenuTanaman() {
    tampilkanHeader("MANAJEMEN TANAMAN");
    printf("1. Pantau Kesehatan        - Cek kondisi lingkungan\n");
    printf("2. Lihat Riwayat Siram     - Histori penyiraman\n");
    printf("3. Catat Penyiraman        - Log penyiraman baru\n");
    printf("4. Statistik Tanaman       - Data pertumbuhan\n");
    printf("5. Tambah Tanaman Baru     - Daftarkan tanaman\n");
    printf("6. Lihat Semua Tanaman     - Browse database tanaman\n");
    printf("7. Hapus Data Tanaman      - Hapus record tanaman\n");
    printf("8. Pengingat Perawatan     - Tugas perawatan\n");
    printf("9. Kembali ke Menu Utama   - Kembali\n");
    printf("═══════════════════════════════════════════════════════════\n");
}

void tampilkanMenuPeralatan() {
    tampilkanHeader("MANAJEMEN PERALATAN");
    printf("1. Lihat Inventaris        - Tampilkan semua peralatan\n");
    printf("2. Tambah/Update Alat      - Kelola stok peralatan\n");
    printf("3. Cari Peralatan          - Temukan item tertentu\n");
    printf("4. Laporan Inventaris      - Buat laporan detail\n");
    printf("5. Hapus Peralatan         - Hapus item inventaris\n");
    printf("6. Notifikasi Stok Rendah  - Peringatan inventaris\n");
    printf("7. Statistik Inventaris    - Analisis penggunaan\n");
    printf("8. Kembali ke Menu Utama   - Kembali\n");
    printf("═══════════════════════════════════════════════════════════\n");
}

void tampilkanMenuPengaturan() {
    tampilkanHeader("PENGATURAN SISTEM");
    printf("1. Ekspor Data             - Simpan data ke file eksternal\n");
    printf("2. Impor Data              - Muat data dari file\n");
    printf("3. Backup Sistem           - Buat cadangan sistem\n");
    printf("4. Hapus Semua Notifikasi  - Bersihkan pemberitahuan\n");
    printf("5. Tentang Sistem          - Informasi sistem\n");
    printf("6. Kembali ke Menu Utama   - Kembali\n");
    printf("═══════════════════════════════════════════════════════════\n");
}

void pantauKesehatanTanaman() {
    bersihkanLayar();
    tampilkanHeader("MONITORING KESEHATAN TANAMAN");
    
    printf("Sedang mengumpulkan data sensor...\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    // Simulasi pembacaan sensor yang realistis
    float suhu = buatPembacaanSensor(18.0, 35.0);
    float kelembaban = buatPembacaanSensor(30.0, 90.0);
    float kelembapanTanah = buatPembacaanSensor(15.0, 85.0);
    float intensitasCahaya = buatPembacaanSensor(200.0, 2000.0);
    
    printf("\nKONDISI LINGKUNGAN SAAT INI:\n");
    printf("────────────────────────────────────────────────────────────\n");
    printf("Suhu:           %.1f°C", suhu);
    if (suhu >= 20.0 && suhu <= 28.0) printf(" [OPTIMAL]");
    else if (suhu < 15.0 || suhu > 35.0) printf(" [KRITIS]");
    else printf(" [PERLU PERHATIAN]");
    printf("\n");
    
    printf("Kelembaban:     %.1f%%", kelembaban);
    if (kelembaban >= 50.0 && kelembaban <= 70.0) printf(" [OPTIMAL]");
    else if (kelembaban < 30.0 || kelembaban > 85.0) printf(" [KRITIS]");
    else printf(" [PERLU PERHATIAN]");
    printf("\n");
    
    printf("Kelembapan Tanah: %.1f%%", kelembapanTanah);
    if (kelembapanTanah >= 40.0 && kelembapanTanah <= 70.0) printf(" [OPTIMAL]");
    else if (kelembapanTanah < 20.0 || kelembapanTanah > 80.0) printf(" [KRITIS]");
    else printf(" [PERLU PERHATIAN]");
    printf("\n");
    
    printf("Intensitas Cahaya: %.0f lux", intensitasCahaya);
    if (intensitasCahaya >= 500.0 && intensitasCahaya <= 1500.0) printf(" [OPTIMAL]");
    else if (intensitasCahaya < 200.0 || intensitasCahaya > 1800.0) printf(" [KRITIS]");
    else printf(" [PERLU PERHATIAN]");
    printf("\n");
    
    // Hitung skor kesehatan keseluruhan
    int skorKesehatan = hitungSkorKesehatan(suhu, kelembaban, kelembapanTanah, intensitasCahaya);
    
    printf("\nPENILAIAN KESEHATAN TANAMAN KESELURUHAN:\n");
    printf("────────────────────────────────────────────────────────────\n");
    printf("Skor Kesehatan: %d/100 ", skorKesehatan);
    
    if (skorKesehatan >= 85) {
        printf("SANGAT BAIK - Tanaman berkembang pesat!\n");
        printf("Kondisi greenhouse Anda sangat sempurna!\n");
    } else if (skorKesehatan >= 70) {
        printf("BAIK - Tanaman sehat dengan sedikit perbaikan\n");
        printf("Sebagian besar kondisi mendukung pertumbuhan.\n");
    } else if (skorKesehatan >= 50) {
        printf("CUKUP - Beberapa kondisi perlu perhatian\n");
        printf("Pertimbangkan untuk menyesuaikan kontrol lingkungan.\n");
    } else {
        printf("BURUK - Diperlukan tindakan segera!\n");
        printf("Beberapa kondisi di luar rentang optimal.\n");
        tambahNotifikasi("Kesehatan", "Kondisi kesehatan tanaman kritis terdeteksi", 3);
    }
    
    printf("\nREKOMENDASI:\n");
    printf("────────────────────────────────────────────────────────────\n");
    if (suhu < 20.0) printf("- Tingkatkan pemanas - suhu terlalu rendah\n");
    if (suhu > 28.0) printf("- Tingkatkan ventilasi - suhu terlalu tinggi\n");
    if (kelembaban < 50.0) printf("- Tingkatkan kelembaban - udara terlalu kering\n");
    if (kelembaban > 70.0) printf("- Perbaiki ventilasi - kelembaban terlalu tinggi\n");
    if (kelembapanTanah < 40.0) printf("- Siram tanaman - tanah terlalu kering\n");
    if (kelembapanTanah > 70.0) printf("- Kurangi penyiraman - tanah terlalu basah\n");
    if (intensitasCahaya < 500.0) printf("- Tambah pencahayaan - cahaya kurang\n");
    if (intensitasCahaya > 1500.0) printf("- Kurangi intensitas cahaya - terlalu terang\n");
    
    // Simpan data monitoring
    char waktuSaatIni[PANJANG_STRING_MAX];
    dapatkanWaktuSaatIni(waktuSaatIni);
    
    FILE *fp = fopen("log_monitoring.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s,%.1f,%.1f,%.1f,%.0f,%d\n", 
                waktuSaatIni, suhu, kelembaban, kelembapanTanah, intensitasCahaya, skorKesehatan);
        fclose(fp);
    }
    
    tekanEnterUntukLanjut();
}

void lihatTanggalTerakhirDisiram() {
    bersihkanLayar();
    tampilkanHeader("RIWAYAT PENYIRAMAN");
    
    FILE *fp = fopen(FILE_TERAKHIR_DISIRAM, "r");
    if (fp == NULL) {
        printf("Tidak ada catatan penyiraman ditemukan.\n");
        printf("Tips: Perbarui catatan penyiraman untuk mulai melacak.\n");
    } else {
        char tanggal[PANJANG_STRING_MAX];
        char namaTanaman[PANJANG_STRING_MAX];
        int jumlahCatatan = 0;
        
        printf("CATATAN PENYIRAMAN TERBARU:\n");
        printf("════════════════════════════════════════════════════════════\n");
        
        while (fscanf(fp, "%s %s", tanggal, namaTanaman) == 2) {
            jumlahCatatan++;
            printf("%d. %s - Terakhir disiram: %s\n", jumlahCatatan, namaTanaman, tanggal);
        }
        
        if (jumlahCatatan == 0) {
            printf("Tidak ada catatan penyiraman dalam file.\n");
        } else {
            printf("\nTotal tanaman yang dicatat: %d\n", jumlahCatatan);
            printf("Ingat: Kebanyakan tanaman perlu disiram setiap 2-3 hari.\n");
        }
        
        fclose(fp);
    }
    
    tekanEnterUntukLanjut();
}

void perbaruiTanggalSiram() {
    bersihkanLayar();
    tampilkanHeader("PERBARUI CATATAN PENYIRAMAN");
    
    char tanggal[PANJANG_STRING_MAX];
    char namaTanaman[PANJANG_STRING_MAX];
    char tanggalHariIni[PANJANG_STRING_MAX];
    
    dapatkanTanggalSaatIni(tanggalHariIni);
    printf("Tanggal hari ini: %s\n", tanggalHariIni);
    printf("════════════════════════════════════════════════════════════\n");
    
    printf("Masukkan nama tanaman: ");
    getchar(); // Bersihkan buffer input
    fgets(namaTanaman, sizeof(namaTanaman), stdin);
    bersihkanString(namaTanaman);
    
    printf("Masukkan tanggal penyiraman (dd-mm-yyyy) atau tekan Enter untuk hari ini: ");
    fgets(tanggal, sizeof(tanggal), stdin);
    bersihkanString(tanggal);
    
    // Jika input kosong, gunakan tanggal hari ini
    if (strlen(tanggal) == 0) {
        strcpy(tanggal, tanggalHariIni);
    }
    
    if (validasiTanggal(tanggal)) {
        FILE *fp = fopen(FILE_TERAKHIR_DISIRAM, "a");
        if (fp != NULL) {
            fprintf(fp, "%s %s\n", tanggal, namaTanaman);
            fclose(fp);
            printf("Catatan penyiraman berhasil diperbarui!\n");
            printf("%s telah disiram pada %s\n", namaTanaman, tanggal);
            
            // Tambah notifikasi sukses
            char pesanNotifikasi[200];
            sprintf(pesanNotifikasi, "Penyiraman dicatat untuk %s pada %s", namaTanaman, tanggal);
            tambahNotifikasi("Penyiraman", pesanNotifikasi, 1);
        } else {
            printf("Error saat memperbarui catatan penyiraman.\n");
        }
    } else {
        printf("Format tanggal tidak valid. Harap gunakan format dd-mm-yyyy.\n");
    }
    
    tekanEnterUntukLanjut();
}

void lihatStatistikTanaman() {
    bersihkanLayar();
    tampilkanHeader("STATISTIK TANAMAN");
    
    FILE *fp = fopen(FILE_DATA_TANAMAN, "r");
    if (fp == NULL) {
        printf("Data tanaman tidak tersedia.\n");
        printf("Tambahkan beberapa data tanaman terlebih dahulu untuk melihat statistik detail.\n");
    } else {
        DataTanaman tanaman;
        int jumlah = 0;
        float rataRataSuhu = 0, rataRataKelembaban = 0, rataRataKelembapanTanah = 0, rataRataCahaya = 0;
        int totalSkorKesehatan = 0;
        
        printf("CATATAN DATABASE TANAMAN:\n");
        printf("════════════════════════════════════════════════════════════\n");
        
        while (fscanf(fp, "%s %s %f %f %f %f %s %s %d", 
                      tanaman.namaTanaman, tanaman.jenisTanaman, &tanaman.suhu, 
                      &tanaman.kelembaban, &tanaman.kelembapanTanah, &tanaman.intensitasCahaya,
                      tanaman.terakhirDisiram, tanaman.tanggalTanam, &tanaman.skorKesehatan) == 9) {
            jumlah++;
            printf("%d. %s (%s)\n", jumlah, tanaman.namaTanaman, tanaman.jenisTanaman);
            printf("   Suhu: %.1f°C | Kelembaban: %.1f%% | Tanah: %.1f%% | Cahaya: %.0flux\n",
                   tanaman.suhu, tanaman.kelembaban, tanaman.kelembapanTanah, tanaman.intensitasCahaya);
            printf("   Terakhir disiram: %s | Ditanam: %s | Kesehatan: %d/100\n\n",
                   tanaman.terakhirDisiram, tanaman.tanggalTanam, tanaman.skorKesehatan);
            
            rataRataSuhu += tanaman.suhu;
            rataRataKelembaban += tanaman.kelembaban;
            rataRataKelembapanTanah += tanaman.kelembapanTanah;
            rataRataCahaya += tanaman.intensitasCahaya;
            totalSkorKesehatan += tanaman.skorKesehatan;
        }
        
        if (jumlah > 0) {
            rataRataSuhu /= jumlah;
            rataRataKelembaban /= jumlah;
            rataRataKelembapanTanah /= jumlah;
            rataRataCahaya /= jumlah;
            int rataRataSkorKesehatan = totalSkorKesehatan / jumlah;
            
            printf("RATA-RATA GREENHOUSE:\n");
            printf("════════════════════════════════════════════════════════════\n");
            printf("Rata-rata Suhu: %.1f°C\n", rataRataSuhu);
            printf("Rata-rata Kelembaban: %.1f%%\n", rataRataKelembaban);
            printf("Rata-rata Kelembapan Tanah: %.1f%%\n", rataRataKelembapanTanah);
            printf("Rata-rata Intensitas Cahaya: %.0f lux\n", rataRataCahaya);
            printf("Rata-rata Skor Kesehatan: %d/100\n", rataRataSkorKesehatan);
            printf("Total Tanaman: %d\n", jumlah);
        }
        
        fclose(fp);
    }
    
    tekanEnterUntukLanjut();
}

void tambahDataTanaman() {
    bersihkanLayar();
    tampilkanHeader("TAMBAH TANAMAN BARU");
    
    DataTanaman tanaman;
    char tanggalSaatIni[PANJANG_STRING_MAX];
    dapatkanTanggalSaatIni(tanggalSaatIni);
    
    printf("Masukkan detail tanaman:\n");
    printf("════════════════════════════════════════════════════════════\n");
    
    printf("Nama tanaman: ");
    getchar(); // Bersihkan buffer input
    fgets(tanaman.namaTanaman, sizeof(tanaman.namaTanaman), stdin);
    bersihkanString(tanaman.namaTanaman);
    
    printf("Jenis tanaman (contoh: Tomat, Mawar, Kemangi): ");
    fgets(tanaman.jenisTanaman, sizeof(tanaman.jenisTanaman), stdin);
    bersihkanString(tanaman.jenisTanaman);
    
    printf("Suhu saat ini (°C): ");
    scanf("%f", &tanaman.suhu);
    
    printf("Kelembaban saat ini (%%): ");
    scanf("%f", &tanaman.kelembaban);
    
    printf("Kelembapan tanah saat ini (%%): ");
    scanf("%f", &tanaman.kelembapanTanah);
    
    printf("Intensitas cahaya saat ini (lux): ");
    scanf("%f", &tanaman.intensitasCahaya);
    
    strcpy(tanaman.terakhirDisiram, tanggalSaatIni);
    strcpy(tanaman.tanggalTanam, tanggalSaatIni);
    
    tanaman.skorKesehatan = hitungSkorKesehatan(tanaman.suhu, tanaman.kelembaban, 
                                           tanaman.kelembapanTanah, tanaman.intensitasCahaya);
    
    FILE *fp = fopen(FILE_DATA_TANAMAN, "a");
    if (fp != NULL) {
        fprintf(fp, "%s %s %.1f %.1f %.1f %.0f %s %s %d\n", 
                tanaman.namaTanaman, tanaman.jenisTanaman, tanaman.suhu, tanaman.kelembaban,
                tanaman.kelembapanTanah, tanaman.intensitasCahaya, tanaman.terakhirDisiram, 
                tanaman.tanggalTanam, tanaman.skorKesehatan);
        fclose(fp);
        
        printf("\nTanaman berhasil ditambahkan!\n");
        printf("%s (%s) telah terdaftar di greenhouse Anda.\n", 
               tanaman.namaTanaman, tanaman.jenisTanaman);
        printf("Skor kesehatan awal: %d/100\n", tanaman.skorKesehatan);
        
        // Tambah notifikasi untuk tanaman baru
        char pesanNotifikasi[200];
        sprintf(pesanNotifikasi, "Tanaman baru ditambahkan: %s (%s)", tanaman.namaTanaman, tanaman.jenisTanaman);
        tambahNotifikasi("Tanaman", pesanNotifikasi, 1);
    } else {
        printf("Error saat menambahkan data tanaman.\n");
    }
    
    tekanEnterUntukLanjut();
}

// Implementasi fungsi utilitas utama

float buatPembacaanSensor(float min, float max) {
    srand(time(NULL) + rand());
    return min + (float)rand() / RAND_MAX * (max - min);
}

int hitungSkorKesehatan(float suhu, float kelembaban, float kelembapanTanah, float cahaya) {
    int skor = 100;
    
    // Skor suhu (optimal: 20-28°C)
    if (suhu < 15.0 || suhu > 35.0) skor -= 30;
    else if (suhu < 20.0 || suhu > 28.0) skor -= 15;
    
    // Skor kelembaban (optimal: 50-70%)
    if (kelembaban < 30.0 || kelembaban > 85.0) skor -= 25;
    else if (kelembaban < 50.0 || kelembaban > 70.0) skor -= 10;
    
    // Skor kelembapan tanah (optimal: 40-70%)
    if (kelembapanTanah < 20.0 || kelembapanTanah > 80.0) skor -= 25;
    else if (kelembapanTanah < 40.0 || kelembapanTanah > 70.0) skor -= 10;
    
    // Skor intensitas cahaya (optimal: 500-1500 lux)
    if (cahaya < 200.0 || cahaya > 1800.0) skor -= 20;
    else if (cahaya < 500.0 || cahaya > 1500.0) skor -= 10;
    
    return (skor < 0) ? 0 : skor;
}

void dapatkanTanggalSaatIni(char *stringTanggal) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(stringTanggal, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void dapatkanWaktuSaatIni(char *stringWaktu) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(stringWaktu, "%02d-%02d-%04d %02d:%02d:%02d", 
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int validasiTanggal(const char *tanggal) {
    int hari, bulan, tahun;
    if (sscanf(tanggal, "%d-%d-%d", &hari, &bulan, &tahun) != 3) {
        return 0;
    }
    
    if (bulan < 1 || bulan > 12) return 0;
    if (hari < 1 || hari > 31) return 0;
    if (tahun < 1900 || tahun > 2100) return 0;
    
    return 1;
}

void tampilkanHeader(const char *judul) {
    printf("\n");
    printf("════════════════════════════════════════════════════════════\n");
    printf("  %-56s  \n", judul);
    printf("════════════════════════════════════════════════════════════\n");
}

void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tekanEnterUntukLanjut() {
    printf("\nTekan Enter untuk melanjutkan...");
    while (getchar() != '\n');
    getchar();
}

void bersihkanString(char *str) {
    char *akhir;
    
    // Hapus spasi di awal
    while(isspace((unsigned char)*str)) str++;
    
    // Semua spasi?
    if(*str == 0) return;
    
    // Hapus spasi di akhir
    akhir = str + strlen(str) - 1;
    while(akhir > str && isspace((unsigned char)*akhir)) akhir--;
    
    // Tulis null terminator baru
    *(akhir+1) = 0;
}

void tambahNotifikasi(const char* jenis, const char* pesan, int prioritas) {
    FILE *fp = fopen(FILE_NOTIFIKASI, "a");
    if (fp != NULL) {
        char waktu[PANJANG_STRING_MAX];
        dapatkanWaktuSaatIni(waktu);
        fprintf(fp, "%s|%s|%s|%d\n", waktu, jenis, pesan, prioritas);
        fclose(fp);
    }
}

// Implementasi fungsi-fungsi tambahan
void lihatSemuaTanaman() {
    bersihkanLayar();
    tampilkanHeader("SEMUA TANAMAN");
    printf("Fitur ini sedang dalam pengembangan.\n");
    printf("Gunakan 'Statistik Tanaman' untuk sementara melihat data tanaman.\n");
    tekanEnterUntukLanjut();
}

void hapusDataTanaman() {
    bersihkanLayar();
    tampilkanHeader("HAPUS DATA TANAMAN");
    printf("Fitur ini sedang dalam pengembangan.\n");
    tekanEnterUntukLanjut();
}

void pengingatPerawatan() {
    bersihkanLayar();
    tampilkanHeader("PENGINGAT PERAWATAN");
    printf("JADWAL PERAWATAN TANAMAN:\n");
    printf("════════════════════════════════════════════════════════════\n");
    printf("Harian: Cek tingkat kelembapan tanah\n");
    printf("Mingguan: Periksa tanaman dari hama dan penyakit\n");
    printf("Bulanan: Potong daun dan batang yang mati\n");
    printf("Musiman: Berikan pupuk dan repot sesuai kebutuhan\n");
    tekanEnterUntukLanjut();
}

void cekInventaris() {
    bersihkanLayar();
    tampilkanHeader("INVENTARIS PERALATAN");
    
    FILE *fp = fopen(FILE_INVENTARIS, "r");
    if (fp == NULL) {
        printf("Data inventaris tidak ditemukan.\n");
        printf("Tambahkan beberapa peralatan untuk mulai melacak inventaris.\n");
    } else {
        char baris[256];
        int jumlahItem = 0;
        
        printf("INVENTARIS SAAT INI:\n");
        printf("════════════════════════════════════════════════════════════\n");
        
        while (fgets(baris, sizeof(baris), fp)) {
            jumlahItem++;
            printf("%d. %s", jumlahItem, baris);
        }
        
        if (jumlahItem == 0) {
            printf("Inventaris kosong.\n");
        } else {
            printf("\nTotal item dalam inventaris: %d\n", jumlahItem);
        }
        
        fclose(fp);
    }
    
    tekanEnterUntukLanjut();
}

void perbaruiInventaris() {
    bersihkanLayar();
    tampilkanHeader("TAMBAH/UPDATE PERALATAN");
    
    ItemInventaris item;
    char tanggalSaatIni[PANJANG_STRING_MAX];
    dapatkanTanggalSaatIni(tanggalSaatIni);
    
    printf("Masukkan detail peralatan:\n");
    printf("════════════════════════════════════════════════════════════\n");
    
    printf("Nama item: ");
    getchar(); // Bersihkan buffer input
    fgets(item.nama, sizeof(item.nama), stdin);
    bersihkanString(item.nama);
    
    printf("Kategori (contoh: Alat, Benih, Pupuk): ");
    fgets(item.kategori, sizeof(item.kategori), stdin);
    bersihkanString(item.kategori);
    
    printf("Jumlah: ");
    scanf("%d", &item.jumlah);
    
    printf("Harga per unit (Rp): ");
    scanf("%f", &item.harga);
    
    printf("Stok minimal: ");
    scanf("%d", &item.stokMinimal);
    
    strcpy(item.tanggal, tanggalSaatIni);
    
    FILE *fp = fopen(FILE_INVENTARIS, "a");
    if (fp != NULL) {
        fprintf(fp, "Item: %s | Kategori: %s | Jumlah: %d | Harga: Rp%.2f | Stok Min: %d | Tanggal: %s\n",
                item.nama, item.kategori, item.jumlah, item.harga, item.stokMinimal, item.tanggal);
        fclose(fp);
        
        printf("\nPeralatan berhasil ditambahkan!\n");
        printf("%s (%d unit) ditambahkan ke kategori %s\n", 
               item.nama, item.jumlah, item.kategori);
        
        // Cek stok rendah
        if (item.jumlah <= item.stokMinimal) {
            char pesanNotifikasi[200];
            sprintf(pesanNotifikasi, "Peringatan stok rendah: %s (%d unit tersisa)", item.nama, item.jumlah);
            tambahNotifikasi("Inventaris", pesanNotifikasi, 2);
        }
    } else {
        printf("Error saat memperbarui inventaris.\n");
    }
    
    tekanEnterUntukLanjut();
}

void cariItemInventaris() {
    bersihkanLayar();
    tampilkanHeader("CARI PERALATAN");
    
    char kataCari[PANJANG_STRING_MAX];
    char baris[256];
    int ditemukan = 0;
    
    printf("Masukkan nama item atau kategori yang dicari: ");
    getchar(); // Bersihkan buffer input
    fgets(kataCari, sizeof(kataCari), stdin);
    bersihkanString(kataCari);
    
    FILE *fp = fopen(FILE_INVENTARIS, "r");
    if (fp == NULL) {
        printf("File inventaris tidak ditemukan.\n");
    } else {
        printf("\nHASIL PENCARIAN:\n");
        printf("════════════════════════════════════════════════════════════\n");
        
        while (fgets(baris, sizeof(baris), fp)) {
            if (strstr(baris, kataCari) != NULL) {
                printf("DITEMUKAN: %s", baris);
                ditemukan++;
            }
        }
        
        if (ditemukan == 0) {
            printf("Tidak ada item yang ditemukan untuk '%s'.\n", kataCari);
        } else {
            printf("\nDitemukan %d item yang cocok dengan '%s'.\n", ditemukan, kataCari);
        }
        
        fclose(fp);
    }
    
    tekanEnterUntukLanjut();
}

void buatLaporanInventaris() {
    bersihkanLayar();
    tampilkanHeader("LAPORAN INVENTARIS");
    
    FILE *fp = fopen(FILE_INVENTARIS, "r");
    if (fp == NULL) {
        printf("Data inventaris tidak tersedia.\n");
    } else {
        char baris[256];
        int totalItem = 0;
        float nilaiTotal = 0.0;
        
        printf("LAPORAN INVENTARIS DETAIL\n");
        char tanggalSaatIni[PANJANG_STRING_MAX];
        dapatkanTanggalSaatIni(tanggalSaatIni);
        printf("Dibuat pada: %s\n", tanggalSaatIni);
        printf("════════════════════════════════════════════════════════════\n");
        
        while (fgets(baris, sizeof(baris), fp)) {
            totalItem++;
            printf("%s", baris);
            
            // Ekstrak harga dan jumlah untuk kalkulasi nilai total
            char *stringHarga = strstr(baris, "Harga: Rp");
            if (stringHarga) {
                float harga;
                if (sscanf(stringHarga, "Harga: Rp%f", &harga) == 1) {
                    char *stringJumlah = strstr(baris, "Jumlah: ");
                    if (stringJumlah) {
                        int jumlah;
                        if (sscanf(stringJumlah, "Jumlah: %d", &jumlah) == 1) {
                            nilaiTotal += harga * jumlah;
                        }
                    }
                }
            }
        }
        
        printf("════════════════════════════════════════════════════════════\n");
        printf("Total Item: %d\n", totalItem);
        printf("Nilai Total Inventaris: Rp%.2f\n", nilaiTotal);
        printf("Rata-rata Nilai Item: Rp%.2f\n", totalItem > 0 ? nilaiTotal / totalItem : 0);
        
        fclose(fp);
    }
    
    tekanEnterUntukLanjut();
}

void cekNotifikasi() {
    bersihkanLayar();
    tampilkanHeader("NOTIFIKASI & PERINGATAN");
    
    FILE *fp = fopen(FILE_NOTIFIKASI, "r");
    if (fp == NULL) {
        printf("Tidak ada notifikasi saat ini.\n");
        printf("Sistem greenhouse Anda berjalan dengan lancar!\n");
    } else {
        char waktu[PANJANG_STRING_MAX], jenis[PANJANG_STRING_MAX], pesan[PANJANG_STRING_MAX];
        int prioritas;
        int jumlahNotifikasi = 0;
        
        printf("NOTIFIKASI SISTEM:\n");
        printf("════════════════════════════════════════════════════════════\n");
        
        while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d\n", waktu, jenis, pesan, prioritas) == 4) {
            jumlahNotifikasi++;
            char ikonPrioritas[10];
            char warnaPrioritas[20];
            
            switch(prioritas) {
                case 3: 
                    strcpy(ikonPrioritas, "[KRITIS]"); 
                    strcpy(warnaPrioritas, ""); 
                    break;
                case 2: 
                    strcpy(ikonPrioritas, "[PENTING]"); 
                    strcpy(warnaPrioritas, ""); 
                    break;
                default: 
                    strcpy(ikonPrioritas, "[INFO]"); 
                    strcpy(warnaPrioritas, ""); 
                    break;
            }
            
            printf("%s [%s] %s: %s\n", 
                   ikonPrioritas, jenis, waktu, pesan);
        }
        
        if (jumlahNotifikasi == 0) {
            printf("Tidak ada notifikasi ditemukan.\n");
        } else {
            printf("\nTotal notifikasi: %d\n", jumlahNotifikasi);
        }
        
        fclose(fp);
    }
    
    tekanEnterUntukLanjut();
}

// Implementasi fungsi placeholder yang tersisa
void hapusItemInventaris() {
    bersihkanLayar();
    tampilkanHeader("HAPUS PERALATAN");
    printf("Fitur ini sedang dalam pengembangan.\n");
    tekanEnterUntukLanjut();
}

void notifikasiStokRendah() {
    bersihkanLayar();
    tampilkanHeader("PERINGATAN STOK RENDAH");
    printf("Memeriksa tingkat inventaris...\n");
    printf("Fitur ini sedang dalam pengembangan.\n");
    tekanEnterUntukLanjut();
}

void statistikInventaris() {
    bersihkanLayar();
    tampilkanHeader("ANALISIS INVENTARIS");
    printf("Membuat statistik penggunaan...\n");
    printf("Fitur ini sedang dalam pengembangan.\n");
    tekanEnterUntukLanjut();
}

void eksporData() {
    bersihkanLayar();
    tampilkanHeader("EKSPOR DATA");
    printf("Mengekspor data sistem...\n");
    printf("Fitur ini sedang dalam pengembangan.\n");
    tekanEnterUntukLanjut();
}

void imporData() {
    bersihkanLayar();
    tampilkanHeader("IMPOR DATA");
    printf("Mengimpor data sistem...\n");
    printf("Fitur ini sedang dalam pengembangan.\n");
    tekanEnterUntukLanjut();
}

void backupData() {
    bersihkanLayar();
    tampilkanHeader("BACKUP SISTEM");
    printf("Membuat cadangan sistem...\n");
    printf("Fitur ini sedang dalam pengembangan.\n");
    tekanEnterUntukLanjut();
}

void hapusNotifikasi() {
    bersihkanLayar();
    tampilkanHeader("HAPUS NOTIFIKASI");
    
    char pilihan;
    printf("Apakah Anda yakin ingin menghapus semua notifikasi? (y/T): ");
    scanf(" %c", &pilihan);
    
    if (pilihan == 'y' || pilihan == 'Y') {
        FILE *fp = fopen(FILE_NOTIFIKASI, "w");
        if (fp != NULL) {
            fclose(fp);
            printf("Semua notifikasi telah dihapus.\n");
        } else {
            printf("Error saat menghapus notifikasi.\n");
        }
    } else {
        printf("Operasi dibatalkan.\n");
    }
    
    tekanEnterUntukLanjut();
}

void tentangSistem() {
    bersihkanLayar();
    tampilkanHeader("TENTANG SISTEM MONITORING GREENHOUSE");
    
    printf("SISTEM MONITORING GREENHOUSE ITTS v2.0\n");
    printf("════════════════════════════════════════════════════════════\n");
    printf("Tujuan: Manajemen dan monitoring greenhouse tingkat lanjut\n");
    printf("Developer: Tim Pengembangan ITTS\n");
    printf("Versi: 2.0 Edisi Lengkap\n");
    printf("Tanggal Rilis: Juli 2025\n");
    printf("Platform: Multi-platform (Windows, Linux, macOS)\n");
    printf("Bahasa: C (Standar C99)\n");
    printf("\n");
    printf("FITUR UTAMA:\n");
    printf("════════════════════════════════════════════════════════════\n");
    printf("- Monitoring kesehatan tanaman real-time\n");
    printf("- Manajemen penyiraman komprehensif\n");
    printf("- Statistik dan analisis tanaman lanjutan\n");
    printf("- Sistem inventaris peralatan lengkap\n");
    printf("- Sistem notifikasi dan peringatan cerdas\n");
    printf("- Kemampuan ekspor dan backup data\n");
    printf("- Interface yang ramah pengguna\n");
    printf("- Penanganan error yang kuat dan validasi\n");
    printf("\n");
    printf("DUKUNGAN:\n");
    printf("════════════════════════════════════════════════════════════\n");
    printf("Email: dukungan@itts-greenhouse.com\n");
    printf("Website: https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS\n");
    printf("Dokumentasi: Tersedia di README.md\n");
    printf("\n");
    printf("Terima kasih telah menggunakan sistem kami!\n");
    printf("Selamat monitoring greenhouse!\n");
    
    tekanEnterUntukLanjut();
}
