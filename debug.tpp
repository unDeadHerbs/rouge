#ifndef __DEBUG_TPP__
#define __DEBUG_TPP__

#include "defines.hpp"
#include "debug.hpp"
#ifdef _UDH_DEBUGGER
#include <iostream>

using std::cout;
using std::endl;
using std::ofstream;

template<typename str>
void debug(int level,str mesg,int warning){
	ofstream logfile;
	logfile.open("warnings.log",std::ios::app);
	if(warning>WARNING){
		#if WARNING>0
			#if DEBUG>0
				for(int i=level;i--;)
					cout<<" ";
				cout<<mesg<<endl;
				usleep(1000000);
			#endif
			#if DEBUG==0 || DEBUGLOG>0
				if(!warning)
					logfile << "DEBUG";
				else
					logfile << "WARNING";
				logfile << "[" << time(nullptr) << "]: ";
				for(int i=level;i--;)
					logfile << " ";
				logfile << mesg << "\n";
				logfile.close();
			#endif
		#endif
	}else{
		#if DEBUG>0
			if(DEBUG+1>level){
				for(int i=level;i--;)
					cout<<" ";
				cout<<mesg<<endl;
				usleep(1000000);
			}
		#endif
		#if ( DEBUG==0 || DEBUGLOG>0 ) && WARNING!=0
			if(!warning)
				logfile << "DEBUG";
			else
				logfile << "WARNING";
			logfile << "[" << time(nullptr) << "]: ";
			for(int i=level;i--;)
				logfile << " ";
			logfile << mesg << "\n";
			logfile.close();
		#endif
	}
}

template<typename str>
void debug(int level,str mesg,bool warning){
	if(warning)
		debug(level,mesg,level);
	else
		debug(level,mesg,0);
}
template<typename str>
void debug(str mesg,bool warning){
	debug(0,mesg,warning);
}
template<typename str>
void debugv(int level,str mesg,bool warning){
	#if VERBOSE>0
		if(level<=VERBOSE)
			debug(level,mesg,warning);
	#endif
}
template<typename str>
void debugv(str mesg,bool warning){
	debugv(0,mesg,warning);
}

#endif
#endif
