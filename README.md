<div align="center" >
  <img src="https://raw.githubusercontent.com/ThreeDP/ThreeDP/main/imgs/GNL.svg" alt="Get Next Line" width="175" height="175">
  <h1>Get_next_line</h1>
</div>

# :trophy: Score
> A pontuação máxima que um projeto pode atingir na 42sp, considerando apenas a parte mandatório, é de 100 pontos. Caso seja realizado o bônus do projeto, a pontuação pode ser de 101 até 125. 

# :clipboard: About
> O projeto da GNL não é tão complicado (será se fizer com lista encadeada), porém é um projeto que exige bastante atenção e cuidado, pois é necessário entender muito bem o que está acontecendo com o código para conseguir implementar a função corretamente. Caso contrário, poderá ter vazamentos de memória (clássico do GNL) e uns erros comuns, como de compilação, erros de execução e etc. Inicialmente, minha ideia era faze-lo com lista encadeada, mas tive mais dificuldade do que imaginava, então mudei para cadeira de arrays e trabalhei a síntaxe exclusivamente com ponteiros.

# :screwdriver: How to use
> Este repósitorio conta com dois main.c diferentes, um para o mandatório, que vai testar um arquivo .txt e um voltado para o bônus, que irá testar vários arquivos .txt que irão ser passados como argumento na execução do programa. Para usa-lo, clone este repositório em sua pasta de interesse, acesse a pasta mandatório ou bônus e execute o comando abaixo:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=<seu_valor> get_next_line.c get_next_line_utils.c main.c && ./a.out
```

> Onde <seu_valor> é o valor que você quer que o BUFFER_SIZE tenha. Caso não seja passado nenhum valor, o BUFFER_SIZE será 50.
Outro ponto, é que o main.c do bônus, irá receber como argumento os arquivos .txt que você quer testar, então, para usa-lo, execute o comando abaixo:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=<seu_valor> get_next_line.c get_next_line_utils.c main_bonus.c && ./a.out <arquivo1.txt> <arquivo2.txt> <arquivo3.txt>
```

# :construction: Development
> Meu projeto foi desenvolvido com cadeia de arrays, pois tive dificuldade em implementar com lista encadeada. Além de fazer com cadeia de arrays, quis fazer exclusivamente com ponteiros, para treinar a síntaxe e entender melhor como funciona a manipulação de ponteiros em C. Foi bem desafiador, principalmente para evitar que vazamentos ocorressem por perda de referência.
