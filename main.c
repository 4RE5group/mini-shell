#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#define false 0
#define true 1

// colors
#define COLOR_GREEN "\e[0;32m"
#define COLOR_RESET "\e[0m"
#define COLOR_RED   "\e[0;31m"



const char** splitCmd(char* input, int size) {
   int isInQuotes=false;
   int arg = 0;
   int charpos = 0;
   char** output = malloc(size * sizeof(char*));

   if(output == NULL || input == NULL) {
      printf("error: allocation\n");
      return NULL;
   }

   output[0] = malloc(size * sizeof(char*));

   for(int i=0; i<strlen(input); i++) {
//      printf("%s", input[i]);
      if(input[i] == '"' || input[i] == '\'') {
         isInQuotes = !isInQuotes;
      }
      else if(input[i] == ' ') {
          if(isInQuotes) {
             output[arg][charpos] = ' ';
             charpos++;
          }
          else {
//             output[arg][charpos+1] = '\r';
             charpos=0;
             arg++;
             output[arg] = malloc(size * sizeof(char*));
          }
      } else {
         output[arg][charpos] = input[i];
         charpos++;
      }
   }
   return output;
}


int main(int argc, char* argv[]) {
   printf("     MINI SHELL    \n");
   printf("type help to get list of commands\n");


   char pwd[255];
   if (getcwd(pwd, sizeof(pwd)) == NULL) {
       perror("getcwd() error");
       return 1;
   }

   char rpwd[255] = "~";
   char inCmd[1024];

   while(1) {
        printf("%s%s%s $ ", COLOR_GREEN, pwd, COLOR_RESET);
        fgets(inCmd, sizeof(inCmd), stdin);


        //remove endline char
        inCmd[strlen(inCmd)-1] = '\0';

        const char** outputArgs = splitCmd(inCmd, 64);

        if(!strcmp(outputArgs[0], "exit")) {
           return 0;
        } else if(!strcmp(outputArgs[0], "help")) {
           printf("MINI SHELL\n");
           printf("available commands: \n");
           printf("help    - display this list\n");
           printf("pwd     - print parent working directory\n");
           printf("exit    - quit mini shell\n");
        } else if(!strcmp(outputArgs[0], "pwd")) {
           printf("%s\n", pwd);
        } else {
           printf("%sunrecognized command: %s%s\n", COLOR_RED, outputArgs[0], COLOR_RESET);
        }
        free(outputArgs);
   }
}