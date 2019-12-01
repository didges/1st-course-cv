#pragma once
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
    int max_len_word;
    wchar_t *mask;
    wchar_t **arr_of_words;
};

typedef struct Text text;
typedef struct Sentence sentence;

