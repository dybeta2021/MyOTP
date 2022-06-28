//
// Created by 稻草人 on 2022/6/25.
//

#ifndef APP_CTP_FUTURE_QUOTE_ENGINE_QUOTE_H
#define APP_CTP_FUTURE_QUOTE_ENGINE_QUOTE_H

namespace ots::data {
    //行情
    struct Quote {
        char source_id[32];        //柜台ID
        char symbol[32];           //合约ID
        int64_t source_time;       //柜台时间戳
        int64_t insert_time;       //本地时间戳
        float pre_close_price;     //昨收价
        float pre_settlement_price;//昨结价
        float last_price;          //最新价
        int64_t volume;            //数量
        double turnover;           //成交金额
        int64_t pre_open_interest; //昨持仓量
        int64_t open_interest;     //持仓量
        float open_price;          //今开盘
        float high_price;          //最高价
        float low_price;           //最低价
        float upper_limit_price;   //涨停板价
        float lower_limit_price;   //跌停板价
        float close_price;         //收盘价
        float settlement_price;    //结算价
        float bid_price[10];       //申买价
        float ask_price[10];       //申卖价
        int64_t bid_volume[10];    //申买量
        int64_t ask_volume[10];    //申卖量
    };
}// namespace ots::data

#endif//APP_CTP_FUTURE_QUOTE_ENGINE_QUOTE_H
