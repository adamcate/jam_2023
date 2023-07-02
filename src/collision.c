#include "../include/collision.h"

bool circle_overlaps(circle_t *c1, circle_t *c2){
    float dist = (c1->x - c2->x) * (c1->x - c2->x) + (c1->y - c2->y) * (c1->y - c2->y);
	
	float threshold = (c1->r + c2->r) * (c1->r + c2->r);
	
	if (dist > threshold) return false;
	
	return true;
}