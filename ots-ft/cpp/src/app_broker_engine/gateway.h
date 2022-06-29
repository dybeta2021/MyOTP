//
// Created by Gavin on 2022/6/29.
//

#ifndef CPP_GATEWAY_H
#define CPP_GATEWAY_H
#include "ThostFtdcTraderApi.h"
#include "ots/broker/broker.h"
#include "ots/utils/encoding.h"
#include "ots/utils/logger.h"
#include "ots/utils/timing.h"
#include <atomic>

namespace ctp_future {
    class CtpTradeClient : public CThostFtdcTraderSpi {
    private:
        CThostFtdcTraderApi *ptr{};
        std::atomic<int> request_id = 0;
        ots::broker::Broker *broker_ = nullptr;

    public:
        void SetBroker(ots::broker::Broker *broker) {
            broker_ = broker;
        }
        // 连接
        void Connect(char frontAddress[]);

        // 客户端认证
        int Authenticate(char brokerID[], char userID[], char appID[], char authCode[]);

        // 释放
        void Release();

        //登陆
        void Login(char brokerID[], char userID[], char password[]);

        void Logout(char brokerID[], char userID[]);

        //结算单确认
        void SettlementInfoConfirm(char brokerID[], char userID[]);

        // 查询账户资金
        bool QueryAccount(char brokerID[], char InvestorID[]);

        // 请求查询投资者持仓
        bool QueryPosition(char brokerID[], char InvestorID[]);

//                	///请求查询投资者持仓
                //	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;


        //        // order
        //        bool insert_order();
        //        bool cancel_order();
        //        bool query_contract();
        //        bool query_position();
        //
        //        bool query_trade();

    public:
        ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
        void OnFrontConnected() override;

        ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
        ///@param nReason 错误原因
        ///        0x1001 网络读失败
        ///        0x1002 网络写失败
        ///        0x2001 接收心跳超时
        ///        0x2002 发送心跳失败
        ///        0x2003 收到错误报文
        void OnFrontDisconnected(int nReason) override;

        ///心跳超时警告。当长时间未收到报文时，该方法被调用。
        ///@param nTimeLapse 距离上次接收报文的时间
        void OnHeartBeatWarning(int nTimeLapse) override;

        ///客户端认证响应
        void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                               CThostFtdcRspInfoField *pRspInfo,
                               int nRequestID,
                               bool bIsLast) override;

        ///登录请求响应
        void
        OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                       CThostFtdcRspInfoField *pRspInfo,
                       int nRequestID,
                       bool bIsLast) override;


        //        ///请求查询投资者结算结果响应
        //        void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo,
        //                                    int nRequestID, bool bIsLast) override;

        ///投资者结算结果确认响应
        void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                        CThostFtdcRspInfoField *pRspInfo,
                                        int nRequestID,
                                        bool bIsLast) override;

        ///登出请求响应
        void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                             CThostFtdcRspInfoField *pRspInfo,
                             int nRequestID,
                             bool bIsLast) override;
        //
        //        ///报单录入请求响应
        //        void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
        //                              bool bIsLast) override;
        //
        //        ///报单操作请求响应
        //        void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo,
        //                              int nRequestID, bool bIsLast) override;
        //
        //        ///报单通知
        //        void OnRtnOrder(CThostFtdcOrderField *pOrder) override;
        //
        //        ///成交通知
        //        void OnRtnTrade(CThostFtdcTradeField *pTrade) override;
        //
        //        ///请求查询合约响应
        //        void
        //        OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
        //                           bool bIsLast) override;
        //
        ///请求查询投资者持仓响应
        void
        OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition,
                                 CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID,
                                 bool bIsLast) override;

        ///请求查询资金账户响应
        void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID,
                                    bool bIsLast) override;
        //
        //        ///请求查询报单响应
        //        void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
        //                           bool bIsLast) override;
        //
        //        ///请求查询成交响应
        //        void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
        //                           bool bIsLast) override;

        ///错误应答
        void OnRspError(CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID,
                        bool bIsLast) override;
    };

    // 连接
    inline void CtpTradeClient::Connect(char frontAddress[]) {
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
    inline int CtpTradeClient::Authenticate(char brokerID[], char userID[], char appID[], char authCode[]) {
        CThostFtdcReqAuthenticateField pReqAuthenticateField{};
        strcpy(pReqAuthenticateField.BrokerID, brokerID);
        strcpy(pReqAuthenticateField.UserID, userID);
        strcpy(pReqAuthenticateField.AppID, appID);
        strcpy(pReqAuthenticateField.AuthCode, authCode);

        SPDLOG_INFO("Authenticate, BrokerID:{}, UserID:{}, appID:{} authCode:{}, requestID:{}", brokerID, userID, appID, authCode, request_id);
        return ptr->ReqAuthenticate(&pReqAuthenticateField, request_id++);
    }

    //释放
    inline void CtpTradeClient::Release() {
        ptr->Release();
    }


    //登陆
    inline void CtpTradeClient::Login(char brokerID[], char userID[], char password[]) {
        CThostFtdcReqUserLoginField t{};
        strcpy(t.BrokerID, brokerID);
        strcpy(t.UserID, userID);
        strcpy(t.Password, password);
        SPDLOG_INFO("Login, brokerID:{}, userID:{}, requestID:{}", brokerID, userID, request_id);
        while (ptr->ReqUserLogin(&t, request_id++) != 0) ots::utils::timing_ms(100);
    }

    //登出
    inline void CtpTradeClient::Logout(char brokerID[], char userID[]) {
        CThostFtdcUserLogoutField t{};
        strcpy(t.BrokerID, brokerID);
        strcpy(t.UserID, userID);
        SPDLOG_INFO("Logout, brokerID:{}, userID:{}, requestID:{}", brokerID, userID, request_id);
        while (ptr->ReqUserLogout(&t, request_id++) != 0) ots::utils::timing_ms(100);
    }

    //结算单确认
    inline void CtpTradeClient::SettlementInfoConfirm(char brokerID[], char userID[]) {
        CThostFtdcSettlementInfoConfirmField t{};
        strcpy(t.BrokerID, brokerID);
        strcpy(t.InvestorID, userID);
        SPDLOG_INFO("ReqSettlementInfoConfirm, brokerID:{}, userID:{}, requestID:{}", brokerID, userID, request_id);
        while (ptr->ReqSettlementInfoConfirm(&t, request_id++) != 0) ots::utils::timing_ms(100);
        SPDLOG_INFO("设定默认自动确认结算单");
    }


    inline void CtpTradeClient::OnFrontConnected() {
        SPDLOG_INFO("交易服务器连接成功");
    }

    inline void CtpTradeClient::OnFrontDisconnected(int nReason) {
        SPDLOG_ERROR("交易服务器连接失败: {}", nReason);
    }

    inline void CtpTradeClient::OnHeartBeatWarning(int nTimeLapse) {
        SPDLOG_WARN("Warn. No packet received for a period of time. {}", nTimeLapse);
    }

    //客户端认证响应
    inline void CtpTradeClient::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                                                  CThostFtdcRspInfoField *pRspInfo,
                                                  int nRequestID, bool bIsLast) {
        SPDLOG_INFO("客户端认证响应, nRequestID:{}", nRequestID);
        if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
            SPDLOG_INFO("认证成功,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
        } else {
            SPDLOG_ERROR("认证失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
        }
    }


    inline void
    CtpTradeClient::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                                   int nRequestID, bool bIsLast) {

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

    inline void CtpTradeClient::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo,
                                                int nRequestID, bool bIsLast) {
        SPDLOG_INFO("交易账户登出, nRequestID:{}", nRequestID);
        if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
            SPDLOG_INFO("交易账户退出成功. Broker ID: {}, Investor ID: {}.", pUserLogout->BrokerID, pUserLogout->UserID);
        } else {
            SPDLOG_ERROR("交易账户登出失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
        }
    }

    // 结算单确认响应
    inline void
    CtpTradeClient::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                               CThostFtdcRspInfoField *pRspInfo, int nRequestID,
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
    inline void CtpTradeClient::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        SPDLOG_ERROR("OnRspError, nRequestID: {},ErrorID={}, ErrMsg={}", nRequestID, pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }

    // 请求查询资金账户
    inline bool CtpTradeClient::QueryAccount(char brokerID[], char InvestorID[]) {
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
    inline void CtpTradeClient::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
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

    inline bool CtpTradeClient::QueryPosition(char *brokerID, char *InvestorID) {
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

    inline void CtpTradeClient::OnRspQryInvestorPosition(
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

}// namespace ctp_future

#endif//CPP_GATEWAY_H
