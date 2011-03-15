
#include <stdio.h>
#include <string.h>


void print_bytes(char ch, int len) 
{
    int i;

    for (i = 0; i < len; i++) {
        printf("%c", ch);
    }
}


int distinguish_utf8(unsigned char *str, size_t len) 
{
    int count;
    unsigned char b1, bn, *start, *p, *last;

    p = str;
    last = str + len;
    count = 0;

    while(p < last) {

        /* See http://en.wikipedia.org/wiki/UTF-8 */
        if ((*p) >= 0x80) {

            start = p;
            b1 = *p++;

            if (p == last) {
                goto end;
            }

            /* 110xxxxx 10xxxxxx */
            if ((b1 >> 5) == 0x06) {
                count = 2;
            }
            /* 1110xxxx 10xxxxxx 10xxxxxx */
            else if ((b1 >> 4) == 0x0e) {
                count = 3;
            }
            /* 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
            else if ((b1 >> 3) == 0x1e) {
                count = 4;
            }
            /* 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
            else if ((b1 >> 2) == 0x3e) {
                count = 5;
            }
            /* 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
            else if ((b1 >> 1) == 0x5e) {
                count = 6;
            }

            while (--count) {
                if (p == last) {
                    goto end;
                }

                bn = *p++;

                if ((bn >> 6) == 0x02) {
                    continue;
                }
                else {
                    break;
                }
            }

            if (count == 0) {
                print_bytes('1', p - start);
            }
            else {
                count = 0;
                print_bytes('0', p - start);
            }
        }
        else {
            /* 0xxxxxxx */
            p++;
            print_bytes('1', 1);
        }
    }

    printf("\n");
    return 0;

end:

    print_bytes('0', p - start);

    printf("\n");

    return 0;
}

/* The output string meaning: 1 stands for utf-8 byte, 0 stands for gbk byte*/

int main () 
{
    char *utf8_str = "a你好你好";
    char *gbk_str = "a\xC4\xE3\xBA\xC3\xC4\xE3\xBA\xC3";

    distinguish_utf8((unsigned char *)utf8_str, strlen(utf8_str)); 
    distinguish_utf8((unsigned char *)gbk_str, strlen(gbk_str)); 

    return 0;
}

