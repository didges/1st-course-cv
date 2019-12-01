#include "lib_and_struct.h"

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
        my_text->arr_of_sent[sent]->mask = calloc(my_text->arr_of_sent[sent]->max_len_word + 1, sizeof(wchar_t));
        
        for(int symb = 0; symb < my_text->arr_of_sent[sent]->max_len_word; symb++)
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
        if (wcslen(my_text->arr_of_sent[sent]->mask) != my_text->arr_of_sent[sent]->max_len_word)
        {
            my_text->arr_of_sent[sent]->mask[wcslen(my_text->arr_of_sent[sent]->mask)] = '*';
        }
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

int compar(const void *a, const void *b)
{
    if(count_of_vowel(*(wchar_t**)a) > count_of_vowel(*(wchar_t**)b))
        return 1;
    if(count_of_vowel(*(wchar_t**)a) < count_of_vowel(*(wchar_t**)b))
        return -1;
    else
        return 0;
}

void thrd_func(text *my_text)
{
    int vowel_1 = 0, vowel_2 = 0; 
    for(int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        qsort(my_text->arr_of_sent[sent]->arr_of_words, my_text->arr_of_sent[sent]->count_of_words, my_text->arr_of_sent[sent]->max_len_word, compar);
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
                if(wcscmp(my_text->arr_of_sent[sent]->arr_of_words[main_word], my_text->arr_of_sent[sent]->arr_of_words[word]) != 0)
                {
                    logic = 0;
                }

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
        
    }
}
