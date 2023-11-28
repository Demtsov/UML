#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDial>
#include <QSlider>
#include <QPixmap>
#include <QTime>
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Плейлист")
                                                              << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);


    QSlider* sl_volume= new QSlider;

    sl_volume-> setRange(0,100);

    int DfVolume=0;
    int Dfperemotka=0;


    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(DfVolume);
    m_player->setPosition(Dfperemotka);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    sl_volume->setValue(DfVolume);

connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);
connect(ui->sl_volume,&QSlider::valueChanged,m_player,&QMediaPlayer::setVolume);
connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        m_playlist->setCurrentIndex(index.row());
});
connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
});

connect(m_player, &QMediaPlayer::positionChanged,this,&MainWindow::on_positionChanged);
connect(m_player, &QMediaPlayer::durationChanged,this,&MainWindow::on_durationChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
}
void MainWindow::on_btn_add_clicked(){
     QStringList files = QFileDialog::getOpenFileNames(this,tr("Открыть файлы"),QString(),tr("Audio Files (*.mp3)"));
     foreach (QString filePath, files) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QDir(filePath).dirName()));
            items.append(new QStandardItem(filePath));
            m_playListModel->appendRow(items);
            m_playlist->addMedia(QUrl(filePath));
        }
}




void MainWindow::on_positionChanged(qint64 position)
{ui->h_slider->setValue(position);
ui->time->setText(gett_time(position));
}

void MainWindow::on_durationChanged(qint64 position)
{ ui->h_slider->setMaximum(position);
ui->time->setText(gett_time(position));
}



void MainWindow::on_h_slider_sliderMoved(int position)
{ m_player->setPosition(position);

}

QString MainWindow::gett_time(qint64 n){
    int nHours=(n/(60*60*1000));
    int nMinutes=((n%(60*60*1000))/(60*1000));
    int nSeconds=((n%(60*1000))/1000);

    return QTime(nHours, nMinutes, nSeconds) .toString ("hh:mm:ss");
}

void MainWindow::on_pushButton_clicked()
{   ui->currentTrack->clear();
    m_playlist->clear();
    m_playListModel->clear();
    ui->playlistView->setModel(m_playListModel);
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Плейлист")
                                                              << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::on_sl_volume_sliderMoved(int position){
QString s = QString::number(position)+"%";
    ui->l_volume->setText(s);
}
