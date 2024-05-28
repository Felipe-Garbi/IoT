# Limpeza de Painel Solar

<h2>Este projeto utiliza um ESP32 para monitorar o pôr do sol e acionar um servo motor para realizar uma tarefa de limpeza quando o pôr do sol ocorre. O ESP32 se conecta a uma rede WiFi, obtém dados meteorológicos de uma API, publica o status via MQTT e recebe comandos do Node-RED.</h2>

## 🛠️ Componentes Utilizados

- **ESP32**: Microcontrolador com conectividade WiFi e Bluetooth.
- **Servo Motor**: Motor que pode ser controlado para mover em ângulos específicos.
- **Conexão WiFi**: Para conectar à Internet e acessar a API e o broker MQTT.
- **Broker MQTT**: HiveMQ broker.hivemq.com para comunicação MQTT.
- **API OpenWeatherMap**: Para obter dados meteorológicos.
- **Node-RED**: Para processar e armazenar dados.
