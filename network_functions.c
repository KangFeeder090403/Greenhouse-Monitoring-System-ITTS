#include "greenhouse_advanced_features.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

// Global variables untuk jaringan
static WSADATA wsaData;
static SOCKET serverSocket = INVALID_SOCKET;
static int jaringanTerinitialisasi = 0;

// Inisialisasi jaringan Windows
int inisialisasiJaringan() {
    int hasil = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (hasil != 0) {
        printf("WSAStartup gagal: %d\n", hasil);
        return 1;
    }
    
    jaringanTerinitialisasi = 1;
    printf("Jaringan berhasil diinisialisasi\n");
    return 0;
}

// Mulai web server untuk dashboard
int mulaiWebServer(int port) {
    if (!jaringanTerinitialisasi) {
        printf("Jaringan belum diinisialisasi\n");
        return 1;
    }
    
    struct addrinfo *result = NULL, hints;
    char portStr[10];
    
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    
    sprintf(portStr, "%d", port);
    
    int hasil = getaddrinfo(NULL, portStr, &hints, &result);
    if (hasil != 0) {
        printf("getaddrinfo gagal: %d\n", hasil);
        WSACleanup();
        return 1;
    }
    
    serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    
    hasil = bind(serverSocket, result->ai_addr, (int)result->ai_addrlen);
    if (hasil == SOCKET_ERROR) {
        printf("Bind gagal: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    freeaddrinfo(result);
    
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen gagal: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    printf("Web server berhasil dimulai di port %d\n", port);
    printf("Akses dashboard di: http://localhost:%d\n", port);
    
    return 0;
}

// Handle client connections
DWORD WINAPI handleClient(LPVOID lpParam) {
    SOCKET clientSocket = *(SOCKET*)lpParam;
    char buffer[4096];
    int bytesReceived;
    
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        printf("Request diterima: %s\n", buffer);
        
        // Parse HTTP request
        if (strstr(buffer, "GET / ") != NULL) {
            kirimHalamanDashboard(clientSocket);
        } else if (strstr(buffer, "GET /api/data") != NULL) {
            kirimDataJSON(clientSocket);
        } else if (strstr(buffer, "GET /api/sensor") != NULL) {
            kirimDataSensorJSON(clientSocket);
        } else {
            kirim404(clientSocket);
        }
    }
    
    closesocket(clientSocket);
    return 0;
}

// Kirim halaman dashboard HTML
int kirimHalamanDashboard(SOCKET clientSocket) {
    char *htmlContent = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Connection: close\r\n\r\n"
        "<!DOCTYPE html>\n"
        "<html lang='id'>\n"
        "<head>\n"
        "    <meta charset='UTF-8'>\n"
        "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n"
        "    <title>Dashboard Monitoring Greenhouse</title>\n"
        "    <style>\n"
        "        body { font-family: Arial, sans-serif; margin: 0; padding: 20px; background-color: #f5f5f5; }\n"
        "        .header { background-color: #2c3e50; color: white; padding: 20px; border-radius: 10px; margin-bottom: 20px; }\n"
        "        .dashboard { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; }\n"
        "        .card { background: white; padding: 20px; border-radius: 10px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }\n"
        "        .sensor-value { font-size: 2em; font-weight: bold; color: #27ae60; }\n"
        "        .status-good { color: #27ae60; }\n"
        "        .status-warning { color: #f39c12; }\n"
        "        .status-danger { color: #e74c3c; }\n"
        "        .refresh-btn { background-color: #3498db; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; }\n"
        "    </style>\n"
        "</head>\n"
        "<body>\n"
        "    <div class='header'>\n"
        "        <h1>Dashboard Monitoring Greenhouse ITTS</h1>\n"
        "        <p>Real-time monitoring sistem greenhouse</p>\n"
        "    </div>\n"
        "    \n"
        "    <div class='dashboard'>\n"
        "        <div class='card'>\n"
        "            <h3>Suhu Lingkungan</h3>\n"
        "            <div class='sensor-value' id='suhu'>--°C</div>\n"
        "            <p>Status: <span id='status-suhu' class='status-good'>Normal</span></p>\n"
        "        </div>\n"
        "        \n"
        "        <div class='card'>\n"
        "            <h3>Kelembaban Udara</h3>\n"
        "            <div class='sensor-value' id='kelembaban'>--%</div>\n"
        "            <p>Status: <span id='status-kelembaban' class='status-good'>Normal</span></p>\n"
        "        </div>\n"
        "        \n"
        "        <div class='card'>\n"
        "            <h3>Kelembaban Tanah</h3>\n"
        "            <div class='sensor-value' id='kelembaban-tanah'>--%</div>\n"
        "            <p>Status: <span id='status-tanah' class='status-good'>Normal</span></p>\n"
        "        </div>\n"
        "        \n"
        "        <div class='card'>\n"
        "            <h3>Intensitas Cahaya</h3>\n"
        "            <div class='sensor-value' id='cahaya'>-- lux</div>\n"
        "            <p>Status: <span id='status-cahaya' class='status-good'>Normal</span></p>\n"
        "        </div>\n"
        "        \n"
        "        <div class='card'>\n"
        "            <h3>Kontrol</h3>\n"
        "            <button class='refresh-btn' onclick='refreshData()'>Refresh Data</button>\n"
        "            <button class='refresh-btn' onclick='exportData()'>Ekspor Data</button>\n"
        "        </div>\n"
        "    </div>\n"
        "    \n"
        "    <script>\n"
        "        function refreshData() {\n"
        "            fetch('/api/sensor')\n"
        "                .then(response => response.json())\n"
        "                .then(data => {\n"
        "                    document.getElementById('suhu').textContent = data.suhu + '°C';\n"
        "                    document.getElementById('kelembaban').textContent = data.kelembaban + '%';\n"
        "                    document.getElementById('kelembaban-tanah').textContent = data.kelembaban_tanah + '%';\n"
        "                    document.getElementById('cahaya').textContent = data.cahaya + ' lux';\n"
        "                    updateStatus(data);\n"
        "                })\n"
        "                .catch(error => console.error('Error:', error));\n"
        "        }\n"
        "        \n"
        "        function updateStatus(data) {\n"
        "            // Update status berdasarkan nilai sensor\n"
        "            updateElementStatus('status-suhu', data.suhu, 20, 30);\n"
        "            updateElementStatus('status-kelembaban', data.kelembaban, 60, 80);\n"
        "            updateElementStatus('status-tanah', data.kelembaban_tanah, 40, 70);\n"
        "            updateElementStatus('status-cahaya', data.cahaya, 500, 2000);\n"
        "        }\n"
        "        \n"
        "        function updateElementStatus(elementId, value, min, max) {\n"
        "            const element = document.getElementById(elementId);\n"
        "            if (value >= min && value <= max) {\n"
        "                element.textContent = 'Normal';\n"
        "                element.className = 'status-good';\n"
        "            } else if (value < min * 0.8 || value > max * 1.2) {\n"
        "                element.textContent = 'Bahaya';\n"
        "                element.className = 'status-danger';\n"
        "            } else {\n"
        "                element.textContent = 'Peringatan';\n"
        "                element.className = 'status-warning';\n"
        "            }\n"
        "        }\n"
        "        \n"
        "        function exportData() {\n"
        "            window.location.href = '/api/export';\n"
        "        }\n"
        "        \n"
        "        // Auto refresh setiap 30 detik\n"
        "        setInterval(refreshData, 30000);\n"
        "        \n"
        "        // Load data pertama kali\n"
        "        refreshData();\n"
        "    </script>\n"
        "</body>\n"
        "</html>";
    
    int bytesSent = send(clientSocket, htmlContent, strlen(htmlContent), 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("Send gagal: %d\n", WSAGetLastError());
        return 1;
    }
    
    return 0;
}

// Kirim data sensor dalam format JSON
int kirimDataSensorJSON(SOCKET clientSocket) {
    char jsonResponse[1024];
    time_t rawtime;
    struct tm * timeinfo;
    char timeString[80];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Simulasi data sensor (dalam implementasi nyata, baca dari sensor)
    float suhu = 25.5 + (rand() % 100) / 10.0;
    float kelembaban = 65.0 + (rand() % 200) / 10.0;
    float kelembabanTanah = 45.0 + (rand() % 300) / 10.0;
    float cahaya = 800.0 + (rand() % 1000);
    
    snprintf(jsonResponse, sizeof(jsonResponse),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Connection: close\r\n\r\n"
        "{\n"
        "  \"suhu\": %.1f,\n"
        "  \"kelembaban\": %.1f,\n"
        "  \"kelembaban_tanah\": %.1f,\n"
        "  \"cahaya\": %.0f,\n"
        "  \"waktu\": \"%s\",\n"
        "  \"status\": \"aktif\"\n"
        "}",
        suhu, kelembaban, kelembabanTanah, cahaya, timeString);
    
    int bytesSent = send(clientSocket, jsonResponse, strlen(jsonResponse), 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("Send gagal: %d\n", WSAGetLastError());
        return 1;
    }
    
    return 0;
}

// Kirim respon 404
int kirim404(SOCKET clientSocket) {
    char *response404 = 
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n"
        "<html><body><h1>404 - Halaman Tidak Ditemukan</h1></body></html>";
    
    send(clientSocket, response404, strlen(response404), 0);
    return 0;
}

// Cek status koneksi jaringan
int cekStatusKoneksi() {
    if (!jaringanTerinitialisasi) {
        return 0;
    }
    
    // Implementasi sederhana ping ke gateway lokal
    SOCKET testSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (testSocket == INVALID_SOCKET) {
        return 0;
    }
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = inet_addr("8.8.8.8"); // Google DNS
    
    int result = connect(testSocket, (struct sockaddr*)&addr, sizeof(addr));
    closesocket(testSocket);
    
    return (result != SOCKET_ERROR) ? 1 : 0;
}

// Loop utama server untuk menerima koneksi
void jalankanWebServer() {
    printf("Web server sedang berjalan...\n");
    printf("Tekan Ctrl+C untuk menghentikan server\n");
    
    while (1) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            printf("Accept gagal: %d\n", WSAGetLastError());
            continue;
        }
        
        // Buat thread baru untuk menangani client
        HANDLE threadHandle = CreateThread(NULL, 0, handleClient, &clientSocket, 0, NULL);
        if (threadHandle == NULL) {
            printf("Gagal membuat thread\n");
            closesocket(clientSocket);
        } else {
            CloseHandle(threadHandle);
        }
    }
}

// Tutup server dan cleanup
void tutupWebServer() {
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
        serverSocket = INVALID_SOCKET;
    }
    
    if (jaringanTerinitialisasi) {
        WSACleanup();
        jaringanTerinitialisasi = 0;
    }
    
    printf("Web server berhasil ditutup\n");
}
