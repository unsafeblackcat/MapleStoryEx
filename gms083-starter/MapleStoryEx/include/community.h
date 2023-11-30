#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define EXPORT __declspec(dllexport)
#define CEXPORT extern "C" __declspec(dllexport)
 