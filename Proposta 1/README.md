<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Proposta 1</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 0;
            background-color: #f9f9f9;
            color: #333;
        }
        header {
            background: #005f73;
            color: #fff;
            padding: 20px;
            text-align: center;
        }
        header h1 {
            margin: 0;
        }
        section {
            padding: 20px;
            max-width: 900px;
            margin: auto;
            background: #fff;
            margin-bottom: 20px;
            border-radius: 5px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }
        h1, h2, h3 {
            color: #005f73;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
            margin-bottom: 20px;
        }
        table th, table td {
            padding: 10px;
            border: 1px solid #ddd;
            text-align: left;
        }
        table th {
            background-color: #e0f4f4;
        }
        ul {
            padding-left: 20px;
        }
        ul li {
            margin-bottom: 10px;
        }
        a {
            color: #005f73;
            text-decoration: none;
            font-weight: bold;
        }
        a:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>
    <header>
        <h1>Proposta 1</h1>
    </header>
    <section>
        <h2>Introdução</h2>
        <p>A proposta consiste em utilizar um ESP32-CAM integrado a uma câmera OV2640, realizando a integração via cabo e requisitando a imagem por um servidor HTTP.</p>
    </section>
    <section>
        <h2>Escolha da Câmera</h2>
        <p>A escolha foi pautada pelos seguintes critérios:</p>
        <ul>
            <li>Capacidade de adquirir e transmitir o stream de vídeo;</li>
            <li>Dimensões reduzidas para facilitar sua integração em um robô;</li>
            <li>Documentação técnica disponível para facilitar implementação;</li>
            <li>Compatibilidade com processamento Python para análise de imagens.</li>
        </ul>
        <p>A análise considerou como o stream seria tratado para identificar objetos e estimar distâncias.</p>
    </section>
    <section>
        <h2>Comparação de Câmeras</h2>
        <table>
            <thead>
                <tr>
                    <th>Modelo</th>
                    <th>PSRAM</th>
                    <th>Tela</th>
                    <th>MicroSD</th>
                    <th>Microfone</th>
                    <th>Bateria</th>
                    <th>GPIOs</th>
                    <th>Sensor Movimento</th>
                    <th>Preço</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td>AI-THINKER</td>
                    <td>4MB</td>
                    <td>x</td>
                    <td>✓</td>
                    <td>x</td>
                    <td>x</td>
                    <td>10</td>
                    <td>x</td>
                    <td>R$70,00</td>
                </tr>
                <tr>
                    <td>FREENOVE WROVER</td>
                    <td>4MB</td>
                    <td>x</td>
                    <td>✓</td>
                    <td>x</td>
                    <td>✓</td>
                    <td>30</td>
                    <td>x</td>
                    <td>$110,00</td>
                </tr>
                <!-- Add more rows as needed -->
            </tbody>
        </table>
        <p>A AI-THINKER foi escolhida por sua relação custo-benefício, ampla documentação e compatibilidade técnica com o projeto.</p>
    </section>
    <section>
        <h2>Protocolo de Comunicação</h2>
        <p>A câmera utiliza os protocolos SCCB e DVP para controle e transmissão de dados:</p>
        <ul>
            <li><strong>SCCB:</strong> Configuração de resolução e parâmetros de imagem.</li>
            <li><strong>DVP:</strong> Transmissão digital de dados de imagem com sincronização via sinais VSYNC, HREF e PCLK.</li>
            <li><strong>API HTTP:</strong> Transmissão do stream para processamento Python, que aplica visão computacional para identificar e classificar objetos.</li>
        </ul>
    </section>
    <section>
        <h2>Detecção de Objetos</h2>
        <p>Usando a câmera OV2640, o projeto prevê o seguinte processo:</p>
        <ul>
            <li>Coletar imagens com a câmera;</li>
            <li>Rotular imagens com ferramentas como Edge Impulse;</li>
            <li>Treinar modelo de detecção de objetos;</li>
            <li>Integrar o modelo ao ESP32 para identificar objetos e classificá-los no stream.</li>
        </ul>
    </section>
    <section>
        <h2>Parâmetros da Câmera</h2>
        <h3>Resolução</h3>
        <ul>
            <li><strong>SVGA (800x600):</strong> Balanceia qualidade e processamento.</li>
            <li><strong>XGA (1024x768):</strong> Melhor para precisão em objetos pequenos ou em movimento.</li>
        </ul>
        <h3>Taxa de Quadro</h3>
        <ul>
            <li><strong>10 FPS:</strong> Adequado para objetos estáticos ou lentos.</li>
            <li><strong>15 FPS:</strong> Melhor para objetos em movimento moderado.</li>
        </ul>
    </section>
    <section>
        <h2>Testes e Conclusão</h2>
        <p>Após testes, foi identificada a fragilidade da câmera OV2640. O projeto será ajustado para incluir um hardware mais robusto. Veja mais detalhes na <a href="Proposta 2/README.md" download>Proposta 2</a>.</p>
    </section>
</body>
</html>
