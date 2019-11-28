#include "stream.h"
#include "funcs.h"

int main(){
    setlocale(LC_ALL,"");
    text my_text;
    read_text(&my_text);
    deleter(&my_text);
    int stop = 0, mod;
    while (!stop)
    {
        wprintf(L"-----------------------------------------------------------------------------------------------\n");
        wprintf(L"\tPress 0 to print the text in the current state\n");
        wprintf(L"\tPress 1 to print the sample string of sentence\n");
        wprintf(L"\tPress 2 to delete sentences that do not have capital letters at the beginning of a word\n");
        wprintf(L"\tPress 3 to sort words in a sentence by the number of vowels in a word\n");
        wprintf(L"\tPress 4 to print the number of identical words in a sentence\n");
        wprintf(L"\tPress 5 to finish the program\n");
        wprintf(L"-----------------------------------------------------------------------------------------------\n");
        scanf("%d", &mod);
        switch (mod)
        {
        case 0:
            printer(&my_text);
            break;
        
        case 1:
            fst_func(&my_text);
            printer_for_fst(&my_text);
            break;
        
        case 2:
            scnd_func(&my_text);
            break;

        case 3:
            thrd_func(&my_text);
            break;

        case 4:
            fth_func(&my_text);
            printer_for_fth(&my_text);
            break;
        
        case 5:
            wprintf(L"Bye!\n");
            stop = 1;
        }

    }
    
    return 0;
}