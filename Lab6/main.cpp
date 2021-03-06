#include <iostream>
#include "GameBoard.h"

int main(int argc, char **argv) {
    GameBoard sb;

    // 检测是否采用了文件输入的测试模式
    string filename_in;
    string filename_out;
    for (int i = 0; i < argc; ++i) {
        string arg_in = "-i";
        string arg_out = "-o";
        if (argv[i] == arg_in) {
            filename_in = argv[i + 1];
        } else if (argv[i] == arg_out) {
            filename_out = argv[i + 1];
        }
    }
    if (!filename_in.empty() && !filename_out.empty()) {
        GameBoard gameBoard;
        gameBoard.test(filename_in, filename_out);
    }

    GameBoard gameBoard;
    gameBoard.board_init(4);

    string test_mode = "-t";
    string size_change = "-s";
    string log_mode = "-log";
    string bonus_mode = "-p";
    bool log_mode_bool = false;

    for (int i = 0; i < argc; ++i) {
        if (log_mode == (argv[i])) {
            cout << "开启日志功能，将生成txt日志文件" << endl;
            gameBoard.log_mode_on();
            log_mode_bool = true;
        }
    }
    for (int i = 0; i < argc; ++i) {
        if (test_mode == (argv[i])) {
            cout << "开启测试模式,合成出数字64时游戏结束" << endl;
            gameBoard.test_mode_on();
        } else if (size_change == (argv[i])) {
            if (i + 1 < argc) {// 确认-s后有参数
                char size = argv[i + 1][0];
                size -= '0';
                if (size > 5 or size < 2) {
                    cout << "-s 参数需要是2-5的数字,请重新输入指令" << endl;
                    exit(0);
                } else {
                    gameBoard.board_init(size);
                }
            }
        } else if (bonus_mode == (argv[i])) {
            cout << "开启奖励功能，1秒内操作可获得额外分数";
            // 根据log_mode_bool决定是否开启日志
            gameBoard.bonus_mode_on(log_mode_bool);
        }
    }
    gameBoard.start();
    return 0;
}
