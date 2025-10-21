#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// ================= Base64 解码函数 =================
static const int B64index[256] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,63,52,53,54,55,56,57,58,59,60,61,0,0,0,64,0,0,
    0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,
    0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51
};

unsigned char* b64decode(const char *src, size_t len, size_t *out_len) {
    unsigned char *out, *pos;
    size_t i, count, pad = 0;
    if (len % 4 != 0) return NULL;

    // 计算输出长度
    for (i = 0; i < len; i++) {
        if (src[i] == '=') pad++;
    }
    count = (len / 4) * 3 - pad;
    out = malloc(count + 1);
    if (!out) return NULL;

    pos = out;
    for (i = 0; i < len; i += 4) {
        int n = (B64index[(int)src[i]] << 18) |
                (B64index[(int)src[i+1]] << 12) |
                (B64index[(int)src[i+2]] << 6) |
                (B64index[(int)src[i+3]]);
        *pos++ = (n >> 16) & 0xFF;
        if (src[i+2] != '=') *pos++ = (n >> 8) & 0xFF;
        if (src[i+3] != '=') *pos++ = n & 0xFF;
    }
    *pos = '\0';
    if (out_len) *out_len = count;
    return out;
}
int main() {
    const char *part1 = "QWVnaXN7VzJMQzBNRQ==";
    size_t len1;
    unsigned char *res1 = b64decode(part1, strlen(part1), &len1); 
    printf("%s\n", res1);

    free(res1);  
 return 0;
}    