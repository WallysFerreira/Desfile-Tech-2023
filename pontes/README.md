# Pontes interativas
- 2 Pirâmides com motores servo e luzes RGB
- 8 Arduinos (receptores) recebem sinal infravermelho e controlam os motores e luzes baseado nesses sinais (ver tabela abaixo).
- 1 Arduino (emissor) monitora dois sensores ultrassonicos e faz requisição em uma API e envia sinal infravermelho baseado nas informações.

## Ideias

| Ação                          | Resultado                                   | Como                                                                                      |
|-------------------------------|---------------------------------------------|-------------------------------------------------------------------------------------------|
| Modelo passa pela piramide | As pontes se viram para a direção que a modelo está indo | Sensor de proximidade percebe o pé da modelo e arduino emissor envia sinal infravermelho fazendo com que os receptores  |
| O público reage à apresentação | As cores das duas reações mais votadas aparecem em cada piramide | Arduino puxa os resultados da aplicação web por uma API |

## Convenções

### Códigos IR

| Ação                                        | Código enviado | Resultado esperado                                      |
|---------------------------------------------|----------------|---------------------------------------------------------|
| Passou pelo primeiro sensor                 | A definir      | Os motores das duas pirâmides mexem pra direita (0º)    |
| Passou pelo segundo sensor na segunda vez   | A definir      | Os motores das duas pirâmides mexem pra esquerda (180º) |
| Recebeu reação vermelha como primeiro lugar | A definir      | Primeira pirâmide fica da cor vermelha                  |
| Recebeu reação vermelha como segundo lugar  | A definir      | Segunda pirâmide fica da cor vermelha                   |
| Recebeu reação azul como primeiro lugar     | A definir      | Primeira pirâmide fica da cor azul                      |
| Recebeu reação azul como segundo lugar      | A definir      | Segunda pirâmide fica da cor azul                       |
| Recebeu reação verde como primeiro lugar    | A definir      | Primeira pirâmide fica da cor verde                     |
| Recebeu reação verde como segundo lugar     | A definir      | Segunda pirâmide fica da cor verde                      |
| Quando a votação acabar                     | A definir      | Mistura as cores das duas pirâmides                     |

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