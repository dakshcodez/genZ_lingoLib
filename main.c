#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct entry{
    char *term;
    char *meaning;
    char *synonym;
    char *antonym;
    struct entry* left;
    struct entry* right;
};

struct entry* createNewWord(char *term, char *meaning, char *synonym, char *antonym){
    struct entry* newWord = (struct entry*)malloc(sizeof(struct entry));
    newWord -> term = term;
    newWord -> meaning = meaning;
    newWord -> synonym = synonym;
    newWord -> antonym = antonym;
    newWord -> left = NULL;
    newWord -> right = NULL;
}

void insert(struct entry** dic, char *term, char *meaning, char *synonym, char *antonym){
    if (*dic == NULL){
        *dic = createNewWord(term, meaning, synonym, antonym);
        return;
    }
    struct entry* parent = NULL;
    struct entry* child = *dic;
    struct entry* newWord = createNewWord(term, meaning, synonym, antonym);
    while (child != NULL){
        parent = child;
        if (strcmp(term, child -> term) < 0){
            child = child -> left;
        } else {
            child = child->right;
        }
    }
    if (strcmp(term, parent -> term) < 0){
        parent -> left = newWord;
    } else {
        parent -> right = newWord;
    }
}

//only printing the term to check

void printAlphabetically(struct entry* dic){
    if (dic != NULL){
        printAlphabetically(dic -> left);
        printf("%s\n", dic -> term);
        printAlphabetically(dic -> right);
    }
}

void search(struct entry* dic, char *searchWord){
    while (dic != NULL){
        if (dic -> term == searchWord){
            printf("%s\n", dic->term);
            printf("%s", dic->meaning);
            return;
        }
        else if (strcmp(searchWord, dic->term) < 0){
            dic = dic->left;
        }
        else{
            dic = dic->right;
        }
    }
    if (dic == NULL){
        printf("Word not found.\n");
        return;
    }
}

int main(){
    struct entry* dictionary = NULL;
    insert(&dictionary, "fr", "abbreviation - for real. Meaning that the event being described is true", "tru", "cap");
    insert(&dictionary, "on god", "Similar to 'fr', except the user is so confident, that he swears his life to god.", "fr", "cap");
    insert(&dictionary, "boomer", "Referring to the person reading this.", "you", "me");

    search(dictionary, "fr");
    return 0;
}