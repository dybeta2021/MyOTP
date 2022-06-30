//
// Created by 稻草人 on 2022/6/30.
//

#include "broker_ctp.h"

void CtpTradeClient::SetBroker(BrokerCTP *broker) {
    broker_ = broker;
}

// 连接
void CtpTradeClient::Connect(char frontAddress[]) {
    ptr = CThostFtdcTraderApi::CreateFtdcTraderApi(".//ctp_future_td_flow/");//必须提前创建好flow目录
    ptr->RegisterSpi(this);
    ptr->SubscribePublicTopic(THOST_TERT_QUICK);
    ptr->SubscribePrivateTopic(THOST_TERT_QUICK);//设置私有流订阅模式
    ptr->RegisterFront(frontAddress);
    SPDLOG_INFO("注册交易前置机: {} ", frontAddress);
    ptr->Init();
    //输出API版本信息
    SPDLOG_INFO("CTPMini-TdApi版本信息: {}", ptr->GetApiVersion());
}

// 客户端认证请求
int CtpTradeClient::Authenticate(char brokerID[], char userID[], char appID[], char authCode[]) {
    CThostFtdcReqAuthenticateField pReqAuthenticateField{};
    strcpy(pReqAuthenticateField.BrokerID, brokerID);
    strcpy(pReqAuthenticateField.UserID, userID);
    strcpy(pReqAuthenticateField.AppID, appID);
    strcpy(pReqAuthenticateField.AuthCode, authCode);

    SPDLOG_INFO("Authenticate, BrokerID:{}, UserID:{}, appID:{} authCode:{}, requestID:{}", brokerID, userID, appID, authCode, request_id);
    return ptr->ReqAuthenticate(&pReqAuthenticateField, request_id++);
}

//释放
void CtpTradeClient::Release() {
    ptr->Release();
}


//登陆
void CtpTradeClient::Login(char brokerID[], char userID[], char password[]) {
    CThostFtdcReqUserLoginField t{};
    strcpy(t.BrokerID, brokerID);
    strcpy(t.UserID, userID);
    strcpy(t.Password, password);
    SPDLOG_INFO("Login, brokerID:{}, userID:{}, requestID:{}", brokerID, userID, request_id);
    while (ptr->ReqUserLogin(&t, request_id++) != 0) ots::utils::timing_ms(100);
}

//登出
void CtpTradeClient::Logout(char brokerID[], char userID[]) {
    CThostFtdcUserLogoutField t{};
    strcpy(t.BrokerID, brokerID);
    strcpy(t.UserID, userID);
    SPDLOG_INFO("Logout, brokerID:{}, userID:{}, requestID:{}", brokerID, userID, request_id);
    while (ptr->ReqUserLogout(&t, request_id++) != 0) ots::utils::timing_ms(100);
}

//结算单确认
void CtpTradeClient::SettlementInfoConfirm(char brokerID[], char userID[]) {
    CThostFtdcSettlementInfoConfirmField t{};
    strcpy(t.BrokerID, brokerID);
    strcpy(t.InvestorID, userID);
    SPDLOG_INFO("ReqSettlementInfoConfirm, brokerID:{}, userID:{}, requestID:{}", brokerID, userID, request_id);
    while (ptr->ReqSettlementInfoConfirm(&t, request_id++) != 0) ots::utils::timing_ms(100);
    SPDLOG_INFO("设定默认自动确认结算单");
}


void CtpTradeClient::OnFrontConnected() {
    SPDLOG_INFO("交易服务器连接成功");
}

void CtpTradeClient::OnFrontDisconnected(int nReason) {
    SPDLOG_ERROR("交易服务器连接失败: {}", nReason);
}

void CtpTradeClient::OnHeartBeatWarning(int nTimeLapse) {
    SPDLOG_WARN("Warn. No packet received for a period of time. {}", nTimeLapse);
}

//客户端认证响应
void CtpTradeClient::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                                       CThostFtdcRspInfoField *pRspInfo,
                                       int nRequestID, bool bIsLast) {
    SPDLOG_INFO("客户端认证响应, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("认证成功,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    } else {
        SPDLOG_ERROR("认证失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
}


void CtpTradeClient::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID,
                                    bool bIsLast) {

    SPDLOG_INFO("交易账户登录, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("交易账户登录成功");
        SPDLOG_INFO("交易日:{}", pRspUserLogin->TradingDay);
        SPDLOG_INFO("登录时间: {}", pRspUserLogin->LoginTime);
        SPDLOG_INFO("交易帐户: {}", pRspUserLogin->UserID);
    } else {
        SPDLOG_ERROR("交易账户登录失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
}

void CtpTradeClient::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                                     CThostFtdcRspInfoField *pRspInfo,
                                     int nRequestID,
                                     bool bIsLast) {
    SPDLOG_INFO("交易账户登出, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("交易账户退出成功. Broker ID: {}, Investor ID: {}.", pUserLogout->BrokerID, pUserLogout->UserID);
    } else {
        SPDLOG_ERROR("交易账户登出失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
}

// 结算单确认响应
void CtpTradeClient::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                                CThostFtdcRspInfoField *pRspInfo,
                                                int nRequestID,
                                                bool bIsLast) {
    SPDLOG_INFO("结算单确认响应, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("程序自动确认结算单，请通过交易终端核对结算单");
        SPDLOG_INFO("确认日期：{}", pSettlementInfoConfirm->ConfirmDate);
        SPDLOG_INFO("确认时间：{}", pSettlementInfoConfirm->ConfirmTime);
    } else {
        SPDLOG_ERROR("交易账户登出失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
}

// 错误应答
void CtpTradeClient::OnRspError(CThostFtdcRspInfoField *pRspInfo,
                                int nRequestID,
                                bool bIsLast) {
    SPDLOG_ERROR("OnRspError, nRequestID: {},ErrorID={}, ErrMsg={}", nRequestID, pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
}

// 请求查询资金账户
bool CtpTradeClient::QueryAccount(char brokerID[], char InvestorID[]) {
    CThostFtdcQryTradingAccountField t{};
    strcpy(t.BrokerID, brokerID);
    strcpy(t.InvestorID, InvestorID);

    SPDLOG_INFO("QueryAccount, brokerID:{}, userID:{}, requestID:{}", brokerID, InvestorID, request_id);
    if (ptr->ReqQryTradingAccount(&t, request_id++) == 0) {
        SPDLOG_INFO("请求查询资金账户发送成功.");
        return false;
    } else {
        SPDLOG_ERROR("请求查询资金账户发送失败.");
        return true;
    }
}

//请求查询资金账户响应
void CtpTradeClient::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
                                            CThostFtdcRspInfoField *pRspInfo,
                                            int nRequestID,
                                            bool bIsLast) {
    SPDLOG_INFO("请求查询资金账户响应, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("请求查询资金账户响应,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    } else {
        SPDLOG_ERROR("请求查询资金账户响应,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
        return;
    }
    SPDLOG_INFO("资金账户, Account ID: {}, Balance: {:.3f}, Frozen: {:.3f}, Margin: {:.3f}", pTradingAccount->AccountID, pTradingAccount->Balance, pTradingAccount->FrozenCash, pTradingAccount->CurrMargin);

    ots::broker::Account account{};
    strcpy(account.account_id, pTradingAccount->AccountID);
    account.total_asset = pTradingAccount->Balance;
    account.margin = pTradingAccount->CurrMargin;
    account.frozen = pTradingAccount->FrozenCash + pTradingAccount->FrozenMargin + pTradingAccount->FrozenCommission;
    account.cash = account.total_asset - account.margin - account.frozen;
    broker_->OnQueryAccount(account);
}

bool CtpTradeClient::QueryPosition(char *brokerID, char *InvestorID) {
    CThostFtdcQryInvestorPositionField t{};
    strcpy(t.BrokerID, brokerID);
    strcpy(t.InvestorID, InvestorID);

    SPDLOG_INFO("QueryPosition, brokerID:{}, userID:{}, requestID:{}", brokerID, InvestorID, request_id);
    if (ptr->ReqQryInvestorPosition(&t, request_id++) == 0) {
        SPDLOG_INFO("请求查询投资者持仓发送成功.");
        return false;
    } else {
        SPDLOG_ERROR("请求查询投资者持仓发送失败.");
        return true;
    }
}

void CtpTradeClient::OnRspQryInvestorPosition(
        CThostFtdcInvestorPositionField *pInvestorPosition,
        CThostFtdcRspInfoField *pRspInfo,
        int nRequestID,
        bool bIsLast) {
    SPDLOG_INFO("请求查询投资者持仓响应, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("请求查询投资者持仓响应,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    } else {
        SPDLOG_ERROR("请求查询投资者持仓响应,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
        return;
    }
}
