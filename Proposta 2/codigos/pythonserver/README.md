<h1>Explicação do código</h1>
<p>Importações</p>
<code>
import cv2

import numpy as np

</code>
<ul>
<li>cv2: Biblioteca OpenCV, usada para manipulação de imagens, vídeos e integração com redes neurais.</li>
<li>numpy: Usada para manipulação de arrays, necessária para o processamento de detecções do YOLO.</li>
</ul>
<p>Configuração de URL do RTSP</p>
<code>
rtsp_url = "rtsp://mjxe:ha4t3k@192.168.15.7:554/"
</code>
<ul>
<li>Define a URL do stream RTSP. Este é o endereço da câmera IP onde o vídeo será capturado.</li>
</ul>
<p>Caminhos para os arquivos do modelo</p>
<code>
model_cfg = "model/yolov4.cfg"
model_weights = "model/yolov4.weights"
classes_file = "model/coco.names"
</code>
<ul>
<li>Define os caminhos para os arquivos de configuração (.cfg), pesos do modelo (.weights) e lista de classes (.names).</li>
</ul>
<p>Caminhos para os arquivos do modelo</p>
<code>
model_cfg = "model/yolov4.cfg"
model_weights = "model/yolov4.weights"
classes_file = "model/coco.names"
</code>
<ul>
<li>Define os caminhos para os arquivos de configuração (.cfg), pesos do modelo (.weights) e lista de classes (.names).</li>
</ul>


