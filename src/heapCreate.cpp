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

//void retrieve_data(const mxArray* prhs, int& htLength){
//    // retrieve pointer from the MX form
//    // check that I actually received something
////    if( data == NULL )
////        mexErrMsgTxt("vararg{2} must be a [kxN] matrix of data\n");
//
//    htLength = (int) mxGetScalar(prhs);
//    if( htLength == 0 )
//    	mexErrMsgTxt("Heap hash table minimum length is 1.\n");
//}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
	// read the parameters
//	int htLength = 1024;
//	if( nrhs == 1 && mxIsNumeric(prhs[0]) )
//		// retrieve the data
//		retrieve_data( prhs[0], htLength );

	// instantiate the min-heap
    GeoHeap<GeoNode> * heap = new GeoHeap<GeoNode>();

	// convert the points to double
	plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
	double* pointer_to_tree = mxGetPr(plhs[0]);
	pointer_to_tree[0] = (long) heap;
}
#endif
