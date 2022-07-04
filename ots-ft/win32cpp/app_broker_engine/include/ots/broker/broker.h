//
// Created by Gavin on 2022/6/29.
//
// 用户使用的终端接口

#ifndef CPP_BROKER_H
#define CPP_BROKER_H
#include <string>

namespace ots::broker {
    struct Config {
        std::string quote_ip{};
        std::string trade_ip{};
        std::string broker_id{};
        std::string user_id{};
        std::string password{};
        std::string app_id{};
        std::string auth_code{};
    };

    struct Account {
        char account_id[32];// 投资者帐号
        double total_asset; // 总资产
        double balance;     // 结余
        double cash;        // 可用资金
        double margin;      // 保证金
        double frozen;      // 冻结金额
        double floating_pnl;// 浮动盈亏
    };

    class Broker {
    protected:
        Account account_{};
        Config config_{};

    public:
        Broker() = default;
        ~Broker() = default;
        virtual int Login(const ots::broker::Config &config) = 0;
        virtual int Logout() = 0;

        virtual int QueryAccount() = 0;
        virtual void OnQueryAccount(const Account &account) = 0;

        virtual int QueryPosition() = 0;
    };
}// namespace ots::broker


#endif//CPP_BROKER_H
