/**
 * @file koreanIME.h
 * @brief
 * @author dcl
 * @version 1.0.0.0
 * @date 2019-11-19
 */

#include <list>

namespace KoreanIME
{
    /**
     * @brief 根据传入的韩语字根，返回拼写出来的韩字
     *
     * @paramsource  存放输入字根的list
     *
     * @return 返回拼写出来的字根
     */
    std::list<unsigned short> compose(const std::list<unsigned short>& source);

}; //end namespace "KoreanIME"


