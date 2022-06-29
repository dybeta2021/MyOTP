//
// Created by 稻草人 on 2022/6/28.
//
#include "ots/utils/logger.h"
#include "broker.h"

int main() {
    ots::broker::Config config{};
    config.quote_ip = "tcp://122.51.136.165:20004";
    config.trade_ip = "tcp://122.51.136.165:20002";
    config.broker_id = "1234";
    config.user_id = "2815";
    config.password = "123456";
    config.app_id = "open_ctp";
    config.auth_code = "open_ctp";

    bool init_log = ots::utils::create_logger("clogs/broker_engine.log", "trace", true, false, false);
    SPDLOG_INFO("Broker-Engine CTP-Future.");

    auto gateway = ctp_future::CtpTradeClient();
    auto broker = broker_engine::BrokerCTP();
    gateway.SetBroker(&broker);
    broker.SetGateway(&gateway);
    broker.Login(config);
    broker.QueryAccount();
    broker.QueryPosition();
    ots::utils::timing_ms(60000);


    broker.Logout();
    ots::utils::timing_ms(10000);
}
