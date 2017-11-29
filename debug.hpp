#include "defines.hpp"

#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#if DEBUGGER > 0
	#ifndef _UDH_DEBUGGER
	#define _UDH_DEBUGGER
	#define NDEBUG
	#ifndef DEBUGLOG
		#define DEBUGLOG 0
	#endif

	#ifndef DEBUG
		#define DEBUG 0
	#endif
	#ifndef WARNING
		#define WARNING 1
	#endif
	#ifndef VERBOSE
		#define VERBOSE 3
	#endif
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
