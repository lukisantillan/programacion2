#include"./TP_2_Listas.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>



double calcular_valor_x(Lista list,double x)
{
    double valor_de_x=0;
    int i;
    TipoElemento item;
    int* aux;
    for ( i = 1; i <= l_longitud(list); i++)
    {
       item= l_recuperar(list,i);
       aux=item->valor;
       valor_de_x+=pow(x,item->clave)*aux[i-1];
       
    }
    
    printf("\n el valor del polinomio en %.2f es: %.2f",x,valor_de_x);
    return valor_de_x;


return 0;

}

int polinomio(Lista list)
{
    int grado,i,grado_multi;
    int coeficiente;
    int* coeficientes;
    int* aux;
    TipoElemento item;
    int inicio_inter,fin_inter,aumentador;

    i=0;
    


    printf("\n por favor, ingrese el grado de su polinomio: ");

    scanf("%i",&grado);

    printf("\n por favor, ingrese el coeficiente principal de su polinomio: ");

    scanf("%i",&coeficiente);

    coeficientes=malloc(sizeof(int)*(grado+1));

    item=te_crear_con_valor(grado,coeficientes);

    l_agregar(list,item);

    coeficientes[i]=coeficiente;
    

    while (grado>0)
    {i++;
        printf("\n por favor, ingrese el exponente de su polinomio: ");

        scanf("%i",&grado);

        printf("\n por favor, ingrese el coeficiente  de su polinomio: ");

        scanf("%i",&coeficiente);

        item= te_crear_con_valor(grado,coeficientes);

        coeficientes[i]=coeficiente;
        l_agregar(list,item);
    }
    
    printf("\n");
    for ( i = 1; i <= l_longitud(list); i++)
    {
        item=l_recuperar(list,i);

        aux=item->valor;

        printf("%ix**%i",aux[i-1],item->clave);
        if (i!=l_longitud(list))
        {
            printf("+");
        }
        
        
    }
    
return 0;
}

Lista rango(Lista list,double x,double y,double sumando)
{
    Lista respuesta;
    TipoElemento item;
   respuesta= l_crear();
    

while (x<=y)
{
    
    item=te_crear(calcular_valor_x(list,x));
    l_agregar(respuesta,item);
    x+=sumando;
    
}
return respuesta;
}

/*int main()
{
    Lista listilla;
    Lista respuesta;
    l_crear(respuesta);
    double resp;
    listilla =l_crear();

   polinomio(listilla);

   respuesta=rango(listilla,-1,1,0.5);
   printf("\n");

   l_mostrar(respuesta);


   
   


    return 0;
}*/