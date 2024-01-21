#include "include/StreamRecorder.h"
#include <QDIr>
#include <QStandardPaths>

// QTC_TEMP
StreamRecorder::StreamRecorder(QObject *parent)
    : QObject(parent)
    , manager(new QNetworkAccessManager(this))
{
    downloadDir = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
}

void StreamRecorder::recordStream(const QByteArray &data)
{
    file.write(data);
}

void StreamRecorder::closeFile()
{
    if (file.isOpen()) {
        file.close();
        qDebug() << "File closed";
    }
}

void StreamRecorder::setFileName(const QString &title, const QString extention)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Konwertuj datę i czas na string w określonym formacie
    QString dateTimeString = currentDateTime.toString("[yyyy-hh-mm]");

    filePath = downloadDir + QDir::separator();
    filePath += dateTimeString + title + "." + extention;
    file.setFileName(filePath);
}

void StreamRecorder::loadCurrentAddress(QString address)
{
    url.setUrl(address);
    if (!file.isOpen()) {
        if (file.open(QIODevice::WriteOnly)) {
            qDebug() << "File opened for writing";
        } else {
            qDebug() << "Error opening file for writing";
            return;
        }
    }
}

void StreamRecorder::clearReply()
{
    if (reply != nullptr)
        reply->deleteLater();
}

void StreamRecorder::startRecording()
{
    // check url!!!
    QNetworkRequest request(url);
    reply = manager->get(request);
    connect(reply, &QNetworkReply::readyRead, this, &StreamRecorder::recordFile);
}

void StreamRecorder::stopRecording()
{
    closeFile();
    clearReply();

    //This is not ... but in some cases help
    if (reply != nullptr) {
        disconnect(reply, &QNetworkReply::readyRead, this, &StreamRecorder::recordFile);
    }
}

bool StreamRecorder::getIsRecording() const
{
    return isRecording;
}

void StreamRecorder::setIsRecording(bool newIsRecording)
{
    isRecording = newIsRecording;
}

void StreamRecorder::recordFile()
{
    while (reply->bytesAvailable()) {
        QByteArray data = reply->readAll();
        file.write(data);
    }
}