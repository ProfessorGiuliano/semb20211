Dados Sobre o funcionamento

O veiculo de mapeamento, atualmente possui duas versões, uma onde é comandando via servidor Stomp e outra via UDP

Apesar de ter duas comunicações, os comandos que o veiculo espera e responde são os mesmos.

Configurado para receber dois comandos principais, movimento e leitura.
	
O comando movimento deve ser formatado da seguinte forma

movimento/direção/tempo

onde:
o termo movimento é fixo,
o termo direção é um dos seguintes comandos:
	f -> frente
	r -> ré
	e -> esquerda
	d -> direita
o termo tempo é em int, onde indica quanto tempo ele executará esse movimento.

O comando leitura deve ser formatado da seguinte forma

leitura/
	
onde o Servo começará a se movimentar, partindo do angulo de 15º até 165º e a cada passo enviara a seguinte mensagem:

Angulo,leituraDoSonar.

depois de fazer a leitura da "ida", o servo faz a "volta", de 165º para 15º e a cada passo envia a seguinte mensagem:

Angulo,leituraDoSonar.


	