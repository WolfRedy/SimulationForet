#ifndef _EXTGLOB_H_
#define _EXTGLOB_H_

#ifndef _MAIN_
#define _EXTERN extern
#else
#define _EXTERN
#endif

_EXTERN int longueur;
_EXTERN int largeur;
_EXTERN int positionFlameX;
_EXTERN int positionFlameY;
bool isInBound(int x, int y);
#endif