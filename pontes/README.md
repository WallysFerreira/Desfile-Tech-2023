# Pontes interativas
- 2 Pirâmides com motores servo e luzes RGB
- 8 Arduinos (receptores) recebem sinal infravermelho e controlam os motores e luzes baseado nesses sinais (ver tabela abaixo).
- 1 Arduino (emissor) monitora dois sensores ultrassonicos e faz requisição em uma API e envia sinal infravermelho baseado nas informações.


A ideia é que o arduino emissor controle os arduinos de cada linha enviando um único comando onde ele vai dizer: 
- O que quer controlar (luz ou motor) 
- O que quer colocar (Cor da luz no caso da luz) 
- Qual motor ou luz quer controlar (numero dele na pirâmide de cima para baixo)
- Como quer controlar (Para luz: Blink, fade ou cor fixa. Para motor: Direto ou cascata)
- Ângulo (para motor), intensidade (para LED em cor fixa) ou tempo (para LED em fade ou blink).

Usando I2C, cada arduino terá um endereço. E na mensagem I2C vamos mandar em formato de array de bytes:
- Qual motor ou luz queremos controlar (Para motor começa com 0x01 e vai até 0x04, para luz começa com 0xA1 e vai até 0xA4)
- Quantidade de vermelho (luz) ou angulo inicial (motor)
- Quantidade de verde (luz) ou angulo final (motor)
- Quantidade de azul (luz) ou velocidade (motor)

Então se quisermos que o motor 2 de uma linha faça um movimento começando no angulo 0 e indo até 180 graus na velocidade 2, enviariamos o array [0x02, 0x00, 0xB4, 0x02]

Para facilitar, os angulos de 0, 90 e 180 graus podem ser enviados usando os codigos 0xF1, 0xF2 e 0xF3 respectivamente.

<!--
Usando IR
O formato seria:
- address: Endereço da ponte que queremos controlar
- command: Comando para dizer se queremos controlar o motor ou qual perna do led RGB e como (blink, fade ou cor fixa)
- data: Dados para dizer o ângulo, intensidade ou tempo

Por exemplo, seguindo a tabela de comandos, se quisermos mexer o motor 5 da pirâmide da esquerda para direita na velocidade 2 enviariamos:

address: 5, command: 0x01, data: 0x000002
-->

## Ideias

| Ação                          | Resultado                                   | Como                                                                                      |
|-------------------------------|---------------------------------------------|-------------------------------------------------------------------------------------------|
| Modelo passa pela piramide | As pontes se viram para a direção que a modelo está indo | Sensor de proximidade percebe o pé da modelo e arduino emissor envia sinal infravermelho |
| O público reage à apresentação | As cores das duas reações mais votadas aparecem em cada piramide | Arduino puxa os resultados da aplicação web por uma API |

## Convenções
Nas pirâmides cada ponte é numerada de cima para baixo, da esquerda para direita. O endereço das pontes da pirâmide da esquerda vão de 1 até 10 e as da direita vão de 11 até 20.

### Conexões arduino receptor
| Componente                          | Porta      |
|-------------------------------------|------------|
| Motor 1 (da esquerda para direita)  | 5          |
| Motor 2 (se houver)                 | 6          |
| Motor 3 (se houver)                 | 7          |
| Motor 4 (se houver)                 | 8          |
| Receptor IR                         | 4          |
| Vermelho, verde, azul (1)           | 1, 2, 3    |
| Vermelho, verde, azul (2 se houver) | 9, 10, 11  |
| Vermelho, verde, azul (3 se houver) | 12, 13, 14 |
| Vermelho, verde, azul (4 se houver) | 15, 16, 17 |

<!--
### Comandos
| Command | Resultado                            |
|---------|--------------------------------------|
| 0x01    | Mudar motor da esquerda para direita |
| 0x02    | Mudar motor da direita para esquerda |
| 0x03    | Mudar motor do meio para direita     |
| 0x04    | Mudar motor do meio para esquerda    |
| 0x10    | Vermelho fixo                        |
| 0x11    | Verde fixo                           |
| 0x12    | Azul fixo                            |
| 0x13    | Vermelho + Verde fixo                |
| 0x14    | Verde + Azul fixo                    |
| 0x15    | Vermelho + Azul fixo                 |

<!--
### Códigos IR

| Ação                                        | Código enviado | Resultado esperado                                      |
|---------------------------------------------|----------------|---------------------------------------------------------|
| Passou pelo primeiro sensor                 | 0xFFFF01       | Os motores das duas pirâmides mexem pra direita (0º)    |
| Passou pelo segundo sensor na segunda vez   | 0xFFFF02       | Os motores das duas pirâmides mexem pra esquerda (180º) |
| Recebeu reação vermelha como primeiro lugar | 0xFFFF03       | Primeira pirâmide fica da cor vermelha                  |
| Recebeu reação vermelha como segundo lugar  | 0xFFFF04       | Segunda pirâmide fica da cor vermelha                   |
| Recebeu reação azul como primeiro lugar     | 0xFFFF05       | Primeira pirâmide fica da cor azul                      |
| Recebeu reação azul como segundo lugar      | 0xFFFF06       | Segunda pirâmide fica da cor azul                       |
| Recebeu reação verde como primeiro lugar    | 0xFFFF07       | Primeira pirâmide fica da cor verde                     |
| Recebeu reação verde como segundo lugar     | 0xFFFF08       | Segunda pirâmide fica da cor verde                      |
| Quando a votação acabar                     | 0xFFFF09       | Mistura as cores das duas pirâmides                     |

<!--
### O que está conectado em que porta

| Porta | Componente   |
|-------|--------------|
| 5     | Motor servo  |
| 7     | Receptor IR  |
| 10    | RGB Vermelho |
| 11    | RGB Verde    |
| 12    | RGB Azul     |

### O que fazer ao receber cada código infravermelho

| Codigo IR | Ação                               |
|-----------|------------------------------------|
| 1         | Subir e descer a ponte rapidamente |
| 2         | Piscar luzes                       |
| 3         | Mudar cores das luzes              |
-->