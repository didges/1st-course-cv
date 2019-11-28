#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

struct Text
{
    int count_of_sent;
    int size_of_txt;
    struct Sentence **arr_of_sent;
};

struct Sentence
{
    int count_of_symb;
    int count_of_words;
    int size_of_snt;
    int size_of_word;
    int same_words;
    wchar_t *mask;
    wchar_t **arr_of_words;
};

typedef struct Text text;
typedef struct Sentence sentence;


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

void deleter(text *my_text)
{
    for(int main_sent = 0; main_sent <= my_text->count_of_sent; main_sent++)
    {
        for(int sent = main_sent + 1; sent <= my_text->count_of_sent; sent++)
        {
            int logic = 1;
            for(int word = 0; word <= my_text->arr_of_sent[sent]->count_of_words; word++)
            {
                for (int symb = 0; symb < wcslen(my_text->arr_of_sent[sent]->arr_of_words[word]); symb++)
                {
                    if (my_text->arr_of_sent[main_sent]->count_of_words == my_text->arr_of_sent[sent]->count_of_words)
                    {
                        if (wcslen(my_text->arr_of_sent[main_sent]->arr_of_words[word]) == wcslen(my_text->arr_of_sent[sent]->arr_of_words[word]))
                        {
                            if (towupper(my_text->arr_of_sent[main_sent]->arr_of_words[word][symb]) == towupper(my_text->arr_of_sent[sent]->arr_of_words[word][symb]))
                            {
                                continue;
                            } else logic = 0;
                        } else logic = 0;                        
                    } else logic = 0;                    
                }                
            }

            if(logic == 1)
            {
                for(int word = 0; word <= my_text->arr_of_sent[sent]->count_of_words; word++)
                {
                    free(my_text->arr_of_sent[sent]->arr_of_words[word]);
                }free(my_text->arr_of_sent[sent]);

                for(int k = sent; k <= my_text->count_of_sent; k++)
                {
                    my_text->arr_of_sent[k] = my_text->arr_of_sent[k+1];
                }     
                sent--;
                my_text->count_of_sent -= 1;
            }
        }
    }
}


void fst_func(text *my_text)
{
    for(int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        int count = 0;
        int max_len_word = wcslen(my_text->arr_of_sent[sent]->arr_of_words[0]);
        
        for(int word = 1; word <= my_text->arr_of_sent[sent]->count_of_words; word++)
        {
            if(wcslen(my_text->arr_of_sent[sent]->arr_of_words[word]) > wcslen(my_text->arr_of_sent[sent]->arr_of_words[word - 1]))
            {
                max_len_word = wcslen(my_text->arr_of_sent[sent]->arr_of_words[word]);
            }
        }
        my_text->arr_of_sent[sent]->mask = calloc(max_len_word+1, sizeof(wchar_t));
        
        for(int symb = 0; symb < max_len_word; symb++)
        {
            wchar_t temp;
            for(int word = 1; word <= my_text->arr_of_sent[sent]->count_of_words; word++)
            {
                if (my_text->arr_of_sent[sent]->arr_of_words[word][symb] == my_text->arr_of_sent[sent]->arr_of_words[word - 1][symb])
                {
                    temp = my_text->arr_of_sent[sent]->arr_of_words[word][symb];
                }
                else
                {
                    temp = '?';
                    break;
                }
            }
            my_text->arr_of_sent[sent]->mask[count++] = temp;
            
        }
        for (int i = wcslen(my_text->arr_of_sent[sent]->mask)-1; i > 0; i--)
        {
            if(my_text->arr_of_sent[sent]->mask[i] == my_text->arr_of_sent[sent]->mask[i-1] && my_text->arr_of_sent[sent]->mask[i] == '?')
            {
                my_text->arr_of_sent[sent]->mask[i] = '\0';
            }
            else {break;}
        }
        if (wcslen(my_text->arr_of_sent[sent]->mask) != max_len_word)
        {
            my_text->arr_of_sent[sent]->mask[wcslen(my_text->arr_of_sent[sent]->mask)] = '*';
        }
        
        wprintf(L"In [%d] sentence sample string is: %ls\n", sent+1, my_text->arr_of_sent[sent]->mask);
    }
}


void scnd_func(text *my_text)
{
    for(int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        int logic = 1;
        for(int word = 0; word <= my_text->arr_of_sent[sent]->count_of_words; word++)
        {
            if (iswupper(my_text->arr_of_sent[sent]->arr_of_words[word][0]))
            {
                continue;                  
            } else logic = 0;                                  
        }

        if(logic == 1)
        {
            for(int word = 0; word <= my_text->arr_of_sent[sent]->count_of_words; word++)
            {
                free(my_text->arr_of_sent[sent]->arr_of_words[word]);
            }free(my_text->arr_of_sent[sent]);

            for(int k = sent; k <= my_text->count_of_sent; k++)
            {
                my_text->arr_of_sent[k] = my_text->arr_of_sent[k+1];
            }     
            sent--;
            my_text->count_of_sent -= 1;
        }
    }
}


int count_of_vowel(wchar_t* word)
{
    wchar_t vowel[] = {'A','E','I','O','U','Y',L'А',L'Е',L'Ё',L'И',L'О',L'У',L'Ы',L'Э',L'Ю',L'Я'};
    int counter = 0;
    for(int symb = 0; symb <= wcslen(word); symb++)
    {
        for(int symb_vowel = 0; symb_vowel  < wcslen(vowel); symb_vowel++)
        {
            if(towupper(word[symb]) == vowel[symb_vowel])
            {
                counter += 1;
            }
        }
    }
    return counter;
}

void thrd_func(text *my_text)
{
    int vowel_1 = 0, vowel_2 = 0; 
    for(int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        for(int i = 0; i <= my_text->arr_of_sent[sent]->count_of_words; i++)
        {
            for (int j = 0; j <= my_text->arr_of_sent[sent]->count_of_words - i - 1; j++)
            {
                if(count_of_vowel(my_text->arr_of_sent[sent]->arr_of_words[j]) > count_of_vowel(my_text->arr_of_sent[sent]->arr_of_words[j+1]))
                {
                    wchar_t *temp = my_text->arr_of_sent[sent]->arr_of_words[j];
                    my_text->arr_of_sent[sent]->arr_of_words[j] = my_text->arr_of_sent[sent]->arr_of_words[j+1];
                    my_text->arr_of_sent[sent]->arr_of_words[j+1] = temp;
                }
            }
            
        }
    }
}

void fth_func(text *my_text)
{
    int total = 0;
    int count_of_same = 0;
    int logic;
    for(int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        total = 0;
        for(int main_word = 0; main_word <= my_text->arr_of_sent[sent]->count_of_words; main_word++)
        {
            count_of_same = 1;
            for(int word = main_word + 1; word <= my_text->arr_of_sent[sent]->count_of_words; word++)
            {
                logic = 1;
                if(wcslen(my_text->arr_of_sent[sent]->arr_of_words[main_word]) == wcslen(my_text->arr_of_sent[sent]->arr_of_words[word]))
                {
                    for (int symb = 0; symb < wcslen(my_text->arr_of_sent[sent]->arr_of_words[word]); symb++)
                    {
                        if(my_text->arr_of_sent[sent]->arr_of_words[main_word][symb] != my_text->arr_of_sent[sent]->arr_of_words[word][symb])
                        {
                            logic = 0;
                        }
                    } 
                } else logic = 0;

                if(logic == 1)
                {
                    count_of_same++;
                }
            }
            if(count_of_same != 1)
            {
                total += count_of_same;
            }
        }
        my_text->arr_of_sent[sent]->same_words = total;
        wprintf(L"In [%d] sentence count of same word: %d\n", sent+1, my_text->arr_of_sent[sent]->same_words);
    }
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


int main(){
    setlocale(LC_ALL,"");
    text my_text;
    read_text(&my_text);
    deleter(&my_text);
    fst_func(&my_text);
    //scnd_func(&my_text);
    //thrd_func(&my_text);
    //fth_func(&my_text);
    //printer(&my_text);
    return 0;
}