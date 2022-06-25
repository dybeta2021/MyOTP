//
// Created by 稻草人 on 2022/6/25.
//

#ifndef APP_CTP_FUTURE_QUOTE_ENGINE_QUOTE_H
#define APP_CTP_FUTURE_QUOTE_ENGINE_QUOTE_H

namespace ots::data {
    //行情
    struct Quote {
        char source_id[32];         //柜台ID
        char symbol[32];            //合约ID
        int64_t source_time;        //柜台时间戳
        int64_t insert_time;        //本地时间戳
        double pre_close_price;     //昨收价
        double pre_settlement_price;//昨结价
        double last_price;          //最新价
        int64_t volume;             //数量
        double turnover;            //成交金额
        double pre_open_interest;   //昨持仓量
        double open_interest;       //持仓量
        double open_price;          //今开盘
        double high_price;          //最高价
        double low_price;           //最低价
        double upper_limit_price;   //涨停板价
        double lower_limit_price;   //跌停板价
        double close_price;         //收盘价
        double settlement_price;    //结算价
        double bid_price[10];       //申买价
        double ask_price[10];       //申卖价
        int64_t bid_volume[10];     //申买量
        int64_t ask_volume[10];     //申卖量
    };
}// namespace ots::data

#endif//APP_CTP_FUTURE_QUOTE_ENGINE_QUOTE_H
