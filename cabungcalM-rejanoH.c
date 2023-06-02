/*********************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The
program was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
 Mary Joselle Cabungcal, DLSU ID# 12149020
 Hans Martin Rejano, DLSU ID# 12107884
*********************************************************************************************************/

/*
This program is tasked to create some language tools that are related to each other: machine translation 
and language identification. It also manages the collection of words as language and translation pairs that will be used.

NOTE: This code is the improved version of both individual's solution, which means some functions of the other was
used altogether.
*/

#include "mpheader.h"

/**
 * getPair() gets a string input for a Language and a Translation
 *
 * @param sLang - pointer to a string containing 1 word
 * @param sTrans - pointer to a string containing 1 word
 * Pre-condition: at least 1 character and at most 20. No space to be included in each word 
 */
void getPair( String20 *sLang, 
              String20 *sTrans)
{
  printf("\nEnter a language: ");
  scanf("%s", *sLang);
  printf("Enter a translation: ");
  scanf("%s", *sTrans);
}

/**
 * checkPair() checks if the language and translation pair exists in the entry
 * 
 * @param entry the array of structs
 * @param n the index of the entry in the array
 * @param sLang The language of the translation
 * @param sTrans The translation of the word
 * 
 * @return 1 if Language and Translation are found, return 2 if only language is found, 
 *         and return 0 if none are found
 */
int checkPair(struct entryTag entry[], 
              int n, 
              String20 sLang, 
              String20 sTrans)
{
  int i;

  for (i = 0; i < entry[n].nPair; i++)
  {
    if (strcmp(sLang, entry[n].sPair[i].pLanguage) == 0 &&
        strcmp(sTrans, entry[n].sPair[i].pTranslation) == 0) //checks if pair exists
    {
      return 1; //found
    }

    else if (strcmp(sLang, entry[n].sPair[i].pLanguage) == 0) //checks if language only exists
      return 2; //found
  }
  return 0; //not found
}

/**
 * addPair() asks for a pair input and checks if the language exists, and if it
 * doesn't, it adds the language-translation pair to the entry. It also modifies
 * the number of pairs in the entry. This function is used in addEntry function
 * 
 * @param entry the array of structs
 * @param n the number of entries in the array
 */
void addPair( struct entryTag entry[], 
              int n)
{
  char cDump1, cOpt;
  String20 sLanguage, sTranslation;

  do
  {
    printf("\nAdd another Language-Translation pairs to the entry? [Y/N] ");
    scanf("%c%c", &cDump1, &cOpt);
    if (cOpt == 'Y' || cOpt == 'y')
    {
      getPair(&sLanguage, &sTranslation);

      if (checkPair(entry, n, sLanguage, sTranslation) == 2 ||
          checkPair(entry, n, sLanguage, sTranslation) == 1) //if pair is found
        printf("LANGUAGE ALREADY EXISTS\n"); 
      
      else
      {
        strcpy(entry[n].sPair[entry[n].nPair].pLanguage, sLanguage); //copy sLanguage to the entry
        strcpy(entry[n].sPair[entry[n].nPair].pTranslation, sTranslation); //copy sTranslation to the entry
        entry[n].nPair++; //increment number of pairs in the entry
      }
    }
  } while ((cOpt == 'Y' || cOpt == 'y') && entry[n].nPair < 10); //checking if no. of pairs is within 10

  if (entry[n].nPair == 10) //if already max number of pairs
    printf("No additional pairs can be added.\n");
}

/**
 * addPair2() adds a language-translation pair to an entry.
 * Used in addTranslation function
 * 
 * @param entry the array of structs
 * @param n the number of entries in the array
 */
void addPair2(struct entryTag entry[], 
              int n)
{
  char cDump1, cOpt;
  String20 sLanguage, sTranslation;

  do
  {
    getPair(&sLanguage, &sTranslation); //gets a language-translation pair
    if (checkPair(entry, n, sLanguage, sTranslation) == 2 ||
        checkPair(entry, n, sLanguage, sTranslation) == 1) //checks if pair exists
      printf("LANGUAGE ALREADY EXISTS\n");
  
    else //if pair doesn't exist, store the sLanguage and sTranslation to the array
    {
      strcpy(entry[n].sPair[entry[n].nPair].pLanguage, sLanguage);
      strcpy(entry[n].sPair[entry[n].nPair].pTranslation, sTranslation);
      entry[n].nPair++; //increment number of pairs
    }

    printf("\nAdd another Language-Translation pairs to the entry? [Y/N]: "); //ask user again
    scanf("%c%c", &cDump1, &cOpt);
  } while ((cOpt == 'Y' || cOpt == 'y') && entry[n].nPair < 10);

  if (entry[n].nPair == 10) //if max num of pairs reached
    printf("No additional pairs can be added.\n");
}

/**
 * addEntry() prompts the user for a language and translation pair, 
 * checks if the pair already exists in the structure, and if it doesn't, adds it to the array
 * 
 * @param entry array of structs
 * @param *n pointer to number of entries
 */
void addEntry(struct entryTag entry[], 
              int *n)
{
  String20 sLanguage, sTranslation;
  int i, j,
      k = 0,
      l = 0,
      nPrompt = 0;
  char cOpt = ' ', //initializd as space 
       cDump1;

  printf("\n[ADD ENTRY]\n");
  getPair(&sLanguage, &sTranslation); //gets a language-translation pair

  // Checking for existing L-T pair
  for (i = 0; i < *n; i++) 
  {
    if (checkPair(entry, i, sLanguage, sTranslation) == 1) 
    {
      k++;
      printf("\nEntry[%d]\n", k);

      for (j = 0; j < entry[i].nPair; j++) //displays existing pair that contains a similar L-T pair
        printf("%s: %s\n", entry[i].sPair[j].pLanguage, entry[i].sPair[j].pTranslation);
      
      nPrompt++; //counter
    }
  }

  l = *n;
  if (nPrompt > 0)
  {
    printf("Is this a new entry? [Y/N] "); //only asks if there is an existing pair in the array
    scanf("%c%c", &cDump1, &cOpt);
  }

  if (cOpt == ' ' ||
      cOpt == 'Y' || cOpt == 'y')
  {//copy sLanguage and sTranslation to the entry
    strcpy(entry[l].sPair[entry[l].nPair].pLanguage, sLanguage);
    strcpy(entry[l].sPair[entry[l].nPair].pTranslation, sTranslation);
    entry[l].nPair++; //increment number of pairs
    *n += 1; //increment number of entries
    addPair(entry, l); //gets more L-T pairs
  }
}

/**
 * addTranslation() adds a language-translation pair to an existing entry
 * 
 * @param entry an array of structs
 * @param n number of entries
 */
void addTranslation(struct entryTag entry[], 
                    int n)
{
  struct entryTag eTemp[150]; //temp
  String20 sLanguage, sTranslation; //temp variable for L-T pair
  int eKeys[150]; //array of indices where the L-T pair was found
  int i, j = 0, k = 0;
  int count = 0;
  int key, nOpt;

  printf("\n[ADD TRANSLATION]\n");
  getPair(&sLanguage, &sTranslation); //gets a L-T pair
  printf("\n");

  for (i = 0; i < n; i++) 
  {
    if (checkPair(entry, i, sLanguage, sTranslation) == 1)//checks if there are similar entries containing the input L-T pair
    {
      eTemp[j] = entry[i]; //stores found entries to temp
      eKeys[k] = i; //stores the index where LT pair was found
      k++;
      j++; //increment index for eTemp
      count++; //increment counter
      key = i; //assign index to key if only one entry found
    }
  }

  if (count > 0) //if more than 1 entries, display the entries information
    displayEntry(eTemp, count);

  if (count == 0) //if no entries are found
  {
    printf("The entry entered does not exist.\n");
    printf("Please use Add Entry option first.\n");
  }

  else if (count == 1) //only 1 entry found 
  {
    if (entry[key].nPair == 10)//if already at max no. of pairs
      printf("Maximum number of translations reached\n");

    else
      addPair2(entry, key); //gets pairs
  }

  else if (count > 1) //if more than 1 entries found
  {
    do
    {
      printf("Which entry would you like to add a pair?: ");//ask user the entry number
      scanf("%d", &nOpt);
      if(nOpt <= count && nOpt > 0)
      {
        if (entry[eKeys[nOpt-1]].nPair == 10)//check if number of pairs reached 10
          printf("Max # of translations reached.\n");

        else
          addPair2(entry, eKeys[nOpt-1]); //ask for pairs 
      }

      else
        printf("Invalid input\n");

    } while (nOpt > n);
  }
}

/**
 * modifyEntry() allows the user to modify an entry in the array
 * 
 * @param entry array of structs
 * @param *n pointer to number of entries
 */
void modifyEntry( struct entryTag entry[], 
                  int *n)
{
  int i;
  int nOpt = 1,
      nOpt2;
  char cOpt, 
       cDump,
       cOpt2;
  String20 sLanguage, sTranslation; //temp variable for L-T pair
  
  printf("\n[MODIFY ENTRY]\n\n");
  displayEntry(entry, *n); //displays all entries information
  if (*n > 1)//if more than 1 entry ask the index number
  {
    printf("Which entry would you like to modify?: ");
    scanf("%d", &nOpt);
  }
  printf("\n");

  if (nOpt > *n || nOpt < 1) //if input is more than the entry number
    printf("Invalid input.\n");

  else
  {
    do
    {
      for (i = 0; i < entry[nOpt - 1].nPair; i++)
        printf("[%d] %s: %s\n", i + 1, entry[nOpt - 1].sPair[i].pLanguage, 
                                entry[nOpt - 1].sPair[i].pTranslation); //displays the L-T pairs of selected entry
      do
      {
        printf("What Pair# would you like to modify?: ");
        scanf("%d", &nOpt2); //asks user what pair number it wishes to modify
      } while (nOpt2 > entry[nOpt - 1].nPair || nOpt2 < 1); //checks for a valid input

      do
      {
        printf("Modify [L]anguage or [T]ranslation?: ");
        scanf(" %c", &cOpt); //asks user what it wants to modify
      } while ((cOpt != 'L' && cOpt != 'l') &&
               (cOpt != 'T' && cOpt != 't')); //checks for a valid input

      if (cOpt == 'L' || cOpt == 'l') //if language was chosen
      {
        printf("\nEnter language:");
        scanf("%s", sLanguage); 
        if(checkPair(entry, nOpt-1, sLanguage, sTranslation) == 0) //check if pair does not exist
          strcpy(entry[nOpt - 1].sPair[nOpt2 - 1].pLanguage, sLanguage);

        else //if pair exists
          printf("LANGUAGE ALREADY EXISTS!\n");
      }

      else if (cOpt == 'T' || cOpt == 't') //if translation was chosen
      {
        printf("\nEnter translation:");
        scanf("%s", entry[nOpt - 1].sPair[nOpt2 - 1].pTranslation);
      }

      printf("\nDo you want to modify another pair in this entry? [Y/N] ");
      scanf(" %c%c", &cOpt2, &cDump); //ask user again
    } while (cOpt2 == 'Y' || cOpt2 == 'y');
  }
}

/**
 * deleteEntry() deletes an entry from the array of structs by replacing the 
 * entry to be deleted with the last entry in the array, then decrementing 
 * the number of entries in the array. It also deletes the contents of the entry.
 * 
 * @param entry array of structs
 * @param *n pointer to number of entries in the array
 * @param key the index of the entry to be deleted
 * 
 * Pre-condition: Deletes only one entry.
 */
void deleteEntry( struct entryTag entry[], 
                  int *n, 
                  int key)
{
  int i, j;

  for (i = 0; i < *n; i++) //checks all entries
  {
    if ((key - 1) == i) //if index is found
    {
      entry[i] = entry[*n - 1]; //replace deleted entry with the last entry

      for(j = 0; j < entry[*n - 1].nPair; j++)
      {
        entry[*n - 1].sPair[j].pLanguage[0] = '\0';
        entry[*n - 1].sPair[j].pTranslation[0] = '\0';
      }

      entry[*n - 1].nPair = 0; // set no. of pairs back to 0
      *n -= 1;                 // decrement entryNum
      i = *n + 1;              // ends loop
    }
  }
}

/**
 * deleteTranslation() to delete a pair of a word and its translation.
 * 
 * @param entry the array of structs
 * @param *n pointer to number of entries
 */
void deleteTranslation( struct entryTag entry[], 
                        int *n)
{
  int i;
  int nOpt, nOpt2;
  char cDump;
  char cOpt2;

  printf("\n[DELETE TRANSLATION]\n\n");
  //nOpt = 1; 
  displayEntry(entry, *n); //displays all entries information

  if (*n > 1) //if number of entries is more than 1
  {
    printf("Which entry would you like to delete a pair?: ");
    scanf("%d", &nOpt); //asks user for an index
  }

  printf("\n");
  if (nOpt > *n || nOpt < 1) //if input is more than number of entries or input is less than 1
    printf("Invalid input.\n");
    
  else
  {
    do
    {
      for (i = 0; i < entry[nOpt - 1].nPair; i++)
        printf("[%d] %s: %s\n", i + 1,entry[nOpt - 1].sPair[i].pLanguage, 
                                      entry[nOpt - 1].sPair[i].pTranslation); //displays selected entry's information
      
      printf("What Pair# would you like to delete?: ");
      scanf("%d", &nOpt2); //asks user for the pair's index to delete

      if (nOpt2 > entry[nOpt - 1].nPair || nOpt2 < 1) //if input is more than number of pairs or input is less than 1
        printf("Invalid input\n");

      else
      {//replace deleted pair with the last pair in the entry
        entry[nOpt - 1].sPair[nOpt2 - 1] = entry[nOpt - 1].sPair[entry[nOpt - 1].nPair - 1]; 
        entry[nOpt - 1].nPair--; //decrement number of pairs
      }

      if(entry[nOpt - 1].nPair > 0)
      {
        printf("\nWould you like to delete a pair again? [Y/N] ");
        scanf(" %c%c", &cOpt2, &cDump); 
      }

    } while ((cOpt2 == 'Y' || cOpt2 == 'y') && entry[nOpt - 1].nPair > 0);
    
    if (entry[nOpt - 1].nPair == 0) //if no pairs remain
        deleteEntry(entry, &*n, nOpt); //delete the entry itself
  }
}

/**
 * sortEntry() sorts the entries in the array by the language name
 * following the ASCII values
 * 
 * @param entry The entry to be sorted
 */
void sortEntry(struct entryTag entry[])
{
  int i, j;
  String20 sDump1, sDump2;
  struct pairTag pTemp;

  for (i = 0; i < (entry->nPair) - 1; i++)
  {
    for (j = i + 1; j < entry->nPair; j++)
    {
      strcpy(sDump1, entry->sPair[i].pLanguage); //store in 1st temp variable
      strcpy(sDump2, entry->sPair[j].pLanguage); //store in 2nd temp variable

      if (strcmp(sDump1, sDump2) > 0) //if 2nd temp variable has higher ASCII value, swapping happens 
      {
        pTemp = entry->sPair[i]; 
        entry->sPair[i] = entry->sPair[j];
        entry->sPair[j] = pTemp;
      }
    }
  }
}

/**
 * displayEntry() displays the entries in the array
 * 
 * @param entry an array of struct entryTag
 * @param n number of entries
 */
void displayEntry(struct entryTag entry[], 
                  int n)
{
  int i, j;
  char cOpt, cDump;

  if (n == 0) //if no entries
    printf("No entry to display\n");
  if (n == 1) //if only one entry
  {
    i = 0; //initialize to 0 as index
    do
    {
      sortEntry(&entry[i]); //performs sorting on the entry's information

      printf("Entry[%d]\n", i + 1);
      for (j = 0; j < entry[i].nPair; j++) //displays entry's information
        printf("%s: %s\n", entry[i].sPair[j].pLanguage, entry[i].sPair[j].pTranslation);

      printf("Press [X] to end display\n");
      scanf(" %c%c", &cOpt, &cDump);

      if (cOpt == 'X' || cOpt == 'x')
        i = n; //assigns value of n to i to exit display

      else //if invalid input
        printf("Invalid input.\n");

    } while ((cOpt != 'X' || cOpt != 'x') && i < n);
  }

  else if (n > 1)
  {
    i = 0; //initialize to 0 as index
    do
    {
      sortEntry(&entry[i]); //perform sorting

      if (i != n)
        printf("Entry[%d]:\n", i + 1);

      for (j = 0; j < entry[i].nPair; j++)
        printf("%s: %s\n", entry[i].sPair[j].pLanguage, entry[i].sPair[j].pTranslation);
  
      if (i != n)
      {
        printf("\nPress [N]ext to proceed\n");
        printf("Press [P]revious to go back\n");
        printf("Press [X] to end display\n");
        scanf(" %c%c", &cOpt, &cDump);

        if (cOpt == 'N' || cOpt == 'n')
          i++; //increment i to display next entry

        else if (cOpt == 'P' || cOpt == 'p')
        {
          i--; //decrement i to display previous entry
          if (i < 0) //check if user can still go back
          {
            printf("You're on Entry 1!\n");
            i = 0; //set as 0 if already on 1st element
          }
        }

        else if (cOpt == 'X' || cOpt == 'x')
          i = n + 1; //end the display
      }

      else
      {
        printf("No more Next Entry!\n");
        i--; //decrement if already at the last entry
      }
      printf("\n");
    } while ((cOpt != 'X' && cOpt != 'x') && i < n + 1);
  }
}

/**
 * searchWord() searches for a word in the array and displays all entries
 * containing the word if found
 * 
 * @param entry an array of struct entryTag
 * @param n number of entries
 */
void searchWord(struct entryTag entry[], 
                int n)
{
  struct entryTag eTemp[150];
  String20 sWord;
  int i, j, k = 0;
  int count = 0; 

  printf("\n[SEARCH WORD]\n\n");
  printf("Enter a word: ");
  scanf("%s", sWord);
  printf("\n");

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < entry[i].nPair; j++)
    {
      if (strcmp(sWord, entry[i].sPair[j].pTranslation) == 0)
      {
        eTemp[k] = entry[i]; //store entry to temp
        k++; //increment index of temp
        count++; //counts the number of times the word is found
        j = entry[i].nPair; 
      }
    }
  }

  if (count > 0) //if count is more than 1
    displayEntry(eTemp, count); //display all entries found with the word

  else // if found none
    printf("No word found.\n");
}

/**
 * searchTranslation() asks for a L-T pair and displays all entries
 * that contains the L-T pair
 *
 * @param entry The array of structs
 * @param n The number of entries in the dictionary
 */
void searchTranslation( struct entryTag entry[], 
                        int n)
{
  struct entryTag eTemp[150];
  String20 sLanguage, sTranslation;
  int i,
      j = 0,
      eCnt = 0;

  printf("\n[SEARCH TRANSLATION]\n");
  getPair(&sLanguage, &sTranslation);
  printf("\n");

  // Checking for existing LT pair
  for (i = 0; i < n; i++)
  {
    if (checkPair(entry, i, sLanguage, sTranslation) == 1) //checks if both language and translation are found in an entry
    {
      eTemp[j] = entry[i]; //store in a temp
      j++; //increment index of temp
      eCnt++; //increment counter
    }
  }

  if (eCnt == 0) //if no entry was found
    printf("No Translation Found.\n");

  else //if an entry is found
    displayEntry(eTemp, eCnt); //display the entry's information
}

/**
 * exportFile() asks for a filename and writes the contents of the
 * array of entries to a text file and saves it to the given filename
 *
 * @param entry the array of structs
 * @param n number of entries
 * @param *count pointer to number of time exportFile was executed
 *
 * Pre-condition: File extension should be included in the filename 
 *                and at most 30 characters
 */
void exportFile(struct entryTag entry[], 
                int n, 
                int *count)
{
  FILE *fp;
  String30 filename;
  int i, j;
  char cDump;

  printf("\n[EXPORT]\n\n");
  printf("Enter filename:");
  scanf("%c", &cDump);
  fgets(filename, sizeof(filename), stdin); //allow multiple strings as a filename
  filename[strlen(filename)-1] = '\0'; //assign the last element as NULL
  
  fp = fopen(filename, "w"); //open file with write file mode
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < entry[i].nPair; j++)
      fprintf(fp, "%s: %s\n", entry[i].sPair[j].pLanguage, 
                              entry[i].sPair[j].pTranslation); //write the contents of array of entries to the text file
    
    fprintf(fp, "\n");
    *count += 1; //increment every successful export
  }
  fclose(fp); //close the file
}

/**
 * getFText() reads a the preceeding lines of an Entry from a file, copies the first ch, 
 *             and then append the first word into the pLanguage of an Entry,
 *             and the second word into the pTranslation of an Entry.
 *
 * @param fp pointer to the file
 * @param pLang pointer to a String20 array
 * @param pTrans pointer to a String20 array
 * @param ch the character that was read in from the file
 */
void
getFText( FILE *fp, 
          String20 *pLang, 
          String20 *pTrans, 
          char ch)
{
  String20 sTemp, sLanguage, sTranslation; 
  char cDump;

    sTemp[0] = ch; //copies ch as first character of sTemp
    sTemp[1] = '\0'; 
    fscanf(fp, "%s%c%s", sLanguage, &cDump, sTranslation);

    if(sLanguage[strlen(sLanguage)-1] == ':')
       sLanguage[strlen(sLanguage)-1] = '\0';

    strcat(sTemp, sLanguage); //appends the preceeding characters of sLanguage 
    strcpy(*pLang, sTemp); //copy sTemp to pointer *pLang
    strcpy(*pTrans, sTranslation); //copy sTranslation to pointer *pTrans
}

/**
 * importFile() reads a file and stores the data into the array of entries
 * 
 * @param entry an array of structs
 * @param *n pointer to number of entries
 *
 * Pre-condition: File extension should be included in the filename 
 *                and at most 30 characters. File is from the exported file
 *                from Manage Data or file must contain the correct format.
 */
void
importFile( struct entryTag entry[], 
            int *n, 
            int *count)
{
  FILE *fp;
  String30 filename;
  char cDump;
  char cOpt;
  int i, j = 0, cdCnt = 0;

  printf("\n[IMPORT]\n");
  printf("Enter filename: ");
  scanf("%c", &cDump);
  fgets(filename, sizeof(filename), stdin); //gets the filename
  filename[strlen(filename)-1] = '\0'; //assign null character at the end of filename
  
  if((fp = fopen(filename, "r")) != NULL) //opens file and if file exists
  {
    *count = 1;
    if(*n == 0) //if no entry yet
    {
      while(!feof(fp) && *n < 150) //iterates until EOF is found or no. of entries is full.
      { 
        fscanf(fp, "%c", &cDump); //reads end of a line and the first character of the next line

        if(cDump != '\n' && cDump != EOF)
        {
          getFText(fp, &entry[*n].sPair[j].pLanguage, 
                  &entry[*n].sPair[j].pTranslation, cDump); //reads the succeeding line of the file
          fscanf(fp, "%c", &cDump);//reads the newline
          entry[*n].nPair++;
          j++;
          cdCnt = 0;
        }

        else if(cDump == '\n') //if first char of next line is a newline
          cdCnt += 1;
        
        if(cdCnt == 1)
        {
          (*n)++;
          j = 0;
        }
      }
    }

    else if(*n > 0) //if entries are loaded before import
    {
      while(!feof(fp) && *n < 150) //iterates until EOF is found
      {
        fscanf(fp, "%c", &cDump); //reads end of a line and the first character of the next line

        if(cDump != '\n' && cDump != EOF)
        {
          getFText(fp, &entry[*n].sPair[j].pLanguage, 
                  &entry[*n].sPair[j].pTranslation, cDump); //reads the succeeding line of the file
          fscanf(fp, "%c", &cDump);
          entry[*n].nPair++;
          j++;
          cdCnt = 0;
        }

        else if(cDump == '\n')
          cdCnt += 1;

        if(cdCnt == 1) //checks if first char of the next line is a newline or EOF
        {
          j = 0; //resets value of j to 0
          do
          {
            printf("\n");

            for (i = 0; i < entry[*n].nPair; i++) //displays one entry's information at a time
              printf("%s: %s\n", entry[*n].sPair[i].pLanguage, entry[*n].sPair[i].pTranslation);

            printf("\nIs this a new entry? [Y/N]");
            scanf(" %c", &cOpt); 
          } while((cOpt != 'Y' && cOpt != 'y') &&
                  (cOpt != 'N' && cOpt != 'n'));

          if(cOpt == 'Y' || cOpt == 'y')
            (*n)++; //if new entry, increment number of entries
          

          else if(cOpt == 'N' || cOpt == 'n') //if not a new entry
          {
            for (i = 0; i < entry[*n].nPair; i++)
            {
              entry[*n].sPair[i].pLanguage[0] = '\0'; //clears the information in the specific lang
              entry[*n].sPair[i].pTranslation[0] = '\0'; //clears the information in the specific trans
            }
            entry[*n].nPair = 0; //resets number of pair of an entry to 0
          }
        }
      }
    }
  }
  else //if file does not exist
    printf("File does not exist.\n");
  
  if(*n== 150)
    printf("MAX NO. OF ENTRIES HAS BEEN REACHED\n");
  
  fclose(fp); //close the file 
  
}

/**
 * mdExit() clears the entries' information upon exiting a menu
 * 
 * @param entry an array of structs
 * @param *entryNum pointer to number of entries
 */
void
mdExit( struct entryTag entry[], 
        int *entryNum)
{
  int i, j;
  for(i = 0; i < *entryNum; i++)
  {
    for(j = 0; j < entry[i].nPair; j++)
    {
      entry[*entryNum - 1].sPair[j].pLanguage[0] = '\0'; //assigns null character to every language
      entry[*entryNum - 1].sPair[j].pTranslation[0] = '\0'; //assigns null character to all translation
    }
    entry[i].nPair = 0; //resets number of pairs to 0
  }
  
  (*entryNum) = 0; //resets number of entries to 0
}

/**
 * getToken() gets a string and breaks it into words, then stores each word into an array of strings
 * 
 * @param words an array of strings
 * @param *nElem pointer to number of elements in the array
 */
void getToken(String20 words[], 
              int *nElem)
{
  longString sentence;
  int i, j = 0, k = 0;
  char cDump;

  scanf("%c", &cDump);
  printf("Enter a phrase or a sentence: ");
  fgets(sentence, sizeof(sentence), stdin); // capacity is to account for space in between words
  sentence[strlen(sentence) - 1] = '\0';

  for (i = 0; i <= strlen(sentence); i++) // including null byte at last element
  {
    if (sentence[i] == ' ' || sentence[i] == '\0')
    {
      (*nElem)++;
      words[j][k] = '\0';
      k = 0;
      j++;
    }

    else
    {
      words[j][k] = sentence[i]; // assign characters of string sentence
      k++;                       // next character
    }
  }

  for (i = 0; i < *nElem; i++)
  {
    for (j = 0; words[i][j] != '\0'; j++)
    {
      if (!(words[i][j] <= 'A' && words[i][j] >= 'Z') &&
          !(words[i][j] <= 'a' && words[i][j] >= 'z') &&
          (words[i][j] == ',' || words[i][j] == '.' ||
           words[i][j] == '!' || words[i][j] == '?')) //removes all the ending punctuation marks of the word
        words[i][j] = '\0'; //replace with a null character
    }
  }
}

/**
 * chkExist() checks if a language exists in the array of languages
 * 
 * @param Langs The array of structs that holds the language tags and their counts.
 * @param pLang The language to check for
 * @param lCount the number of languages in the array
 * 
 * @return the value of the variable i.
 */
int chkExist( struct langTag Langs[], 
              String20 pLang, 
              int lCount)
{
  int i;

  for (i = 0; i < lCount; i++)
    if (strcmp(Langs[i].iLanguage, pLang) == 0)
      return 0;

  return 1; // returns 1 if it doesn't exist
}


/**
 * sortLang()) sorts the array of structs by the number of words in each language
 * 
 * @param Langs The array of structs that contains the languages.
 * @param n the number of languages
 */
void sortLang(struct langTag Langs[], 
              int n)
{
  int i, j, min;
  struct langTag lTemp;

  for (i = 0; i < n - 1; i++)
  {
    min = i;

    for (j = i + 1; j < n; j++)
    {
      if (Langs[min].nWord < Langs[j].nWord)
        min = j;
    }

    if (i != min)
    {
      lTemp = Langs[i];
      Langs[i] = Langs[min];
      Langs[min] = lTemp;
    }
  }
}

/**
 * identifyLanguage() takes a string of words, and checks if the words are in the dictionary. If they are, it adds the
 * language to a struct array
 * 
 * NOTE: Word Count is included in displaying the main language/s to determine how many words from the imported entries were detected.
 *
 * @param entry an array of struct entryTag
 * @param entryNum number of entries in the dictionary
 * @param Langs an array of struct langTag
 */
void identifyLanguage(struct entryTag entry[], 
                      int entryNum, 
                      struct langTag Langs[])
{
  String20 words[50];
  int nElem = 0;
  int i, j, k, m,
      l = 0,
      lCount = 0,
      wCntDmp, wCnt;

  printf("\n[IDENTIFY MAIN LANGUAGE]\n\n");
  getToken(words, &nElem);
  printf("\n");

  for (i = 0; i < nElem; i++)
  {
    for (j = 0; j < entryNum; j++)
    {
      for (k = 0; k < entry[j].nPair; k++)
      {
        if (strcmp(words[i], entry[j].sPair[k].pTranslation) == 0 &&
            chkExist(Langs, entry[j].sPair[k].pLanguage, lCount) == 1)
        {
          strcpy(Langs[l].iLanguage, entry[j].sPair[k].pLanguage); //gets the language of the word detected
          l++; //new language
          lCount++; //adds number of language detected
        }
      }
    }
  }

  if (lCount == 0) //No exiusting Languages in the Entry
    printf("CANNOT DETERMINE THE LANGUAGE\n");

  else if (lCount > 0)
  {
    for (i = 0; i < lCount; i++)
    {
      wCnt = 0;
      for (m = 0; m < nElem; m++)
      {
        wCntDmp = 0;
        for (j = 0; j < entryNum; j++)
        {
          if (checkPair(entry, j, Langs[i].iLanguage, words[m]) == 1) //checks if the word has translation to the detected language 
          {
            wCntDmp += 1;
          }
        }

        if (wCntDmp > 0)
        {
          wCnt += 1; //word count adds if it detects Lang-Trans Pair
        }
      }
      Langs[i].nWord = wCnt;
    }

    if (lCount > 1)
      sortLang(Langs, lCount);

    printf("MAIN LANGUAGE/S:\n");

    if(lCount == 1)
    {
      printf("[%d] %s: %d\n", 1, Langs[0].iLanguage, Langs[0].nWord);
      Langs[0].iLanguage[0] = '\0'; //deletes content of Langs
      Langs[0].nWord = 0;
    }
    else if (lCount > 1)
    {
      for (i = 0; i < 2; i++)
      {
        printf("[%d] %s: %d\n", i + 1, Langs[i].iLanguage, Langs[i].nWord);
      }

      for (i = 0; i < lCount; i++)
      {
        Langs[i].iLanguage[0] = '\0'; //deletes content of Langs
        Langs[i].nWord = 0; 
      }
    }
  }
}

/**
 * simpleTranslation() takes in an array of structs and the number of structs in the
 * array. It then prompts the user to enter the language of the source text and the language to be
 * translated to. It then calls the function getToken() to get the words from the source text
 * 
 * @param entry the array of structs
 * @param entryNum the number of entries in the dictionary
 */
void simpleTranslation( struct entryTag entry[], 
                        int entryNum)
{
  String20 words[50]; //sentence to be translated
  String20 trans[50]; //translated text
  String20 sLang1, sLang2;
  char cOpt;
  int nElem, nOpt = 0; //number of words in the sentence
  int i, j, k, l;

  printf("\n[SIMPLE TRANSLATION]\n\n");

  do
  {
    if(nOpt == 0)
    {
      nElem = 0;
      printf("Enter the language of the source text: ");
      scanf("%s", sLang1); //Language of text to be translated

      getToken(words, &nElem);

      printf("Enter the language to be translated to: ");
      scanf("%s", sLang2); //Language of text to translate to
      nOpt = 1;
    }

    for(i = 0; i < nElem; i++)
      strcpy(trans[i], words[i]); //copies the contents of words to trans

    for(i = 0; i < nElem; i++)
    {
      for(j = 0; j < entryNum; j++)
      {
        for (k = 0; k < entry[j].nPair; k++)
        {
          if (strcmp(words[i], entry[j].sPair[k].pTranslation) == 0 &&
              strcmp(sLang1, entry[j].sPair[k].pLanguage) == 0) //Source Language of word found
          {
            for (l = 0; l < entry[j].nPair; l++)
            {
              if (strcmp(sLang2, entry[j].sPair[l].pLanguage) == 0) //Translation Language found
              {
                strcpy(trans[i], entry[j].sPair[l].pTranslation); //copies translated word
                j = entryNum; //ends loop to proceed to next word
                k = entry[j].nPair; //ends loop for checking further source language
                l = entry[j].nPair; //ends loop  for checking further translation language
              }
            }
          }
        } 
      }
    }

    printf("\nTRANSLATED TEXT:");

    for(i = 0; i < nElem; i++)
      printf(" %s", trans[i]); //prints translated text
    
    printf("\n");

    do
    {
      printf("\nDo you want to translate a new text? [Y/N] ");
      scanf(" %c", &cOpt);
      if((cOpt != 'Y' && cOpt != 'y') &&
         (cOpt != 'N' && cOpt != 'n'))
         printf("INVALID INPUT\n\n");
    } while((cOpt != 'Y' && cOpt != 'y') &&
           (cOpt != 'N' && cOpt != 'n'));
    if(cOpt == 'Y' || cOpt == 'y')
    {
      for(i = 0; i < nElem; i++)
          strcpy(trans[i], " ");

      nElem = 0;
      getToken(words, &nElem);
    }
      
  } while(cOpt == 'Y' || cOpt == 'y');
}

/**
 * manageData() allows the user to add, modify, delete, search, import and export entries
 * 
 * @param entry an array of struct entryTag
 * @param *entryNum number of entries
 */
void manageData(struct entryTag entry[], 
                int *entryNum)
{
  int nOpt1, nKey; //nKey is the entry no. that user prompted
  char cOpt, cOpt2;
  int count = 0; //count of successful export file
  int count2 = 0;
  do
  {
    nKey = 0;
    cOpt = 'n';

    printf("\nWelcome to Manage Data Menu!\n");
    printf("Please select one option to proceed:\n");
    printf("[1] Add Entry\n");
    printf("[2] Add Translation\n");
    printf("[3] Modify Entry\n");
    printf("[4] Delete Entry\n");
    printf("[5] Delete Translation\n");
    printf("[6] Display All Entries\n");
    printf("[7] Search Word\n");
    printf("[8] Search Translation\n");
    printf("[9] Export\n");
    printf("[10] Import\n");
    printf("[11] Exit\n");
    printf("Input: ");
    scanf("%d", &nOpt1);
    if (nOpt1 < 1 || nOpt1 > 11)
      printf("Wrong input.\n\n");

    switch (nOpt1)
    {
      case 1:
        if (*entryNum == 150) //max number of entries achieved
          printf("Max # of entries have been reached.\n");
        else
        {
          addEntry(entry, &*entryNum);
          count = 0;
        }
        break;

      case 2:
        if (*entryNum == 0) //no entry found yet
          printf("Please use Add Entry option first.\n");
        else
        {
          addTranslation(entry, *entryNum);
          count = 0;
        }
          
        break;

      case 3:
        if (*entryNum == 0)
          printf("Please use Add Entry option first.\n");
        else
        {
          modifyEntry(entry, &*entryNum);
          count = 0;
        }
        break;

      case 4:
        if (*entryNum == 0)
          printf("Please use Add Entry option first.\n");
        else
        {
          printf("\n[DELETE ENTRY]\n\n");
          displayEntry(entry, *entryNum);
          if(*entryNum == 1) 
          {
            printf("Would you like to delete this Entry? [Y/N]\n");
            scanf(" %c", &cOpt);
            if(cOpt == 'Y' || cOpt == 'y')
              nKey = 1;
          }
          else if(*entryNum > 1)
          {
            printf("Which Entry would you like to delete?\n");
            printf("Enter Entry No.: ");
            scanf("%d", &nKey);
          }

          if ((nKey > 0 && nKey < *entryNum + 1) ||
              (cOpt == 'Y' || cOpt == 'y'))
          {
            deleteEntry(entry, &*entryNum, nKey);
            count = 0;
          }
          else if(((cOpt != 'Y' && cOpt != 'y') &&
                    (cOpt != 'N' && cOpt != 'n')) ||
                    (nKey < 1 || nKey > *entryNum))
            printf("INVALID INPUT\n\n");
        }
        break;

      case 5:
        if (*entryNum == 0)
          printf("Please use Add Entry option first.\n");
        else
        {
          deleteTranslation(entry, &*entryNum);
          count = 0;
        }
        break;

      case 6:
        printf("\n");
        displayEntry(entry, *entryNum);
        break;

      case 7:
        if (*entryNum == 0)
          printf("Please use Add Entry option first.\n");
        else
          searchWord(entry, *entryNum);
        break;

      case 8:
        if (*entryNum == 0)
          printf("Please use Add Entry option first.\n");
        else
          searchTranslation(entry, *entryNum);
        break;

      case 9:
        if (*entryNum == 0)
          printf("Please use Add Entry option first.\n");
        else
          exportFile(entry, *entryNum, &count);
        break;

      case 10:
        importFile(entry, &*entryNum, &count2);
        if(count2 == 1)
          count = 0;
        break;
      
      case 11:
        if(*entryNum > 0 && count == 0) 
        {
          printf("Your Latest data is not yet saved and will be lost.\n");
          printf("Enter any letter to proceed\n");
          printf("Enter [E] to export the data and exit Manage Data\n");
          printf("Input: ");
          scanf(" %c", &cOpt2);
          if(cOpt2 != 'E' && cOpt2 != 'e')
            mdExit(entry, &*entryNum);
          else if(cOpt2 == 'E' || cOpt2 == 'e')
          {
            exportFile(entry, *entryNum, &count); 
            mdExit(entry, &*entryNum);
          }
        }
        else if(count > 0)
          mdExit(entry, &*entryNum);
        break;
    }
  } while (nOpt1 != 11); //exits manageData menu
  printf("\n");
}


/**
 * languageTools() contains the menu for Language Tools that identifies 
 *                 Main Language and performs simple translation.
 *
 * @param entry an array of struct entryTag
 * @param entryNum number of entries in the entry array
 * @param Langs an array of struct langTag
 */
void languageTools( struct entryTag entry[], 
                    int entryNum, 
                    struct langTag Langs[])
{
  int nOpt;
  int count = 0;
  printf("\nWelcome to Language Tools Menu!\n");
  printf("Enter the filename where data is located");
  
  importFile(entry, &entryNum, &count); //asks user to import file of entries
    
  if(count == 1)
  {
   do
    {
      printf("\nWelcome to Language Tools Menu!\n");
      printf("Please select one option to proceed:\n");
      printf("[1] Identify Main Language\n");
      printf("[2] Simple Translation\n");
      printf("[3] Exit\n");
      printf("Input:");
      scanf("%d", &nOpt);
      if (nOpt < 1 || nOpt > 3)
        printf("Wrong input.\n\n");

      switch (nOpt)
      {
      case 1:
        identifyLanguage(entry, entryNum, Langs); //calls identifyLanguage func
        break;

      case 2:
        simpleTranslation(entry, entryNum); //calls simpleTranslation func
        break;

      case 3:
        mdExit(entry, &entryNum); //clears the entry
        break;
      }
    } while (nOpt != 3); //exits language tools 
  }
  printf("\n");
}

int main()
{
  struct entryTag entry[150]; //entries
  struct langTag Langs[10]; //max of 10 languages for identifyLanguage func
  int entryNum = 0; //number of entries
  int nOpt;

  do
  {
    printf("Welcome to Simple Language Tools\n");
    printf("Please select to proceed:\n");
    printf("[1] Manage Data\n");
    printf("[2] Language Tools\n");
    printf("[3] Exit\n");
    printf("Input:");
    scanf("%d", &nOpt);
    if (nOpt < 1 || nOpt > 3) //ask user until valid input (1-3)
      printf("Wrong input.\n\n");
    switch (nOpt)
    {
    case 1:
      manageData(entry, &entryNum); //calls manageData func
      break;
      
    case 2:
      languageTools(entry, entryNum, Langs); //calls languageTools func
      break;
    }
  } while (nOpt != 3); //exits program

  return 0;
}