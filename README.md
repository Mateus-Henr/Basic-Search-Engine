# Mecanismo de Busca Basico 
> Trabalho Prático 01 – AEDES 2 – Trio
No trabalho, foi sugerido a implementação de um código para a construção de índice invertido para máquinas de busca, a análise do tempo de execução, a relevância dos termos para a consulta, etc. a fim de compreender melhor como funciona a busca de palavras-chave.

# Compilar o codigo no ubuntu
Como o codigo foi feito por meio da IDE CLion então utilizaremos da cmakefile para compilar o codigo,primeiro execute o codigopara instalar o cmake em seu sistema operacional com o comando:
~~~
$ sudo apt-get install cmake
~~~
Apos a instalação basta abrir o projeto e executar os seguintes comandos:
~~~
$ rm -rf build
$ mkdir build && cd build
$ cmake ../
$ make 
$ ./TP1-AEDES2
~~~
# Colaboradores
## João Victor
Nome: João Victor Graciano Belfort de Andrade

Usuário_GitHub: [BelfortJoao](https://github.com/BelfortJoao)

Instituição: [UFV-Florestal](https://www.novoscursos.ufv.br/graduacao/caf/ccp/www/)

## Vitor Ribeiro
Nome: Vitor Ribeiro Lacerda

Usuário_GitHub: [Vith-MCB](https://github.com/Vith-MCB)

Instituição: [UFV-Florestal](https://www.novoscursos.ufv.br/graduacao/caf/ccp/www/)

## Mateus Henrique
Nome: Mateus Henrique Vieira Figueiredo

Usuário_GitHub: [Mateus-Henr](https://github.com/Mateus-Henr)

Instituição: [UFV-Florestal](https://www.novoscursos.ufv.br/graduacao/caf/ccp/www/)

# Arquivos:
...

# Observações:
Nesse TP, estamos utilizando a pasta "files" encontrada no diretório raiz para armazenamento de arquivos de teste.Como o TP (trabalho prático) foi realizado usando a IDE (Integrated Development Environment) CLion, o ".exe" é gerado na pasta "cmake-build-debug", portanto utilizamos essa pasta como base para arquivos para serem lidos.Dessa forma, no arquivo " src/file/file.c", caso não seja utilizado CLion é necessário editar o valor na constante "INPUT_FILE_PATH" para "files/", no qual referenciará a pasta no diretório raiz to projeto.
