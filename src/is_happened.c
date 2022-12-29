#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <time.h>
#include "structs.h"
#include "replace.h"

#define BUF_SIZE 100

void is_happened(struct Text text) {
    wchar_t *strtime = malloc(BUF_SIZE * sizeof(wchar_t));

    wchar_t *month[] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};
    wchar_t *int_month[] = {L"01", L"02", L"03", L"04", L"05", L"06", L"07", L"08", L"09", L"10,", L"11", L"12"};

    for (int i = 0; i < text.num; i++) {
        int k = 0;
        time_t *dates = malloc(BUF_SIZE * sizeof(time_t));
        int size = BUF_SIZE;
        int len = wcslen(text.sents[i]->str);
        wchar_t *str_orig = malloc((len) * sizeof(wchar_t *));
        for (int x = 0; x <= len; x++) {
            str_orig[x] = text.sents[i]->str[x];
        }
        wchar_t *str_copy = malloc((len) * sizeof(wchar_t *));
        for (int x = 0; x <= len; x++) {
            str_copy[x] = str_orig[x];
        }
        for (int mon = 0; mon < 12; mon++) {
            str_copy = replace(str_copy, month[mon], int_month[mon]);
            str_orig = replace(str_orig, month[mon], int_month[mon]);
        }

        for (int j = 0; j <= len; j++) {
            if (isdigit(str_copy[j])) {
                str_copy[j] = '$';
            }
        }
        wchar_t *t;
        do {
            t = wcsstr(str_copy, L"$$ $$ $$$$");
            if (t) {
                wchar_t *year = malloc(4 * sizeof(wchar_t));
                wcsncpy(year, (str_orig + (t - str_copy + 6)), 4 * sizeof(wchar_t));
                if (size <= sizeof(int) * (k + 1)) {
                    dates = realloc(dates, size + BUF_SIZE);
                    if (!dates) {
                        wprintf(L"ошибка выделения памяти");
                        break;
                    }
                    size += BUF_SIZE;
                }
                struct tm *timeinfo;
                time_t now = time(0);
                timeinfo = gmtime(&now);
                timeinfo->tm_mday = wcstol(str_orig + (t - str_copy), NULL, 10);
                timeinfo->tm_year = wcstol(year, NULL, 10) - 1900;
                timeinfo->tm_mon = wcstol(str_orig + (t - str_copy + 3), NULL, 10) - 1;
                dates[k] = mktime(timeinfo);
                time_t seconds;
                seconds = time(NULL);
                wcsftime(strtime, 20, L"%d %m %Y\0", timeinfo);
                if (dates[k] > seconds) {
                    wprintf(L"%ls, %ls\n", strtime, L"Not Happened");
                } else {
                    wprintf(L"%ls, %ls\n", strtime, L"Happened");
                }

                str_copy[t - str_copy] = 'g';
                str_copy[t - str_copy + 3] = 'g';
                str_copy[t - str_copy + 5] = 'g';
                free(year);
                k++;
            }
        } while (t);
        free(str_orig);
        free(str_copy);
        dates = realloc(dates, k * sizeof(int));
        free(dates);
    }
};

