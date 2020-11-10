#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>

#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class Player; }
QT_END_NAMESPACE

class Player : public QWidget
{
        Q_OBJECT

public:
        Player(QWidget *parent = nullptr);
        int playCurrent();
        ~Player();

private slots:
        void on_volumeSlider_sliderMoved(int position);

        void on_mute_stateChanged(int arg1);

        void on_pauseNPlay_released();

        void on_next_released();

        void on_prev_released();

        void updateDuration(long );
        void updatePosition(long );

        void on_musicProcess_sliderMoved(int position);

        void on_musicProcess_sliderPressed();

        void on_musicProcess_sliderReleased();

        void on_playlist_clicked(const QModelIndex &index);

private:
        Ui::Player *ui;
        /* player instance */
        QMediaPlayer *p;
        /* playlist instance */
        QMediaPlaylist *list;
        /* playlist info */
        QFileInfoList playListInfo;

        /* fixed music directory : to be changed in the future */
        const QString musicDirectory = "/home/whoami/workspace/WePinkyPromised/MediaPlayer/Music/";
};
#endif // PLAYER_H
