#ifndef SIMPLE_CLS_H
#define SIMPLE_CLS_H

class SimpleCls
{
public:
    int value;

    SimpleCls() = default;

    SimpleCls(int v)
    {
        std::cout << "SimpleCls ： 构造函数\n";
        value = v;
    }

    SimpleCls(const SimpleCls &A)
    {
        std::cout << "SimpleCls ： 拷贝构造函数\n";
        value = A.value;
    }

    SimpleCls &operator=(const SimpleCls &p)
    {
        std::cout << "赋值构造函数" << std::endl;
        this->value = p.value;

        return *this;
    }

    void print()
    {
        std::cout << "smaple_cls:value = " << value << "\n";
    }

    ~SimpleCls() = default;
};

#endif
