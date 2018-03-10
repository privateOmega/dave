#include <iostream>
#include <fstream>

#include <portaudiocpp/PortAudioCpp.hxx>
#include "buffer.h"

using namespace std;
using namespace portaudio;

const int BEEP_SECONDS = 1;
const double SAMPLE_RATE = 16000.0;
const int FRAMES_PER_BUFFER = 64;
const int TABLE_SIZE = 200;

int main(int argc, char *argv[])
{
    try
    {
        char chWait;
        int inputDevice = -1;

        Buffer objBuffer((int)(SAMPLE_RATE * 60));
        cout << "Setting up Recorder Interface." << endl;
        AutoSystem autoSys;
        System &sys = System::instance();
        cout << "Using system default input device." << endl;
        inputDevice = sys.defaultInputDevice().index();
        // Device inDevice = Device(sys.defaultInputDevice());
        cout << "Started recording on " << sys.deviceByIndex(inputDevice).name() << endl;
        DirectionSpecificStreamParameters inParamsRecord(sys.deviceByIndex(inputDevice), 1, INT16, false, sys.deviceByIndex(inputDevice).defaultLowInputLatency(), NULL);
        StreamParameters paramsRecord(inParamsRecord, DirectionSpecificStreamParameters::null(), SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff);
        MemFunCallbackStream<Buffer> streamRecord(paramsRecord, objBuffer, &Buffer::RecordCallback);
        cout << "Press enter to STOP recording.";
        streamRecord.start();
        cin.get(chWait);
        streamRecord.stop();
        cout << "Writing audio sample to audio.raw" << endl;
        objBuffer.WriteToFile("audio.raw");
        streamRecord.close();
    }
    catch (...)
    {
        cout << "An unknown exception occured." << endl;
    }
    return 0;
}