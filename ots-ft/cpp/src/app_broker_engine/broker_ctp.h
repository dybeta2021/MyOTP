//
// Created by 稻草人 on 2022/6/29.
//

#ifndef OTS_FT_BROKER_CTP_H
#define OTS_FT_BROKER_CTP_H

#include "ots/broker/broker.h"
#include "ots/utils/create_folder.h"
#include "ots/utils/encoding.h"
#include "ots/utils/logger.h"
#include "ots/utils/timing.h"
#include "gateway.h"
#include <unordered_map>

// TODO:修改为信号量
using ots::utils::timing_ms;

class BrokerCTP : public ots::broker::Broker {
private:
    CtpTradeClient *client_ = nullptr;

public:
    BrokerCTP(){};
    ~BrokerCTP(){};
    void SetGateway(CtpTradeClient *client);

    int Login(const ots::broker::Config &config) override;
    int Logout() override;

    int QueryAccount() override;
    void OnQueryAccount(const ots::broker::Account &account) override;

    int QueryPosition() override;
    //        void OnQueryPosition() override;
};


#endif//OTS_FT_BROKER_CTP_H
