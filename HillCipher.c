/*=============================================================================
| Assignment: Encrypting a plaintext file using the Hill cipher
|
| Author: Paul Seitner
| Language: c 
|
| To Compile: gcc -o pa01 pa01.c
| 
|
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//this functions brings in a vector of the matrix size and computes the algebra for the first letter 
// in the ciphertext using the first row of the matrix key. Does one letter at a time.
void matrixMultiplication(char vector[],int matrixKey[],int keyMatrixSize)
{
  int letter = 0;
  // the look evenly goes through the vector adding them all total 
  for(int i=0 ; i < keyMatrixSize ; i++)
  {
   letter += (vector[i]-'a') * matrixKey[i];
  }
  // prints every letter modules 26
  printf("%c",letter % 26 + 'a' );
}

int main(int argc, char**file) {

  // console arguements 
    char *arguement1 = file[1];
    char *arguement2 = file[2];
    FILE *inputKey = fopen(arguement1,"r");
    FILE *inputString = fopen(arguement2,"r");

  //These check if there were any errors when opening the files
  if(inputKey == NULL ){
  printf("failed to open files.\n");
    return 1;
  }
  if(inputString == NULL ){
  printf("failed to open files.\n");
    return 1;
  }

  char plaintext[10000];
  int keySize;
  
  fscanf(inputKey,"%d",&keySize);

  int matrixKey[keySize][keySize];
  // scanning for the 2d array of the key martix
  for(int i =0;i <keySize; i++)
  {
    for(int j=0;j<keySize; j++)
    {
      fscanf(inputKey,"%d",&matrixKey[i][j]);
    }
  }
  // printing from the input key file
  printf("\nKey matrix:\n");
  for(int i =0;i <keySize; i++)
  {
    for(int j=0;j<keySize; j++)
    {
      printf("   %d",matrixKey[i][j]);
    }
    printf("\n");
  }

  // Below is used to get the input file and convert in into plaintext with padding of x's if its not modules = 0 with the matrix
  
  //fgets to get the whole string used 10000 due to requirements
  fgets(plaintext,10000,inputString);

  int letterIndex = 0;
  int letter;
  printf("%s",plaintext);
  // this loop goes through the same after fgets and converts only the letters to lower case.
  // isalpha is used to check if its in the alphbet and tolower is used to convert uppercase letters to lowercase
  for(letter = 0; letter <strlen(plaintext); letter++)
  {
    if(isalpha(plaintext[letter]))
    {
      plaintext[letterIndex++] = tolower(plaintext[letter]);    
    }
  }

  // pads the string to make sure its % = 0 with the size of matrix
  while(letterIndex % keySize != 0)
  {
    plaintext[letterIndex++] = 'x';
  }
  // make sure that the rest of the string is gone after the changes. making it the end of the string using '\0'
  plaintext[letterIndex] ='\0';

// Printing plaintext from above
  printf("\nPlaintext:\n");
  letter = 0;
  int formatPlaintext= 0;
  for(letter = 0 ; letter < strlen(plaintext) ; letter++)
  {
    printf("%c",plaintext[letter]);
    formatPlaintext++;

    // formats 80 characters per line 
    if(formatPlaintext >79)
    {
      printf("\n");
      formatPlaintext = 0;
    }
      
  }
  
  printf("\n");

  int counter=0;
  char vector[keySize];
  int formatCipherText = 0;
  // this prints the ciphertext using a vector to grab the size of the matrix within the plaintext string.
  // 
  printf("\nCiphertext:\n");
  for(int i = 0; i < strlen(plaintext) ; i += keySize)
  {
    for(int j = 0 ; j < keySize ; j++)
    {
      vector[j] = plaintext[counter++];
    }

    // you have to have another for loop for every letter in the vector.
    for(int k = 0;k<keySize;k++)
    {
      // calling a function makes it easier to sort since it does one row at a time.
      matrixMultiplication(vector, matrixKey[k], keySize);

      // formatting for 
      formatCipherText++;
      if(formatCipherText > 79)
      {
        printf("\n");
        formatCipherText = 0;
      }
    }
  }

printf("\n");  
fclose(inputKey);
fclose(inputString);
  
return 0;
}

