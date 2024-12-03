import cv2
import numpy as np

# URL do stream RTSP
rtsp_url = "rtsp://mjxe:ha4t3k@192.168.15.7:554/"

# Caminhos para os arquivos do modelo
model_cfg = "model/yolov4.cfg"
model_weights = "model/yolov4.weights"
classes_file = "model/coco.names"

# Ler as classes
with open(classes_file, "r") as f:
    classes = [line.strip() for line in f.readlines()]

# Configurar a rede YOLO
net = cv2.dnn.readNetFromDarknet(model_cfg, model_weights)
net.setPreferableBackend(cv2.dnn.DNN_BACKEND_OPENCV)
net.setPreferableTarget(cv2.dnn.DNN_TARGET_CPU)

# Obter as camadas de saída do YOLO
layer_names = net.getLayerNames()
output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]

# Conectar ao stream RTSP
cap = cv2.VideoCapture(rtsp_url)
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)  # Manter apenas 1 frame no buffer

if not cap.isOpened():
    print("Erro: Não foi possível conectar ao stream RTSP.")
    exit()

frame_count = 0

while True:
    ret, frame = cap.read()
    if not ret:
        print("Erro ao receber frame. Tentando novamente...")
        continue

    # Reduzir resolução para aliviar processamento
    frame = cv2.resize(frame, (640, 480))
    height, width, channels = frame.shape

    # Processar a cada 5 frames
    frame_count += 1
    if frame_count % 5 != 0:
        cv2.imshow("RTSP Stream - Detecção de Mouse", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        continue

    # Criar o blob e fazer as previsões
    blob = cv2.dnn.blobFromImage(frame, 1/255.0, (320, 320), (0, 0, 0), swapRB=True, crop=False)
    net.setInput(blob)
    detections = net.forward(output_layers)

    # Processar as detecções
    mouse_detected = False
    for detection in detections:
        for obj in detection:
            scores = obj[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.5 and classes[class_id] == "mouse":
                mouse_detected = True
                center_x = int(obj[0] * width)
                center_y = int(obj[1] * height)
                w = int(obj[2] * width)
                h = int(obj[3] * height)
                x = int(center_x - w / 2)
                y = int(center_y - h / 2)
                # Desenhar a caixa ao redor do mouse detectado
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
                cv2.putText(frame, f"Mouse ({confidence:.2f})", (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    # Mensagem no console
    if mouse_detected:
        print("Mouse detectado no frame atual!")
    else:
        print("Nenhum mouse detectado no frame atual.")

    # Exibir o frame processado
    cv2.imshow("RTSP Stream - Detecção de Mouse", frame)

    # Encerrar com a tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
