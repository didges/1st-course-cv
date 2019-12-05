#include "stream.h"
#include "funcs.h"

int main(){
    setlocale(LC_ALL,"");
    text my_text;
    read_text(&my_text);
    deleter(&my_text);
    int stop = 0, mod, temp = -1;
    while (!stop)
    {
        wprintf(L"-----------------------------------------------------------------------------------------------\n");
        wprintf(L"\tEnter 0 to print the text in the current state\n");
        wprintf(L"\tEnter 1 to print the sample string of sentence\n");
        wprintf(L"\tEnter 2 to delete sentences that do not have capital letters at the beginning of a word\n");
        wprintf(L"\tEnter 3 to sort words in a sentence by the number of vowels in a word\n");
        wprintf(L"\tEnter 4 to print the number of identical words in a sentence\n");
        wprintf(L"\tEnter any else key to finish the program\n");
        wprintf(L"-----------------------------------------------------------------------------------------------\n");

        temp = wscanf(L"%d", &mod);
        if(temp != 1){mod = -1;}
        switch(mod)
        {
        case 0:
            printer(&my_text);
            break;
        
        case 1:
            sample_string(&my_text);
            printer_sample_string(&my_text);
            for(int i = 0; i <= my_text.count_of_sent; i++)
            {
                free(my_text.arr_of_sent[i]->mask);
            }
            break;
        
        case 2:
            deleter_sent(&my_text);
            break;

        case 3:
            sort_by_vowel(&my_text);
            break;

        case 4:
            count_of_same(&my_text);
            printer_count_of_same(&my_text);
            break;
        
        default:
            wprintf(L"Bye\n");
            stop = 1;
            break;
        }
    }

    for(int sent = 0; sent <= my_text.count_of_sent; sent++)
    {
        for(int word = 0; word <= my_text.arr_of_sent[sent]->count_of_words; word++)
        {
            free(my_text.arr_of_sent[sent]->arr_of_words[word]);
        }
        free(my_text.arr_of_sent[sent]->arr_of_words);
        free(my_text.arr_of_sent[sent]);
    }free(my_text.arr_of_sent);
    return 0;
}