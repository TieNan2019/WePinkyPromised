#include "player.h"
#include "ui_player.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QSlider>
#include <QPushButton>
#include <QCheckBox>

#include <QDir>

#include <sstream>
#include <iomanip>



#define __DEBUG__
#ifdef __DEBUG__
#include <QDebug>
#endif




Player::Player(QWidget *parent)
        : QWidget(parent), ui(new Ui::Player)
{
        ui->setupUi(this);

        /* initialize playlist instance */
        list = new QMediaPlaylist;
        QDir root(musicDirectory);
        for (auto s : root.entryList(QDir::Files)) {
                list->addMedia(QUrl::fromLocalFile(musicDirectory + s));

                QListWidgetItem *newItem = new QListWidgetItem;
                newItem->setText(s);
                ui->playlist->addItem(newItem);
        }

        /* initialize player instance */
        p = new QMediaPlayer;
        p->setPlaylist(list);
        p->setVolume(50);

        /* play list info */
        playListInfo = root.entryInfoList(QDir::Files);

        /* process bar */
        connect(p, &QMediaPlayer::positionChanged, this, &Player::updatePosition);
        connect(p, &QMediaPlayer::durationChanged, this, &Player::updateDuration);
}



int Player::playCurrent()
{
        p->play();
        /* hightlight the current song */
        ui->playlist->setCurrentRow(list->currentIndex());

        return 0;
}


Player::~Player()
{
        /* Clean player instance */
        delete p;
        /* Clean list instance */
        delete list;

        delete ui;
}


/* to deal with volum slider status */
void Player::on_volumeSlider_sliderMoved(int vol) {
        #ifdef __DEBUG__
        qDebug() << "Volume changed into " << vol;
        #endif

        p->setVolume(vol);
}


/* deal with the mute buttom event */
void Player::on_mute_stateChanged(int status) {
        #ifdef __DEBUG__
        qDebug() << "status changed into " << status;
        #endif

        p->setMuted(status);
}

/* deal with the event when "next" button was pressed */
void Player::on_next_released() {
        #ifdef __DEBUG__
        qDebug() << "Next song ...";
        #endif

        list->next();

        /* hightlight the current song */
        ui->playlist->setCurrentRow(list->currentIndex());

        if (list->currentIndex() < 0) {
                on_pauseNPlay_released();
                #ifdef __DEBUG__
                qDebug() << "Reach the end ...";
                #endif
        }
}


/* deal with the event when "Prev" button was pressed */
void Player::on_prev_released() {
        #ifdef __DEBUG__
        qDebug() << "Previous song ...";
        #endif

        list->previous();
        /* hightlight the current song */
        ui->playlist->setCurrentRow(list->currentIndex());

        if (list->currentIndex() < 0) {
                on_pauseNPlay_released();
                #ifdef __DEBUG__
                qDebug() << "Reach the start ...";
                #endif
        }
}



/* deal with the event when "pause/play" button was pressed */
void Player::on_pauseNPlay_released()
{
        static bool playStatus = false;

#ifdef __DEBUG__
        if (playStatus)
                qDebug() << "pause ...";
        else
                qDebug() << "play ...";
#endif
        /* hightlight the current song */
        ui->playlist->setCurrentRow(list->currentIndex());

        if (playStatus) {
                p->pause();
                ui->pauseNPlay->setText("Play");
        }
        else {
                p->play();
                ui->pauseNPlay->setText("Pause");
        }

        playStatus = !playStatus;
}



void Player::updatePosition(long position) {
        #ifdef __DEBUG__
        qDebug() << position;
        #endif

        /* update the current process information label */
        int minutes = position / 1000 / 60;
        int seconds = position / 1000 % 60;
        std::ostringstream currMedLen;
        currMedLen << minutes << ":" << std::setw(2)
        << std::setfill('0') << seconds;
        QString currLen(currMedLen.str().c_str());

        ui->currentMediaLength->setText(currLen);

        /* update the position of the bar */
        ui->musicProcess->setValue(position);
}


void Player::updateDuration(long duration) {
        #ifdef __DEBUG__
        qDebug() << duration;
        #endif

        /* update media information from total length label */
        int minutes = duration / 1000 / 60;
        int seconds = duration / 1000 % 60;
        std::ostringstream totalMedLen;
        totalMedLen << minutes << ":" << std::setw(2)
        << std::setfill('0') << seconds;

        QString totalLen(totalMedLen.str().c_str());
        ui->totalMediaLength->setText(totalLen);

        /* update the step length of process bar */
        ui->musicProcess->setRange(0, duration);
}


/* user try to drag the process bar */
void Player::on_musicProcess_sliderMoved(int position)
{
        p->setPosition(position);
}

/* disable the noise when user drag the process bar */
void Player::on_musicProcess_sliderPressed() { p->setMuted(true); }
void Player::on_musicProcess_sliderReleased() { p->setMuted(false); }

/* user clicked the entry in the list */
void Player::on_playlist_clicked(const QModelIndex &index){
        list->setCurrentIndex(index.row());
        p->play();
}
