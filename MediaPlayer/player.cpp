#include "player.h"
#include "ui_player.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QSlider>
#include <QPushButton>
#include <QCheckBox>

#include <QDir>




#define __DEBUG__
#ifdef __DEBUG__
#include <QDebug>
#endif




Player::Player(QWidget *parent)
        : QWidget(parent), ui(new Ui::Player)
{
        /* initialize playlist instance */
        list = new QMediaPlaylist;

        QDir root(musicDirectory);

        for (auto s : root.entryList(QDir::Files))
                list->addMedia(QUrl::fromLocalFile(musicDirectory + s));


        /* initialize player instance */
        p = new QMediaPlayer;

        p->setPlaylist(list);
        p->setVolume(50);

        /* play list info */
        playListInfo = root.entryInfoList(QDir::Files);

        ui->setupUi(this);
}




int Player::playCurrent()
{
        p->play();

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
        static bool playStatus = true;
#ifdef __DEBUG__
        if (playStatus)
                qDebug() << "pause ...";
        else
                qDebug() << "play ...";
#endif

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
