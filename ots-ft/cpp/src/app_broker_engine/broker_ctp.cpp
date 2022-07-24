//
// Created by 稻草人 on 2022/6/30.
//
#include "ots/utils/logger.h"
#include "broker_ctp.h"
#include "ThostFtdcTraderApi.h"
#include "ots/broker/contract.h"

void BrokerCTP::SetGateway(CtpTradeApi *client) {
    client_ = client;
}

int BrokerCTP::Login() {
    std::string dir_path = "ctp_future_td_flow";
    ots::utils::create_folder(dir_path);

    SPDLOG_INFO("Step:交易前置机.");
    if (client_->Init() != 0) {
        return -1;
    }

    SPDLOG_INFO("Step:看穿式认证.");
    if (client_->Authenticate() != 0) {
        return -1;
    }

    SPDLOG_INFO("Step:登陆.");
    if (client_->Login() != 0) {
        return -1;
    }
    // TODO：查询结算单没有回调是否是因为openctp导致的
    //    SPDLOG_INFO("Step:查询结算单.");
    //    if(client_->QuerySettlementInfoConfirm()!=0){
    //        return -1;
    //    }

    SPDLOG_INFO("Step:确认结算单.");
    if (client_->SettlementInfoConfirm() != 0) {
        return -1;
    }

    if (client_->GetStatus() != 0) {
        SPDLOG_ERROR("Step:GetStatus ERROR:{}.", client_->GetStatus());
        return -1;
    }

    SPDLOG_INFO("Step:交易账户登陆完成.");
    return 0;
}

int BrokerCTP::Logout() {
    client_->Logout();
    client_->Release();
    return 0;
}

int BrokerCTP::QueryAccount() {
    return client_->QueryAccount();
}

void BrokerCTP::OnQueryAccount(const ots::broker::Account &account) {
    account_manager_->OnQuery(account);
    account_manager_->OnPosition(position_manager_->GetAccount());
}

int BrokerCTP::QueryPosition() {
    return client_->QueryPosition();
}

void BrokerCTP::OnQueryPosition(const ots::data::Position &position) {
    position_manager_->OnQuery(position);
}

void BrokerCTP::ShowPosition() {
    position_manager_->Show();
}

int BrokerCTP::QueryParams() {
    return client_->QueryBrokerTradingParams();
}

void BrokerCTP::OnQueryParams() {
}

int BrokerCTP::InsertLimitOrder(ots::data::Order &order) {
    using namespace ots::data;

    if (order.type != ots::data::OrderType::Limit) {
        SPDLOG_WARN("OrderType Error, {}.", magic_enum::enum_name(order.type));
        return -1;
    }

    order.order_ref_num = order_manager_->GetOrderRef();
    order.status = OrderStatus::Insert;
    strcpy(order.trading_day, kungfu::yijinjing::time::strfnow("%F").c_str());
    order.insert_time = kungfu::yijinjing::time::now_in_nano();
    order.traded_volume = 0;
    order.left_volume = order.volume;
    order.cancel_volume = 0;
    order_manager_->InsertOrder(order);

    CThostFtdcInputOrderField t{};
    strcpy(t.InstrumentID, order.symbol);
    if (order.offset == Offset::Open)
        t.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    else if (order.offset == Offset::Close)
        t.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    else if (order.offset == Offset::CloseToday)
        t.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
    else
        t.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;

    t.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    strcpy(t.ExchangeID, order.exchange_id);
    t.VolumeTotalOriginal = order.volume;
    // 自动挂起标志 必填0
    t.IsAutoSuspend = 0;
    // 互换单标志 必填
    t.IsSwapOrder = 1;
    t.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    t.LimitPrice = order.price;

    //todo:StopPrice是否需要填写
    auto contract = ots::broker::ContractTable::get_contract(order.symbol);
    if (order.direction == Direction::Long) {
        t.Direction = THOST_FTDC_D_Buy;
        t.StopPrice = contract.price_min_limit;
    } else {
        t.Direction = THOST_FTDC_D_Sell;
        t.StopPrice = contract.price_max_limit;
    }

    if (strcmp(order.exchange_id, ots::data::exchange::CZCE) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_GFD;
        t.VolumeCondition = THOST_FTDC_VC_AV;
    } else if (strcmp(order.exchange_id, ots::data::exchange::DCE) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_GFD;
        t.VolumeCondition = THOST_FTDC_VC_AV;
    } else if (strcmp(order.exchange_id, ots::data::exchange::CFFEX) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_GFD;
        t.VolumeCondition = THOST_FTDC_VC_AV;
    } else if (strcmp(order.exchange_id, ots::data::exchange::SHFE) == 0 | strcmp(order.exchange_id, ots::data::exchange::INE) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_GFD;
        t.VolumeCondition = THOST_FTDC_VC_AV;
    } else {
        SPDLOG_ERROR("{}", order.exchange_id);
        return -1;
    }

    strcpy(t.OrderRef,std::to_string(order.order_ref_num).c_str());
    auto ret = client_->InsertOrder(t);
    //todo:
    if(ret!=0){
        order.status = OrderStatus::NetworkError;
        order.update_time =  kungfu::yijinjing::time::now_in_nano();
        strcpy(order.error_msg, "网络错误？.");
        order_manager_->OnError(order);
    }
    return ret;
}

int BrokerCTP::InsertMarketOrder(ots::data::Order &order) {
    using namespace ots::data;

    if (order.type != ots::data::OrderType::Market) {
        SPDLOG_WARN("OrderType Error, {}.", magic_enum::enum_name(order.type));
        return -1;
    }

    order.order_ref_num = order_manager_->GetOrderRef();
    order.status = OrderStatus::Insert;
    strcpy(order.trading_day, kungfu::yijinjing::time::strfnow("%F").c_str());
    order.insert_time = kungfu::yijinjing::time::now_in_nano();
    order.traded_volume = 0;
    order.left_volume = order.volume;
    order.cancel_volume = 0;
    order_manager_->InsertOrder(order);

    CThostFtdcInputOrderField t{};
    strcpy(t.InstrumentID, order.symbol);
    if (order.offset == Offset::Open)
        t.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    else if (order.offset == Offset::Close)
        t.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    else if (order.offset == Offset::CloseToday)
        t.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
    else
        t.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;

    t.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    strcpy(t.ExchangeID, order.exchange_id);
    t.VolumeTotalOriginal = order.volume;
    // 自动挂起标志 必填0
    t.IsAutoSuspend = 0;
    // 互换单标志 必填
    t.IsSwapOrder = 1;
    t.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

    if (strcmp(order.exchange_id, ots::data::exchange::CZCE) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_GFD;
        t.VolumeCondition = THOST_FTDC_VC_AV;
    } else if (strcmp(order.exchange_id, ots::data::exchange::DCE) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_GFD;
        t.VolumeCondition = THOST_FTDC_VC_AV;
    } else if (strcmp(order.exchange_id, ots::data::exchange::CFFEX) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_FiveLevelPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_IOC;
        t.VolumeCondition = THOST_FTDC_VC_AV;
    } else if (strcmp(order.exchange_id, ots::data::exchange::SHFE) == 0 | strcmp(order.exchange_id, ots::data::exchange::INE) == 0) {
        t.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
        t.ContingentCondition = THOST_FTDC_CC_Immediately;
        t.TimeCondition = THOST_FTDC_TC_GFD;
        t.VolumeCondition = THOST_FTDC_VC_AV;

        auto contract = ots::broker::ContractTable::get_contract(order.symbol);
        if (order.direction == Direction::Long) {
            t.Direction = THOST_FTDC_D_Buy;
            t.LimitPrice = contract.price_max_limit;
            t.StopPrice = contract.price_min_limit;
        } else {
            t.Direction = THOST_FTDC_D_Sell;
            t.LimitPrice = contract.price_min_limit;
            t.StopPrice = contract.price_max_limit;
        }
    } else {
        SPDLOG_ERROR("{}", order.exchange_id);
        return -1;
    }

    strcpy(t.OrderRef,std::to_string(order.order_ref_num).c_str());
    auto ret = client_->InsertOrder(t);
    //todo:
    if(ret!=0){
        order.status = OrderStatus::NetworkError;
        order.update_time =  kungfu::yijinjing::time::now_in_nano();
        strcpy(order.error_msg, "网络错误？.");
        order_manager_->OnError(order);
    }
    return ret;
}
