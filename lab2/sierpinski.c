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
void plot_vline(char grid[],int x, float fy0, float fy1, char pixel);

struct point{
    float x;
    float y;
};

void plot_poly_sweep(char grid[],struct point tab[],int nb_points,int x_coord_swept,char pixel);
void plot_poly(char grid[],struct point tab[],int nb_points,char pixel);

void plot_triangle(char grid[],struct point p1, struct point p2, struct point p3,char pixel);
struct point line_middle(struct point p1, struct point p2);
void sierpinski(char grid[],struct point p1, struct point p2, struct point p3,int n, char pixel);



int main(void){
    char grid[nb_columns()*nb_lines()];
    grid_init(grid,' ');
    //struct point p[] = {{ 2, 13 }, { 10, 13 }, { 30, 7 }, { 10, 1 }, { 2, 1 }, { 18, 7 }};
    //plot_poly(grid,p,6,'*');

    struct point p1 = {.x=0 , .y=0};
    struct point p2 = {.x=64 , .y=64};
    struct point p3 = {.x=128 , .y=0};
    sierpinski(grid,p1,p2,p3,6,'*');
    grid_display(grid);

    return 0;
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
}

void sort_insert_at(float tab[],int i,int top,float val){
    for (int j=top;j>i;j--){
        tab[j] = tab[j-1];
    }
    tab[i] = val; 
}

void sort_insert(float tab[], int top, float val){
    int new_index = sort_get_index( tab, top, val);
    sort_insert_at(tab,new_index, top, val);
}

// SECOND PART 
int nb_columns(){
    return 129;
}
int nb_lines(){
    return 65;
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


void plot_vline(char grid[],int x, float fy0, float fy1, char pixel){
    //Lets first convert fy0 and fy1 
    int y0 = (int)(fy0+0.5);
    int y1 = (int)(fy1+0.5);
    if(fy0==y0-0.5){
        y0=y0-1;
    }
    for(int y=y0;y<=y1;y++){
        plot_point(grid,x,y,pixel);
    };
}

void plot_poly_sweep(char grid[],struct point p[],int n,int x,char pixel){
    float vlines[n*4]; 
    int top =0; 
    //printf("sweep %i: ",x);
    for(int k=0;k<n;k++){
        int i;
        int j;
        if (k==0){
            j = n-1;
            i = k; 
        }
        else{
        j = k-1;
        i = k; 
        };
        //Question 20 
                if (p[i].x == x){
            if (p[j].x==x){
                if (p[i].y < p[j].y){
                    plot_vline(grid,x,p[i].y,p[j].y,pixel);
                }
                else {
                    plot_vline(grid,x,p[j].y,p[i].y,pixel);
                }
            }
            else {
                plot_vline(grid,x,p[i].y,p[i].y,pixel);
            }
        }
        // End of Question 20 

        if((x>= p[i].x && x<p[j].x) || (x>= p[j].x && x<p[i].x)){
            float intersec_y = p[i].y + (x - p[i].x) * (p[j].y - p[i].y) / (p[j].x - p[i].x);
            sort_insert(vlines,top,intersec_y);
            top+=1;
        };

    };
    /*
    for(int i=0;i<top;i++){
    printf("%f ",vlines[i]);
    }
    */
    for(int m=0;m<top;m+=2){
        plot_vline(grid,x,vlines[m],vlines[m+1],pixel);
    }
    //printf("\n");
}

void plot_poly(char grid[],struct point tab[],int nb_points,char pixel){
    for(int x=0;x<nb_columns();x++){
        plot_poly_sweep(grid,tab,nb_points,x,pixel);
    }
}

void plot_triangle(char grid[],struct point p1, struct point p2, struct point p3,char pixel){
    struct point tab[] = {p1,p2,p3};
    plot_poly(grid, tab, 3, pixel);
}

struct point line_middle(struct point p1, struct point p2){
    float xmid = (p1.x+p2.x)/2;
    float ymid = (p1.y+p2.y)/2;
    struct point p3 = {.x=xmid, .y=ymid};
    return p3;
}

void sierpinski(char grid[],struct point p1, struct point p2, struct point p3,int n, char pixel){
    if (n==1){
        plot_triangle(grid,p1,p2,p3,pixel);
    }
    else {
        //Remove the central triangle first : 
        struct point p1mid = line_middle(p1,p2);
        struct point p2mid = line_middle(p2,p3);
        struct point p3mid = line_middle(p1,p3);
        plot_triangle(grid,p1mid,p2mid,p3mid,' ');

        struct point triangle1[3] = {p1, p1mid, p3mid};
        struct point triangle2[3] = {p1mid, p2, p2mid};
        struct point triangle3[3] = {p3mid, p2mid, p3};

        sierpinski(grid,triangle1[0],triangle1[1],triangle1[2],n-1,pixel);
        sierpinski(grid,triangle2[0],triangle2[1],triangle2[2],n-1,pixel);
        sierpinski(grid,triangle3[0],triangle3[1],triangle3[2],n-1,pixel);

        
    }
}