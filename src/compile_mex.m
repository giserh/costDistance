% compile the heap C++ library 
%
% Copyright (c) 2012 CJ Grady
% All Rights Reserved
% email: cjgrady@ku.edu

clc, clear, close all;
mex heapCreate.cpp;
mex heapDelete.cpp;

mex heapEmpty.cpp

mex heapPush.cpp; 
mex heapPop.cpp; 

