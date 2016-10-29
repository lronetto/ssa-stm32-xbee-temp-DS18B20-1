/*
 * media.h
 *
 *  Created on: 10 de jul de 2016
 *      Author: Leandro
 */

#ifndef INCLUDE_MEDIA_H_
#define INCLUDE_MEDIA_H_

typedef struct{
	int n;
	double vals[100];
}Media_T;

double media_process(Media_T *m,double input);
void media_Init(Media_T *m,int n);
#endif /* INCLUDE_MEDIA_H_ */
