/**
* This file is part of rgbdtam.
*
* Copyright (C) 2015 Alejo Concha Belenguer <alejocb at unizar dot es> (University of Zaragoza)
* and Javier Civera Sancho   <jcivera at unizar dot es> (University of Zaragoza)
*
* rgbdtam is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* rgbdtam is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rgbdtam. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __SUPERPIXEL_H
#define __SUPERPIXEL_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <cstdio>

using namespace std;


#include <boost/thread/thread.hpp>
#include <iostream>
#include <stdio.h>
#include <boost/filesystem.hpp>



///////////////////////////


#define SPX_IS_LARGE 1000

class superpixel {
public:
    superpixel(){informative = 0;size = 0; bGoodSp=false; bLargeEnough=false; bMatched = false;}

    int informative;

    //int area () {return (x[1]*x[2]);}
    void set_matchings (int,int,int,int);
    void set_color (int a, int b, int c)
    {     color[0] = a;
          color[1] = b;
            color[2] = c;
    };
    void set_contour (float,float,float);
    void set_contourR (cv::Mat contourR1) { contourR=contourR1.clone();}
    void set_contour3D (cv::Mat contour3D1) { contour3D=contour3D1.clone();}
    void set_pixels3D (cv::Mat pixels3D1) { pixels3D=pixels3D1.clone();}
    void set_plane (float,float,float);

    void set_matrix (cv::Mat m1) {m=m1.clone();}

    void set_pixels (float,float,float);

    void setGood(bool good){bGoodSp = good;}// sup[i]->setGood(true)
    bool isGood(){return bGoodSp;}

    void SetbAlreadyMatched(bool good){bMatched = good;} // sup[i]->SetbAlreadyMatched(true)
    bool bAlreadyMatched(){return bMatched;}

    bool isLarge(){return size > SPX_IS_LARGE;}
    void incSize(){size ++;}
    int getSize(){return size;}
    cv::Mat getContour(){return contour;}
    cv::Mat getContourR(){return contourR;}
    cv::Mat getContour3D(){return contour3D;}

    cv::Mat getMatchings(){return matchings;}
    cv::Mat getPixels3D(){return pixels3D;}

    cv::Mat getPlane(){return plane;}

    cv::Mat getMatrix(){return m;}

    cv::Mat getPixels(){return pixels;}

    cv::Mat matchings,plane;

private:

    bool bGoodSp, bLargeEnough, bMatched;
    cv::Mat contour,contourR,pixels,contour3D,pixels3D;
    int size;
    int color[3];
    cv::Mat m;
};

class SuperpixelsImage {
public:
    struct Data
    {           cv::Mat R1;
                cv::Mat t1;
                        float f1;
                                int reduction;
    }Data1;

    SuperpixelsImage(){}
    cv::Mat image;
    char *image_name;
    char *sup_name;


    void set_data (cv::Mat R1,cv::Mat t1,float f1)
    {Data1.R1 = R1; Data1.t1 = t1; Data1.f1 = f1;}
    Data GetData(){return Data1;}

    void cargarImage_class();

    /// this function compute superpixels and calculate the contours, used for 3D superpixel matching
    int computeSuperpixels();
    /// this function compute superpixels and calculate the contours, used for 3D superpixel matching


    vector<superpixel*> getSuperpixeles(){return sup;}
    int getNumberOfSuperpixels(){return sup.size();}

    vector<superpixel*> sup;

private:

};

class Image_class {
public:

    Image_class():is_used_for_mapping(0){}

    int num_keyframes;

    cv::Mat accurate_sd_map;

    double stamps;

    int image_number;

    int is_used_for_mapping;
    cv::Mat image, image_gray;
    cv::Mat R,t,t_r;
    float fx,fy,cx,cy;
    int reduction;
    float error;

private:

};


class Images_class {
public:
    Images_class(){}
    void computeImage();

    void computeImageSup();
    int getNumberOfImages(){return Im.size();}
    int getNumberOfImageSuperpixels(){return supIm.size();}

    vector<SuperpixelsImage*> getSuperpixelsImage(){return supIm;}
    vector<Image_class*> Im;
    vector<SuperpixelsImage*> supIm;

private:


};


class photometric_term {
public:

    photometric_term(){}
    void computeError();
    vector<cv::Mat> ph_error;
private:
};



class MapShared  :public Images_class {
public:
    MapShared(){}

    void set_R(cv::Mat R_aux) { R = R_aux.clone();}
    cv::Mat get_R(){return R;}

    void set_t(cv::Mat t_aux) { t = t_aux.clone();}
    cv::Mat get_t(){return t;}

private:
    cv::Mat R,t;
    cv::Mat superpixels3D;

};
#endif
