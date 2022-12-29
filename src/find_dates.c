#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <time.h>
#include "structs.h"
#define BUF_SIZE 100

int compare(const void *x1, const void *x2)   
{
  return(*(int*)x1 - *(int*)x2); 
};

void find_dates(struct Text text){
    wchar_t *strtime = malloc(12*sizeof(wchar_t));
    int *dates = malloc(BUF_SIZE*sizeof(int));
    int k = 0;
    int size = BUF_SIZE;
    for (int i = 0; i < text.num; i++){
        wchar_t *str_orig = text.sents[i]->str;
        int len = text.sents[i]->size;
        wchar_t *str_copy = malloc(len*sizeof(wchar_t));
        for(int x = 0; x <= len; x++){
            str_copy[x] = str_orig[x];
        }
        for(int j = 0; j <= len; j++){
            if(isdigit(str_copy[j])){
                str_copy[j] = '$';
            }
        }
    wchar_t *t;
    do{
        t = wcsstr(str_copy, L"$$/$$/$$$$");
        if(t){
            wchar_t *year = malloc(4*sizeof(wchar_t));
            wcsncpy(year, (str_orig + (t - str_copy+6)), 4*sizeof(wchar_t));
            if(size<=sizeof(int*)*(k+1)){
                dates = realloc(dates, size+BUF_SIZE*sizeof(int));
                if(!dates){
            	wprintf(L"ошибка выделения памяти");
            	break;
            	}
                size+=BUF_SIZE;
            }
            dates[k] = wcstol(str_orig+(t - str_copy), NULL, 10) + 100*wcstol(str_orig+(t - str_copy+3), NULL, 10) + 10000*wcstol(year, NULL, 10);
            dates[k] *= 10;
            dates[k] += 5; 
            k++;
	str_copy[t-str_copy] = 'g';
	free(year);
        }
    }while(t);
    
    do{
        t = wcsstr(str_copy, L"$$$$-$$-$$");
        if(t){
            wchar_t *day = malloc(2*sizeof(wchar_t));
            wcsncpy(day, (str_orig + (t - str_copy+8)), 2*sizeof(wchar_t));
            if(size<=sizeof(int)*(k+1)){
                dates = realloc(dates, size+BUF_SIZE*sizeof(int));
                if(!dates){
            	wprintf(L"ошибка выделения памяти");
            	break;
            	}
                size+=BUF_SIZE;
            }
            dates[k] = 10000*wcstol(str_orig+(t - str_copy), NULL, 10) + 100*wcstol(str_orig+(t - str_copy+5), NULL, 10) + wcstol(day, NULL, 10); 
            dates[k]*=10;
            k++;
		
	str_copy[t-str_copy] = 'g';
	free(day);
    	}
    }while(t);
        
    free(str_copy);
      }
      qsort(dates, k, sizeof(int), compare);
      for(int m = 0; m < k; m++){
      struct tm *timeinfo;
      time_t now = time(0); 
      timeinfo = gmtime(&now);
      timeinfo->tm_mday = dates[m]/10%100;
      timeinfo->tm_year = dates[m]/10/10000 - 1900;      
      timeinfo->tm_mon = (dates[m]/10/100)%100 - 1;  
      if(dates[m]%10==5){
      wcsftime(strtime, 20, L"%d/%m/%Y", timeinfo);
      wprintf(L"%ls\n", strtime);
      }else{
      wcsftime(strtime, 20, L"%Y-%m-%d", timeinfo);
      wprintf(L"%ls\n", strtime);
      }
    }
    dates = realloc(dates, k*sizeof(int));
    free(dates);
};

