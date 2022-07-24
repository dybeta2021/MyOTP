//
// Created by 稻草人 on 2022/6/29.
//
// 用户使用的终端接口

#ifndef CPP_BROKER_H
#define CPP_BROKER_H
#include "account.h"
#include "order.h"
#include "position.h"
#include <string>

namespace ots::broker {
    using ots::data::Account;
    using ots::data::Order;
    using ots::data::Position;

    class Broker {
    protected:
        AccountManager *account_manager_ = nullptr;
        PositionManager *position_manager_ = nullptr;
        OrderManager *order_manager_ = nullptr;

    public:
        Broker() = default;
        ~Broker() = default;

        void SetAccountManager(AccountManager &account_manager){
            account_manager_ = &account_manager;
        }

        void SetPositionManager(PositionManager &position_manager){
            position_manager_ = &position_manager;
        }

        void SetOrderManager(OrderManager &order_manager){
            order_manager_ = &order_manager;
        }

    public:
        virtual int Login() = 0;
        virtual int Logout() = 0;

        // 查询broker参数设置
        virtual int QueryParams() = 0;
        virtual void OnQueryParams() = 0;

        // 查询账户资金
        virtual int QueryAccount() = 0;
        virtual void OnQueryAccount(const Account &account) = 0;

        // 请求查询持仓
        virtual int QueryPosition() = 0;
        virtual void OnQueryPosition(const Position &position) = 0;
        virtual void ShowPosition() = 0;

        // 限价单，当日有效
        virtual int InsertLimitOrder(Order &order) = 0;

        // 市价单，当日有效
        virtual int InsertMarketOrder(Order &order) = 0;

        //        // 成交响应， 持仓模块
        //        virtual void OnTradeLongOpen(const Position &position) = 0;
        //        virtual void OnTradeShortOpen(const Position &position) = 0;
        //        virtual void OnTradeLongClose(const Position &position) = 0;
        //        virtual void OnTradeShortClose(const Position &position) = 0;

        //        virtual int InsertOrder(const order::Order &order) = 0;
    };
}// namespace ots::broker


#endif//CPP_BROKER_H
