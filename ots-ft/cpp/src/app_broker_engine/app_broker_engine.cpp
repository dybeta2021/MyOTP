//
// Created by 稻草人 on 2022/6/28.
//
#include "ots/utils/logger.h"
#include "broker_ctp.h"
#include "kftime.h"
#include "ots/broker/order.h"
#include "ots/utils/sql_utils.h"
#include "ots/utils/timing.h"
#include <fmt/format.h>


int main() {
    // logger
    bool init_log = ots::utils::create_logger("clogs/broker_engine.log", "trace", false, false, false);
    SPDLOG_INFO("MyOTS启动.");

    // static-data
    auto contract_vector = ots::sql::get_commodity_future_contract();
    ots::broker::ContractTable::Init(contract_vector);
    //todo:打开
//    ots::broker::ContractTable::ShowTable();

    // login
    ots::data::Config config{};
    config.quote_ip = "tcp://122.51.136.165:20004";
    config.trade_ip = "tcp://122.51.136.165:20002";
    //config.trade_ip = "tcp://121.36.146.182:20002";
    config.broker_id = "1234";
    config.account_id = "2815";
    config.password = "123456";
    config.app_id = "open_ctp";
    config.auth_code = "open_ctp";
    config.agent_id = "agent_test";
    config.source_id = "ctp_future";

    auto gateway = CtpTradeApi();
    auto broker = BrokerCTP();
    gateway.SetConfig(config);
    gateway.SetBroker(&broker);
    broker.SetGateway(&gateway);

    if (broker.Login() != 0) {
        SPDLOG_ERROR("Broker-Login.");
        return -1;
    }
    SPDLOG_INFO("MyOTS交易账户登陆.");

    if (broker.QueryParams() != 0) {
        SPDLOG_ERROR("Broker-QueryParams.");
        return -1;
    }
    SPDLOG_INFO("MyOTS设置交易账户参数.");

    // position manager
    auto today = kungfu::yijinjing::time::strfnow("%F");
    auto position_manager = ots::broker::PositionManager();
    for (auto iter: contract_vector) {
        ots::data::Position position{};
        position.type = iter.contract_type;
        strcpy(position.date, today.c_str());
        strcpy(position.symbol, iter.symbol);
        strcpy(position.product_id, iter.product_id);
        strcpy(position.exchange_id, iter.exchange_id);
        strcpy(position.source_id, config.source_id.c_str());
        strcpy(position.account_id, config.account_id.c_str());
        position.holding = 0;
        position.today_holding = 0;
        position.yesterday_holding = 0;
        position.frozen_holding = 0;
        position.frozen_margin = 0;
        position.last_price = 0;
        position.settlement_price = 0;
        position.margin = 0;
        position.average_price = 0;
        position.position_profit = 0;
        position.close_profit = 0;
        position.commission = 0;
        position.frozen_commission = 0;
        position.update_time = kungfu::yijinjing::time::now_in_nano();
        strcpy(position.update_msg, "Init");
        position.direction = ots::data::Direction::Long;
        position_manager.Init(position);
        position.direction = ots::data::Direction::Short;
        position_manager.Init(position);
    }
    broker.SetPositionManager(position_manager);
    if (broker.QueryPosition() != 0) {
        SPDLOG_ERROR("Broker-QueryPosition.");
        return -1;
    }
    SPDLOG_INFO("MyOTS设置持仓管理模块.");

    auto account_manager = ots::broker::AccountManager();
    broker.SetAccountManager(account_manager);
    if (broker.QueryAccount() != 0) {
        SPDLOG_ERROR("QueryAccount.");
        return -1;
    }
    SPDLOG_INFO("MyOTS设置资金管理模块.");

    auto order_manager = ots::broker::OrderManager();
    broker.SetOrderManager(order_manager);
    // 下单测试 市价单
    {
        ots::data::Order order{};
        strcpy(order.agent_id, config.agent_id.c_str());
        strcpy(order.account_id, config.account_id.c_str());
        strcpy(order.exchange_id, ots::data::exchange::SHFE);
        strcpy(order.symbol, "bu2208");
        order.direction = ots::data::Direction::Long;
        order.offset = ots::data::Offset::Open;
        order.hedge_flag = ots::data::HedgeFlag::Speculation;
        order.volume = 100;
        order.type = ots::data::OrderType::Market;
        broker.InsertMarketOrder(order);
    }

    // 下单测试 限价单
    {
        ots::data::Order order{};
        strcpy(order.agent_id, config.agent_id.c_str());
        strcpy(order.account_id, config.account_id.c_str());
        strcpy(order.exchange_id, ots::data::exchange::SHFE);
        strcpy(order.symbol, "bu2208");
        order.direction = ots::data::Direction::Short;
        order.offset = ots::data::Offset::Open;
        order.hedge_flag = ots::data::HedgeFlag::Speculation;
        order.volume = 100;
        order.type = ots::data::OrderType::Limit;
        auto contract = ots::broker::ContractTable::get_contract(order.symbol);
        order.price = contract.price_min_limit;
        broker.InsertLimitOrder(order);
    }

    SPDLOG_INFO("Broker初始化成功.");
    ots::utils::timing_ms(5000000);
}
