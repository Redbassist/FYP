#pragma once
#include "stdafx.h" 

//variables being used by threads globally
extern int rw;
extern int nr;
extern std::mutex mutexR;