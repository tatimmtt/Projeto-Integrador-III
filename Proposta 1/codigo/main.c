#include "esp_log.h"
#include "esp_http_server.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "ESP32-CAM" // Tag para facilitar o rastreamento dos logs no terminal

// Definições dos pinos usados pela câmera OV2640
#define CAM_PIN_PWDN   -1  // GPIO PWDN (não conectado em muitos módulos ESP32-CAM)
#define CAM_PIN_RESET  -1  // GPIO RESET (não conectado em muitos módulos ESP32-CAM)
#define CAM_PIN_XCLK    0  // Pino de clock externo
#define CAM_PIN_SIOD   26  // Pino I2C de dados
#define CAM_PIN_SIOC   27  // Pino I2C de clock
#define CAM_PIN_D7     35  // Dados D7
#define CAM_PIN_D6     34  // Dados D6
#define CAM_PIN_D5     39  // Dados D5
#define CAM_PIN_D4     36  // Dados D4
#define CAM_PIN_D3     21  // Dados D3
#define CAM_PIN_D2     19  // Dados D2
#define CAM_PIN_D1     18  // Dados D1
#define CAM_PIN_D0      5  // Dados D0
#define CAM_PIN_VSYNC  25  // Pino de sincronização vertical
#define CAM_PIN_HREF   23  // Pino de sincronização horizontal
#define CAM_PIN_PCLK   22  // Pino de clock de pixel

#define CAM_I2C_ADDRESS 0x30 // Endereço I2C do sensor OV2640

/**
 * Função para inicializar a câmera OV2640.
 */
static esp_err_t camera_init() {
    ESP_LOGI(TAG, "Inicializando pinos da câmera...");
    
    // Configuração dos pinos de controle como saída
    gpio_config_t io_conf = {
        .pin_bit_mask = ((1ULL << CAM_PIN_XCLK) | // XCLK
                         (1ULL << CAM_PIN_SIOD) | // SIOD (I2C Data)
                         (1ULL << CAM_PIN_SIOC)), // SIOC (I2C Clock)
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);

    // Se o pino PWDN (Power Down) estiver conectado, configure-o
    if (CAM_PIN_PWDN != -1) {
        gpio_set_direction(CAM_PIN_PWDN, GPIO_MODE_OUTPUT);
        gpio_set_level(CAM_PIN_PWDN, 0); // Desliga o modo Power Down
    }

    ESP_LOGI(TAG, "Inicializando I2C...");

    // Configuração da interface I2C para comunicação com o sensor OV2640
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,               // Configuração como mestre
        .sda_io_num = CAM_PIN_SIOD,           // Pino SDA
        .scl_io_num = CAM_PIN_SIOC,           // Pino SCL
        .sda_pullup_en = GPIO_PULLUP_ENABLE,  // Habilitar pull-up interno para SDA
        .scl_pullup_en = GPIO_PULLUP_ENABLE,  // Habilitar pull-up interno para SCL
        .master.clk_speed = 100000,           // Velocidade do barramento I2C (100 kHz)
    };
    i2c_param_config(I2C_NUM_0, &i2c_conf); // Configura os parâmetros I2C
    i2c_driver_install(I2C_NUM_0, i2c_conf.mode, 0, 0, 0); // Instala o driver I2C

    ESP_LOGI(TAG, "Inicialização da câmera concluída.");
    return ESP_OK;
}

/**
 * Manipulador HTTP para capturar a imagem da câmera.
 */
static esp_err_t http_handler_image(httpd_req_t *req) {
    ESP_LOGI(TAG, "Requisição de imagem recebida");

    // Aqui, futuramente, você capturará a imagem da câmera e retornará
    const char *response = "Imagem capturada com sucesso!";
    httpd_resp_send(req, response, strlen(response)); // Responde ao cliente
    return ESP_OK;
}

/**
 * Função para iniciar o servidor web.
 */
static httpd_handle_t start_webserver(void) {
    // Configurações padrão do servidor HTTP
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    ESP_LOGI(TAG, "Iniciando servidor HTTP...");
    // Inicia o servidor HTTP
    if (httpd_start(&server, &config) == ESP_OK) {
        // Configura um endpoint para a rota "/image"
        httpd_uri_t image_uri = {
            .uri       = "/image",        // Caminho da URL
            .method    = HTTP_GET,       // Método HTTP GET
            .handler   = http_handler_image, // Função que processará a requisição
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &image_uri); // Registra o manipulador
        return server;
    }
    ESP_LOGE(TAG, "Erro ao iniciar servidor HTTP!");
    return NULL;
}

/**
 * Função principal do aplicativo.
 */
void app_main(void) {
    ESP_LOGI(TAG, "Iniciando ESP32-CAM...");

    // Inicializa a câmera
    if (camera_init() == ESP_OK) {
        ESP_LOGI(TAG, "Câmera inicializada com sucesso.");
    } else {
        ESP_LOGE(TAG, "Falha ao inicializar a câmera!");
        return;
    }

    // Inicia o servidor HTTP
    start_webserver();
    ESP_LOGI(TAG, "Servidor HTTP ativo. Acesse '/image' para capturar imagens.");
}
