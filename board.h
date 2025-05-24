// board.h
#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QStack>
#include <QPair>
#include <QMessageBox>

using namespace std;

// 定义棋盘大小为15×15
const int BOARD_SIZE = 15;
// 定义棋盘上的棋子状态枚举类型
enum Piece { EMPTY, BLACK, WHITE };

// 定义Board类，继承自QWidget
class Board : public QWidget
{
    Q_OBJECT

public:
    // 构造函数，参数为父窗口部件，默认为nullptr
    explicit Board(QWidget *parent = nullptr);
    // 开始游戏的方法，参数表示玩家是否为黑方
    void startGame(bool playerIsBlack, bool isVsAI = false);
    void setVsAI(bool isVsAI); // 添加设置游戏模式的方法
    void regretMove(); // 添加悔棋函数声明
    // 定义棋盘状态的二维数组
    Piece board[BOARD_SIZE][BOARD_SIZE];
    // 定义历史走棋位置的栈
    QStack<QPair<int, int>> moveHistory;
    // 定义当前玩家
    Piece currentPlayer;
    // 定义玩家是否为黑方
    bool isPlayerBlack;
    // 定义游戏是否结束
    bool gameOver;
    // 定义错误信息字符串
    string errorMsg;
    //------------------------下面是函数区域----------------------------

    // 清空棋盘的方法
    void clearBoard();

    // 检查是否获胜的方法，参数为行和列的坐标
    bool checkWin(int row, int col);

    // 获取AI走棋位置的方法
    pair<int, int> getAIMove();

    // 绘制棋盘的方法，参数为QPainter引用
    void drawBoard(QPainter &painter);

    // 绘制棋子的方法，参数为QPainter引用
    void drawPieces(QPainter &painter);

    // 处理玩家走棋的方法，参数为鼠标点击的坐标
    void handlePlayerMove(int x, int y);

    // 结束游戏的方法，参数为获胜者信息
    void endGame(const QString &winner);

    // 从控制台代码中提取的辅助函数
    // 评估某个点的得分，参数为行、列坐标和棋子状态
    int evaluatePoint(int row, int col, Piece side);
    void makeMove(int row, int col);
    // 获取某个位置的得分，参数为行、列坐标和棋子状态
signals:
    // 游戏结束信号，参数为获胜者信息
    void gameEnded(const QString &winner);

protected:
    // 重写绘制事件方法，用于绘制棋盘和棋子
    void paintEvent(QPaintEvent *event) override;
    // 重写鼠标点击事件方法，用于处理玩家走棋
    void mousePressEvent(QMouseEvent *event) override;
private:
    bool ItisVsAI; // 标志是否对战 AI
};

#endif // BOARD_H
