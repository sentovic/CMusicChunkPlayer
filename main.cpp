#include <QCoreApplication>
#include <QAudioOutput>
#include <QAudio>
#include <QByteArray>
#include <QEventLoop>
#include <QBuffer>
#include <QFile>

#include <iostream>
#include <unistd.h>
#include <math.h>

using namespace std;

void hello(QAudio::State state) {

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile inputFile;

    if (argc < 2) {
        cout << "Especifica el archivo de musica." << endl;
        return 1;
    }

    cout << " Reproductor de musica por Mateo Olaya Bernal" << endl;
    cout << "  Github: https://github.com/molayab" << endl;
    cout << endl;
    inputFile.setFileName((QString) argv[1]);
    inputFile.open(QIODevice::ReadOnly);

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");

    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    inputFile.seek(44); // skip wav header

    QAudioOutput *audio = new QAudioOutput(format, 0);
    QObject nil;

    // connect(audio, SIGNAL(stateChanged(QAudio::State)), SLOT(stateChanged(QAudio::State)));
    QIODevice * dev = audio->start();
    dev->open(QIODevice::ReadWrite);


    int chunk_size = 1024; // bytes
    int delay = 5; // ms

    while (!inputFile.atEnd()) {
        if (dev->isOpen()) {
            QByteArray data = inputFile.read(chunk_size);
            cout << "READ SEEK: " << inputFile.pos() << "\r";

            dev->write(data);

            usleep(5000);
        }
    }

    cout << endl << "File read!" << endl;

    return a.exec();
}
