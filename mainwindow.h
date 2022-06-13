#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QtDebug>
#include <QFileDialog>
#include "list.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //mis modificaciones
public:
    List<QString> song_name;
private:
    QMediaPlayer player;
    QFileDialog explorer;
    QString duration2string( qint64 duration);
    QTimer timer;

private slots:

    void on_volumen_dial_valueChanged(int value);

    void on_file_open_triggered();

    void on_file_exit_triggered();

    void on_actionDelete_Song_triggered();

    void on_actionDelete_All_triggered();

    void on_play_button_clicked();

    void on_pause_button_clicked();

    void on_stop_button_clicked();

    void on_set_audio_pos(int value);

    void on_update_metadata();

    void on_playmusic(int song_request);

    void on_mute_button_stateChanged();

    void End_curr_media(QMediaPlayer::MediaStatus curr_state);

    void song_time ();

    void new_media();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
