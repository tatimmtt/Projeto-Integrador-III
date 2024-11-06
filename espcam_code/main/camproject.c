#include "esp_camera.h"
#include <WiFi.h>

// Definição do modelo da câmera e dos pinos
#define CAMERA_MODEL_AI_THINKER // Define o modelo de câmera OV2640
#define PWDN_GPIO_NUM     32    // Pino de controle de energia da câmera
#define RESET_GPIO_NUM    -1    // Pino de reset (não usado)
#define XCLK_GPIO_NUM      0    // Pino para o clock XCLK
#define SIOD_GPIO_NUM     26    // Pino de dados do barramento I2C
#define SIOC_GPIO_NUM     27    // Pino de clock do barramento I2C
#define Y9_GPIO_NUM       35    // Pinos de dados de imagem da câmera
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM    25    // Pino VSYNC para sincronização vertical
#define HREF_GPIO_NUM     23    // Pino HREF para sincronização horizontal
#define PCLK_GPIO_NUM     22    // Pino de clock para os dados da imagem

// Configurações de rede Wi-Fi
const char* ssid = "Mateus";       // SSID do Wi-Fi
const char* password = "Mf@t!nv702";  // Senha do Wi-Fi

// Função para configurar a câmera com as especificações de hardware
void setupCamera() {
    camera_config_t config;            // Cria estrutura de configuração da câmera
    config.ledc_channel = LEDC_CHANNEL_0;   // Canal LEDC para o clock da câmera
    config.ledc_timer = LEDC_TIMER_0;       // Temporizador LEDC para o clock
    config.pin_d0 = Y2_GPIO_NUM;            // Configuração dos pinos de dados
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;        // Pino do clock XCLK
    config.pin_pclk = PCLK_GPIO_NUM;        // Pino do clock dos pixels
    config.pin_vsync = VSYNC_GPIO_NUM;      // Pino de sincronização vertical
    config.pin_href = HREF_GPIO_NUM;        // Pino de sincronização horizontal
    config.pin_sscb_sda = SIOD_GPIO_NUM;    // Pino SDA do I2C para controle da câmera
    config.pin_sscb_scl = SIOC_GPIO_NUM;    // Pino SCL do I2C para controle da câmera
    config.pin_pwdn = PWDN_GPIO_NUM;        // Pino de energia da câmera
    config.pin_reset = RESET_GPIO_NUM;      // Pino de reset (não usado)
    config.xclk_freq_hz = 20000000;         // Frequência do clock XCLK (20 MHz)
    config.pixel_format = PIXFORMAT_JPEG;   // Formato de imagem JPEG

    // Configurações de frame e qualidade da imagem com base na presença de PSRAM
    if (psramFound()) {                     // Se houver PSRAM disponível
        config.frame_size = FRAMESIZE_UXGA; // Tamanho de frame UXGA (1600x1200)
        config.jpeg_quality = 10;           // Qualidade JPEG (1-63, sendo 1 a melhor qualidade)
        config.fb_count = 2;                // Buffer duplo para melhor desempenho
    } else {                                // Caso contrário, usa configuração mais leve
        config.frame_size = FRAMESIZE_SVGA; // Tamanho de frame SVGA (800x600)
        config.jpeg_quality = 12;           // Qualidade JPEG menor (reduz uso de memória)
        config.fb_count = 1;                // Um buffer de frame
    }

    // Inicializa a câmera com as configurações especificadas
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Erro ao inicializar a câmera: 0x%x", err); // Exibe erro se a inicialização falhar
        return;
    }
}

// Função para transmitir o vídeo ao vivo
void streamHandler() {
    WiFiClient client = server.client();     // Obtem o cliente conectado
    String responseHeader = "HTTP/1.1 200 OK\r\n";
    responseHeader += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    client.print(responseHeader);            // Envia cabeçalho HTTP para transmissão de imagem em partes

    while (client.connected()) {             // Enquanto o cliente estiver conectado
        camera_fb_t * fb = esp_camera_fb_get(); // Obtém um frame da câmera
        if (!fb) {                           // Verifica se o frame foi capturado
            Serial.println("Erro ao capturar imagem.");
            break;
        }

        // Envia a imagem capturada em formato JPEG para o cliente
        client.printf("--frame\r\n");
        client.printf("Content-Type: image/jpeg\r\n");
        client.printf("Content-Length: %d\r\n\r\n", fb->len);
        client.write(fb->buf, fb->len);      // Envia dados do buffer de imagem
        client.printf("\r\n");
        esp_camera_fb_return(fb);            // Libera o buffer de frame

        delay(100); // Controla a taxa de frames (ajuste conforme necessário)
    }
}

// Cria o servidor HTTP na porta 80
WiFiServer server(80);

void setup() {
    Serial.begin(115200);    // Inicializa a serial para monitoramento
    setupCamera();           // Chama a função para configurar a câmera

    // Conecta-se à rede Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {  // Espera a conexão
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Conectado ao WiFi! IP: ");
    Serial.println(WiFi.localIP());          // Exibe o IP do ESP32-CAM

    server.begin();                          // Inicia o servidor HTTP
}

void loop() {
    WiFiClient client = server.available();  // Verifica se há clientes conectados
    if (!client) {
        return;                              // Se não houver clientes, sai da função
    }

    String request = client.readStringUntil('\r'); // Lê a solicitação do cliente
    client.flush();                           // Limpa o buffer do cliente

    // Verifica se a solicitação é para a rota "/stream"
    if (request.indexOf("/stream") >= 0) {
        streamHandler();                      // Inicia a transmissão de vídeo ao vivo
    } else {
        // Envia uma resposta HTML básica para acessar a transmissão ao vivo
        String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        response += "<html><body><h1>ESP32-CAM Stream</h1>";
        response += "<img src=\"/stream\" style=\"width:100%; height:auto;\" />";
        response += "</body></html>";
        client.print(response);               // Envia a resposta HTML
    }

    delay(1);                                 // Aguarda um breve momento para evitar sobrecarga
}
