#include "funciones.h" //Se incluye el .h para las funciones 
#include "fdacoefs2.h" //Se incluyen los coeficientes del filtro

long FIR_p(const int32_t*coeffs, int input) {
    // buffer de entrada
    static int buffer[N_BUFFER] = {0};

    static int *startBuffer = buffer;    //Puntero de la cabeza
    static int *endBuffer = buffer + MASK_Bufer;    //Puntero de la cola

    static int *head = buffer;    //Puntero iterante de la cabeza
    static int *tail = buffer + ((-BL) & MASK_Bufer) ;    //Puntero iterante de la cabeza


    static int *head_i = buffer;    //Puntero iterante de la cabeza
    static int *tail_i = buffer + ((-BL + 1) & MASK_Bufer);    //Puntero iterante de la cola


    static int indexHead = 0; // �ndice del buffer de la cabeza
    static int indexTail = ((-BL + 1) & MASK_Bufer); // �ndice del buffer de la cabeza

    unsigned long output = 0; // valor de salida


    // agregar nuevo valor de entrada al buffer y actualizar el �ndice
    *(head) = input;

    // calcular la salida del filtro
    for (int i = 0; i < BL/2; i++) {

        //Salida acumulador
        output += (unsigned long) *(coeffs++) * ((unsigned long) * (head_i) + (unsigned long) * (tail_i));

        //Verificamos si llegamos a un extremo de la cola para volver
        if(head_i == startBuffer)
        {
            head_i = endBuffer;
        } else
        {
            head_i--;
        }
        if(tail_i == endBuffer)
        {
            tail_i = startBuffer;
        } else
        {
            tail_i++;
        }
        if(head_i == tail_i)
        {
            //Aqui entramos solo si los coheficientes son impares
            output += (unsigned long) *(coeffs) * ((unsigned long) * (head_i));
        }
    }


    indexHead = (indexHead + 1) & MASK_Bufer;
    indexTail = (indexTail + 1) & MASK_Bufer;

    head = (buffer + indexHead);
    tail = (buffer + indexTail);

    head_i = head;
    tail_i = tail;

    return output;
}


long FilterFIR(int input)
{
    //Aqui simplificamos la rutina
    return FIR_p(B, input) >> 16;
}
/***
                   _      <-. (`-')_
         <-.      (_)        \( OO) )
      (`-')-----. ,-(`-') ,--./ ,--/
      (OO|(_\---' | ( OO) |   \ |  |
       / |  '--.  |  |  ) |  . '|  |)
       \_)  .--' (|  |_/  |  |\    |
        `|  |_)   |  |'-> |  | \   |
         `--'     `--'    `--'  `--'
*/
