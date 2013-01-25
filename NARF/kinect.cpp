#include "kinect.h"

typedef pcl::PointXYZ PointType;

Kinect::Kinect()
{
    this->ReadParameters();

    cout<<"Podaj nazwe pliku do zapisania wynikow"<<endl;
    
    string te;
    cin>>te;
	
 	zapis.open(te.c_str());	
}

Kinect::~Kinect()
{
	zapis.close();
}

void Kinect::ReadParameters()
{
	string linia;
	ifstream o;
	o.open("parameters.cfg");
	while(!o.eof())
	{
		getline(o,linia);
		
		if(linia == "# Filtr antyNANowy")
		{
			o>>linia;
			if(linia == "1") antyNaN = true;
			else 		 antyNaN = false;
		}
		else if(linia == "# Filtr VoxelGrid (downsampling)")
		{
			o>>linia;
			if(linia == "1") VoxelGrid = true;
			else 		 VoxelGrid = false;
		}
		else if(linia == "# Filtr Antyszumowy 3D")
		{
			o>>linia;
			if(linia == "1") antySzum = true;
			else 		 antySzum = false;
		}
		else if(linia == "# SetUnseenToMaxRange (NARF)")
		{
			o>>linia;
			if(linia == "1") SetUnseen = true;
			else 		 SetUnseen = false;
		}
		else if(linia == "# RANSAC - ile iteracji")
		{
			o>>linia;			
			iteration_number = atoi(linia.c_str());
		}
		else if(linia == "# Ile par deskyptorow uzyc do stworzenia modelu")
		{
			o>>linia;			
			NARF_pair_number = atoi(linia.c_str());
		}
		else if(linia == "# RANSAC 1-on, 0-off")
		{
			o>>linia;
			if(linia == "1") RANSAC = true;
			else 		 	 RANSAC = false;
		}
		else if(linia == "# Threshold - kiedy uznany za inliera")
		{
			o>>linia;			
			Threshold = atof(linia.c_str());
		}
		else if(linia == "# Ile procent pokrycia punktow")
		{
			o>>linia;			
			NARF_minimal_matched = atof(linia.c_str());
		}
		else if(linia == "# MODE: 0- chmury z kinecta 1- wczytywanie z pliku")
		{
			o>>linia;
			if(linia == "1") MODE = true;
			else 		 MODE = false;
		}
		else if(linia == "# Rozdzielczosc katowa (NARF)")
		{
			o>>linia;			
			ang_res = atof(linia.c_str());
		}
		else if(linia == "# Support size (NARF)")
		{
			o>>linia;			
			support_size = atof(linia.c_str());
		}
		else if(linia == "# Maksymalna liczba iteracji RANSACa bez poprawy")
		{
			o>>linia;			
			MaxLiczbaIteracjiBezPoprawy = atoi(linia.c_str());
		}
		else if(linia == "# Zadany error do RANSACa")
		{
			o>>linia;			
			RANSACerror = atof(linia.c_str());
		}
		else if(linia == "# Pkt odniesienia dla RANSACa: 0- chmura NARF 1- cala chmura")
		{
			o>>linia;			
			RANSAC_pkt_odniesienia = atoi(linia.c_str());
		}
		else if(linia == "# minObrX")
		{
			o>>linia;			
			minObrX = atof(linia.c_str());
		}
		else if(linia == "# maxObrX")
		{
			o>>linia;			
			maxObrX = atof(linia.c_str());
		}
		else if(linia == "# minObrY")
		{
			o>>linia;			
			minObrY = atof(linia.c_str());
		}
		else if(linia == "# maxObrY")
		{
			o>>linia;			
			maxObrY = atof(linia.c_str());
		}
		else if(linia == "# minObrZ")
		{
			o>>linia;			
			minObrZ = atof(linia.c_str());
		}
		else if(linia == "# maxObrZ")
		{
			o>>linia;			
			maxObrZ = atof(linia.c_str());
		}
		else if(linia == "# minTx")
		{
			o>>linia;			
			minTx = atof(linia.c_str());
		}
		else if(linia == "# maxTx")
		{
			o>>linia;			
			maxTx = atof(linia.c_str());
		}
		else if(linia == "# minTy")
		{
			o>>linia;			
			minTy = atof(linia.c_str());
		}
		else if(linia == "# maxTy")
		{
			o>>linia;			
			maxTy = atof(linia.c_str());
		}
		else if(linia == "# minTz")
		{
			o>>linia;			
			minTz = atof(linia.c_str());
		}
		else if(linia == "# maxTz")
		{
			o>>linia;			
			maxTz = atof(linia.c_str());
		}
	}
	//cout<<"P"<<minObrX<<" "<<maxObrX<<" "<<minObrY<<" "<<maxObrY<<" "<<minObrZ<<" "<<maxObrZ<<" "<<minTx<<" "<<maxTx<<" "<<minTy<<" "<<maxTy<<" "<<minTz<<" "<<maxTz;
	//cout<<antyNaN<<VoxelGrid<<antySzum<<SetUnseen<<" " << iteration_number<< " "<<NARF_pair_number<<" " <<Threshold<<" "<<NARF_minimal_matched<<" "<<MODE<<" "<<ang_res<<endl;
}
void Kinect::PrzygotujChmury()
{
	if(MODE == 0)
	{
		PobierzZKinecta();
	}
	else
	{
		ReadCloudsFromFile();
	}
}

void Kinect::ICP()
{
	  double StartTime = pcl::getTime ();
	  cout<<"ICP start"<<endl;
	  zapis<<"*********************"<<endl;
	  zapis<<"***   ICP START   ***"<<endl;
	  zapis<<"*********************"<<endl;
	  
	  // KinectStream.disconnect();
	  
	  // Obiekt ICP
	  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
	  //icp.setMaxCorrespondenceDistance (15);
	  //icp.setRANSACOutlierRejectionThreshold (5);
	  //icp.setTransformationEpsilon (0);
	  //icp.setMaximumIterations (500);

	  // chmura wejsciowa dla ICP
	  icp.setInputCloud(chmura_1);
		
	  // chmura wejsciowa dla ICP
	  icp.setInputTarget(chmura_2);
	
	  // Z input1 do input2
	  pcl::PointCloud<pcl::PointXYZ> Final;
	  icp.align(Final);

	  cout << "ICP has converged:" << icp.hasConverged() << endl << "Score: "<< icp.getFitnessScore() << endl;
	  zapis<< "ICP has converged:" << icp.hasConverged() << endl<< "Score: "<< icp.getFitnessScore() << endl;
	  
	  double EndTime = pcl::getTime ();
	  cout<<"Czas : "<<EndTime-StartTime<<endl;
	  zapis<<"Czas : "<<EndTime-StartTime<<endl;
	  
	  cout<< "Macierz transformacji" <<endl;
	  zapis << "Macierz transformacji" <<endl;
	  
	  Eigen::Matrix4f transformation;
	  transformation=icp.getFinalTransformation();
	  
	  cout << transformation << endl;
	  zapis<< transformation << endl;
	  
	  
	  float Orient[3];
	  Oblicz_Katy(transformation, Orient);
	  cout<<"Obrót w osi x "<<Orient[0]<<endl;
	  cout<<"Obrót w osi y "<<Orient[1]<<endl;
	  cout<<"Obrót w osi z "<<Orient[2]<<endl;

	  zapis<<"Obrót w osi x "<<Orient[0]<<endl;
	  zapis<<"Obrót w osi y "<<Orient[1]<<endl;
	  zapis<<"Obrót w osi z "<<Orient[2]<<endl;
	  
	 
	 // KinectStream = grabber.registerCallback (boost::function<void(const CloudConstPtr&)>(boost::bind(&StrukturaKinecta::callback,&Kinect_Data, _1)));
}

void Kinect::Oblicz_Katy(Eigen::Matrix4f &transformation, float *Orient)
{
	//obrót wokól osi x
     Orient[0]=(atan2(transformation(2,1),transformation(2,2)))*180/PI;
	//obrót wokół osi y
     Orient[1]=(atan2(-transformation(2,0),sqrt(transformation(2,1))+pow(transformation(2,2),2)))*180/PI;
	//obrót wokół osi z
     Orient[2]=(atan2(transformation(1,0),transformation(0,0)))*180/PI;
}

void Kinect::PobierzZKinecta()
{		
	// tworzymy strukturę dla przechwycenia danych z urządzenia
	StrukturaKinecta Kinect_Data;
	// tworzymy interfejs  który posluży do komunikacji z Kinectem
	pcl::OpenNIGrabber grabber;
	// obiekt do którego podłączamy streaming z kinecta	
	boost::signals2::connection KinectStream;
	
	// Dziwny callback
    KinectStream = grabber.registerCallback (boost::function<void(const CloudConstPtr&)>(boost::bind(&StrukturaKinecta::callback,&Kinect_Data, _1)));
 
    // podpinamy strukturę Kinect_Data jako docelową dla streamingu danych z kinecta
   	Kinect_Data.Streaming=1;///inicjujemy wartość początkową

    // Uruchomienie polaczenia z Kinectem
    grabber.start();
    
    // Niemy getchar :D
	getchar();

	for(int h=0;h<2;h++)
	{
		cout<<"Wciśnij enter, aby zapisać " <<h+1<<" chmurę"<<endl;
		getchar();	  

		while(Kinect_Data.Streaming==1){}
		
		pcl::PointCloud<pcl::PointXYZ>::Ptr buf1 (new pcl::PointCloud<pcl::PointXYZ>);
		pcl::PointCloud<pcl::PointXYZ>::Ptr buf2 (new pcl::PointCloud<pcl::PointXYZ>);

		// Kinect disconnect
		KinectStream.disconnect();
	
	

		// Zapis chmury punktow
		if(h==0)
			pcl::io::savePCDFileASCII ("chmura_z_kinecta_0.pcd",*Kinect_Data.pc);
		else
			pcl::io::savePCDFileASCII ("chmura_z_kinecta_1.pcd",*Kinect_Data.pc);
		printf("Zapisano chmure testowa prosto z kinecta\n");
		 
		
		// Filtry antyNAN
		if(antyNaN == true)
		{
			pcl::PassThrough<pcl::PointXYZ> pass;
			pass.setInputCloud(Kinect_Data.pc);
			pass.filter(*buf1);
		}
		else	*buf1 = *Kinect_Data.pc;

		// Zapis chmury punktow po anty NaN
		//pcl::io::savePCDFileASCII ("chmura_po_antyNaN.pcd",*buf1);
		//printf("Zapisano chmure testowa po anty NaN\n");

		
		// Filtr downsampling
		if(VoxelGrid == true)
		{
			pcl::VoxelGrid<pcl::PointXYZ> filtr_sample;
			filtr_sample.setInputCloud (buf1);
			filtr_sample.setLeafSize (0.01, 0.01, 0.01);
			filtr_sample.filter (*buf2);
		}
		else *buf2 = *buf1;
	
		// Zapis chmury punktow po downsamplingu
		//pcl::io::savePCDFileASCII ("chmura_po_downsampling.pcd",*buf2);
		//printf("Zapisano chmure testowa po downsamplingu\n");


		// Filtr antyszumowy 3D
		if(antySzum == true)
		{
			pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
			sor.setInputCloud (buf2);
			sor.setMeanK (50);
			sor.setStddevMulThresh (1.0);
			sor.filter (*buf1);
		}
		else *buf1 = *buf2;

		// Zapis chmury punktow po antyszumowym 3D
		//pcl::io::savePCDFileASCII ("chmura_po_antyszumowym.pcd",*buf2);
		//printf("Zapisano chmure testowa po antyszumowym\n");

		if(h==0)
		{
			chmura_1 = buf1;
			pcl::io::savePCDFileASCII ("chmura_final_0.pcd",*chmura_1);
		}
		if(h==1)
		{
			chmura_2 = buf1;
			pcl::io::savePCDFileASCII ("chmura_final_1.pcd",*chmura_2);
		}


		KinectStream = grabber.registerCallback (boost::function<void(const CloudConstPtr&)>(boost::bind(&StrukturaKinecta::callback,&Kinect_Data, _1)));
	  }
}

void Kinect::ReadCloudsFromFile()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZ>);

	string naz,naz2;
	cout<<"Podaj nazwe 1 chmury: np. chmura.pcd"<<endl;
	cin>>naz;
	//naz = "chmura_z_kinecta_0.pcd";
	cout<<"Podaj nazwe 2 chmury: np. chmura2.pcd"<<endl;
	cin>>naz2;
	//naz2 = "chmura_z_kinecta_1.pcd";

	pcl::io::loadPCDFile<pcl::PointXYZ> (naz, *cloud);
	pcl::io::loadPCDFile<pcl::PointXYZ> (naz2, *cloud2);

	chmura_1 = cloud;
	chmura_2 = cloud2;
	
	// Filtry, żeby udrzucić złe punkty dla ICP
	for(int h=0;h<2;h++)
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr buf (new pcl::PointCloud<pcl::PointXYZ>);
		
		// Filtry antyNAN
		if(antyNaN == true)
		{
			pcl::PassThrough<pcl::PointXYZ> pass;
			if ( h == 0 )
			{
				pass.setInputCloud(cloud);
			}
			else
			{
				pass.setInputCloud(cloud2);
			}
			pass.filter(*buf);
		}
		else
		{
			if(h==0) *buf = *cloud;
			else *buf = *cloud2;
		}

		// Filtr downsampling

		if(VoxelGrid == true)
		{
			pcl::VoxelGrid<pcl::PointXYZ> filtr_sample;
			filtr_sample.setInputCloud (buf);
			filtr_sample.setLeafSize (0.01, 0.01, 0.01);
			filtr_sample.filter (*cloud);
		}
		else *buf = *cloud;
		
		// Filtr antyszumowy 3D
		if(antySzum == true)
		{
			pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
			sor.setInputCloud (cloud);
			sor.setMeanK (50);
			sor.setStddevMulThresh (1.0);
			sor.filter (*buf);
		}
		else *buf = *cloud;

		if(h==0)
		{
			chmura_1 = buf;
			pcl::io::savePCDFileASCII ("chmura_final_0.pcd",*chmura_1);
		}
		if(h==1)
		{
			chmura_2 = buf;
			pcl::io::savePCDFileASCII ("chmura_final_1.pcd",*chmura_2);
		}
	  }
}


void Kinect::NARF_ICP()
{
	cout<<"NARF_ICP"<<endl;
	zapis<<"NARF_ICP"<<endl;
	
	// Wylicza NARF i zapisuje je w chmurze NARFow
	WyliczNARF();

	float errorek,min;
	vector<ParaDeskryptorow> Pary;
	struct ParaDeskryptorow ParaTym;
	
	// Policzenie roznic narfow
	for(int j=0;j<narf_descriptors->size();j++)
	{	
		min = 99999;
		for(int k=0;k<narf_descriptors2->size();k++)
		{
			errorek = 0;
			for(int i=0;i<36;i++)
			{
				errorek += abs(narf_descriptors->points[j].descriptor[i] - narf_descriptors2->points[k].descriptor[i]);
			}
			if(errorek< min) min = errorek;
		}
		
		// Odrzucanie większych różnic niż 3 minima
		ParaTym.indeks1 = j;
		for(int k=0;k<narf_descriptors2->size();k++)
		{
			ParaTym.indeks2 = k;
			
			errorek = 0;
			for(int i=0;i<36;i++)
			{
				errorek += abs(narf_descriptors->points[j].descriptor[i] - narf_descriptors2->points[k].descriptor[i]);
			}
			if(errorek < 3*min) 
			{
				ParaTym.value = errorek;
				Pary.push_back(ParaTym);
			}
		}
	}
	cout<<"Wszystkich par bylo : "<<narf_descriptors->size()*narf_descriptors2->size()<<endl;
	cout<<"Pary size : "<<Pary.size()<<endl;
	
	
	int ind = -1, par = 0;
	double sigma = 0;
	vector<bool> uzyte;
	for(int i=0;i<Pary.size();i++) uzyte.push_back(false);
	vector<int> indeksss;
	// Petla znajdujaca najlepsze dopasowania tworzące model
	while(par != NARF_pair_number)
	{
		min = 999999;
		for(int i=0;i<Pary.size();i++)
		{
			if(Pary[i].value < min )
			{
				min = Pary[i].value;
				ind = i;
			}
		}
		if(uzyte[Pary[ind].indeks1] == false && uzyte[Pary[ind].indeks2] == false)
		{
			uzyte[Pary[ind].indeks1] = true;
			uzyte[Pary[ind].indeks2] = true;
			indeksss.push_back(ind);
			par++;
			sigma += Pary[ind].value;
		}
		Pary[ind].value = 9999999;
	}
	
	// RANSAC
	int size1 = narf_descriptors->size();
	int size2 = narf_descriptors2->size();
	int size = size1*size2;
	int LiczbaIteracjiBezPoprawy = 0;
	vector <bool> valid_indexes;
	vector <int> model;
	
	// Zapisanie NARFow z 1 i 2 do chmury NARFOW przed iteracją
	pcl::PointCloud<pcl::PointXYZ>::Ptr chmura_NARF1(new pcl::PointCloud<pcl::PointXYZ>),chmura_NARF2(new pcl::PointCloud<pcl::PointXYZ>);
			
	chmura_NARF1->width    = chmura_NARF2->width    	= chmura_1->width;
	chmura_NARF1->height   = chmura_NARF2->height		= chmura_1->height;
	chmura_NARF1->is_dense = chmura_NARF2->is_dense 	= false;
			  
	chmura_NARF1->points.resize (size1);
	chmura_NARF2->points.resize (size2);
	
	// Przepisanie punktów deskryptorów do chmury 2
	for(int j=0;j<chmura_NARF2->points.size();j++)
	{
		chmura_NARF2->points[j].x = narf_descriptors->points[j].x;
		chmura_NARF2->points[j].y = narf_descriptors->points[j].y;
		chmura_NARF2->points[j].z = narf_descriptors->points[j].z;
	}
	
	 pcl::PointCloud<pcl::PointXYZ>::Ptr Chmura1TYM(new pcl::PointCloud<pcl::PointXYZ>);
	// Kopia calej chmury 1, gdy pkt odniesienia jest cala chmura
	if ( RANSAC_pkt_odniesienia == 1)
	{	
		Chmura1TYM->width    = chmura_1->width;
		Chmura1TYM->height	 = chmura_1->height;
		Chmura1TYM->is_dense = false;
				  
		Chmura1TYM->points.resize (chmura_1->points.size());
		
		// Przepisanie punktów deskryptorów do chmury tymczasowej
		for(int j=0;j<chmura_1->points.size();j++)
		{
			Chmura1TYM->points[j].x = chmura_1->points[j].x;
			Chmura1TYM->points[j].y = chmura_1->points[j].y;
			Chmura1TYM->points[j].z = chmura_1->points[j].z;
		}
	}
				
	// Inicjalizacja FLANN dla NARF
	pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
	
	// Liczymy error w stosunku do chmury deskryptorow czy calej chmury
	if ( RANSAC_pkt_odniesienia == 1) kdtree.setInputCloud(chmura_2);
	else 				kdtree.setInputCloud(chmura_NARF2);
	
	// Zmienne do zapisu najlepszych wartości z RANSACa
	Eigen::Matrix3f BestRotation(3,3);
	Eigen::Vector3f BestTranslation(3);
	float BestError = 99999999, BestProcentPunktow;
	float mean[6], BestMean[6];
	Eigen::MatrixXf U;
	
	srand(time(0));
	
	if(RANSAC == false) iteration_number = 1;
	// Glowna petla RANSACa
	for(int i=0;i<iteration_number;i++)
	{
			// Przepisanie punktów deskryptorów do chmury 1
			for(int j=0;j<size1;j++)
			{
				 chmura_NARF1->points[j].x = narf_descriptors->points[j].x;
				 chmura_NARF1->points[j].y = narf_descriptors->points[j].y;
				 chmura_NARF1->points[j].z = narf_descriptors->points[j].z;
			}
			
			// TESTOWO
			if(RANSAC_pkt_odniesienia == 1)
			{
				for(int j=0;j<chmura_1->points.size();j++)
				{
					Chmura1TYM->points[j].x = chmura_1->points[j].x;
					Chmura1TYM->points[j].y = chmura_1->points[j].y;
					Chmura1TYM->points[j].z = chmura_1->points[j].z;
				}
			}
			valid_indexes.clear();
			model.clear();
			
			for(int j=0;j< size ;j++) valid_indexes.push_back(true);
			
			if(RANSAC == 0 || i == 0)
			{
				for(int k=0;k<NARF_pair_number;k++)
				{
					model.push_back(indeksss[k]);
				}
			}
			else
			{
				// Znajdz pary uzyte do stworzenia modelu
				while(model.size() < NARF_pair_number)
				{
					int a = rand() % Pary.size();
					if(valid_indexes[Pary[a].indeks1] == true && valid_indexes[Pary[a].indeks2] == true)
					{
						valid_indexes[Pary[a].indeks1] = false;
						valid_indexes[Pary[a].indeks2] = false;
						model.push_back(a);
					}
				}
			}
				
			// Po wyborze musimy policzyc najlepsza transformacje dla danego modelu
			// Karbsh
			
			// Zapisać punkty wejściowe w wektorze
			Eigen::MatrixXf P(NARF_pair_number,3),Q(NARF_pair_number,3);
			for(int j=0;j<NARF_pair_number;j++)
			{
				int indeks = Pary[model[j]].indeks1;
				P(j, 0) = narf_descriptors->points[indeks].x;
				P(j, 1) = narf_descriptors->points[indeks].y;
				P(j, 2) = narf_descriptors->points[indeks].z;
				
				indeks = Pary[model[j]].indeks2;
				Q(j, 0) = narf_descriptors2->points[indeks].x;
				Q(j, 1) = narf_descriptors2->points[indeks].y;
				Q(j, 2) = narf_descriptors2->points[indeks].z;
				
			}
			//cout<<"P :"<<P<<endl<<"Q : "<<Q<<endl;
			
			// Przesuniecie do srodka
			for(int j=0;j<6;j++) mean[j] = 0.0f;
			
			for(int j=0;j<NARF_pair_number;j++)
			{
				for(int h=0;h<3;h++) mean[h] += P(j,h);
				for(int h=0;h<3;h++) mean[h+3] += Q(j,h);
			}
			for(int j=0;j<6;j++) mean[j] /= NARF_pair_number;
			
			// Po policzeniu arytmetycznej musimy odjac
			for(int j=0;j<NARF_pair_number;j++)
			{
				for(int h=0;h<3;h++) P(j,h) -= mean[h];
				for(int h=0;h<3;h++) Q(j,h) -= mean[h+3];
			} 
			
			// Policzenie transpose P * Q
			Eigen::MatrixXf A = P.transpose() * Q;
			//cout<<"A: "<<A<<endl;
			
			// SVD	
			Eigen::JacobiSVD<Eigen::MatrixXf> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
			Eigen::MatrixXf V = svd.matrixU(), W = svd.matrixV();
			//Eigen::VectorXf S = svd.singularValues();
			
			//cout<<"SVD: " << S<<endl<<endl;
			//cout<<"V: "<<V<<endl<<endl;
			//cout<<"W: "<<W<<endl<<endl;
			//cout<<"det(A) : "<<A.determinant()<<"\tsgn : "<<sgn(A.determinant())<<endl;
			
			// Czy prawoskretny
			Eigen::MatrixXf Temp = Eigen::MatrixXf::Identity(3,3);
			Temp(2,2) = sgn(A.determinant());
			
			// Macierz rotacji to:
			U = W * Temp * V.transpose();
			
			//cout<<"++++"<<endl;
			//cout<<U<<endl;
			//cout<<"++++"<<endl;
			
			// Przesunięcie
			 float T[3] = { mean[3] - mean[0], mean[4] - mean[1], mean[5] - mean[2]}; 
			 
	//		 cout<<"T: " <<T[0]<<"\t"<<T[1]<<"\t"<<T[2]<<endl;
			 
			float ERR  = 0;
			int inliers_number = 0;
			if(RANSAC_pkt_odniesienia == 0 )
			{
				for(int j=0;j<size1;j++)
				{
					// Przepisanie punktu chmury i przesunięcie punktu do miejsca, dla którego liczony był 1 obrót
					Eigen::VectorXf punkt(3);
					punkt[0] = chmura_NARF1->points[j].x - mean[0];
					punkt[1] = chmura_NARF1->points[j].y - mean[1];
					punkt[2] = chmura_NARF1->points[j].z - mean[2];

					// Obrot o macierz R
					punkt = U * punkt;

					
					// Przesunięcie zgodnie z wyznaczoną translacją
					for(int k=0;k<3;k++) punkt[k] = punkt[k] + mean[k+3];
					
					// Przepisanie nowej wartości punktu do chmury
					chmura_NARF1->points[j].x = punkt[0];
					chmura_NARF1->points[j].y = punkt[1];
					chmura_NARF1->points[j].z = punkt[2];
				}
				
				ERR  = 0;
				inliers_number = 0;
				
		
				// Dla wszystkich punktów z przesuniętej chmury1 znajdz najblizszy w chmurze 2
				for(int j=0;j<size1;j++)
				{
					vector<int> a;
					vector<float> odleglosc;
					if ( kdtree.nearestKSearch (chmura_NARF1->points[j], 1, a, odleglosc) > 0 )
					{
						// Sprawdzenie, ile mamy inlinierów
						if(odleglosc[0] < Threshold)
						{
							// Policzenie fitness score dla tego modelu dla inlierów
							ERR += odleglosc[0];
							if(ERR>1000000) cout<<"ZAKRES"<<endl;
							inliers_number++;
						}
						else
						{
							// Kara za outliera
							//ERR += 100;
						}
						
					}
					else 
					{
						// Kara za brak punktu najblizszego
						//ERR+=5000;
						//ERR = BestError + 1;
						//break;
					}
					// Gdy i tak nie bedzie mniejszego erroru
					if(ERR > BestError) break;
					// Gdy i tak nie spelni warunku procentow
					else if( (size1 - j - 1 + inliers_number) *100 < NARF_minimal_matched * size1 ) break;
				}
			}
			else
			{
				// Cala chmura
				for(int j=0;j<Chmura1TYM->points.size();j++)
				{
					// Przepisanie punktu chmury i przesunięcie punktu do miejsca, dla którego liczony był 1 obrót
					Eigen::VectorXf punkt(3);
					punkt[0] = Chmura1TYM->points[j].x - mean[0];
					punkt[1] = Chmura1TYM->points[j].y - mean[1];
					punkt[2] = Chmura1TYM->points[j].z - mean[2];

					// Obrot o macierz R
					punkt = U * punkt;

					
					// Przesunięcie zgodnie z wyznaczoną translacją
					for(int k=0;k<3;k++) punkt[k] = punkt[k] + mean[k+3];
					
					// Przepisanie nowej wartości punktu do chmury
					Chmura1TYM->points[j].x = punkt[0];
					Chmura1TYM->points[j].y = punkt[1];
					Chmura1TYM->points[j].z = punkt[2];
				}
				
				ERR  = 0;
				inliers_number = 0;
				
		
				// Dla wszystkich punktów z przesuniętej chmury1 znajdz najblizszy w chmurze 2
				for(int j=0;j<Chmura1TYM->points.size();j++)
				{
					vector<int> a;
					vector<float> odleglosc;
					if ( kdtree.nearestKSearch (Chmura1TYM->points[j], 1, a, odleglosc) > 0 )
					{
						// Sprawdzenie, ile mamy inlinierów
						if(odleglosc[0] < Threshold)
						{
							// Policzenie fitness score dla tego modelu dla inlierów
							ERR += odleglosc[0];
							if(ERR>1000000) cout<<"ZAKRES"<<endl;
							inliers_number++;
						}
						else
						{
							// Kara za outliera
							//ERR += 100;
						}
						
					}
					else 
					{
						// Kara za brak punktu najblizszego
						//ERR+=5000;
						//ERR = BestError + 1;
						//break;
					}
					// Gdy i tak nie bedzie mniejszego erroru
					if(ERR > BestError) break;
					// Gdy i tak nie spelni warunku procentow
					else if( (Chmura1TYM->points.size() - j - 1 + inliers_number) *100 < NARF_minimal_matched * Chmura1TYM->points.size() ) break;
				}
			}
			
			float ProcentPunktow;
			if (RANSAC_pkt_odniesienia == 1)	ProcentPunktow = float(inliers_number)*100.0/Chmura1TYM->points.size();
			else ProcentPunktow = float(inliers_number)*100.0/size1;
			//	if ( ProcentPunktow > NARF_minimal_matched )cout<<"Odleglosc : "<<ERR<< "\tInliers : "<<inliers_number<<"\t Procent pkt:"<<ProcentPunktow<<endl;
			
			float Obrot[3];
			Eigen::Matrix4f trans(4,4);
			trans.block<3,3>(0,0) = U.block<3,3>(0,0);
			Oblicz_Katy(trans, Obrot);
			
			// Porownanie czy spelnia warunki podane w pliku .cfg i jest lepszym modelem od najlepszego
			if(Obrot[0] <= maxObrX && Obrot[0] >= minObrX && Obrot[1] <= maxObrY && Obrot[1] >= minObrY && Obrot[2] <= maxObrZ && Obrot[2] >= minObrZ &&
				T[0] <= maxTx && T[0] >= minTx && T[1] <= maxTy && T[1] >= minTy && T[2] <= maxTz && T[2] >= minTz && ERR < BestError && ProcentPunktow > NARF_minimal_matched)
			{
				BestError = ERR;
				BestRotation = U;
				BestProcentPunktow = ProcentPunktow;
				
				for(int j=0;j<6;j++) BestMean[j] = mean[j];
				BestTranslation[0] = T[0];
				BestTranslation[1] = T[1];
				BestTranslation[2] = T[2];
				
				LiczbaIteracjiBezPoprawy=0;
			}
			else
			{
				LiczbaIteracjiBezPoprawy++;
			}
			
			// Nie nastapiła poprawa przez N iteracji to break
			if(LiczbaIteracjiBezPoprawy>MaxLiczbaIteracjiBezPoprawy && BestError<RANSACerror) 
			{
				cout<<"Zrobił "<<i<<" iteracji"<<endl;
				break;
			}
	}
	
	
	cout<<endl<<endl<<"-------- Best model --------"<<endl;
	cout<<"-------- ERR : "<<BestError<<endl<<"-------- Rotacja:"<<endl<<BestRotation<<endl<<"-------- Translacja : "<<endl<<BestTranslation<<endl<<"-------- Procent punktow : "<<BestProcentPunktow<<endl<<endl;
	
	zapis<<endl<<endl<<"-------- Best model --------"<<endl;
	zapis<<"-------- ERR : "<<BestError<<endl<<"-------- Rotacja:"<<endl<<BestRotation<<endl<<"-------- Translacja : "<<endl<<BestTranslation<<endl<<"-------- Procent punktow : "<<BestProcentPunktow<<endl<<endl;
	
	// Najlepsza transformacja z RANSACA uzyta do przesuniecia chmury 1
	pcl::PointCloud<pcl::PointXYZ>::Ptr tym(new pcl::PointCloud<pcl::PointXYZ>);
			
	tym->width    = chmura_1->width;
	tym->height   = chmura_1->height;
	tym->is_dense = false;
	tym->points.resize (chmura_1->width * chmura_1->height);
			
	// Przekształcenie chmury 1 przez zadany obrót i translacje
	for(int j=0;j<chmura_1->points.size();j++)
	{
		// Przepisanie punktu chmury i przesunięcie punktu do miejsca, dla którego liczony był 1 obrót
		Eigen::VectorXf punkt(3);
		punkt[0] = chmura_1->points[j].x - BestMean[0];
		punkt[1] = chmura_1->points[j].y - BestMean[1];
		punkt[2] = chmura_1->points[j].z - BestMean[2];
				
		// Obrot o macierz R
		punkt = BestRotation * punkt;
				
		// Przesunięcie zgodnie z wyznaczoną translacją
		for(int k=0;k<3;k++) punkt[k] = punkt[k] + BestMean[3+k];
				
		// Przepisanie nowej wartości punktu do chmury
		tym->points[j].x = punkt[0];
		tym->points[j].y = punkt[1];
		tym->points[j].z = punkt[2];
	}
	
	// Zapisanie tego przeksztalcenia w postaci 4x4 z uwzglednieniem przesuwania do srodka dla Algorytmu Kabscha
	  Eigen::Matrix4f transformation(4,4), Tp(4,4), Tq(4,4),final(4,4);
	  transformation <<  Eigen::MatrixXf::Identity(4,4);
	  Tp <<  Eigen::MatrixXf::Identity(4,4);
	  Tq <<  Eigen::MatrixXf::Identity(4,4);
	  final <<  Eigen::MatrixXf::Identity(4,4);
	  
	  transformation.block<3,3>(0,0) = BestRotation.block<3,3>(0,0);
	  Tp.col(3).head(3) << -BestMean[0], -BestMean[1], -BestMean[2];
	  Tq.col(3).head(3) << BestMean[3], BestMean[4], BestMean[5];
	  
	  
	  // Wypisanie obrotów dla najlepszego modelu
	  float Orient[3];
	  
	  Oblicz_Katy(transformation, Orient);
	  cout<<"Deskryptory NARF sugerują takie obroty w osiach:"<<endl;	
	  cout<<"Obrót w osi x "<<Orient[0]<<endl;
	  cout<<"Obrót w osi y "<<Orient[1]<<endl;
	  cout<<"Obrót w osi z "<<Orient[2]<<endl;
	  
	cout<<endl<<"ICP dla NARF starting pose"<<endl;
			
	// Algorytm IPC
	pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
	
  	icp.setInputCloud(tym);
  	icp.setInputTarget(chmura_2);

	// Stworzenie zmiennej z zapisana chmura wyjsciowa - odpalenie IPC
	pcl::PointCloud<pcl::PointXYZ> Final;
	  icp.align(Final);
	  cout << "has converged:" << icp.hasConverged() << " score: " << icp.getFitnessScore() << endl;
	  zapis << "ICP NARF has converged:" << icp.hasConverged() << " score: " << icp.getFitnessScore() << endl;
	  
	  EndTime = pcl::getTime (); 
	  cout<<"Czas : "<<EndTime-StartTime<<endl;
	  zapis<<"Czas : "<<EndTime-StartTime<<endl;

	  cout<< "Macierz transformacji" <<endl;
	  zapis << "Macierz transformacji" <<endl;
	
	   // Przesuniecie TRicp * Tq * R * Tp 
	  final = icp.getFinalTransformation();
	  final = final * Tq * transformation * Tp;
	  
	  cout << final << endl;
	  zapis<< final << endl;
	 
	 // Zapisanie jakim obrotom to odpowiada
	  Oblicz_Katy(final, Orient);
	  cout<<"Obrót w osi x "<<Orient[0]<<endl;
	  cout<<"Obrót w osi y "<<Orient[1]<<endl;
	  cout<<"Obrót w osi z "<<Orient[2]<<endl;

	  zapis<<"Obrót w osi x "<<Orient[0]<<endl;
	  zapis<<"Obrót w osi y "<<Orient[1]<<endl;
	  zapis<<"Obrót w osi z "<<Orient[2]<<endl;
}	

void Kinect::WyliczNARF()
{	
	// Wartości potrzebne do stworzenia range_image, który jest potrzebny do wyliczenia NARF
	ang_res = pcl::deg2rad (ang_res);
	pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;

	bool rotation_invariant = true;
	float noise_level = 0.0;
	float min_range = 0.0f;
	int border_size = 1;

	StartTime = pcl::getTime ();
	pcl::PointCloud<PointType>& point_cloud = *chmura_1;
	pcl::PointCloud<PointType>& point_cloud2 = *chmura_2;

	// Pozycja sensora w ukladzie wspolrzednych
	Eigen::Affine3f scene_sensor_pose (Eigen::Affine3f::Identity ());
	scene_sensor_pose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);
	 
  	// -----------------------------------------------
	// -----Create RangeImage from the PointCloud-----
	// -----------------------------------------------
	  
	boost::shared_ptr<pcl::RangeImage> range_image_ptr (new pcl::RangeImage);
	boost::shared_ptr<pcl::RangeImage> range_image_ptr2 (new pcl::RangeImage);

	pcl::RangeImage& range_image = *range_image_ptr;   
	pcl::RangeImage& range_image2 = *range_image_ptr2;  
 
	range_image.createFromPointCloud (point_cloud, ang_res, pcl::deg2rad (360.0f), pcl::deg2rad (180.0f),
		                           scene_sensor_pose, coordinate_frame, noise_level, min_range, border_size);
	range_image2.createFromPointCloud (point_cloud2, ang_res, pcl::deg2rad (360.0f), pcl::deg2rad (180.0f),
		                           scene_sensor_pose, coordinate_frame, noise_level, min_range, border_size);

	// true polepsza znajdowanie deskryptorow NARF
	if(SetUnseen == true)
	{
		range_image.setUnseenToMaxRange (); 
	  	range_image2.setUnseenToMaxRange (); 
	}

	// --------------------------------
	// -----Extract NARF keypoints-----
	// --------------------------------
	pcl::RangeImageBorderExtractor range_image_border_extractor;
	pcl::RangeImageBorderExtractor range_image_border_extractor2;
	pcl::NarfKeypoint narf_keypoint_detector;
	pcl::NarfKeypoint narf_keypoint_detector2;

	narf_keypoint_detector.setRangeImageBorderExtractor (&range_image_border_extractor);
	narf_keypoint_detector2.setRangeImageBorderExtractor (&range_image_border_extractor2);

	narf_keypoint_detector.setRangeImage (&range_image);
	narf_keypoint_detector2.setRangeImage (&range_image2);

	narf_keypoint_detector.getParameters ().support_size = support_size;
	narf_keypoint_detector2.getParameters ().support_size = support_size;
	  
	// Wyliczenie NARF keypoints
	pcl::PointCloud<int> keypoint_indices;
 	pcl::PointCloud<int> keypoint_indices2;

	narf_keypoint_detector.compute (keypoint_indices);
	narf_keypoint_detector2.compute (keypoint_indices2);

	cout << "1 chmura : Found "<<keypoint_indices.points.size ()<<" key points.\n";
	cout << "2 chmura : Found "<<keypoint_indices2.points.size ()<<" key points.\n";

	zapis << "1 chmura : Found "<<keypoint_indices.points.size ()<<" key points.\n";
	zapis << "2 chmura : Found "<<keypoint_indices2.points.size ()<<" key points.\n";
	  
	// NARF descriptors
    std::vector<int> keypoint_indices_1,keypoint_indices_2;
	keypoint_indices_1.resize (keypoint_indices.points.size ());
	keypoint_indices_2.resize (keypoint_indices2.points.size ());
	
	for (unsigned int i=0; i<keypoint_indices.size (); ++i) // This step is necessary to get the right vector type
		keypoint_indices_1[i]=keypoint_indices.points[i];
		
	for (unsigned int i=0; i<keypoint_indices2.size (); ++i) // This step is necessary to get the right vector type
		keypoint_indices_2[i]=keypoint_indices2.points[i];
		
	// Wylicz deskryptory dla keypoints	
	pcl::NarfDescriptor narf_descriptor (&range_image, &keypoint_indices_1), narf_descriptor2 (&range_image2, &keypoint_indices_2);
	narf_descriptor.getParameters ().support_size = narf_descriptor2.getParameters ().support_size = support_size;
	narf_descriptor.getParameters ().rotation_invariant = narf_descriptor2.getParameters ().rotation_invariant  = true;
	
	
	pcl::PointCloud<pcl::Narf36>::Ptr a(new pcl::PointCloud<pcl::Narf36>), b(new pcl::PointCloud<pcl::Narf36>);
	narf_descriptors = a;
	narf_descriptors2 = b;
	
	narf_descriptor.compute (*narf_descriptors);
	narf_descriptor2.compute (*narf_descriptors2);
	
	cout << "Cloud 1:\tExtracted "<<narf_descriptors->size ()<<" descriptors for "<<keypoint_indices.points.size ()<< " keypoints.\n";
	cout << "Cloud 2:\tExtracted "<<narf_descriptors2->size ()<<" descriptors for "<<keypoint_indices2.points.size ()<< " keypoints.\n";
	
	zapis << "Cloud 1:\tExtracted "<<narf_descriptors->size ()<<" descriptors for "<<keypoint_indices.points.size ()<< " keypoints.\n";
	zapis << "Cloud 2:\tExtracted "<<narf_descriptors2->size ()<<" descriptors for "<<keypoint_indices2.points.size ()<< " keypoints.\n";
}
