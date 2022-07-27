//
// Created by 稻草人 on 2022/6/28.
//

#ifndef OTS_FT_POSITION_H
#define OTS_FT_POSITION_H
#include "kftime.h"
#include "magic_enum.hpp"
#include "ots/broker/contract.h"
#include "ots/data.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <string>
#include <unordered_map>

namespace ots::broker {
    using ots::data::Direction;
    using ots::data::Position;

    class PositionManager {
    private:
        std::unordered_map<std::string, Position> long_pos_;
        std::unordered_map<std::string, Position> short_pos_;

    private:
        static void OnTradeLongOpen(Position &pos, const OrderTransaction &st) {
            pos.last_price = st.traded_price;
            pos.position_profit = (st.traded_price - pos.average_price) * (double)pos.holding;
            pos.average_price = (pos.average_price * (double)pos.holding + st.traded_price * st.traded_volume) / (double)(pos.holding + st.traded_volume);
            pos.holding += st.traded_volume;
            pos.today_holding += st.traded_volume;
            // todo:手续费
//            pos.commission += st.commission;
            Contract contract = ContractTable::get_contract(pos.symbol);
            pos.margin = pos.last_price * (double )pos.holding * contract.short_margin_ratio * contract.contract_multiple;
            pos.update_time = st.update_time;
            strcpy(pos.update_msg, "LongOpen");
        }

        static void OnTradeShortOpen(Position &pos, const OrderTransaction &st) {
            pos.last_price = st.traded_price;
            pos.position_profit = (pos.average_price - pos.last_price) * (double)pos.holding;
            pos.average_price = (pos.average_price * (double)pos.holding + st.traded_price * st.traded_volume) / (double)(pos.holding + st.traded_volume);
            pos.holding += st.traded_volume;
            pos.today_holding += st.traded_volume;
            // todo:手续费
//            pos.commission += st.commission;
            Contract contract = ContractTable::get_contract(pos.symbol);
            pos.margin = pos.last_price * (double )pos.holding * contract.short_margin_ratio * contract.contract_multiple;
            pos.update_time = st.update_time;
            strcpy(pos.update_msg, "ShortOpen");
        }

        static void OnTradeLongClose(Position &pos, const OrderTransaction &st) {
            pos.last_price = st.traded_price;
            pos.close_profit += (pos.average_price - st.traded_price) * st.traded_volume;
            pos.position_profit = (pos.average_price - st.traded_price) * (double)(pos.holding - st.traded_volume);
            if (pos.holding > st.traded_volume) {
                pos.average_price = (pos.average_price * (double)pos.holding - st.traded_price * st.traded_volume) / (double)(pos.holding - st.traded_volume);
            } else {
                pos.average_price = 0;
            }
            pos.holding -= st.traded_volume;

            // 上期所
            if (strcmp(st.exchange_id, ots::data::exchange::SHFE) == 0) {
                if (st.offset == Offset::CloseToday) {
                    pos.today_holding -= st.traded_volume;
                } else {
                    pos.yesterday_holding -= st.traded_volume;
                }
            }
            // 上海能源中心
            else if (strcmp(st.exchange_id, ots::data::exchange::INE) == 0) {
                if (st.offset == Offset::CloseToday) {
                    pos.today_holding -= st.traded_volume;
                } else {
                    pos.yesterday_holding -= st.traded_volume;
                }
            }
            // 大商所
            else if (strcmp(st.exchange_id, ots::data::exchange::DCE) == 0) {
                if(pos.yesterday_holding > 0){
                    if (pos.yesterday_holding >= st.traded_volume){
                        pos.yesterday_holding -= st.traded_volume;
                    }else{
                        auto left_num = st.traded_volume - pos.yesterday_holding;
                        pos.yesterday_holding = 0;
                        pos.today_holding -= left_num;
                    }
                }else{
                    pos.today_holding -= st.traded_volume;
                }
            }
            // 郑商所
            else if (strcmp(st.exchange_id, ots::data::exchange::CZCE) == 0) {
                if(pos.yesterday_holding > 0){
                    if (pos.yesterday_holding >= st.traded_volume){
                        pos.yesterday_holding -= st.traded_volume;
                    }else{
                        auto left_num = st.traded_volume - pos.yesterday_holding;
                        pos.yesterday_holding = 0;
                        pos.today_holding -= left_num;
                    }
                }else{
                    pos.today_holding -= st.traded_volume;
                }
            }
            // 中金所
            else if (strcmp(st.exchange_id, ots::data::exchange::CFFEX) == 0) {
                if(pos.yesterday_holding > 0){
                    if (pos.yesterday_holding >= st.traded_volume){
                        pos.yesterday_holding -= st.traded_volume;
                    }else{
                        auto left_num = st.traded_volume - pos.yesterday_holding;
                        pos.yesterday_holding = 0;
                        pos.today_holding -= left_num;
                    }
                }else{
                    pos.today_holding -= st.traded_volume;
                }
            }
            else{
                SPDLOG_CRITICAL("交易所类型:{}.", st.exchange_id);
                return ;
            }

            // todo:手续费
//            pos.commission += st.commission;
            Contract contract = ContractTable::get_contract(pos.symbol);
            pos.margin = pos.last_price * (double )pos.holding * contract.short_margin_ratio * contract.contract_multiple;
            pos.update_time = st.update_time;
            strcpy(pos.update_msg, "LongClose");
        }

        static void OnTradeShortClose(Position &pos, const OrderTransaction &st) {
            pos.last_price = st.traded_price;
            pos.close_profit += (st.traded_price - pos.average_price) * st.traded_volume;
            pos.position_profit = (st.traded_price - pos.average_price) * (double)(pos.holding - st.traded_volume);
            if (pos.holding > st.traded_volume) {
                pos.average_price = (pos.average_price * (double)pos.holding - st.traded_price * st.traded_volume) / (double)(pos.holding - st.traded_volume);
            } else {
                pos.average_price = 0;
            }
            pos.holding -= st.traded_volume;

            // 上期所
            if (strcmp(st.exchange_id, ots::data::exchange::SHFE) == 0) {
                if (st.offset == Offset::CloseToday) {
                    pos.today_holding -= st.traded_volume;
                } else {
                    pos.yesterday_holding -= st.traded_volume;
                }
            }
            // 上海能源中心
            else if (strcmp(st.exchange_id, ots::data::exchange::INE) == 0) {
                if (st.offset == Offset::CloseToday) {
                    pos.today_holding -= st.traded_volume;
                } else {
                    pos.yesterday_holding -= st.traded_volume;
                }
            }
            // 大商所
            else if (strcmp(st.exchange_id, ots::data::exchange::DCE) == 0) {
                if(pos.yesterday_holding > 0){
                    if (pos.yesterday_holding >= st.traded_volume){
                        pos.yesterday_holding -= st.traded_volume;
                    }else{
                        auto left_num = st.traded_volume - pos.yesterday_holding;
                        pos.yesterday_holding = 0;
                        pos.today_holding -= left_num;
                    }
                }else{
                    pos.today_holding -= st.traded_volume;
                }
            }
            // 郑商所
            else if (strcmp(st.exchange_id, ots::data::exchange::CZCE) == 0) {
                if(pos.yesterday_holding > 0){
                    if (pos.yesterday_holding >= st.traded_volume){
                        pos.yesterday_holding -= st.traded_volume;
                    }else{
                        auto left_num = st.traded_volume - pos.yesterday_holding;
                        pos.yesterday_holding = 0;
                        pos.today_holding -= left_num;
                    }
                }else{
                    pos.today_holding -= st.traded_volume;
                }
            }
            // 中金所
            else if (strcmp(st.exchange_id, ots::data::exchange::CFFEX) == 0) {
                if(pos.yesterday_holding > 0){
                    if (pos.yesterday_holding >= st.traded_volume){
                        pos.yesterday_holding -= st.traded_volume;
                    }else{
                        auto left_num = st.traded_volume - pos.yesterday_holding;
                        pos.yesterday_holding = 0;
                        pos.today_holding -= left_num;
                    }
                }else{
                    pos.today_holding -= st.traded_volume;
                }
            }
            else{
                SPDLOG_CRITICAL("交易所类型:{}.", st.exchange_id);
                return ;
            }

            // todo:手续费
//            pos.commission += st.commission;
            Contract contract = ContractTable::get_contract(pos.symbol);
            pos.margin = pos.last_price * (double )pos.holding * contract.short_margin_ratio * contract.contract_multiple;
            pos.update_time = st.update_time;
            strcpy(pos.update_msg, "LongClose");
        }

    public:
        PositionManager() = default;
        ~PositionManager() = default;

        void Init(const Position &position) {
            if (position.direction == Direction::Long) {
                long_pos_[position.symbol] = position;
            } else {
                short_pos_[position.symbol] = position;
            }
        }

        void OnQuery(const Position &st) {
            auto &pos = st.direction == Direction::Long ? long_pos_[st.symbol] : short_pos_[st.symbol];
            if (strcmp(pos.account_id, st.account_id) != 0) {
                SPDLOG_ERROR("MyOTS暂不支持多账户，{}:{}.", pos.account_id, st.account_id);
            }
            if (st.holding > 0) {
                pos.average_price = (pos.average_price * (double) pos.holding + st.average_price * (double) st.holding) /
                                    (double) (pos.holding + st.holding);
            }
            pos.holding += st.holding;
            pos.today_holding += st.today_holding;
            pos.yesterday_holding += st.yesterday_holding;
            pos.frozen_holding += st.frozen_holding;
            pos.frozen_margin += st.frozen_margin;
            pos.margin += st.margin;
            pos.pre_settlement_price = st.pre_settlement_price;
            pos.settlement_price = st.settlement_price;
            pos.position_profit += st.position_profit;
            pos.close_profit += st.close_profit;
            pos.commission += st.commission;
            pos.frozen_commission += st.frozen_commission;
            pos.update_time = st.update_time;
            strcpy(pos.update_msg, st.update_msg);
        }

        void OnTrade(const OrderTransaction &st) {
            auto &pos = st.direction == Direction::Long ? long_pos_[st.symbol] : short_pos_[st.symbol];
            if (strcmp(pos.account_id, st.account_id) != 0) {
                SPDLOG_ERROR("MyOTS暂不支持多账户，{}:{}.", pos.account_id, st.account_id);
            }

            if (st.direction == Direction::Long && st.offset == Offset::Open) {
                OnTradeLongOpen(pos, st);
            } else if (st.direction == Direction::Short && st.offset == Offset::Open) {
                OnTradeShortOpen(pos, st);
            } else if (st.direction == Direction::Long && st.offset != Offset::Open) {
                OnTradeLongClose(pos, st);
            } else if (st.direction == Direction::Short && st.offset != Offset::Open) {
                OnTradeShortClose(pos, st);
            } else {
                SPDLOG_ERROR("ERROR.");
            }
        }

        void Show() {
            for (const auto& iter: long_pos_) {
                if (iter.second.holding != 0) {
                    SPDLOG_INFO("account:{}, date:{}, symbol:{}, direction:{}, holding:{}, today_holding:{}, yesterday_holding:{}, "
                                "frozen_holding:{}, frozen_margin:{}, margin:{}, last_price:{}, settlement_price:{}, pre_settlement_price:{},"
                                "average_price:{}, position_profit:{},  close_profit:{}, commission:{}, frozen_commission:{}, msg:{}",
                                iter.second.account_id,
                                iter.second.date,
                                iter.second.symbol,
                                magic_enum::enum_name(iter.second.direction),
                                iter.second.holding,
                                iter.second.today_holding,
                                iter.second.yesterday_holding,
                                iter.second.frozen_holding,
                                iter.second.frozen_margin,
                                iter.second.margin,
                                iter.second.last_price,
                                iter.second.settlement_price,
                                iter.second.pre_settlement_price,
                                iter.second.average_price,
                                iter.second.position_profit,
                                iter.second.close_profit,
                                iter.second.commission,
                                iter.second.frozen_commission,
                                iter.second.update_msg);
                }
            }

            for (const auto& iter: short_pos_) {
                if (iter.second.holding != 0) {
                    SPDLOG_INFO("account:{}, date:{}, symbol:{}, direction:{}, holding:{}, today_holding:{}, yesterday_holding:{}, "
                                "frozen_holding:{}, frozen_margin:{}, margin:{}, last_price:{}, settlement_price:{}, pre_settlement_price:{},"
                                "average_price:{}, position_profit:{},  close_profit:{}, commission:{}, frozen_commission:{}, msg:{}",
                                iter.second.account_id,
                                iter.second.date,
                                iter.second.symbol,
                                magic_enum::enum_name(iter.second.direction),
                                iter.second.holding,
                                iter.second.today_holding,
                                iter.second.yesterday_holding,
                                iter.second.frozen_holding,
                                iter.second.frozen_margin,
                                iter.second.margin,
                                iter.second.last_price,
                                iter.second.settlement_price,
                                iter.second.pre_settlement_price,
                                iter.second.average_price,
                                iter.second.position_profit,
                                iter.second.close_profit,
                                iter.second.commission,
                                iter.second.frozen_commission,
                                iter.second.update_msg);
                }
            }
        }

        ots::data::Account GetAccount() {
            double long_margin = 0;
            double long_frozen_margin = 0;
            double short_margin = 0;
            double short_frozen_margin = 0;
            double long_close_profit = 0;
            double short_close_profit = 0;
            double long_position_profit = 0;
            double short_position_profit = 0;
            double long_commission = 0;
            double short_commission = 0;
            double long_frozen_commission = 0;
            double short_frozen_commission = 0;
            for (const auto& iter: long_pos_) {
                if (iter.second.holding != 0) {
                    long_margin += iter.second.margin;
                    long_frozen_margin += iter.second.frozen_margin;
                    long_close_profit += iter.second.close_profit;
                    long_position_profit += iter.second.position_profit;
                    long_commission += iter.second.commission;
                    long_frozen_commission += iter.second.frozen_commission;
                }
            }
            for (const auto& iter: short_pos_) {
                if (iter.second.holding != 0) {
                    short_margin += iter.second.margin;
                    short_frozen_margin += iter.second.frozen_margin;
                    short_close_profit += iter.second.close_profit;
                    short_position_profit += iter.second.position_profit;
                    short_commission += iter.second.commission;
                    short_frozen_commission += iter.second.frozen_commission;
                }
            }

            ots::data::Account account{};
            // todo:大边保证金算法
            account.margin = long_margin + short_margin;
            account.frozen_margin = long_frozen_margin + short_frozen_margin;
            account.close_profit = long_close_profit + short_close_profit;
            account.position_profit = long_position_profit + short_position_profit;
            account.commission = long_commission + short_commission;
            account.frozen_commission = long_frozen_commission + short_frozen_commission;
            account.update_time = kungfu::yijinjing::time::now_in_nano();
            return account;
        }
    };


}// namespace ots::broker

#endif//OTS_FT_POSITION_H
