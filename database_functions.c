#include "greenhouse_advanced_features.h"
#include <sqlite3.h>

// Global database connection
static sqlite3 *db = NULL;

// Callback function untuk query results
static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    printf("\n");
    for(i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Inisialisasi database SQLite
int inisialisasiDatabase() {
    int rc;
    char *errMsg = 0;
    
    // Buka koneksi database
    rc = sqlite3_open(DATABASE_NAME, &db);
    
    if (rc) {
        printf("Tidak dapat membuka database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    printf("Database berhasil dibuka\n");
    
    // Buat tabel tanaman
    char *sqlTanaman = "CREATE TABLE IF NOT EXISTS tanaman("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "nama_tanaman TEXT NOT NULL,"
                      "jenis_tanaman TEXT,"
                      "suhu REAL,"
                      "kelembaban REAL,"
                      "kelembaban_tanah REAL,"
                      "intensitas_cahaya REAL,"
                      "terakhir_disiram TEXT,"
                      "tanggal_tanam TEXT,"
                      "skor_kesehatan INTEGER,"
                      "waktu_input DATETIME DEFAULT CURRENT_TIMESTAMP);";
    
    rc = sqlite3_exec(db, sqlTanaman, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    
    // Buat tabel sensor
    char *sqlSensor = "CREATE TABLE IF NOT EXISTS sensor_data("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "tipe_sensor TEXT NOT NULL,"
                     "lokasi TEXT,"
                     "nilai REAL,"
                     "satuan TEXT,"
                     "waktu_baca DATETIME DEFAULT CURRENT_TIMESTAMP,"
                     "status_aktif INTEGER DEFAULT 1);";
    
    rc = sqlite3_exec(db, sqlSensor, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    
    // Buat tabel inventaris
    char *sqlInventaris = "CREATE TABLE IF NOT EXISTS inventaris("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "nama_item TEXT NOT NULL,"
                         "jumlah INTEGER,"
                         "tanggal TEXT,"
                         "harga REAL,"
                         "kategori TEXT,"
                         "stok_minimal INTEGER,"
                         "waktu_update DATETIME DEFAULT CURRENT_TIMESTAMP);";
    
    rc = sqlite3_exec(db, sqlInventaris, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    
    // Buat tabel notifikasi
    char *sqlNotifikasi = "CREATE TABLE IF NOT EXISTS notifikasi("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "jenis_notifikasi TEXT,"
                         "pesan TEXT,"
                         "prioritas INTEGER,"
                         "status_baca INTEGER DEFAULT 0,"
                         "waktu_kirim DATETIME DEFAULT CURRENT_TIMESTAMP);";
    
    rc = sqlite3_exec(db, sqlNotifikasi, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    
    printf("Semua tabel database berhasil dibuat\n");
    return 0;
}

// Simpan data tanaman ke database
int simpanDataTanamanDB(DataTanaman* tanaman) {
    if (!db) {
        printf("Database belum diinisialisasi\n");
        return 1;
    }
    
    char *sql = "INSERT INTO tanaman (nama_tanaman, jenis_tanaman, suhu, kelembaban, "
                "kelembaban_tanah, intensitas_cahaya, terakhir_disiram, tanggal_tanam, skor_kesehatan) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        printf("Gagal menyiapkan statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    // Bind parameter
    sqlite3_bind_text(stmt, 1, tanaman->namaTanaman, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tanaman->jenisTanaman, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, tanaman->suhu);
    sqlite3_bind_double(stmt, 4, tanaman->kelembaban);
    sqlite3_bind_double(stmt, 5, tanaman->kelembapanTanah);
    sqlite3_bind_double(stmt, 6, tanaman->intensitasCahaya);
    sqlite3_bind_text(stmt, 7, tanaman->terakhirDisiram, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, tanaman->tanggalTanam, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, tanaman->skorKesehatan);
    
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        printf("Gagal menyimpan data tanaman: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }
    
    printf("Data tanaman berhasil disimpan ke database\n");
    sqlite3_finalize(stmt);
    return 0;
}

// Simpan data sensor ke database
int simpanDataSensorDB(SensorData* sensor) {
    if (!db) {
        printf("Database belum diinisialisasi\n");
        return 1;
    }
    
    char *sql = "INSERT INTO sensor_data (tipe_sensor, lokasi, nilai, satuan, status_aktif) "
                "VALUES (?, ?, ?, ?, ?);";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        printf("Gagal menyiapkan statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    sqlite3_bind_text(stmt, 1, sensor->tipe, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, sensor->lokasi, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, sensor->nilai);
    sqlite3_bind_text(stmt, 4, sensor->satuan, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, sensor->statusAktif);
    
    rc = sqlite3_step(stmt);
    
    if (rc != SQLITE_DONE) {
        printf("Gagal menyimpan data sensor: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }
    
    printf("Data sensor berhasil disimpan\n");
    sqlite3_finalize(stmt);
    return 0;
}

// Ambil data tanaman dari database
int ambilDataTanamanDB(DataTanaman* tanaman, int limit) {
    if (!db) {
        printf("Database belum diinisialisasi\n");
        return 1;
    }
    
    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT nama_tanaman, jenis_tanaman, suhu, kelembaban, kelembaban_tanah, "
             "intensitas_cahaya, terakhir_disiram, tanggal_tanam, skor_kesehatan "
             "FROM tanaman ORDER BY waktu_input DESC LIMIT %d;", limit);
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        printf("Gagal menyiapkan query: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    int count = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && count < limit) {
        strcpy(tanaman[count].namaTanaman, (char*)sqlite3_column_text(stmt, 0));
        strcpy(tanaman[count].jenisTanaman, (char*)sqlite3_column_text(stmt, 1));
        tanaman[count].suhu = sqlite3_column_double(stmt, 2);
        tanaman[count].kelembaban = sqlite3_column_double(stmt, 3);
        tanaman[count].kelembapanTanah = sqlite3_column_double(stmt, 4);
        tanaman[count].intensitasCahaya = sqlite3_column_double(stmt, 5);
        strcpy(tanaman[count].terakhirDisiram, (char*)sqlite3_column_text(stmt, 6));
        strcpy(tanaman[count].tanggalTanam, (char*)sqlite3_column_text(stmt, 7));
        tanaman[count].skorKesehatan = sqlite3_column_int(stmt, 8);
        count++;
    }
    
    sqlite3_finalize(stmt);
    return count;
}

// Tutup koneksi database
int tutupDatabase() {
    if (db) {
        sqlite3_close(db);
        db = NULL;
        printf("Database berhasil ditutup\n");
        return 0;
    }
    return 1;
}

// Fungsi untuk membuat backup database
int buatBackupDatabase(char* namaFileBackup) {
    if (!db) {
        printf("Database belum diinisialisasi\n");
        return 1;
    }
    
    sqlite3 *backupDb;
    sqlite3_backup *backup;
    int rc;
    
    rc = sqlite3_open(namaFileBackup, &backupDb);
    if (rc) {
        printf("Tidak dapat membuat file backup: %s\n", sqlite3_errmsg(backupDb));
        return 1;
    }
    
    backup = sqlite3_backup_init(backupDb, "main", db, "main");
    if (backup) {
        sqlite3_backup_step(backup, -1);
        sqlite3_backup_finish(backup);
    }
    
    rc = sqlite3_errcode(backupDb);
    sqlite3_close(backupDb);
    
    if (rc == SQLITE_OK) {
        printf("Backup database berhasil dibuat: %s\n", namaFileBackup);
        return 0;
    } else {
        printf("Gagal membuat backup database\n");
        return 1;
    }
}
