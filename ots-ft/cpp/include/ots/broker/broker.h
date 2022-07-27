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

        void SetAccountManager(AccountManager &account_manager) {
            account_manager_ = &account_manager;
        }

        void SetPositionManager(PositionManager &position_manager) {
            position_manager_ = &position_manager;
        }

        void SetOrderManager(OrderManager &order_manager) {
            order_manager_ = &order_manager;
        }

        // 查询broker一些柜台参数设置
        void OnQueryParams(){};

        // 查询资金账户回报
        void OnQueryAccount(const ots::broker::Account &account) {
            account_manager_->OnQuery(account);
            account_manager_->OnPosition(position_manager_->GetAccount());
        }

        // 查询持仓回报
        void OnQueryPosition(const ots::data::Position &position) {
            position_manager_->OnQuery(position);
        }

        // 显示持仓
        void ShowPosition() {
            position_manager_->Show();
        }

        // 订单回报
        void OnOrderEntrust(const OrderEntrust &entrust) {
            order_manager_->OnEntrust(entrust);
        };

        void OnOrderRejected(const OrderRejected &rejected) {
            order_manager_->OnRejected(rejected);
        }

        // 成交回报
        void OnOrderTrade(const OrderTransaction &transaction) {
            position_manager_->OnTrade(transaction);
        };

        // 初始查询订单回报
        void OnOrderQuery(const Order &order) {
            order_manager_->OnQuery(order);
        }

    public:
        virtual int Login() = 0;
        virtual int Logout() = 0;

        // 查询broker参数设置
        virtual int QueryParams() = 0;

        // 查询账户资金
        virtual int QueryAccount() = 0;

        // 请求查询持仓
        virtual int QueryPosition() = 0;

        // 限价单，当日有效
        virtual int InsertLimitOrder(Order &order) = 0;
        // 市价单，当日有效
        virtual int InsertMarketOrder(Order &order) = 0;
        // 撤单
        virtual int CancelOrder(Order &order) = 0;
    };
}// namespace ots::broker


#endif//CPP_BROKER_H
