#include "ring.h"

#include "stdlib.h"

RING_FUNC(ring_myfunction)
{
	printf("Hello, World!\n");
}

RING_FUNC(ring_sumtwonumbers)
{
	double nNum1,nNum2,nSum;
	// Check Parameters Count
		if (RING_API_PARACOUNT != 2) {
			RING_API_ERROR(RING_API_MISS2PARA);
			return;
		}
	// Check Parameters Type
		if ( ! (RING_API_ISNUMBER(1) && RING_API_ISNUMBER(2)) ) {
			RING_API_ERROR(RING_API_BADPARATYPE);
			return;
		}
	// Sum Numbers 
		nNum1 = RING_API_GETNUMBER(1);
		nNum2 = RING_API_GETNUMBER(2);
		nSum  = nNum1 + nNum2 ;
	// Return Output
		RING_API_RETNUMBER(nSum);
}

RING_FUNC(ring_sayhello)
{
	// Check Parameters Count
		if (RING_API_PARACOUNT != 1) {
			RING_API_ERROR(RING_API_MISS1PARA);
			return;
		}
	// Check Parameters Type
		if ( ! RING_API_ISSTRING(1) ) {
			RING_API_ERROR(RING_API_BADPARATYPE);
			return;
		}
	printf("Hello %s\n",RING_API_GETSTRING(1));
}

RING_FUNC(ring_sumlist)
{
	List *pList;
	int x,nSum;
	// Check Parameters Count
		if (RING_API_PARACOUNT != 1) {
			RING_API_ERROR(RING_API_MISS1PARA);
			return;
		}
	// Check Parameters Type
		if ( ! RING_API_ISPOINTER(1) ) {
			RING_API_ERROR(RING_API_BADPARATYPE);
			return;
		}
	// Sum List Numbers 
		nSum = 0;
		pList = RING_API_GETLIST(1);
		for(x=1 ; x <= ring_list_getsize(pList) ; x++) {
			if ( ring_list_isdouble(pList,x) ) {
				nSum += (int) ring_list_getdouble(pList,x) ;
			}
		}
	// Return Output 
		RING_API_RETNUMBER(nSum);
}

RING_FUNC(ring_inclist)
{
	List *pList;
	int x,nSum;
	// Check Parameters Count
		if (RING_API_PARACOUNT != 2) {
			RING_API_ERROR(RING_API_MISS2PARA);
			return;
		}
	// Check Parameters Type
		if ( ! ( RING_API_ISPOINTER(1) && RING_API_ISNUMBER(2) ) ) {
			RING_API_ERROR(RING_API_BADPARATYPE);
			return;
		}
	// Increment List Items
		nSum = 0;
		pList = RING_API_GETLIST(1);
		for(x=1 ; x <= ring_list_getsize(pList) ; x++) {
			if ( ring_list_isdouble(pList,x) ) {
				ring_list_setdouble(pList,x,ring_list_getdouble(pList,x)+RING_API_GETNUMBER(2)) ;
			}
		}
	// Return Output
		RING_API_RETLIST(pList);
}

RING_FUNC(ring_filterlist)
{
	List *pList;
	int x;
	// Check Parameters Count
		if (RING_API_PARACOUNT != 2) {
			RING_API_ERROR(RING_API_MISS2PARA);
			return;
		}
	// Check Parameters Type
		if ( ! ( RING_API_ISPOINTER(1) && RING_API_ISNUMBER(2) ) ) {
			RING_API_ERROR(RING_API_BADPARATYPE);
			return;
		}
	// Filter List Items
		pList = RING_API_GETLIST(1);
		for(x = ring_list_getsize(pList) ; x >= 1 ; x--) 
			if ( ring_list_isdouble(pList,x) ) 
				if ( ! (ring_list_getdouble(pList,x) > RING_API_GETNUMBER(2)) )
					ring_list_deleteitem(pList,x) ;
	// Return Output
		RING_API_RETLIST(pList);
}

RING_API void ringlib_init(RingState *pRingState)
{
	ring_vm_funcregister("myfunction",ring_myfunction);
	ring_vm_funcregister("sumtwonumbers",ring_sumtwonumbers);
	ring_vm_funcregister("sayhello",ring_sayhello);
	ring_vm_funcregister("sumlist",ring_sumlist);
	ring_vm_funcregister("inclist",ring_inclist);
	ring_vm_funcregister("filterlist",ring_filterlist);
}
