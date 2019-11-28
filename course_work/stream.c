#include "lib_and_struct.h"

void read_text(text *my_text)
{
    FILE *f = fopen("test.txt", "r");
    my_text->size_of_txt = 20;
    my_text->arr_of_sent = malloc(my_text->size_of_txt * sizeof(sentence*));
    my_text->count_of_sent = 0;
    wchar_t current_symb;
    int logic = 1;
    while(current_symb != '\n')
    {
        current_symb = fgetwc(f);
        if(logic)
        {
            if(my_text->size_of_txt == my_text->count_of_sent)
            {
                my_text->size_of_txt += 2;
                my_text->arr_of_sent = realloc(my_text->arr_of_sent, sizeof(sentence*) * my_text->size_of_txt);
            }
            my_text->arr_of_sent[my_text->count_of_sent] = malloc(sizeof(sentence));
            my_text->arr_of_sent[my_text->count_of_sent]->size_of_snt = 8; 
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words = malloc(my_text->arr_of_sent[my_text->count_of_sent]->size_of_snt * sizeof(wchar_t *));
                   
            logic = 0;
            my_text->arr_of_sent[my_text->count_of_sent]->count_of_words = 0;
            my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb = 0;
            my_text->arr_of_sent[my_text->count_of_sent]->size_of_word = 8;
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words] = malloc(my_text->arr_of_sent[my_text->count_of_sent]->size_of_word * sizeof(wchar_t));
            if(my_text->arr_of_sent[my_text->count_of_sent]->count_of_words == 0 &&( current_symb == ' ' || current_symb == '\t'))
                continue;
        }
        
        if(current_symb == '.')
        {
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words][my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb] = current_symb;
            logic = 1;
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words][my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb + 1] = '\0';
            my_text->count_of_sent += 1;
            continue;
        }
        
        if(current_symb == ' ' || current_symb == ',')
        {
            if(my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb == 0)
                continue;
            if(my_text->arr_of_sent[my_text->count_of_sent]->size_of_snt == my_text->arr_of_sent[my_text->count_of_sent]->count_of_words)
            {
                my_text->arr_of_sent[my_text->count_of_sent]->size_of_snt += 2;
                my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words = realloc(my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words, my_text->arr_of_sent[my_text->count_of_sent]->size_of_snt * sizeof(wchar_t *));
            }
            if(current_symb == ',')
            {
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words][my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb++] = current_symb;
            }
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words][my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb] = '\0';
            my_text->arr_of_sent[my_text->count_of_sent]->count_of_words += 1;
            my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb = 0;

            my_text->arr_of_sent[my_text->count_of_sent]->size_of_word = 8;
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words] = malloc(my_text->arr_of_sent[my_text->count_of_sent]->size_of_word * sizeof(wchar_t));

            continue;
        }
        
        if(my_text->arr_of_sent[my_text->count_of_sent]->size_of_word == my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb)
        {
            my_text->arr_of_sent[my_text->count_of_sent]->size_of_word *= 2;
            my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words] = realloc(my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words], my_text->arr_of_sent[my_text->count_of_sent]->size_of_word * sizeof(wchar_t));
        }
        my_text->arr_of_sent[my_text->count_of_sent]->arr_of_words[my_text->arr_of_sent[my_text->count_of_sent]->count_of_words][my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb] = current_symb;
        my_text->arr_of_sent[my_text->count_of_sent]->count_of_symb += 1;

    } my_text->count_of_sent -= 1;

    fclose(f);    
}


void printer(text *my_text)
{
    for(int i=0;i <= my_text->count_of_sent; i++)
    {
        wprintf(L"[%d] sentence: ", i+1);
        for(int j=0;j <= my_text->arr_of_sent[i]->count_of_words;j++)
        {
            wprintf(L"%ls ", my_text->arr_of_sent[i]->arr_of_words[j]);
        }
            wprintf(L"\n");
    }
}

void printer_for_fst(text *my_text)
{
    for(int i=0;i <= my_text->count_of_sent; i++)
    {
        wprintf(L"In [%d] sentence sample string is: %ls\n", i+1, my_text->arr_of_sent[i]->mask);
    }
}

void printer_for_fth(text *my_text)
{
    for(int i=0;i <= my_text->count_of_sent; i++)
    {
        wprintf(L"In [%d] sentence count of same word: %d\n", i+1, my_text->arr_of_sent[i]->same_words);
    }
}


