#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Crysis / Crysis Warhead Benchmarktool");
    setFixedSize(width(), height());

    connect( ui->launchBenchmark, SIGNAL( clicked() ),
                this, SLOT( startBenchmarkButtonClicked() ) );

    connect( ui->addToQueue, SIGNAL( clicked() ),
             this, SLOT( addToQueueButtonClicked() ) );
    connect( ui->clearSelected, SIGNAL( clicked() ),
             this, SLOT( clearSelectedButtonClicked()));
    connect( ui->clearQueue, SIGNAL( clicked() ),
             this, SLOT( clearAllButtonClicked()));
    connect( ui->toggleStatus, SIGNAL( clicked() ),
             this, SLOT( toggleStatusButtonClicked()));
    connect( ui->toggleStatusAll, SIGNAL( clicked() ),
             this, SLOT( toggleStatusAllButtonClicked()));
    connect( ui->cancelBenchmark, SIGNAL( clicked() ),
             this, SLOT( cancelButtonClicked()));
    connect( ui->browseCrysis, SIGNAL( clicked() ),
             this, SLOT( browseCrysisButtonClicked()));
    connect( ui->browseCrysisWarhead, SIGNAL( clicked() ),
             this, SLOT( browseCrysisWarheadButtonClicked()));

    //Setting Quality Dropdowns
    QStringList sys_spec_values;
    sys_spec_values.append("Low");
    sys_spec_values.append("Medium");
    sys_spec_values.append("High");
    sys_spec_values.append("VeryHigh");

    ui->sys_spec_global->addItems(sys_spec_values);
    ui->sys_spec_global->addItem("Custom");
    ui->sys_spec_GameEffects->addItems(sys_spec_values);
    ui->sys_spec_ObjectDetail->addItems(sys_spec_values);
    ui->sys_spec_Particles->addItems(sys_spec_values);
    ui->sys_spec_Physics->addItems(sys_spec_values);
    ui->sys_spec_PostProcessing->addItems(sys_spec_values);
    ui->sys_spec_Shading->addItems(sys_spec_values);
    ui->sys_spec_Shadows->addItems(sys_spec_values);
    ui->sys_spec_Sound->addItems(sys_spec_values);
    ui->sys_spec_Texture->addItems(sys_spec_values);
    ui->sys_spec_VolumetricEffects->addItems(sys_spec_values);
    ui->sys_spec_Water->addItems(sys_spec_values);

    connect( ui->sys_spec_global, SIGNAL( currentIndexChanged(int) ),
                this, SLOT( sysSpecGlobalCurrentIndexChanged(int) ) );

    connect( ui->sys_spec_GameEffects, SIGNAL( currentIndexChanged(int) ),
                this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_ObjectDetail, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_Particles, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_Physics, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_PostProcessing, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_Shading, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_Shadows, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_Sound, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_Texture, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_VolumetricEffects, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );
    connect( ui->sys_spec_Water, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( sysSpecSubCurrentIndexChanged(int) ) );

    //Setting Antialias
    ui->antialias->addItem("No AA");
    ui->antialias->addItem("2x");
    ui->antialias->addItem("4x");
    ui->antialias->addItem("8x");
    ui->antialias->addItem("8xQ");
    ui->antialias->addItem("16x");
    ui->antialias->addItem("16xQ");

    //DX Level
    ui->dxlevel->addItem("DX 9");
    ui->dxlevel->addItem("DX 10");

    connect( ui->game, SIGNAL( currentIndexChanged(int) ),
             this, SLOT( gameCurrentIndexChanged(int) ) );

    //Game
    ui->game->addItem("Crysis");
    ui->game->addItem("Crysis:Warhead 32bit");
    ui->game->addItem("Crysis:Warhead 64bit");

    //Queue
    QStandardItemModel *model = new QStandardItemModel(0, 4);
    model->setHorizontalHeaderItem(0, new QStandardItem("Settings"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Avg. FPS"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Runtime"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Status"));
    ui->queueView->setModel(model);
    ui->queueView->setColumnWidth(0, 420);

    //Settings
    settings = new QSettings("smurfy", "crysisbenchmark");
    crysisPath = settings->value("crysisPath","").toString();
    crysisWarheadPath = settings->value("crysisWarheadPath","").toString();
    ui->sys_spec_global->setCurrentIndex(settings->value("sys_spec_global",2).toInt());
    changeForced = true;
    ui->sys_spec_GameEffects->setCurrentIndex(settings->value("sys_spec_GameEffects",2).toInt());
    ui->sys_spec_ObjectDetail->setCurrentIndex(settings->value("sys_spec_ObjectDetail",2).toInt());
    ui->sys_spec_Particles->setCurrentIndex(settings->value("sys_spec_Particles",2).toInt());
    ui->sys_spec_Physics->setCurrentIndex(settings->value("sys_spec_Physics",2).toInt());
    ui->sys_spec_PostProcessing->setCurrentIndex(settings->value("sys_spec_PostProcessing",2).toInt());
    ui->sys_spec_Shading->setCurrentIndex(settings->value("sys_spec_Shading",2).toInt());
    ui->sys_spec_Shadows->setCurrentIndex(settings->value("sys_spec_Shadows",2).toInt());
    ui->sys_spec_Sound->setCurrentIndex(settings->value("sys_spec_Sound",2).toInt());
    ui->sys_spec_Texture->setCurrentIndex(settings->value("sys_spec_Texture",2).toInt());
    ui->sys_spec_VolumetricEffects->setCurrentIndex(settings->value("sys_spec_VolumetricEffects",2).toInt());
    ui->sys_spec_Water->setCurrentIndex(settings->value("sys_spec_Water",2).toInt());
    changeForced = false;
    ui->r_width->setText(settings->value("r_width","1920").toString());
    ui->r_height->setText(settings->value("r_height","1200").toString());
    ui->antialias->setCurrentIndex(settings->value("antialias",0).toInt());
    ui->demoloops->setValue(settings->value("demoloops",2).toInt());
    ui->timeofday->setValue(settings->value("timeofday",9).toInt());
    ui->dxlevel->setCurrentIndex(settings->value("dxlevel",1).toInt());
    ui->game->setCurrentIndex(settings->value("game",0).toInt());
    ui->timedemo->setCurrentIndex(settings->value("timedemo",0).toInt());
    ui->vsync->setChecked(settings->value("vsync",false).toBool());
    ui->customcvars->setText(settings->value("customcvars","").toString());
    ui->screenshotEveryX->setChecked(settings->value("screenshotEveryX",false).toBool());
    ui->screenshotOnX->setChecked(settings->value("screenshotOnX",false).toBool());
    ui->screenshotNo->setChecked(settings->value("screenshotNo",true).toBool());
    ui->screenshotFrameX->setValue(settings->value("screenshotFrameX",100).toInt());

    runstatus = QueueRunStatusIdle;
    crysisCheckTimer = new QTimer();
    connect(crysisCheckTimer, SIGNAL(timeout()), this, SLOT(crysisCheckTimerUpdate()));
    crysisCheckTimer->start(1000);

}


MainWindow::~MainWindow()
{
    settings->setValue("crysisPath",crysisPath);
    settings->setValue("crysisWarheadPath",crysisWarheadPath);
    settings->setValue("sys_spec_global",ui->sys_spec_global->currentIndex());
    settings->setValue("sys_spec_GameEffects",ui->sys_spec_GameEffects->currentIndex());
    settings->setValue("sys_spec_ObjectDetail",ui->sys_spec_ObjectDetail->currentIndex());
    settings->setValue("sys_spec_Particles",ui->sys_spec_Particles->currentIndex());
    settings->setValue("sys_spec_Physics",ui->sys_spec_Physics->currentIndex());
    settings->setValue("sys_spec_PostProcessing",ui->sys_spec_PostProcessing->currentIndex());
    settings->setValue("sys_spec_Shading",ui->sys_spec_Shading->currentIndex());
    settings->setValue("sys_spec_Shadows",ui->sys_spec_Shadows->currentIndex());
    settings->setValue("sys_spec_Sound",ui->sys_spec_Sound->currentIndex());
    settings->setValue("sys_spec_Texture",ui->sys_spec_Texture->currentIndex());
    settings->setValue("sys_spec_VolumetricEffects",ui->sys_spec_VolumetricEffects->currentIndex());
    settings->setValue("sys_spec_Water",ui->sys_spec_Water->currentIndex());
    settings->setValue("r_width",ui->r_width->text());
    settings->setValue("r_height",ui->r_height->text());
    settings->setValue("antialias",ui->antialias->currentIndex());
    settings->setValue("demoloops",ui->demoloops->value());
    settings->setValue("timeofday",ui->timeofday->value());
    settings->setValue("dxlevel",ui->dxlevel->currentIndex());
    settings->setValue("game",ui->game->currentIndex());
    settings->setValue("timedemo",ui->timedemo->currentIndex());
    settings->setValue("vsync",ui->vsync->isChecked());
    settings->setValue("customcvars",ui->customcvars->toPlainText());
    settings->setValue("screenshotEveryX",ui->screenshotEveryX->isChecked());
    settings->setValue("screenshotOnX",ui->screenshotOnX->isChecked());
    settings->setValue("screenshotNo",ui->screenshotNo->isChecked());
    settings->setValue("screenshotFrameX",ui->screenshotFrameX->value());

    crysisCheckTimer->stop();
    delete ui;
}

void MainWindow::sysSpecSubCurrentIndexChanged(int index)
{
    if (changeForced == false) {
        ui->sys_spec_global->setCurrentIndex(4);
    }
}

void MainWindow::browseCrysisButtonClicked()
{
    QSettings settings(QSettings::UserScope, "Microsoft", "Windows");
    settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
    QStringList path;
    path.append(settings.value("Personal").toString() + "\\My Games\\Crysis\\ScreenShots");

    QProcess *myProcess = new QProcess();
    myProcess->start("explorer.exe", path);
}

void MainWindow::browseCrysisWarheadButtonClicked()
{
    QSettings settings(QSettings::UserScope, "Microsoft", "Windows");
    settings.beginGroup("CurrentVersion/Explorer/Shell Folders");
    QStringList path;
    path.append(settings.value("Personal").toString() + "\\My Games\\Crysis_WARHEAD\\ScreenShots");

    QProcess *myProcess = new QProcess();
    myProcess->start("explorer.exe", path);
}

void MainWindow::gameCurrentIndexChanged(int index)
{
    ui->timedemo->clear();

    switch (index)
    {
        case 0:
           ui->timedemo->addItem("benchmark_gpu");
           ui->timedemo->addItem("benchmark_cpu 1");
           ui->timedemo->addItem("benchmark_cpu 2");
           ui->timedemo->addItem("crysis_demo1");
           break;
        case 1:
        case 2:
           ui->timedemo->addItem("airfield");
           ui->timedemo->addItem("ambush");
           ui->timedemo->addItem("avalanche");
           ui->timedemo->addItem("cargo");
           ui->timedemo->addItem("frost");
           ui->timedemo->addItem("warhead_demo1");
           ui->timedemo->addItem("warhead_demo2");
           break;
    }
}

void MainWindow::sysSpecGlobalCurrentIndexChanged(int index)
{
    if (index < 4) {
        changeForced = true;
        ui->sys_spec_GameEffects->setCurrentIndex(index);
        ui->sys_spec_ObjectDetail->setCurrentIndex(index);
        ui->sys_spec_Particles->setCurrentIndex(index);
        ui->sys_spec_Physics->setCurrentIndex(index);
        ui->sys_spec_PostProcessing->setCurrentIndex(index);
        ui->sys_spec_Shading->setCurrentIndex(index);
        ui->sys_spec_Shadows->setCurrentIndex(index);
        ui->sys_spec_Sound->setCurrentIndex(index);
        ui->sys_spec_Texture->setCurrentIndex(index);
        ui->sys_spec_VolumetricEffects->setCurrentIndex(index);
        ui->sys_spec_Water->setCurrentIndex(index);
        changeForced = false;
    }
}

void MainWindow::toggleStatusAllButtonClicked()
{
    QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
    for (int i = 0; i < model->rowCount(); i++) {
        QStandardItem *statusItem = model->item(i, 3);
        QueueItem * curQueueItem = getQueueItem(i);
        switch (curQueueItem->status)
        {
            case QueueItemStatusRunning:
            case QueueItemStatusQueued:
                break;
            case QueueItemStatusFinished:
            case QueueItemStatusSkip:
            case QueueItemStatusFailed:
                curQueueItem->status = QueueItemStatusQueued;
                statusItem->setText("Queued");
                break;
        }
    }
}

void MainWindow::cancelButtonClicked()
{
    runstatus = QueueRunStatusCanceld;
}

void MainWindow::clearSelectedButtonClicked()
{
    QModelIndex index = ui->queueView->currentIndex();
    if (index.row() >= 0) {
        QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
        model->removeRow(index.row());
    }
}

void MainWindow::toggleStatusButtonClicked()
{
    QModelIndex index = ui->queueView->currentIndex();
    if (index.row() >= 0) {
        QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
        QStandardItem *statusItem = model->item(index.row(), 3);
        QueueItem * curQueueItem = getQueueItem(index.row());
        switch (curQueueItem->status)
        {
            case QueueItemStatusRunning:
                break;
            case QueueItemStatusQueued:
                curQueueItem->status = QueueItemStatusSkip;
                statusItem->setText("Skip");
                break;
            case QueueItemStatusFinished:
            case QueueItemStatusSkip:
            case QueueItemStatusFailed:
                curQueueItem->status = QueueItemStatusQueued;
                statusItem->setText("Queued");
                break;
        }
    }

    this->repaint();
}

void MainWindow::clearAllButtonClicked()
{
    QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
    model->removeRows(0, model->rowCount());
}

void MainWindow::addToQueueButtonClicked()
{
    QueueItem *newQueueItem = new QueueItem();

    newQueueItem->status = QueueItemStatusQueued;
    newQueueItem->sys_spec_GameEffects = ui->sys_spec_GameEffects->currentIndex();
    newQueueItem->sys_spec_ObjectDetail = ui->sys_spec_ObjectDetail->currentIndex();
    newQueueItem->sys_spec_Particles = ui->sys_spec_Particles->currentIndex();
    newQueueItem->sys_spec_Physics = ui->sys_spec_Physics->currentIndex();
    newQueueItem->sys_spec_PostProcessing = ui->sys_spec_PostProcessing->currentIndex();
    newQueueItem->sys_spec_Shading = ui->sys_spec_Shading->currentIndex();
    newQueueItem->sys_spec_Shadows = ui->sys_spec_Shadows->currentIndex();
    newQueueItem->sys_spec_Sound = ui->sys_spec_Sound->currentIndex();
    newQueueItem->sys_spec_Texture = ui->sys_spec_Texture->currentIndex();
    newQueueItem->sys_spec_VolumetricEffects = ui->sys_spec_VolumetricEffects->currentIndex();
    newQueueItem->sys_spec_Water = ui->sys_spec_Water->currentIndex();
    newQueueItem->customCvars = ui->customcvars->toPlainText();
    newQueueItem->demo_num_runs = ui->demoloops->value();
    newQueueItem->demo_time_of_day = ui->timeofday->value();
    newQueueItem->r_vsync = ui->vsync->isChecked();
    newQueueItem->dxlevel = ui->dxlevel->currentText();
    newQueueItem->r_height = ui->r_height->text();
    newQueueItem->r_width = ui->r_width->text();
    newQueueItem->antialias = ui->antialias->currentIndex();

    newQueueItem->doscreenshots = false;
    if (ui->screenshotEveryX->isChecked())
    {
        newQueueItem->doscreenshots = true;
        newQueueItem->screenshotinterval = -ui->screenshotFrameX->value();
    }
    if (ui->screenshotOnX->isChecked())
    {
        newQueueItem->doscreenshots = true;
        newQueueItem->screenshotinterval = ui->screenshotFrameX->value();
    }

    switch (ui->game->currentIndex())
    {
        case 0:
            newQueueItem->game = BenchmarkGameCrysis;
            break;
        case 1:
            newQueueItem->game = BenchmarkGameCrysisWarhead32;
            break;
        case 2:
            newQueueItem->game = BenchmarkGameCrysisWarhead64;
            break;
    }

    //Timedemo names
    newQueueItem->internallevel = false;
    switch (newQueueItem->game)
    {
        case BenchmarkGameCrysis:
            switch (ui->timedemo->currentIndex())
            {
                case 0:
                    newQueueItem->levelname = "island";
                    newQueueItem->timedemoname = "benchmark_gpu";
                    break;
                case 1:
                    newQueueItem->levelname = "island";
                    newQueueItem->timedemoname = "benchmark_cpu";
                    break;
                case 2:
                    newQueueItem->levelname = "ice";
                    newQueueItem->timedemoname = "benchmark_cpu";
                    break;
                case 3:
                    newQueueItem->levelname = "harbor";
                    newQueueItem->timedemoname = "crysis_demo1";
                    newQueueItem->internallevel = true;
                    break;
            }
            break;
        case BenchmarkGameCrysisWarhead32:
        case BenchmarkGameCrysisWarhead64:
            switch (ui->timedemo->currentIndex())
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    newQueueItem->levelname = ui->timedemo->currentText();
                    newQueueItem->timedemoname = "flythrough";
                    break;
                case 5:
                    newQueueItem->levelname = "airfield";
                    newQueueItem->timedemoname = "warhead_demo1";
                    newQueueItem->internallevel = true;
                    break;
                case 6:
                    newQueueItem->levelname = "ambush";
                    newQueueItem->timedemoname = "warhead_demo2";
                    newQueueItem->internallevel = true;
                    break;
            }
            break;
    }

    QString settingsStr = "";

    switch (newQueueItem->game)
    {
        case BenchmarkGameCrysis:
            settingsStr.append("Crysis - ");
            break;
        case BenchmarkGameCrysisWarhead32:
            settingsStr.append("Warhead 32bit - ");
            break;
        case BenchmarkGameCrysisWarhead64:
            settingsStr.append("Warhead 64bit - ");
            break;
    }

    settingsStr.append(getStrValue(newQueueItem->sys_spec_Texture) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_ObjectDetail) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_Shadows) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_Physics) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_Shading) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_VolumetricEffects) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_GameEffects) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_PostProcessing) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_Particles) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_Water) + ":");
    settingsStr.append(getStrValue(newQueueItem->sys_spec_Sound));

    settingsStr.append(" " + newQueueItem->r_width + "x" + newQueueItem->r_height);
    settingsStr.append(" " + ui->antialias->currentText() );
    settingsStr.append(" " + newQueueItem->dxlevel );

    if (newQueueItem->r_vsync) {
        settingsStr.append(" Vsync");
    }

    settingsStr.append(" (" + newQueueItem->levelname + "/" + newQueueItem->timedemoname + ")");

    if (newQueueItem->demo_num_runs > 1)
    {
        settingsStr.append(" " + QString::number(newQueueItem->demo_num_runs) + "runs " );
    }

    QStandardItem *settingItem = new QStandardItem(settingsStr);
    QVariant data = qVariantFromValue((void *) newQueueItem);
    settingItem->setData(data, QueueItemClassRole);

    QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
    QList<QStandardItem*> *items = new QList<QStandardItem*>;
    items->append(settingItem);
    items->append(new QStandardItem("-"));
    items->append(new QStandardItem("-"));
    items->append(new QStandardItem("Queued"));
    model->appendRow(*items);
}

QString MainWindow::getStrValue(int index)
{
    if (index == 0) {
        return "L";
    }
    if (index == 1) {
        return "M";
    }
    if (index == 2) {
        return "H";
    }
    if (index == 3) {
        return "V";
    }

    return "";
}

QueueItem * MainWindow::getQueueItem(int itemnum)
{
    QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
    QStandardItem *settingItem = model->item(itemnum,0);
    QVariant data = settingItem->data(QueueItemClassRole);
    QueueItem *newQueueItem = (QueueItem *) data.value<void *>();

    return newQueueItem;
}

QueueItem * MainWindow::prepareQueueItem(int itemnum)
{
    QueueItem *newQueueItem = getQueueItem(itemnum);

    switch (newQueueItem->game)
    {
        case BenchmarkGameCrysis:
            newQueueItem->path = crysisPath;
            newQueueItem->bindir = "Bin32";
            newQueueItem->exename = "crysis.exe";
            newQueueItem->bindir = "Bin32";
            break;
        case BenchmarkGameCrysisWarhead32:
            newQueueItem->path = crysisWarheadPath;
            newQueueItem->exename = "crysis.exe";
            newQueueItem->bindir = "Bin32";
            break;
        case BenchmarkGameCrysisWarhead64:
            newQueueItem->path = crysisWarheadPath;
            newQueueItem->exename = "crysis64.exe";
            newQueueItem->bindir = "Bin64";
            break;
    }

    QStringList cfgFile;

    //System specs
    cfgFile.append("sys_spec_VolumetricEffects=" + QString::number(newQueueItem->sys_spec_VolumetricEffects + 1));
    cfgFile.append("sys_spec_Texture=" + QString::number(newQueueItem->sys_spec_Texture + 1));
    cfgFile.append("sys_spec_ObjectDetail=" + QString::number(newQueueItem->sys_spec_ObjectDetail + 1));
    cfgFile.append("sys_spec_Sound=" + QString::number(newQueueItem->sys_spec_Sound + 1));
    cfgFile.append("sys_spec_Shadows=" + QString::number(newQueueItem->sys_spec_Shadows + 1));
    cfgFile.append("sys_spec_Water=" + QString::number(newQueueItem->sys_spec_Water + 1));
    cfgFile.append("sys_spec_Physics=" + QString::number(newQueueItem->sys_spec_Physics + 1));
    cfgFile.append("sys_spec_Particles=" + QString::number(newQueueItem->sys_spec_Particles + 1));
    cfgFile.append("sys_spec_Shading=" + QString::number(newQueueItem->sys_spec_Shading + 1));
    cfgFile.append("sys_spec_PostProcessing=" + QString::number(newQueueItem->sys_spec_PostProcessing + 1));
    cfgFile.append("sys_spec_GameEffects=" + QString::number(newQueueItem->sys_spec_GameEffects + 1));

    //Antialias
    switch (newQueueItem->antialias)
    {
        case 0:
            cfgFile.append("r_FSAA=0");
            cfgFile.append("r_FSAA_samples=0");
            cfgFile.append("r_FSAA_quality=0");
            break;
        case 1:
            cfgFile.append("r_FSAA=1");
            cfgFile.append("r_FSAA_samples=2");
            cfgFile.append("r_FSAA_quality=0");
            break;
        case 2:
            cfgFile.append("r_FSAA=1");
            cfgFile.append("r_FSAA_samples=4");
            cfgFile.append("r_FSAA_quality=0");
            break;
        case 3:
            cfgFile.append("r_FSAA=1");
            cfgFile.append("r_FSAA_samples=4");
            cfgFile.append("r_FSAA_quality=8");
            break;
        case 4:
            cfgFile.append("r_FSAA=1");
            cfgFile.append("r_FSAA_samples=8");
            cfgFile.append("r_FSAA_quality=8");
            break;
        case 5:
            cfgFile.append("r_FSAA=1");
            cfgFile.append("r_FSAA_samples=4");
            cfgFile.append("r_FSAA_quality=16");
            break;
        case 6:
            cfgFile.append("r_FSAA=1");
            cfgFile.append("r_FSAA_samples=8");
            cfgFile.append("r_FSAA_quality=16");
            break;
    }

    //Resolution + Vsync
    cfgFile.append("r_width=" + newQueueItem->r_width);
    cfgFile.append("r_height=" + newQueueItem->r_height);
    cfgFile.append("r_vsync=" + QString::number(newQueueItem->r_vsync));
    cfgFile.append("r_Fullscreen=1");

    //Custom CVars
    cfgFile.append(newQueueItem->customCvars);

    //Add Map
    cfgFile.append("map " + newQueueItem->levelname);

    //Other Settings
    cfgFile.append("g_godMode=1");
    cfgFile.append("i_noweaponlimit 1");
    cfgFile.append("i_unlimitedammo 1");
    cfgFile.append("demo_file=crysis_benchmark");
    cfgFile.append("demo_num_runs=" + QString::number(newQueueItem->demo_num_runs));
    cfgFile.append("demo_quit=1");
    cfgFile.append("hud_startPaused=0");
    cfgFile.append("demo");
    if (newQueueItem->demo_time_of_day > 0)
    {
        cfgFile.append("demo_time_of_day=" + QString::number(newQueueItem->demo_time_of_day));
    }
    cfgFile.append("demo_restart_level=2");
    if (newQueueItem->doscreenshots)
    {
        cfgFile.append("demo_screenshot_frame=" + QString::number(newQueueItem->screenshotinterval));
    }
    cfgFile.append("demo_ai=0");
    cfgFile.append("sys_flash=0");
    cfgFile.append("s_DialogVolume=0");
    cfgFile.append("r_nodrawnear=0");

    //Write Cfg to crysis dir
    QFile file(newQueueItem->path + "\\Game\\Config\\crysis_benchmark.cfg");
    file.open(QIODevice::WriteOnly);
    QTextStream qout(&file);
    qout << cfgFile.join("\r\n");
    file.close();

    //Reset Logfile
    QFile file2(newQueueItem->path + "\\Game\\Levels\\" + newQueueItem->levelname + "\\crysis_benchmark.log");
    file2.open(QIODevice::WriteOnly);
    QTextStream qout2(&file2);
    qout2 << "\r\n";
    file2.close();

    QFile::remove(newQueueItem->path + "\\Game\\Levels\\" + newQueueItem->levelname + "\\crysis_benchmark.tmd");

    //Copy our internal timedemo or default timedemo to leveldir with a static name
    if (newQueueItem->internallevel)
    {
        QString path = QApplication::applicationDirPath();
        QFile::copy(path + "\\" + newQueueItem->timedemoname + ".tmd", newQueueItem->path + "\\Game\\Levels\\" + newQueueItem->levelname + "\\crysis_benchmark.tmd");
    } else {
        QFile::copy(newQueueItem->path + "\\Game\\Levels\\" + newQueueItem->levelname + "\\" + newQueueItem->timedemoname + ".tmd", newQueueItem->path + "\\Game\\Levels\\" + newQueueItem->levelname + "\\crysis_benchmark.tmd");
    }

    return newQueueItem;
}

void MainWindow::parseLogfile(int itemnum)
{
    QueueItem *newQueueItem = getQueueItem(itemnum);

    //Load Logfile
    QFile file(newQueueItem->path + "\\Game\\Levels\\" + newQueueItem->levelname + "\\crysis_benchmark.log");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    QString datastr = data;

    QRegExp regexp = QRegExp("Play Time: (.*s), Average FPS: (.*)\n");
    regexp.setMinimal(true);
    int pos = 0;

    QStringList fpsitems;
    QStringList timeitems;

    while ((pos = regexp.indexIn(datastr, pos)) != -1) {
        fpsitems.append(regexp.cap(2));
        timeitems.append(regexp.cap(1));
        pos += regexp.matchedLength();
    }

    QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
    QStandardItem *fpsItem = model->item(itemnum, 1);
    QStandardItem *timeItem = model->item(itemnum, 2);

    if (fpsitems.count() > 0)
    {
        fpsItem->setText(fpsitems.join(", "));
        timeItem->setText(timeitems.join(", "));
    } else {
        fpsItem->setText("-");
        timeItem->setText("-");
    }
}

void MainWindow::crysisCheckTimerUpdate()
{
    DWORD cid = getCrysisPid();
    QString dots = ".";
    switch (runstatus)
    {
        case QueueRunStatusIdle:
            ui->benchmark->setTitle("Benchmark: Idle");
            ui->cancelBenchmark->setEnabled(false);
            ui->launchBenchmark->setEnabled(true);
            break;
        case QueueRunStatusStarted:
            launchtime++;
            ui->benchmark->setTitle("Benchmark: Launching Crysis" + dots.repeated(launchtime));
            this->repaint();
            if (cid != 0) {
                runstatus = QueueRunStatusRunning;
            } else {
                if (launchtime >= 20) {
                    runstatus = QueueRunStatusItemFailed;
                }
            }
            break;
        case QueueRunStatusRunning:
            ui->benchmark->setTitle("Benchmark: Running...");
            if (cid == 0) {
                cleanCurrentQueueItem();
                runstatus = QueueRunStatusItemFinished;
                startNextQueueItem();
            }
            this->repaint();
            ui->cancelBenchmark->setEnabled(true);
            ui->launchBenchmark->setEnabled(false);
            break;
        case QueueRunStatusItemFinished:
            break;
        case QueueRunStatusItemFailed:
            cleanCurrentQueueItem();
            runstatus = QueueRunStatusItemFinished;
            startNextQueueItem();
            this->repaint();
            ui->cancelBenchmark->setEnabled(true);
            ui->launchBenchmark->setEnabled(false);
            break;
        case QueueRunStatusCanceld:
                ui->benchmark->setTitle("Benchmark: Aborting...");
                if (cid != 0) {
                    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, cid);
                    TerminateProcess(hProcess, 0);
                    CloseHandle( hProcess );
                }
                cleanCurrentQueueItem();
                runstatus = QueueRunStatusIdle;
                this->repaint();
                break;
        case QueueRunStatusFinished:
                ui->benchmark->setTitle("Benchmark: Finished");
                runstatus = QueueRunStatusIdle;
                this->repaint();
                break;
    }
}

void MainWindow::launchCrysis(QString path, QString programm, QStringList extraArguments)
{
    launchtime = 0;
    runstatus = QueueRunStatusStarted;

    QStringList arguments;
    arguments << extraArguments;
    arguments << "-DEVMODE" <<"+exec crysis_benchmark";
    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(path);
    myProcess->start(path + "\\" + programm, arguments);

    myProcess->waitForFinished();
}

bool MainWindow::selectGamePath(BenchmarkGame game)
{
    QString path;
    QString testFile;
    QString gameName;
    switch (game)
    {
        case BenchmarkGameCrysis:
            path = crysisPath;
            testFile = "\\Game\\ZPatch1.pak";
            gameName = "Crysis";
            break;
        case BenchmarkGameCrysisWarhead32:
        case BenchmarkGameCrysisWarhead64:
            path = crysisWarheadPath;
            testFile = "\\Game\\VPatch1.pak";
            gameName = "Crysis Warhead";
            break;
    }

    if (!QFile::exists(path + testFile))
    {
        path = QFileDialog::getExistingDirectory(this,"Please select your " + gameName + " root directory");
        if (!QFile::exists(path + testFile)) {
            QMessageBox msgBox;
            msgBox.setText("Please specify the correct " + gameName + " root directory.");
            msgBox.exec();
            return false;
        }
    }

    switch (game)
    {
        case BenchmarkGameCrysis:
            crysisPath = path;
            break;
        case BenchmarkGameCrysisWarhead32:
        case BenchmarkGameCrysisWarhead64:
            crysisWarheadPath = path;
            break;
    }

    return true;
}

void MainWindow::selectCrysisDirButtonClicked()
{
    selectGamePath(BenchmarkGameCrysis);
}

void MainWindow::selectCrysisWarheadDirButtonClicked()
{
    selectGamePath(BenchmarkGameCrysisWarhead32);
}

void MainWindow::startBenchmarkButtonClicked()
{
    DWORD cpid = getCrysisPid();
    if (cpid > 0) {
        ui->benchmark->setTitle("Benchmark: Aborted!");
        QMessageBox msgBox;
        msgBox.setText("Crysis is already running. Please close it first!");
        msgBox.exec();
        return;
    }

    ui->launchBenchmark->setEnabled(false);
    startNextQueueItem();
}

void MainWindow::cleanCurrentQueueItem()
{
    QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
    for (int i = 0; i < model->rowCount(); i++) {
        QueueItem * newQueueItem = getQueueItem(i);

        if (newQueueItem->status == QueueItemStatusRunning) {
            QStandardItem *statusItem = model->item(i, 3);

            if (runstatus == QueueRunStatusRunning)
            {
                newQueueItem->status = QueueItemStatusFinished;
                statusItem->setText("Finished");
                parseLogfile(i);
            }
            if (runstatus == QueueRunStatusItemFailed || runstatus == QueueRunStatusCanceld)
            {
                newQueueItem->status = QueueItemStatusFailed;
                statusItem->setText("Failed");
            }
            break;
        }
    }
}

void MainWindow::startNextQueueItem()
{
    QStandardItemModel *model = (QStandardItemModel*)ui->queueView->model();
    for (int i = 0; i < model->rowCount(); i++) {
        QueueItem * newQueueItem = prepareQueueItem(i);
        currentGame = newQueueItem->game;

        if (!selectGamePath(currentGame))
        {
            runstatus = QueueRunStatusCanceld;
            return;
        }

        if (newQueueItem->status == QueueItemStatusQueued) {
            QStandardItem *statusItem = model->item(i, 3);
            newQueueItem->status = QueueItemStatusRunning;
            statusItem->setText("Running");
            this->repaint();

            QStringList arguments;
            if (newQueueItem->dxlevel == "DX 9") {
                arguments.append("-DX9");
            } else {
                arguments.append("-DX10");
            }

            launchCrysis(newQueueItem->path + "\\" + newQueueItem->bindir + "\\", newQueueItem->exename, arguments);
            return;
        }
    }

    runstatus = QueueRunStatusFinished;
}

DWORD MainWindow::getCrysisPid()
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 0;
    }

    cProcesses = cbNeeded / sizeof(DWORD);
    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            const HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, aProcesses[i]);

            if (NULL != hProcess) {
                DWORD w_len = 0;
                WCHAR buffer[MAX_PATH];
                w_len = GetModuleFileNameEx(hProcess, 0, buffer, MAX_PATH);

                if (w_len == 0) {
                    w_len = GetProcessImageFileName(hProcess, buffer, MAX_PATH);
                }

                if (w_len > 0) {

                    QFileInfo pathInfo(  QString::fromWCharArray(buffer) );
                    QString teststr = pathInfo.fileName();

                    if (teststr.toLower() == "crysis.exe") {
                       CloseHandle(hProcess);
                       return aProcesses[i];
                    }
                    if (teststr.toLower() == "crysis64.exe") {
                       CloseHandle(hProcess);
                       return aProcesses[i];
                    }
                }
            }

            CloseHandle(hProcess);
        }
    }

    return 0;
}
