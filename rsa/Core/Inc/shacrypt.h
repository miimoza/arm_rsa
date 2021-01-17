#include <stdlib.h>
#include "main.h"


#define SHA256_LEN 32

#define PRIVATE_KEY "-----BEGIN RSA PRIVATE KEY-----\n\
MIIEogIBAAKCAQEArYSwrMhUl0PUfcloj6pn3DOxpf2COdPVsTUexSjx7BNhdNFr\n\
1NW4drO3qxRueldwPx+NgeEKV+H5TuYb0t8I/G2eIKSUtCOmu7cux1VXoTCP/Gs1\n\
0RIBhyfcoSrNTccr2SXW07XI2hnFb3EYrgbk6+VgSgq6wqTVv17U16F/eJn5asLn\n\
9E3zyx1HwqLlZN+7qqN0DLlDChiKrbnzAXQYNYQr+vqlO7RdiQKm+/DNp/f29ldI\n\
/33VtVJ7p44WH2JdGQ0Yi8rRY+QKcyW9AuO3Luu2SKJXZe1/j4RnDTuvfiahK5g9\n\
rUwZUhMFm3MDwL7tqEd+qX1o50DxbUYUYCiXbQIDAQABAoIBAA/G++WKBZ8HbN/P\n\
G3HMtcrg7GtCZL/rUgfd46FburuTe44KqLpegHpSlwW4Qt9e6fbjYJOJqc4Z3vhc\n\
lfUTkJabRQCE1nyWrUduPZOkX+ZpKv5xpSAQehEW/8mrwaUr0gHZnfH8GnoyU7Bx\n\
YSQZvmDwp1O0LA0cvc67ybCdn6CQgR+FsjkNKINZE3HOnPf8iQftai1/xPQ5qnuf\n\
Iv+/cbgFFiq7UzfGCfJ95m1Gz3Qv/K86gtGYe219rltsEUhvzwI3Pi42Mewcq7A1\n\
9MEuS8bUocf+MRwdpAjo9hFGJTnti5Whrc6icxOlksvBMVTZsXt/0cw3W3PUefiD\n\
uVuYeYECgYEA4kfLvsD61di8+hYxhkCwCWNovExQ15HdTGdS7Mpv4QZdGR1BFo5x\n\
WWrSru6pQNDiRfTmfYIGwubTra16YQwyoRw934y7rjZRnMv/K4G9asmGcwxbT6Qg\n\
gIMzalpIwRxPCqOk6Ijab/Lw9D6H/QCFTvQ+xKHjsYfoRFFrFbFsKA0CgYEAxE7g\n\
6yJAyqsJcl3duhr4nuIf8vRZXUADR1PHh3y4zOFyKP+ZbNzkxfmBgs5KI6xzAaz4\n\
7w58ZkeNdedp+/AKgvpvk352iXQAVES+eivUEwnqab5yt2h/RlajQcTarhxMofNs\n\
+iOd4U070y93daweXm0uAN6cF+VipstGcaFh9OECgYADUWwyauACvL/gpuyo/E/Y\n\
g2WoxTG2R4RIN4emwz0qvo4k7SHkM8iDuCZIvGUs9yMqRXIPyxVQTFQ0SsPtomEn\n\
raNWoNirsE44D2G5gJiHdVcMXtUD8PMtDz90wsgoVMLv9ABaDI+vbo+L9VLHKffK\n\
dZhqB7mwA78rKUp5sfVVDQKBgDEB5CKvTW+LHXOgvV7dpt27Y/B6Uej2txrSboiD\n\
eXskeSSFEt9bkf1emZd3OokHXzq23PqJKkM6b7VUjV/pACbMsJgoxRzxibd/5fGI\n\
CYyrOAsoEWl6O/PqYx1jMJiw1ezEYZtc0uhRKLNDMVZ+HqLCLO7opB1PFb7AFpj9\n\
if/hAoGAMDBz25jNhQwv7ek5VTkhSLG8G1Ct0tsw6NEEu9abHAlpnP53t0d2h/po\n\
ZD/spv8IN8e2+TnIIfA2hDKSU/2rBOE/PW9yY+bWiMOiCx1Dao5NZueubmGHGCXE\n\
aIcsSeGMo3M/FlxBt9Z51qMrpaNAoixLsdkzh1b9rO/BMTB61yI=\n\
-----END RSA PRIVATE KEY-----\n"

#define PRIVATE_KEY_LEN 1675

int rsa_wrapper(UART_HandleTypeDef *huart2);
unsigned long long uart_main(uint8_t *rsa_secret_key, char *passphrase, uint8_t *hash, uint8_t *encoded_hash);
uint8_t *get_secret_key();
