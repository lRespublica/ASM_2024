#include <stdio.h>

int main() {
    int i;
    short int x, z, v, v_c, v_as;
    char y;

    printf("Enter test num\n");
    scanf("%d", &i);

    switch(i)
    {
        case 1:
            x = -0x3;
            y = -0x1;
            z = 0x2;
            v = 0x7;
            break;
        case 2:
            x = 0x7bc2;
            y = 0x7f;
            z = 0x4c;
            v = -0x4857;
            break;
        default:
            printf("Undefined option");
            return 1;
    }

    printf("x: %hx\ny: %hx\nz: %hx\n", x, y, z);

    v_c = 2 - ((z*(x-1) - 2)/(y+3));

    __asm__(// Clear registers
            "and ax, 0x0\n\t"
            "and bx, 0x0\n\t"
            "and cx, 0x0\n\t"
            // Numerator
            "mov ax, %1;\n\t"
            "dec ax;\n\t"
            "imul %3;\n\t"
            "sub ax, 2;\n\t"
            "sbb dx, 0;\n\t"
            // Denomerator
            "mov cl, %2;\n\t"
            "add cl, 3;\n\t"
            // Divison
            "idiv cx;\n\t"
            // Subtract the result from two
            "neg ax;\n\t"
            "add ax, 2;\n\t"
            // Export value
            "mov %0, ax;\n\t"
            :"=m"(v_as)
            :"m"(x), "m"(y), "m"(z)
            :"ax", "bx", "cx");

    printf("Expected value is %hx\n", v);
    printf("Asm value is %hx\n", v_as);
    printf("C value is %hx\n", v_c);
}
