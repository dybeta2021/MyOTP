//
// Created by 稻草人 on 2022/6/29.
//

#ifndef OTS_FT_BROKER_CTP_H
#define OTS_FT_BROKER_CTP_H
#include "ctp_trade_api.h"
#include "ots/broker/broker.h"
#include "ots/broker/position.h"
#include "ots/utils/create_folder.h"
#include "ots/utils/encoding.h"
#include "ots/utils/timing.h"
#include "spdlog/spdlog.h"
#include <unordered_map>

using ots::utils::timing_ms;

class BrokerCTP : public ots::broker::Broker {
private:
    CtpTradeApi *client_ = nullptr;

public:
    BrokerCTP() = default;
    ~BrokerCTP() = default;

    void SetGateway(CtpTradeApi *client);

    int Login() override;
    int Logout() override;

    int QueryParams() override;

    int QueryAccount() override;

    int QueryPosition() override;

    int InsertLimitOrder(ots::data::Order &order) override;
    int InsertMarketOrder(ots::data::Order &order) override;
    int CancelOrder(ots::data::Order &order) override;
};


#endif//OTS_FT_BROKER_CTP_H
