# Panduan Fitur Advanced - Greenhouse Monitoring System ITTS

## Daftar Isi
1. [Integrasi Database SQLite](#database-sqlite)
2. [Konektivitas Jaringan](#konektivitas-jaringan)  
3. [Integrasi Sensor Nyata](#integrasi-sensor)
4. [Dashboard Berbasis Web](#dashboard-web)
5. [Aplikasi Pendamping Mobile](#aplikasi-mobile)
6. [Notifikasi dan Peringatan](#notifikasi)
7. [Ekspor Data](#ekspor-data)
8. [Dukungan Multi-bahasa](#multi-bahasa)
9. [Instalasi dan Konfigurasi](#instalasi)

---

## Database SQLite

### Fitur Database
- **Penyimpanan Terstruktur**: Data tanaman, sensor, dan inventaris tersimpan dalam database SQLite
- **Backup Otomatis**: Sistem membuat backup database secara berkala
- **Recovery**: Kemampuan restore dari backup jika terjadi kerusakan
- **Query Optimization**: Query database dioptimalkan untuk performa tinggi

### Tabel Database
```sql
-- Tabel Tanaman
CREATE TABLE tanaman (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nama_tanaman TEXT NOT NULL,
    jenis_tanaman TEXT,
    suhu REAL,
    kelembaban REAL,
    kelembaban_tanah REAL,
    intensitas_cahaya REAL,
    terakhir_disiram TEXT,
    tanggal_tanam TEXT,
    skor_kesehatan INTEGER,
    waktu_input DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Tabel Sensor
CREATE TABLE sensor_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tipe_sensor TEXT NOT NULL,
    lokasi TEXT,
    nilai REAL,
    satuan TEXT,
    waktu_baca DATETIME DEFAULT CURRENT_TIMESTAMP,
    status_aktif INTEGER DEFAULT 1
);
```

### Penggunaan
```c
// Inisialisasi database
inisialisasiDatabase();

// Simpan data tanaman
DataTanaman tanaman = {...};
simpanDataTanamanDB(&tanaman);

// Ambil data tanaman
DataTanaman daftarTanaman[50];
int jumlah = ambilDataTanamanDB(daftarTanaman, 50);
```

---

## Konektivitas Jaringan

### Web Server Terintegrasi
- **Port Default**: 8080
- **Protocol**: HTTP/1.1
- **Multi-threading**: Mendukung multiple client connections
- **API Endpoints**: RESTful API untuk data sensor dan kontrol

### Endpoints API
```
GET /                    - Dashboard utama
GET /api/data           - Data tanaman JSON
GET /api/sensor         - Data sensor real-time JSON
GET /api/export         - Download data CSV
POST /api/control       - Kontrol sistem jarak jauh
```

### Contoh Response JSON
```json
{
  "suhu": 25.5,
  "kelembaban": 65.2,
  "kelembaban_tanah": 45.8,
  "cahaya": 850.0,
  "waktu": "2025-07-22 14:30:00",
  "status": "aktif"
}
```

### Penggunaan
```c
// Inisialisasi jaringan
inisialisasiJaringan();

// Mulai web server
mulaiWebServer(8080);

// Cek status koneksi
int status = cekStatusKoneksi();
```

---

## Integrasi Sensor

### Sensor yang Didukung
- **DHT22**: Suhu dan kelembaban udara
- **Soil Moisture**: Kelembaban tanah
- **LDR**: Intensitas cahaya
- **Extensible**: Mudah menambah sensor baru

### Fitur Sensor
- **Real-time Monitoring**: Pembacaan setiap 30 detik
- **Kalibrasi**: Sistem kalibrasi untuk akurasi
- **Validasi Data**: Filter untuk data yang tidak valid
- **Simulasi**: Mode simulasi untuk testing tanpa hardware

### Konfigurasi Sensor
```c
// Daftarkan sensor baru
daftarkanSensor("DHT22_SUHU", "Greenhouse_Utama", "°C");

// Baca sensor
int suhu = bacaSensorSuhu(PIN_SENSOR_SUHU);

// Kalibrasi sensor
kalibrasiSensor("DHT22_SUHU", 25.0);
```

### Monitoring Otomatis
```c
// Mulai monitoring background
HANDLE thread = mulaiMonitoringOtomatis();

// Update manual
updateDataSensorOtomatis();
```

---

## Dashboard Web

### Fitur Dashboard
- **Real-time Charts**: Grafik data sensor live
- **Responsive Design**: Otomatis menyesuaikan layar
- **Multi-device**: Desktop, tablet, mobile
- **Auto-refresh**: Update otomatis setiap 30 detik

### Komponen Dashboard
- **Status Cards**: Kartu status untuk setiap sensor
- **Trend Graphs**: Grafik tren data historis
- **Alert Panel**: Panel peringatan dan notifikasi
- **Control Panel**: Kontrol sistem jarak jauh

### Akses Dashboard
1. Jalankan program greenhouse_advanced.exe
2. Buka browser
3. Akses: `http://localhost:8080`
4. Dashboard akan menampilkan data real-time

### Customization
- Tema warna dapat disesuaikan
- Layout responsif untuk berbagai device
- Widget dapat ditambah/dikurangi
- Export data langsung dari dashboard

---

## Aplikasi Mobile

### Fitur Mobile (Planned)
- **Cross-platform**: Android dan iOS
- **Push Notifications**: Notifikasi real-time
- **Remote Control**: Kontrol sistem dari smartphone
- **Offline Mode**: Cache data untuk akses offline

### API Integration
```javascript
// Contoh integrasi mobile app
fetch('http://[ip-greenhouse]:8080/api/sensor')
  .then(response => response.json())
  .then(data => {
    updateUI(data);
  });
```

---

## Notifikasi dan Peringatan

### Jenis Notifikasi
- **Push Notifications**: Notifikasi desktop
- **Email Alerts**: Email otomatis (simulasi)
- **SMS Notifications**: SMS darurat (simulasi)
- **Web Notifications**: Browser notifications

### Kondisi Peringatan
- **Suhu Tinggi**: > 35°C
- **Suhu Rendah**: < 15°C
- **Kelembaban Tanah Rendah**: < 30%
- **Kelembaban Udara Tinggi**: > 90%

### Prioritas Peringatan
- **Tinggi (3)**: Kondisi berbahaya, tindakan segera
- **Sedang (2)**: Perlu perhatian dalam 1-2 jam
- **Rendah (1)**: Informasi umum

### Penggunaan
```c
// Kirim notifikasi push
kirimNotifikasiPush("Suhu terlalu tinggi!", 3);

// Kirim email alert
kirimNotifikasiEmail("admin@greenhouse.com", "Alert", "Peringatan sistem");

// Periksa peringatan otomatis
periksaPeningatanOtomatis();
```

---

## Ekspor Data

### Format Export
- **CSV**: Kompatibel dengan Excel
- **JSON**: Untuk integrasi API
- **PDF**: Laporan formal (planned)
- **Excel**: Native format .xlsx (planned)

### Jenis Laporan
- **Harian**: Ringkasan data per hari
- **Mingguan**: Trend seminggu
- **Bulanan**: Analisis bulanan
- **Custom Range**: Rentang tanggal kustom

### Contoh Export CSV
```csv
Nama Tanaman,Jenis,Suhu,Kelembaban,Kelembaban Tanah,Intensitas Cahaya,Waktu
"Tomat Cherry","Solanaceae",25.5,65.2,45.8,850.0,"2025-07-22 14:30:00"
"Selada","Asteraceae",24.8,68.1,52.3,720.0,"2025-07-22 14:30:00"
```

### Penggunaan
```c
// Setup parameter ekspor
ParameterEkspor param;
strcpy(param.namaFile, "data_tanaman");
param.jenisData = 1; // 1=Tanaman, 2=Sensor, 3=Inventaris

// Ekspor ke CSV
eksporKeCSV(&param);

// Buat laporan harian
buatLaporanHarian();
```

---

## Multi-bahasa

### Bahasa yang Didukung
- **Indonesia**: Bahasa utama
- **English**: Planned
- **Local Languages**: Sesuai kebutuhan daerah

### Sistem Localization
```c
// Muat bahasa
muatBahasa("id_ID");

// Dapatkan teks berdasarkan kunci
char* teks = dapatkanTeks("menu.main.title");
```

### File Bahasa (JSON Format)
```json
{
  "id_ID": {
    "menu.main.title": "Menu Utama",
    "sensor.temperature": "Suhu",
    "alert.high_temp": "Suhu terlalu tinggi!"
  },
  "en_US": {
    "menu.main.title": "Main Menu",
    "sensor.temperature": "Temperature",
    "alert.high_temp": "Temperature too high!"
  }
}
```

---

## Instalasi dan Konfigurasi

### System Requirements
- **OS**: Windows 10/11, Linux Ubuntu 18+
- **Compiler**: GCC with C99 support
- **Libraries**: SQLite3, WinSock2 (Windows)
- **Memory**: Minimum 512MB RAM
- **Storage**: 100MB free space

### Dependencies Windows
```bash
# MSYS2 Installation
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-sqlite3
pacman -S mingw-w64-x86_64-curl
```

### Dependencies Linux
```bash
sudo apt-get update
sudo apt-get install gcc build-essential
sudo apt-get install libsqlite3-dev
sudo apt-get install libcurl4-openssl-dev
```

### Kompilasi
```bash
# Menggunakan Makefile
make -f Makefile_advanced all

# Atau menggunakan build script
./build_advanced.bat  # Windows
./build_advanced.sh   # Linux
```

### Konfigurasi Awal
1. **Database Setup**: Otomatis saat pertama kali run
2. **Network Configuration**: Edit IP dan port jika perlu
3. **Sensor Calibration**: Kalibrasi sensor sesuai kondisi lokal
4. **Notification Settings**: Setup email dan SMS gateway

### File Konfigurasi
```ini
[database]
path=greenhouse_data.db
backup_interval=3600

[network]
web_port=8080
api_enabled=true

[sensors]
update_interval=30
auto_calibrate=true

[notifications]
email_enabled=true
sms_enabled=false
push_enabled=true
```

### Testing
```bash
# Test kompilasi
make test

# Test database
./greenhouse_advanced.exe --test-db

# Test network
./greenhouse_advanced.exe --test-network
```

---

## Troubleshooting

### Common Issues

#### Kompilasi Error
```
Error: sqlite3.h not found
Solution: Install SQLite3 development libraries
```

#### Network Error
```
Error: Web server failed to start
Solution: Check if port 8080 is available
```

#### Database Error
```
Error: Cannot open database
Solution: Check file permissions and disk space
```

### Log Files
- **System Log**: `greenhouse_system.log`
- **Error Log**: `greenhouse_errors.log`
- **Sensor Log**: `sensor_data.log`
- **Network Log**: `network_activity.log`

### Support
- **Documentation**: README.md, DOCS.md
- **Sample Data**: SAMPLE_DATA.md
- **GitHub Issues**: [Repository Issues](https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS/issues)

---

## Roadmap

### Phase 1 ✅
- Database integration
- Basic web dashboard
- Sensor simulation
- Export functionality

### Phase 2 🚧
- Real hardware sensor integration
- Mobile app development
- Email/SMS gateway integration
- Advanced analytics

### Phase 3 📋
- Machine learning predictions
- IoT cloud integration
- Multi-greenhouse support
- Advanced reporting

---

*Dokumentasi ini akan terus diperbarui seiring pengembangan fitur baru.*
