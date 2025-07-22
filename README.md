# Sistem Monitoring Greenhouse ITTS (Advanced Version)

Sistem monitoring dan manajemen greenhouse yang komprehensif dengan fitur advanced seperti database SQLite, web dashboard, monitoring sensor real-time, dan aplikasi mobile companion.

## Fitur Advanced

### 🗄️ Database SQLite Terintegrasi
- **Penyimpanan Terstruktur**: Data tanaman, sensor, dan inventaris dalam database SQLite
- **Backup Otomatis**: Sistem backup database berkala
- **Query Performance**: Optimized queries untuk performa maksimal
- **Data Integrity**: Relational database dengan foreign key constraints

### 🌐 Web Dashboard Real-time
- **Port**: http://localhost:8080
- **Real-time Monitoring**: Update data setiap 30 detik
- **Responsive Design**: Mobile-friendly interface
- **API RESTful**: Endpoint untuk integrasi eksternal
- **Live Charts**: Grafik data sensor real-time

### 📱 Aplikasi Mobile Companion
- **Progressive Web App (PWA)**: Install sebagai aplikasi mobile
- **Offline Support**: Bekerja tanpa koneksi internet
- **Push Notifications**: Alert langsung ke perangkat mobile
- **Touch-optimized**: Interface dioptimasi untuk sentuhan

### 🔔 Sistem Notifikasi Otomatis
- **Push Notifications**: Alert real-time untuk kondisi kritis
- **Email Alerts**: Notifikasi via email (simulasi)
- **SMS Alerts**: Peringatan via SMS (simulasi)
- **Prioritas Alert**: Level rendah, sedang, dan tinggi

### 📊 Ekspor Data Multi-Format
- **CSV Export**: Data dalam format Excel-compatible
- **Laporan PDF**: Laporan harian dan mingguan (planned)
- **Data Analytics**: Statistik dan tren data
- **Backup Export**: Export untuk backup dan migrasi

### 🌍 Dukungan Multi-Bahasa
- **Bahasa Indonesia**: Interface lengkap dalam bahasa Indonesia
- **English Support**: Full English language support
- **Dynamic Language Switching**: Ubah bahasa tanpa restart
- **Localized Notifications**: Alert dalam bahasa pilihan

### 🔌 Integrasi Sensor Real-time
- **DHT22**: Sensor suhu dan kelembaban udara
- **Soil Moisture**: Sensor kelembaban tanah
- **LDR**: Sensor intensitas cahaya
- **Auto Calibration**: Kalibrasi sensor otomatis
- **Error Detection**: Deteksi sensor rusak/disconnect

## Fitur Klasik (Tetap Tersedia)

### Manajemen Tanaman
- **Monitoring Kesehatan Tanaman Real-time**: Pembacaan sensor untuk suhu, kelembaban, dan kelembapan tanah
- **Penilaian Kesehatan**: Evaluasi otomatis kondisi tanaman dengan feedback berkode warna
- **Jadwal Penyiraman**: Lacak dan perbarui tanggal terakhir disiram
- **Statistik Tanaman**: Lihat data historis dan rata-rata kondisi lingkungan
- **Pencatatan Data**: Tambah dan simpan data tanaman untuk analisis

### Manajemen Peralatan
- **Pelacakan Inventaris**: Sistem manajemen inventaris yang komprehensif
- **Pencarian Item**: Fungsi pencarian cepat untuk item inventaris
- **Pelacakan Harga**: Monitor biaya peralatan dan nilai total inventaris
- **Laporan Inventaris**: Buat ringkasan inventaris yang detail
- **Pelacakan Tanggal**: Lacak kapan item ditambahkan atau diperbarui

## Memulai

### Prasyarat (Advanced Version)
- **Compiler GCC** (MinGW di Windows)
- **SQLite3 Development Libraries**
- **Windows SDK** (untuk Winsock2)
- **Dukungan standar C99**

### Instalasi Advanced

1. **Clone repository**:
   ```bash
   git clone https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS.git
   cd Greenhouse-Monitoring-System-ITTS
   ```

2. **Install Dependencies**:
   ```bash
   # Windows (MinGW/MSYS2)
   pacman -S mingw-w64-x86_64-sqlite3
   
   # Ubuntu/Debian
   sudo apt-get install sqlite3 libsqlite3-dev
   
   # CentOS/RHEL
   sudo yum install sqlite-devel
   ```

3. **Build Sistem Advanced**:
   ```bash
   # Menggunakan build script (Recommended)
   build_advanced.bat
   
   # Atau manual compilation
   gcc -Wall -Wextra -std=c99 -O2 -I. \
       greenhouse_system_advanced.c \
       database_functions.c \
       network_functions.c \
       sensor_functions.c \
       export_notification.c \
       multilang_functions.c \
       -o greenhouse_advanced.exe \
       -lsqlite3 -lws2_32 -lm
   ```

4. **Jalankan Aplikasi**:
   ```bash
   ./greenhouse_advanced.exe
   ```

5. **Akses Web Dashboard**:
   - Buka browser
   - Kunjungi: http://localhost:8080
   - Dashboard akan menampilkan data real-time

6. **Install Mobile App**:
   - Buka mobile_app.html di browser mobile
   - Pilih "Add to Home Screen" untuk install PWA

### Build Options

#### Normal Build
```bash
build_advanced.bat
# Pilih opsi 1: Build Sistem Lengkap
```

#### Debug Build
```bash
gcc -g -DDEBUG [source_files] -o greenhouse_debug.exe
```

#### Release Build
```bash
gcc -O3 -DNDEBUG [source_files] -o greenhouse_release.exe
```

2. **Kompilasi program**:
   ```bash
   # Menggunakan Makefile (direkomendasikan)
   make

   # Atau kompilasi manual
   gcc -Wall -Wextra -std=c99 -o greenhouse_monitoring greenhouse_monitoring.c
   ```

3. **Jalankan program**:
   ```bash
   # Menggunakan Makefile
   make run

   # Atau jalankan langsung
   ./greenhouse_monitoring
   ```

## Panduan Penggunaan

### Menu Utama
Sistem menyediakan lima pilihan utama:
1. **Manajemen Tanaman** - Monitor dan kelola kesehatan tanaman
2. **Manajemen Peralatan** - Lacak dan kelola peralatan greenhouse
3. **Notifikasi & Peringatan** - Lihat pemberitahuan sistem
4. **Pengaturan Sistem** - Konfigurasi dan perawatan
5. **Keluar** - Tutup aplikasi

### Fitur Manajemen Tanaman

#### Monitoring Kesehatan
- Menampilkan pembacaan lingkungan tersimulasi
- Memberikan penilaian kesehatan berdasarkan rentang optimal:
  - Suhu: 20-28°C (optimal)
  - Kelembaban: 50-70% (optimal)
  - Kelembapan Tanah: 40-70% (optimal)
  - Intensitas Cahaya: 500-1500 lux (optimal)

#### Manajemen Penyiraman
- Lihat tanggal terakhir disiram
- Perbarui catatan penyiraman
- Validasi tanggal otomatis

#### Statistik Tanaman
- Lihat semua data tanaman yang tercatat
- Hitung rata-rata kondisi lingkungan
- Analisis data historis

### Fitur Manajemen Peralatan

#### Operasi Inventaris
- Tambah item baru dengan jumlah dan harga
- Lihat daftar inventaris lengkap
- Cari item tertentu
- Buat laporan komprehensif

#### Field Data
- Nama item
- Jumlah
- Harga per unit
- Kategori
- Stok minimal
- Tanggal ditambahkan/diperbarui

## Struktur File

```
Greenhouse-Monitoring-System-ITTS/
├── greenhouse_system_advanced.c  # Kode sumber utama (versi lengkap)
├── greenhouse_monitoring.c       # Kode sumber dasar
├── Makefile                      # Konfigurasi build
├── build.bat                     # Script build Windows
├── README.md                     # Dokumentasi
├── DOCS.md                       # Dokumentasi teknis
├── SAMPLE_DATA.md               # Contoh data
├── data_inventaris.txt          # Data inventaris (generated)
├── tanggal_siram.txt           # Catatan penyiraman (generated)
├── data_tanaman.txt            # Statistik tanaman (generated)
└── notifikasi.txt              # Notifikasi sistem (generated)
```

## Antarmuka Pengguna

Sistem ini menampilkan antarmuka yang intuitif dengan:
- Opsi menu yang jelas
- Indikator sukses
- Pesan peringatan
- Notifikasi error
- Elemen visualisasi data

## Detail Teknis

### Penyimpanan Data
- **File Teks**: Semua data disimpan dalam file teks yang dapat dibaca manusia
- **Penyimpanan Persisten**: Data bertahan setelah program ditutup
- **Format Portabel**: Mudah untuk backup dan transfer

### Validasi Input
- Validasi format tanggal (dd-mm-yyyy)
- Verifikasi input numerik
- Perlindungan buffer overflow
- Penanganan error untuk operasi file

### Kompatibilitas Lintas Platform
- Windows: Menggunakan `cls` untuk membersihkan layar
- Linux/macOS: Menggunakan `clear` untuk membersihkan layar
- Fungsi pustaka C standar untuk kompatibilitas maksimum

## Perbaikan dari Versi Asli

### Kualitas Kode
- Memperbaiki bug struktur menu (case 2 yang hilang)
- Menambahkan penanganan error yang tepat
- Implementasi validasi input
- Desain fungsi modular
- Format kode yang konsisten
- Antarmuka bahasa Indonesia

### Fitur Baru
- Statistik tanaman dan pencatatan data
- Manajemen inventaris lanjutan
- Fungsi pencarian
- Pelaporan inventaris
- Pelacakan harga
- Penanganan tanggal otomatis
- Sistem notifikasi dan peringatan
- Monitoring kesehatan real-time

### Pengalaman Pengguna
- Navigasi menu yang diperbaiki
- Antarmuka yang lebih bersih
- Pesan error yang lebih baik
- Feedback validasi input
- Indikator kemajuan

## Pengembangan Masa Depan

- Integrasi database (SQLite)
- Konektivitas jaringan untuk monitoring jarak jauh
- Integrasi sensor nyata
- Dashboard berbasis web
- Aplikasi pendamping mobile
- Notifikasi dan peringatan otomatis
- Ekspor data ke CSV/Excel
- Dukungan multi-bahasa

---

**Happy Greenhouse Monitoring! 🌱🌿🌺**
