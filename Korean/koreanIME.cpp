/**
 * @file koreanIME.cpp
 * @brief
 * @author dcl
 * @version 1.0.0.0
 * @date 2019-11-19
 */
#include <map>
#include <QVector>
using namespace std;

namespace KoreanIME
{
    enum HangulMedialIndex
    {                                 // VIndex    Letter Jungseong   Double Jamo
        // ----------------------------------------------------------------------
        HANGUL_MEDIAL_A,              //      0      314F      1161
        HANGUL_MEDIAL_AE,             //      1      3150      1162
        HANGUL_MEDIAL_YA,             //      2      3151      1163
        HANGUL_MEDIAL_YAE,            //      3      3152      1164
        HANGUL_MEDIAL_EO,             //      4      3153      1165
        HANGUL_MEDIAL_E,              //      5      3154      1166
        HANGUL_MEDIAL_YEO,            //      6      3155      1167
        HANGUL_MEDIAL_YE,             //      7      3156      1168
        HANGUL_MEDIAL_O,              //      8      3157      1169
        HANGUL_MEDIAL_WA,             //      9      3158      116A     3157+314F
        HANGUL_MEDIAL_WAE,            //     10      3159      116B     3157+3150
        HANGUL_MEDIAL_OE,             //     11      315A      116C     3157+3163
        HANGUL_MEDIAL_YO,             //     12      315B      116D
        HANGUL_MEDIAL_U,              //     13      315C      116E
        HANGUL_MEDIAL_WEO,            //     14      315D      116F     315C+3153
        HANGUL_MEDIAL_WE,             //     15      315E      1170     315C+3154
        HANGUL_MEDIAL_WI,             //     16      315F      1171     315C+3163
        HANGUL_MEDIAL_YU,             //     17      3160      1172
        HANGUL_MEDIAL_EU,             //     18      3161      1173
        HANGUL_MEDIAL_YI,             //     19      3162      1174     3161+3163
        HANGUL_MEDIAL_I               //     20      3163      1175
    };
    enum HangulFinalIndex
    {                                 // TIndex    Letter Jongseong   Double Jamo
        // ----------------------------------------------------------------------
        HANGUL_FINAL_NONE,            //      0       n/a       n/a
        HANGUL_FINAL_KIYEOK,          //ㄱ      1      3131      11A8
        HANGUL_FINAL_SSANGKIYEOK,     //ᄁ      2      3132      11A9
        HANGUL_FINAL_KIYEOK_SIOS,     //ㄳ      3      3133      11AA     3131+3145
        HANGUL_FINAL_NIEUN,           //ᄂ      4      3134      11AB
        HANGUL_FINAL_NIEUN_CIEUC,     //ᆬ      5      3135      11AC     3134+3148
        HANGUL_FINAL_NIEUN_HIEUH,     //ᆭ      6      3136      11AD     3134+314E
        HANGUL_FINAL_TIKEUT,          //ᄃ      7      3137      11AE
        HANGUL_FINAL_RIEUL,           //ᄅ      8      3139      11AF
        HANGUL_FINAL_RIEUL_KIYEOK,    //ᆰ      9      313A      11B0     3139+3131
        HANGUL_FINAL_RIEUL_MIEUM,     //ᆱ     10      313B      11B1     3139+3141
        HANGUL_FINAL_RIEUL_PIEUP,     //ᆲ     11      313C      11B2     3139+3142
        HANGUL_FINAL_RIEUL_SIOS,      //ᆳ     12      313D      11B3     3139+3145
        HANGUL_FINAL_RIEUL_THIEUTH,   //ᆴ     13      313E      11B4     3139+314C
        HANGUL_FINAL_RIEUL_PHIEUPH,   //ᆵ     14      313F      11B5     3139+314D
        HANGUL_FINAL_RIEUL_HIEUH,     //ᄚ     15      3140      11B6     3139+314E
        HANGUL_FINAL_MIEUM,           //ᄆ     16      3141      11B7
        HANGUL_FINAL_PIEUP,           //ᄇ     17      3142      11B8
        HANGUL_FINAL_PIEUP_SIOS,      //ᄡ     18      3144      11B9     3142+3145
        HANGUL_FINAL_SIOS,            //ᄉ     19      3145      11BA
        HANGUL_FINAL_SSANGSIOS,       //ᄊ     20      3146      11BB
        HANGUL_FINAL_IEUNG,           //ᄋ     21      3147      11BC
        HANGUL_FINAL_CIEUC,           //ᄌ     22      3148      11BD
        HANGUL_FINAL_CHIEUCH,         //ᄎ     23      314A      11BE
        HANGUL_FINAL_KHIEUKH,         //ᄏ     24      314B      11BF
        HANGUL_FINAL_THIEUTH,         //ᄐ     25      314C      11C0
        HANGUL_FINAL_PHIEUPH,         //ᄑ     26      314D      11C1
        HANGUL_FINAL_HIEUH            //ᄒ     27      314E      11C2
    };

    using t_unicode = unsigned short;

    //19辅音L
    const static QVector<t_unicode> initials =
    {
        0x3131, 0x3132, 0x3134, 0x3137, 0x3138, 0x3139, 0x3141,
        0x3142, 0x3143, 0x3145, 0x3146, 0x3147, 0x3148, 0x3149,
        0x314A, 0x314B, 0x314C, 0x314D, 0x314E
    };

    //21个元音是连续的:0x314f...0x3163,因此没有定义的必要了
    //const static QVector<t_unicode> medial = { };

    //27个收音T
    static const QVector<t_unicode> finals =
    {
        0x0000, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136,
        0x3137, 0x3139, 0x313A, 0x313B, 0x313C, 0x313D, 0x313E,
        0x313F, 0x3140, 0x3141, 0x3142, 0x3144, 0x3145, 0x3146,
        0x3147, 0x3148, 0x314A, 0x314B, 0x314C, 0x314D, 0x314E
    };

    static const map<t_unicode, HangulFinalIndex> doubleFinalMap =
    {
        {4865,  HANGUL_FINAL_KIYEOK_SIOS},
        {5636, HANGUL_FINAL_NIEUN_CIEUC},
        {6916, HANGUL_FINAL_NIEUN_HIEUH},
        {264, HANGUL_FINAL_RIEUL_KIYEOK},
        {4104, HANGUL_FINAL_RIEUL_MIEUM},
        {4360, HANGUL_FINAL_RIEUL_PIEUP},
        {4872, HANGUL_FINAL_RIEUL_SIOS},
        {6408, HANGUL_FINAL_RIEUL_THIEUTH},
        {6664, HANGUL_FINAL_RIEUL_PHIEUPH},
        {6920, HANGUL_FINAL_RIEUL_HIEUH},
        {4881, HANGUL_FINAL_PIEUP_SIOS},
    };

    constexpr t_unicode LCount = 19;
    constexpr t_unicode VCount = 21;
    constexpr t_unicode TCount = 28;
    constexpr t_unicode SCount = LCount * VCount * TCount;
    constexpr t_unicode SBase = 0xAC00;

    inline bool isL(const t_unicode u)
    {
        return initials.contains(u);
    }

    inline bool isV(const t_unicode u)
    {
        return (u >= 0x314f && u <= 0x3163);
    }

    inline bool isT(const t_unicode u)
    {
        return finals.contains(u);
    }

    inline bool isLV(const t_unicode u)
    {
        if (u >= SBase && u <= SBase + SCount && (u - SBase)% TCount == 0)
            return true;
        return false;
    }

    inline bool isLVT(const t_unicode u)
    {
        if (u >= SBase && u <= SBase + SCount && (u - SBase) % TCount != 0)
            return true;
        return false;
    }

    inline int indexOfL(const t_unicode u)
    {
        return initials.indexOf(u);
    }

    inline int indexOfV(const t_unicode u)
    {
        if (u >= 0x314f && u <= 0x3163)
            return u - 0x314f;
        return -1;
    }

    inline int indexOfT(const t_unicode u)
    {
        return finals.indexOf(u);
    }

    t_unicode do_L_V(const t_unicode l, const t_unicode v)
    {
        return SBase + static_cast<t_unicode>(indexOfL(l) * VCount * TCount + indexOfV(v) * TCount);
    }

    t_unicode do_LV_T(const t_unicode lv, const t_unicode t)
    {
        return lv + static_cast<t_unicode>(indexOfT(t));
    }

    //before callback, must make sure lv is lv syllable, and v is vowel jamo
    //if can compose lv + v, us lv as output params.
    bool try_LV_V(t_unicode& lv, const t_unicode& v)
    {
        static const map<unsigned short, HangulMedialIndex> doubleMedialMap =
        {
            {8,    HANGUL_MEDIAL_WA},
            {264,  HANGUL_MEDIAL_WAE},
            {5128, HANGUL_MEDIAL_OE},
            {1037, HANGUL_MEDIAL_WEO},
            {1293, HANGUL_MEDIAL_WE},
            {5133, HANGUL_MEDIAL_WI},
            {5138, HANGUL_MEDIAL_YI}
        };
        auto v1 = (lv - SBase) % (VCount * TCount) / TCount;
        auto v2 = indexOfV(v);
        auto it = doubleMedialMap.find(static_cast<t_unicode>(v1 | v2 << 8));
        if (doubleMedialMap.end() != it)
        {
            lv = lv + static_cast<t_unicode>((it->second - v1) * TCount);
            return true;
        }

        return false;
    }

    //before callback, must make sure lvt is lvt syllable, and v is vowel jamo
    //if can compose lvt + v to lv + lv, then use lvt as first output, v as second output.
    bool do_LVT_V(t_unicode& lvt, t_unicode& v)
    {
        auto tIndex = (lvt - SBase) % TCount;
        auto lIndex = initials.indexOf(finals[tIndex]);
        if (lIndex != -1) //lvt is lvt
        {
            lvt = lvt - static_cast<t_unicode>(tIndex);
            v = do_L_V(initials[lIndex], v);
        }
        else //lvt is lvtt
        {
            // In this scenario, the double consonant is split into parts
            // and the second part is removed from the current syllable.
            // Then the second part is joined with the current vowel making
            // the new syllable of form LV.
            auto it = find_if(doubleFinalMap.cbegin(), doubleFinalMap.cend(),[tIndex](const pair<t_unicode, HangulFinalIndex>& t){
                return t.second == tIndex;
            });
            auto t1 = it->first & 0xFF;
            auto t2 = it->first >> 8 & 0xFF;
            lvt = static_cast<t_unicode>(lvt + (t1 - tIndex));
            v = do_L_V(finals[t2], v);
        }
        return true;
    }

    //before callback, must make sure lvt is lvt syllable, and t is final consonant.
    //if can compose lvt + t , then use lvt as output params.
    bool try_LVT_T(t_unicode& lvt, const t_unicode& t)
    {
        auto t1Index = (lvt - SBase) % TCount;
        auto t2Index = indexOfT(t);
        auto it = doubleFinalMap.find(t1Index | t2Index << 8);
        if (it != doubleFinalMap.cend())
        {
            lvt = static_cast<t_unicode>(lvt + (it->second - t1Index));
            return true;
        }
        return false;
    }


    list<t_unicode> compose(const list<t_unicode>& source)
    {
        list<t_unicode> result;
        if (source.size() == 0)
            return result;

        auto it = source.cbegin();
        t_unicode preC = *it++;
        result.push_back(preC);

        for(; it != source.cend(); it++)
        {
            /** In the following five cases, preC and currentC can be
              * composed into Korean characters:
              *   preC       currentC        syllable-type
              *    L             V               LV
              *    LV            T               LVT
              *    LV            V               LV
              *    LVT           T               LVT
              *    LVT           V               LV+LV / LVT+LV
             **/
            auto currentC = *it;

            //1. compose way: L + V -> LV
            if (isL(preC) && isV(currentC))
            {
                preC = do_L_V(preC, currentC);
                result.pop_back();
                result.push_back(preC);
                continue;
            }

            //2. compose way: LV + T -> LVT
            if (isLV(preC) && isT(currentC))
            {
                preC = do_LV_T(preC, currentC);
                result.pop_back();
                result.push_back(preC);
                continue;
            }

            //3. compose way: LV + V -> LV
            if (isLV(preC) && isV(currentC))
            {
                if (try_LV_V(preC, currentC))
                    result.pop_back();
                result.push_back(preC);
                continue;
            }

            //4. compose way: LVT + T -> LVT
            if (isLVT(preC) && isT(currentC))
            {
                if (try_LVT_T(preC, currentC))
                    result.pop_back();
                result.push_back(preC);
                continue;
            }

            //5. compose way: LVT + V -> LV + LV
            //                LVT + V -> LVT + LV
            if (isLVT(preC) && isV(currentC))
            {
                do_LVT_V(preC, currentC);
                result.pop_back();
                result.push_back(preC);
                result.push_back(currentC);
                preC = currentC;
                continue;
            }

            preC = currentC;
            result.push_back(preC);
        }

        return result;
    }
}


