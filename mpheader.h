#include <stdio.h>
#include <string.h>

typedef char String20[21];
typedef char String30[31];
typedef char longString[151];

struct pairTag {
	String20 pLanguage;
	String20 pTranslation;
};

struct entryTag {
	struct pairTag sPair[10];
	int nPair;
};

struct langTag { //Language Tools structure 
	String20 iLanguage;
	int nWord;
};

void getPair(String20 *sLang, String20 *sTrans);
int checkPair(struct entryTag entry[], int n, String20 sLang, String20 sTrans);
void addPair(struct entryTag entry[], int n);
void addPair2(struct entryTag entry[], int n);
void addEntry(struct entryTag entry[], int *n);
void addTranslation(struct entryTag entry[], int n);
void modifyEntry(struct entryTag entry[], int *n);
void deleteEntry(struct entryTag entry[], int *n, int key);
void deleteTranslation(struct entryTag entry[], int *n);
void sortEntry(struct entryTag entry[]);
void displayEntry(struct entryTag entry[], int n);
void searchWord(struct entryTag entry[], int n);
void searchTranslation(struct entryTag entry[], int n);
void exportFile(struct entryTag entry[], int n, int *count);
void getFText(FILE *fp, String20 *pLang, String20 *pTrans, char ch);
void importFile(struct entryTag entry[], int *n, int *count);
void mdExit(struct entryTag entry[], int *entryNum);
void getToken(String20 words[], int *nElem);
int chkExist(struct langTag Langs[], String20 pLang, int lCount);
void sortLang(struct langTag Langs[], int n);
void identifyLanguage(struct entryTag entry[], int entryNum, struct langTag Langs[]);
void simpleTranslation(struct entryTag entry[], int entryNum);
void manageData(struct entryTag entry[], int *entryNum);
void languageTools(struct entryTag entry[], int entryNum, struct langTag Langs[]);
