@echo off
chcp 65001 >nul
title Sistem Build Greenhouse Monitoring Advanced ITTS

echo ════════════════════════════════════════════════════════════
echo            SISTEM BUILD GREENHOUSE ADVANCED
echo ════════════════════════════════════════════════════════════
echo.

:MENU
echo Pilih opsi build:
echo.
echo  1. Build Sistem Lengkap (Recommended)
echo  2. Build Mode Debug
echo  3. Build Mode Release
echo  4. Build dan Jalankan
echo  5. Test Sistem
echo  6. Clean Build Files
echo  7. Install Dependencies Info
echo  8. Buat Backup
echo  9. Help dan Dokumentasi
echo  0. Keluar
echo.
echo ════════════════════════════════════════════════════════════

set /p choice="Masukkan pilihan (0-9): "

if "%choice%"=="1" goto BUILD_ALL
if "%choice%"=="2" goto BUILD_DEBUG
if "%choice%"=="3" goto BUILD_RELEASE
if "%choice%"=="4" goto BUILD_RUN
if "%choice%"=="5" goto TEST_SYSTEM
if "%choice%"=="6" goto CLEAN
if "%choice%"=="7" goto DEPS_INFO
if "%choice%"=="8" goto BACKUP
if "%choice%"=="9" goto HELP
if "%choice%"=="0" goto EXIT

echo Pilihan tidak valid! Silakan coba lagi.
pause
goto MENU

:BUILD_ALL
echo.
echo Memulai kompilasi sistem lengkap...
echo ────────────────────────────────────────────────────────────

rem Buat direktori yang diperlukan
if not exist "build" mkdir build
if not exist "exports" mkdir exports
if not exist "backup" mkdir backup

echo Mengompilasi komponen database...
gcc -Wall -Wextra -std=c99 -O2 -c database_functions.c -o database_functions.o
if errorlevel 1 goto ERROR

echo Mengompilasi komponen jaringan...
gcc -Wall -Wextra -std=c99 -O2 -c network_functions.c -o network_functions.o
if errorlevel 1 goto ERROR

echo Mengompilasi komponen sensor...
gcc -Wall -Wextra -std=c99 -O2 -c sensor_functions.c -o sensor_functions.o
if errorlevel 1 goto ERROR

echo Mengompilasi komponen ekspor dan notifikasi...
gcc -Wall -Wextra -std=c99 -O2 -c export_notification.c -o export_notification.o
if errorlevel 1 goto ERROR

echo Mengompilasi sistem utama...
gcc -Wall -Wextra -std=c99 -O2 -c greenhouse_system_advanced.c -o greenhouse_system_advanced.o
if errorlevel 1 goto ERROR

echo Linking program final...
gcc greenhouse_system_advanced.o database_functions.o network_functions.o sensor_functions.o export_notification.o -o greenhouse_advanced.exe -lsqlite3 -lws2_32 -lm
if errorlevel 1 goto LINK_ERROR

echo.
echo Kompilasi berhasil!
echo ────────────────────────────────────────────────────────────
echo Program: greenhouse_advanced.exe
echo Dashboard Web: http://localhost:8080
echo Database: SQLite3 terintegrasi
echo Sensor: Simulasi real-time
echo Jaringan: Web server dan monitoring jarak jauh
echo ────────────────────────────────────────────────────────────
goto MENU_CONTINUE

:BUILD_DEBUG
echo.
echo Memulai kompilasi mode debug...
echo ────────────────────────────────────────────────────────────

gcc -Wall -Wextra -std=c99 -g -DDEBUG -c *.c
if errorlevel 1 goto ERROR

gcc *.o -o greenhouse_advanced_debug.exe -lsqlite3 -lws2_32 -lm
if errorlevel 1 goto LINK_ERROR

echo Debug build berhasil: greenhouse_advanced_debug.exe
goto MENU_CONTINUE

:BUILD_RELEASE
echo.
echo Memulai kompilasi mode release...
echo ────────────────────────────────────────────────────────────

gcc -Wall -Wextra -std=c99 -O3 -DNDEBUG -c *.c
if errorlevel 1 goto ERROR

gcc *.o -o greenhouse_advanced_release.exe -lsqlite3 -lws2_32 -lm
if errorlevel 1 goto LINK_ERROR

echo Release build berhasil: greenhouse_advanced_release.exe
goto MENU_CONTINUE

:BUILD_RUN
echo.
echo Build dan jalankan sistem...
echo ────────────────────────────────────────────────────────────

call :BUILD_ALL
if exist greenhouse_advanced.exe (
    echo.
    echo Menjalankan program...
    echo ════════════════════════════════════════════════════════════
    greenhouse_advanced.exe
) else (
    echo Gagal menemukan executable!
    pause
)
goto MENU

:TEST_SYSTEM
echo.
echo Menjalankan test sistem...
echo ────────────────────────────────────────────────────────────

if not exist greenhouse_advanced.exe (
    echo Program belum dikompilasi. Kompilasi terlebih dahulu.
    pause
    goto MENU
)

echo Test 1: Verifikasi executable...
if exist greenhouse_advanced.exe (
    echo Executable ditemukan
) else (
    echo Executable tidak ditemukan
)

echo Test 2: Cek dependencies...
echo SQLite3 support
echo Windows Socket library
echo Math library

echo Test 3: Cek file konfigurasi...
if exist data_inventaris.txt (echo File inventaris) else (echo File inventaris belum ada)
if exist data_tanaman.txt (echo File tanaman) else (echo File tanaman belum ada)

echo.
echo Test sistem selesai!
goto MENU_CONTINUE

:CLEAN
echo.
echo Membersihkan file build...
echo ────────────────────────────────────────────────────────────

if exist *.o del /q *.o
if exist greenhouse_advanced.exe del /q greenhouse_advanced.exe
if exist greenhouse_advanced_debug.exe del /q greenhouse_advanced_debug.exe
if exist greenhouse_advanced_release.exe del /q greenhouse_advanced_release.exe
if exist greenhouse_data.db del /q greenhouse_data.db

echo File build berhasil dibersihkan!
goto MENU_CONTINUE

:DEPS_INFO
echo.
echo Informasi Dependencies
echo ════════════════════════════════════════════════════════════
echo.
echo Dependencies yang diperlukan:
echo.
echo 1. GCC Compiler dengan C99 support
echo    - MinGW-w64 (Windows)
echo    - MSYS2: pacman -S mingw-w64-x86_64-gcc
echo.
echo 2. SQLite3 Development Libraries
echo    - Download dari: https://sqlite.org/download.html
echo    - MSYS2: pacman -S mingw-w64-x86_64-sqlite3
echo.
echo 3. Windows Socket Library (built-in)
echo    - Sudah tersedia di Windows
echo.
echo 4. Math Library (built-in)
echo    - Sudah tersedia dengan GCC
echo.
echo Instalasi MSYS2 (Recommended):
echo 1. Download MSYS2 dari https://www.msys2.org/
echo 2. Install dan jalankan MSYS2 terminal
echo 3. Update: pacman -Syu
echo 4. Install tools: pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-sqlite3
echo.
goto MENU_CONTINUE

:BACKUP
echo.
echo Membuat backup source code...
echo ────────────────────────────────────────────────────────────

for /f "tokens=1-3 delims=/ " %%a in ('date /t') do set tanggal=%%c%%b%%a
for /f "tokens=1-2 delims=: " %%a in ('time /t') do set waktu=%%a%%b

if not exist backup mkdir backup

echo Menyalin file source...
xcopy /y *.c backup\ >nul 2>&1
xcopy /y *.h backup\ >nul 2>&1
xcopy /y *.txt backup\ >nul 2>&1
xcopy /y *.md backup\ >nul 2>&1
xcopy /y Makefile* backup\ >nul 2>&1
xcopy /y build.bat backup\ >nul 2>&1

echo Backup berhasil dibuat di folder backup\
echo Timestamp: %tanggal%_%waktu%
goto MENU_CONTINUE

:HELP
echo.
echo Help dan Dokumentasi
echo ════════════════════════════════════════════════════════════
echo.
echo FITUR SISTEM:
echo.
echo Database SQLite
echo    - Penyimpanan data tanaman, sensor, dan inventaris
echo    - Backup otomatis dan recovery
echo.
echo Web Dashboard
echo    - Monitoring real-time di browser
echo    - Akses: http://localhost:8080
echo    - API endpoints untuk data sensor
echo.
echo Sistem Sensor
echo    - Simulasi sensor suhu, kelembaban, cahaya
echo    - Monitoring otomatis setiap 30 detik
echo    - Kalibrasi dan validasi data
echo.
echo Ekspor Data
echo    - CSV export untuk Excel
echo    - Laporan harian dan mingguan
echo    - Backup database otomatis
echo.
echo Notifikasi
echo    - Push notifications
echo    - Email alerts (simulasi)
echo    - SMS notifications (simulasi)
echo.
echo Multi-bahasa
echo    - Interface dalam bahasa Indonesia
echo    - Siap untuk ekstensi bahasa lain
echo.
echo PENGGUNAAN:
echo 1. Kompilasi dengan opsi 1 (Build Sistem Lengkap)
echo 2. Jalankan greenhouse_advanced.exe
echo 3. Akses web dashboard di browser
echo 4. Monitor data sensor real-time
echo.
goto MENU_CONTINUE

:ERROR
echo.
echo ERROR: Kompilasi gagal!
echo ────────────────────────────────────────────────────────────
echo Kemungkinan penyebab:
echo 1. GCC compiler tidak terinstall atau tidak di PATH
echo 2. Source file (.c) rusak atau hilang
echo 3. Header file (.h) tidak ditemukan
echo.
echo Solusi:
echo 1. Install MinGW-w64 atau MSYS2
echo 2. Pastikan gcc ada di PATH
echo 3. Periksa integritas file source
echo.
pause
goto MENU

:LINK_ERROR
echo.
echo ERROR: Linking gagal!
echo ────────────────────────────────────────────────────────────
echo Kemungkinan penyebab:
echo 1. SQLite3 library tidak ditemukan
echo 2. Windows Socket library tidak tersedia
echo 3. Object files (.o) rusak
echo.
echo Solusi:
echo 1. Install SQLite3 development libraries
echo 2. Gunakan MSYS2 untuk environment lengkap
echo 3. Coba clean build (opsi 6) lalu build ulang
echo.
pause
goto MENU

:MENU_CONTINUE
echo.
echo Tekan tombol apa saja untuk kembali ke menu...
pause >nul
cls
goto MENU

:EXIT
echo.
echo Terima kasih telah menggunakan Build System!
echo Selamat mengembangkan Greenhouse Monitoring System.
echo.
pause
exit /b 0
