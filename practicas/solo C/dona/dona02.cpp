#include <stdio.h>
#include "conio2.h"
#include <unistd.h>
#include <string.h>
#include <math.h>

const float theta_spacing = 0.07;
const float phi_spacing = 0.02;

const float R1 = 2;
const float R2 = 4;
const float K2 = 5;
// Calcular K1 en funcion del tamano de la pantalla: la distancia x maxima se produce
// aproximadamente en el borde del toroide, que esta en x=R1+R2, z=0
// queremos que este desplazado 3/8 de la anchura de la pantalla, lo que
// es 3/4 del camino desde el centro hasta el lado de la pantalla.
// ancho_pantalla*3/8 = K1*(R1+R2)/(K2+0)
// ancho_pantalla*K2*3/(8*(R1+R2)) = K1
const float K1 = screen_width * K2 * 3 / (8 * (R1));

render_frame(float A, float B)
{
    // precalcular senos y cosenos de A y B
    float cosA = cos(A), sinA = sin(A);
    float cosB = cos(B), sinB = sin(B);

    char output[0..screen_width, 0..screen_height] = ' ';
    float zbuffer[0..screen_width, 0..screen_height] = 0;

    // theta rodea el circulo transversal de un toroide
    for (float theta = 0; theta < 2 * pi; theta += theta_spacing)
    {
        // precalcular senos y cosenos delta
        float costheta = cos(theta), sintheta = sin(theta);

        // phi rodea el centro de revolucion de un toroide
        for (float phi = 0; phi < 2 * pi; phi += phi_spacing)
        {
            // precompute sines and cosines of phi
            float cosphi = cos(phi), sinphi = sin(phi);

            // la coordenada x,y del circulo, antes de girar (factorizado
            // de las ecuaciones anteriores)
            float circlex = R1 * costheta;
            float circley = R1 * sintheta;

            // coordenada 3D final (x,y,z) despues de las rotaciones, directamente de
            // nuestra matematica anterior
            float x = circlex * (cosB * cosphi + sinA * sinB * sinphi) - circley * cosA * sinB;
            float y = circlex * (sinB * cosphi - sinA * cosB * sinphi) + circley * cosA * cosB;
            float z = K2 + cosA * circlex * sinphi + circley * sinA;
            float ooz = 1 / z; // "one over z"

            // proyeccion x e y. notese que y se niega aqui, porque y
            // sube en el espacio 3D pero baja en las pantallas 2D.
            int xp = (int)(screen_width / 2 + K1 * ooz * x);
            int yp = (int)(screen_height / 2 - K1 * ooz * y);

            // calcular luminancia. feo, pero correcto.
            float L = cosphi * costheta * sinB - cosA * costheta * sinphi -
                        sinA * sintheta + cosB * (cosA * sintheta - costheta * sinA * sinphi);
            // L oscila entre -sqrt(2) y +sqrt(2).  Si es < 0, la superficie
            // esta apuntando lejos de nosotros, asi que no nos molestaremos en trazarla.
            if (L > 0)
            {
                // prueba contra el bufer z. 1/z mas grande significa que el pixel esta
                // mas cerca del visor de lo que ya esta trazado.
                if (ooz > zbuffer[xp, yp])
                {
                    zbuffer[xp, yp] = ooz;
                    int luminance_index = L * 8;
                    // luminance_index esta ahora en el rango 0..11 (8*sqrt(2) = 11.3)
                    // ahora buscamos el caracter correspondiente a la
                    // luminancia y lo trazamos en nuestra salida:
                    output[xp, yp] = ".,-~:;=!*#$@"[luminance_index];
                }
            }
        }
    }

    // ahora, vuelca output[] a la pantalla.
    // lleva el cursor a la posicion "home", en casi cualquier modulacion de
    // emulacioon de terminal
    printf("\x1b[H");
    for (int j = 0; j < screen_height; j++)
    {
        for (int i = 0; i < screen_width; i++)
        {
            putchar(output[i, j]);
        }
        putchar('\n');
    }
}