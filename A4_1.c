#include <stdio.h>

int main() {
    char v_as;
    char arrA[16] = "1234567890abcdef";
    char* arrB[16];
    char amount_of_pairs = 0;
    char str_len = sizeof(arrA);


    for(char i = 0; i < str_len; i++)
    {
        scanf("%hhd", arrA + i);
        arrB[i] = 0;
    }
    __asm__(// Clear registers
            "and eax, 0x0\n\t"
            "and ebx, eax\n\t"
            "and ecx, eax\n\t"
            "and edx, eax\n\t"
            "and esi, eax\n\t"
            "and edi, eax\n\t"
            // Init cycle counter. (size)/2 steps are required
            "mov al, %2\n\t"
            "mov bl, 2\n\t"
            "div bl\n\t"
            "mov cl, al\n\t"
            "and ebx, 0x0\n\t"
            // There will be two counters: cx and di.
            // Ax - not in use
            // Bx - count of pairs and comparision
            // Cx - counter and left part
            // Dx - comparision
            // Di - right part 
            // Si - swap 
            "mov di, cx\n\t"
            "dec di\n\t"
            // Init pairs count on stack
            "push 0x0\n\t"
            // Begin cycle
            // In address dereferences using ecx, 1 is subtracted because the values of ecx are [8,7,...,2,1]
            "\nbegin:\n\t"
            "inc di\n\t"
            // Load values and check condition |a - b| = 2
            "and edx, 0x0\n\t"
            "mov bl, [%0 + ecx - 1]\n\t"
            "mov dl, [%0 + edi]\n\t"
            // Increase first operand on two. If overflowed - skip this part of comparision
            "add bl, 2\n\t"
            "jo second\n\t"
            // If they are equal, then condition is true
            "cmp bl, dl\n\t"
            "je swap"
            // If they are not equal, then there is might be situation b = a-2
            "\nsecond:\n\t"
            "sub bl, 4\n\t"
            "jo skip\n\t"
            "cmp bl, dl\n\t"
            "je swap\n\t"
            // If both conditions are false, then skip iteration
            "jmp skip\n\t"
            // Append in arrB pairs from arrA 
            // Value of ebx multiplied by 4 due to address size
            // Which is 4 bytes
            "\nswap:\n\t"
            "pop ebx\n\t"
            "lea esi, [%0 + ecx - 1]\n\t"
            "mov [%1 + ebx*4], esi\n\t"
            "inc ebx\n\t"
            "lea esi, [%0 + edi]\n\t"
            "mov [%1 + ebx*4], esi\n\t"
            "inc ebx\n\t"
            "push ebx\n\t"
            //Cycle skip mark
            "\nskip:\n\t"
            "loop begin\n\t"
            // End of procedure
            "\nend: nop\n\t"
            // Counting pairs
            "pop ebx\n\t"
            "and eax, 0x0\n\t"
            "mov al, bl\n\t"
            "mov bl, 2\n\t"
            "div bl\n\t"
            "mov %3, al\n\t"
            :
            :"m"(arrA[0]), "m"(arrB[0]), "m"(str_len), "m"(amount_of_pairs)
            :"eax", "ebx", "ecx", "edx", "esi", "edi");
    

    for(char i = 0; i < amount_of_pairs*2; i++)
        printf("%x\n", arrB[i]);
    
    printf("Amount of pairs: %d\n", amount_of_pairs);
}
