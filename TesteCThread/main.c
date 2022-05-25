#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

bool isLogged = false;
bool isActive = true;
char nameLogged[128];

//Star Auxiliar function

void clear () { 
	system("clear"); 
}

bool isAccountValid (char * name) {
	return (fopen(strcat(name, ".txt"), "r") == NULL) ? true : false;
}

bool isPasswordValid (char * accountPassword,  char * currentPassword) {
	printf("%s\n", accountPassword);
}
//End Auxiliar function

//Star SignUp Function
	void *signUp(void *arg) {
	  char name[128];
		char tempname[128];
	  char password[128];
	  int count = 0;
	  bool flag = false;
	
	  char *params = (char *)arg;
		char * stringPassword = "";
		for(int i = 0; i < strlen(params); i++){
	    if (flag){
	      password[count] = params[i];
	      count++;
	    }else{
	      if (params[i] == ';'){
	        flag = true;
	        count = 0;
	      }else{
	        name[count] = params[i];
	        count++;
	      }
	    }
		}
		strcat(tempname, name);
		if(isAccountValid(name)){
			FILE *fptr;
			fptr = fopen(name, "w+");
			fputs(password, fptr);
			fclose(fptr);
	
			printf("Conta criada com sucesso.\n");
			strcat(nameLogged, tempname);
			isLogged = true;
		} else {
			printf("Conta já existente.\n");
		}
	}
	
	void callSignUp (){
		clear();
		pthread_t thread_id;
	  char string[30] = "default";
		char stringPassword[30] = "default";
		char autenticateString[60] = "";
		
		printf("--- CADASTRO ---\n");
		printf("Login:\n");
	  fgets(string, 30, stdin);
		printf("Password:\n");
		fgets(stringPassword, 30, stdin);
	  for (int i = 0; i<strlen(string); i++){
	    if (string[i] == '\n'){
	      string[i] = '\0';
	    }
	  }
	  for (int i = 0; i<strlen(stringPassword); i++){
	    if (stringPassword[i] == '\n'){
	      stringPassword[i] = '\0';
	    }
	  }
		strcat(string, ";");
		strcat(string, stringPassword);
		
	  pthread_create(&thread_id, NULL, signUp, (void *)string);
	  pthread_join(thread_id, NULL);
	}
//End SignUp Function

//Star Login Function
	void *autenticateLogin(void *arg) {
	  char name[128];
		char tempname[128];
	  char password[128];
	  int count = 0;
	  bool flag = false;
	
	  char *params = (char *)arg;
		char * stringPassword = "";
		for(int i = 0; i < strlen(params); i++){
	    if (flag){
	      password[count] = params[i];
	      count++;
	    }else{
	      if (params[i] == ';'){
	        flag = true;
	        count = 0;
	      }else{
	        name[count] = params[i];
	        count++;
	      }
	    }
		}
		strcat(tempname, name);
		if(!isAccountValid(name)){
			char currentPassword;
			FILE *fptr;
			fptr = fopen(name, "r");

			currentPassword = fgetc(fptr);
			
			fclose(fptr);
			printf("%s \n", &currentPassword);
			
			if(isPasswordValid(&currentPassword, password)){	
				printf("Login realizado com sucesso.\n");
				strcat(nameLogged, tempname);
				isLogged = true;
			} else {
				printf("Senha Inválida.\n");
			}
		} else {
			printf("Login ou Password incorretos tente novamente ou cadastre-se.\n");
		}
	}
	
	void callLogin(){
		//clear();
		pthread_t thread_id;
	  char string[30] = "default";
		char stringPassword[30] = "default";
		char autenticateString[60] = "";
		
		printf("--- Login ---\n");
		printf("Login:\n");
	  fgets(string, 30, stdin);
		printf("Password:\n");
		fgets(stringPassword, 30, stdin);
	  for (int i = 0; i<strlen(string); i++){
	    if (string[i] == '\n'){
	      string[i] = '\0';
	    }
	  }
	  for (int i = 0; i<strlen(stringPassword); i++){
	    if (stringPassword[i] == '\n'){
	      stringPassword[i] = '\0';
	    }
	  }
		strcat(string, ";");
		strcat(string, stringPassword);
		
	  pthread_create(&thread_id, NULL, autenticateLogin, (void *)string);
	  pthread_join(thread_id, NULL);
	}
//End Login Function

int main(void) {
	//clear();
	char option [20];
	if(isActive){	
		if(isLogged){
			printf("Bem Vindo %s \n", nameLogged);
		}
		printf("Menu \n");
		printf("1 - Login \n");
		printf("2 - Cadastro \n");
		printf("3 - Jogo 1 - Jogo da Forca\n");
		printf("4 - Jogo 2 - Jogo do Augusto \n");
		printf("5 - Sair \n");
		printf("6 - Logout \n");
	
		fgets(option, 20, stdin);
		if(option[0] == '1'){
			//call login
			callLogin();
			main();
		} else if (option[0] == '2'){
			//call signUp
			callSignUp();
			main();
		} else if (option[0] == '3'){
			//
		} else if (option[0] == '4'){
			//
		} else if (option[0] == '5'){
			//call exit
			isActive = false;
			main();
		} else if (option[0] == '6'){
			//call Logout
			if(isLogged){
				// call Logout func
				isLogged = false;
			} else {
				//false
				printf("Você precisa estar logado para poder deslogar.");
			}
		} else {
			printf("Digite uma opção válida.");
			main();
		}
	}
	
}