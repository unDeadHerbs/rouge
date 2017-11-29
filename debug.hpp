#include "defines.hpp"

#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#if DEBUGGER > 0
	#ifndef _UDH_DEBUGGER
	#define _UDH_DEBUGGER
	#define NDEBUG
	#define DEBUGLOG 1
	#define DEBUG 0
	#define WARNING 1
	#define VERBOSE 3
	#endif

	#include <unistd.h>
	#if ( DEBUG==0 || DEBUGLOG>0 ) && WARNING!=0
		#include <ctime>
		#include <iostream>
		#include <fstream>
	#endif

	template<typename str>
	void debug(int,str,bool=false);
	template<typename str>
       	void debug(str,bool=false);
	template<typename str>
	void debugv(int,str,bool=false);
	template<typename str>
	void debugv(str,bool=false);
#else
	#define debug(...) ;
	#define debugv(...) ;
	#define delay(...) ;
#endif
#include <cassert>
#include "debug.tpp"
#endif
