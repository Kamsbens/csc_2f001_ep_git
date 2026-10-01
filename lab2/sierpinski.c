#include <stdio.h>

int sort_get_index(float tab[], int top, float val);
void sort_insert_at(float tab[],int i,int top,float val);
void sort_insert(float tab[], int top, float val);



int main(void){
    float tab[5] = {1,3,5,7,0};
    for(int i =0;i<5;i++){
        printf("%f  ",tab[i]);
    };
    /*
    //TESTS 
    float new_nb = 2; 
    int new_pos = sort_get_index(tab,4,new_nb);
    printf("\nInsert %f at %i \n",new_nb,new_pos);
    sort_insert_at(tab,new_pos,4,new_nb);

    for(int i =0;i<5;i++){
        printf("%f  ",tab[i]);
    }
    */
    printf("\n\n");

    sort_insert(tab,4,2);
    for(int i =0;i<5;i++){
        printf("%f  ",tab[i]);
    };
}


int sort_get_index(float tab[],int top,float val){
    //returns the potential position of val in the sorted array tab
    int res=-1;
    for(int i =0;i<top;i++){
        if (val<tab[i]){
            res = i;
            return res;
        }
    }
    return top;
};

void sort_insert_at(float tab[],int i,int top,float val){
    for (int j=top;j>i;j--){
        tab[j] = tab[j-1];
    }
    tab[i] = val; 
};

void sort_insert(float tab[], int top, float val){
    int new_index = sort_get_index( tab, top, val);
    sort_insert_at(tab,new_index, top, val);
};

