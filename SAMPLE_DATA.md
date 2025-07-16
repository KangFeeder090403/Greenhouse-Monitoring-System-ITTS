# File Data Contoh untuk Sistem Monitoring Greenhouse

Direktori ini berisi file data contoh untuk membantu Anda memulai menggunakan Sistem Monitoring Greenhouse.

## Petunjuk Setup Cepat

1. **Salin file contoh ke direktori utama**:
   ```bash
   # Linux/macOS
   cp sample_data/* ../
   
   # Windows
   copy sample_data\* ..\
   ```

2. **Atau buat file secara manual** menggunakan konten di bawah ini.

## Konten File Contoh

### data_inventaris.txt
```
Item: Kaleng Penyiram | Kategori: Alat | Jumlah: 3 | Harga: Rp239.900 | Stok Min: 1 | Tanggal: 16-07-2025
Item: Pupuk NPK | Kategori: Pupuk | Jumlah: 10 | Harga: Rp127.500 | Stok Min: 2 | Tanggal: 16-07-2025
Item: Benih Tomat | Kategori: Benih | Jumlah: 25 | Harga: Rp44.900 | Stok Min: 5 | Tanggal: 16-07-2025
Item: Gunting Pangkas | Kategori: Alat | Jumlah: 2 | Harga: Rp344.900 | Stok Min: 1 | Tanggal: 16-07-2025
Item: Pot Tanaman 6 Inci | Kategori: Wadah | Jumlah: 15 | Harga: Rp52.400 | Stok Min: 5 | Tanggal: 16-07-2025
Item: pH Meter Tanah | Kategori: Instrumen | Jumlah: 1 | Harga: Rp689.900 | Stok Min: 1 | Tanggal: 16-07-2025
Item: Kompos Organik | Kategori: Pupuk | Jumlah: 8 | Harga: Rp194.900 | Stok Min: 3 | Tanggal: 16-07-2025
```

### data_tanaman.txt
```
Tanaman_Tomat_1 Tomat 24.5 62.0 55.0 850 15-07-2025 10-07-2025 88
Kebun_Kemangi Kemangi 22.8 58.0 48.0 920 16-07-2025 05-07-2025 82
Semak_Mawar_1 Mawar 26.2 65.0 52.0 780 14-07-2025 01-07-2025 85
Bedengan_Selada_A Selada 21.5 70.0 62.0 650 16-07-2025 12-07-2025 89
Tanaman_Cabai_Merah Cabai 25.8 60.0 50.0 900 15-07-2025 08-07-2025 86
```

### tanggal_siram.txt
```
16-07-2025 Tanaman_Tomat_1
16-07-2025 Kebun_Kemangi
16-07-2025 Bedengan_Selada_A
15-07-2025 Tanaman_Tomat_1
15-07-2025 Tanaman_Cabai_Merah
14-07-2025 Semak_Mawar_1
```

### notifikasi.txt
```
15-07-2025 14:30:22|Kesehatan|Monitoring kesehatan tanaman selesai - semua sistem normal|1
16-07-2025 08:15:45|Penyiraman|Penyiraman dicatat untuk Tanaman_Tomat_1 pada 16-07-2025|1
16-07-2025 09:22:10|Inventaris|Peringatan stok rendah: Kompos Organik (3 unit tersisa)|2
16-07-2025 10:45:33|Tanaman|Tanaman baru ditambahkan: Bedengan_Selada_A (Selada)|1
16-07-2025 11:20:18|Kesehatan|Kondisi optimal terdeteksi di zona greenhouse 1|1
```

## Spesifikasi Format File

### Format Inventaris Peralatan
```
Item: [nama] | Kategori: [kategori] | Jumlah: [angka] | Harga: Rp[jumlah] | Stok Min: [angka] | Tanggal: [dd-mm-yyyy]
```

### Format Data Tanaman
```
[nama_tanaman] [jenis_tanaman] [suhu] [kelembaban] [kelembaban_tanah] [intensitas_cahaya] [terakhir_disiram] [tanggal_tanam] [skor_kesehatan]
```

### Format Catatan Penyiraman
```
[dd-mm-yyyy] [nama_tanaman]
```

### Format Notifikasi
```
[dd-mm-yyyy hh:mm:ss]|[jenis_notifikasi]|[pesan]|[tingkat_prioritas]
```

## Tips Menggunakan Data Contoh

1. **Sesuaikan Nama**: Ubah nama tanaman dan peralatan sesuai dengan greenhouse Anda
2. **Perbarui Tanggal**: Modifikasi tanggal ke waktu saat ini atau realistis
3. **Sesuaikan Nilai**: Ubah jumlah, harga, dan pengukuran sesuai situasi Anda
4. **Tambah Entri**: Silakan tambahkan lebih banyak tanaman dan peralatan sesuai kebutuhan
5. **Uji Fitur**: Gunakan data ini untuk menjelajahi semua fitur sistem

## Membuat Data Sendiri

### Mulai dari Awal
Jika Anda lebih suka memulai dengan file kosong, buat file kosong berikut:
- `data_inventaris.txt` (kosong)
- `data_tanaman.txt` (kosong)
- `tanggal_siram.txt` (kosong)
- `notifikasi.txt` (kosong)

Sistem akan mengisinya saat Anda menggunakan aplikasi.

### Validasi Data
Sistem mencakup validasi untuk:
- ✅ Format tanggal (dd-mm-yyyy)
- ✅ Nilai numerik (jumlah, harga, pengukuran)
- ✅ Field yang diperlukan
- ✅ Izin dan akses file

## Rekomendasi Backup

Selalu backup file data Anda sebelum:
- 🔄 Update sistem
- 🧹 Operasi pembersihan
- 🔧 Perubahan konfigurasi besar
- 📊 Impor data besar

```bash
# Buat direktori backup
mkdir backup_$(date +%Y%m%d)

# Salin file data
cp *.txt backup_$(date +%Y%m%d)/
```

Selamat monitoring greenhouse! 🌱
