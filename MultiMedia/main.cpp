#include "player.h"
#include <QApplication>

// Qt 音频解码模块
// #include <QtMultimedia/QAudio>
// #include <QtMultimedia/QAudioFormat>
// #include <QtMultimedia/QAudioOutput>
// #include <QMediaPlayer>


int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        Player w;

        // 全屏幕锁定界面
        w.setWindowFlags(Qt::FramelessWindowHint);
        w.showFullScreen();

        /*
        p = new QMediaPlayer;
        // ...
        p->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
        p->setVolume(50);
        p->play();

        delete p;
        */

        w.show();
        return a.exec();
}
