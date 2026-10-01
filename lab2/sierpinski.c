#include <stdio.h>
#include <stdlib.h>

int sort_get_index(float tab[], int top, float val);
void sort_insert_at(float tab[],int i,int top,float val);
void sort_insert(float tab[], int top, float val);

int nb_columns();
int nb_lines();
void grid_init(char grid[], char pixel);
void grid_display(char grid[]);
void plot_point(char grid[],int x,int y, char pixel);


int main(void){
    char grid[nb_columns()*nb_lines()];
    grid_init(grid,'*');

    plot_point(grid,3,100,' ');
    grid_display(grid);


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

// SECOND PART 
int nb_columns(){
    return 32;
}
int nb_lines(){
    return 16;
}

void grid_init(char grid[], char pixel){
    int total_space = nb_columns()*nb_lines();
    for(int i=0;i<total_space;i++){
        grid[i] = pixel;
    }
}

void grid_display(char grid[]){
    for(int k=0;k<nb_columns()*nb_lines();k+=nb_columns()){
        for(int i=k;i<nb_columns()+k;i++)
            printf("%c",grid[i]);
        printf("\n");
    }
}

void plot_point(char grid[],int x,int y, char pixel){
    //Place the character pixel on the grid 

    //Verify x and y plausible 
    if (x>nb_columns()-1 || x<0 || y > nb_lines()-1 || y < 0){
        printf("Error message\n");
        exit(EXIT_FAILURE);
    }
    int row = nb_lines()-y-1;
    int colomn = x; 
    int index_point = row*nb_columns()+colomn;
    grid[index_point] = pixel;
}
