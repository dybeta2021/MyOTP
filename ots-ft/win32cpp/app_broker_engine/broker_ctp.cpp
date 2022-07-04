//
// Created by 稻草人 on 2022/6/30.
//

#include "broker_ctp.h"

void BrokerCTP::SetGateway(CtpTradeClient *client) {
    client_ = client;
}

int BrokerCTP::Login(const ots::broker::Config &config) {
    config_ = config;

    std::string dir_path = "ctp_future_td_flow";
    ots::utils::create_folder(dir_path);

    SPDLOG_INFO("连接交易前置机.");
    client_->Connect(const_cast<char *>(config.trade_ip.c_str()));
    timing_ms(2000);

    // 终端认证 容易失败！
    int counter = 0;
    while (true) {
        counter++;
        if (counter > 10) {
            SPDLOG_ERROR("终端认证失败，退出程序.");
            return -1;
        }
        int intAuthRet = client_->Authenticate(const_cast<char *>(config.broker_id.c_str()),
                                               const_cast<char *>(config.user_id.c_str()),
                                               const_cast<char *>(config.app_id.c_str()),
                                               const_cast<char *>(config.auth_code.c_str()));
        SPDLOG_INFO("发送终端认证请求：" + std::to_string(intAuthRet));
        timing_ms(500);
        if (intAuthRet == 0) {
            break;
        }
    }
    timing_ms(1000);

    // 账户登录
    client_->Login(const_cast<char *>(config.broker_id.c_str()),
                   const_cast<char *>(config.user_id.c_str()),
                   const_cast<char *>(config.password.c_str()));
    timing_ms(500);

    // 结算单
    client_->SettlementInfoConfirm(const_cast<char *>(config.broker_id.c_str()),
                                   const_cast<char *>(config.user_id.c_str()));
    ots::utils::timing_ms(500);
    return 0;
}

int BrokerCTP::Logout() {
    client_->Logout(const_cast<char *>(config_.broker_id.c_str()), const_cast<char *>(config_.user_id.c_str()));
    client_->Release();
    return 0;
}

int BrokerCTP::QueryAccount() {
    auto ret = client_->QueryAccount(const_cast<char *>(config_.broker_id.c_str()), const_cast<char *>(config_.user_id.c_str()));
    if (!ret) {
        return -1;
    }
    return 0;
}

void BrokerCTP::OnQueryAccount(const ots::broker::Account &account) {
    account_ = account;
    SPDLOG_DEBUG("OnQueryAccount, account:{}, assess:{}, balance:{}, cash:{}, margin:{}, frozen:{}, pnl:{}", account_.account_id, account.total_asset, account_.balance, account_.cash, account_.margin, account_.frozen, account_.floating_pnl);
}

int BrokerCTP::QueryPosition() {
    auto ret = client_->QueryPosition(const_cast<char *>(config_.broker_id.c_str()), const_cast<char *>(config_.user_id.c_str()));
    if (!ret) {
        return -1;
    }
    return 0;
}