/**
 * @file main.cpp
 * @brief
 * @author dcl
 * @version 1.0.0.0
 * @date 2019-11-19
 */
#include "koreanIME.h"
#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <codecvt>
#include <QDebug>

#include <sys/time.h>
class ITime
{
    public:
        int elapsed(void)
        {
            struct timeval t;
            gettimeofday(&t, nullptr);
//            return ((t.tv_sec - _t.tv_sec) * 1000+ (t.tv_usec - _t.tv_usec) / 1000);
            return ((t.tv_sec - _t.tv_sec) * 1000 * 1000 + (t.tv_usec - _t.tv_usec));
        }

        void restart(void)
        {
            gettimeofday(&_t, nullptr);
        }

        void start(void)
        {
            restart();
        }

        ITime()
        {
            restart();
        }

        ~ITime()
        {
        }

    private:
        struct timeval _t;
};

QString IndexOf(QString& str, int index)
{
    int i = 0;
    QChar high;
    for (auto& t : str)
    {
        if (t.isHighSurrogate())
        {
            if (index == i)
                high = t;
            continue;
        }

        if (index == i)
        {
            return (t.isLowSurrogate() ? QString(high).append(t) : QString(t));
        }

        i++;
    }

    return QString(high);
}

void Test(QString&& other) {
    qDebug() << "QString &&";
}

void Test(const QString& other) {
    qDebug() << "const QString &";
}

/**
 * @brief  \u 表示UNICODE码； \x 表示utf-8编码后的数据
 * @return
 */
int main(void)
{
#if 1    //测试学习编码知识
    std::string utf8 = "\U0001d10bz\u6c34\U0001d10b\U0001D10F\u0398xyz\U0001d10b";
    std::cout << utf8 << std::endl;
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf8to16conv;
    std::u16string  utf16 = utf8to16conv.from_bytes(utf8);
    qDebug() << "fromu16string: " << QString::fromStdU16String(utf16);
    QString str;
    for (auto c : utf16)
    {
        qDebug() << str.append(QChar(c));
    }
    qDebug() << "str fromu16string: " << str;
    qDebug() << "directr :  " << "z\u6c34\U0001d10b";

    qDebug() << str.count() << ":" << str;
    auto t = str.toUcs4();
    for (auto tp : t)
    {
        qDebug() << QString(QString::fromUcs4(&tp, 1));
    }

    qDebug() << "IndexOf " << IndexOf(str, 0);

#endif

#if 0
    QString str;
    for (int i = 0; i < 10000; ++i)
    {
        str += "\U0001d10bz\u6c34\U0001d10b\U0001D10F\u0398xyz\U0001d10b";
    }

    ITime t;

    Test(IndexOf(str, 10000));;
    qDebug() << t.elapsed();
    t.restart();

    auto vec = str.toUcs4();
    QString ret(QString::fromUcs4(&(vec.at(10000)), 1));
    qDebug() << t.elapsed();

#endif

#if 0
    std::list<unsigned short> source = {
        0x3131, 0x3151
    };
    auto dst = KoreanIME::compose(source);
#endif
    return 0;
}

