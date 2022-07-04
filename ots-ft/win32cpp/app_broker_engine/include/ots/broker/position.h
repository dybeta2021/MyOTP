//
// Created by 稻草人 on 2022/6/28.
//

#ifndef OTS_FT_POSITION_H
#define OTS_FT_POSITION_H
#include <string>

namespace ots::broker::position {

    enum class ContractType : int8_t {
        Stock,
        StockETF,
        StockETFOption,
        StockIndexFuture,
        StockIndexOption,
        CommodityFuture,
        CommodityOption
    };

    //持仓信息
    struct Position {
        int64_t update_time; //更新时间，ctp返回时间戳
        int64_t receive_time;//更新时间,本地接收时间
        char trading_day[32];
        char symbol[32];
        char underlying_symbol[32];
        ContractType contract_type; //合约类型
        char exchange_id[32];       //交易所ID
        char source_id[32];         //柜台ID
        char account_id[32];        //账号ID
        bool direction;             //持仓方向
        int64_t holding;            //数量
        int64_t yesterday_holding;  //昨仓数量
        int64_t frozen_total;       //冻结数量
        int64_t frozen_yesterday;   //冻结昨仓
        float last_price;          //最新价
        float position_cost_price; //持仓成本价
        float close_price;         //收盘价(股票和债券)
        float pre_close_price;     //昨收价(股票和债券)
        float settlement_price;    //结算价(期货)
        float pre_settlement_price;//昨结算(期货)
        float margin;              //保证金(期货)
    }


}// namespace ots::broker::position

#endif//OTS_FT_POSITION_H
