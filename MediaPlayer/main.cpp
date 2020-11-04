#include "player.h"

#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        Player w;
        // 全屏幕锁定界面
         w.setWindowFlags(Qt::FramelessWindowHint);
         w.showFullScreen();

        w.show();
        w.playCurrent();

        return a.exec();
}
