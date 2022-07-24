//
// Created by 稻草人 on 2022/7/16.
//

#ifndef OTS_FT_ACCOUNT_H
#define OTS_FT_ACCOUNT_H
#include "ots/data.h"
#include "spdlog/spdlog.h"

//todo: 盘中出入金
namespace ots::broker {
    class AccountManager {
    private:
        ots::data::Account account_;

    public:
        AccountManager() = default;
        ~AccountManager() = default;

        void OnQuery(const ots::data::Account &st) {
            account_ = st;

            SPDLOG_DEBUG("Query, account_id:{}, pre_balance:{}, balance:{}, withdraw:{}, deposit:{}, available_cash:{}, frozen_cash:{}, margin:{}, "
                         "frozen_margin:{}, close_profit:{}, position_profit:{}, commission:{}, frozen_commission:{}, update_msg:{}",
                         account_.account_id,
                         account_.pre_balance,
                         account_.balance,
                         account_.withdraw,
                         account_.deposit,
                         account_.available_cash,
                         account_.frozen_cash,
                         account_.margin,
                         account_.frozen_margin,
                         account_.close_profit,
                         account_.position_profit,
                         account_.commission,
                         account_.frozen_commission,
                         account_.update_msg);
        }

        /// Update from Position Manager
        /// \param st
        void OnPosition(const ots::data::Account &st) {
            account_.margin = st.margin;
            account_.frozen_margin = st.frozen_margin;
            account_.close_profit = st.close_profit;
            account_.position_profit = st.position_profit;
            account_.commission = st.commission;
            account_.frozen_commission = st.frozen_commission;
            account_.update_time = st.update_time;
            account_.balance = account_.pre_balance + account_.close_profit + account_.position_profit - account_.commission + account_.deposit - account_.withdraw;
            account_.available_cash = account_.balance - account_.margin - account_.frozen_margin - account_.frozen_commission;
            strcpy(account_.update_msg, "Position");
            SPDLOG_DEBUG("OnPosition, account_id:{}, pre_balance:{}, balance:{}, withdraw:{}, deposit:{}, available_cash:{}, frozen_cash:{}, margin:{}, "
                         "frozen_margin:{}, close_profit:{}, position_profit:{}, commission:{}, frozen_commission:{}, update_msg:{}",
                         account_.account_id,
                         account_.pre_balance,
                         account_.balance,
                         account_.withdraw,
                         account_.deposit,
                         account_.available_cash,
                         account_.frozen_cash,
                         account_.margin,
                         account_.frozen_margin,
                         account_.close_profit,
                         account_.position_profit,
                         account_.commission,
                         account_.frozen_commission,
                         account_.update_msg);
        }

        ots::data::Account* GetAccount(){
            return &account_;
        }
    };

}// namespace ots::broker

#endif//OTS_FT_ACCOUNT_H
