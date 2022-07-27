//
// Created by 稻草人 on 2022/6/29.
//

#ifndef CPP_GATEWAY_H
#define CPP_GATEWAY_H
#include "ThostFtdcTraderApi.h"
#include "nut/signal/sem.h"
#include "ots/data.h"
#include "ots/utils/encoding.h"
#include "ots/utils/timing.h"
#include "spdlog/spdlog.h"
#include <atomic>

//extern class BrokerCTP;
class BrokerCTP;

class CtpTradeApi : public CThostFtdcTraderSpi {
private:
    CThostFtdcTraderApi *ptr{};

    // 前置编号、会话编号
    int front_id_ = -1;
    int session_id_ = -1;

    // TODO:是否需要使用atomic？
    int request_id = -1;
    BrokerCTP *broker_ = nullptr;
    ots::data::Config config_;

    // 登录状态，-1:未登录, 0:Init, 1:监管认证，2:Login，3:确认结算单
    std::atomic<int> status_ = -1;
    nut::Semaphore *signal_init_ = nullptr;
    nut::Semaphore *signal_authenticate_ = nullptr;
    nut::Semaphore *signal_login_ = nullptr;
    nut::Semaphore *signal_query_settlement_confirm_ = nullptr;
    nut::Semaphore *signal_settlement_confirm_ = nullptr;
    nut::Semaphore *signal_logout_ = nullptr;
    nut::Semaphore *signal_query_trading_params_ = nullptr;
    nut::Semaphore *signal_query_account_ = nullptr;
    nut::Semaphore *signal_query_position_ = nullptr;

public:
    CtpTradeApi();
    ~CtpTradeApi();

    void SetConfig(const ots::data::Config &config);
    void SetBroker(BrokerCTP *broker);

    // 连接 客户端认证 登陆 结算单确认
    int Init();
    int Authenticate();
    int Login();
    int QuerySettlementInfoConfirm();
    int SettlementInfoConfirm();

    // 连接状态
    int GetStatus();

    // 注销账户 客户端释放
    int Logout();
    void Release();

    // 查询保证金算法
    int QueryBrokerTradingParams();

    // 查询账户资金
    int QueryAccount();

    // 请求查询投资者持仓
    int QueryPosition();

    // 下单
    int InsertOrder(CThostFtdcInputOrderField &t);

    // 撤单
    int CancelOrder(CThostFtdcInputOrderActionField &t);

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
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLoginField,
                        CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID,
                        bool bIsLast) override;


    ///请求查询结算信息确认响应
    void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirmField,
                                       CThostFtdcRspInfoField *pRspInfo,
                                       int nRequestID,
                                       bool bIsLast) override;


    ///投资者结算结果确认响应
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirmField,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID,
                                    bool bIsLast) override;

    ///登出请求响应
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogoutField,
                         CThostFtdcRspInfoField *pRspInfo,
                         int nRequestID,
                         bool bIsLast) override;

    // OnRspOrderInsert是当前报单者收到的回调，OnErrRtnOrderInsert是该客户名下所有的链接都会收到的回调。
    // 例如，用户通过CTP的API同时开了两个链接A和B分别连到了CTP后台（这两个链接称之为两个会话：session），
    // 他通过Session A报单，这笔订单因为某原因被CTP拒单。这时他的报单Session A会收到OnRspOrderInsert回调；
    // 他名下另一个连着的Session B会收到OnErrRtnOrderInsert回调。
    ///报单录入请求响应
    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrderField, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                          bool bIsLast) override;

    ///报单录入错误回报
    void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrderField, CThostFtdcRspInfoField *pRspInfo) override;

    ///撤单错误响应
    void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderActionField, CThostFtdcRspInfoField *pRspInfo,
                          int nRequestID, bool bIsLast) override;

    ///撤单错误响应
    void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderActionField, CThostFtdcRspInfoField *pRspInfo) override;

    ///报单通知
    void OnRtnOrder(CThostFtdcOrderField *pOrderField) override;

    ///成交通知
    void OnRtnTrade(CThostFtdcTradeField *pTradeField) override;

    ///请求查询投资者持仓响应
    void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPositionField,
                                  CThostFtdcRspInfoField *pRspInfo,
                                  int nRequestID,
                                  bool bIsLast) override;

    ///请求查询资金账户响应
    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccountField,
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
    void OnRspError(CThostFtdcRspInfoField *pRspInfoField,
                    int nRequestID,
                    bool bIsLast) override;

    ///请求查询经纪公司交易参数响应
    void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParamsField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
};


#endif//CPP_GATEWAY_H
