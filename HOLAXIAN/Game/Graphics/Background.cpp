#include "Background.h"

Background::Background(){
    for(int i=0; i<STARS; i+=2){
        stars[i]=0+rand()/(float(RAND_MAX)+1)*(getmaxx());
    }
    for(int i=1; i<STARS; i+=2){
        stars[i]=0+rand()/(float(RAND_MAX)+1)*(getmaxy());
    }
}

void Background::Update(){
    for(int i=1; i<STARS; i+=2){
        if(stars[i]>getmaxy()){
            stars[i]=0;
        }else{
            ++stars[i];
        }
    }
}

void Background::Render(){
    setcolor(COLOR_STARS);
    for(int i=0; i<STARS; i+=2){
        rectangle(stars[i],stars[i+1],stars[i]+1,stars[i+1]+1);
    }
}
