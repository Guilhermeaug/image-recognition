
# Introdução  
O projeto da disciplina de Laboratório de Algoritmos e Estruturas de Dados I tem como missão criar um sistema escrito na linguagem C/C++ que recebe como parâmetro um arquivo contendo diversas linhas com segmentos de números inteiros que sinalizam uma determinada cor.  
  
Na realidade, cada segmento indica uma seção de uma imagem, sendo o objetivo final do trabalho identificar determinadas sequências na imagem dada.  
  
O problema em si foi solucionado em uma função que recebe uma linha do arquivo, que representa uma faixa da imagem, e verifica se nela existem um ou mais padrões, que são:  
  
- Padrão da pista (1, 3, 2, 3, 1)  
- Padrão da faixa de pedestre (1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1)  
  
Através de uma estrutura de repetição que percorre toda a lista encadeada foi verificado se os padrões estão presentes, seguindo a sequência dada.  
  
Em uma das partes do projeto foi necessário saber se a pista tende a ser uma curva à esquerda, à direita ou linha reta. Para cobrir esse requisito, durante a verificação dos padrões também é salvo o ponto médio da parte vermelha da pista. Desse modo, posteriormente foi calculada a porcentagem da imagem que contém o padrão da pista. Caso seja maior que 70%, o programa obtém a média e desvio padrão dos pontos médios da parte que contém a pista. Por meio destes dois dados, obtém-se o coeficiente de variação. Para casos com coeficiente maior que 10%, tem-se uma curva, para casos menores, será uma linha reta.  
  
# Desenvolvimento e Implementação  
Quanto às estruturas de dados, o projeto conta com 5 structs, sendo uma delas criada por nós para facilitar a implementação e as outras 4 são referências da implementação de listas encadeadas por ponteiros do Prof. Nivio Ziviani:  
  
Perfil: estrutura utilizada para guardar os padrões encontrados em cada linha da imagem e o respectivo ponto médio da pista (foi duplicado aqui para facilitar a recuperação posterior). Conta com duas booleanas e um double. 
TipoItem: corresponde a cada item armazenado na lista. Contém três inteiros que representam uma chave (id), tipo e número de elementos do segmento. Além de um ponto flutuante para armazenar o ponto médio.
TipoApontador: É simplesmente um envoltório para um ponteiro de TipoCelula.
TipoCelula: Possui como parâmetro um TipoItem e um TipoApontador.

Na função main do programa é declarado um *vector* do tipo TipoLista. Desse modo, cada linha da imagem será uma lista. Além disso, existe um outro *vector* do tipo double, para armazenar os pontos médios da pista. O primeiro *vector* é enviado para uma função que preenche o seu conteúdo com os itens lidos do arquivo. Além disso, a função *PreencheListas* também calcula o ponto médio dos segmentos.

No entanto, a principal função do código é a *VerificaSequencia*. Tal método recebe 	uma variável TipoLista por parâmetro e retorna um Perfil como resultado. Basicamente, a lista encadeada é percorrida, e quando algum padrão é encontrado, a variável booleana correspondente é *setada* como verdadeiro. Após isso, na função main, as estatísticas de tendência central são calculados e o resultado é apresentado de acordo com os perfis preenchidos.

# Conclusão

Por fim, é importante dizer que o projeto realizado ao longo do curso de Algoritmos e Estruturas de Dados I foi um excelente ponto de partida para o estudo mais aprofundado da programação, principalmente relacionado à produção de códigos fontes mais otimizados.

Como dificuldades para a produção do programa destacam-se a análise de casos de borda dos segmentos da imagem e a montagem de como organizar as listas e todas as variáveis de controle que são necessárias para gerar o resultado final. Pelos casos de teste realizados pelo sistema runCodes, não foram encontradas limitações para a implementação realizada.
