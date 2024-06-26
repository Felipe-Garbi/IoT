#  Limpeza de Painel Solar

<h2>Este projeto utiliza um ESP32 para monitorar o pôr do sol e acionar um servo motor para realizar uma tarefa de limpeza quando o pôr do sol ocorre. O ESP32 se conecta a uma rede WiFi, obtém dados meteorológicos de uma API, publica o status via MQTT e recebe comandos do Node-RED.</h2>

Tem como objetivo automatizar a tarefa de limpeza dos painéis com base no horário do pôr do sol.

## 🛠️ Componentes Utilizados

- **ESP32**: Microcontrolador com conectividade WiFi e Bluetooth. ([Link para o Wokwi](https://wokwi.com/projects/398893398687345665))
- **Servo Motor**: Motor que pode ser controlado para mover em ângulos específicos.
- **Conexão WiFi**: Para conectar à Internet e acessar a API e o broker MQTT.
- **Broker MQTT**: HiveMQ broker.hivemq.com para comunicação MQTT.
- **API OpenWeatherMap**: Para obter dados meteorológicos.
- **Node-RED**: Para processar e armazenar dados.

## 👥 Grupo

- Gabriel Rezende Rangel Santana - 10331989
- Rafael Pakalnis Paez - 10401462
- João Victor Silva - 10401977
- Felipe da Silva Morishita Garbi - 10401362
