
  <h1>Proposta 1</h1>
  <h1> Introdução</h1>
<p> A crescente demanda por sistemas autônomos e inteligentes tem impulsionado o desenvolvimento de soluções inovadoras baseadas em visão computacional. Nesse contexto, este projeto propõe a criação de um sistema de detecção e identificação de objetos utilizando o microcontrolador ESP32-CAM. Esse módulo, equipado com uma câmera OV2640, será capaz de capturar imagens do ambiente, processá-las em tempo real e identificar a presença de objetos, categorizando-os em diferentes distâncias (perto, médio e longe).

A escolha do ESP32-CAM justifica-se por suas características técnicas que o tornam adequado para aplicações de IoT (Internet das Coisas). Essas características incluem a integração de sensores, conectividade Wi-Fi e capacidade de processamento de dados. A câmera integrada oferece aquisição de imagens em alta resolução, possibilitando a extração de informações relevantes para a detecção e classificação de objetos.
  </p>
<h1>Objetivos</h1>
  <ul>
  <li>Desenvolver um sistema de visão computacional baseado no ESP32-CAM, capaz de detectar e identificar objetos em ambientes controlados.
  capaz de detectar e identificar objetos em um ambiente controlado;</li>
  <li>Classificar os objetos detectados em categorias de distância,
   utilizando técnicas de aprendizado de máquina.</li>
  <li>Implementar algoritmos de processamento de imagem para 
  extrair características do objeto;</li >
  <li>Transmitir os dados coletados para um sistema externo, 
  possibilitando a análise e o controle de processos;</li>
  <li>Minimizar os custos do projeto, priorizando soluções acessíveis e viáveis.</li>
  </ul>
  <p>A primeira proposta foi desenhada de acordo com as informações no início do projeto, a proposta consiste em utilizar um esp32-cam integrado a uma cÂmera ov2640 realizando a integração por cabo e requisitando a imagem por um server http</p>


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
    <a href="documentos/OV2640DS.pdf" download>Datasheet OV2640</a>
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
     Para realizar a detecção de objetos usando uma câmera OV2640 e um ESP32 com um banco de dados de imagens, iremos treinar um modelo de detecção de objetos rotulados (utilizando ferramentas como o EDGE IMPULSE) e, em seguida, usaremos esse modelo no ESP32 utilizando uma biblioteca apropriada. O passo a passo que pretendemos seguir está explicado abaixo
       </p>
     <ul>
     <li> Coleta de dados: Capture imagens de objetos usando a OV2640.</li>
     <li>Rotular as Imagens: Definir qual seria o nome de cada objeto</li>
     <li>Treinamento do modelo: Faremos o upload desses imagem em uma plataforma para treinar um modelo baseado nas imagens rotuladas.</li>
     <li>Utilizar o modelo  ESP32: Carregue o modelo treinado no ESP32 e após isso quando a câmera estiver streamando a imagem O ESP32 conseguirá identificar que há um objeto no campo de visão da câmera e o que seria esse objeto.</li>
     </ul>
    <h1>Diagrama de blocos</h1>
    <img src= "imagens/proposta-1-ov2640.jpg" alt = "aruitetura">
    <h1>Entrega 2</h1>
    <h2>Escolha de uma biblioteca adequada para a comunicação entre a câmera e o ESP32-CAM</h2>
    <h3>esp_camera.h</h3>
    <p>
     A escolha da biblioteca esp_camera.h para este projeto se fundamenta na necessidade de configurar e controlar a câmera do módulo ESP32-CAM de maneira eficiente e prática. Abaixo estão descritos os principais motivos que justificam sua utilização:
  <ul>
    <li><b>Interface Direta com o Sensor de Imagem:</b>A biblioteca esp_camera.h oferece uma interface direta com o sensor OV2640, amplamente utilizado no módulo ESP32-CAM. Com ela, é possível configurar parâmetros como resolução, brilho, contraste e saturação da imagem, elementos essenciais para capturar fotos e vídeos com qualidade ajustada às necessidades do projeto. Além de diminuir a complexidade do projeto uma vez que reduz significativamente o esforço de programação ao abstrair a complexidade da comunicação direta com o sensor OV2640. Sem essa biblioteca, o desenvolvedor precisaria programar toda a interface de comunicação com o sensor, o que demandaria maior conhecimento técnico e aumentaria o tempo de desenvolvimento.</li>
    <li><b>Facilidade de Configuração:</b> Essa biblioteca permite configurar a câmera de maneira simplificada por meio de uma estrutura de dados (camera_config_t). Nessa estrutura, são definidos os pinos de conexão, a resolução e o formato da imagem, entre outros parâmetros. Sem o uso da esp_camera.h, seria necessário um código significativamente mais complexo para ajustar todos esses aspectos manualmente.</li>
    <li><b>Captura de Imagens Otimizada:</b> A esp_camera.h possui funções específicas para capturar imagens e gerenciar o formato dos dados, como JPEG ou RGB565, o que facilita a adaptação da imagem capturada para diferentes tipos de uso no projeto. A função esp_camera_fb_get() possibilita a obtenção do frame buffer da câmera (ou seja, o conteúdo da imagem), de forma otimizada para processamento em tempo real, essencial para aplicações de monitoramento e visão computacional. </li >
    <li><b>Eficiência em Memória e Processamento:</b> A biblioteca foi desenvolvida com foco na arquitetura do ESP32, que possui limitações de memória e processamento. Assim, o uso da esp_camera.h permite capturar e manipular imagens sem comprometer a estabilidade e o desempenho do sistema, otimizando o uso dos recursos disponíveis.</li>
    <li><b>Integração com Funcionalidades do ESP32:</b>Além da captura de imagens, a esp_camera.h facilita a integração com outras funcionalidades do ESP32, como o Wi-Fi, permitindo enviar as imagens capturadas por protocolos HTTP ou por streaming.</li>
   <li> </li>
    </ul>
  
  </p>
  <h2>Definições das configurações e parâmetros da câmera</h2>
  <h3>Resolução</h3>
  <p>
   Em testes com a câmera foi analisado que a resolução pode ser SVGA(800x600) ou XVGA(1024x768) sendo que:
   <ul>
    <li>SVGA (800x600): Fornece detalhes suficientes para detectar objetos de tamanho médio a curta e média distância, enquanto mantém um equilíbrio entre qualidade e tempo de processamento.</li>
    <li>XGA (1024x768): Adequado para uma melhor precisão na detecção de objetos e estimativas de distância, especialmente se o ESP32-CAM estiver monitorando alvos em movimento ou objetos pequenos.
  Essas resoluções proporcionam o detalhamento necessário sem comprometer significativamente a taxa de processamento e a capacidade de transmissão de dados.</li>
   </ul>
  
  </p>
  <h2> Taxa de Quadro (FPS)</h2>
  <p>
   Em testes com a câmera foi a considerado as taxas de quadro 15FPS e 10 FPS as melhores de rendimento, considerando a requisição http:
  
  <ul>
   <li>10 FPS: Para aplicações onde os objetos se movem lentamente ou são estáticos, como detecção de forma e posição.</li>
   <li>15 FPS: Para objetos em movimento moderado ou rápido, permitindo um monitoramento mais dinâmico e precisão na estimativa de distância.</li>
  </ul>
  </p>
  <h2> Implementação do código para capturar as imagens da câmera em tempo real</h2>
   <a href="codigo/main.c" download>Código captura das imagens OV2640</a>
   <h2>Testes e conclusão</h2>
   <p>Os testes demonstraram que a câmera OV2640, apesar de ser compacta, apresentou fragilidades no hardware após uma semana de uso, estragou. Isso levou à necessidade de reconsiderar o hardware utilizado no projeto, optando por um modelo mais robusto para garantir a confiabilidade do sistema.

A continuação deste trabalho, incluindo a adaptação para um novo hardware, pode ser consultada na proposta 2 no: <a href="../Proposta 2/README.md"> Link</a>, onde abordamos as mudanças realizadas para melhorar a solução e alcançar os objetivos do projeto. </p>
  