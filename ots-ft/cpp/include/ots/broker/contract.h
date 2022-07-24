//
// Created by 稻草人 on 2022/7/6.
//

#ifndef OTS_FT_CONTRACT_H
#define OTS_FT_CONTRACT_H
#include "magic_enum.hpp"
#include "ots/utils/logger.h"
#include "spdlog/spdlog.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ots::broker {
    using ots::data::Contract;

    class ContractTable {
    private:
        // 禁止外部构造
        ContractTable() {
            SPDLOG_TRACE("ContractTable");
        };
        // 禁止外部析构
        ~ContractTable() { SPDLOG_TRACE("~ContractTable"); };

    public:
        // 禁止外部复制构造
        ContractTable(const ContractTable &signal) = delete;
        // 禁止外部赋值操作
        const ContractTable &operator=(const ContractTable &signal) = delete;

    private:
        bool is_inited_ = false;
        std::vector<Contract> contract_vector_;
        std::unordered_map<std::string, Contract> contract_map_;

    private:
        static ContractTable *get() {
            static ContractTable ct;
            return &ct;
        };

    public:
        static bool Init(std::vector<Contract> &vec) {
            if (!get()->is_inited_) {
                auto &contracts = get()->contract_vector_;
                auto &contract_map_ = get()->contract_map_;
                contracts = vec;
                for (auto iter: contracts) {
                    const std::string symbol = iter.symbol;
                    contract_map_[symbol] = iter;
                }
                get()->is_inited_ = true;
            } else {
                SPDLOG_WARN("ContractTable:{}", get()->is_inited_);
            }
            return true;
        }

        static void ShowTable() {
            SPDLOG_INFO("ShowTable");
            if (!get()->is_inited_) {
                SPDLOG_ERROR("ContractTable:{}", get()->is_inited_);
                return;
            }

            auto &contract_map_ = get()->contract_map_;
            for (auto iter = contract_map_.begin(); iter != contract_map_.end(); iter++) {
                SPDLOG_INFO("symbol:{}, exchange_id:{}, product_id:{}, order_max_limit:{}, order_min_limit:{}, "
                            "contract_multiple:{}, price_tick:{}, expire_date:{}, long_margin_ratio:{}, "
                            "short_margin_ratio:{}, price_max_limit:{}, price_min_limit:{}, product_class:{}.",
                            iter->second.symbol,
                            iter->second.exchange_id,
                            iter->second.product_id,
                            iter->second.volume_max_limit,
                            iter->second.volume_min_limit,
                            iter->second.contract_multiple,
                            iter->second.price_tick,
                            iter->second.expire_date,
                            iter->second.long_margin_ratio,
                            iter->second.short_margin_ratio,
                            iter->second.price_max_limit,
                            iter->second.price_min_limit,
                            magic_enum::enum_name(iter->second.contract_type));
            }
        }

        // TODO:
        static std::unordered_map<std::string, Contract> GetTable() {
            return get()->contract_map_;
        }

        static Contract get_contract(const std::string &symbol) {
            return get()->contract_map_[symbol];
        }
    };
}// namespace ots::broker

#endif//OTS_FT_CONTRACT_H
