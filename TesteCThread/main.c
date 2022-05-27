#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

bool isLogged = false;
bool isActive = true;
char nameLogged[128];

int checkpoint = 0;
bool Amendous = false;
int counter = 0;
bool flashlight = false; 
bool op3 = false;

//Star Auxiliar function

void clear () { 
	system("clear"); 
}

bool isAccountValid (char * auxname) {
	return (fopen(strcat(auxname, ".txt"), "r") == NULL) ? true : false;
}

bool isPasswordValid (char * accountPassword,  char * currentPassword) {
	return (strcmp(accountPassword, currentPassword) == 0 ? true : false);
}

void clearNameLogged(){
	sprintf(nameLogged, "%s", "");
}

const char *  getRandomAnime(){
	srand(time(NULL));
	int r = rand() % 100;
	FILE *fptr;
	char currentAnime [128] = "";
	static char randomAnime [128] = "";
	fptr = fopen("Animes.txt", "r");
	for(int i = 0; i <= 99; i++){
		fgets(currentAnime, 128, fptr);
		if(i == r){
			strcpy(randomAnime, currentAnime);
		}
	}
	fclose(fptr);
	return randomAnime;
}

const char * fillUnknownAnime(char * currentAnime){ 
	char * receivedAnime = currentAnime; 
	char * unknownAnime[128];
	static char * returnUnknownAnime [128];
	for(int i = 0; i < strlen(currentAnime) - 1; i++){
		strcat(unknownAnime, "_");
	}
	strcpy(returnUnknownAnime, unknownAnime);
	return returnUnknownAnime;
}

bool isLetterValid(char * currentLetter){
	int letter = tolower(currentLetter[0]);
  char minusletter = letter;
    
	return (minusletter >= 'a' && minusletter <= 'z' ? true : false);
}

void printUnknownAnime(char * unknownAnime){
	printf("L ");
	for(int i = 0; i < strlen(unknownAnime); i++){
		printf("%c", unknownAnime[i]);
	}
}

bool isLetterInWord(
	char * currentLetter, 
	char * currentAnime){
	bool isFound = false;
	char * receivedAnime = currentAnime; 
	for(int i = 0; i < strlen(currentAnime); i++){
		if(receivedAnime[i] == currentLetter[0]){
			isFound = true;
		}
	}
	return isFound;
}

//End Auxiliar function

//Star SignUp Function
	void *signUp(void *arg) {
	  char name[128] = "";
		char auxname[128] = "";
		char tempname[128] = "";
	  char password[128] = "";
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
		strcat(auxname, name);
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
	  char name[128] = "";
		char auxname[128] = "";
		char tempname[128] = "";
	  char password[128] = "";
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
		printf("%s\n", name);
		strcat(auxname, name);
		strcat(tempname, name);
		if(!isAccountValid(auxname)){
			FILE *fptr;
			char currentPassword [128];
			fptr = fopen(auxname, "r");
			fgets(currentPassword, 128, fptr);
			fclose(fptr);
			
			if(isPasswordValid(currentPassword, password)){	
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
		clear();
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

//Start Forca Game - Jogo 1
	void *gameForca(void *arg){
		int missCount = 0;
		char *params = (char *)arg;
		bool isGame = true;
		char * currentUnknownAnime = fillUnknownAnime(params);
		printf("%s\n", params);
		printf("%s\n", currentUnknownAnime);
		while(isGame){
			clear();
			printf("--- Jogo da Forca ---\n");
			printf("Erros Restantes: %d\n", missCount);
			switch (missCount)
			{
				case 0:
					printf("________\n");
					printf("|      |\n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printUnknownAnime(currentUnknownAnime);
					printf("\n");
			   	break;
			
			 	case 1:
				 	printf("________\n");
					printf("|      |\n");
					printf("|      O\n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printUnknownAnime(currentUnknownAnime);
					printf("\n");
			   	break;
				
				case 2:
				 	printf("________\n");
					printf("|      |\n");
					printf("|      O\n");
					printf("|      |\n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printUnknownAnime(currentUnknownAnime);
					printf("\n");
			   	break;
				case 3:
				 	printf("________\n");
					printf("|      |\n");
					printf("|      O\n");
					printf("|     /|\n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printUnknownAnime(currentUnknownAnime);
					printf("\n");
			   	break;
				case 4:
				 	printf("________\n");
					printf("|      |\n");
					printf("|      O\n");
					printf("|     /|\\ \n");
					printf("|       \n");
					printf("|       \n");
					printf("|       \n");
					printUnknownAnime(currentUnknownAnime);
					printf("\n");
			   	break;
				case 5:
				 	printf("________\n");
					printf("|      |\n");
					printf("|      O\n");
					printf("|     /|\\ \n");
					printf("|     / \n");
					printf("|       \n");
					printf("|       \n");
					printUnknownAnime(currentUnknownAnime);
					printf("\n");
			   	break;
				case 6:
				 	printf("________\n");
					printf("|      |\n");
					printf("|      O\n");
					printf("|     /|\\ \n");
					printf("|     / \\ \n");
					printf("|       \n");
					printf("|       \n");
					printUnknownAnime(currentUnknownAnime);
					printf("\n");
			
				default:
				isGame = false;
			}
			if(missCount < 6){
				printf("Tentativas erradas restantes: %d \n", missCount);
				bool isLetter = false;
				char letter [128];
				
				while(!isLetter){
					printf("Digite uma Letra(OBS: se digitar mais de uma letra só será considerado a primeira):\n");
					fgets(letter, 128, stdin);
					isLetter = isLetterValid(letter);
				}
				bool isWordComplete = true;
				if(isLetterInWord(letter, params)){
					for(int i=0; i < strlen(params) - 1; i++){
						if( params[i] == letter[0] ){
							currentUnknownAnime[i] = letter[0];
						}
					}
					for(int j=0; j < strlen(params) - 1; j++){
						if( params[j] != currentUnknownAnime[j] ){
							isWordComplete = false;
						}
					}
					isGame = isWordComplete ? false : isGame;
				} else {
					missCount ++;
				}
			} 			
		}
	}
	void callForca(){
		clear();
		pthread_t thread_id;
	  char * string = getRandomAnime();
		printf("%s\n", string);
		
		
	  pthread_create(&thread_id, NULL, gameForca, (void *)string);
	  pthread_join(thread_id, NULL);
	}
//End Forca Game - Jogo 1

//Start Amendous - Jogo 2
void phaseTwo(){
  checkpoint = 4;
  char optionPt[4];
  char key[10];
  
  clear();
  printf("Welcome to the Witching Kingdom\n\n");
  sleep(1);
  printf("You were teleported for the Witching Kingdom, you only saw one sign and one door in the middle of nowhere\n 1 - Check the door\n 2 - Check the sign\n\n\n");
  fgets(optionPt, 4, stdin);
  if(optionPt[0] == '1'){
    printf("Please input the password for entering:\n\n");
    fgets(key, 10, stdin);
    if(key[0] == '1' && key[1] == '3' && key[2] == '4' && key[3] == '3' && key[4] == '4' && key[5] == '0'){
      checkpoint = 5;
      printf("\nYou Entered in the Majestic Land!\n");
      sleep(2);
      printf("Witch arc completed!");
      //call tela inicial
    }
    else{
      printf("Wrong Password, try checking the sign... \n");
      sleep(3);
      phaseTwo();
    }
  }
  else if(optionPt[0] == '2'){
    printf("Ones say it's a Planet, some say it's a Star. We refer formally\n");
    sleep(4);
    phaseTwo();
  }
}

void *phaseOne(void *arg){
  
  clear();
  //printf("c", (char *)arg);
  //printf("CHECKPOINT %d\n\n", checkpoint);
  //printf("COUNTER %d\n\n", counter);
  //printf("AMENDOUS %d\n\n", Amendous);
  //printf("op3 %d\n\n", op3);

  char option[20];
  char option4[4];
  char option41[4];
  char option3[4];
  char option2 [4];
  char option21 [4];
  char option211 [4];
  char option2112 [9];
  
  printf("\nYou were sleeping.. \nYou just woke up cause you heard a really weird noise in your house\nYou are supposed to be alone\n \n \n What do you want to do? \n \n \n 1 - Continue to Sleep \n 2 - Go downstairs to check the noise \n 3 - Turn on the Tv for see the News \n 4 - Check what time is it\n\n\n");
  fgets(option, 20, stdin);
  if(counter == 2){
    
    clear();
    printf("You are really boring, just sleeps, you don't deserve this adventure!\n");
    sleep(5);
    phaseOne(checkpoint);
    //kill();
    }
  else if(option[0] == '1'){
    
    clear();
    printf("\nYou continues to sleep \nYou just woke up in the morning and it's all right, you survived one more day, congratulations!\nYou have worked so hard in your day, now it's time to sleep again.\n");
    counter = counter + 1;
    sleep(3);
    phaseOne(checkpoint);
    
  }
    
  else if (option[0] == '2'){
    
    clear();
    if(Amendous == true){
      checkpoint = 4;
      printf("\nYou hears the sound it's coming from the Kitchen, when you aproaches you can see a powerfull Green light\nYour hands are shaking it's calling for you!\n");
      sleep(5);
      
      clear();
      printf("\n\n It's a Portal Let's s.....\n");
      sleep(4);
      phaseTwo();
    }
    else if(flashlight == true){
      printf("\nIt's really hard to see... \nAll the lights are off, But you have a flashlight!\nYou can see everything, the weird sound seens to be from the kitchen, when you are approaching it you can see a big silhouette...\n\nIt's a THIEF! He does not realizes you are behind him, what you want to do? \n 1 - Calls 190 \n 2 - Take the Knife from the Kitchen\n\n");
      fgets(option2, 4, stdin);
      if(option2[0] == '1'){
        printf("\nYou called 190.. \nNobody answers \nForgot about the Blackout? home phone is not working... \nThe Thief saw you...\n");
        sleep(1);
        printf("A wild Thief Appears!\n 1 - Attack\n 2 - Guard\n 3 - Use Special Ability\n");
        fgets(option21, 4, stdin);
        if (option21[0] == '1'){
          checkpoint = 2;
          printf("You punched him!\nCrital damge!\nDeals 20 damage\n\n");
          sleep(2);
          printf("You knocked him down, Lights turn on\nBlackout has ended\nYou called the police and they make it all right\n");
          sleep(2);
          printf("Congratulations! Thief arc complete!");
          }
        else if (option21[0] == '2'){
          checkpoint = 2;
          printf("You see an weird green energy pulling the thief over, he desapaired in front of your eyes!\n");
          sleep(2);
          printf("Congratulations! Thief arc complete!");
        }
        else if (option21[0] == '3'){
          printf("Cast the Spell: \n");
          fgets(option2112, 9, stdin);
          if(option2112[0] == 'A' && option2112[1] == 'm' && option2112[2] == 'e' && option2112[3] == 'n' && option2112[4] == 'd' && option2112[5] == 'o' && option2112[6] == 'u' && option2112[7] == 's'){ 
            checkpoint = 2; 
            printf("AMENDOUS! The thief is desintegrated...\n");
            sleep(1);
            printf("Thief arc Complete"); 
          }
        }  
      }
      else if(option2[0] == '2'){
        checkpoint = 2;
        printf("\nYou really went to this? Kill the enemy attacking from the back? Well, it's your life, you survived and killed the thief, Congratulations! You've won the Thief Arc\n");
        sleep(3);
        //haseOne(checkpoint);
      }
    }
    else{
      printf("\nIt's really hard to see... \nAll the lights are off, you saw through the window and all houses and light poles are off, unfortunately you will need to carry your path in this way.\n \n \nYou heard the noise again, it's seems to be from the kitchen \n \nYou went to the Kitchen and... \n \n \nYou hear sirens \nYou are in the hospital\nYou... \n \n \n \nGood luck next time!\n");
      sleep(10);
      
      clear();
      phaseOne(checkpoint);
      //usleep(100);
    }
    
  }
    
  else if (option[0] == '3'){
    
    clear();
    if(op3 == true){
      printf("\nYou've already checked the news!\n");
      sleep(3);
      phaseOne(checkpoint);
    }
    printf("\nIn the News: General BlackOut in the City! Prepare your backup lights \nDo You want to take your flashLight? \n 1 - Yes \n 2 - No\n\n");
    fgets(option3, 4, stdin);
    if(option3[0] == '1'){
      op3 = true;
      printf("Wise Choise!\n");
      //
      //system("clear");
      sleep(3);
      flashlight = true;
      phaseOne(checkpoint);
    }
    else if(option3[0] == '2'){
      op3 = true;
      phaseOne(checkpoint);
    }
    
  }
    
  else if (option[0] == '4'){
    
    clear();
  
    printf("\nTime is currently 3:33, or as called, the witching hour, you believe in the tail of the Witches? Choose Carefully.\n 1 - Yes \n 2 - No \n 3 - Tale? \n\n");
    
    fgets(option4, 4, stdin);

    if(option4[0] == '1'){
      printf("\nPlease be carefull\n");
      Amendous = true;
      sleep(2);
      phaseOne(checkpoint);
    }
    else if(option4[0] == '2'){
      Amendous = false;
      printf("\nPlease be extremely carefull\n");
      sleep(2);
      phaseOne(checkpoint);  
    }
    else if(option4[0] == '3'){
      //134340 
      printf("\nThe tale of the W1tches, if you wak3s up in the witching hour, you can aw4ke som3 speci4l Ability, called Amendous if y0u spell that, something can happen, can be good, or can be really bad, it depends on your belief\n Well...\n\n\nDo you Believe in it or not? \n 1 - Yes \n 2 - No\n\n");
      fgets(option41, 4, stdin);
      if(option41[0] == '1'){
        Amendous = true; 
        printf("\nGreat to hear that you believe in it!\n");
        sleep(2);
        phaseOne(checkpoint);
           
      }
      else{
        Amendous = false;
        printf("\nPlease be extremely carefull\n");
        sleep(2);
        phaseOne(checkpoint);
      }
    }
    
  }
}

void callAmendous(){
  pthread_t thread_id;
	char * string = nameLogged;
	printf("%s\n", string);

	pthread_create(&thread_id, NULL, phaseOne, (void *)string);
	pthread_join(thread_id, NULL);

  Amendous = false;
  counter = 0;
  flashlight = false; 
  op3 = false;
  
  clear();
  if(checkpoint == 2){
    printf("\nYou've already won the game in the Thief Arc, try other answers to beat another arc!\n");
    sleep(7);
    phaseOne(checkpoint);
  }
  else if(checkpoint == 0){
    printf("\nThis is a choise based game, depending in what you choose the history can change\n\n\n");
    sleep(7);
    
    clear();
    
    phaseOne(checkpoint);
    //phaseTwo();
  }
   else if(checkpoint == 5){
     printf("\nYou've already won the game in the Witch Arc, try other answers to beat another arc!\n");
    sleep(7);
    
    clear();
    phaseOne(checkpoint);
  }
  
}

//End Amendous - Jogo 2

int main(void) {
	clear();
	char option [20];
	if(isActive){	
		if(isLogged){
			printf("Bem Vindo %s \n", nameLogged);
		}
		printf("Menu \n");
		printf("1 - Login \n");
		printf("2 - Cadastro \n");
		printf("3 - Jogo 1 - Jogo da Forca\n");
		printf("4 - Jogo 2 - Jogo Amendous \n");
		printf("5 - Sair \n");
		printf("6 - Logout \n");
	
		fgets(option, 20, stdin);
		if(option[0] == '1'){
			//call login
			if(!isLogged){
				callLogin();
				main();
			} else {
				printf("Você precisa estar deslogado para logar.");
				main();
			}
		} else if (option[0] == '2'){
			//call signUp
			if(!isLogged){
				callSignUp();
				main();
			} else {
				printf("Você precisa estar deslogado para criar uma conta nova.");
				main();
			}
		} else if (option[0] == '3'){
			//callForca
			if(isLogged){
				callForca();
				main();
			} else {
				printf("Você precisa estar logado para poder jogar.\n");
			}
		} else if (option[0] == '4'){
			//callAmendous
			if(isLogged){
				callAmendous();
      	main();
			} else {
				printf("Você precisa estar logado para poder jogar.\n");
			}
		} else if (option[0] == '5'){
			//call exit
			isActive = false;
			main();
		} else if (option[0] == '6'){
			//call Logout
			if(isLogged){
				// call Logout func
				isLogged = false;
				clearNameLogged();
				main();
			} else {
				//false
				printf("Você precisa estar logado para poder deslogar.\n");
				main();
			}
		} else {
			printf("Digite uma opção válida.");
			main();
		}
	}
	
}