#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static size_t my_len(const char *s) {
    size_t n = 0;
    while (s[n] != '\0') n++;
    return n;
}
static char lower_char(char c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    return c;
}
char *str_find_char(const char *s, char c) {
    size_t i = 0;
    while (1) {
        if (s[i] == c) return (char *)(s + i);
        if (s[i] == '\0') return NULL;
        i++;
    }
}
void str_reverse(char *s) {
    size_t len = my_len(s);
    size_t i;
    for (i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}
int str_compare_ci(const char *s1, const char *s2) {
    size_t i = 0;
    while (1) {
        char a = lower_char(s1[i]);
        char b = lower_char(s2[i]);
        if (a != b) return (a < b) ? -1 : 1;
        if (a == '\0') return 0;
        i++;
    }
}
size_t str_copy_bounded(char *dst, const char *src, size_t size) {
    size_t len = my_len(src);
    size_t i;
    if (size == 0) return len;
    for (i = 0; i + 1 < size && src[i] != '\0'; i++) dst[i] = src[i];
    dst[i] = '\0';
    return len;
}
const char *str_find_sub(const char *hay, const char *needle) {
    size_t i, j;
    if (needle[0] == '\0') return hay;
    for (i = 0; ; i++) {
        for (j = 0; needle[j] != '\0'; j++) {
            if (hay[i + j] == '\0') break;
            if (hay[i + j] != needle[j]) break;
        }
        if (needle[j] == '\0') return hay + i;
        if (hay[i] == '\0') return NULL;
    }
}
size_t str_squeeze(char *s) {
    size_t r = 0, w = 0;
    int in_word = 0, need_space = 0;
    while (s[r] != '\0') {
        char c = s[r];
        if (c == ' ' || c == '\t') {
            if (in_word) need_space = 1;
            r++;
        } else {
            if (need_space) { s[w] = ' '; w++; need_space = 0; }
            s[w] = c; w++; in_word = 1; r++;
        }
    }
    s[w] = '\0';
    return w;
}
int str_split(char *s, char delim, char **fields, int max_fields) {
    int count = 1, stored = 0;
    size_t i = 0;
    if (max_fields > 0) { fields[0] = s; stored = 1; }
    while (s[i] != '\0') {
        if (s[i] == delim) {
            s[i] = '\0'; count++;
            if (stored < max_fields) { fields[stored] = s + i + 1; stored++; }
        }
        i++;
    }
    return count;
}
int main(void) {
    char a[] = "  hello   world  ";
    char b[] = "red,green,blue";
    char *f[5] = {0};
    char dst[10] = {0};
    char rev[] = "hello";
    char *ch;
    const char *sub;
    size_t sq;
    int nsplit;
    size_t copied;

    ch = str_find_char("hello", 'l');
    printf("find_char: %s\n", ch ? ch : "(null)");

    printf("compare_ci: %d\n", str_compare_ci("Hello", "hello"));

    copied = str_copy_bounded(dst, "hello", 4);
    printf("copy_bounded: %lu dst=%s\n", (unsigned long)copied, dst);

    sub = str_find_sub("mississippi", "issip");
    printf("find_sub: %s\n", sub ? sub : "(null)");

    sq = str_squeeze(a);
    printf("squeeze: %lu s=%s\n", (unsigned long)sq, a);

    str_reverse(rev);
    printf("reverse: %s\n", rev);

    nsplit = str_split(b, ',', f, 5);
    printf("split: %d %s|%s|%s\n", nsplit, f[0], f[1], f[2]);

    printf("find_sub tail: %s\n", str_find_sub("hi", "hello") ? "found" : "not found");
    printf("find_sub empty: %s\n", str_find_sub("hi", ""));
    return 0;
}
