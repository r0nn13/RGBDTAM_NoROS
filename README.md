# RGBDTAM (No ROS):

This is a ROS-free version of RGBDTAM - a SLAM system that estimates a dense reconstruction of a scene in real-time and on a CPU using RGB-D cameras. 

Related Publication:
[1] Alejo Concha, Javier Civera. RGBDTAM: A cost-effective and accurate RGBD Tracking and Mapping System. https://arxiv.org/pdf/1703.00754.pdf

# License

RGBDTAM is licensed under the GNU General Public License Version 3 (GPLv3), please see http://www.gnu.org/licenses/gpl.html.

For commercial purposes, please contact the authors.


# Disclaimer

This site and the code provided here are under active development. Even though we try to only release working high quality code, this version might still contain some issues. Please use it with caution.

# Dependencies

PCL library for visualization:

     version >= 1.7.2
     
BOOST library to launch the different threads:
    
     sudo apt-get install libboost-all-dev 
     
CHOLMOD, BLAS, LAPACK and Eigen3 to compile g2o:

     sudo apt-get install libsuitesparse-dev
     sudo apt-get install libblas-dev
     sudo apt-get install liblapack-dev
     sudo apt-get install libeigen3-dev   

Vocabulary used for loop closure and relocalization:
    
We have used the vocabulary created by ORB-SLAM authors. Please, download the vocabulary from this link "https://github.com/raulmur/ORB_SLAM/blob/master/Data/ORBvoc.txt.tar.gz" and place it in "ThirdParty/DBoW2/ORBvoc.txt"

    
# Compilation

1-) Download rgbdtam. Rename the main folder 'rgbdtam-master' and name it 'rgbdtam' instead.


2-) Run the script build_thirdparty.sh to compile the ThirdParty directories (segmentation, DBoW2 and g20).
       
    sh build_thirdparty.sh


3-) Compile rgbdtam
    mkdir build
    cd build  
    cmake ..
    make

There are four parameters that you have to modify (before executing a sequence) in rgbdtam/src/data.yml:

1-) Intrinsic parameters of the camera:

'cameraMatrix'

'distCoeffs'

2-) Camera and depth camera topics

'camera_path'

'depth_camera_path'


# Parameters

There are a few tuneable parameters that you can modify in rgbdtam/src/data.yml:


1-) Number of frames for mapping

num_cameras_mapping_th: [int]. Number of frames that you want to use to estimate the depth maps. Default: 10.

2-) Minimum parallax required for mapping

translational_ratio_th_min: [double]. Minimum parallax to insert a keyframe. Default: 0.01. Typical values [0.03-0.15].

3-) Depth - RGB offset

depth_rgb_offset: [double]. Offset between the timestamps of depth and rgb images. Default: -0.020 (TUM dataset).

4-) Do relocalization

use_relocalization: [bool]. If true, the system will try to detect when it is lost and will try to relocalize.

5-) Minimize geometric error

use_depth_tracking: [bool]. If false, geometric error will not be minimized (only the photometric error will be minimized). It is recommended to minimize also the geometric error unless RGBDTAM does not work in real-time in your computer. Default: True.

6-) Maximum depth to print

depth_range_print: [float]. If higher far away points will also be displayed. Default: 1.7 (meters).

# Contact
For this ROS-free version:
     Ronald Clark -> ron.clark@live.com

For original code, please contact the authors:

     Alejo Concha -> aconchabelenguer@gmail.com

     Javier Civera -> jcivera@unizar.es
