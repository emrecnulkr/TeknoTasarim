 
 // Emre Can Ülker
 // 04.07.2017
 // Araç Takip Cihazı
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <errno.h>
 #include <wiringPi.h>
 #include <wiringSerial.h>
 #include <unistd.h>
 #include <strrev.c>
 #include <pthread.h>
 #include <signal.h>


FILE *fp;

struct {
char kod[11];
char saat[11];
char enlem[11];
char N_S[11];
char boylam[15];
char E_W[11];
char fix[11];
char uydu[11];
char HDOP[11];
char rakim[11];
char r_birm[11];
char geoid[11];
char g_birm[11];
char bos[11];
char checksum[11];	
float f_enlem;
float f_boylam;
int tr_saat;	
}GGA;

struct {
char kod[11];
char saat[11];
char enlem[11];
char N_S[11];
char boylam[15];
char E_W[11];
char fix[11];
char tarih[11];
char heading[11];
char magnet_var[11];
char magned2[11];
char checksum[11];
char hiz[11];
float f_enlem;
float f_boylam;	
int tr_saat;	
}RMC;

char thread_exit=0;
char Data_In[20] = "20,30,40"; 	// string that have to be parsed
char str_val[10]; 				// pointer to the first character of a token
int saat, enlem, boylam,yukseklik;
int fd; 						// diziden çıkarılan değerler.
char txt[74];					// 74
char dat[100];
int i;
char k=0;
char gga[74];					// 74
char rmc[74];					// 74
int gga_guncelle=0;
//char san;


void exit_event(){   
	
	thread_exit=1;             // thread fonksiyonları durduruluyor
	printf("çıkış yapılıyor");
	sleep(1);                  // 1 saniye bekle. 
	digitalWrite(1, LOW);      //LED söndürülüyor.
	fclose(fp);                // dosya yazma kapatılıyor.
	exit(0);                   // app sonlandırma.
	
	}

void *th ()
{
	int saat,dakika,saniye; 
	int gun,ay,yil;
	
	while(1 ) 
	{
		if (thread_exit)
			{pthread_exit(NULL);} // pthread_exit(NULL); fonksiyonu dışarıdan çalıştırılamadıgı için bu şekilde kullanıldı
		
		sleep(4); // Kayıt süresi 1 saniyede kayıt eder 12 saat yaklaşık 4MB 1 ay 240mb kayıt dosyası boyutu.
		 
		if (GGA.fix[0] == '1' || GGA.fix[0] == '2' )
		{  // gga.fix 1 veya 2 ise gps datası anlamlıdır.
			fp=fopen("gps.txt", "at"); // dosyayı aç 
			
			if(fp==NULL)
				printf("dosya yazma hatası\n");
			
			else
			{
			
			// Hız Parçalanması
			float speed = atof(RMC.hiz);speed = speed * 1.85200;
			
			// Saatin Parçalanması
			int saat_total = atoi(RMC.saat);saniye = saat_total%100;dakika = ((saat_total-saniye)/100)%100;saat=(saat_total-dakika*100-saniye)/10000;
			
			// Tarihin Parçalanması.	  
			int tarih = atoi (RMC.tarih);yil = (tarih%100);ay=((tarih-yil)/100)%100;gun=(tarih-yil-ay*100)/10000;
			
			float mesafe = ((speed*1000)/3600) * saniye;
   
			fprintf(fp,"TARİH: %.2d/%.2d/%.2d SAAT: %.2d:%.2d,%.2d ENLEM: %f BOYLAM: %f RAKIM: %s M HIZ: %2f km/h "
													
			,gun,ay,yil,saat+3,dakika,saniye,GGA.f_enlem,GGA.f_boylam,GGA.rakim,speed); // kayıt değişkenleri
			
			fprintf(fp, "MESAFE: %2f M\n", mesafe);
									
			fclose(fp); // dosyayı kapat.
			}
		}	
	}
	return NULL;	
}

void *led()								// led yakma durumlarına bak
{
	
	while(1)
	{
		if (thread_exit)
			pthread_exit(NULL);			// pthread_exit(NULL); fonksiyonu dışarıdan çalıştırılamadıgı için bu şekilde kullanıldı
		
		if (GGA.fix[0] == '1' || GGA.fix[0] == '2' )
		{	
			digitalWrite(1, HIGH);  	// 1 numaralı pine baglı LED'i açıyoruz /** wiringpi kütüphanesi
			delay(1000);        	 	// 1 saniye (1000 milisaniye) bekliyoruz/** wiringpi kütüphanesi sleep(1) ile aynıdır.
			digitalWrite(1, LOW);   	// 1 numaralı pine baglı LED'i kapatıyoruz/** wiringpi kütüphanesi
			delay(1000);  
		}
	}	
}


void parcala_GGA(){
  int sayac=0; // gps den alınan GGA parametreler vilgülden sonra sırası ile parçalanıyor.
  char temp[11];
  char temp2[11];
  char * pch;
  pch = strtok (gga,",");
  
  
 
  while (pch != NULL)							// Gelen veriler anlamlandırıldı.
  {
  	if(sayac==0) strcpy(GGA.kod,pch);
  	
	else if(sayac==1) strcpy(GGA.saat,pch);
	
	else if(sayac==2)  strcpy(GGA.enlem,pch);
	
    else if(sayac==3) strcpy(GGA.N_S,pch);
	
	else if(sayac==4) strcpy(GGA.boylam,pch);
	
	else if(sayac==5) strcpy(GGA.E_W,pch);
	
	else if(sayac==6)strcpy(GGA.fix,pch);
	
	else if(sayac==7) strcpy(GGA.uydu,pch);
	
	else if(sayac==8) strcpy(GGA.HDOP,pch);
	
	else if(sayac==9) strcpy(GGA.rakim,pch);
	
	else if(sayac==10) strcpy(GGA.r_birm,pch);
	
	else if(sayac==11) strcpy(GGA.geoid,pch);
	
	else if(sayac==12) strcpy(GGA.g_birm,pch);
	
	else if(sayac==13) strcpy(GGA.checksum,pch);
	
    pch = strtok (NULL, ",");
    sayac++;
  }
    
   // enlem hesabı yapılıyor
	memcpy(temp,GGA.enlem,2);strrev(GGA.enlem);memcpy(temp2,GGA.enlem,8);strrev(temp2);
	GGA.f_enlem=atof(temp2)/60 + atoi(temp);strrev(GGA.enlem);strrev(temp2);
   
   //boylam  hesap
	memcpy(temp,GGA.boylam,3);strrev(GGA.boylam);memcpy(temp2,GGA.boylam,8);strrev(temp2);
	GGA.f_boylam=atof(temp2)/60 + atoi(temp);strrev(GGA.boylam);strrev(temp2);
	
	
	//saniye = GGA.saat%100;
	//dakika = ((GGA.saat - saniye)/100)%100;
	//sa = (GGA.saat - (dakika*100) - saniye )/10000;
   
	//printf ("kod		:%s\n" 	, GGA.kod);
	//printf ("saat		:%s\n"	, GGA.saat);
	//printf ("rakım		:%s\n" 	, GGA.rakim);
	//printf ("f_enlem		:%f\n" , GGA.f_enlem);
	//printf ("f_boylam	:%f\n\n", GGA.f_boylam);
  
}
	

void parcala_RMC(){
  int sayac=0; // gps den alınan RMC parametreler vilgülden sonra sırası ile parçalanıyor.
  
  char temp[11];
  char temp2[11];
  char * pch;
  pch = strtok (rmc,",");
  
  while (pch != NULL)							// Gelen veriler anlamlandırıldı.
  {
  	if(sayac==0) strcpy(RMC.kod,pch);
	
	else if(sayac==1) strcpy(RMC.saat,pch);
	
	else if(sayac==2) strcpy(RMC.fix,pch);
	
    else if(sayac==3) strcpy(RMC.enlem,pch);
	
	else if(sayac==4) strcpy(RMC.N_S,pch);
	
	else if(sayac==5) strcpy(RMC.boylam,pch);
	
	else if(sayac==6) strcpy(RMC.E_W,pch);
	
	else if(sayac==7) strcpy(RMC.hiz,pch);
	
	else if(sayac==8) strcpy(RMC.tarih,pch);
	
	else if(sayac==9) strcpy(RMC.checksum,pch);

    pch = strtok (NULL, ",");
    sayac++;
  }
  
   // enlem hesabı yapılıyor
   memcpy(temp,RMC.enlem,2);strrev(RMC.enlem);memcpy(temp2,RMC.enlem,8);strrev(temp2); 
   RMC.f_enlem=atof(temp2)/60 + atoi(temp);strrev(RMC.enlem);strrev(temp2);
   
   //boylam  hesap
   memcpy(temp,RMC.boylam,3);strrev(RMC.boylam);memcpy(temp2,RMC.boylam,8);strrev(temp2);
   RMC.f_boylam=atof(temp2)/60 + atoi(temp);strrev(RMC.boylam);strrev(temp2);
   
   //printf ("kod		:%s\n",RMC.kod);
   //printf ("tarih	:%s\n",RMC.tarih);
   //printf ("fix			:%s\n",RMC.fix);
   //printf ("enlem		:%s\n" ,RMC.enlem);
   //printf ("ns			:%s\n" ,RMC.N_S);
   //printf ("boylam		:%s\n" ,RMC.boylam);
   //printf ("ew			:%s\n" ,RMC.E_W);
   //printf ("speed		:%s\n" ,RMC.speed);
   

   

}
	

void loop()
{
	    
	    while(serialDataAvail(fd)) // uart datası geldiğinde işletilir, uart kesmesi
	    {
			//printf("serialdataavail fd:%d\n",fd);
			sleep(1);
			txt[0]=serialGetchar(fd); // ilk karekter alınıyor. $ ise tüm karekterleri \n ifadesidesine kadar alıyoruz. sonraki karakter döndürülür
		
		
			if (txt[0]=='$')  
			{
				for (i=1;i<100;i++)
				{
					txt[i] = serialGetchar(fd);
					if (txt[i]=='\n') break;						
				}					
			}
	   
			if ( txt[3]=='G' && txt[4]=='G' && txt[5]=='A')
			{	//3.4.5. karaterle GGA ise gga değişkenine kopyalanıyor.																						
																								
				memcpy(gga, txt, strlen(txt)+1);
				parcala_GGA();																															
																																																																								
			}
			
			if ( txt[3]=='R' && txt[4]=='M' && txt[5]=='C')	
			{   //3.4.5. karaterle RMC ise rmc değişkenine kopyalanıyor.
															
				memcpy(rmc, txt, strlen(txt)+1);
				parcala_RMC();														
			}											  
		}
}

	
int  main() 
{	
	wiringPiSetup ();	// Gpio kütüphanesi kuruluyor
	pinMode(1, OUTPUT); // dosya kaydı ledi çıkış olarak ayarlanıyor
	
	fd = serialOpen ("/dev/ttyS0", 9600); // 9600 bund hızında seri iletişim ayarlanıyor.

	signal(SIGINT, exit_event); 					// ctrl+c çıkışı için olay döngüsü ctrl+c basıldıgında exit_event işletilecek program çıkışı bu şekilde olmalıdır.
	pthread_t pth;									// thread fonksitonları oluşturuluyor.	
	pthread_create(&pth,NULL,th,"processing..."); 	// GGA.fix değişkeni 1 veya 2 ise dosya yazmak için sürekli çalışır.
	pthread_create(&pth,NULL,led,"processing..."); 	// dosya yazılıyorsa led flash
 
	printf (" -------Uygulama başlatılıyor----\n") ;
   
	while(1) loop();

	pthread_join(pth, NULL );       
return 0;      	      
}
