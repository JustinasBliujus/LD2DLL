#pragma once
#ifndef _DLL_H_
#define _DLL_H_

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#ifdef DLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif
using namespace std;

extern "C" {
    enum TimerAction {
        TIMER_START,
        TIMER_END
    };
    DLL_API void ManageTimer(TimerAction action);
    DLL_API double GetElapsedTime();
    DLL_API void modifyUserTime(const std::string& username, const std::string& day, const std::string& timeInterval);
    DLL_API void createDirectoriesAndFiles(const std::string& name, const std::string& surname);
    DLL_API void calculateAndWriteData(double F, double x0, double xn, double dx);
    DLL_API void mergeAndSortFiles(const std::string& rootDir, const std::string& outputFilePrefix);
    DLL_API void deleteDirectories(const std::string& name, const std::string& surname);
    string name = "Justinas";
    string surname = "Bliujus";
    struct Point {
        double x;
        double y;
    };
    static unsigned long start_time = 0;
    static unsigned long end_time = 0;
    static bool timer_running = false;
    DLL_API Point* readPointsFromFile(const string& filename, int& numPoints);
    DLL_API void writePointsToFile(const string& filename, const Point* points, int numPoints);
}
#endif