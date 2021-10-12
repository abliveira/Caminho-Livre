# Caminho Livre

[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

**O Caminho Livre é um repositório de hardware livre do projeto de Tecnologia Assistiva para Locomoção de Pessoas com Deficiência Visual, desenvolvido no Instituto Federal de São Paulo (IFSP) como trabalho de conclusão de curso.**

![Bengala_Dobrada](https://github.com/abliveira/Caminho-Livre/blob/main/midia/1.jpg)

O projeto foi criado com o objetivo de desenvolver uma tecnologia assistiva para melhorar a locomoção de pessoas com deficiência visual, sempre focando nas necessidades do grupo, desde o momento da concepção, com pesquisas e entrevistas, até os testes práticos para validação e aperfeiçoamento com a participação de voluntários reais.

Após a conclusão do projeto, como trabalho de graduação, a criação deste repositório vem com o objetivo de permitir que mais pessoas possam contribuir, reproduzir ou dar sequência, incentivando discussões sobre o tema da deficiência visual e de tecnologias assistivas, ou até mesmo permitir a evolução do projeto ao ponto de maturidade em que possa ser produzido.

* * *

# Índice

| [Monografia][monografia-pdf] | [Contato][form-contato] | [Licença de Uso](#licença-de-uso)
|--|--|--|

1. [Intro](#intro)</br>
    1.1 [Por que fazer?](#por-que-fazer)</br>
    1.2 [Por que tão poucas opções?](#por-que-tão-poucas-opções)</br>
    1.3 [O que fazer?](#o-que-fazer)</br>
2. [O Projeto](#o-projeto)</br>
    2.1 [Versão de Desenvolvimento](#versão-de-desenvolvimento)</br>
    ⠀⠀⠀2.1.1 [Montagem Eletrônica](#montagem-eletrônica-dev)</br>
    ⠀⠀⠀2.1.2 [Montagem Mecânica](#montagem-mecânica-dev)</br>
    ⠀⠀⠀2.1.3 [Testes](#testes-dev)</br>
    2.2 [Versão de Produção](#versão-de-produção)</br>
    ⠀⠀⠀2.2.1 [Montagem Eletrônica](#montagem-eletrônica-prod)</br>
    ⠀⠀⠀2.2.2 [Montagem Mecânica](#montagem-mecânica-prod)</br>
    ⠀⠀⠀2.2.3 [Testes](#testes-prod)</br>
3. [Pendências](#pendências)</br>
4. [Como Colaborar ou Fazer](#como-colaborar-ou-fazer)
5. [Contato](#contato)
6. [Licença de Uso](#licença-de-uso)
7. [Aviso](#aviso)

# Intro

> *Com o envelhecimento populacional e a maior expectativa da vida em todo o mundo, houve um aumento significativo de pessoas com deficiência. Estima-se que 15% da população global viva com algum tipo de deficiência (OMS, 2011).*
>
> *No Brasil, existem aproximadamente 45 milhões de deficientes, dos quais 7 milhões se enquadram como pessoas com deficiência de alta ou total perda de visão (IBGE, 2010). A deficiência visual, em qualquer grau, compromete a capacidade das pessoas de se orientar e de se movimentar no espaço com plena segurança e independência (GIL, 2000).*
>
> *A integração completa na sociedade exige, para pessoas com quaisquer deficiências, que todos os seus direitos sejam garantidos, como saúde, educação, emprego, transporte e informação. Tecnologias assistivas, isto é, qualquer equipamento, criado ou adaptado, com o intuito de melhorar a capacidade funcional de pessoas com deficiência, têm se mostrado ferramentas poderosas no auxílio a esses direitos.*

*(Texto extraído e adaptado na [monografia][monografia-pdf] deste trabalho*

[monografia-pdf]: https://github.com/abliveira/Caminho-Teste/blob/0b8b0f25ac2f70357020341182dcb537150a3389/docs/Desenvolvimento%20de%20Tecnologia%20Assistiva%20para%20Locomo%C3%A7%C3%A3o%20de%20Pessoas%20com%20Defici%C3%AAncia%20Visual.pdf

## Por que fazer?

A tradicional bengala branca e o cão guia são os dois métodos mais comuns de auxílio à locomoção de pessoas com deficiência visual. Já não são o suficiente?

Acontece que a bengala branca não é perfeita. É ineficaz para que o usuário identifique obstáculos acima do solo, como mesas, árvores, orelhões e fios de tensão. Isso é um problema comum, e grave.

Já um cão guia, ainda que muito competente, envolve altos custos de aquisição e requer muito cuidado e responsabilidade, fator delicado para pessoas de maior vulnerabilidade. É para poucos.

E basicamente, é só isso. 

## Por que tão poucas opções?

Identificamos que apesar de haver muitas ideias de tecnologias assistivas, poucas tiveram algum tipo de êxito. Até se encontram alguns dispositivos diferentes a venda, mas são poucos e a preços proibitivos.

Conversamos bastante ao longo do trabalho com voluntários com deficiência visual, e entendemos que novas ferramentas são sempre bem-vindas, mas precisam vir para agregar, e de forma alguma atrapalhar. Além disso, eles afirmam necessitar de independência e incomodar-se com tratamentos diferenciados.

São nesses pontos que a maioria das novas ideias erram. Apesar do válido entusiasmo de desenvolver equipamentos das mais diversas novas e excitantes tecnologias, a falta de contato com os usuários reais leva a uma distância muito grande do que os engenheiros querem fazer e com o que os usuários querem usar.

Equipamentos vestíveis, sensores gigantes alocados na face, ou até no lugar dos olhos são no mínimo constrangedores para os usuários. Além de muitos também serem pesados, pouco ergonômicos e difíceis de usar. Muitos dos trabalhos acadêmicos se quer são testados ou avaliados por deficientes visuais.

## O que fazer?

Existem inúmeras possibilidades, inclusive tecnologias avançadas como sensores 3D, reconhecimento de objetos, inteligência artificial, etc. Neste projeto, optamos pelo design mais simples: apenas um sensor eletrônico acoplado na tradicional bengala branca. Por quê? Porque é simples e funcional.

Desenvolver um equipamento que cause impacto não necessariamente quer dizer que precise ser complicado, mas que cumpra o seu objetivo e alcance o máximo de pessoas possível. E não complicando excessivamente, permite focar no desenvolvimento de um hardware dedicado, com tamanho e custos reduzidos, viabilizando a sua implementação em larga escala. E utilizando como base um equipamento já consagrado, porém falho — e é isso que decidimos resolver — facilita a adesão dos usuários.

Mas é necessário atender critérios mínimos, caso contrário, não há o porquê migrar dos métodos tradicionais, por mais que estes possuem suas limitações. Sumarizamos estes critérios como: funcionalidade, usabilidade, confiabilidade, ergonomia, portabilidade e discrição.

# O Projeto

O desenvolvimento do projeto foi dividido em duas versões: uma [versão de desenvolvimento](#versão-de-desenvolvimento) e uma [versão de produção](#versão-de-produção). Ambas versões compartilham a mesma estrutura: a parte mecânica, composta por uma bengala branca, e a parte eletrônica, composta basicamente por um microcontrolador, um sensor de distância, um atuador, um sistema de alimentação recarregável e botões de controle.

O funcionamento se dá pela identificação de obstáculos pelo sensor de distância, que fornece dados para o microcontrolador. Se interpretar que há uma barreira, é gerado um alerta para usuário com antecedência necessária para que seja feito um desvio no percurso. A geração de alertas para o usuário é feita por atuador de vibração, e o ajuste de sensibilidade, que é a distância para disparo do alerta, é feito com potenciômetros — deve ser um valor de distância segura, mas sem alertar desnecessariamente o usuário.

O tipo de sensor usado para este projeto é critico: requer uma distância de medição na ordem de metros, alta velocidade de resposta, capacidade de detectar diferentes tipos de materiais e sob diferentes condições ambientais, como luz e umidade, tamanho e consumo de energia reduzidos e ainda precisam ter custo razoavelmente baixo.

Considerando a necessidade de uso diário e o tempo de deslocamento urbano, estimado pelos usuários em até 3 horas, o dispositivo conta com bateria recarregável, larga autonomia e prático sistema de recarregamento.

## Versão de Desenvolvimento

![Versão_de_Desenvolvimento](https://github.com/abliveira/Caminho-Livre/blob/main/midia/2.jpg)

A versão de desenvolvimento tem como objetivo permitir a definição de características básicas, como a escolha de sensores, atuadores, etc, facilitando testes e agilizando ajustes, mas deixando de lado aspectos importantes como ergonomia, portabilidade e discrição, que são priorizados na versão de produção.

Esta versão passou por testes de bancada, testes práticos com pessoas não portadoras de deficiência visual e testes práticos monitorados com pessoas portadoras — etapa essencial para o recebimento de feedbacks para a execução de ajustes necessários.

#### Materiais Necessários

- Bengala branca
- Arduino Nano
- Sensores de distância: VL53L0X e HC-SR04
- Atuadores de vibração (Diversos tipos)
- Display
- Potenciômetros
- Módulo Powerbank
- Bateria de lítio 3.7V
- Buzzer (Opcional)
- Materiais para soldagem: Placa de fenolite ilhada, estanho e ferro de solda
- Componentes eletrônicos básicos (Pinos, jumpers, resistores, MOSFETs, diodos)
- Software Arduino IDE
- Software de Desenho Eletrônico

### Montagem Eletrônica <sup><sub>(dev)</sub></sup>

![Eletrônica_Desenvolvimento](https://github.com/abliveira/Caminho-Livre/blob/main/midia/3.jpg)

O circuito eletrônico desta versão é projetado para permitir testes comparativos entre tipos de sensores e tipos de atuadores. A eletrônica é comandada por um Arduino Nano — pela flexibilidade, disponibilidade de bibliotecas, tamanho e baixo consumo. 

Os sensores usados nesta versão são o HC-SR04 — um sensor ultrassônico bem comum e bem documentado — e o VL53L0X — um sensor óptico baseado em tecnologia ToF (Time-Of-Flight). Com o sensor HC-SR04, a distância é aferida através do controle dos pinos Trigger e da leitura do pino Echo, que responde com um intervalo de tempo de acordo com a distância medida após o disparo do primeiro pino. Já com o sensor VL53L0X, a distância é aferida e calculada pelo próprio sensor, sendo necessário o uso da API disponibilizada pelo fabricante para comunicação via rede I2C (Neste projeto utilizada a biblioteca [VL53L0X library for Arduino](https://github.com/pololu/vl53l0x-arduino) para Arduino).

A checagem de dados em tempo real é possível por comunicação serial (quando na bancada) ou por display OLED (quando em campo). O ajuste de sensibilidade é feito individualmente para cada sensor por meio de potenciômetros.

A geração de alertas para o usuário é feita para cada sensor com um tipo de atuador diferente para fins de teste: um motor de corrente contínua com uma massa desbalanceada no eixo e um atuador de vibração linear, de tamanho reduzido e sem partes móveis expostas. Um buzzer também é usado apenas para auxiliar os desenvolvedores na identificação do alerta vibratório sentido por um usuário durante os testes, mas não usado prática por ser considerado indiscreto pelos usuários.

<!---
**Figura: Fotos dos motores
-->
Como as portas do microcontrolador não suportam a corrente dos atuadores, cada um é acionado por um circuito de drive com um MOSFET BS170 controlado por uma porta lógica do microcontrolador com PWM, um resistor de 1 kΩ ligado ao Gate do MOSFET, um diodo 1N4007 de flyback e o atuador, ligado ao 5 V da placa Arduino.

<!---
**Figura 18: Esboço inicial do diagrama do circuito eletrônico.
-->
Para a alimentação do circuito eletrônico, é usada uma bateria de lítio (escolhida devido à leveza e facilidade de recarregamento) com um módulo de powerbank, que protege, gerencia, recarrega e converte a tensão da bateria para os 5V necessários pelo circuito.

<!---
**Figura: foto de bateria, modulo power
-->
Para finalização, o circuito é montado em uma placa de fenolite, usando pinos sempre que possível para facilitar a troca dos componentes.

<!---
Figura 19: Diagrama do circuito eletrônico.

Figura 20: Primeira versão do sistema eletrônico.
-->
### Montagem Mecânica <sup><sub>(dev)</sub></sup>

Com a necessidade de detecção básica de identificação de objetos acima da linha da cintura, é necessário um sensor com inclinação em relação ao solo entre 30° a 45°. Complementarmente, poderia ser adotado um segundo sensor para auxiliar a detecção de objetos afrente do usuário com antecedência. No entanto, devido à fragilidade das partes inferiores das bengalas, frequentemente quebradas durante o uso, um segundo sensor seria também facilmente danificado, aumentando consideravelmente o custo de manutenção. Além disso, a complexidade da instalação aumentaria, devido à necessidade de fiação passando entre os gomos. Assim, a detecção de obstáculos à frente do usuário não é implementado neste projeto.
<!---
Figura 11: Dispositivo com sensor único. Figura 12: Dispositivo com sensor duplo.
-->
O sistema eletrônico foi montado em uma bengala dobrável utilizando-se fita adesiva. Para evitar curtos na placa devido ao contato do corpo metálico da bengala com o circuito, a placa pode ser revestida com fita isolante. Para que as vibrações possam ser sentidas na mão do usuário, é necessária uma boa fixação dos atuadores na bengala. 

### Testes <sup><sub>(dev)</sub></sup>

Esta versão do projeto foi testada com foco no desempenho dos sensores e na funcionalidade do equipamento em cenários controlados. Para ambos os sensores, foram analisados características como alcance, resolução, estabilidade, tempo de resposta e consistência das medições em determinados tipos de materiais, ângulos de superfícies, refletâncias e opacidades. 

O sensor ultrassônico HC-SR04, possui boa distância máxima de 4 m e boa resolução, mas para distâncias curtas. Este tipo de sensor apresentou falhas com tecidos e superfícies inclinadas, devido às características da onda emitida que pode ser facilmente absorvida ou refletida. Além disso, há diferença de qualidade entre sensores HC-SR04, sendo que algumas unidades apresentaram instabilidade.

O sensor VL53L0X, possui de fábrica distância máxima de 1,2 m. É possível ajustá-lo para até 2 m, podendo ocorrer imprecisões, mas que não apresentaram grandes problemas (Há a versão VL53L1X, não usada neste projeto, mas que possui distância máxima de até 4 m). Este sensor apresentou ótima consistência na detecção dos objetos testados, não apresentando diferenças com tipos de materiais e ângulos de superfícies.

Por segurança, os testes práticos foram realizados em cenários controlados, e primeiramente com pessoas sem deficiência visual. Os cenários foram criados com obstáculos específicos, perigosos e comuns para uma pessoa a deficiência, como vasos, lonas, varais, árvores e orelhões. Nos testes, o sensor ultrassônico não foi capaz de detectar obstáculos de forma segura, já que as falhas anteriormente citadas comprometeram a capacidade do sensor de detectar obstáculos. Já o sensor óptico, foi capaz de detectar os obstáculos de modo satisfatório.

Na avaliação dos usuários, o conceito foi validado pelo fato do dispositivo ter sido capaz de identificar com antecedência obstáculos que seriam difíceis somente com a bengala branca. O dispositivo agradou por ser uma integração simples da bengala branca tradicional com um sistema eletrônico, e por ser de fácil uso, possuir recarregamento com carregador de celular e possuir ajuste de distância.
<!---
Figura 28: Participante com deficiência visual durante os testes.
-->
Foram necessários ajustes da intensidade de vibração dos atuadores, devido à dificuldade de se distinguir a vibração gerada pelo alerta com a vibração gerada pelo contato da bengala com o solo, e a criação de um indicador de orientação do sensor, que sempre deve estar para frente. Considerando a posição habitual dos usuários de segurar a bengala, o indicador foi colocado na região do polegar.

## Versão de Produção

![Versão_de_Produção](https://github.com/abliveira/Caminho-Livre/blob/main/midia/4.jpg)

A versão de "produção" foi criada para ser o mais próximo possível de um produto real. Com o projeto mais maduro, e características melhor definidas, são abandonadas facilidades adotadas exclusivamente para desenvolvimento, limitando as possibilidades mudanças radicais, mas atingindo  melhor eficiência, custo, visual e ergonomia, sem comprometer a funcionalidade. 

Para a eletrônica, foi projetada uma placa de circuito impresso customizado, abrangendo a maior parte da eletrônica anteriormente modularizada. Na mecânica, uma bengala customizada foi desenvolvida para abrigar o circuito e ficar o mais parecido o possível de uma bengala comum. Ao final, o equipamento passou por novos testes práticos para validação final.

#### Materiais Necessários

- Bengala branca dobrável
- Tubo de alumínio
- Serra e torno mecânico
- Placa de circuito impressa (sob encomenda)
- Componentes eletrônicos da placa <!---(**Lista BOM**)-->
- Sensores de distância VL53L0X
- Atuador vibração linear
- Bateria de lítio 3.7V 14500
- Arduino ou Gravador ISCP com jumpers
- Materiais para soldagem: estanho e ferro de solda
- Software Arduino IDE
- Software **avrdude
- Software de Desenho Eletrônico
- Software de Desenho Mecânico

### Montagem Eletrônica <sup><sub>(prod)</sub></sup>

![Eletrônica_Produção](https://github.com/abliveira/Caminho-Livre/blob/main/midia/5.jpg)

O circuito eletrônico foi embarcado em uma placa de circuito impresso, com exceção do sensor, da bateria e do motor. O circuito é comandado diretamente pelo microcontrolador ATMEGA328. A gravação do firmware é feita interface ICSP - mais direta e simples que via serial. E a comunicação serial, se necessária, pode feita com um conversor Serial-USB externo, através de pinos disponibilizados no layout da placa.

<!---
Figura 31: Diagrama do sistema de controle e de drive.
-->
Como na versão de testes o sensor ultrassônico HC-SR04 apresentou problemas, esta versão foi projetada apenas com o sensor óptico VL53L0X, que além de melhor desempenho, é pequeno o suficiente para ser embutido dentro da bengala, junto com o restante do sistema eletrônico — ao contrário do sensor ultrassônico que precisaria ser instalado externamente, ficando exposto a danos e impactando o aspecto visual final.

O sistema de alimentação utiliza nível lógico de 3,3 V, por apresentar melhor compatibilidade entre os componentes utilizados — incluindo a bateria. São necessários apenas um regulador de tensão para o circuito (MIC5205, escolhido pelo tamanho e custo-benefício) e um sistema de proteção da bateria (Circuito composto pelo TP4056, DW01 e FS8205). Para ligar e desligar, a entrada do regulador é ligada a um botão com trava, para maior conforto do usuário.

A bateria é uma célula Li-Ion 14500 de 900 mAh, que devido ao encapsulamento cilíndrico, é ideal para alojamento no interior bengala, possuindo apenas 50 mm de comprimento e 14 mm de diâmetro. O recarregamento é feito via interface USB Tipo C, que pode ser facilmente encontrada em carregadores de celular e ainda tem a vantagem de ter conector reversível, que facilita o uso principalmente por pessoas com deficiência visual. O cabo usado é USB Tipo C com conector magnético, facilitando ainda mais o recarregamento.

<!---
**Figura 32: Cabo USB magnético utilizado para carregamento.**
-->
O controle do carregamento da bateria é feito pelo circuito integrado TP4056. A corrente máxima é determinada por um resistor entre os pino PROG e GND.  O valor de 2,2 kΩ limita a corrente em 0,5 A, ideal para um carregamento rápido sem danificar a bateria. Os pinos CHRG e STBY indicam os estados de "em carregamento" e "carregado", respectivamente. Como sinalizadores luminosos não atendem à necessidade de portadores de deficiência visual, os pinos são ligados ao microcontrolador, para sinalizar estes estados através de padrões vibratórios. Complementarmente, o circuito integrado DW01 junto ao MOSFET duplo FS8205 protegem a bateria contra descarga e carregamento excessivos e contra sobrecorrente. O monitoramento do nível de tensão da bateria é feito por um divisor de tensão ligado a uma porta analógica do microcontrolador: caso a bateria esteja fraca, uma função no firmware ativa o atuador para o usuário seja alertado através de padrões vibratórios. O nível de carga também é indicado toda vez ao ligar o dispositivo.

<!---
Figura 33: Diagrama do sistema de alimentação do circuito.
-->
Como entre os tipos de atuadores de vibração não aprestaram diferença de sensibilidade, devido ao consumo de 230 mA do motor CC e 70 mA do atuador linear, foi adotado o de menor consumo.

Para reduzir o tamanho, a placa foi projetada com componentes em ambos os lados. São usados os menores encapsulamentos, mas sem dificultar a montagem manual — uma versão futura poderia ter dimensões ainda mais reduzidas caso fossem adotados encapsulamentos menores para serem montados por máquinas pick and place.

As trilhas da placa são projetadas para suportar com folga a corrente do circuito, com 0,381 mm de largura para trilhas de energia, 0,254 mm para trilhas de sinais e planos GND em ambos lados da placa. Os capacitores do circuito são dimensionados de acordo com os datasheets dos fabricantes dos circuitos integrados.

Finalizada, as dimensões são 58 x 15 mm, o suficiente para a placa ser alocada no interior de uma bengala com dimensões padrões. O layout foi enviado para produção e os componentes foram comprados separadamente, sendo soldados à mão. Para ligação dos componentes externos, (bateria, o motor e o sensor), foram soldados cabos e conectores.

<!---
**Figura xx: Fotos**
-->
### Montagem Mecânica <sup><sub>(prod)</sub></sup>

Entre os tipos mais comuns de bengalas — dobráveis e telescópicas — a dobrável foi adotada pela possibilidade de alojar toda eletrônica no interior da bengala, ficando menos exposta ao ambiente e a choques mecânicos, além de ser esteticamente mais agradável. Na bengala telescópica, seria inviável o alojamento no interior devido à retração dos gomos. Além disso, a bengala dobrável é a mais comum e que possui maior resistência — e consequentemente maior segurança e menor custo de manutenção.

A produção do protótipo da bengala customizada foi realizada em parceria com um fabricante de bengalas brancas. Graças as dimensões reduzidas da eletrônica, foi possível adotar um tamanho padrão de bengalas brancas com diâmetro interno da luva de 16 mm. Todos os gomos foram fabricados normalmente — cortados e torneados — sendo apenas a luva customizada para o alojamento e fixação da eletrônica: furos da porta USB, da chave liga-desliga e furos de fixação, feita por parafusos, e abertura da lente, que deve ser ampla o suficiente para não atrapalhar o funcionamento do sensor. Ainda foi realizado umn recartilhado na luva para sinalizar a extremidade da bengala.

Aderindo aos feedbacks dados no teste da bengala, foi incluído um indicador de orientação na lateral da luva para o polegar, para que o usuário possa sempre manter o sensor apontado para frente.

<!---
Figura 52: Indicador de orientação da bengala.

Figura 48: Processo de fabricação da bengala por torneamento.

Figura 49: Foto frontal do modelo em alumínio. Figura 50: Foto lateral do modelo em alumínio.

Figura 51: Luva da bengala com circuito eletrônico montado. Figura 53: Versão final montada e estendida.
-->
### Testes <sup><sub>(prod)</sub></sup>

O consumo médio de energia do circuito, sem nenhum tipo de otimização, foi medido em 8,3 uA quando desligado e 22 mA ativo, sem ativação do atuador. Portanto, a capacidade de 900 mA seria capaz de alimentar o circuito por no máximo 41 horas, sem alertas. No pior cenário possível, com o alerta sendo disparado ininterruptamente, o consumo médio seria de 57 mA, considerando o padrão de vibração do atuador. Assim, a autonomia mínima seria cerca de 16 horas, superior ao uso diário estimado pelos usuários em cerca de 3 horas.

Os testes práticos foram elaborados e executados com participação de pessoas com deficiência visual e especialistas em mobilidade urbana de pessoas com deficiência visual. Os cenários de testes foram criados para simular ambientes internos e externos com obstáculos comuns e perigosos, como cadeiras, porta e mesas, desníveis de solo, degraus, árvores, etc. Conforme esperado, a identificação de obstáculos baixos foi possível apenas usando a bengala tradicionalmente. Mas obstáculos altos foram detectados pelo sensor com pelo menos 0,3 m de distância, o suficiente para desvios com antecedência.

Na avaliação geral feita pelos usuários, o dispositivo foi visto como uma melhoria real para locomoção, sem de forma alguma comprometer algum outro aspecto de sua mobilidade. Agradou por, além de ser funcional, atender as exigências feitas durantes as entrevistas, como boa ergonomia, peso e visual — muito similares a de bengalas tradicionais que já estão habituados, não gerando nenhum tipo de dificuldade, desconforto ou insegurança. 

Como pontos fortes, foram citados a facilidade de recarga (carregador celular e conector magnético), autonomia estimada, prático botão liga-desliga, indicador de orientação e robustez mecânica. Por outro lado, os usuários sugeriram a possibilidade da detecção de obstáculos mais baixos, que apesar de terem sido de forma tradicional, sem sensor, talvez pudesse ser identificados também eletronicamente, dando maior segurança. E ainda, apesar da robustez contra choques mecânicos, não há resistência a água, sendo incapaz de ser usada sob condições de chuva

# Pendências

- Desenvolvimento de impermeabilização da eletrônica
- Estudo de implementação de sensor frontal
- Uso de componentes menores e mais baratos (ex. microcontrolador) para redução do tamanho e custo da placa
- Estudo de embarcar conversor Serial-USB para permitir atualizações de firmware via USB
- Testes e mais testes: autonomia real do circuito, comportamento em ambientes e condições climáticas diversas, sensores diferentes e mais potentes (ex. VL53L1X)

# Como Colaborar ou Fazer

Apesar do desenvolvimento deste projeto ter sido finalizado, você pode abrir uma Issue para ajudar a identificar problemas ou possíveis melhorias. Você também pode contribuir diretamente com material para o repositório, fazendo uma Fork e uma Pull-Request.

Ou se deseja reproduzir, ou dar continuidade ao projeto, você pode fazer uma Fork apenas. Mas lembre-se: para a reprodução do projeto deste repositório, siga a licença de uso. E respeite os direitos autorais dos textos e imagens deste repositório e da monografia.

# Contato

Tem alguma dúvida ou sugestão sobre o projeto? Preencha este [formulário][form-contato] para entrar em contato.

[form-contato]: https://forms.gle/dRyWCC76HSZJ2Dhy7

# Licença de Uso

A reprodução do projeto deste repositório deve ser feita somente seguindo a licença de uso [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa]. Os textos e imagens deste repositório e da monografia possuem direitos autorais protegidos por lei, não abrangendo o conteúdo científico ou técnico ([Lei nº 9.610, de 19 de fevereiro de 1998](http://www.planalto.gov.br/ccivil_03/leis/l9610.htm)).

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: https://creativecommons.org/licenses/by-sa/4.0/deed.pt_BR
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
<!---

# Aviso
-->
