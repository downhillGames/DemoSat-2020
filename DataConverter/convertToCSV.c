/*
============================================================================
Name        : loremIpsum.c
Author      : Tyler Schmidt
Class       : CS 2060 SEC 01
Description : Basic File I/O
Date        : 02/22/18
============================================================================
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_WORD_LEN 10000
#define MAX_LINE_LEN 10000

//first page (checkout)
#define dataTXT "data.txt"
#define dataCSV "data.csv"
#define dataAppend "data_append.txt"

//prototypes
int wordCount(FILE *fp);
int charCount(FILE *fp);
int sendContentTo(FILE *fp, FILE *out);
int getWordAt(FILE *fp, int pos, char *word);
int appendToFile(char *fileName, char*newText);

//main function
int main(void)
{
    //strings to append
	replaceFile();
	char append[1000] ="UV_1_A, UV_1_B, UV_1_COMP_1, UV_1_COMP_2, UV_1_INDEX, UV_2_A, UV_2_B, UV_2_COMP_1, UV_2_COMP_2, UV_2_INDEX, UV_3_A, UV_3_B, UV_3_COMP_1, UV_3_COMP_2, UV_3_INDEX, UV_4_A, UV_4_B, UV_4_COMP_4, UV_4_COMP_4, UV_4_INDEX, ALTITUDE, TEMP, TIMESTAMP  \n";
    appendPHP(dataAppend, dataCSV, append);
	return 0;
}


// Read content from file one line (crlf) at a time.
// Send content to output one line at a time.
// Returns number of lines processed.
int sendContentTo(FILE *in, FILE *out)
{
	fprintf(stdout, "Performing file copy...\n\n");

	//start at the beginning of the file
	rewind(in);
	fseek(in, 0L, SEEK_SET);
	// array to hold one line of text up to 1000 characters
	char line[MAX_LINE_LEN];

	// Start out assuming input
	// file contains ZERO lines.
	int lineCount = 0;
    //fgets(line, MAX_LINE_LEN, in);


	// read one line at a time from our input file
	while (fgets(line, MAX_LINE_LEN, in) != NULL)
	{
        char oldWord0[] = "HI";
        char oldWord1[] = "UV_1_A ";
        char oldWord2[] = "UV_1_B ";
        char oldWord3[] = "UV_1_COMP1 ";
        char oldWord4[] = "UV_1_COMP2 ";
        char oldWord5[] = "UV_1_INDEX ";

        char oldWord6[] = "UV_2_A ";
        char oldWord7[] = "UV_2_B ";
        char oldWord8[] = "UV_2_COMP1 ";
        char oldWord9[] = "UV_2_COMP2 ";
        char oldWord10[] = "UV_2_INDEX ";

        char oldWord11[] = "UV_3_A ";
        char oldWord12[] = "UV_3_B ";
        char oldWord13[] = "UV_3_COMP1 ";
        char oldWord14[] = "UV_3_COMP2 ";
        char oldWord15[] = "UV_3_INDEX ";

        char oldWord16[] = "UV_4_A ";
        char oldWord17[] = "UV_4_B ";
        char oldWord18[] = "UV_4_COMP1 ";
        char oldWord19[] = "UV_4_COMP2 ";
        char oldWord20[] = "UV_4_INDEX ";

        char oldWord21[] = "Altitude";
        char oldWord22[] = "timestamp";
        char oldWord23[] = "Temp";
        char oldWord24[] = ";";
        char newWord[] = "";
        replaceAll(line, oldWord0, newWord);
        replaceAll(line, oldWord1, newWord);
        replaceAll(line, oldWord2, newWord);
        replaceAll(line, oldWord3, newWord);
        replaceAll(line, oldWord4, newWord);
        replaceAll(line, oldWord5, newWord);
        replaceAll(line, oldWord6, newWord);
        replaceAll(line, oldWord7, newWord);
        replaceAll(line, oldWord8, newWord);
        replaceAll(line, oldWord9, newWord);
        replaceAll(line, oldWord10, newWord);
        replaceAll(line, oldWord11, newWord);
        replaceAll(line, oldWord12, newWord);
        replaceAll(line, oldWord13, newWord);
        replaceAll(line, oldWord14, newWord);
        replaceAll(line, oldWord15, newWord);
        replaceAll(line, oldWord16, newWord);
        replaceAll(line, oldWord17, newWord);
        replaceAll(line, oldWord18, newWord);
        replaceAll(line, oldWord19, newWord);
        replaceAll(line, oldWord20, newWord);
        replaceAll(line, oldWord21, newWord);
        replaceAll(line, oldWord22, newWord);
        replaceAll(line, oldWord23, newWord);
		//send line we just read to output.
		fprintf(out, "%s",  line);
        fprintf(stdout, "%s",  line);
		//count the lines
		lineCount++;
	}

	fprintf(stdout, "\nFinished line PHP Append.\n");
	fprintf(stdout, "Count is: %d.\n\n", lineCount);

	// Return how many text lines
	// we've processed from input file.
	return lineCount;
}

// Read content from file one character at a time.
// Returns number of total characters read from the file.
//Problem #2
int charCount(FILE *fp)
{
	fprintf(stdout, "Performing char count...\n\n");
	unsigned int ch;
	rewind(fp);

	int charCount = 0;

	while ((ch = getc(fp)) != EOF)
	{


		putc(ch, stdout);

		//count the char
		charCount++;
	}

	fprintf(stdout, "\nFinished char count.\n");
	fprintf(stdout, "Count is: %d.\n\n", charCount);
	return charCount;
}


// Read content from file one word at a time.
// Returns number of total words read from the file.
int wordCount(FILE *fp)
{
	fprintf(stdout, "Performing word count...\n\n");

	rewind(fp);

	char word[MAX_WORD_LEN];
	int wordCount = 0;

	while (fscanf(fp, "%s", word) == 1)
	{
		// Send entire word string
		// we just read to console
		puts(word);

		//count the word
		wordCount++;
	}

	fprintf(stdout, "\nFinished word count.\n");
	fprintf(stdout, "Count is: %d.\n\n", wordCount);
	return wordCount;
}


void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[MAX_LINE_LEN];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);


    /*
     * Repeat till all occurrences are replaced.
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word
        strcat(str, newWord);

        // Concatenate str with remaining words after
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}



//Problem #4
int appendToFile(char *fileName, char*newText)
{
    fprintf(stdout, "Performing file append...\n\n");
	fprintf(stdout, "Appending: %s\n\n", newText);
	//open using "append " rights
	FILE *file = fopen(fileName, "ab");

	fputs(newText,file);
	fclose(file);

	return 0;

}

void appendPHP(char *inputFile, char *outputFile, char*newText)
{
   FILE *fp;
	FILE *out = fopen(outputFile, "wb+");
	//appended text

	char word[MAX_WORD_LEN];
	// open Lorem ipsum.txt for read.
	if ((fp = fopen(inputFile, "rb+")) == NULL)
	{
		fprintf(stdout, "Can't open %s file.\n", inputFile);
		exit(EXIT_FAILURE);
	}
	rewind(fp);
	rewind(out);
    fprintf(out, newText);
	int copyFile = sendContentTo(fp, out); //copy text file (Problem #1)

	//close first file
	fclose(out);
	if (fclose(fp) != 0)
		fprintf(stderr, "Error closing file\n");
	FILE *outAppend = fopen(outputFile, "rb+");
	fclose(outAppend);
}



void replaceFile(){
	char ch;

    /* Pointer for both the file*/
    FILE *fpr, *fpw;
    /* Opening file FILE1.C in “r” mode for reading */
    fpr = fopen(dataTXT, "r");

    /* Ensure FILE1.C opened successfully*/
    if (fpr == NULL)
    {
         puts("Input file cannot be opened");
    }

    /* Opening file FILE2.C in “w” mode for writing*/
    fpw= fopen(dataAppend , "w");

    /* Ensure FILE2.C opened successfully*/
    if (fpw == NULL)
    {
       puts("Output file cannot be opened");
    }

    /*Read & Write Logic*/
    while(1)
    {
        ch = fgetc(fpr);
        fprintf(stdout, "Character: %c \n", ch);
        if (ch==EOF)
            break;
	else if (ch==';'){
	    ch = fgetc(fpr);
	    fputc('\n', fpw);
	}
        else
            fputc(ch, fpw);
    }

    /* Closing both the files */
    fclose(fpr);
    fclose(fpw);
}

//Problem #3
int getWordAt(FILE *fp, int pos, char *word)
{
	printf(stdout, "Performing word count...\n\n");

	rewind(fp);

	char wordA[MAX_WORD_LEN];
	int wordCount = 0;

	while (fscanf(fp, "%s", wordA) == 1 && wordCount < pos)
	{
		// Send entire word string
		// we just read to console
		puts(wordA);

		//count the word
		wordCount++;
	}
	word = wordA;
	fprintf(stdout, "\nFinished finding word\n");
	fprintf(stdout, "The word is: %s.\n\n", wordA);

	return 0;
	}
