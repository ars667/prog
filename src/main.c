#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <time.h>
#include "structs.h"
#include "read_text.h"
#include "read_sentence.h"
#include "delete_double.h"
#include "replace.h"
#include "replace_text.h"
#include "find_dates.h"
#include "delete_same_words.h"
#include "is_happened.h"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    struct Text text;
    wprintf(L"Введите текст\n");
    text = read_text();
    text = delete_double(text);
    wprintf(L"Выберете действие:\n1 - Заменить в тексте все подстроки “high noon” на “полдень” и “полночь” на “midnight”.\n2 - Найти и вывести все даты в виде “ DD/MM/YYYY ” или “ YYYY-MM-DD ” в порядке возрастания.\n3 - Удалить все предложения, которые начинаются и заканчиваются на одно и то же слово.\n4 - Для всех дат вида “<day> <month> <year>, вывести эти даты в виде “DD.MM.YYYY”, “Happened” если эта дата была до текущей и “Not Happened” в противном случае\nДля завершения программы введите 0\n");
    char choise = getwchar();
    switch (choise){
    	case '0':
    	exit(0);
    	break;
        case '1':            
            text = replace_text(text, L"high noon", L"полдень");
    	    text = replace_text(text, L"полночь", L"midnight");
    	    for (int i = 0; i < text.num; i++){
         	wprintf(L"%ls", (text.sents[i])->str);   
    	    }
            break;
        case '2':
            find_dates(text);
            break;
        case '3':
            text = delete_same_words(text);
    	    for (int i = 0; i < text.num; i++){
         	wprintf(L"%ls", (text.sents[i])->str);   
    	    }
            break;
        case '4':
            is_happened(text);
            break;
        default:
            wprintf(L"Неправильный ввод.\n");
    }
    	    for(int i = 0; i < text.num; i++){
         	free((text.sents[i])->str);   
    	    }	
    	    free(text.sents);
    
    return 0;
}
