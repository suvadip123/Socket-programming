#include <stdio.h>
#include <string.h>

int main() {
    char rem[50], msg[100], key[50], temp[100];
    int msg_len, key_len, i;

    printf("Enter the dividend :");
    scanf("%s", msg);

    printf("Enter the divisor:");
    scanf("%s", key);

    msg_len = strlen(msg);
    key_len = strlen(key);

    msg[msg_len] = '\0';
    rem[key_len] = '\0';

    // Append 0 at the end
    strcpy(temp, msg);
    for (i = 0; i < key_len-1; i++)
    {
        temp[msg_len + i] = '0';
    }

    
    // XOR operation
    for (int j = 0; j < msg_len; j++)
    {
        if (temp[j] != '0')
        {
            for (int k = 0; k < key_len; k++)
            {
                rem[k] = temp[j+k] = (temp[j+k] == key[k]) ? '0' : '1';
            }
        }
        // printf("%s\n",temp);
        // printf("%s\n",rem);
    }
    // printf("%s\n",temp);
    printf("%s\n",rem);

    // Reduce remainder
    for (int i = 0; i < key_len; i++)
    {
        rem[i] = rem[i+1];
    }
    
    printf("%s",strcat(msg,rem));

    return 0;
}
