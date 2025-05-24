#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QTimer>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QStackedLayout>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("世界上最好玩的五子棋");
    setWindowIcon(QIcon(":/res/favicon.ico"));
    // 设置窗口背景颜色
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(240, 240, 240));
    this->setPalette(palette);

    // 设置字体
    QFont font;
    font.setFamily("华文楷体");
    font.setPointSize(20);
    this->setFont(font);
/*
    // 创建开始游戏和退出游戏按钮
    QPushButton* startButton = new QPushButton("开始游戏", this);
    QPushButton* exitButton = new QPushButton("退出游戏", this);

    // 设置按钮样式
    startButton->setStyleSheet("QPushButton {"
                               "background-color: rgba(255,255,255,150);"
                               "min-width: 200px;"
                               "padding: 15px;"
                               "border-radius: 8px;"
                               "font: bold 18px;"
                               "}"
                               "QPushButton:hover { background-color: rgba(255,255,255,200); }");
    exitButton->setStyleSheet("QPushButton {"
                              "background-color: rgba(255,255,255,150);"
                              "min-width: 200px;"
                              "padding: 15px;"
                              "border-radius: 8px;"
                              "font: bold 18px;"
                              "}"
                              "QPushButton:hover { background-color: rgba(255,255,255,200); }");
// 创建一个垂直布局来放置按钮
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(exitButton);
    // 创建一个垂直布局来放置按钮
    //QVBoxLayout* mainLayout = new QVBoxLayout;
   // mainLayout->addStretch(1); // 添加一个伸展项，使按钮往下移动
    //mainLayout->addWidget(startButton, 0, Qt::AlignCenter); // 居中对齐
    //mainLayout->addWidget(exitButton, 0, Qt::AlignCenter); // 居中对齐
    //mainLayout->addStretch(1); // 添加另一个伸展项，使按钮往下移动

    // 创建一个中心窗口部件并设置布局
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
*/

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignBottom);
    //主页插入图片
    setStyleSheet("QWidget#MainWindow { border-image: url(:/res/Background.jpg); }");

    // 创建标题标签
    QLabel* titleLabel = new QLabel("五子棋", this);

    // 设置字体属性
    QFont titleFont("华文楷体", 48, QFont::Bold);  // 推荐使用中文系统字体
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, 2);  // 字间距2px
    titleLabel->setFont(titleFont);

    // 设置对齐方式和布局参数
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);  // 水平居中+顶部对齐

    // 设置样式表（带文字阴影效果）
    titleLabel->setStyleSheet(
        "QLabel {"
        "   color: #000000;"  // 白色文字
        "   text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.8);"  // 黑色阴影增强对比度
        "   background: transparent;"  // 完全透明背景
        "   padding: 10px 0;"  // 上下内边距
        "}"
        );
    mainLayout->addWidget(titleLabel, 0, Qt::AlignTop);  // 固定在顶部
    // 创建按钮容器
    QWidget *buttonContainer = new QWidget(centralWidget);
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonContainer);

    // 设置容器尺寸策略
    buttonContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 添加按钮
    QPushButton *startBtn = new QPushButton("开始游戏", buttonContainer);
    QPushButton *exitBtn = new QPushButton("退出游戏", buttonContainer);

    // 设置按钮固定高度
    startBtn->setFixedHeight(40);
    exitBtn->setFixedHeight(40);

    // 添加按钮间距
    buttonLayout->setSpacing(30);
    buttonLayout->addWidget(startBtn);
    buttonLayout->addWidget(exitBtn);

    // 主布局设置
    mainLayout->addWidget(buttonContainer); // 添加按钮容器

    // 设置边距保证按钮可见
    mainLayout->setContentsMargins(50, 20, 50, 50); // 左，上，右，下

    setCentralWidget(centralWidget);
    // 连接开始游戏按钮的点击信号到槽函数
    connect(startBtn, &QPushButton::clicked, this, &MainWindow::onStartGameClicked);

    // 连接退出游戏按钮的点击信号到槽函数
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::close);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 开始游戏按钮点击事件的槽函数
void MainWindow::onStartGameClicked()
{
    QWidget* newPageWidget = new QWidget(this);

    // 设置新页面的背景图片
    newPageWidget->setStyleSheet("QWidget { border-image: url(:/res/NewBackground.jpg); }");
    setStyleSheet("QMainWindow#MainWindow { border-image: url(:/res/NewBackground.jpg); }");
    newPageWidget->setObjectName("NewPageWidget");
    // 创建人机对战和真人对战按钮
    QPushButton* vsAIButton = new QPushButton("真人对战", this);
    QPushButton* vsPlayerButton = new QPushButton("人机对战", this);
    vsAIButton->setStyleSheet("QPushButton {"
                               "background-color: rgba(255,255,255,0.8) !important;"
                              " border: 10px solid rgba(255,255,255,0.5) !important;"
                               "min-width: 200px;"
                               "padding: 15px;"
                               "border-radius: 8px;"
                               "font: bold 18px;"
                               "color: #FFFFFF;"
                               "}"
                              "QPushButton:hover {"
                              "   background-color: rgba(255,255,255,1) !important;"
                              "   border-color: rgba(76,175,80,0.8) !important;"
                              "}");
    vsPlayerButton->setStyleSheet("QPushButton {"
                                  "background-color: rgba(255,255,255,0.8) !important;"
                                  " border: 10px solid rgba(255,255,255,0.5) !important;"
                              "min-width: 200px;"
                              "padding: 15px;"
                              "border-radius: 8px;"
                              "font: bold 18px;"
                              "color: #FFFFFF;"
                              "}"
                                  "QPushButton:hover {"
                                  "   background-color: rgba(255,255,255,1) !important;"
                                  "   border-color: rgba(76,175,80,0.8) !important;"
                                  "}");
    // 创建一个水平布局来放置新按钮
    QHBoxLayout* gameModeLayout = new QHBoxLayout;
    gameModeLayout->addWidget(vsAIButton);
    gameModeLayout->addWidget(vsPlayerButton);

    // 创建一个垂直布局来放置按钮布局
    QVBoxLayout* newPageLayout = new QVBoxLayout(newPageWidget);
    newPageLayout->addLayout(gameModeLayout);

    // 将新页面设置为主窗口的中央部件
    setCentralWidget(newPageWidget);
    // 连接人机对战按钮的点击信号到槽函数
    connect(vsAIButton, &QPushButton::clicked, this, &MainWindow::onVsAIButtonClicked);

    // 连接真人对战按钮的点击信号到槽函数
    connect(vsPlayerButton, &QPushButton::clicked, this, &MainWindow::onVsPlayerButtonClicked);
}
// 人机对战按钮点击事件的槽函数
void MainWindow::onVsAIButtonClicked()//这个名字和用途不符 但是我懒得改了qwq——by NJUPT-B24040316李博涵
{
    QWidget* gameContainer = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(gameContainer);

    board = new Board(this);
    mainLayout->addWidget(board,1);
    // 创建操作按钮栏
    QWidget* buttonBar = new QWidget(gameContainer);
    QHBoxLayout* btnLayout = new QHBoxLayout(buttonBar);

    // 悔棋按钮
    QPushButton* regretButton = new QPushButton("悔棋", buttonBar);
    regretButton->setFixedSize(80, 30);

    // 返回按钮
    QPushButton* returnButton = new QPushButton("返回", buttonBar);
    returnButton->setFixedSize(80, 30);

    // 设置返回按钮样式
    returnButton->setStyleSheet("QPushButton {"
                                "background-color: rgba(255,255,255,150);"
                                "border-radius: 4px;"
                                "font: bold 14px;"
                                "}"
                                "QPushButton:hover { background-color: rgba(255,255,255,200); }");

    // 添加按钮到按钮栏布局
    btnLayout->addStretch();
    btnLayout->addWidget(regretButton);
    btnLayout->addWidget(returnButton);

    mainLayout->addWidget(buttonBar);

    // 设置为主界面
    setCentralWidget(gameContainer);
    board->startGame(true, false); // 启用双人模式

    // 连接按钮信号
    connect(regretButton, &QPushButton::clicked, this, &MainWindow::on_regretButton_clicked);
    connect(returnButton, &QPushButton::clicked, this, &MainWindow::on_returnButton_clicked); // 连接返回按钮信号
}

void MainWindow::onVsPlayerButtonClicked()//这个名字也和用途不符TAT
{
    // 创建选择棋子颜色对话框
    QDialog* colorDialog = new QDialog(this);
    colorDialog->setWindowTitle("选择棋子颜色");
    colorDialog->setMinimumSize(300, 150);

    // 创建对话框布局
    QVBoxLayout* dialogLayout = new QVBoxLayout(colorDialog);

    // 添加提示标签
    QLabel* promptLabel = new QLabel("请选择您要执的颜色：", colorDialog);
    dialogLayout->addWidget(promptLabel);

    // 创建按钮容器
    QWidget* buttonContainer = new QWidget(colorDialog);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);

    // 创建选择按钮
    QPushButton* blackButton = new QPushButton("黑棋", buttonContainer);
    QPushButton* whiteButton = new QPushButton("白棋", buttonContainer);
    QPushButton* cancelButton = new QPushButton("取消", buttonContainer);

    // 设置按钮属性
    blackButton->setMinimumSize(80, 30);
    whiteButton->setMinimumSize(80, 30);
    cancelButton->setMinimumSize(80, 30);

    // 添加按钮到布局
    buttonLayout->addWidget(blackButton);
    buttonLayout->addWidget(whiteButton);
    buttonLayout->addWidget(cancelButton);

    dialogLayout->addWidget(buttonContainer);

    // 连接按钮信号
    // 在按钮点击时设置对话框属性
    connect(blackButton, &QPushButton::clicked, [colorDialog]() {
        colorDialog->setProperty("isPlayerBlack", true);
        colorDialog->accept();
    });

    connect(whiteButton, &QPushButton::clicked, [colorDialog]() {
        colorDialog->setProperty("isPlayerBlack", false);
        colorDialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, colorDialog, &QDialog::reject);

    // 处理对话框关闭事件
    connect(colorDialog, &QDialog::finished, [this, colorDialog](int result) {
        if (result == QDialog::Accepted) {
            bool isPlayerBlack = colorDialog->property("isPlayerBlack").toBool();

            // 创建游戏主界面
            QWidget* gameContainer = new QWidget();
            QVBoxLayout* mainLayout = new QVBoxLayout(gameContainer);

            // 创建棋盘
            board = new Board(gameContainer);
            mainLayout->addWidget(board, 1);

            // 创建操作按钮栏
            QWidget* buttonBar = new QWidget(gameContainer);
            QHBoxLayout* btnLayout = new QHBoxLayout(buttonBar);

            // 悔棋按钮
            QPushButton* regretButton = new QPushButton("悔棋", buttonBar);
            regretButton->setFixedSize(80, 30);

            QPushButton* returnButton = new QPushButton("返回", buttonBar);
            returnButton->setFixedSize(80, 30);

            // 设置返回按钮样式
            returnButton->setStyleSheet("QPushButton {"
                                        "background-color: rgba(255,255,255,150);"
                                        "border-radius: 4px;"
                                        "font: bold 14px;"
                                        "}"
                                        "QPushButton:hover { background-color: rgba(255,255,255,200); }");

            // 添加按钮到按钮栏布局
            btnLayout->addStretch();
            btnLayout->addWidget(regretButton);
            btnLayout->addWidget(returnButton);

            mainLayout->addWidget(buttonBar);

            // 设置为主界面
            setCentralWidget(gameContainer);

            // 初始化游戏
            board->startGame(isPlayerBlack,true);

            if (!isPlayerBlack) {
                QTimer::singleShot(500, this, [this]() {
                    if (board && !board->gameOver) {
                        board->makeMove(7, 7);
                    }
                });
            }

            // 连接按钮信号
            connect(regretButton, &QPushButton::clicked, this, &MainWindow::on_regretButton_clicked);
            connect(returnButton, &QPushButton::clicked, this, &MainWindow::on_returnButton_clicked);
        }
        colorDialog->deleteLater();
    });

    // 显示模态对话框
    colorDialog->exec();
}


void MainWindow::on_regretButton_clicked()
{
    if (board) {
        board->regretMove(); // 调用 Board 类的悔棋函数
        board->regretMove();
    }
}

void MainWindow::on_returnButton_clicked()
{
    // 创建一个新的窗口部件来显示选择对战模式的页面
    QWidget* newPageWidget = new QWidget(this);

    // 设置新页面的背景图片
    newPageWidget->setStyleSheet("QWidget { border-image: url(:/res/NewBackground.jpg); }");
    newPageWidget->setObjectName("NewPageWidget");

    // 创建人机对战和真人对战按钮
    QPushButton* vsAIButton = new QPushButton("真人对战", this);
    QPushButton* vsPlayerButton = new QPushButton("人机对战", this);

    // 设置按钮样式
    vsAIButton->setStyleSheet("QPushButton {"
                              "background-color: rgba(255,255,255,0.8);"
                              "border: 10px solid rgba(255,255,255,0.5);"
                              "min-width: 200px;"
                              "padding: 15px;"
                              "border-radius: 8px;"
                              "font: bold 18px;"
                              "color: #FFFFFF;"
                              "}"
                              "QPushButton:hover {"
                              "   background-color: rgba(255,255,255,1);"
                              "   border-color: rgba(76,175,80,0.8);"
                              "}");
    vsPlayerButton->setStyleSheet("QPushButton {"
                                  "background-color: rgba(255,255,255,0.8);"
                                  "border: 10px solid rgba(255,255,255,0.5);"
                                  "min-width: 200px;"
                                  "padding: 15px;"
                                  "border-radius: 8px;"
                                  "font: bold 18px;"
                                  "color: #FFFFFF;"
                                  "}"
                                  "QPushButton:hover {"
                                  "   background-color: rgba(255,255,255,1);"
                                  "   border-color: rgba(76,175,80,0.8);"
                                  "}");

    // 创建一个水平布局来放置按钮
    QHBoxLayout* gameModeLayout = new QHBoxLayout;
    gameModeLayout->addWidget(vsAIButton);
    gameModeLayout->addWidget(vsPlayerButton);

    // 创建一个垂直布局来放置按钮布局
    QVBoxLayout* newPageLayout = new QVBoxLayout(newPageWidget);
    newPageLayout->addLayout(gameModeLayout);

    // 将新页面设置为主窗口的中央部件
    setCentralWidget(newPageWidget);

    // 连接按钮信号
    connect(vsAIButton, &QPushButton::clicked, this, &MainWindow::onVsAIButtonClicked);
    connect(vsPlayerButton, &QPushButton::clicked, this, &MainWindow::onVsPlayerButtonClicked);
}


void MainWindow::on_gameEnded(const QString &winner)
{
    // 显示游戏结束的消息框
    QMessageBox::information(this, "游戏结束", winner);
}
