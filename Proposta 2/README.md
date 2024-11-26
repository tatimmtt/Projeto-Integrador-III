
  <h1>Entrega 3</h1>
  <h2> Mudança de escopo </h2>
  <p>Após testes, foi identificado que a câmera OV2640 apresentou problemas de fragilidade, sendo necessário redefinir a arquitetura do projeto. Optou-se por utilizar a câmera Speed Dome iCSee, caracterizada por sua robustez (IP67 e IK10), garantindo maior durabilidade e facilidade de implementação.</p>
  <h2>Nova arquitetura</h2>
  <img src= "imagens/2pi3arquitetura-diagram.drawio.png" alt = "aruitetura">
  <h2>Diagrama de tempo</h2>

  <p>Descrição Detalhada do Fluxo de Processamento

Etapa 1: Captura de Vídeo pela Câmera
Evento: A câmera inicia a captura de vídeo.
Ação: Os frames capturados são enviados ao servidor utilizando o protocolo RTSP.


Etapa 2: Processamento no Servidor
Recepção dos Dados:

O servidor recebe os frames transmitidos pela câmera via RTSP.
Este processo inicia no momento em que o frame é transmitido.

Processamento dos Frames: 
O servidor, utilizando a biblioteca OpenCV, processa o vídeo para:
Identificar objetos relevantes no frame.
Calcular a distância dos objetos identificados.

Etapa 3: Envio do Parâmetro ao ESP32: 
O servidor transmite o parâmetro de distância calculado para o ESP32 via protocolo HTTP.

Recepção do Parâmetro:
O ESP32 recebe o parâmetro enviado pelo servidor e realiza uma ação com base no que foi recebido.


O ESP32 executa uma ação baseada no parâmetro de distância recebido, por exemplo:
Atuar em um motor (ex: ajustar posição).
Ligar um LED indicador.
Transmitir dados para outro sistema.

 <table>
        <thead>
            <tr>
                <th>Etapa</th>
                <th>Descrição</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>Captura e envio (Câmera)</td>
                <td>Enviar frames via RTSP</td>
            </tr>
            <tr>
                <td>Recepção (Servidor)</td>
                <td>Receber dados RTSP</td>
            </tr>
            <tr>
                <td>Processamento (Servidor)</td>
                <td>Análise e cálculo de distâncias</td>
            </tr>
            <tr>
                <td>Envio ao ESP32</td>
                <td>Transmitir parâmetros</td>
            </tr>
            <tr>
                <td>Recepção (ESP32)</td>
                <td>Receber parâmetro</td>
            </tr>
            <tr>
                <td>Execução (ESP32)</td>
                <td>Ação com base nos dados</td>
            </tr>
        </tbody>
    </table>

Segue a imagem do diagrama de tempo:</p>

  <img src = "imagens/diagrama-tempo-pi3.drawio.png" alt = "Diagrama de tempo">

  <h2>Código para requisitar a imagem da câmera</h2>
  <p></p>
  <h2>Código opencv para identificar objetos e calcular a distância</h2>
