// ==============================================================
// Author: CJ Grady
// Date:   November 14, 2012
// ==============================================================

#include "GeoHeap.h"
#include "GeoNode.h"

// The following 3 lines are added because of the "error C2371" while compiling using VC++ 2010 on 64-bit machine
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

//------------------------------- MATLAB -------------------------------------//
 #define toSysout(...) printf(__VA_ARGS__)
 #define exit_with_error(...)           \
 do {                                   \
		 fprintf(stdout, "Error: ");    \
		 fprintf(stdout, __VA_ARGS__ ); \
		 fprintf(stdout, "\n" );        \
		 exit(1);                       \
 } while(0)
#ifdef MATLAB_MEX_FILE
#include "mex.h"

void retrieve_heap(const mxArray* matptr, GeoHeap<GeoNode>* & heap)
{
    // retrieve pointer from the MX form
    double* pointer0 = mxGetPr(matptr);
    // check that I actually received something
    if( pointer0 == NULL )
        mexErrMsgTxt("vararg{1} must be a valid priority queue pointer\n");
    // convert it to "long" datatype (good for addresses)
    long pointer1 = (long) pointer0[0];
    // convert it to "KDTree"
    heap = (GeoHeap<GeoNode>*) pointer1;
    // check that I actually received something
    if( heap == NULL )
        mexErrMsgTxt("vararg{1} must be a valid priority queue pointer\n");
}
void retrieve_index_key(const mxArray* matptr, long& idxKey){
	// check that I actually received something
	if( matptr == NULL )
		mexErrMsgTxt("missing second parameter (indexed key)\n");

	if( 1 != mxGetM(matptr) || !mxIsNumeric(matptr) || 1 != mxGetN(matptr) )
		mexErrMsgTxt("second parameter should be a long index\n");

	// retrieve index
	idxKey = (long) mxGetScalar(matptr);

	if( idxKey % 1 != 0 )
		mexErrMsgTxt("the index should have been a long integer!\n");
}

void retrieve_heap_key_cost(const mxArray* matptr, double& cost){
	// check that I actually received something
	if( matptr == NULL )
		mexErrMsgTxt("missing third parameter (element index)\n");

	if( 1 != mxGetM(matptr) || !mxIsNumeric(matptr) || 1 != mxGetN(matptr) )
		mexErrMsgTxt("third parameter should be cost\n");

	// retrieve index
	cost = (double) mxGetScalar(matptr);
}

void retrieve_heap_key_backLink(const mxArray* matptr, long& preNodeIdx){
	// check that I actually received something
	if( matptr == NULL )
		mexErrMsgTxt("missing fourth parameter (element index)\n");

	if( 1 != mxGetM(matptr) || !mxIsNumeric(matptr) || 1 != mxGetN(matptr) )
		mexErrMsgTxt("fourth parameter should be water volume\n");

	// retrieve index
	preNodeIdx = (long) mxGetScalar(matptr);
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
	if( nrhs!=5 )
		mexErrMsgTxt("This function requires 4 arguments\n");
	if( !mxIsNumeric(prhs[0]) )
		mexErrMsgTxt("parameter 1 missing!\n");
	if( !mxIsNumeric(prhs[1]) )
		mexErrMsgTxt("parameter 2 missing!\n");
	if( !mxIsNumeric(prhs[2]) )
		mexErrMsgTxt("parameter 3 missing!\n");
	if( !mxIsNumeric(prhs[3]) )
		mexErrMsgTxt("parameter 4 missing!\n");

	// retrieve the heap
	GeoHeap<GeoNode>*  heap;
	retrieve_heap(prhs[0], heap);
	// retrieve the parameters
	long index;
	retrieve_index_key(prhs[1], index );
	double cost;
	retrieve_heap_key_cost(prhs[2], cost);
	long backLink;
	retrieve_heap_key_backLink(prhs[3], backLink);

	GeoNode hKey(index, cost, backLink);
	// push in the PQ
	heap->push(hKey);

	// return control to matlab
	return;
}
#endif
