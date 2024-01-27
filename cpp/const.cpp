#include <iostream>

int main()
{
    int i = 100;

    // 允许常量引用 引用非常量
    const int &r = i;

    // 创建临时变量，引用它
    const int &c = 100;

    const int *p2 = nullptr;
    p2 = &i;

    constexpr int *p = nullptr;
    // p = &i;  // 错误，constexpr 用于指针表示 顶层const，指针不可修改


    i = 101;

    std::cout << "r=" << r << std::endl;
}