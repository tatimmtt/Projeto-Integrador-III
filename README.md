# Projeto-Integrador-III
Este projeto visa implementar um sistema de detecção de obstáculos utilizando um módulo ESP32-S3 com câmera integrada. A câmera capturará imagens do ambiente e identificará a presença de obstáculos. Paraêmtros de distância de obstáculos serão detectados e transmitidas para um microcontrolador ESP32-S3 para que tomada de ações.  
<h1> Introdução</h1>
<p> A crescente demanda por sistemas autônomos e inteligentes impulsiona o desenvolvimento de soluções inovadoras baseadas em visão computacional. Neste contexto, o presente projeto propõe a implementação de um sistema de detecção e identificação de objetos utilizando um microcontrolador ESP32-CAM. A plataforma, equipada com uma câmera ov2640, será capaz de capturar imagens do ambiente, processá-las em tempo real e identificar a presença de objetos, classificando-os em categorias de distância (perto, médio e longe).

A escolha do ESP32-CAM se justifica por suas características técnicas que o tornam ideal para aplicações de IoT, como a integração de sensores, conectividade Wi-Fi e processamento de dados. A câmera integrada, por sua vez, possibilita a aquisição de imagens em alta resolução, permitindo a extração de informações relevantes para a detecção e classificação de objetos. </p>
<h1>Objetivos</h1>
  <ul>
  <li>Desenvolver um sistema de visão computacional baseado em ESP32-CAM capaz de detectar e identificar objetos em um ambiente controlado;</li>
  <li>Classificar os objetos detectados em categorias de distância, utilizando técnicas de aprendizado de máquina.</li>
  <li>Implementar algoritmos de processamento de imagem para extrair características do objeto;</li >
  <li>Transmitir os dados coletados para um sistema externo, possibilitando a análise e o controle de processos;</li>
  </ul>
  <h1>Escolha da câmera</h1>
  <p>Requisitos para escolhar da camera:
  <ul>
  <li>Deve ser possível adquirir o stream de vídeo;</li>
  <li>A câmera deve ser pequena para que seja possível aclopar no robo, posteriormente</li>
  <li>Deve ter documentação disponível para acesso, de como adquirir o stream de vídeo</li>
  <li>Deve ser possível após adquirir o stream de vídeo, coletar as informações para o código em python gerar a visão computacional em cima da imagem capturada.</li>
  </ul>
  </p>
  <p>A escolha da câmera leva em consideração de que forma o stream de vídeo será adquirido, e como a imagem será tratada com visão computacional para realizar a identificação de objetos e identificar parâmetros de distância as opções que foram levadas em consideração foram
  <ul>
  <li>Câmera ip convencional: para realizar a integração com uma câmera ip tradicional é necessário ter conhecimento da api, a documentação deve estar disponível e a câmera deve ser leve e pequena de uma forma que seja possível aclopar ao robo em futuros projetos</li>
  </ul>
  </p>
  <h2>Comparação de câmeras</h2>
  <table>
  <tr><th>Modelo da câmera</th>
  <td>AI-THINKER</td>
  <td>FREENOVE WROVER</td>
  <td>ESP-EYE</td>
  <td>M5-CAMERA A/B</td>
  <td>TTGO T-Plus</td>
  <td>TTGO T-Camera</td>
  <td>T-Journal</td>
<td>M5 ESP32-Camera</td>
</tr>
  <tr>
  <th>PSRAM</th>
  <td>4MB</td>
  <td>4MB</td>
  <td>8MB</td>
  <td>4MB</td>
  <td>8MB</td>
  <td>8MB</td>
  <td>x</td>
  <td>x</td>
  </tr>
  <tr>
  <th>Screen</th>
  <td>x</td>
  <td>x</td>
  <td>x</td>
  <td>x</td>
  <td>1.3inch TFT display (ST7789)</td>
  <td>0.96inch SSD1306 OLED</td>
  <td>0.91inch SSD1306 OLED</td>
  <td>x</td>
  </tr>
  <tr>
  <th>MicroSD Card</th>
  <td>✓</td>
  <td>✓</td>
  <td>x</td>
  <td>x</td>
  <td>✓</td>
  <td>x</td>
  <td>x</td>
  <td>x</td>
  </tr>
  <th>Microphone</th>
    <td>x</td>
    <td>x</td>
    <td>✓</td>
    <td>✓ (add-on)</td>
    <td>✓</td>
    <td>x</td>
    <td>x</td>
    <td>✓ (add-on)</td>
  </tr>
  <tr>
    <th>Function button</th>
    <td>x</td>
    <td>x</td>
    <td>✓</td>
    <td>x</td>
    <td>x</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
  </tr>
  <tr>
    <th>Battery Connector</th>
    <td>x</td>
    <td>x</td>
    <td>x</td>
    <td>x</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
  </tr>
  <tr>
    <th>Built-in programmer</th>
    <td>x</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
  </tr>
  <tr>
    <th>GPIOs</th>
    <td>10</td>
    <td>30</td>
    <td>x</td>
    <td>x</td>
    <td>2</td>
    <td>x</td>
    <td>4</td>
    <td>x</td>
  </tr>
  <tr>
    <th>Motion sensor</th>
    <td>x</td>
    <td>x</td>
    <td>x</td>
    <td>x</td>
    <td>x</td>
    <td>✓</td>
    <td>x</td>
    <td>x</td>
  </tr>
  <tr>
    <th>Grove connector</th>
    <td>x</td>
    <td>x</td>
    <td>x</td>
    <td>✓</td>
    <td>✓</td>
    <td>✓</td>
    <td>x</td>
    <td>✓</td>
  </tr>
  </table>
  <h2>Documentação da câmera escolhida</h2>
  <h1>Definição do ambiente controlado</h1>
  <h1>Definição dos objetos</h1>
  <h1>Parâmetros de distância</h1>
  <h1>Modelo computacional</h1>
  <h1>Diagram de blocos</h1>
  