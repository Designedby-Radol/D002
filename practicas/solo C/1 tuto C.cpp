#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main() {
    float A = 0, B = 0;
    float i, j;

    for(;;) {
        float z[1760], b[1760];
        memset(b,32,1760);
        memset(z,0,7040);

        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c=sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;

                float m = cos(B);
                float D = 1 / (c * h * e + f * g + 5);

                float n = sin(B);
                float t=c* h* g - f * e;

                int x = 40 + 30 * D * (1 * h * m - t * n);
                int y = 12 + 40 * (1 - D * n + t * m);

                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[(int)(x + 80 * y)]) {
                    z[(int)(x + 80 * y)] = D;
                }
            }
        }

        printf("\x1b[H");
        for(int k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }

        usleep(30000);
    }

    return 0;
}
// #include <stdio.h>

// int main(){

// 	//imprimir en pantalla

// 	printf("hola estoy aprendiendo C\n");
// 	printf("pene\n"); // \n se utiliza para dar el salto de line

// 	//variables

// 	float joder = 635.98;
// 	char si = 'a';
// 	int resultado; //variable de tipo entero
// 	resultado = 6 * 24;
// 	printf("%d\n", resultado); // %d se utiliza para especificar que se va a imprimir un INT (numero entero)

// 	//pedir el numero en la terminal

// 	int multiplicacion;
// 	int numero1;
// 	int numero2;

// 	printf("dame el numero 1:\n");
// 	scanf("%d", &numero1); // scanf se utiliza para pedir cualquier variable desde terminal
// 	printf("dame el numero 2:\n");
// 	scanf("%d", &numero2);

// 	multiplicacion= numero1 * numero2;
// 	printf("%d\n", multiplicacion);

// 	//condicionales

// 	if (multiplicacion <= 50){
// 		printf("pene penesillo\n");
// 	}
// 	else{
// 	    printf("uy se le paso\n");
// 	}

// 	//condicionales
// 	int x = 20;

// 	  // if/else if

// 	if (x == 20){
//         printf ("x es igual a 20. \n");
// 	}else if(x == 30){
// 	    printf ("x es igual a 30. \n");
// 	}else if(x == 40){
// 	    printf ("x es igual a 40. \n");
// 	}

//       //switch

// 	int c = 30;

// 	switch (c){
//         case 20: //caso de condicional
//         printf ("c es igual a 20. \n");
//         break; //rompimineto de la funcion en caso de que entre a la condicional
//         case 30:
//         printf ("c es igual a 30. \n");
//         break;
//         case 40:
//         printf ("c es igual a 40. \n");
//         break;
//         case 50:
//         printf ("c es igual a 50. \n");
//         break;
//         case 60:
//         printf ("c es igual a 60. \n");
//         break;
//         case 70:
//         printf ("c es igual a 70. \n");
//         break;
//         case 80:
//         printf ("c es igual a 80. \n");
//         break;
// 	}

// 	// bucles

// 	int k = 10;

// 	  //while

// 	while (k > 15){
//         printf("k vale %d\n", k);
//         k++;
// 	}

// 	  //do while

// 	do{
//         printf("k vale %d\n", k);
//         k++;
// 	}while(k < 15);

// 	  //for

//     int i = 0;
//     for(i; i<5; i++){
//         printf("i vale %d\n", i);
//     }

//        //PUNTEROS

//     int g = 10;
//     printf("g = %d\n", g);
//     //& se utiliza para saber en espacio de memoria se encuentra
//     printf(" direccion de memoria de g = %d\n", &g);
// }
