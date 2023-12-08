#include <stdbool.h>
#include "ext_glob.h"
bool isInBound(int x, int y){
    if(x>=longueur || y>=largeur || x<0 || y<0){
        return false;
    }
    return true;
}