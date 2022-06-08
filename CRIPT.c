#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Configuração da Chave para criptografia
char CHAVE[500];
int TAM_CHAVE;

bool set_chave(char chave[]){
    if(strlen(chave)<500){
        strcpy(CHAVE,chave);
        TAM_CHAVE = strlen(CHAVE);
        return true;
    }else{
        return false;
    }
}
//----------------------------------------

// Vetor de entrada do texto a ser criptografado
char TEXTO[100000];
int TAM_TEXTO=100000;
//----------------------------------------------

int TEXTO_CRIPT[100000];

bool Criptografar(){
    int CHAVE_int;
    for(int i=0; i< strlen(TEXTO) ; i++){
        TEXTO_CRIPT[i]=TEXTO[i];
    }
    //printf("\n -- %d -- \n",TEXTO_CRIPT[9]);
    for(int aux=0; aux < strlen(TEXTO) ; ){
        for(int i=0;i<TAM_CHAVE; i++){
            //TEXTO_CRIPT[aux] = TEXTO_CRIPT[aux] * CHAVE[i];
            CHAVE_int = CHAVE[i];
            TEXTO_CRIPT[aux] *= CHAVE_int;
            TEXTO_CRIPT[aux] ^= CHAVE_int;
            ~TEXTO_CRIPT[aux];
            aux++;
        }
    }

    //printf("\n -- %d -- \n",TEXTO_CRIPT[9]);

    return true;
}

bool Descriptografar(){
    FILE *arquivo;

    int valor;
    int pos_chave;
    int pos_texto;

    arquivo = fopen("arquivos_recebidos\\criptografado.txt","r");

    if(arquivo==NULL){
        return false;
    }


    pos_chave=0;

    pos_texto=0;
    while(!feof(arquivo)){
        fscanf(arquivo,"%d",&valor);

        ~CHAVE[pos_chave];
        valor ^= CHAVE[pos_chave];
        valor /= CHAVE[pos_chave];
        //valor = valor / CHAVE[pos_chave];

        TEXTO[pos_texto] = (char)valor;

        pos_texto++;

        if(pos_chave==TAM_CHAVE-1){
            pos_chave=0;
        }else{
            pos_chave++;
        }
    }

    fclose(arquivo);
    return true;
}

// ----------------------------------------- Menus

void Recebe_texto(char tipo[]){
    char aux[TAM_TEXTO];
    char pause;
    bool ok;

    FILE *arquivo;
    char palavra[100];
    if(strcmp(tipo,"msg")==0){
        printf("\n\nReceber texto para criptografar");
        printf("\n\nDigite o texto: ");
        gets(aux);//GETS :(
        if( strlen(aux) <= TAM_TEXTO){
            strcpy(TEXTO,aux);
            printf("\n\nTexto recebido com sucesso!");
            printf("\n\nCriptografando texto...\n\n");
            ok=true;
        }else{
            printf("\n\nErro!\nTamanho do texto excede o limite de caracteres\n\n");
            ok=false;
            system("pause");
        }
    }else if(strcmp(tipo,"arquivo")==0){
        printf("\n\nInstrucoes para importar um arquivo de texto:");
        printf("\n\n 1 - Renomeie o arquivo para 'descriptografado.txt'");
        printf("\n\n 2 - Copie o arquivo para a pasta arquivos_recebidos");
        printf("\n\n 3 - Feche o explorador e retorne a aplicacao");


        printf("\n\nPressione enter apos colar o arquivo na pasta...\n");
        printf("\n\nImportando arquivo...\n\n");

        arquivo = fopen("arquivos_recebidos\\descriptografado.txt","r");
        if(arquivo==NULL){
             printf("\n\nErro ao abrir o arquivo...\n\n");
        }else{
            while(!feof(arquivo)){
                fscanf(arquivo,"%s",palavra);
                strcat(aux," ");
                strcat(aux,palavra);
            }
            fclose(arquivo);
            if( strlen(aux) <= TAM_TEXTO){
                strcpy(TEXTO,aux);
                printf("\n\nTexto recebido com sucesso!");
                printf("\n\nCriptografando texto...\n\n");

                ok=true;
            }else{
                printf("\n\nErro!\nTamanho do texto excede o limite de caracteres\n\n");
                ok=false;
                system("pause");
            }
        }

    }else{
        printf("\n\nErro ao receber texto\n\n");
    }
    if(ok){
        if(Criptografar()){
            printf("\n\nTexto criptografado com sucesso!");
            arquivo = fopen("arquivos_recebidos\\criptografado.txt","wt");
            if(arquivo==NULL){
                printf("\n\nErro ao criar o arquivo...\n\n");
            }else{
                for(int i=0; i < strlen(TEXTO); i++){
                    fprintf(arquivo,"%d ",TEXTO_CRIPT[i]);
                }
            }
            fclose(arquivo);
        }else{
            printf("\n\nNao foi possivel criptografar o texto!\n\n");
        }

    }
}

void Receber_Arquivo_cript(){
    char pause;
    FILE *arquivo;
    printf("\n\nInstrucoes para importar um arquivo criptografado:");
    printf("\n\n 1 - Renomeie o arquivo para 'criptografado.txt'");
    printf("\n\n 2 - Copie o arquivo para a pasta arquivos_recebidos");
    printf("\n\n 3 - Feche o explorador e retorne a aplicacao\n\n");

    //printf("\n\nPressione enter apos colar o arquivo na pasta...\n");
    system("pause");
    printf("\n\nImportando arquivo...\n\n");
    if(Descriptografar()){
        printf("\n Iniciando descriptografia...\n");
        system("pause");
        system("cls");
        printf("\n%s\n\n",TEXTO);
        arquivo = fopen("arquivos_recebidos\\descriptografado.txt","wt");
        if(arquivo==NULL){
                printf("\n\nErro ao criar o arquivo descriptografado...\n\n");
            }
        fprintf(arquivo,"%s ",TEXTO);
        fclose(arquivo);
        system("pause");

    }else{
        printf("\n Nao foi possivel descriptografar o arquivo!\n\n");
        system("pause");
    }
}

void Menu_Criptografar(){
    int opcao;
    printf("\n\tCriptografia de dados");
    printf("\n\n Criptografar texto ou arquivo");
    printf("\n\n\n 1 - Digitar texto");
    printf("\n\n 2 - Importar arquivo de texto (txt)");
    printf("\n\n 3 - Voltar ao menu principal");
    printf("\n\n Informe a opcao desejada: ");
    scanf("%d", &opcao);
    fflush(stdin);
    switch(opcao){
    case 1:
        system("cls");
        Recebe_texto("msg");
        break;
    case 2:
        system("cls");
        Recebe_texto("arquivo");
        break;
    case 3:
        break;
    default:
        printf("Opcao invalida! Tente novamente...");
    }
}

void Menu(){
    int opcao;
    char chave[500];
    while(1){
        system("cls");
        printf("\n\tCriptografia de dados");
        printf("\n\n 1 - Criptografar texto ou arquivo");
        printf("\n\n 2 - Receber arquivo");
        printf("\n\n 3 - Configurar Chave");
        printf("\n\n 4 - Sair");
        printf("\n\n Informe a opcao desejada: ");
        scanf("%d", &opcao);
        fflush(stdin);
        switch(opcao){
        case 1:
            system("cls");
            Menu_Criptografar();
            break;
        case 2:
            system("cls");
            Receber_Arquivo_cript();
            break;
        case 3:
            system("cls");
            printf("\n\nInforme a chave: ");
            gets(chave);
            if(set_chave(chave)){
                printf("\n\nChave modificada com sucesso!\n");
            }else{
                printf("\n\nChave nao pode ser modificada!");
            }
            system("pause");
            break;
        case 4:
            printf("\nFinalizando...\n\n");
            system("pause");
            exit(0);
            break;
        default:
            printf("Opcao invalida! Tente novamente...");
        }
    }
}

//-----------------------------------------------

int main(int argc, char *argv[]){
    char teste[7];
    char *pteste = teste;
    set_chave("AbCd");
    FILE *arquivo;
    if(argc == 1){
        Menu();
    }
    if(strcmp(argv[1], "--help")==0 || strcmp(argv[1], "-h")==0){
        printf("Use\n-m para criptografar uma mensagem escrita na hora\n"
               "-a para criptografar o arquivo criptografado.txt\n"
               "-d para descriptografar o arquivo descriptografado.txt\n");
        return 0;
    }
    if(argc == 3){
        set_chave(argv[2]);
    }
    if(argc==2){
        if(strcmp(argv[1], "-m")==0){
            Recebe_texto("msg");

        }else if(strcmp(argv[1],"-a")==0){
            Recebe_texto("arquivo");

        }else if(strcmp(argv[1], "-d")==0){
            Receber_Arquivo_cript();
        }
    }
    return 0;
}
