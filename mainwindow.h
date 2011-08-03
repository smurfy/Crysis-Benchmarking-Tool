#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qprocess.h>
#include <windows.h>
#include <psapi.h>
#include "Xsleep.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QRegExp>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

enum BenchmarkGame
{
    BenchmarkGameCrysis = 0,
    BenchmarkGameCrysisWarhead32 = 1,
    BenchmarkGameCrysisWarhead64 = 2
};

enum QueueItemStatus
{
    QueueItemStatusQueued = 1,
    QueueItemStatusRunning = 2,
    QueueItemStatusSkip = 3,
    QueueItemStatusFinished = 4,
    QueueItemStatusFailed = 5
};

enum QueueRunStatus
{
    QueueRunStatusIdle = 0,
    QueueRunStatusStarted = 1,
    QueueRunStatusRunning = 2,
    QueueRunStatusItemFinished = 3,
    QueueRunStatusFinished = 4,
    QueueRunStatusCanceld = 5,
    QueueRunStatusItemFailed = 6
};

struct QueueItem
{
    QueueItemStatus status;
    int sys_spec_VolumetricEffects;
    int sys_spec_Texture;
    int sys_spec_ObjectDetail;
    int sys_spec_Sound;
    int sys_spec_Shadows;
    int sys_spec_Water;
    int sys_spec_Physics;
    int sys_spec_Particles;
    int sys_spec_Shading;
    int sys_spec_PostProcessing;
    int sys_spec_GameEffects;
    int antialias;
    QString r_width;
    QString r_height;
    int r_vsync;
    int demo_num_runs;
    int demo_time_of_day;
    QString customCvars;
    QString dxlevel;
    BenchmarkGame game;
    QString levelname;
    bool internallevel;
    QString timedemoname;
    QString path;
    QString bindir;
    QString exename;
    int screenshotinterval;
    bool doscreenshots;
};

enum QueueItemRoles
{
    QueueItemClassRole = Qt::UserRole + 1
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
        void startBenchmarkButtonClicked();
        void addToQueueButtonClicked();
        void toggleStatusAllButtonClicked();
        void clearSelectedButtonClicked();
        void clearAllButtonClicked();
        void cancelButtonClicked();
        void toggleStatusButtonClicked();
        void sysSpecGlobalCurrentIndexChanged(int index);
        void sysSpecSubCurrentIndexChanged(int index);
        void gameCurrentIndexChanged(int index);
        void crysisCheckTimerUpdate();
        void selectCrysisDirButtonClicked();
        void selectCrysisWarheadDirButtonClicked();
        void browseCrysisButtonClicked();
        void browseCrysisWarheadButtonClicked();
private:
    Ui::MainWindow *ui;
    DWORD getCrysisPid();
    bool changeForced;
    QString getStrValue(int index);
    QueueItem * prepareQueueItem(int itemnum);
    QueueItem * getQueueItem(int itemnum);
    QString crysisPath;
    QString crysisWarheadPath;
    void launchCrysis(QString path, QString programm, QStringList extraArguments);
    QTimer * crysisCheckTimer;
    QueueRunStatus runstatus;
    BenchmarkGame currentGame;
    void startNextQueueItem();
    void cleanCurrentQueueItem();
    void parseLogfile(int itemnum);
    bool selectGamePath(BenchmarkGame game);
    int launchtime;
    QSettings *settings;
};

#endif // MAINWINDOW_H
