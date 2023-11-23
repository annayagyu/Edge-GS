Problema e solução:  

O problema que o VitaKids pretende resolver é a dificuldade que pais e cuidadores de bebês e crianças têm em monitorar a saúde de seus filhos de forma fácil e conveniente, sem a necessidade de precisar usar vários medidores e sensores, que muitas vezes incomoda a criança e causa estresse desnecessário para ambas as partes. O VitaKids fornece informações essenciais sobre a saúde da criança, tais como temperatura, batimentos cardíacos, níveis de açúcar no sangue, percentagem de gordura corporal (IMC), então pode ajudar a identificar problemas de saúde precocemente, antes que eles se agravem, evitando assim mortes de recém-nascidos e crianças menores de 5 anos, com metas específicas de mortalidade neonatal e infantil. (Meta 3.2 da ONU) 

 A ferramenta permite que os pais e responsáveis monitorem a saúde de seus filhos de forma remota, a qualquer hora e em qualquer lugar. Isso pode proporcionar aos pais e responsáveis maior tranquilidade e segurança, pois eles poderão acompanhar o desenvolvimento e a saúde de seus filhos de forma mais próxima e automática O Vitakids é um produto inovador que oferece uma solução completa para o monitoramento remoto da saúde de bebês e crianças. O Vitakids é portátil, seguro, preciso, pequeno, confortavel e as medições são exibidas em tempo real no aplicativo. Além disso, o Vitakids pode ajudar a detectar precocemente problemas de saúde, o que pode ajudar a prevenir complicações. 

 Em linhas gerais, o problema é a dificuldade de monitorar a saúde de bebês e crianças de forma calma e prática. A proposta de solução do Vitakids é oferecer um appgadget que permita aos pais e responsáveis monitorar a saúde de seus filhos de forma remota, a qualquer hora e em qualquer lugar 

Instruções: 

Objetivo e Visão Geral 

Este código é projetado para um Monitor VitaKids, um dispositivo que simula o monitoramento de vários parâmetros de saúde: temperatura, frequência cardíaca, açúcar no sangue, vitaminas e gordura corporal. Ele se conecta a uma rede Wi-Fi e publica notificações em um broker MQTT quando qualquer um dos parâmetros monitorados estiver fora dos limites predefinidos. 

Explicação Detalhada 

Bibliotecas e Constantes 

O código começa incluindo as bibliotecas necessárias para comunicação Wi-Fi (Wire.h), display LCD (LiquidCrystal_I2C.h), mensagens MQTT (PubSubClient.h) e operações de rede gerais (WiFi.h). 

Em seguida, define constantes para credenciais Wi-Fi (SSID e PASSWORD), configurações do broker MQTT (BROKER_MQTT, BROKER_PORT, ID_MQTT, TOPIC_PUBLISH_MSG, TOPIC_SUBSCRIBE_DISABLE) e limites de parâmetros de saúde (temperaturaLimite, batimentosLimiteSuperior, batimentosLimiteInferior, acucarLimiteInferior, acucarLimiteSuperior, vitaminasLimite, gorduraLimiteSuperior, gorduraLimiteInferior). 

Funções Wi-Fi e MQTT 

O código define funções para inicializar conexões Wi-Fi e MQTT: 

initWiFi(): Estabelece uma conexão com a rede Wi-Fi especificada e exibe mensagens de status. 

initMQTT(): Define os parâmetros de conexão do broker MQTT e a função de retorno de chamada. 

Função de retorno de chamada MQTT 

A função de retorno de chamada callbackMQTT() é responsável por lidar com mensagens MQTT recebidas. Neste caso, ainda não executa nenhuma ação específica. 

Funções de Reconexão 

As funções reconnectMQTT() e reconnectWiFi() são usadas para reestabelecer conexões em caso de interrupções: 

reconnectMQTT(): Tenta se reconectar ao broker MQTT e se inscrever no tópico especificado. 

reconnectWiFi(): Reconecta à rede Wi-Fi e exibe mensagens de status. 

Função de Verificação e Notificação de Parâmetros de Saúde 

A função exibirNotificacao(String mensagem) exibe uma mensagem de notificação no LCD e a publica no tópico MQTT TOPIC_PUBLISH_MSG: 

exibirNotificacao(String mensagem): Limpa o LCD, exibe a mensagem fornecida, aguarda 2 segundos, limpa o LCD novamente e publica a mensagem no tópico MQTT. 

Função de Atualização do Display LCD 

A função atualizarTela(int temp, int bpm, int acucar, int vit, int gordura) atualiza o display LCD com os valores atuais dos parâmetros de saúde: 

atualizarTela(int temp, int bpm, int acucar, int vit, int gordura): Limpa o LCD, exibe os valores de temperatura, frequência cardíaca, açúcar no sangue, vitaminas e gordura corporal, cada um em uma linha separada. 

Leitura Simulada de Sensores 

A função simularSensor(int minValue, int maxValue) simula leituras de sensores gerando valores aleatórios dentro de um intervalo especificado: 

simularSensor(int minValue, int maxValue): Retorna um número inteiro aleatório entre os valores mínimo e máximo fornecidos (inclusive). 

Função Setup 

A função setup() é executada uma vez na inicialização: 

setup(): Inicializa as conexões Wi-Fi e MQTT, configura o monitor serial, inicializa o display LCD, exibe uma mensagem de boas-vindas, aguarda 2 segundos, limpa o LCD e exibe o nome do dispositivo. 

Função Loop 

A função loop() é executada continuamente: 

loop(): Verifica as conexões Wi-Fi e MQTT, lida com mensagens MQTT, simula leituras de sensores para temperatura, frequência cardíaca, açúcar no sangue, vitaminas e gordura corporal, verifica cada parâmetro contra seu limite respectivo, exibe notificações e atualiza o display LCD conforme necessário, e aguarda 5 segundos antes de repetir o ciclo. 

Explicação Adicional 

A função simularSensor(int minValue, int maxValue) é usada para gerar valores aleatórios para os parâmetros de saúde. Os valores mínimo e máximo são definidos pelas constantes temperaturaLimite, `batimentosLimiteSuperi. 

 

Link para simulação: 

https://wokwi.com/projects/382120070819581953 