// mainwindow.h

// 防止头文件被重复包含
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 包含必要的头文件
#include <QMainWindow>
#include "board.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QStackedLayout>

// 声明命名空间 Ui
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } // 声明 Ui 命名空间中的 MainWindow 类
QT_END_NAMESPACE

// 声明 MainWindow 类，继承自 QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT // 声明该类是一个 Qt 对象，支持信号和槽机制

public:
    // 构造函数和析构函数
    MainWindow(QWidget *parent = nullptr); // 主窗口的构造函数
    ~MainWindow(); // 主窗口的析构函数

private slots:
    // 槽函数声明
    void on_gameEnded(const QString &winner); // 处理游戏结束信号
    void onStartGameClicked();
    void onVsAIButtonClicked();
    void onVsPlayerButtonClicked();
    void on_regretButton_clicked();
    void on_returnButton_clicked();

private:
    // 私有成员变量
    Ui::MainWindow *ui; // 指向由 Qt 生成的 UI 类的指针
    Board *board; // 指向 Board 类的对象，管理游戏逻辑
     QVBoxLayout *mainLayout;
};

// 结束头文件保护
#endif // MAINWINDOW_H
