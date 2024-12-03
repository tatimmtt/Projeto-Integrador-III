<h1>Explicação do código</h1>
<p>Importações</p>
<pre>
<code>
import cv2
import numpy as np
</code>
</pre>
<ul>
<li>cv2: Biblioteca OpenCV, usada para manipulação de imagens, vídeos e integração com redes neurais.</li>
<li>numpy: Usada para manipulação de arrays, necessária para o processamento de detecções do YOLO.</li>
</ul>
<p>Configuração de URL do RTSP</p>
<pre>
<code>
rtsp_url = "rtsp://mjxe:ha4t3k@192.168.15.7:554/"
</code>
</pre>
<ul>
<li>Define a URL do stream RTSP. Este é o endereço da câmera IP onde o vídeo será capturado.</li>
</ul>
<p>Caminhos para os arquivos do modelo</p>
<pre>
<code>
model_cfg = "model/yolov4.cfg"
model_weights = "model/yolov4.weights"
classes_file = "model/coco.names"
</code>
</pre>
<ul>
<li>Define os caminhos para os arquivos de configuração (.cfg), pesos do modelo (.weights) e lista de classes (.names).</li>
</ul>
<p>Leitura das classes</p>
<pre>
<code>
with open(classes_file, "r") as f:
classes = [line.strip() for line in f.readlines()]
</code>
</pre>
<ul>
<li>Abre o arquivo de classes e lê cada linha. O resultado é uma lista de nomes de classes (e.g., "mouse", "car", etc.).</li>
</ul>
<p>Configuração do YOLO</p>
<pre>
<code>
net = cv2.dnn.readNetFromDarknet(model_cfg, model_weights)
net.setPreferableBackend(cv2.dnn.DNN_BACKEND_OPENCV)
net.setPreferableTarget(cv2.dnn.DNN_TARGET_CPU)
</code>
</pre>
<ul>
<li>readNetFromDarknet: Carrega a arquitetura e os pesos do modelo YOLO.</li>
<li>setPreferableBackend e setPreferableTarget: Configuram o backend e o hardware. Aqui, o processamento é configurado para usar a CPU.</li>
</ul>
<p>Camadas de saída do YOLO</p>
<pre>
<code>
layer_names = net.getLayerNames()
output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]
</code>
</pre>
<ul>
<li>getLayerNames: Obtém os nomes de todas as camadas da rede.</li>
<li>getUnconnectedOutLayers: Identifica as camadas de saída, essenciais para obter as detecções.</li>
</ul>
<p>Conexão ao RTSP</p>
<pre>
<code>
cap = cv2.VideoCapture(rtsp_url)
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)
</code>
</pre>
<ul>
<li>VideoCapture: Abre o stream RTSP.</li>
<li>CAP_PROP_BUFFERSIZE: Limita o buffer a um único quadro, reduzindo atrasos no vídeo.</li>
</ul>
<p>Checagem de Conexão</p>
<pre>
<code>
if not cap.isOpened():
    print("Erro: Não foi possível conectar ao stream RTSP.")
    exit()
</code>
</pre>
<ul>
<li>Verifica se a conexão foi estabelecida. Caso contrário, encerra o programa.</li>
</ul>
<p>Loop principal</p>
<pre>
<code>
frame_count = 0
</code>
</pre>
<ul>
<li>Inicializa um contador de quadros para processar apenas quadros específicos.</li>
</ul>
<pre>
<code>
while True:
    ret, frame = cap.read()
    if not ret:
        print("Erro ao receber frame. Tentando novamente...")
        continue
</code>
</pre>
<ul>
<li>cap.read: Captura um quadro do stream RTSP.</li>
<li>Verifica se o quadro foi recebido. Em caso de falha, tenta novamente.</li>
</ul>
<p>Redução de Resolução:</p>
<pre>
<code>
frame = cv2.resize(frame, (640, 480))

height, width, channels = frame.shape
</code>
</pre>
<ul>
<li>Redimensiona o quadro para 640x480 pixels, reduzindo a carga de processamento.</li>
<li>Obtém as dimensões do quadro para cálculos posteriores.</li>
</ul>
<p>Processamento de Quadros Específicos: </p>
<pre>
<code>
frame_count += 1
if frame_count % 5 != 0:
    cv2.imshow("RTSP Stream - Detecção de Mouse", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    continue
</code>
</pre>
<ul>
<li>Processa apenas a cada 5 quadros, aliviando o processamento. Exibe os quadros intermediários.</li>
</ul>
<p>Criar o Blob e Fazer Previsões: </p>
<pre>
<code>
blob = cv2.dnn.blobFromImage(frame, 1/255.0, (320, 320), (0, 0, 0), swapRB=True, crop=False)
net.setInput(blob)
detections = net.forward(output_layers)
</code>
</pre>
<ul>
<li>blobFromImage: Prepara o quadro para entrada no YOLO, normalizando os valores (1/255), ajustando o tamanho (320x320) e trocando canais (RGB para BGR).</li>
<li>net.forward: Faz as detecções usando o modelo.</li>
</ul>
<p>Processamento das Detecções: </p>
<pre>
<code>
mouse_detected = False
for detection in detections:
    for obj in detection:
        scores = obj[5:]
        class_id = np.argmax(scores)
        confidence = scores[class_id]
        if confidence > 0.5 and classes[class_id] == "mouse":

</code>
</pre>
<ul>
<li>detection: Analisa cada saída.</li>
<li>scores: Pega as pontuações de cada classe.</li>
<li>confidence: Verifica a confiança da detecção.</li>
<li>Filtra as detecções com confiança acima de 50% e verifica se a classe detectada é "mouse".</li>
</ul>
<p>Cálculos e Desenho da Caixa </p>
<pre>
<code>
center_x = int(obj[0] * width)
center_y = int(obj[1] * height)
w = int(obj[2] * width)
h = int(obj[3] * height)
x = int(center_x - w / 2)
y = int(center_y - h / 2)
cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
cv2.putText(frame, f"Mouse ({confidence:.2f})", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
</code>
</pre>
<ul>
<li>Calcula as coordenadas da caixa delimitadora e a desenha no quadro.</li>
<li>Exibe o rótulo e a confiança da detecção.</li>
</ul>
<p>Mensagens no Console </p>
<pre>
<code>
if mouse_detected:
    print("Mouse detectado no frame atual!")
else:
    print("Nenhum mouse detectado no frame atual.")
</code>
</pre>
<ul>
<li>Imprime mensagens indicando se um "mouse" foi detectado no quadro.</li>
</ul>
<p>Exibir o Quadro e Encerrar </p>
<pre>
<code>
cv2.imshow("RTSP Stream - Detecção de Mouse", frame)
if cv2.waitKey(1) & 0xFF == ord('q'):
    break
cap.release()
cv2.destroyAllWindows()

</code>
</pre>
<ul>
<li>Exibe o quadro processado em uma janela.</li>
<li>Encerra o programa ao pressionar 'q' e libera os recursos.</li>
</ul>



