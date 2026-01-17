
#include "CAP.H"
#include "ELEITOR.H"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(){
// inicializar campos do no cabeca
eleitor *cabecaeleitor = malloc(sizeof(eleitor));
cabecaeleitor->prox = NULL;
 
 // Inicializar lista CAPs
    ListaCaps listaCaps;
        inicializarListaCaps(&listaCaps, MAX_CAPS);
  

    int opcao, subopcao;

    do {
        // Menu Principal
        printf("\n=== BEM-VINDO A SGDE ===\n");
        printf("1. Eleitores\n");
        printf("2. Candidatos\n");
        printf("3. CAPs\n");
        printf("4. Apuracao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Menu Eleitores
                do {
                    printf("\n=== MENU ELEITORES ===\n");
                    printf("1. Inserir eleitor\n");
                    printf("2. Listar eleitores\n");
                    printf("3. Buscar eleitor\n");
                    printf("4. Marcar voto\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &subopcao);

                    switch(subopcao) {
                        case 1: {
                            int id, bi, idcap, prioridade;
                            char nome[50];
                            
                            printf("ID: "); scanf("%d", &id);
                            printf("Nome: ");
                           getchar(); // limpa buffer
                             fgets(nome, sizeof(nome), stdin);
                             nome[strcspn(nome, "\n")] = '\0';// para guardar nome com espacos 
                            printf("BI: "); scanf("%d", &bi);
                            printf("ID CAP: "); scanf("%d", &idcap);
                                       printf("0 - Normal\n");
                                        printf("1 - Idoso\n");
                                        printf("2 - Deficiente\n");
                                         printf("3 - Gravida\n"); 
                                        printf("Escolha: ");
                                        scanf("%d", &prioridade);
                                        if (buscarCAP(&listaCaps, idcap) == NULL) {
                                        printf("Erro: CAP inexistente. Insira primeiro o CAP.\n");
                                          break; 
                                    }

                            if(inserireleitor(cabecaeleitor,&listaCaps, id, nome, bi, idcap,prioridade)){
                             printf("sucedido!");
                            }else{
                                printf("eleitor ja existente ou falha na alocacao!");
                            }
                            
                        
                            break;
                        }
                        case 2:
                            listareleitores(cabecaeleitor);
                            break;
                        case 3: {// buscar eleitor por id
                            int id; 
                            printf("ID do eleitor: "); scanf("%d", &id);
                            eleitor *e = buscareleitor(cabecaeleitor, id);
                            if(e != NULL) printf("Eleitor encontrado: %s\n", e->nome);
                            else printf("Eleitor nao encontrado.\n");
                            break;
                        }
                        case 4: { // marcar q o eleitor ja votou
                            int id; 
                            printf("ID do eleitor: "); scanf("%d", &id);
                            if(marcarvoto(cabecaeleitor, id)){
                               printf("Voto marcado!\n");
                               
                            } else{
                               printf("Erro: eleitor nao encontrado ou ja votou.\n");
                            } 
                            break;
                              
                            
                        }
                    }

                } while(subopcao != 0);
                break;

            case 2:
                printf("Menu Candidatos ainda nao implementado.\n");
                break;

            
                  
             case 3:{ // Menu CAP
              int opcaocap;     
    
    do {
        printf("\n--- Menu CAP ---\n");
        printf("1. Inserir CAP\n");
        printf("2. Listar CAPs\n");
        printf("3. Enfileirar Eleitor em CAP\n");
        printf("4. Desenfileirar Eleitor de CAP\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaocap);

        switch(opcaocap) {
            case 1: {
                int id, numUrnas, maxEleitoresPorUrna;
                char localizacao[50];

                printf("ID do CAP: "); scanf("%d", &id);
                
                        // verificar se já existe CAP com este ID
                        if (buscarCAP(&listaCaps, id) != NULL) {
                           printf("Erro: ja existe um CAP com esse id.\n");
                                  break;
                           }
                getchar(); // limpar buffer
                printf("Localizacao do CAP: "); fgets(localizacao, sizeof(localizacao), stdin);
                localizacao[strcspn(localizacao, "\n")] = '\0'; // remover \n
                printf("Numero de urnas: "); scanf("%d", &numUrnas);
                printf("Maximo de eleitores por urna: "); scanf("%d", &maxEleitoresPorUrna);
                       if (numUrnas <= 0 || maxEleitoresPorUrna <= 0) {
                              printf("Erro: valor invalido.\n");
                                      break;
                                  }

                cap novoCAP = criarCAP(id, localizacao, numUrnas, maxEleitoresPorUrna);
              
               if(inserirCAP(&listaCaps, novoCAP)){
            
                    printf("CAP inserido com sucesso!\n");
              }  
                break;
            }

            case 2: {
                // Lista todos os CAPs existentes
                listarCAPS(&listaCaps);
                break;
            }

            case 3: {
                // Inserir um eleitor na fila de um CAP
                int idCAP, idEleitor;
                printf("ID do CAP: "); scanf("%d", &idCAP);
                printf("ID do Eleitor: "); scanf("%d", &idEleitor);

                cap *capSelecionado = buscarCAP(&listaCaps, idCAP);
                if (capSelecionado == NULL) {
                    printf("CAP nao encontrado!\n");
                    break;
              }
                eleitor *e=buscareleitor(cabecaeleitor,idEleitor);
                if (e== NULL) {
                     printf("erro:Eleitor nao encontrado!\n");
                     break;
                }
                
                if(e->estadovoto==1){
                    printf("erro:Eleitor ja votou.\n");
                    break; //  sai do  e nao coloca na fila e
                }
                
                
                    if (enfileirar(capSelecionado, e)) {
                        printf("Eleitor enfileirado com sucesso!\n");
                    } else {
                        printf("Erro: fila cheia!\n");
                    }
                }
                   break;
            
               
            case 4: {
                // Remover (desenfileirar) o próximo eleitor que votou
                int idCAP;
                printf("ID do CAP: "); scanf("%d", &idCAP);

                cap *capSelecionado = buscarCAP(&listaCaps, idCAP);
                if (capSelecionado == NULL) {
                    printf("CAP nao encontrado!\n");
                } else {
                    
                 eleitor *removido = desenfileirar(capSelecionado);
                    if (removido != NULL) {
                         removido->estadovoto = 1; // MARCA QUE VOTOU
                     printf("Eleitor com ID %d votou e foi removido da fila!\n", removido->id);
                         } else {
                               printf("Fila vazia!\n");
                         }

                }
                break;
            }

            case 5: 
                printf("Voltando ao menu principal...\n");
               
                  break;
    
              
                        default:
                      printf("Opcao invalida!\n");
                   break;

        }

    } while (opcaocap != 5);
    break;
}


             case 4:
                printf("Menu Apuracao ainda nao implementado.\n");
                break;
        }

    } while(opcao != 0);
   
    printf("Saindo do sistema...\n");
    return 0;


}































