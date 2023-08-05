#include <iostream>
#include <string>

#include "test_construct.h"

class TestCls {
    public:
        SimpleCls use_simple;

        TestCls(int v);
        TestCls(SimpleCls S);

    private:
        std::string name;
};


TestCls::TestCls(int v)
    : use_simple(v)     //调用一次SimpleCls的构造函数
{
    std::cout << "TestCls 构造函数\n";
}

TestCls::TestCls(SimpleCls S)
    : use_simple(S)     //S按值传递，调用复制构造; 为use_simple赋值，再次调用复制构造函数
{
    std::cout << "TestCls 构造函数2\n";
}

class TestCls2 {
    public:
        SimpleCls use_simple;

        // 如果SimpleCls没有定义无参构造函数（默认构造函数），这必须通过列表初始化，
        // 不能在这个构造函数中赋值
        TestCls2(int v) {
            std::cout << "TestCls2 构造函数\n";
            this->use_simple = SimpleCls(v);
        }

        // 如果SimpleCls没有定义无参构造函数（默认构造函数），这必须通过列表初始化，
        // 不能在这个构造函数中赋值
        TestCls2(SimpleCls v) {
            std::cout << "TestCls2 构造函数2\n";
            this->use_simple = v;
        }

    private:
        std::string name;
};



int main()
{
    TestCls  A(2);
    A.use_simple.print();

    printf("====2=====\n");

    SimpleCls s(100);
    TestCls A2(s);
    A2.use_simple.print();

    printf("====3=====\n");

    TestCls2 B(3);
    B.use_simple.print();

    printf("====4=====\n");
    SimpleCls s2(100);
    TestCls2 B2(s2);
    B2.use_simple.print();

    return 0;
}

/*
SimpleCls ： 构造函数
TestCls 构造函数
smaple_cls:value = 2
====2=====
SimpleCls ： 构造函数
SimpleCls ： 拷贝构造函数
SimpleCls ： 拷贝构造函数
TestCls 构造函数2
smaple_cls:value = 100
====3=====
TestCls2 构造函数
SimpleCls ： 构造函数
赋值构造函数
smaple_cls:value = 3
====4=====
SimpleCls ： 构造函数
SimpleCls ： 拷贝构造函数
TestCls2 构造函数2
赋值构造函数
smaple_cls:value = 100

*/