@echo off
:: Enhanced Build Script for Greenhouse Monitoring System ITTS v2.0
:: Windows Batch File for Easy Compilation and Execution

color 0A
echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║  🌱 GREENHOUSE MONITORING SYSTEM ITTS v2.0 - BUILD SCRIPT  ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.

:: Check if GCC is available
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo ❌ Error: GCC compiler not found!
    echo.
    echo 💡 Please install one of the following:
    echo    - MinGW-w64: https://www.mingw-w64.org/
    echo    - MSYS2: https://www.msys2.org/
    echo    - Dev-C++: https://www.bloodshed.net/devcpp.html
    echo    - Code::Blocks: https://www.codeblocks.org/
    echo.
    pause
    exit /b 1
)

:menu
cls
echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║              🌱 GREENHOUSE BUILD MENU 🌱                    ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.
echo  1. 🔨 Build Basic Version
echo  2. 🚀 Build Advanced Version  
echo  3. 🔧 Build Both Versions
echo  4. ▶️  Run Basic Version
echo  5. 🚀 Run Advanced Version
echo  6. 🧹 Clean Build Files
echo  7. 🗑️  Clean Data Files (⚠️  Destructive!)
echo  8. 📋 Show System Info
echo  9. ❓ Help
echo  0. 🚪 Exit
echo.
set /p choice="Enter your choice (0-9): "

if "%choice%"=="1" goto build_basic
if "%choice%"=="2" goto build_advanced
if "%choice%"=="3" goto build_both
if "%choice%"=="4" goto run_basic
if "%choice%"=="5" goto run_advanced
if "%choice%"=="6" goto clean_build
if "%choice%"=="7" goto clean_data
if "%choice%"=="8" goto system_info
if "%choice%"=="9" goto help
if "%choice%"=="0" goto exit
echo ❌ Invalid choice! Please enter a number between 0-9.
pause
goto menu

:build_basic
echo.
echo 🔨 Building Basic Greenhouse Monitoring System...
echo ═══════════════════════════════════════════════
gcc -Wall -Wextra -std=c99 -O2 -o greenhouse_system.exe greenhouse_monitoring.c
if %errorlevel% equ 0 (
    echo ✅ Basic version compiled successfully!
    echo 📁 Executable: greenhouse_system.exe
) else (
    echo ❌ Compilation failed!
)
echo.
pause
goto menu

:build_advanced
echo.
echo 🚀 Building Advanced Greenhouse Monitoring System...
echo ═══════════════════════════════════════════════════
gcc -Wall -Wextra -std=c99 -O2 -o greenhouse_advanced.exe greenhouse_system_advanced.c
if %errorlevel% equ 0 (
    echo ✅ Advanced version compiled successfully!
    echo 📁 Executable: greenhouse_advanced.exe
) else (
    echo ❌ Compilation failed!
)
echo.
pause
goto menu

:build_both
echo.
echo 🔧 Building Both Versions...
echo ═══════════════════════════
call :build_basic_silent
call :build_advanced_silent
echo ✅ Both versions compiled!
echo.
pause
goto menu

:build_basic_silent
gcc -Wall -Wextra -std=c99 -O2 -o greenhouse_system.exe greenhouse_monitoring.c >nul 2>&1
if %errorlevel% equ 0 (
    echo ✅ Basic version: OK
) else (
    echo ❌ Basic version: FAILED
)
goto :eof

:build_advanced_silent
gcc -Wall -Wextra -std=c99 -O2 -o greenhouse_advanced.exe greenhouse_system_advanced.c >nul 2>&1
if %errorlevel% equ 0 (
    echo ✅ Advanced version: OK
) else (
    echo ❌ Advanced version: FAILED
)
goto :eof

:run_basic
echo.
echo ▶️  Starting Basic Greenhouse Monitoring System...
echo ══════════════════════════════════════════════════
if not exist greenhouse_system.exe (
    echo ❌ greenhouse_system.exe not found!
    echo 💡 Please build the basic version first.
    pause
    goto menu
)
echo 🚀 Launching application...
echo.
greenhouse_system.exe
echo.
echo 👋 Application closed. Press any key to return to menu.
pause >nul
goto menu

:run_advanced
echo.
echo 🚀 Starting Advanced Greenhouse Monitoring System...
echo ════════════════════════════════════════════════════
if not exist greenhouse_advanced.exe (
    echo ❌ greenhouse_advanced.exe not found!
    echo 💡 Please build the advanced version first.
    pause
    goto menu
)
echo 🚀 Launching application...
echo.
greenhouse_advanced.exe
echo.
echo 👋 Application closed. Press any key to return to menu.
pause >nul
goto menu

:clean_build
echo.
echo 🧹 Cleaning Build Files...
echo ═════════════════════════
del /q greenhouse_system.exe 2>nul
del /q greenhouse_advanced.exe 2>nul
del /q *.o 2>nul
del /q *.obj 2>nul
echo ✅ Build files cleaned!
echo.
pause
goto menu

:clean_data
echo.
echo ⚠️  WARNING: This will delete all data files!
echo ═══════════════════════════════════════════════
echo 📁 Files to be deleted:
echo    - equipment_inventory.txt
echo    - last_watered_date.txt  
echo    - plant_data.txt
echo    - alerts.txt
echo    - monitoring_log.txt
echo.
set /p confirm="Are you sure? (y/N): "
if /i "%confirm%"=="y" (
    del /q equipment_inventory.txt 2>nul
    del /q last_watered_date.txt 2>nul
    del /q plant_data.txt 2>nul
    del /q alerts.txt 2>nul
    del /q monitoring_log.txt 2>nul
    echo ✅ Data files deleted!
) else (
    echo 🔙 Operation cancelled.
)
echo.
pause
goto menu

:system_info
echo.
echo 📋 System Information
echo ═══════════════════════
echo 💻 Operating System: %OS%
echo 🏛️  Architecture: %PROCESSOR_ARCHITECTURE%
echo 👤 Username: %USERNAME%
echo 📁 Current Directory: %CD%
echo ⏰ Date/Time: %DATE% %TIME%
echo.
echo 🔧 Development Tools:
where gcc >nul 2>nul && echo ✅ GCC: Available || echo ❌ GCC: Not Found
where mingw32-gcc >nul 2>nul && echo ✅ MinGW: Available || echo ❌ MinGW: Not Found
where git >nul 2>nul && echo ✅ Git: Available || echo ❌ Git: Not Found
echo.
echo 📁 Project Files:
if exist greenhouse_monitoring.c echo ✅ greenhouse_monitoring.c
if exist greenhouse_system_advanced.c echo ✅ greenhouse_system_advanced.c
if exist Makefile echo ✅ Makefile
if exist README.md echo ✅ README.md
echo.
echo 🏗️  Built Executables:
if exist greenhouse_system.exe echo ✅ greenhouse_system.exe
if exist greenhouse_advanced.exe echo ✅ greenhouse_advanced.exe
echo.
echo 📊 Data Files:
if exist equipment_inventory.txt echo 📦 equipment_inventory.txt
if exist last_watered_date.txt echo 💧 last_watered_date.txt
if exist plant_data.txt echo 🌱 plant_data.txt
if exist alerts.txt echo 🔔 alerts.txt
if exist monitoring_log.txt echo 📈 monitoring_log.txt
echo.
pause
goto menu

:help
echo.
echo ❓ Help & Usage Instructions
echo ═══════════════════════════
echo.
echo 🔨 BUILD OPTIONS:
echo    Basic Version    - Simple greenhouse monitoring with core features
echo    Advanced Version - Full-featured system with enhanced capabilities
echo    Both Versions    - Compile both basic and advanced versions
echo.
echo ▶️  RUN OPTIONS:
echo    The system will automatically check for executables before running.
echo    If not found, you'll be prompted to build first.
echo.
echo 🧹 CLEAN OPTIONS:
echo    Clean Build Files - Removes .exe, .o, .obj files
echo    Clean Data Files  - Removes all system data (⚠️  irreversible!)
echo.
echo 💡 TIPS:
echo    - Make sure GCC is installed and in your PATH
echo    - Use MinGW-w64 for best Windows compatibility  
echo    - Build the advanced version for full features
echo    - Regular backups are recommended before cleaning data
echo.
echo 🌐 ADDITIONAL RESOURCES:
echo    - README.md: Detailed documentation
echo    - Source code: Well-commented for learning
echo    - GitHub: Check for updates and issues
echo.
pause
goto menu

:exit
echo.
echo 🌱 Thank you for using Greenhouse Monitoring System ITTS!
echo 🌿 Happy greenhouse management! 🌸
echo.
echo 👋 Goodbye!
timeout /t 2 >nul
exit /b 0
