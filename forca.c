#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcao.h"

char ps[TAMANHO_PALAVRA]; // palavra secreta.
char chutes[26]; // o máximo de letras que podem ser chutadas.
int chutesdados = 0; // essa variável vai dizer quantos chutes o usuário ja deu.
int chuteserrados()
{
    int erros = 0;
    for(int i = 0; i < chutesdados; i++)
    {
        int existe = 0;
        for(int j = 0; j < strlen(ps); j++)
        {
            if(chutes[i] == ps[j])
            {
                existe = 1;
                break;
            }
        }
        if(!existe)
        erros++;
    }
    return erros;
}
void addpalavra()
{
    printf("voce quer adiionar uma palavra???\n");
    printf("se sim digite s, se nao digite n \n");
    
    char add;
    scanf(" %c", &add);

    if(add == 's')
    {
        char novapalavra[TAMANHO_PALAVRA];
        printf("qual a nova palavra? ");
        scanf("%s", novapalavra);

        FILE *f;
        f = fopen("palavras.txt", "r+"); //r+ significa ler e escrever.
        if(f == NULL)
        {
            printf("ERRO AO ABRIR O ARQUIVO\n");
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++; // aumentando um na quantidade de palavras

        fseek(f, 0, SEEK_SET); // posicionado a quantitade de palavras nova no começo do arquivo
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END); // posicionando a palavranova no final do arquivo.txt
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
    else
    printf("voce nao adicionou uma palavra nova\n");
}
void escolhepalavra()
{
    FILE *f; // uma variavel file também é um ponteiro
    f = fopen("palavras.txt", "r"); // lendo o arquivo "palavras.txt"

    int qtdpalavras; 
    fscanf(f, "%d", &qtdpalavras);// %d pois a primeira linha do arquivo possui o n 45 q e a quantidade de palavras
    if(f == NULL)
    {
        printf("\nerro ao abrir o arquivo\n");
    }
    srand(time(0)); // gerando uma semente aleatória para escolher uma palavra rand.
    int nrand = rand() % qtdpalavras; // isso porque o computador não consegue escolher uma palavra rand
                                      // mas consegue escolher uma linha.
    for(int i = 0; i <= nrand; i++)// o for le o arquivo sequencialmente até parar, e ele para quando
    {                              // i for igual ao numero randomico gerado.
        fscanf(f, "%s", ps);
    }
    fclose(f); 
}
int verifica(char letra)
{
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) // está varrendo o array de chutes, igual foi feito com o ps[i].
        {
            if(chutes[j] == letra) // se o que foi chutato, existir na ps, quer dizer que essa letra ja foi chutada.
            {
              achou = 1; // se o if for executato, quer dizer que achou é verdadeiro(1).
              break;
            }
        }
        return achou;
/* nessa função verifica, o resultado dela é importante, é preciso do resultado do achou depois
 da função ser executada, se resolve esse probleba dessa maneira. ao invés de void escreva int
 e adicione o "return achou;"
 o lugar da palavra void representa oque a função vai devolver. */
}
void chuta()
{
        char chute;
        printf("qual o seu chute: ");
        scanf(" %c", &chute);

        chutes[chutesdados] = chute; // os chutes do usuário estão sendo guardados nesse array
       chutesdados++;
}
void desenhaforca()
{
    int erros = chuteserrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '),(erros >= 1 ? '_' : ' ' ), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(ps); i++)
    
        {
            int achou = verifica(ps[i]);
            // o resultado dessa função vai ir para a variavel "achou"
            // esse resultado foi armazenado ali para ser usado no decorrer do código.
            if(achou)
                printf("%c ", ps[i]);
                else
                    printf("_ ");
        }
        printf("\n");
}
void abertura()
{
    printf("\n -_- !FORCA O JOGUINHO! -_-\n");
}
int enforcou()
{
    int erros = 0;
    for(int i = 0; i < chutesdados; i++)
    {
        int existe = 0;
        for(int j = 0; j < strlen(ps); j++)
        {
            if(chutes[i] == ps[j])
            {
                existe = 1;
                break;
            }
        }
        if(!existe)
            erros++;
    }
    return chuteserrados() >= 5;
}
int acertou()
{
    for(int i = 0; i < strlen(ps); i++)
    {
        if(!verifica(ps[i]))
            return 0;
    }
    return 1;
}
int main()
{   
    abertura();
    escolhepalavra(); 
    
    do
    {
        desenhaforca();
        chuta();
    }
    while(!acertou() && !enforcou()); // '!' significa negação.
    if(acertou())
        printf("\n:) !VOCE ACERTOU! (: \n");
        else
        {
            printf("\n:( !VOCE ERROU! ): \n");
            printf("A palavra sereta era: %s\n", ps);
        }
    //addpalavra();
}