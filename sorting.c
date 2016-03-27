#include "runner.h"

 /*
  * Comparator will return a positive integer if value 1 is
  * greater and a negative integer otherwise.
  */
 int comparator(value *val1, value *val2){
 	return val1->frequency - val2->frequency;
 }

/*
 * Sort function:
 * merge sort over all elements;
 * run-time nlog(n) 
 */
 value* listSort(value *list){
 	value *p, *q, *e, *tail;
 	int nmerges, psize, qsize, i, insize = 1;

 	while(1){
 		p = list;
 		list = NULL;
 		tail = NULL;
		nmerges = 0;

		while(p){
			nmerges++;
			q = p;
			psize = 0;
			for(i = 0; i < insize; i++){
				psize++;
				q = q->next;
				// Loop ends if list is NULL
				if(!q){
					break;
				}
			}

			qsize = insize;
			// Merge is performed:
			while(psize > 0 || (qsize > 0 && q)){
				/*
				 * If one list is empty, the element
				 * is retrieved from the other list
				 */
				if(psize == 0){
					e = q;
					q = q->next;
					qsize--;
				}
				else if (qsize == 0 || !q){
					e = p;
					p = p->next;
					psize--;
				}
				/*
				 * If neither list is empty,
				 * the first elements are compared
				 */
				else if(comparator(p, q) >= 0){
					e = p;
					p = p->next;
					psize--;
				}
				else{
					e = q;
					q = q->next;
					qsize--;
				}
				/*
				 * The appropriate element is added
				 */
				if(tail){
					tail->next = e;
				}
				else{
					list = e;
				}
				tail = e;
				//printf("sorting %s\n", tail->valueWord);
			}
			p = q;
		}
		tail->next = NULL;
		/*
		 * Base case
		 */
		if(nmerges <= 1){
			return list;
		}
		insize *= 2;
 	}
 }