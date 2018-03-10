#include "buffer.h"

using namespace std;

Buffer::Buffer(int iSizeHint)
{
    if (iSizeHint > 0)
    {
        samples.reserve(iSizeHint);
    }
}

Buffer::~Buffer()
{
}

int Buffer::RecordCallback(const void *paInputBuffer, void *paOutputBuffer, unsigned long iFramesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags)
{
    short **paData = (short **)paInputBuffer;
    if (paInputBuffer == NULL)
    {
        cout << "Input buffer was NULL!" << endl;
        return paContinue;
    }
    // Copy all the frames over to our internal vector of samples
    for (unsigned long i = 0; i < iFramesPerBuffer; i++)
        samples.push_back(paData[0][i]);
    return paContinue;
}

void Buffer::Clear()
{
    samples.clear();
}

void Buffer::WriteToFile(const string &filename)
{
    fstream outputFile(filename.c_str(), ios::out | ios::binary);
    short iSample;
    for (SHORT_VECTOR_ITER iter = samples.begin(); iter != samples.end(); iter++)
    {
        iSample = (short)*iter;
        outputFile.write((char *)&iSample, sizeof(short));
    }
    outputFile.close();
}