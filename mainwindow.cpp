#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) ,
    explorer(this,"Select a Mp3 file","D:\\","*.mp3;*.m4a") , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //modificaciones
    setWindowTitle("MP3 Player");
    int vol_init = 25;
    player.setVolume(vol_init);
    ui->volumen_LCD->display(vol_init);
    player.setNotifyInterval(50);
    connect(&player,SIGNAL(durationChanged(qint64)),ui->duration_slider,SLOT(SetMax(qint64)));
    connect(&player,SIGNAL(positionChanged(qint64)),ui->duration_slider,SLOT(SetPos(qint64)));
    connect(ui->duration_slider,SIGNAL(sliderMoved(int)),this,SLOT(on_set_audio_pos(int)));
    connect(&player,SIGNAL(metaDataChanged()),this,SLOT(on_update_metadata()));
    connect(ui->song_list,SIGNAL(activated(int)),this,SLOT(on_playmusic(int)));
    connect(&player,SIGNAL(durationChanged(qint64)),this,SLOT(new_media));
    connect(&player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(End_curr_media(QMediaPlayer::MediaStatus)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_volumen_dial_valueChanged(int value)
{
    ui->volumen_LCD->display(value);
    player.setVolume(value);
}
void MainWindow::on_file_open_triggered()
{
    qDebug() << "open file process";
    explorer.exec();
    QString title;
    QString filename;
    if(explorer.selectedFiles().length() != 0)
    {
        filename = explorer.selectedFiles()[0];
        qDebug() << explorer.selectedFiles()[0];
        qDebug() << ui->song_list->count();
        if(song_name.length() == 0)
        {
            player.setMedia(QUrl::fromLocalFile(filename));
            song_name.append(filename);
            title = filename.mid( (filename.lastIndexOf('/')+1));
            ui->song_list->addItem(title);
            player.play();
        }
        else{
            song_name.append(filename);
            title = filename.mid( (filename.lastIndexOf('/')+1));
            ui->song_list->addItem(title);
        }
    }
}

void MainWindow::on_file_exit_triggered()
{
    close();
}

void MainWindow::on_actionDelete_Song_triggered()
{
    int cant_items = ui->song_list->count();
    int curr_song  = ui->song_list->currentIndex();
    if(cant_items == 0)
        return;
    if(cant_items == 1){
        ui->song_list->removeItem(curr_song);
        --cant_items;
        song_name.remove(curr_song);
        player.stop();
    }
    if(cant_items > curr_song){
        ui->song_list->removeItem(curr_song);
        --cant_items;
        song_name.remove(curr_song);
        player.setMedia(QUrl::fromLocalFile(song_name[curr_song-1]));
        player.play();
    }

}

void MainWindow::on_actionDelete_All_triggered()
{
    ui->song_list->clear();
    song_name.~List();
    player.stop();
}

void MainWindow::on_play_button_clicked()
{
    qDebug() << "play audio";
    player.play();
}

void MainWindow::on_pause_button_clicked()
{
    qDebug() << "pause";
    player.pause();
}

void MainWindow::on_stop_button_clicked()
{
    qDebug() << "stop";
    player.stop();
}

void MainWindow::on_set_audio_pos(int value)
{
    player.setPosition(value);
}

void MainWindow::on_update_metadata()
{
    QString title  = player.metaData("Tittle").toString();
    QString artist = player.metaData("Author").toString();
    title = title + "-" + artist;
    setWindowTitle(title);
}

void MainWindow::on_playmusic(int song_request)
{
    player.setMedia(QUrl::fromLocalFile(song_name[song_request]));
    player.play();

}

void MainWindow::on_mute_button_stateChanged()
{
    if(ui->mute_button->isChecked() == true)
        player.setMuted(true);
    else
        player.setMuted(false);
}

void MainWindow::End_curr_media(QMediaPlayer::MediaStatus curr_state)
{
    int cant_elements_song = ui->song_list->count();
    int current_song = ui->song_list->currentIndex();
    int randomNum;
    if (curr_state == QMediaPlayer::MediaStatus::EndOfMedia)
    {
        qDebug() << "la cancion termina";
        if(ui->random_button->isChecked() == true)
        {
            randomNum = (rand() % (cant_elements_song + 1));
            qDebug() << "randonnum =" << randomNum;
            if(curr_state == QMediaPlayer::MediaStatus::EndOfMedia)
                player.setMedia(QUrl::fromLocalFile(song_name[randomNum]));
        }
        if(current_song < cant_elements_song){
            qDebug() << "estoy aqui";
            player.setMedia(QUrl::fromLocalFile(song_name[current_song+1]));
            qDebug() << current_song;
            player.play();
        }

    }
}
QString MainWindow::duration2string(qint64 duration)
{
    double min = ((double)duration/1000.0)/60.0;
    //saco los segundos
    double seg = (min - (int)min)*60;
    min = (int)min; // minutos en entero
    QString time;
    time = time.number(min) + ":" + time.number(seg);
    return time;
}
void MainWindow::song_time()
{
    QString duration = duration2string(player.duration());
    QString cur = duration2string(player.position());
    ui->duration_label->setText(cur + '/' + duration);
}
void MainWindow::new_media()
{
    qDebug() << duration2string(player.duration());
}
