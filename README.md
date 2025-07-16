# Sistem Monitoring Greenhouse ITTS

Sistem monitoring dan manajemen greenhouse yang komprehensif ditulis dalam bahasa C yang membantu Anda melacak kesehatan tanaman, kondisi lingkungan, dan inventaris peralatan.

## Fitur

### Manajemen Tanaman
- **Monitoring Kesehatan Tanaman Real-time**: Simulasi pembacaan sensor untuk suhu, kelembaban, dan kelembapan tanah
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

### Fitur Tambahan
- **Interface Ramah Pengguna**: Sistem menu yang berwarna dan intuitif
- **Validasi Input**: Penanganan error yang kuat dan validasi input
- **Lintas Platform**: Bekerja di Windows, Linux, dan macOS
- **Penyimpanan Berbasis File**: Penyimpanan data persisten menggunakan file teks
- **Penanganan Tanggal Otomatis**: Integrasi tanggal saat ini

## Memulai

### Prasyarat
- Compiler GCC (MinGW di Windows)
- Dukungan standar C99

### Instalasi

1. **Clone repository**:
   ```bash
   git clone https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS.git
   cd Greenhouse-Monitoring-System-ITTS
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
├── environment.yml              # Environment Conda (opsional)
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

## Kontribusi

1. Fork repository
2. Buat branch fitur (`git checkout -b feature/FiturMenarik`)
3. Commit perubahan Anda (`git commit -m 'Tambah FiturMenarik'`)
4. Push ke branch (`git push origin feature/FiturMenarik`)
5. Buka Pull Request

## Lisensi

Proyek ini dilisensikan di bawah Lisensi MIT - lihat file [LICENSE](LICENSE) untuk detail.

## Pengembang

**KangFeeder090403**
- GitHub: [@KangFeeder090403](https://github.com/KangFeeder090403)
- Email: dukungan@itts-greenhouse.com

## Terima Kasih

Terima kasih telah menggunakan Sistem Monitoring Greenhouse ITTS!
Semoga sistem ini membantu Anda dalam mengelola greenhouse dengan lebih efektif.

---
*Dibuat dengan cinta untuk komunitas greenhouse Indonesia*

## 📞 Support

If you have any questions or need help with the system, please:
1. Check this README first
2. Look through existing [Issues](https://github.com/KangFeeder090403/Greenhouse-Monitoring-System-ITTS/issues)
3. Create a new issue if needed

---

**Happy Greenhouse Monitoring! 🌱🌿🌺**