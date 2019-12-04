#include "lib_and_struct.h"

void deleter(text *my_text)
{
    for(int main_sent = 0; main_sent <= my_text->count_of_sent; main_sent++)
    {
        int sent = main_sent + 1;
        while(sent <= my_text->count_of_sent)
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
                my_text->count_of_sent -= 1;
            }
            else
            {
                sent++;
            }
            
        }
    }
}

void fst_func(text *my_text)
{
    for(int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        int count = 0;
        my_text->arr_of_sent[sent]->mask = calloc(my_text->arr_of_sent[sent]->max_len_word+1, sizeof(wchar_t));

        if(my_text->arr_of_sent[sent]->count_of_words == 0)
        {
            for(int i = 0; i <= wcslen(my_text->arr_of_sent[sent]->arr_of_words[0]); i++)
            {
                my_text->arr_of_sent[sent]->mask[i] = my_text->arr_of_sent[sent]->arr_of_words[0][i];
            }
        }
        else
        {
            for(int symb = 0; symb <my_text->arr_of_sent[sent]->max_len_word; symb++)
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
}


void scnd_func(text *my_text)
{
    int sent = 0;
    while(sent <= my_text->count_of_sent)
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
            my_text->count_of_sent -= 1;
        }
        else
        {
            sent++;
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
    wchar_t **aa = (wchar_t**)a;
    wchar_t **bb = (wchar_t**)b;

    if(count_of_vowel(*aa) > count_of_vowel(*bb))
        return 1;
    if(count_of_vowel(*aa) < count_of_vowel(*bb))
        return -1;
    else
        return 0;
}

void thrd_func(text *my_text)
{
    int vowel_1 = 0, vowel_2 = 0; 
    for(int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        qsort(my_text->arr_of_sent[sent]->arr_of_words, my_text->arr_of_sent[sent]->count_of_words + 1, sizeof(wchar_t*), compar);
    }
}

void fth_func(text *my_text)
{
    for (int sent = 0; sent <= my_text->count_of_sent; sent++)
    {
        int total = 0;
        wchar_t **temp = malloc(my_text->arr_of_sent[sent]->size_of_snt * sizeof(wchar_t *));
        int count_words = my_text->arr_of_sent[sent]->count_of_words;
        for (int i = 0; i <= count_words; i++)
        {
            temp[i] = malloc((wcslen(my_text->arr_of_sent[sent]->arr_of_words[i])+1) * sizeof(wchar_t));
            wcscpy(temp[i], my_text->arr_of_sent[sent]->arr_of_words[i]);
        }
        
        for(int main_word = 0; main_word <= count_words; main_word++)
        {
            int count_of_same = 1;
            int word = main_word + 1;
            while(word <= count_words)
            {
                int logic = 1;

                if(wcscmp(temp[main_word], temp[word]) != 0)
                {
                    logic = 0;
                    word++;
                }

                if(logic == 1)
                {
                    count_of_same++;
                    free(temp[word]);
                    for (int i = word; i < count_words; i++)
                    {
                        temp[i] = temp[i+1];
                    }
                    
                    count_words--;
                }
            }
            if(count_of_same != 1)
            {
                total += count_of_same;
            }
        }
        my_text->arr_of_sent[sent]->same_words = total;
        for(int i = 0; i <= count_words; i++)
        {
            free(temp[i]);
        }free(temp);
        
    }
    
}