#ifndef MODELER_H
#define MODELER_H

//
//  processor.hpp
//  Map Processor
//
//  Created by Tasman Thenell on 8/17/16.
//  Copyright © 2016 Tasman Thenell. All rights reserved.
//

#include <QObject>
#include <QFile>
#include "qdebug.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include "heatmap.h"
#include "lodepng.h"
#include "CImg.h"
//#include "colorschemes/RdYlGn.h"

using namespace std;

/*
static const unsigned char discrete_data[] = {
    0, 0, 0, 0, 0, 104, 55, 255, 26, 152, 80, 255, 102, 189, 99, 255, 166, 217, 106, 255, 217, 239, 139, 255, 254, 224, 139, 255, 253, 174, 97, 255, 244, 109, 67, 255, 215, 48, 39, 255, 165, 0, 38, 255
};
static const heatmap_colorscheme_t discrete = { discrete_data, sizeof(discrete_data)/sizeof(discrete_data[0]/4) };
const heatmap_colorscheme_t* heatmap_cs_RdYlGn_discrete = &discrete;
*/

struct parameters{
    string workingPath;
    string name;
    int x;
    int y;
    int years;
    int startYear;
    int huntsPerYear;
    int carryCapacity;
    int huntRange;
    int diffusionSamples;
    double killProb;
    double geoX;
    double geoY;
    bool geolocation;
    bool setupComplete;
    double animalGrowthRate;
    double theta;
    double encounterRate;
    double animalDiffRate;
    int *output;

    parameters(){
        startYear = 0;
        animalDiffRate = .02;
        //animalGrowthRate = .07;
        encounterRate = .02043;
        theta = 1;
        diffusionSamples = 1;
        output = new int[5]; //create heatmap(s), csv(s), config, population file, heatmap scale
        for(int i = 0; i < 4; i++){
            output[i] = 0;
        }

        output[4] = 1; //heatmap scale initially 1x
    };

    ~parameters(){
        delete []output;
    };
};

struct village{
    string name;
    int population;
    vector<int> vectorPop;
    int x;
    int y;
    double killRate;
    village(int, int, vector<int>, double, string, int);
    void printvillage(){std::cout << "name: " << name << " pop: " << population << " x: " << x << " y: " << y << std::endl;};
    int getPop(int);
};

class processor : public QObject{
    Q_OBJECT
private:
    double geoX;
    double geoY;
    bool geolocation;

    int xSize;
    int ySize;
    int years;
    int startYear;
    double encounterRate;
    int HpHy;
    double carryCapacity;
    double animalGrowthRate;

    //other junk
    double theta;
    double animalDiffRate;
    int huntRange;
    double killProb;
    int diffusionSamples;
    //double lambdas;

    string directory;
    string name;
    int *output;
    double ***grid;
    vector<struct village*> towns;

public:
    explicit processor(parameters* = 0);
    void addVillage(village*);
    void runSimulation();
    void printResults();
    void dumpForHeatmap();
    void generateHeatmap(int);
    void generateOverlay(int);
    void generateOutput();
    void generateCSV(int);
    void dumpConfig(bool);
    void savePopulations();

    //helper functions
    double getNeighborTotals(int year, int x, int y);

    ~processor();

signals:
    void progressUpdate(int i);
    void progressImages(int i);
};

#endif // MODELER_H
