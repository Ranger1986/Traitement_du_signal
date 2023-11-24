#include "Wave.hpp"
#include "Wave.cpp"
#include <iostream>
#include <cmath>

void creation_note(double Freq, double fe, int nbechantillons, double *realdata)
{
	for (size_t i = 0; i < nbechantillons; i++)
	{
		realdata[i] = sin(((double)i / fe) * Freq * 2 * M_PI) * 0.5;
	}
}

unsigned char doubleToUnsignedChar(double nombre)
{
	if (nombre > 1)
		return 255;
	if (nombre < -1)
		return 0;
	return floor((nombre + 1) / 2 * 255);
}

double unsignedCharToDouble(unsigned char caractere)
{
	return (double)caractere / 127.5 - 1;
}

int main(int argc, char **argv)
{
	unsigned char *data8;
	int data_nb;
	short mono = 1;

	double laFreq = 440.0;
	double fe = 44100.0;
	int nbechantillons;
	double temps = 6.0;
	double *realdata;

	nbechantillons = (int)floor(temps * fe);
	int m = ceil(log2(nbechantillons));
	//nbechantillons = pow(2, m);

	realdata = (double *)malloc(pow(2, m) * sizeof(double));
	for (size_t i = 0; i < pow(2, m); i++)
	{
		realdata[i] = 0;
	}
	int frequence = 440;
	for (char i = 0; i < 1; i++)
	{
		creation_note(frequence, fe, nbechantillons, realdata);

	}
	data8 = new unsigned char[nbechantillons];

	for (int i = 0; i < nbechantillons; i++)
	{
		data8[i] = doubleToUnsignedChar(realdata[i]);
	}

	Wave la2(data8, nbechantillons, mono, fe);

	// la.modifData8(data8);
	la2.write("test.wav");
	return 0;
}

/*
#include "Wave.cpp"
#include "Wave.hpp"
#include <iostream>
#include <cstdlib>

int CreerNote(double freq_note, double freq_ech, int nb_ech, double *signal){
	double alpha = 2.0 * M_PI*freq_note/freq_ech;
	for (int i = 0; i < nb_ech; i++)
	{
		signal[i] = sin(alpha*(double)i);
	}
	
	return 1;
}
unsigned char dtoc(double nombre)
{
	if (nombre > 1)
		return 255;
	if (nombre < -1)
		return 0;
	return floor((nombre + 1) / 2 * 255);
}

int main(){
	double frequence_note = 440;
	int sampling_freq = 100;
	long int data_nb = 600;
	short channels_nb = 1;

	double signal[data_nb];

	CreerNote(frequence_note,sampling_freq, data_nb, signal);
	//std::cout << signal[400] << std::endl;

	unsigned char data8[data_nb];
	for(int i = 0; i < data_nb; i++){
		data8[i] = dtoc(signal[i]);
	}
	
	// le temps du son = data_nb/sampling_freq
	Wave w(data8, data_nb, channels_nb, sampling_freq);

	w.write("test.wav");

	return 0;
}
/**/