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

void retrieve_heap( const mxArray* matptr, GeoHeap<GeoNode>* & heap){
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
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
	if( nrhs!=1 )
		mexErrMsgTxt("This function requires 1 arguments\n");
	if( !mxIsNumeric(prhs[0]) )
		mexErrMsgTxt("parameter 1 missing!\n");

	// retrieve the heap
	GeoHeap<GeoNode>*  heap;
	retrieve_heap( prhs[0], heap);

	// pop top element in the PQ
	plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
	*mxGetPr(plhs[0]) = heap->empty();
}
#endif
