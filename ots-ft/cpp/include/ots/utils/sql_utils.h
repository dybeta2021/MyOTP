//
// Created by 稻草人 on 2022/7/11.
//

#ifndef OTS_FT_SQL_UTILS_H
#define OTS_FT_SQL_UTILS_H

#include "SQLiteCpp/SQLiteCpp.h"
#include "fmt/format.h"
#include "ots/broker/contract.h"
#include "spdlog/spdlog.h"
#include <iostream>

namespace ots::sql {
    using namespace ots::broker;

    inline std::vector<Contract> get_commodity_future_contract() {
        SQLite::Database db("static_data.sqlite");

        // last-time
        SQLite::Statement query_last_time(db, ""
                                              "SELECT DISTINCT InsertTime FROM static_data ORDER BY InsertTime LIMIT 1;"
                                              "");
        query_last_time.executeStep();
        std::string last_time = query_last_time.getColumn(0);
        SPDLOG_TRACE("SQLite static_data, last_time: {}", last_time);

        // last-data
        std::string sql = fmt::format(""
                                      "SELECT InstrumentID,\n"
                                      "       ExchangeID,\n"
                                      "       ProductID,\n"
                                      "       MaxLimitOrderVolume,\n"
                                      "       MinLimitOrderVolume,\n"
                                      "       VolumeMultiple,\n"
                                      "       PriceTick,\n"
                                      "       ExpireDate,\n"
                                      "       LongMarginRatio,\n"
                                      "       ShortMarginRatio,\n"
                                      "       UpperLimitPrice,\n"
                                      "       LowerLimitPrice,\n"
                                      "       ContractType\n"
                                      "FROM static_data WHERE InsertTime = '{}' AND ContractType='CommodityFuture';"
                                      "",
                                      last_time);
        SQLite::Statement cursor(db, sql.c_str());
        std::vector<Contract> contract_vector;
        while (cursor.executeStep()) {
            Contract contract{};

            const std::string symbol = cursor.getColumn(0);
            strcpy(contract.symbol, symbol.c_str());
            const std::string exchange_id = cursor.getColumn(1);
            strcpy(contract.exchange_id, exchange_id.c_str());
            const std::string product_id = cursor.getColumn(2);
            strcpy(contract.product_id, product_id.c_str());
            contract.volume_max_limit = cursor.getColumn(3);
            contract.volume_min_limit = cursor.getColumn(4);
            contract.contract_multiple = cursor.getColumn(5);
            // TODO:是否全部使用double格式
            contract.price_tick = cursor.getColumn(6);
            const std::string expire_date = cursor.getColumn(7);
            strcpy(contract.expire_date, expire_date.c_str());
            contract.long_margin_ratio = cursor.getColumn(8);
            contract.short_margin_ratio = cursor.getColumn(9);
            contract.price_max_limit = cursor.getColumn(10);
            contract.price_min_limit = cursor.getColumn(11);
            const auto contract_type = cursor.getColumn(12);
            if (contract_type.getString() == "CommodityFuture") {
                contract.contract_type = ots::data::ContractType::CommodityFuture;
            } else {
                SPDLOG_ERROR("sqlite static-data error!");
            }
            contract_vector.emplace(contract_vector.end(), contract);
        }
        return contract_vector;
    }

    inline std::vector<Contract> get_stock_index_future_contract() {
        SQLite::Database db("static_data.sqlite");

        // last-time
        SQLite::Statement query_last_time(db, ""
                                              "SELECT DISTINCT InsertTime FROM static_data ORDER BY InsertTime LIMIT 1;"
                                              "");
        query_last_time.executeStep();
        std::string last_time = query_last_time.getColumn(0);
        SPDLOG_TRACE("SQLite static_data, last_time: {}", last_time);

        // last-data
        std::string sql = fmt::format(""
                                      "SELECT InstrumentID,\n"
                                      "       ExchangeID,\n"
                                      "       ProductID,\n"
                                      "       MaxLimitOrderVolume,\n"
                                      "       MinLimitOrderVolume,\n"
                                      "       VolumeMultiple,\n"
                                      "       PriceTick,\n"
                                      "       ExpireDate,\n"
                                      "       LongMarginRatio,\n"
                                      "       ShortMarginRatio,\n"
                                      "       UpperLimitPrice,\n"
                                      "       LowerLimitPrice,\n"
                                      "       ContractType\n"
                                      "FROM static_data WHERE InsertTime = '{}' AND ContractType='StockIndexFuture';"
                                      "",
                                      last_time);
        SQLite::Statement cursor(db, sql.c_str());
        std::vector<Contract> contract_vector;
        while (cursor.executeStep()) {
            Contract contract{};

            const std::string symbol = cursor.getColumn(0);
            strcpy(contract.symbol, symbol.c_str());
            const std::string exchange_id = cursor.getColumn(1);
            strcpy(contract.exchange_id, exchange_id.c_str());
            const std::string product_id = cursor.getColumn(2);
            strcpy(contract.product_id, product_id.c_str());
            contract.volume_max_limit = cursor.getColumn(3);
            contract.volume_min_limit = cursor.getColumn(4);
            contract.contract_multiple = cursor.getColumn(5);
            // TODO:是否全部使用double格式
            contract.price_tick = cursor.getColumn(6);
            const std::string expire_date = cursor.getColumn(7);
            strcpy(contract.expire_date, expire_date.c_str());
            contract.long_margin_ratio = cursor.getColumn(8);
            contract.short_margin_ratio = cursor.getColumn(9);
            contract.price_max_limit = cursor.getColumn(10);
            contract.price_min_limit = cursor.getColumn(11);
            const auto contract_type = cursor.getColumn(12);
            if (contract_type.getString() == "StockIndexFuture") {
                contract.contract_type = ots::data::ContractType::StockIndexFuture;
            } else {
                SPDLOG_ERROR("sqlite static-data error!");
            }

            contract_vector.emplace(contract_vector.end(), contract);
        }
        return contract_vector;
    }

}// namespace ots::sql

#endif//OTS_FT_SQL_UTILS_H
