# Projeto-Integrador-III
Este projeto visa implementar um sistema de detecção de obstáculos 
utilizando um módulo ESP32-S3 com câmera integrada. 
A câmera capturará imagens do ambiente e identificará a presença de 
obstáculos. Paraêmtros de distância de obstáculos serão detectados e 
transmitidas para um microcontrolador ESP32-S3 para que tomada de ações.  
<h1> Introdução</h1>
<p> A crescente demanda por sistemas autônomos e inteligentes impulsiona 
o desenvolvimento de soluções inovadoras baseadas em visão computacional. 
Neste contexto, o presente projeto propõe a implementação de um sistema de
 detecção e identificação de objetos utilizando um microcontrolador
  ESP32-CAM. A plataforma, equipada com uma câmera ov2640, será capaz
   de capturar imagens do ambiente, processá-las em tempo real e 
   identificar a presença de objetos, classificando-os em categorias
    de distância (perto, médio e longe).

A escolha do ESP32-CAM se justifica por suas características técnicas 
que o tornam ideal para aplicações de IoT, como a integração de sensores, 
conectividade Wi-Fi e processamento de dados. A câmera integrada, por sua 
vez, possibilita a aquisição de imagens em alta resolução, permitindo a
 extração de informações relevantes para a detecção e classificação de
  objetos. 
  </p>
<h1>Objetivos</h1>
  <ul>
  <li>Desenvolver um sistema de visão computacional baseado em ESP32-CAM 
  capaz de detectar e identificar objetos em um ambiente controlado;</li>
  <li>Classificar os objetos detectados em categorias de distância,
   utilizando técnicas de aprendizado de máquina.</li>
  <li>Implementar algoritmos de processamento de imagem para 
  extrair características do objeto;</li >
  <li>Transmitir os dados coletados para um sistema externo, 
  possibilitando a análise e o controle de processos;</li>
  <li>O custo deve ser levado em consideração</li>
  </ul>
  <h1>Escolha da câmera</h1>
  <p>A escolha da câmera foi pautada pelos seguintes critérios:
  <ul>
  <li>Capacidade de adquirir e transmitir o stream de vídeo;</li>
  <li>Dimensões reduzidas para facilitar sua integração futura em um robô;</li>
  <li>Disponibilidade de documentação técnica para facilitar a implementação do 
  stream de vídeo;</li>
  <li>Compatibilidade com o processamento em Python
   para análise de imagens e geração de visão computacional.</li>
  </ul>
  </p>
  <p>
A seleção levou em conta a maneira como o stream de vídeo seria
 adquirido e como a imagem seria tratada para realizar a 
 identificação de objetos e estimar distâncias. 
Foram analisadas diversas opções de câmeras compatíveis com o ESP32-CAM.
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
  <th>Tela</th>
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
  <th>Microfone</th>
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
    <th>Conector de bateria<td>x</td>
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
    <th>Sensor de movimento</th>
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
    <th>Preço</th>
    <td>R$70,00</td>
    <td>$110,00</td>
    <td>R$279,53</td>
    <td>R$127,29</td>
    <td>R$195,98</td>
    <td>R$177,96</td>
    <td>R$139,68</td>
    <td>R$ 93,93</td>
  </tr>
  </table>
  <p>Após análise, conclui-se que os modelos AI-THINKER e 
  FREENOVE WROVER oferecem a melhor relação custo-benefício, 
  além de contar com extensa documentação e suporte técnico, 
  facilitando sua integração ao projeto. 
  Considerando o maior número de projetos já desenvolvidos com a AI-THINKER
   e sua compatibilidade técnica, este módulo foi escolhido para o projeto.
    O modelo AI-THINKER inclui a câmera OV2640. </p>

  <h2>Documentação da câmera escolhida</h2>
  <a href="OV2640DS.pdf" download>Baixar Datasheet da OV2640</a>
  <h2>Protocolo de comunicação</h2>
  <p>
  A câmera utiliza principalmente dois protocolos para sua comunicação com o ESP32: o Serial Camera Control Bus (SCCB) e o Digital Video Port (DVP) e será utilizado o protocolo HTTP para requisição de stream de vídeo para o código python:
  </p>  
  <ul>
  <li> SCCB: É um protocolo proprietário da OmnVision. É o principal protocolo de controle da câmera. Ele é usado para configurar os parâmetros de resolução, formato da imagem e outros ajustes. 
  </li>
   <li> DVP: Essa interface é usada para transmitir os dados de imagem capturados pela câmera em forma de fluxo digital. O VDP utiliza um conjunto de pinos para transmitir os dados, incluindo:</li>
   <ul>
   <li>VSYNC (Vertical Sync): indica o início de um novo frame de imagem.</li>
     <li>HREF (Horizontal Reference): marca a linha ativa da imagem.</li>
     <li>PCLK (Pixel Clock): sincroniza a leitura dos dados de cada pixel.</li>
     <li>D0-D7 (Barramento de dados): carrega os bits de dados do pixel.</li>
   </ul>
   <li>API HTTP: O protocolo HTTP será utilizado para realizar a requisição do stream de vídeo, que será processado no código Python. Após a recepção do stream, o código realizará o tratamento da imagem, aplicando técnicas de visão computacional para identificar objetos e estimar a distância, classificando-os como próximos, médios ou distantes. </li>
  </ul>
  </p>
  <h1>Detecção de objetos</h1>
  <p>
   Para realizar a detecção de objetos usando uma câmera OV2640 e um ESP32 com um banco de dados de imagens, iremos treinar um modelo de detecção de objetos rotulados (utilizando ferramentas como o EDGE IMPULSE) e, em seguida, usaremos esse modelo no ESP32 utilizando uma biblioteca apropriada.	O passo a passo que pretendemos seguir está explicado abaixo
Coleta de dados: Capture imagens de objetos usando a OV2640.
Rotular as Imagens: Definir qual seria o nome de cada objeto
Treinamento do modelo: Faremos o upload desses imagem em uma plataforma para treinar um modelo baseado nas imagens rotuladas.
Utilizar o modelo  ESP32: Carregue o modelo treinado no ESP32 e após isso quando a câmera estiver streamando a imagem O ESP32 conseguirá identificar que há um objeto no campo de visão da câmera e o que seria esse objeto.![image](https://github.com/user-attachments/assets/353da1e9-3ca0-4549-967a-77a53a07c50c)

  </p>
  <h1>Definição dos objetos</h1>
  <h1>Parâmetros de distância</h1>
  <h1>Modelo computacional</h1>
  <h1>Diagram de blocos</h1>
  
