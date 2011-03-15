
#include <stdio.h>
#include <string.h>


int is_gbk(unsigned char head, unsigned char tail)
{

    printf("head = %X, tail = %X\n", head, tail);

    /* See http://en.wikipedia.org/wiki/GBK */
    /* Level GBK/1 */
    if (head >= 0xA1 && head <= 0xA9 && tail >= 0xA1 && tail <= 0xFE) {
        return 1;
    }

    /* Level GBK/2 */
    if (head >= 0xB0 && head <= 0xF7 && tail >= 0xA1 && tail <= 0xFE) {
        return 1;
    }

    /* Level GBK/3 */
    if (head >= 0x81 && head <= 0xA0 && tail >= 0x40 && tail <= 0xFE && tail != 0x7F) {
        return 1;
    }

    /* Level GBK/4 */
    if (head >= 0xAA && head <= 0xFE && tail >= 0x40 && tail <= 0xA0 && tail != 0x7F) {
        return 1;
    }

    /* Level GBK/5 */
    if (head >= 0xA8 && head <= 0xA9 && tail >= 0x40 && tail <= 0xA0 && tail != 0x7F) {
        return 1;
    }

    /* user-defined */
    if (head >= 0xAA && head <= 0xAF && tail >= 0xA1 && tail <= 0xFE) {
        return 1;
    }

    /* user-defined */
    if (head >= 0xF8 && head <= 0xFE && tail >= 0xA1 && tail <= 0xFE) {
        return 1;
    }

    /* user-defined */
    if (head >= 0xA1 && head <= 0xA7 && tail >= 0x40 && tail <= 0xA0 && tail != 0x7F) {
        return 1;
    }

    return 0;
}


int distinguish_gbk(unsigned char *str, size_t len) 
{
    unsigned char head, tail, *p, *last;

    p = str;
    last = str + len;

    while(p < last) {

        if ((*p) >= 0x80) {

            head = *p;
            p++;

            if (p == last) {
                printf("0\n");
                return 0;
            }

            tail = *p;

            if (is_gbk(head, tail)) {
                printf("11");
            }
            else {
                printf("00");
            }
        }
        else {
            printf("0");
        }

        p++;
    }

    printf("\n");

    return 0;
}


int main () 
{
    char *utf8_str = "a你好你好";
    char *gbk_str = "a\xC4\xE3\xBA\xC3\xC4\xE3\xBA\xC3";

    distinguish_gbk((unsigned char *)utf8_str, strlen(utf8_str)); 
    distinguish_gbk((unsigned char *)gbk_str, strlen(gbk_str)); 

    return 0;
}

