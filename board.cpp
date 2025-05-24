// board.cpp
#include "board.h"
#include <QTimer>

Board::Board(QWidget *parent) : QWidget(parent)
{
    clearBoard();
    isPlayerBlack = true;
    gameOver = false;
    ItisVsAI = false;
}

void Board::startGame(bool isPlayerBlack, bool isVsAI)
{
    clearBoard();
    ItisVsAI = isVsAI; // 设置游戏模式
    this->isPlayerBlack = isPlayerBlack;
    currentPlayer = BLACK;
    gameOver = false;
    update();
}

void Board::clearBoard()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = EMPTY;
    moveHistory.clear();
}

bool Board::checkWin(int row, int col)
{
    const int directions[4][2] = { {0,1},{1,0},{1,1},{1,-1} };
    Piece target = board[row][col];
    for (auto& dir : directions) {
        int count = 1;
        for (int d = -1; d <= 1; d += 2) {
            int dx = dir[0] * d;
            int dy = dir[1] * d;
            int x = row + dx, y = col + dy;
            while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE &&
                   board[x][y] == target) {
                count++;
                x += dx;
                y += dy;
            }
        }
        if (count >= 5)
            return true;
    }
    return false;
}

int Board::evaluatePoint(int row, int col, Piece side)
{
    const int dirs[4][2] = { {0,1},{1,0},{1,1},{1,-1} };
    int score = 0;

    for (auto& dir : dirs) {
        int count = 1, blocks = 0;

        for (int d = -1; d <= 1; d += 2) {
            int dx = dir[0] * d;
            int dy = dir[1] * d;
            int x = row + dx;
            int y = col + dy;

            while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE &&
                   board[x][y] == side) {
                count++;
                x += dx;
                y += dy;
            }

            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE ||
                board[x][y] != EMPTY) {
                blocks++;
            }
        }

        if (count >= 5) score += 100000;
        else if (count == 4 && blocks == 0) score += 10000;
        else if (count == 4 && blocks == 1) score += 5000;
        else if (count == 3 && blocks == 0) score += 1000;
        else if (count == 3 && blocks == 1) score += 500;
        else if (count == 2 && blocks == 0) score += 200;
        else if (count == 2 && blocks == 1) score += 100;
    }

    return score;
}

pair<int, int> Board::getAIMove()
{
    int bestScore = -1;
    pair<int, int> bestMove = { -1, -1 };
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != EMPTY) continue;

            int selfScore = evaluatePoint(i, j, currentPlayer);
            Piece opponent = (currentPlayer == BLACK ? WHITE : BLACK);
            int opponentScore = evaluatePoint(i, j, opponent);
            int totalScore = selfScore + opponentScore * 0.9;

            if (totalScore > bestScore) {
                bestScore = totalScore;
                bestMove = { i, j };
            }
        }
    }
    return bestMove;
}

void Board::drawBoard(QPainter &painter)
{
    // 计算网格大小，使棋盘适应窗口
    int gridSize = qMin(width(), height()) / (BOARD_SIZE + 1);
    int offset = gridSize; // 计算棋盘偏移量

    painter.setPen(Qt::black); // 设置画笔颜色为黑色

    // 绘制棋盘网格线
    for (int i = 0; i < BOARD_SIZE; ++i) {
        // 绘制水平线
        painter.drawLine(offset, offset + i * gridSize,
                         offset + (BOARD_SIZE - 1) * gridSize, offset + i * gridSize);
        // 绘制垂直线
        painter.drawLine(offset + i * gridSize, offset,
                         offset + i * gridSize, offset + (BOARD_SIZE - 1) * gridSize);
    }

    // 设置标记颜色为灰色
    painter.setPen(Qt::gray);

    // 绘制行和列的标记
    for (int i = 0; i < BOARD_SIZE; ++i) {
        // 绘制行号标记（数字）
        painter.drawText(offset - gridSize/2, offset + i * gridSize + gridSize/2,
                         QString::number(i+1));
        // 绘制列标记（字母）
        painter.drawText(offset + i * gridSize + gridSize/2,
                         offset + BOARD_SIZE * gridSize - gridSize/2,
                         QChar('A' + i));
    }
}

void Board::drawPieces(QPainter &painter)
{
    int gridSize = qMin(width(), height()) / (BOARD_SIZE + 1); // 计算网格大小
    int offset = gridSize; // 计算棋盘偏移量

    for (int i = 0; i < BOARD_SIZE; ++i) { // 遍历每一行
        for (int j = 0; j < BOARD_SIZE; ++j) { // 遍历每一列
            if (board[i][j] != EMPTY) { // 如果格子不为空（有棋子）
                int x = offset + j * gridSize; // 计算棋子的 x 坐标
                int y = offset + i * gridSize; // 计算棋子的 y 坐标

                painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

                if (board[i][j] == BLACK) { // 如果是黑棋
                    painter.setBrush(Qt::black); // 设置画刷为黑色
                    painter.drawEllipse(x - gridSize/2, y - gridSize/2, gridSize, gridSize); // 绘制黑棋
                } else { // 如果是白棋
                    painter.setBrush(Qt::white); // 设置画刷为白色
                    painter.drawEllipse(x - gridSize/2, y - gridSize/2, gridSize, gridSize); // 绘制白棋填充
                    painter.setPen(Qt::black); // 设置画笔为黑色（绘制边框）
                    painter.drawEllipse(x - gridSize/2, y - gridSize/2, gridSize, gridSize); // 绘制白棋边框
                }
            }
        }
    }
}

void Board::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // 忽略未使用的参数event，避免编译警告
    QPainter painter(this); // 创建一个QPainter对象，用于在当前窗口绘制
    drawBoard(painter); // 调用自定义函数绘制棋盘
    drawPieces(painter); // 调用自定义函数绘制棋子
}

void Board::mousePressEvent(QMouseEvent *event)
{
    if (gameOver) return; // 如果游戏结束，不处理鼠标事件

    int gridSize = qMin(width(), height()) / (BOARD_SIZE + 1); // 计算网格大小
    int offset = gridSize; // 计算棋盘偏移量

    // 使用 position() 方法获取鼠标点击的坐标
    QPointF pos = event->position();
    int x = pos.x();
    int y = pos.y();

    // 将屏幕坐标转换为棋盘坐标
    int col = (x - offset + gridSize/2) / gridSize;
    int row = (y - offset + gridSize/2) / gridSize;

    // 检查点击是否在棋盘范围内且该位置为空
    if (col >= 0 && col < BOARD_SIZE && row >= 0 && row < BOARD_SIZE && board[row][col] == EMPTY) {
        handlePlayerMove(row, col); // 调用函数处理玩家移动
    }
}
void Board::handlePlayerMove(int row, int col)
{
    // 仅在人机对战模式下检查当前玩家是否允许操作
    if (ItisVsAI && currentPlayer != (isPlayerBlack ? BLACK : WHITE))
        return;

    // 更新棋盘状态
    board[row][col] = currentPlayer;
    moveHistory.push({row, col});
    update();

    if (checkWin(row, col)) {
        endGame(isPlayerBlack ? "黑棋获胜!" : "白棋获胜!");
        return;
    }

    currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;

    // 仅在人机对战模式下触发 AI 回合
    if (ItisVsAI) {
        QTimer::singleShot(500, this, [this]() {
            if (!gameOver) {
                auto move = getAIMove();
                board[move.first][move.second] = currentPlayer;
                moveHistory.push(move);
                update();

                if (checkWin(move.first, move.second)) {
                    endGame(isPlayerBlack ? "白棋获胜!" : "黑棋获胜!");
                    return;
                }

                currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
            }
        });
    }
}
void Board::makeMove(int row, int col)
{
    if (gameOver || board[row][col] != EMPTY) return;

    board[row][col] = currentPlayer;
    moveHistory.push({row, col});
    update();

    if (checkWin(row, col)) {
        endGame(currentPlayer == BLACK ? "黑棋获胜!" : "白棋获胜!");
        return;
    }

    currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
}
void Board::regretMove()
{
    if (!moveHistory.empty() && !gameOver) { // 如果历史移动栈不为空且游戏未结束
        auto lastMove = moveHistory.top(); // 获取最后一步移动
        board[lastMove.first][lastMove.second] = EMPTY; // 将最后一步的位置设为空
        moveHistory.pop(); // 从历史移动栈中移除最后一步
        currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK; // 切换当前玩家
        update(); // 更新界面
    }
}
void Board::endGame(const QString &winner)
{
    gameOver = true;
    QMessageBox::information(this, "游戏结束", winner);
    emit gameEnded(winner);
}
