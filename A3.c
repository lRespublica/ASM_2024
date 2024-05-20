#include <stdio.h>

void asm_func(char* arr)
{
    __asm__(// Clear registers
            "and rax, 0x0\n\t"
            "and rbx, 0x0\n\t"
            "and rcx, 0x0\n\t"
            // Check condition
            // arr[0] <= arr[1] and arr[2] <= arr[3]
            // If first part is false, jmp to swap
            "mov al, %1\n\t"
            "cmp %0, al\n\t"
            "ja swap\n\t"
            // If second part is false, jmp to swap
            "mov al, %3\n\t"
            "cmp %2, al\n\t"
            "ja swap\n\t"
            // If both parts are true, then
            // Increase first number
            // 9 should be turned into 0
            "mov al, %0\n\t"
            "inc al\n\t"
            // If first num is not 10, then finish
            "cmp al, 10\n\t"
            "jne incr_end\n\t"
            // Else if num is 10, then change value to zero
            "mov al, 0x0\n\t"
            // End of increase procedure
            "\nincr_end:\n\t"
            "mov %0, al\n\t"
            "jmp end\n\t"
            // If condition is false, swap first and last numbers
            "\nswap:\n\t"
            "mov al, %0\n\t"
            "push rax\n\t"
            "mov al, %3\n\t"
            "mov %0, al\n\t"
            "pop rax\n\t"
            "mov %3, al\n\t"
            // End of procedure
            "\nend:\n\t"
            "nop\n\t"
            :
            :"m"(arr[0]), "m"(arr[1]), "m"(arr[2]), "m"(arr[3]) 
            :"ax", "bx", "cx", "dx");
}

int main() {
    char v_as;
    char arr[4] = "9934";
    short int str_size = sizeof(arr);

    for(int i = 0; i < str_size; i++)
    {
        if(arr[i] < '0' || arr[i] > '9')
        {
            fprintf(stderr, "Invalid string\n");
            return 1;
        }
        arr[i] -= '0';
    }
    
    asm_func(arr);

    for(int i = 0; i < str_size; i++)
        arr[i] += '0';

    printf("Asm value is %s\n", arr);
}
