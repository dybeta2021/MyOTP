//
// Created by 稻草人 on 2022/7/18.
//

#ifndef OTS_FT_DATA_H
#define OTS_FT_DATA_H

#include "ots/define.h"
#include <cstdint>
#include <string>


namespace ots::data {
    using namespace ots::define;

    struct Config {
        std::string quote_ip{};
        std::string trade_ip{};
        std::string broker_id{};
        std::string account_id{};
        std::string password{};
        std::string app_id{};
        std::string auth_code{};
        std::string agent_id{}; // 本地身份识别
        std::string source_id{};//柜台ID
    };

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
        int64_t pre_open_interest;  //昨持仓量
        int64_t open_interest;      //持仓量
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

    struct Contract {
        char symbol[32];
        char exchange_id[32];
        char product_id[32];
        int volume_max_limit;  //最大报单数量
        int volume_min_limit;  //最小报单数量
        double price_max_limit;//涨停板
        double price_min_limit;//跌停板
        int contract_multiple; //合约乘数
        double price_tick;     //最小变动价位
        char expire_date[32];
        double long_margin_ratio;
        double short_margin_ratio;
        ContractType contract_type;
    };

    // 订单价格类型
    enum class OrderType {
        // 市价单，不同的平台对市价单的支持不同
        Market = 1,
        // 限价单，指定价格的挂单，订单时限为当日有效
        Limit = 2,
        // 对方最优价格的限价单
        Best = 3,
        // 立即全部成交否则立即撤销，不同平台的实现也不同
        // 对于CTP来说是限价单，需要指定价格
        Fak = 4,
        // 立即成交剩余部分立即撤单，不同平台的实现也不同
        // 对于CTP来说是限价单，需要指定价格
        Fok = 5
    };

    //OrderStatus 委托状态
    enum class OrderStatus {
        Insert = 1,                // 请求报单
        Rejected = 2,              //拒单
        Submitted = 3,             //柜台已接收
        Accepted = 4,              //柜台已受理
        Cancelled = 5,             //撤单
        Filled = 6,                //全部成交
        PartialFilledNotActive = 7,//部成部撤
        PartialFilledActive = 8,   //部分成交
        NetworkError = 9, //网络错误
        Error = 10, //未定义错误
        Unknown = 11
    };

    struct Order {
        size_t order_ref_num;//订单序号
        char trading_day[32]; //真实日期
        int64_t insert_time; //更新时间
        int64_t update_time; //更新时间
        char agent_id[32];
        char account_id[32];
        char exchange_id[32]; //交易所
        char symbol[32]; //合约ID
        ots::define::Direction direction; // 多空
        ots::define::Offset offset;       //开平
        ots::define::HedgeFlag hedge_flag;// 投机套保
        int volume; //委托量
        int traded_volume; //成交数量
        int left_volume; //未成交数量
        int cancel_volume; //撤单数量
        float price; //委托价格
        OrderType type; //订单价格类型（市价、限价、本方最优）
        OrderStatus status;
        int error_code; //错误代码
        char error_msg[64]; //错误信息
    };

    //逐笔委托
    struct Entrust {
        size_t order_ref_num;//订单序号
        int64_t update_time; //更新时间
        int traded_volume;   //成交数量
        int left_volume;     //未成交数量
        int cancel_volume;   //撤单数量
    };

    //持仓信息
    struct Position {
        ContractType type;          //合约类型
        char date[32];              //当前日期
        char symbol[32];            //合约编码
        char product_id[32];        //品种，例如铁矿石i、动力煤zc
        char exchange_id[32];       //交易所ID
        char source_id[32];         //柜台ID
        char account_id[32];        //账号ID
        Direction direction;        //持仓方向
        int64_t holding;            //持仓
        int64_t today_holding;      //今仓
        int64_t yesterday_holding;  //昨仓
        int64_t frozen_holding;     //冻结数量
        double frozen_margin;       //冻结保证金
        double margin;              //保证金(期货)
        double last_price;          //最新价
        double settlement_price;    //结算价(期货)
        double pre_settlement_price;//昨结算(期货)
        double average_price;       //成交均价、当日成本价
        double position_profit;     //持仓盈亏
        double close_profit;        //平仓盈亏
        double commission;          //手续费
        double frozen_commission;   //冻结手续费
        int64_t update_time;        // 刷新时间
        char update_msg[64];        //更新信息
    };

    struct Account {
        char account_id[32];     // 投资者帐号
        double pre_balance;      //上次结算准备金/静态权益
        double balance;          //结算准备金/总资产/净资产/动态权益
        double deposit;          //入金金额
        double withdraw;         //出金金额
        double available_cash;   //可用现金
        double frozen_cash;      //冻结现金
        double margin;           // 保证金
        double frozen_margin;    // 冻结保证金
        double close_profit;     //平仓盈亏
        double position_profit;  //持仓盈亏/浮动盈亏
        double commission;       //手续费
        double frozen_commission;//冻结的手续费
        int64_t update_time;     //更新时间
        char update_msg[64];     //更新信息
    };
}// namespace ots::data

#endif//OTS_FT_DATA_H
