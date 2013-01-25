#ifndef __kinect__
#define __kinect__

#include "pcl/range_image/range_image.h"
#include "pcl/io/pcd_io.h"
#include "pcl/visualization/range_image_visualizer.h"
#include "pcl/visualization/pcl_visualizer.h"
#include "pcl/features/range_image_border_extractor.h"
#include "pcl/keypoints/narf_keypoint.h"
#include "pcl/features/narf_descriptor.h"
#include <pcl/console/parse.h>

#include <pcl/registration/icp.h>

#include <boost/thread/thread.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/openni_camera/openni_driver.h>
#include <vector>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <stdio.h>
#include <math.h>
#include <pcl/kdtree/kdtree_flann.h>

#include <cstring>
#include <fstream>

#include <iostream>
#include <utility>
#include <time.h>
#include <vector>

#include <pcl/registration/ia_ransac.h>


#define PI 3.141592

typedef pcl::PointCloud<pcl::PointXYZ>::ConstPtr CloudConstPtr;
typedef pcl::PointXYZ PointType;

using namespace std;

// Struktura przechowujaca indkesy pary deskryptorow
struct ParaDeskryptorow
{
	int indeks1,indeks2;
	double value;
};

// struktura podpinana jako bufor danych z Kinecta
struct StrukturaKinecta
{
    void callback(const CloudConstPtr& cloud)
    {
        pc = cloud; 
	// Streaming zakonczony - wystaw flage 1     
	Streaming=0;
    }
    CloudConstPtr pc;
   
    //zmienna zezwalająca na odczytanie danych z buffora zbierającego dane z Kinect
    bool Streaming;
};

template <typename T> int sgn(T val)
{
    return (val > T(0)) - (val < T(0));
}

class Kinect
{
public:
	// Stream wyjsciowy do zapisu NARF keypoints
	ofstream zapis;

	// Filtr antyNANowy
	bool antyNaN;

	// Filtr VoxelGrid (downsampling)
	bool VoxelGrid;

	// Filtr Antyszumowy 3D
	bool antySzum;
	
	// SetUnseenToMaxRange
	bool SetUnseen;

	// Angular resolution (NARF)
	double ang_res;
	
	// Support size (NARF)
	double support_size;
	
	// RANSAC on/off
	bool RANSAC;
	
	// RANSAC iteration number
	int iteration_number;
	
	// Number of used pairs of NARF descriptors to compute RANSAC model
	int NARF_pair_number;

	// Threshold - when acknowledged as inlier
	double Threshold;

	// Minimal number of matched points in NARF matching
	int NARF_minimal_matched;
	
	// Maksymalna liczba iteracji RANSACa bez poprawy
	int MaxLiczbaIteracjiBezPoprawy;
	
	// Zadany maksymalny error z RANSACA
	double RANSACerror;
	
	// Pkt odniesienia dla RANSACa: 0- chmura NARF 1- cala chmura
	int RANSAC_pkt_odniesienia;
	
	// Ograniczenia na 6 DOF
	double minObrX, maxObrX, minObrY, maxObrY, minObrZ, maxObrZ, minTx, maxTx, minTy, maxTy, minTz, maxTz;
	
	//Bufory
	pcl::PointCloud<pcl::PointXYZ>::Ptr chmura_1;
	pcl::PointCloud<pcl::PointXYZ>::Ptr chmura_2;
	pcl::PointCloud<pcl::Narf36>::Ptr narf_descriptors, narf_descriptors2;
	
	// Czasy
	double StartTime, EndTime;

	// MODE: 0- chmury z kinecta 1- wczytywanie z pliku
	bool MODE;

	// Konstruktor
	Kinect();	

	// Destruktor
	~Kinect();

	// Wczytanie parametrow
	void ReadParameters();

	// Pobierz chmury
	void PrzygotujChmury();

	// ICP
	void ICP();

	// Oblicz katy dla macierzy transformacji
	void Oblicz_Katy(Eigen::Matrix4f &transformation, float *Orient);

	// Pobranie chmury z kinecta
	void PobierzZKinecta();

	// Załadowanie chmur z plikow
	void ReadCloudsFromFile();

	// NARf + ICP
	void NARF_ICP();
	
	// Wylicz NARF;
	void WyliczNARF();
};
#endif
