//
// Created by 稻草人 on 2022/7/18.
//

#ifndef OTS_FT_DEFINE_H
#define OTS_FT_DEFINE_H
#include <utility>
#define OTS_ORDER_VECTOR_SIZE 8192


namespace ots::define {
    enum class ContractType : int8_t {
        Stock = 0,
        StockETF = 1,
        StockETFOption = 2,
        StockIndexFuture = 3,
        StockIndexOption = 4,
        CommodityFuture = 5,
        CommodityOption = 6
    };

    //多空方向
    enum class Direction {
        Long = 1,
        Short = 2
    };

    //开平类型
    enum class Offset {
        Open = 1,
        Close = 2,
        CloseToday = 3,
        CloseYesterday = 4,
    };

    // HedgeFlag 投机套保标识
    enum class HedgeFlag {
        Speculation = 1
    };

    // 交易所的英文简称
    namespace exchange {
        // 上海期货交易所
        constexpr char SHFE[] = "SHFE";
        // 上海国际能源交易所
        constexpr char INE[] = "INE";
        // 中国金融期货交易所
        constexpr char CFFEX[] = "CFFEX";
        // 郑州商品交易所
        constexpr char CZCE[] = "CZCE";
        // 大连商品交易所
        constexpr char DCE[] = "DCE";
        // 上海证券交易所-A股
        constexpr char SSE[] = "SH";
        // 深圳证券交易所-A股
        constexpr char SZE[] = "SZ";
    }// namespace exchange
}// namespace ots::define

#endif//OTS_FT_DEFINE_H
