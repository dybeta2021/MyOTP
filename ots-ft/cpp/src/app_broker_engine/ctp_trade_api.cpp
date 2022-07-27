//
// Created by 稻草人 on 2022/6/30.
//
#include "ots/utils/logger.h"
#include "ctp_trade_api.h"
#include "broker_ctp.h"
#include "kftime.h"
#include "magic_enum.hpp"
#include "ots/broker/contract.h"
#include "ots/data.h"
#include "spdlog/spdlog.h"
#include <string>


CtpTradeApi::CtpTradeApi() {
    signal_init_ = new nut::Semaphore(0);
    signal_authenticate_ = new nut::Semaphore(0);
    signal_login_ = new nut::Semaphore(0);
    signal_query_settlement_confirm_ = new nut::Semaphore(0);
    signal_settlement_confirm_ = new nut::Semaphore(0);
    signal_logout_ = new nut::Semaphore(0);
    signal_query_trading_params_ = new nut::Semaphore(0);
    signal_query_account_ = new nut::Semaphore(0);
    signal_query_position_ = new nut::Semaphore(0);
}

CtpTradeApi::~CtpTradeApi() {
    //    ReqUserLogout();
    //    Release();

    delete signal_init_;
    delete signal_authenticate_;
    delete signal_login_;
    delete signal_query_settlement_confirm_;
    delete signal_settlement_confirm_;
    delete signal_logout_;
    delete signal_query_trading_params_;
    delete signal_query_account_;
    delete signal_query_position_;
}

void CtpTradeApi::SetConfig(const ots::data::Config &config) {
    config_ = config;
}


void CtpTradeApi::SetBroker(BrokerCTP *broker) {
    broker_ = broker;
}

// 连接
int CtpTradeApi::Init() {
    if (status_ != -1) {
        SPDLOG_WARN("接口已初始化,-1 {}.", status_);
        return -1;
    }
    ptr = CThostFtdcTraderApi::CreateFtdcTraderApi(".//ctp_future_td_flow/");//必须提前创建好flow目录
    ptr->RegisterSpi(this);

    //CTP公有流和私有流提供三种订阅方式，
    //THOST_TERT_RESTART：从本交易日开始重传。
    //THOST_TERT_RESUME：从上次收到的续传。
    //THOST_TERT_QUICK：只传送登录后的内容。
    ptr->SubscribePublicTopic(THOST_TERT_QUICK);
    ptr->SubscribePrivateTopic(THOST_TERT_QUICK);//设置私有流订阅模式

    ptr->RegisterFront(const_cast<char *>(config_.trade_ip.c_str()));
    ptr->Init();

    SPDLOG_INFO("CTPMini-TdApi版本信息: {}", ptr->GetApiVersion());
    SPDLOG_INFO("TradeIP: {}", config_.trade_ip);
    SPDLOG_INFO("Init.");

    if (signal_init_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        status_.store(-1);
        return -1;
    }
}

// 客户端认证请求
int CtpTradeApi::Authenticate() {
    if (status_ != 0) {
        SPDLOG_ERROR("状态错误: 0 {}.", status_);
        return -1;
    }
    CThostFtdcReqAuthenticateField pReqAuthenticateField{};
    strcpy(pReqAuthenticateField.BrokerID, config_.broker_id.c_str());
    strcpy(pReqAuthenticateField.UserID, config_.account_id.c_str());
    strcpy(pReqAuthenticateField.AppID, config_.app_id.c_str());
    strcpy(pReqAuthenticateField.AuthCode, config_.auth_code.c_str());

    // 终端认证 容易失败！
    int counter = 0;
    while (true) {
        counter++;
        if (counter > 10) {
            SPDLOG_ERROR("终端认证失败，退出程序.");
            return -1;
        }
        int intAuthRet = ptr->ReqAuthenticate(&pReqAuthenticateField, ++request_id);
        SPDLOG_DEBUG("Authenticate, BrokerID:{}, UserID:{}, appID:{} authCode:{}, requestID:{}",
                     config_.broker_id, config_.account_id, config_.app_id, config_.auth_code, request_id);
        timing_ms(500);
        if (intAuthRet == 0) {
            break;
        }
    }

    if (signal_authenticate_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}

//释放
void CtpTradeApi::Release() {
    ptr->Release();
}


//登陆
int CtpTradeApi::Login() {
    if (status_ != 1) {
        SPDLOG_ERROR("状态错误: 1 {}.", status_);
        return -1;
    }
    CThostFtdcReqUserLoginField t{};
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.UserID, config_.account_id.c_str());
    strcpy(t.Password, config_.password.c_str());
    while (ptr->ReqUserLogin(&t, ++request_id) != 0) ots::utils::timing_ms(100);
    SPDLOG_DEBUG("ReqUserLogin, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id, request_id);

    if (signal_login_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}

//登出
int CtpTradeApi::Logout() {
    if (status_ < 2) {
        SPDLOG_ERROR("状态错误: >=2 {}.", status_);
        return -1;
    }
    CThostFtdcUserLogoutField t{};
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.UserID, config_.account_id.c_str());
    while (ptr->ReqUserLogout(&t, ++request_id) != 0) ots::utils::timing_ms(100);
    SPDLOG_DEBUG("ReqUserLogout, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id, request_id);

    if (signal_logout_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}

//结算单查询
int CtpTradeApi::QuerySettlementInfoConfirm() {
    if (status_ != 2) {
        SPDLOG_ERROR("状态错误: =2 {}.", status_);
        return -1;
    }
    CThostFtdcQrySettlementInfoField t{};
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.InvestorID, config_.account_id.c_str());
    while (ptr->ReqQrySettlementInfo(&t, ++request_id) != 0) ots::utils::timing_ms(100);
    SPDLOG_DEBUG("ReqQrySettlementInfo, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id,
                 request_id);
    SPDLOG_INFO("查询结算单");
    if (signal_query_settlement_confirm_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}

//结算单确认
int CtpTradeApi::SettlementInfoConfirm() {
    if (status_ != 2) {
        SPDLOG_ERROR("状态错误: =2 {}.", status_);
        return -1;
    }

    SPDLOG_INFO("确认结算单");
    CThostFtdcSettlementInfoConfirmField t{};
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.InvestorID, config_.account_id.c_str());
    while (ptr->ReqSettlementInfoConfirm(&t, ++request_id) != 0) ots::utils::timing_ms(100);
    SPDLOG_DEBUG("ReqSettlementInfoConfirm, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id,
                 request_id);

    if (signal_settlement_confirm_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}


void CtpTradeApi::OnFrontConnected() {
    SPDLOG_INFO("交易服务器连接成功");
    status_.store(0);
    signal_init_->post();
}

void CtpTradeApi::OnFrontDisconnected(int nReason) {
    // TODO: 这个函数什么时间被调用

    SPDLOG_ERROR("交易服务器连接失败: {}", nReason);
    status_.store(-1);
    //    Init();
    //    Authenticate();
    //    Login();
}

void CtpTradeApi::OnHeartBeatWarning(int nTimeLapse) {
    SPDLOG_WARN("Warn. No packet received for a period of time. {}", nTimeLapse);
}

//客户端认证响应
void CtpTradeApi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID, bool bIsLast) {
    SPDLOG_TRACE("CThostFtdcRspAuthenticateField");
    SPDLOG_TRACE("BrokerID:{}", pRspAuthenticateField->BrokerID);
    SPDLOG_TRACE("UserID:{}", pRspAuthenticateField->UserID);
    SPDLOG_TRACE("UserProductInfo:{}", pRspAuthenticateField->UserProductInfo);
    SPDLOG_TRACE("AppID:{}", pRspAuthenticateField->AppID);
    SPDLOG_TRACE("AppType:{}", pRspAuthenticateField->AppType);
    SPDLOG_TRACE("CThostFtdcRspAuthenticateField");
    SPDLOG_DEBUG("OnRspAuthenticate, nRequestID:{}", nRequestID);

    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        status_.store(1);
        SPDLOG_INFO("认证成功,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    } else {
        SPDLOG_ERROR("认证失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
    signal_authenticate_->post();
}


void CtpTradeApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLoginField,
                                 CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID,
                                 bool bIsLast) {
    SPDLOG_TRACE("CThostFtdcRspUserLoginField");
    SPDLOG_TRACE("TradingDay:{}", pRspUserLoginField->TradingDay);
    SPDLOG_TRACE("LoginTime:{}", pRspUserLoginField->LoginTime);
    SPDLOG_TRACE("BrokerID:{}", pRspUserLoginField->BrokerID);
    SPDLOG_TRACE("UserID:{}", pRspUserLoginField->UserID);
    SPDLOG_TRACE("SystemName:{}", pRspUserLoginField->SystemName);
    SPDLOG_TRACE("FrontID:{}", pRspUserLoginField->FrontID);
    SPDLOG_TRACE("SessionID:{}", pRspUserLoginField->SessionID);
    SPDLOG_TRACE("MaxOrderRef:{}", pRspUserLoginField->MaxOrderRef);
    SPDLOG_TRACE("SHFETime:{}", pRspUserLoginField->SHFETime);
    SPDLOG_TRACE("DCETime:{}", pRspUserLoginField->DCETime);
    SPDLOG_TRACE("CZCETime:{}", pRspUserLoginField->CZCETime);
    SPDLOG_TRACE("FFEXTime:{}", pRspUserLoginField->FFEXTime);
    SPDLOG_TRACE("INETime:{}", pRspUserLoginField->INETime);
    SPDLOG_TRACE("CThostFtdcRspUserLoginField");

    SPDLOG_DEBUG("OnRspUserLogin, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("交易账户登录成功");
        SPDLOG_INFO("交易日:{}", pRspUserLoginField->TradingDay);
        SPDLOG_INFO("登录时间: {}", pRspUserLoginField->LoginTime);
        SPDLOG_INFO("交易帐户: {}", pRspUserLoginField->UserID);
        front_id_ = pRspUserLoginField->FrontID;
        session_id_ = pRspUserLoginField->SessionID;
        status_.store(2);
    } else {
        SPDLOG_ERROR("交易账户登录失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
    signal_login_->post();
}

void CtpTradeApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogoutField,
                                  CThostFtdcRspInfoField *pRspInfo,
                                  int nRequestID,
                                  bool bIsLast) {
    SPDLOG_TRACE("CThostFtdcUserLogoutField");
    SPDLOG_TRACE("BrokerID:{}", pUserLogoutField->BrokerID);
    SPDLOG_TRACE("UserID:{}", pUserLogoutField->UserID);
    SPDLOG_TRACE("CThostFtdcUserLogoutField");

    SPDLOG_INFO("交易账户登出, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("交易账户退出成功. Broker ID: {}, Investor ID: {}.", pUserLogoutField->BrokerID, pUserLogoutField->UserID);
        status_.store(1);
    } else {
        SPDLOG_ERROR("交易账户登出失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
    signal_logout_->post();
}

void CtpTradeApi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirmField,
                                                CThostFtdcRspInfoField *pRspInfo,
                                                int nRequestID,
                                                bool bIsLast) {
    SPDLOG_INFO("查询结算单响应, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_TRACE("CThostFtdcSettlementInfoConfirmField");
        SPDLOG_TRACE("BrokerID:{}", pSettlementInfoConfirmField->BrokerID);
        SPDLOG_TRACE("InvestorID:{}", pSettlementInfoConfirmField->InvestorID);
        SPDLOG_TRACE("ConfirmDate:{}", pSettlementInfoConfirmField->ConfirmDate);
        SPDLOG_TRACE("ConfirmTime:{}", pSettlementInfoConfirmField->ConfirmTime);
        SPDLOG_TRACE("SettlementID:{}", pSettlementInfoConfirmField->SettlementID);
        SPDLOG_TRACE("AccountID:{}", pSettlementInfoConfirmField->AccountID);
        SPDLOG_TRACE("CurrencyID:{}", pSettlementInfoConfirmField->CurrencyID);
        SPDLOG_TRACE("CThostFtdcSettlementInfoConfirmField");
        SPDLOG_TRACE("OnRspQrySettlementInfoConfirm, nRequestID:{}", nRequestID);
    } else {
        SPDLOG_ERROR("查询结算单响应失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
    signal_query_settlement_confirm_->post();
}

// 结算单确认响应
void CtpTradeApi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirmField,
                                             CThostFtdcRspInfoField *pRspInfo,
                                             int nRequestID,
                                             bool bIsLast) {
    SPDLOG_TRACE("CThostFtdcSettlementInfoConfirmField");
    SPDLOG_TRACE("BrokerID:{}", pSettlementInfoConfirmField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pSettlementInfoConfirmField->InvestorID);
    SPDLOG_TRACE("ConfirmDate:{}", pSettlementInfoConfirmField->ConfirmDate);
    SPDLOG_TRACE("ConfirmTime:{}", pSettlementInfoConfirmField->ConfirmTime);
    SPDLOG_TRACE("SettlementID:{}", pSettlementInfoConfirmField->SettlementID);
    SPDLOG_TRACE("AccountID:{}", pSettlementInfoConfirmField->AccountID);
    SPDLOG_TRACE("CurrencyID:{}", pSettlementInfoConfirmField->CurrencyID);
    SPDLOG_TRACE("CThostFtdcSettlementInfoConfirmField");

    SPDLOG_DEBUG("OnRspSettlementInfoConfirm, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_INFO("程序自动确认结算单，请通过交易终端核对结算单");
        SPDLOG_INFO("确认日期：{}", pSettlementInfoConfirmField->ConfirmDate);
        SPDLOG_INFO("确认时间：{}", pSettlementInfoConfirmField->ConfirmTime);
        status_.store(3);
    } else {
        SPDLOG_ERROR("程序自动确认结算单失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
    signal_settlement_confirm_->post();
}

// 错误应答
void CtpTradeApi::OnRspError(CThostFtdcRspInfoField *pRspInfoField,
                             int nRequestID,
                             bool bIsLast) {
    SPDLOG_TRACE("CThostFtdcRspInfoField");
    SPDLOG_TRACE("ErrorID:{}", pRspInfoField->ErrorID);
    SPDLOG_TRACE("ErrorMsg:{}", pRspInfoField->ErrorMsg);
    SPDLOG_TRACE("CThostFtdcRspInfoField");

    SPDLOG_ERROR("OnRspError, nRequestID: {},ErrorID={}, ErrMsg={}", nRequestID, pRspInfoField->ErrorID,
                 ots::utils::gbk2utf8(pRspInfoField->ErrorMsg));
    //TODO:根据nRequestID返回对应的请求函数错误信息
}

// 状态
int CtpTradeApi::GetStatus() {
    if (status_ == 3) {
        return 0;
    } else {
        return -1;
    }
}


// 请求查询资金账户
int CtpTradeApi::QueryAccount() {
    if (status_ != 3) {
        SPDLOG_ERROR("状态错误: 3 {}.", status_);
        return -1;
    }

    CThostFtdcQryTradingAccountField t{};
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.InvestorID, config_.account_id.c_str());

    if (ptr->ReqQryTradingAccount(&t, ++request_id) == 0) {
        SPDLOG_DEBUG("ReqQryTradingAccount, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id,
                     request_id);
        if (signal_query_account_->timedwait(5, 0)) {
            return 0;
        } else {
            SPDLOG_ERROR("Network Error.");
            return -1;
        }
    } else {
        SPDLOG_ERROR("ReqQryTradingAccount, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id,
                     request_id);
        SPDLOG_ERROR("请求查询资金账户发送失败.");
        return -1;
    }
}

//请求查询资金账户响应
void CtpTradeApi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccountField,
                                         CThostFtdcRspInfoField *pRspInfo,
                                         int nRequestID,
                                         bool bIsLast) {
    SPDLOG_TRACE("CThostFtdcTradingAccountField");
    SPDLOG_TRACE("BrokerID:{}", pTradingAccountField->BrokerID);
    SPDLOG_TRACE("AccountID:{}", pTradingAccountField->AccountID);
    SPDLOG_TRACE("PreMortgage:{}", pTradingAccountField->PreMortgage);
    SPDLOG_TRACE("PreCredit:{}", pTradingAccountField->PreCredit);
    SPDLOG_TRACE("PreDeposit:{}", pTradingAccountField->PreDeposit);
    SPDLOG_TRACE("PreBalance:{}", pTradingAccountField->PreBalance);
    SPDLOG_TRACE("PreMargin:{}", pTradingAccountField->PreMargin);
    SPDLOG_TRACE("InterestBase:{}", pTradingAccountField->InterestBase);
    SPDLOG_TRACE("Interest:{}", pTradingAccountField->Interest);
    SPDLOG_TRACE("Deposit:{}", pTradingAccountField->Deposit);
    SPDLOG_TRACE("Withdraw:{}", pTradingAccountField->Withdraw);
    SPDLOG_TRACE("FrozenMargin:{}", pTradingAccountField->FrozenMargin);
    SPDLOG_TRACE("FrozenCash:{}", pTradingAccountField->FrozenCash);
    SPDLOG_TRACE("FrozenCommission:{}", pTradingAccountField->FrozenCommission);
    SPDLOG_TRACE("CurrMargin:{}", pTradingAccountField->CurrMargin);
    SPDLOG_TRACE("CashIn:{}", pTradingAccountField->CashIn);
    SPDLOG_TRACE("Commission:{}", pTradingAccountField->Commission);
    SPDLOG_TRACE("CloseProfit:{}", pTradingAccountField->CloseProfit);
    SPDLOG_TRACE("PositionProfit:{}", pTradingAccountField->PositionProfit);
    SPDLOG_TRACE("Balance:{}", pTradingAccountField->Balance);
    SPDLOG_TRACE("Available:{}", pTradingAccountField->Available);
    SPDLOG_TRACE("WithdrawQuota:{}", pTradingAccountField->WithdrawQuota);
    SPDLOG_TRACE("Reserve:{}", pTradingAccountField->Reserve);
    SPDLOG_TRACE("TradingDay:{}", pTradingAccountField->TradingDay);
    SPDLOG_TRACE("SettlementID:{}", pTradingAccountField->SettlementID);
    SPDLOG_TRACE("Credit:{}", pTradingAccountField->Credit);
    SPDLOG_TRACE("Mortgage:{}", pTradingAccountField->Mortgage);
    SPDLOG_TRACE("ExchangeMargin:{}", pTradingAccountField->ExchangeMargin);
    SPDLOG_TRACE("DeliveryMargin:{}", pTradingAccountField->DeliveryMargin);
    SPDLOG_TRACE("ExchangeDeliveryMargin:{}", pTradingAccountField->ExchangeDeliveryMargin);
    SPDLOG_TRACE("ReserveBalance:{}", pTradingAccountField->ReserveBalance);
    SPDLOG_TRACE("CurrencyID:{}", pTradingAccountField->CurrencyID);
    SPDLOG_TRACE("PreFundMortgageIn:{}", pTradingAccountField->PreFundMortgageIn);
    SPDLOG_TRACE("PreFundMortgageOut:{}", pTradingAccountField->PreFundMortgageOut);
    SPDLOG_TRACE("FundMortgageIn:{}", pTradingAccountField->FundMortgageIn);
    SPDLOG_TRACE("FundMortgageOut:{}", pTradingAccountField->FundMortgageOut);
    SPDLOG_TRACE("FundMortgageAvailable:{}", pTradingAccountField->FundMortgageAvailable);
    SPDLOG_TRACE("MortgageableFund:{}", pTradingAccountField->MortgageableFund);
    SPDLOG_TRACE("SpecProductMargin:{}", pTradingAccountField->SpecProductMargin);
    SPDLOG_TRACE("SpecProductFrozenMargin:{}", pTradingAccountField->SpecProductFrozenMargin);
    SPDLOG_TRACE("SpecProductCommission:{}", pTradingAccountField->SpecProductCommission);
    SPDLOG_TRACE("SpecProductFrozenCommission:{}", pTradingAccountField->SpecProductFrozenCommission);
    SPDLOG_TRACE("SpecProductPositionProfit:{}", pTradingAccountField->SpecProductPositionProfit);
    SPDLOG_TRACE("SpecProductCloseProfit:{}", pTradingAccountField->SpecProductCloseProfit);
    SPDLOG_TRACE("SpecProductPositionProfitByAlg:{}", pTradingAccountField->SpecProductPositionProfitByAlg);
    SPDLOG_TRACE("SpecProductExchangeMargin:{}", pTradingAccountField->SpecProductExchangeMargin);
    SPDLOG_TRACE("BizType:{}", pTradingAccountField->BizType);
    SPDLOG_TRACE("FrozenSwap:{}", pTradingAccountField->FrozenSwap);
    SPDLOG_TRACE("RemainSwap:{}", pTradingAccountField->RemainSwap);
    SPDLOG_TRACE("CThostFtdcTradingAccountField");

    SPDLOG_DEBUG("OnRspQryTradingAccount, nRequestID:{}", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        ots::data::Account account{};
        account.update_time = kungfu::yijinjing::time::now_in_nano();
        strcpy(account.update_msg, "query");
        strcpy(account.account_id, pTradingAccountField->AccountID);
        account.pre_balance = pTradingAccountField->PreBalance;
        account.balance = pTradingAccountField->Balance;
        account.deposit = pTradingAccountField->Deposit;
        account.withdraw = pTradingAccountField->Withdraw;
        account.available_cash = pTradingAccountField->Available;
        account.frozen_cash = pTradingAccountField->FrozenCash + pTradingAccountField->FrozenCommission +
                              pTradingAccountField->FrozenMargin;
        account.margin = pTradingAccountField->CurrMargin;
        account.frozen_margin = pTradingAccountField->FrozenMargin;
        account.close_profit = pTradingAccountField->CloseProfit;
        account.position_profit = pTradingAccountField->PositionProfit;
        account.commission = pTradingAccountField->Commission;
        account.frozen_commission = pTradingAccountField->FrozenCommission;
        strcpy(account.update_msg, "Query");
        broker_->OnQueryAccount(account);
    } else {
        SPDLOG_ERROR("请求查询资金账户响应,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
    signal_query_account_->post();
}

int CtpTradeApi::QueryPosition() {
    if (status_ != 3) {
        SPDLOG_ERROR("状态错误: 3 {}.", status_);
        return -1;
    }

    CThostFtdcQryInvestorPositionField t{};
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.InvestorID, config_.account_id.c_str());

    if (ptr->ReqQryInvestorPosition(&t, ++request_id) == 0) {
        SPDLOG_DEBUG("ReqQryInvestorPosition, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id,
                     request_id);
        if (signal_query_position_->timedwait(5, 0)) {
            return 0;
        } else {
            SPDLOG_ERROR("Network Error.");
            return -1;
        }
    } else {
        SPDLOG_ERROR("请求查询投资者持仓发送失败.");
        return -1;
    }
}

void CtpTradeApi::OnRspQryInvestorPosition(
        CThostFtdcInvestorPositionField *pInvestorPositionField,
        CThostFtdcRspInfoField *pRspInfo,
        int nRequestID,
        bool bIsLast) {
    SPDLOG_TRACE("OnRspQryInvestorPosition");
    SPDLOG_TRACE("CThostFtdcInvestorPositionField");
    SPDLOG_TRACE("BrokerID:{}", pInvestorPositionField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pInvestorPositionField->InvestorID);
    SPDLOG_TRACE("PosiDirection:{}", pInvestorPositionField->PosiDirection);
    SPDLOG_TRACE("HedgeFlag:{}", pInvestorPositionField->HedgeFlag);
    SPDLOG_TRACE("PositionDate:{}", pInvestorPositionField->PositionDate);
    SPDLOG_TRACE("YdPosition:{}", pInvestorPositionField->YdPosition);
    SPDLOG_TRACE("Position:{}", pInvestorPositionField->Position);
    SPDLOG_TRACE("LongFrozen:{}", pInvestorPositionField->LongFrozen);
    SPDLOG_TRACE("ShortFrozen:{}", pInvestorPositionField->ShortFrozen);
    SPDLOG_TRACE("LongFrozenAmount:{}", pInvestorPositionField->LongFrozenAmount);
    SPDLOG_TRACE("ShortFrozenAmount:{}", pInvestorPositionField->ShortFrozenAmount);
    SPDLOG_TRACE("OpenVolume:{}", pInvestorPositionField->OpenVolume);
    SPDLOG_TRACE("CloseVolume:{}", pInvestorPositionField->CloseVolume);
    SPDLOG_TRACE("OpenAmount:{}", pInvestorPositionField->OpenAmount);
    SPDLOG_TRACE("CloseAmount:{}", pInvestorPositionField->CloseAmount);
    SPDLOG_TRACE("PositionCost:{}", pInvestorPositionField->PositionCost);
    SPDLOG_TRACE("PreMargin:{}", pInvestorPositionField->PreMargin);
    SPDLOG_TRACE("UseMargin:{}", pInvestorPositionField->UseMargin);
    SPDLOG_TRACE("FrozenMargin:{}", pInvestorPositionField->FrozenMargin);
    SPDLOG_TRACE("FrozenCash:{}", pInvestorPositionField->FrozenCash);
    SPDLOG_TRACE("FrozenCommission:{}", pInvestorPositionField->FrozenCommission);
    SPDLOG_TRACE("CashIn:{}", pInvestorPositionField->CashIn);
    SPDLOG_TRACE("Commission:{}", pInvestorPositionField->Commission);
    SPDLOG_TRACE("CloseProfit:{}", pInvestorPositionField->CloseProfit);
    SPDLOG_TRACE("PositionProfit:{}", pInvestorPositionField->PositionProfit);
    SPDLOG_TRACE("PreSettlementPrice:{}", pInvestorPositionField->PreSettlementPrice);
    SPDLOG_TRACE("SettlementPrice:{}", pInvestorPositionField->SettlementPrice);
    SPDLOG_TRACE("TradingDay:{}", pInvestorPositionField->TradingDay);
    SPDLOG_TRACE("SettlementID:{}", pInvestorPositionField->SettlementID);
    SPDLOG_TRACE("OpenCost:{}", pInvestorPositionField->OpenCost);
    SPDLOG_TRACE("ExchangeMargin:{}", pInvestorPositionField->ExchangeMargin);
    SPDLOG_TRACE("CombPosition:{}", pInvestorPositionField->CombPosition);
    SPDLOG_TRACE("CombLongFrozen:{}", pInvestorPositionField->CombLongFrozen);
    SPDLOG_TRACE("CombShortFrozen:{}", pInvestorPositionField->CombShortFrozen);
    SPDLOG_TRACE("CloseProfitByDate:{}", pInvestorPositionField->CloseProfitByDate);
    SPDLOG_TRACE("CloseProfitByTrade:{}", pInvestorPositionField->CloseProfitByTrade);
    SPDLOG_TRACE("TodayPosition:{}", pInvestorPositionField->TodayPosition);
    SPDLOG_TRACE("MarginRateByMoney:{}", pInvestorPositionField->MarginRateByMoney);
    SPDLOG_TRACE("MarginRateByVolume:{}", pInvestorPositionField->MarginRateByVolume);
    SPDLOG_TRACE("StrikeFrozen:{}", pInvestorPositionField->StrikeFrozen);
    SPDLOG_TRACE("StrikeFrozenAmount:{}", pInvestorPositionField->StrikeFrozenAmount);
    SPDLOG_TRACE("AbandonFrozen:{}", pInvestorPositionField->AbandonFrozen);
    SPDLOG_TRACE("ExchangeID:{}", pInvestorPositionField->ExchangeID);
    SPDLOG_TRACE("YdStrikeFrozen:{}", pInvestorPositionField->YdStrikeFrozen);
    SPDLOG_TRACE("InvestUnitID:{}", pInvestorPositionField->InvestUnitID);
    SPDLOG_TRACE("PositionCostOffset:{}", pInvestorPositionField->PositionCostOffset);
    SPDLOG_TRACE("TasPosition:{}", pInvestorPositionField->TasPosition);
    SPDLOG_TRACE("TasPositionCost:{}", pInvestorPositionField->TasPositionCost);
    SPDLOG_TRACE("InstrumentID:{}", pInvestorPositionField->InstrumentID);
    SPDLOG_TRACE("CThostFtdcInvestorPositionField");

    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_DEBUG("请求查询投资者持仓响应, nRequestID:{}", nRequestID);
        ots::data::Position position{};
        strcpy(position.symbol, pInvestorPositionField->InstrumentID);
        strcpy(position.account_id, pInvestorPositionField->InvestorID);
        if (pInvestorPositionField->PosiDirection == THOST_FTDC_PD_Long) {
            position.direction = ots::data::Direction::Long;
            position.frozen_holding = pInvestorPositionField->LongFrozen;
        } else {
            position.direction = ots::data::Direction::Short;
            position.frozen_holding = pInvestorPositionField->ShortFrozen;
        }
        position.holding = pInvestorPositionField->Position;
        position.today_holding = pInvestorPositionField->TodayPosition;
        // 上期所
        if (strcmp(pInvestorPositionField->ExchangeID, ots::data::exchange::SHFE) == 0) {
            if (pInvestorPositionField->YdPosition > 0 && pInvestorPositionField->TodayPosition <= 0) {
                position.yesterday_holding = pInvestorPositionField->Position;
            }
        }
        // 上海能源中心
        else if (strcmp(pInvestorPositionField->ExchangeID, ots::data::exchange::INE) == 0) {
            if (pInvestorPositionField->YdPosition > 0 && pInvestorPositionField->TodayPosition <= 0) {
                position.yesterday_holding = pInvestorPositionField->Position;
            }
        } else {
            position.yesterday_holding = pInvestorPositionField->Position - pInvestorPositionField->TodayPosition;
        }
        position.frozen_margin = pInvestorPositionField->FrozenMargin;
        position.margin = pInvestorPositionField->UseMargin;
        position.settlement_price = pInvestorPositionField->SettlementPrice;
        position.pre_settlement_price = pInvestorPositionField->PreSettlementPrice;

        auto contract_multiple = ots::broker::ContractTable::get_contract(pInvestorPositionField->InstrumentID).contract_multiple;
        if (position.holding > 0) {
            //todo:搞清楚PositionCost这个字段是正是负
            position.average_price = -1 * pInvestorPositionField->PositionCost / (double) (position.holding * contract_multiple);
        } else {
            position.average_price = 0.;
        }
        position.position_profit = pInvestorPositionField->PositionProfit;
        position.close_profit = pInvestorPositionField->CloseProfit;
        position.commission = pInvestorPositionField->Commission;
        position.frozen_commission = pInvestorPositionField->FrozenCommission;
        position.update_time = kungfu::yijinjing::time::now_in_nano();
        strcpy(position.update_msg, "Query");
        broker_->OnQueryPosition(position);
    } else {
        SPDLOG_ERROR("OnRspQryInvestorPosition, nRequestID:{}, ErrorID={}, ErrMsg={}", nRequestID, pRspInfo->ErrorID,
                     ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
        signal_query_position_->post();
        return;
    }

    if (bIsLast) {
        broker_->ShowPosition();
        signal_query_position_->post();
    }
}


int CtpTradeApi::InsertOrder(CThostFtdcInputOrderField &t) {
    using namespace ots::data;
    t.RequestID = ++request_id;
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.InvestorID, config_.account_id.c_str());
    strcpy(t.UserID, config_.account_id.c_str());

    auto ret = ptr->ReqOrderInsert(&t, request_id);
    return ret;
}


void CtpTradeApi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrderField, CThostFtdcRspInfoField *pRspInfo,
                                   int nRequestID, bool bIsLast) {
    SPDLOG_TRACE("OnRspOrderInsert");
    SPDLOG_TRACE("CThostFtdcInputOrderField");
    SPDLOG_TRACE("BrokerID:{}", pInputOrderField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pInputOrderField->InvestorID);
    SPDLOG_TRACE("reserve1:{}", pInputOrderField->reserve1);
    SPDLOG_TRACE("OrderRef:{}", pInputOrderField->OrderRef);
    SPDLOG_TRACE("UserID:{}", pInputOrderField->UserID);
    SPDLOG_TRACE("OrderPriceType:{}", pInputOrderField->OrderPriceType);
    SPDLOG_TRACE("Direction:{}", pInputOrderField->Direction);
    SPDLOG_TRACE("CombOffsetFlag:{}", pInputOrderField->CombOffsetFlag);
    SPDLOG_TRACE("CombHedgeFlag:{}", pInputOrderField->CombHedgeFlag);
    SPDLOG_TRACE("LimitPrice:{}", pInputOrderField->LimitPrice);
    SPDLOG_TRACE("VolumeTotalOriginal:{}", pInputOrderField->VolumeTotalOriginal);
    SPDLOG_TRACE("TimeCondition:{}", pInputOrderField->TimeCondition);
    SPDLOG_TRACE("GTDDate:{}", pInputOrderField->GTDDate);
    SPDLOG_TRACE("VolumeCondition:{}", pInputOrderField->VolumeCondition);
    SPDLOG_TRACE("MinVolume:{}", pInputOrderField->MinVolume);
    SPDLOG_TRACE("ContingentCondition:{}", pInputOrderField->ContingentCondition);
    SPDLOG_TRACE("StopPrice:{}", pInputOrderField->StopPrice);
    SPDLOG_TRACE("ForceCloseReason:{}", pInputOrderField->ForceCloseReason);
    SPDLOG_TRACE("IsAutoSuspend:{}", pInputOrderField->IsAutoSuspend);
    SPDLOG_TRACE("BusinessUnit:{}", pInputOrderField->BusinessUnit);
    SPDLOG_TRACE("RequestID:{}", pInputOrderField->RequestID);
    SPDLOG_TRACE("UserForceClose:{}", pInputOrderField->UserForceClose);
    SPDLOG_TRACE("IsSwapOrder:{}", pInputOrderField->IsSwapOrder);
    SPDLOG_TRACE("ExchangeID:{}", pInputOrderField->ExchangeID);
    SPDLOG_TRACE("InvestUnitID:{}", pInputOrderField->InvestUnitID);
    SPDLOG_TRACE("AccountID:{}", pInputOrderField->AccountID);
    SPDLOG_TRACE("CurrencyID:{}", pInputOrderField->CurrencyID);
    SPDLOG_TRACE("ClientID:{}", pInputOrderField->ClientID);
    SPDLOG_TRACE("reserve2:{}", pInputOrderField->reserve2);
    SPDLOG_TRACE("MacAddress:{}", pInputOrderField->MacAddress);
    SPDLOG_TRACE("InstrumentID:{}", pInputOrderField->InstrumentID);
    SPDLOG_TRACE("IPAddress:{}", pInputOrderField->IPAddress);
    SPDLOG_TRACE("CThostFtdcInputOrderField\n");

    SPDLOG_WARN("OnRspOrderInsert, nRequestID={}, ErrorID={}, ErrMsg={}.", nRequestID, pRspInfo->ErrorID,
                ots::utils::gbk2utf8(pRspInfo->ErrorMsg));

    // 拒单
    using ots::data::OrderRejected;
    OrderRejected rejected{};
    rejected.order_ref_num = std::stoi(pInputOrderField->OrderRef);
    rejected.update_time = kungfu::yijinjing::time::now_in_nano();
    rejected.status = ots::data::OrderStatus::Rejected;
    strcpy(rejected.status_msg, ots::utils::gbk2utf8(pRspInfo->ErrorMsg).c_str());
    broker_->OnOrderRejected(rejected);
}

void CtpTradeApi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrderField, CThostFtdcRspInfoField *pRspInfo) {
    SPDLOG_TRACE("OnErrRtnOrderInsert");
    SPDLOG_TRACE("CThostFtdcInputOrderField");
    SPDLOG_TRACE("BrokerID:{}", pInputOrderField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pInputOrderField->InvestorID);
    SPDLOG_TRACE("reserve1:{}", pInputOrderField->reserve1);
    SPDLOG_TRACE("OrderRef:{}", pInputOrderField->OrderRef);
    SPDLOG_TRACE("UserID:{}", pInputOrderField->UserID);
    SPDLOG_TRACE("OrderPriceType:{}", pInputOrderField->OrderPriceType);
    SPDLOG_TRACE("Direction:{}", pInputOrderField->Direction);
    SPDLOG_TRACE("CombOffsetFlag:{}", pInputOrderField->CombOffsetFlag);
    SPDLOG_TRACE("CombHedgeFlag:{}", pInputOrderField->CombHedgeFlag);
    SPDLOG_TRACE("LimitPrice:{}", pInputOrderField->LimitPrice);
    SPDLOG_TRACE("VolumeTotalOriginal:{}", pInputOrderField->VolumeTotalOriginal);
    SPDLOG_TRACE("TimeCondition:{}", pInputOrderField->TimeCondition);
    SPDLOG_TRACE("GTDDate:{}", pInputOrderField->GTDDate);
    SPDLOG_TRACE("VolumeCondition:{}", pInputOrderField->VolumeCondition);
    SPDLOG_TRACE("MinVolume:{}", pInputOrderField->MinVolume);
    SPDLOG_TRACE("ContingentCondition:{}", pInputOrderField->ContingentCondition);
    SPDLOG_TRACE("StopPrice:{}", pInputOrderField->StopPrice);
    SPDLOG_TRACE("ForceCloseReason:{}", pInputOrderField->ForceCloseReason);
    SPDLOG_TRACE("IsAutoSuspend:{}", pInputOrderField->IsAutoSuspend);
    SPDLOG_TRACE("BusinessUnit:{}", pInputOrderField->BusinessUnit);
    SPDLOG_TRACE("RequestID:{}", pInputOrderField->RequestID);
    SPDLOG_TRACE("UserForceClose:{}", pInputOrderField->UserForceClose);
    SPDLOG_TRACE("IsSwapOrder:{}", pInputOrderField->IsSwapOrder);
    SPDLOG_TRACE("ExchangeID:{}", pInputOrderField->ExchangeID);
    SPDLOG_TRACE("InvestUnitID:{}", pInputOrderField->InvestUnitID);
    SPDLOG_TRACE("AccountID:{}", pInputOrderField->AccountID);
    SPDLOG_TRACE("CurrencyID:{}", pInputOrderField->CurrencyID);
    SPDLOG_TRACE("ClientID:{}", pInputOrderField->ClientID);
    SPDLOG_TRACE("reserve2:{}", pInputOrderField->reserve2);
    SPDLOG_TRACE("MacAddress:{}", pInputOrderField->MacAddress);
    SPDLOG_TRACE("InstrumentID:{}", pInputOrderField->InstrumentID);
    SPDLOG_TRACE("IPAddress:{}", pInputOrderField->IPAddress);
    SPDLOG_TRACE("CThostFtdcInputOrderField\n");

    //TODO:记录报单数据
    SPDLOG_WARN("OnErrRtnOrderInsert, ErrorID={}, ErrMsg={}.", pRspInfo->ErrorID,
                ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    // 拒单
    using ots::data::OrderRejected;
    OrderRejected rejected{};
    rejected.order_ref_num = std::stoi(pInputOrderField->OrderRef);
    rejected.update_time = kungfu::yijinjing::time::now_in_nano();
    rejected.status = ots::data::OrderStatus::Rejected;
    strcpy(rejected.status_msg, ots::utils::gbk2utf8(pRspInfo->ErrorMsg).c_str());
    broker_->OnOrderRejected(rejected);
}

//todo: 下面两个字段如何处理
//部分成交不在队列中
//#define THOST_FTDC_OST_PartTradedNotQueueing '2'
//未成交还在队列中
//#define THOST_FTDC_OST_NoTradeQueueing '3'
// https://www.cnblogs.com/leijiangtao/p/5379133.html
void CtpTradeApi::OnRtnOrder(CThostFtdcOrderField *pOrderField) {
    SPDLOG_TRACE("OnRtnOrder");
    SPDLOG_TRACE("CThostFtdcOrderField");
    SPDLOG_TRACE("BrokerID:{}", pOrderField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pOrderField->InvestorID);
    SPDLOG_TRACE("reserve1:{}", pOrderField->reserve1);
    SPDLOG_TRACE("OrderRef:{}", pOrderField->OrderRef);
    SPDLOG_TRACE("UserID:{}", pOrderField->UserID);
    SPDLOG_TRACE("OrderPriceType:{}", pOrderField->OrderPriceType);
    SPDLOG_TRACE("Direction:{}", pOrderField->Direction);
    SPDLOG_TRACE("CombOffsetFlag:{}", pOrderField->CombOffsetFlag);
    SPDLOG_TRACE("CombHedgeFlag:{}", pOrderField->CombHedgeFlag);
    SPDLOG_TRACE("LimitPrice:{}", pOrderField->LimitPrice);
    SPDLOG_TRACE("VolumeTotalOriginal:{}", pOrderField->VolumeTotalOriginal);
    SPDLOG_TRACE("TimeCondition:{}", pOrderField->TimeCondition);
    SPDLOG_TRACE("GTDDate:{}", pOrderField->GTDDate);
    SPDLOG_TRACE("VolumeCondition:{}", pOrderField->VolumeCondition);
    SPDLOG_TRACE("MinVolume:{}", pOrderField->MinVolume);
    SPDLOG_TRACE("ContingentCondition:{}", pOrderField->ContingentCondition);
    SPDLOG_TRACE("StopPrice:{}", pOrderField->StopPrice);
    SPDLOG_TRACE("ForceCloseReason:{}", pOrderField->ForceCloseReason);
    SPDLOG_TRACE("IsAutoSuspend:{}", pOrderField->IsAutoSuspend);
    SPDLOG_TRACE("BusinessUnit:{}", pOrderField->BusinessUnit);
    SPDLOG_TRACE("RequestID:{}", pOrderField->RequestID);
    SPDLOG_TRACE("OrderLocalID:{}", pOrderField->OrderLocalID);
    SPDLOG_TRACE("ExchangeID:{}", pOrderField->ExchangeID);
    SPDLOG_TRACE("ParticipantID:{}", pOrderField->ParticipantID);
    SPDLOG_TRACE("ClientID:{}", pOrderField->ClientID);
    SPDLOG_TRACE("reserve2:{}", pOrderField->reserve2);
    SPDLOG_TRACE("TraderID:{}", pOrderField->TraderID);
    SPDLOG_TRACE("InstallID:{}", pOrderField->InstallID);
    SPDLOG_TRACE("OrderSubmitStatus:{}", pOrderField->OrderSubmitStatus);
    SPDLOG_TRACE("NotifySequence:{}", pOrderField->NotifySequence);
    SPDLOG_TRACE("TradingDay:{}", pOrderField->TradingDay);
    SPDLOG_TRACE("SettlementID:{}", pOrderField->SettlementID);
    SPDLOG_TRACE("OrderSysID:{}", pOrderField->OrderSysID);
    SPDLOG_TRACE("OrderSource:{}", pOrderField->OrderSource);
    SPDLOG_TRACE("OrderStatus:{}", pOrderField->OrderStatus);
    SPDLOG_TRACE("OrderType:{}", pOrderField->OrderType);
    SPDLOG_TRACE("VolumeTraded:{}", pOrderField->VolumeTraded);
    SPDLOG_TRACE("VolumeTotal:{}", pOrderField->VolumeTotal);
    SPDLOG_TRACE("InsertDate:{}", pOrderField->InsertDate);
    SPDLOG_TRACE("InsertTime:{}", pOrderField->InsertTime);
    SPDLOG_TRACE("ActiveTime:{}", pOrderField->ActiveTime);
    SPDLOG_TRACE("SuspendTime:{}", pOrderField->SuspendTime);
    SPDLOG_TRACE("UpdateTime:{}", pOrderField->UpdateTime);
    SPDLOG_TRACE("CancelTime:{}", pOrderField->CancelTime);
    SPDLOG_TRACE("ActiveTraderID:{}", pOrderField->ActiveTraderID);
    SPDLOG_TRACE("ClearingPartID:{}", pOrderField->ClearingPartID);
    SPDLOG_TRACE("SequenceNo:{}", pOrderField->SequenceNo);
    SPDLOG_TRACE("FrontID:{}", pOrderField->FrontID);
    SPDLOG_TRACE("SessionID:{}", pOrderField->SessionID);
    SPDLOG_TRACE("UserProductInfo:{}", pOrderField->UserProductInfo);
    SPDLOG_TRACE("StatusMsg:{}", ots::utils::gbk2utf8(pOrderField->StatusMsg));
    SPDLOG_TRACE("UserForceClose:{}", pOrderField->UserForceClose);
    SPDLOG_TRACE("ActiveUserID:{}", pOrderField->ActiveUserID);
    SPDLOG_TRACE("BrokerOrderSeq:{}", pOrderField->BrokerOrderSeq);
    SPDLOG_TRACE("RelativeOrderSysID:{}", pOrderField->RelativeOrderSysID);
    SPDLOG_TRACE("ZCETotalTradedVolume:{}", pOrderField->ZCETotalTradedVolume);
    SPDLOG_TRACE("IsSwapOrder:{}", pOrderField->IsSwapOrder);
    SPDLOG_TRACE("BranchID:{}", pOrderField->BranchID);
    SPDLOG_TRACE("InvestUnitID:{}", pOrderField->InvestUnitID);
    SPDLOG_TRACE("AccountID:{}", pOrderField->AccountID);
    SPDLOG_TRACE("CurrencyID:{}", pOrderField->CurrencyID);
    SPDLOG_TRACE("reserve3:{}", pOrderField->reserve3);
    SPDLOG_TRACE("MacAddress:{}", pOrderField->MacAddress);
    SPDLOG_TRACE("InstrumentID:{}", pOrderField->InstrumentID);
    SPDLOG_TRACE("ExchangeInstID:{}", pOrderField->ExchangeInstID);
    SPDLOG_TRACE("IPAddress:{}", pOrderField->IPAddress);
    SPDLOG_TRACE("CThostFtdcOrderField\n");

    using ots::data::Order;
    using ots::data::OrderEntrust;
    OrderEntrust entrust{};
    entrust.order_ref_num = std::stoi(pOrderField->OrderRef);
    entrust.update_time = kungfu::yijinjing::time::now_in_nano();
    strcpy(entrust.status_msg, ots::utils::gbk2utf8(pOrderField->StatusMsg).c_str());

    // 报单 已受理
    if (pOrderField->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && pOrderField->OrderStatus == THOST_FTDC_OST_Unknown) {
        entrust.status = ots::data::OrderStatus::Submitted;
        entrust.traded_volume = 0;
        entrust.left_volume = pOrderField->VolumeTotal;
        entrust.cancel_volume = 0;
    }
    // 已报入
    else if (pOrderField->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && pOrderField->OrderStatus == THOST_FTDC_OST_NoTradeQueueing) {
        entrust.status = ots::data::OrderStatus::Accepted;
        entrust.traded_volume = 0;
        entrust.left_volume = pOrderField->VolumeTotal;
        entrust.cancel_volume = 0;
    }
    // 全部成交
    else if (pOrderField->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && pOrderField->OrderStatus == THOST_FTDC_OST_AllTraded) {
        entrust.status = ots::data::OrderStatus::Filled;
        entrust.traded_volume = pOrderField->VolumeTraded;
        entrust.left_volume = pOrderField->VolumeTotal;
        entrust.cancel_volume = 0;
    }
    // 部分成交
    else if (pOrderField->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && pOrderField->OrderStatus == THOST_FTDC_OST_PartTradedQueueing) {
        entrust.status = ots::data::OrderStatus::PartialFilledActive;
        entrust.traded_volume = pOrderField->VolumeTraded;
        entrust.left_volume = pOrderField->VolumeTotal;
        entrust.cancel_volume = 0;
    }
    // 全部撤单
    else if (pOrderField->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && pOrderField->OrderStatus == THOST_FTDC_OST_Canceled) {
        entrust.status = ots::data::OrderStatus::Cancelled;
        entrust.traded_volume = pOrderField->VolumeTraded;
        entrust.left_volume = 0;
        entrust.cancel_volume = pOrderField->VolumeTotal;
    }
    //todo:部成部撤
    else if (pOrderField->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted && pOrderField->OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing) {
        entrust.status = ots::data::OrderStatus::Cancelled;
        entrust.traded_volume = pOrderField->VolumeTraded;
        entrust.left_volume = 0;
        entrust.cancel_volume = pOrderField->VolumeTotal;
    } else {
        SPDLOG_ERROR("OrderSubmitStatus:{}, OrderStatus:{}", pOrderField->OrderSubmitStatus, pOrderField->OrderStatus);
    }

    broker_->OnOrderEntrust(entrust);
}

void CtpTradeApi::OnRtnTrade(CThostFtdcTradeField *pTradeField) {
    SPDLOG_TRACE("OnRtnTrade");
    SPDLOG_TRACE("CThostFtdcTradeField");
    SPDLOG_TRACE("BrokerID:{}", pTradeField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pTradeField->InvestorID);
    SPDLOG_TRACE("reserve1:{}", pTradeField->reserve1);
    SPDLOG_TRACE("OrderRef:{}", pTradeField->OrderRef);
    SPDLOG_TRACE("UserID:{}", pTradeField->UserID);
    SPDLOG_TRACE("ExchangeID:{}", pTradeField->ExchangeID);
    SPDLOG_TRACE("TradeID:{}", pTradeField->TradeID);
    SPDLOG_TRACE("Direction:{}", pTradeField->Direction);
    SPDLOG_TRACE("OrderSysID:{}", pTradeField->OrderSysID);
    SPDLOG_TRACE("ParticipantID:{}", pTradeField->ParticipantID);
    SPDLOG_TRACE("ClientID:{}", pTradeField->ClientID);
    SPDLOG_TRACE("TradingRole:{}", pTradeField->TradingRole);
    SPDLOG_TRACE("reserve2:{}", pTradeField->reserve2);
    SPDLOG_TRACE("OffsetFlag:{}", pTradeField->OffsetFlag);
    SPDLOG_TRACE("HedgeFlag:{}", pTradeField->HedgeFlag);
    SPDLOG_TRACE("Price:{}", pTradeField->Price);
    SPDLOG_TRACE("Volume:{}", pTradeField->Volume);
    SPDLOG_TRACE("TradeDate:{}", pTradeField->TradeDate);
    SPDLOG_TRACE("TradeTime:{}", pTradeField->TradeTime);
    SPDLOG_TRACE("TradeType:{}", pTradeField->TradeType);
    SPDLOG_TRACE("PriceSource:{}", pTradeField->PriceSource);
    SPDLOG_TRACE("TraderID:{}", pTradeField->TraderID);
    SPDLOG_TRACE("OrderLocalID:{}", pTradeField->OrderLocalID);
    SPDLOG_TRACE("ClearingPartID:{}", pTradeField->ClearingPartID);
    SPDLOG_TRACE("BusinessUnit:{}", pTradeField->BusinessUnit);
    SPDLOG_TRACE("SequenceNo:{}", pTradeField->SequenceNo);
    SPDLOG_TRACE("TradingDay:{}", pTradeField->TradingDay);
    SPDLOG_TRACE("SettlementID:{}", pTradeField->SettlementID);
    SPDLOG_TRACE("BrokerOrderSeq:{}", pTradeField->BrokerOrderSeq);
    SPDLOG_TRACE("TradeSource:{}", pTradeField->TradeSource);
    SPDLOG_TRACE("InvestUnitID:{}", pTradeField->InvestUnitID);
    SPDLOG_TRACE("InstrumentID:{}", pTradeField->InstrumentID);
    SPDLOG_TRACE("ExchangeInstID:{}", pTradeField->ExchangeInstID);
    SPDLOG_TRACE("CThostFtdcTradeField\n");

    ots::data::OrderTransaction transaction{};
    transaction.order_ref_num = std::stoi(pTradeField->OrderRef);
    strcpy(transaction.exchange_id, pTradeField->ExchangeID);
    strcpy(transaction.account_id, pTradeField->InvestorID);
    strcpy(transaction.symbol, pTradeField->InstrumentID);

    if (pTradeField->Direction == THOST_FTDC_D_Buy) {
        transaction.direction = ots::data::Direction::Long;
    } else {
        transaction.direction = ots::data::Direction::Short;
    }

    if (pTradeField->OffsetFlag == THOST_FTDC_OF_Open) {
        transaction.offset = ots::data::Offset::Open;
    } else if (pTradeField->OffsetFlag == THOST_FTDC_OF_Close) {
        transaction.offset = ots::data::Offset::Close;
    } else if (pTradeField->OffsetFlag == THOST_FTDC_OF_CloseToday) {
        transaction.offset = ots::data::Offset::CloseToday;
    } else if (pTradeField->OffsetFlag == THOST_FTDC_OF_CloseYesterday) {
        transaction.offset = ots::data::Offset::CloseYesterday;
    } else {
        SPDLOG_ERROR("Error OffsetFlag: {}.", pTradeField->OffsetFlag);
    }

    transaction.update_time = kungfu::yijinjing::time::now_in_nano();
    transaction.traded_volume = pTradeField->Volume;
    transaction.traded_price = pTradeField->Price;
    broker_->OnOrderTrade(transaction);
}

void CtpTradeApi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderActionField, CThostFtdcRspInfoField *pRspInfo,
                                   int nRequestID, bool bIsLast) {
    SPDLOG_TRACE("OnRspOrderAction");
    SPDLOG_TRACE("CThostFtdcInputOrderActionField");
    SPDLOG_TRACE("BrokerID:{}", pInputOrderActionField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pInputOrderActionField->InvestorID);
    SPDLOG_TRACE("OrderActionRef:{}", pInputOrderActionField->OrderActionRef);
    SPDLOG_TRACE("OrderRef:{}", pInputOrderActionField->OrderRef);
    SPDLOG_TRACE("RequestID:{}", pInputOrderActionField->RequestID);
    SPDLOG_TRACE("FrontID:{}", pInputOrderActionField->FrontID);
    SPDLOG_TRACE("SessionID:{}", pInputOrderActionField->SessionID);
    SPDLOG_TRACE("ExchangeID:{}", pInputOrderActionField->ExchangeID);
    SPDLOG_TRACE("OrderSysID:{}", pInputOrderActionField->OrderSysID);
    SPDLOG_TRACE("ActionFlag:{}", pInputOrderActionField->ActionFlag);
    SPDLOG_TRACE("LimitPrice:{}", pInputOrderActionField->LimitPrice);
    SPDLOG_TRACE("VolumeChange:{}", pInputOrderActionField->VolumeChange);
    SPDLOG_TRACE("UserID:{}", pInputOrderActionField->UserID);
    SPDLOG_TRACE("reserve1:{}", pInputOrderActionField->reserve1);
    SPDLOG_TRACE("InvestUnitID:{}", pInputOrderActionField->InvestUnitID);
    SPDLOG_TRACE("reserve2:{}", pInputOrderActionField->reserve2);
    SPDLOG_TRACE("MacAddress:{}", pInputOrderActionField->MacAddress);
    SPDLOG_TRACE("InstrumentID:{}", pInputOrderActionField->InstrumentID);
    SPDLOG_TRACE("IPAddress:{}", pInputOrderActionField->IPAddress);
    SPDLOG_TRACE("CThostFtdcInputOrderActionField\n");
}

int CtpTradeApi::QueryBrokerTradingParams() {
    if (status_ != 3) {
        SPDLOG_ERROR("状态错误: 3 {}.", status_);
        return -1;
    }

    CThostFtdcQryBrokerTradingParamsField t{};
    strcpy(t.InvestorID, config_.account_id.c_str());
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.CurrencyID, "CNY");
    strcpy(t.AccountID, config_.account_id.c_str());

    if (ptr->ReqQryBrokerTradingParams(&t, ++request_id) == 0) {
        SPDLOG_DEBUG("ReqQryBrokerTradingParams, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id, request_id);
        if (signal_query_trading_params_->timedwait(5, 0)) {
            return 0;
        } else {
            SPDLOG_ERROR("Network Error.");
            return -1;
        }
    } else {
        SPDLOG_ERROR("ReqQryBrokerTradingParams, brokerID:{}, userID:{}, requestID:{}", config_.broker_id, config_.account_id, request_id);
        return -1;
    }
}

void CtpTradeApi::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParamsField,
                                              CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    SPDLOG_DEBUG("OnRspQryBrokerTradingParams, nRequestID:{}.", nRequestID);
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        SPDLOG_TRACE("CThostFtdcBrokerTradingParamsField");
        SPDLOG_TRACE("BrokerID:{}", pBrokerTradingParamsField->BrokerID);
        SPDLOG_TRACE("InvestorID:{}", pBrokerTradingParamsField->InvestorID);
        SPDLOG_TRACE("MarginPriceType:{}", pBrokerTradingParamsField->MarginPriceType);
        SPDLOG_TRACE("Algorithm:{}", pBrokerTradingParamsField->Algorithm);
        SPDLOG_TRACE("AvailIncludeCloseProfit:{}", pBrokerTradingParamsField->AvailIncludeCloseProfit);
        SPDLOG_TRACE("CurrencyID:{}", pBrokerTradingParamsField->CurrencyID);
        SPDLOG_TRACE("OptionRoyaltyPriceType:{}", pBrokerTradingParamsField->OptionRoyaltyPriceType);
        SPDLOG_TRACE("AccountID:{}", pBrokerTradingParamsField->AccountID);
        SPDLOG_TRACE("CThostFtdcBrokerTradingParamsField");
        broker_->OnQueryParams();
    } else {
        SPDLOG_ERROR("OnRspQryBrokerTradingParams, ErrorID={}, ErrMsg={}.", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
        signal_query_trading_params_->post();
        return;
    }

    if (bIsLast) {
        signal_query_trading_params_->post();
    }
}

//撤单
int CtpTradeApi::CancelOrder(CThostFtdcInputOrderActionField &t) {
    using namespace ots::data;
    t.ActionFlag = THOST_FTDC_AF_Delete;
    t.RequestID = ++request_id;
    strcpy(t.BrokerID, config_.broker_id.c_str());
    strcpy(t.InvestorID, config_.account_id.c_str());
    strcpy(t.UserID, config_.account_id.c_str());
    t.FrontID = front_id_;
    t.SessionID = session_id_;

    auto ret = ptr->ReqOrderAction(&t, request_id);
    return ret;
}

// 撤单响应
void CtpTradeApi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderActionField, CThostFtdcRspInfoField *pRspInfo) {
    SPDLOG_TRACE("CThostFtdcOrderActionField");
    SPDLOG_TRACE("BrokerID:{}", pOrderActionField->BrokerID);
    SPDLOG_TRACE("InvestorID:{}", pOrderActionField->InvestorID);
    SPDLOG_TRACE("OrderActionRef:{}", pOrderActionField->OrderActionRef);
    SPDLOG_TRACE("OrderRef:{}", pOrderActionField->OrderRef);
    SPDLOG_TRACE("RequestID:{}", pOrderActionField->RequestID);
    SPDLOG_TRACE("FrontID:{}", pOrderActionField->FrontID);
    SPDLOG_TRACE("SessionID:{}", pOrderActionField->SessionID);
    SPDLOG_TRACE("ExchangeID:{}", pOrderActionField->ExchangeID);
    SPDLOG_TRACE("OrderSysID:{}", pOrderActionField->OrderSysID);
    SPDLOG_TRACE("ActionFlag:{}", pOrderActionField->ActionFlag);
    SPDLOG_TRACE("LimitPrice:{}", pOrderActionField->LimitPrice);
    SPDLOG_TRACE("VolumeChange:{}", pOrderActionField->VolumeChange);
    SPDLOG_TRACE("ActionDate:{}", pOrderActionField->ActionDate);
    SPDLOG_TRACE("ActionTime:{}", pOrderActionField->ActionTime);
    SPDLOG_TRACE("TraderID:{}", pOrderActionField->TraderID);
    SPDLOG_TRACE("InstallID:{}", pOrderActionField->InstallID);
    SPDLOG_TRACE("OrderLocalID:{}", pOrderActionField->OrderLocalID);
    SPDLOG_TRACE("ActionLocalID:{}", pOrderActionField->ActionLocalID);
    SPDLOG_TRACE("ParticipantID:{}", pOrderActionField->ParticipantID);
    SPDLOG_TRACE("ClientID:{}", pOrderActionField->ClientID);
    SPDLOG_TRACE("BusinessUnit:{}", pOrderActionField->BusinessUnit);
    SPDLOG_TRACE("OrderActionStatus:{}", pOrderActionField->OrderActionStatus);
    SPDLOG_TRACE("UserID:{}", pOrderActionField->UserID);
    SPDLOG_TRACE("StatusMsg:{}", pOrderActionField->StatusMsg);
    SPDLOG_TRACE("reserve1:{}", pOrderActionField->reserve1);
    SPDLOG_TRACE("BranchID:{}", pOrderActionField->BranchID);
    SPDLOG_TRACE("InvestUnitID:{}", pOrderActionField->InvestUnitID);
    SPDLOG_TRACE("reserve2:{}", pOrderActionField->reserve2);
    SPDLOG_TRACE("MacAddress:{}", pOrderActionField->MacAddress);
    SPDLOG_TRACE("InstrumentID:{}", pOrderActionField->InstrumentID);
    SPDLOG_TRACE("IPAddress:{}", pOrderActionField->IPAddress);
    SPDLOG_TRACE("CThostFtdcOrderActionField");
}
