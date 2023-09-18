#ifndef RADIOLIST_H
#define RADIOLIST_H

#include "jsonlistprocessor.h"
#include "radioaudiomanager.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QStringList>

enum Stations {
    TOP, DISCOVERY, POPULAR, NEW
};

class RadioList : public QObject
{
    Q_OBJECT
public:
    explicit RadioList(QObject *parent = nullptr);
    RadioList(Ui::MainWindow *ui);

    void loadRadioList();
    void loadAllData();
    void setLoadedStationsCount(int num);

    void setTypeMenu();

private slots:
    void onTreeViewItemClicked(const QModelIndex &index);
    void loadMoreStationsIfNeeded();
    void onTableViewDoubleClicked(const QModelIndex &index);
    void onPlayPauseButtonCliced();
    void onNextButtonClicked();
    void onPrevButtonClicked();
    void onStopButtonClicked();
    void onTableViewClicked(const QModelIndex &index);
    void tableViewActivated(const QModelIndex &index);


private:
    int loadedStationsCount     = -1;
    int currentPlaylistIndex    = -1;
    int currentStationIndex     = -1;
    int currentPlayListPlaying  = -1;
    Ui::MainWindow     *ui      = nullptr;
    QStandardItemModel *model   = nullptr;
    QHeaderView        *header  = nullptr;
    QStringList         headers;
    QString             treeItem;
    JsonListProcessor   jsonListProcesor;
    RadioAudioManager   radioManager;
    QString             currentRadioPlayingAddress = "";
    QString item = "";
    int radioIndexNumber = 0;
    int radioEnterIndexNumber = 0;

    const QString STATION   = "Station";
    const QString GENRE     = "Genre";
    const QString COUNTRY   = "Country";
    const QString HOMEPAGE  = "Homepage";
    const QString LIBRARY   = "Library";
    const QString FAVORITE  = "Favorite";

    const QString JSON_ENDPOINT_TOP         = "json/stations/topvote/5";
    const QString JSON_ENDPOINT_DISCOVER    = "json/stations";
    const QString JSON_ENDPOINT_POPULAR     = "json/stations/topclick/5";
    const QString JSON_ENDPOINT_NEW         = "json/stations/lastchange/5";
    const QString JSON_ENDPOINT_EMPTY       = "empty";
    const QString LIBRARY_TREE              = "Library";
    const QString FAVORITE_TREE             = "Favorite";

    QVector<QVector<TableRow>>  allTableRows;
    QVector<QVector<QString>>   allStreamAddresses;

    void playStream(int radioNumber);
    void clearTableViewColor();
    void setIndexColor();
    void sliderMoved(int move);
};

#endif // RADIOLIST_H