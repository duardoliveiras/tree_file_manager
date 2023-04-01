#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define lenght 16

	typedef struct arvore {
			char info; // p ou a
			char name[lenght];
			struct arvore *r[N];
			struct arvore *pai;

	} Arvore;

	void print_arvore(Arvore* a){

			if(a != NULL){
				int i;
				for(int i=0; i<N; i++){
					if(a->r[i] != NULL){
					  if(a->r[i]->info == 'p')
						printf("%s-\n",a->r[i]->name);

					  else
						printf("%s\n",a->r[i]->name);

					}
				}
			}
	}


	void remova(Arvore* a){
	int i;
	if(a != NULL){
		for(i=0;i<N;i++){
			if(a->r[i] != NULL){
			remova(a->r[i]);
		}
	  }free(a);
	 }else{ printf("comando invalido\n");
		}
	 }

	 void print_caminho(Arvore* a){
		if(a->pai == NULL){
			printf("->");
		}else{
			printf("-%s",a->name);
			print_caminho(a->pai);
		}
		//printf("\n");
	}


	Arvore* cria_Arvore(char i, char nm[lenght], Arvore* pai){
			Arvore *r = (Arvore*)malloc(sizeof(Arvore));
			r->info = i;
			r->pai = pai;
			strcpy(r->name, nm);
			return r;
	}




void copiaStr(char des[], char ori[], int in, int fi){
	int i = 0, tam = strlen(ori);
	while(i+in < tam && i<(fi-in) && ori[i+in] != '\0' && ori[i+in] != '\n'){
		des[i]= ori[i+in];
		i++;
	}
	des[i]='\0';

}

Arvore* buscaArvore(Arvore* a, char par[16]){
	int i = 0;

	    for(i=0;i<N;i++){
	    if(a->r[i] != NULL){
	      if(strcmp(a->r[i]->name,par) == 0){
	      	 return a->r[i];
		  }
		}else { return NULL;}
	}

}


int pos(Arvore* a, char par[16]){
	int i;
	for(i=0;i<N;i++){
	  if(a->r[i] != NULL){
		if(strcmp(a->r[i]->name,par) == 0){
		  return i;

	             }
	           }
   }

}

	int main(){
	Arvore *raiz = NULL, *atual = NULL, *aux = NULL;
	int k;
	char str[20], cmd[3], par[17];
	int i, j,m;
;
	copiaStr(par,"raiz",0,10);
	raiz = cria_Arvore('p',par,NULL);
	atual = raiz;

		Arvore *teste = NULL;

		
		do{	
			fflush(stdin);
			print_caminho(atual);
			fgets(str,20,stdin);
			copiaStr(cmd, str, 0, 2);
			copiaStr(par, str, 3, 16);
			
			if(strcmp(cmd,"ls") == 0){
			    print_arvore(atual);

			}
			else if(strcmp(cmd,"cd") == 0){

			    if(strcmp(par,"..")==0){
					if(atual->pai != NULL)
					atual = atual->pai;
				}
				 else{
					aux = buscaArvore(atual,par);
					if(aux != NULL && aux->info == 'p')
					 atual = aux;

					else{
					printf("comando invalido\n");
					}
				}
			
			}else if(strcmp(cmd,"ma") == 0){
				//criando arquivo

				for(i=0;i<N;i++){
					if(atual->r[i] == NULL){
						atual->r[i] = cria_Arvore('a',par,atual);

						break;
					}else{
					if(strcmp(par,atual->r[i]->name) < 0){
						for(i=0;i<N;i++){
							if(atual->r[i] == NULL){
								m = i;
								break;
							}
						}
						for(j=m-1;j>0;j--){
						atual->r[i+j] = atual->r[i+j-1];
						}
						atual->r[i] = cria_Arvore('a',par,atual);
						break;
					}
				}

				};
			}else if(strcmp(cmd,"mp") == 0){
				//criando pasta

				for(i=0;i<N;i++){
					if(atual->r[i] == NULL){
						atual->r[i] = cria_Arvore('p',par,atual);
						break;
	              }else{
					if(strcmp(par,atual->r[i]->name) < 0){
						m = 0;
						for(i=0;i<N;i++){
							if(atual->r[i] == NULL){
								m = i;
								break;
							}
						}
						for(j=m-1;j>0;j--){
						atual->r[i+j] = atual->r[i+j-1];
						}
						atual->r[i] = cria_Arvore('p',par,atual);
						break;
					}
				}
			  }
			}else if(strcmp(cmd,"rm") == 0){
				  aux = buscaArvore(atual,par);
				  k = pos(atual,par);
				  remova(aux);
				  atual->r[k] = NULL;

			}

			else{
			if(strcmp(cmd,"ex") != 0 && strcmp(cmd,"mp") != 0 && strcmp(cmd,"ma") != 0 && strcmp(cmd,"rm") != 0 &&strcmp(cmd,"ls") != 0 && strcmp(cmd,"cd") != 0){
			printf("comando invalido\n");

				}
				else
				printf("sistema encerrado");
			continue;

			}



		}while(strcmp(cmd,"ex") != 0);


	return 0;
	}


