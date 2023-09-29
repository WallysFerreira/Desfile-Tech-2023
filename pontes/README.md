# Pontes interativas
Códigos e anotações das pontes que irão decorar a passarela do desfile.  

## Ideias

| Ação                          | Resultado                                   | Como                                                                                      |
|-------------------------------|---------------------------------------------|-------------------------------------------------------------------------------------------|
| Modelo pisa na linha da ponte | A ponte sobe e desce devagar                | Sensor de proximidade percebe o pé da modelo e dispara a função de subir e descer a ponte |
| Sinal infravermelho é enviado | Reage conforme a tabela de código IR e ação | Receptor IR recebe o sinal infravermelho e passa o código para um switch                  |

## Convenções

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