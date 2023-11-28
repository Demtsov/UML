#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include <QLabel>
#include <QDebug>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_btn_add_clicked();
    void slotSetMediaPosition(int);

    void on_m_psldPosition_sliderMoved(int position);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);

    void on_h_slider_sliderMoved(int position);
    QString gett_time(qint64 n);
    void on_pushButton_clicked();

    void on_sl_volume_sliderMoved(int position);

    void on_sl_volume_windowIconTextChanged(const QString &iconText);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_playListModel;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;


};
#endif // MAINWINDOW_H
