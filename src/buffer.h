
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <portaudiocpp/PortAudioCpp.hxx>

using namespace std;

typedef vector<short> SHORT_VECTOR;
typedef vector<short>::iterator SHORT_VECTOR_ITER;

class Buffer
{
  public:
    Buffer(int iSizeHint);
    ~Buffer();
    int RecordCallback(const void *paInputBuffer, void *paOutputBuffer, unsigned long iFramesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags);
    void Clear();
    void WriteToFile(const string &filename);

  private:
    SHORT_VECTOR samples;
};

#endif