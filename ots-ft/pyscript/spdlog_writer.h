std::ostream& operator<<(std::ostream& os, const CThostFtdcDisseminationField& c)
{
return os<<"SequenceSeries"<< c.SequenceSeries<<"SequenceNo"<< c.SequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqUserLoginField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"Password"<< c.Password<<"UserProductInfo"<< c.UserProductInfo<<"InterfaceProductInfo"<< c.InterfaceProductInfo<<"ProtocolInfo"<< c.ProtocolInfo<<"MacAddress"<< c.MacAddress<<"OneTimePassword"<< c.OneTimePassword<<"reserve1"<< c.reserve1<<"LoginRemark"<< c.LoginRemark<<"ClientIPPort"<< c.ClientIPPort<<"ClientIPAddress"<< c.ClientIPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspUserLoginField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"LoginTime"<< c.LoginTime<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"SystemName"<< c.SystemName<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"MaxOrderRef"<< c.MaxOrderRef<<"SHFETime"<< c.SHFETime<<"DCETime"<< c.DCETime<<"CZCETime"<< c.CZCETime<<"FFEXTime"<< c.FFEXTime<<"INETime"<< c.INETime;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcUserLogoutField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcForceUserLogoutField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqAuthenticateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"UserProductInfo"<< c.UserProductInfo<<"AuthCode"<< c.AuthCode<<"AppID"<< c.AppID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspAuthenticateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"UserProductInfo"<< c.UserProductInfo<<"AppID"<< c.AppID<<"AppType"<< c.AppType;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcAuthenticationInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"UserProductInfo"<< c.UserProductInfo<<"AuthInfo"<< c.AuthInfo<<"IsResult"<< c.IsResult<<"AppID"<< c.AppID<<"AppType"<< c.AppType<<"reserve1"<< c.reserve1<<"ClientIPAddress"<< c.ClientIPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspUserLogin2Field& c)
{
return os<<"TradingDay"<< c.TradingDay<<"LoginTime"<< c.LoginTime<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"SystemName"<< c.SystemName<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"MaxOrderRef"<< c.MaxOrderRef<<"SHFETime"<< c.SHFETime<<"DCETime"<< c.DCETime<<"CZCETime"<< c.CZCETime<<"FFEXTime"<< c.FFEXTime<<"INETime"<< c.INETime<<"RandomString"<< c.RandomString;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferHeaderField& c)
{
return os<<"Version"<< c.Version<<"TradeCode"<< c.TradeCode<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"TradeSerial"<< c.TradeSerial<<"FutureID"<< c.FutureID<<"BankID"<< c.BankID<<"BankBrchID"<< c.BankBrchID<<"OperNo"<< c.OperNo<<"DeviceID"<< c.DeviceID<<"RecordNum"<< c.RecordNum<<"SessionID"<< c.SessionID<<"RequestID"<< c.RequestID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferBankToFutureReqField& c)
{
return os<<"FutureAccount"<< c.FutureAccount<<"FuturePwdFlag"<< c.FuturePwdFlag<<"FutureAccPwd"<< c.FutureAccPwd<<"TradeAmt"<< c.TradeAmt<<"CustFee"<< c.CustFee<<"CurrencyCode"<< c.CurrencyCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferBankToFutureRspField& c)
{
return os<<"RetCode"<< c.RetCode<<"RetInfo"<< c.RetInfo<<"FutureAccount"<< c.FutureAccount<<"TradeAmt"<< c.TradeAmt<<"CustFee"<< c.CustFee<<"CurrencyCode"<< c.CurrencyCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferFutureToBankReqField& c)
{
return os<<"FutureAccount"<< c.FutureAccount<<"FuturePwdFlag"<< c.FuturePwdFlag<<"FutureAccPwd"<< c.FutureAccPwd<<"TradeAmt"<< c.TradeAmt<<"CustFee"<< c.CustFee<<"CurrencyCode"<< c.CurrencyCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferFutureToBankRspField& c)
{
return os<<"RetCode"<< c.RetCode<<"RetInfo"<< c.RetInfo<<"FutureAccount"<< c.FutureAccount<<"TradeAmt"<< c.TradeAmt<<"CustFee"<< c.CustFee<<"CurrencyCode"<< c.CurrencyCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferQryBankReqField& c)
{
return os<<"FutureAccount"<< c.FutureAccount<<"FuturePwdFlag"<< c.FuturePwdFlag<<"FutureAccPwd"<< c.FutureAccPwd<<"CurrencyCode"<< c.CurrencyCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferQryBankRspField& c)
{
return os<<"RetCode"<< c.RetCode<<"RetInfo"<< c.RetInfo<<"FutureAccount"<< c.FutureAccount<<"TradeAmt"<< c.TradeAmt<<"UseAmt"<< c.UseAmt<<"FetchAmt"<< c.FetchAmt<<"CurrencyCode"<< c.CurrencyCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferQryDetailReqField& c)
{
return os<<"FutureAccount"<< c.FutureAccount;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferQryDetailRspField& c)
{
return os<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"TradeCode"<< c.TradeCode<<"FutureSerial"<< c.FutureSerial<<"FutureID"<< c.FutureID<<"FutureAccount"<< c.FutureAccount<<"BankSerial"<< c.BankSerial<<"BankID"<< c.BankID<<"BankBrchID"<< c.BankBrchID<<"BankAccount"<< c.BankAccount<<"CertCode"<< c.CertCode<<"CurrencyCode"<< c.CurrencyCode<<"TxAmount"<< c.TxAmount<<"Flag"<< c.Flag;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspInfoField& c)
{
return os<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ExchangeName"<< c.ExchangeName<<"ExchangeProperty"<< c.ExchangeProperty;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcProductField& c)
{
return os<<"reserve1"<< c.reserve1<<"ProductName"<< c.ProductName<<"ExchangeID"<< c.ExchangeID<<"ProductClass"<< c.ProductClass<<"VolumeMultiple"<< c.VolumeMultiple<<"PriceTick"<< c.PriceTick<<"MaxMarketOrderVolume"<< c.MaxMarketOrderVolume<<"MinMarketOrderVolume"<< c.MinMarketOrderVolume<<"MaxLimitOrderVolume"<< c.MaxLimitOrderVolume<<"MinLimitOrderVolume"<< c.MinLimitOrderVolume<<"PositionType"<< c.PositionType<<"PositionDateType"<< c.PositionDateType<<"CloseDealType"<< c.CloseDealType<<"TradeCurrencyID"<< c.TradeCurrencyID<<"MortgageFundUseRange"<< c.MortgageFundUseRange<<"reserve2"<< c.reserve2<<"UnderlyingMultiple"<< c.UnderlyingMultiple<<"ProductID"<< c.ProductID<<"ExchangeProductID"<< c.ExchangeProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentField& c)
{
return os<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InstrumentName"<< c.InstrumentName<<"reserve2"<< c.reserve2<<"reserve3"<< c.reserve3<<"ProductClass"<< c.ProductClass<<"DeliveryYear"<< c.DeliveryYear<<"DeliveryMonth"<< c.DeliveryMonth<<"MaxMarketOrderVolume"<< c.MaxMarketOrderVolume<<"MinMarketOrderVolume"<< c.MinMarketOrderVolume<<"MaxLimitOrderVolume"<< c.MaxLimitOrderVolume<<"MinLimitOrderVolume"<< c.MinLimitOrderVolume<<"VolumeMultiple"<< c.VolumeMultiple<<"PriceTick"<< c.PriceTick<<"CreateDate"<< c.CreateDate<<"OpenDate"<< c.OpenDate<<"ExpireDate"<< c.ExpireDate<<"StartDelivDate"<< c.StartDelivDate<<"EndDelivDate"<< c.EndDelivDate<<"InstLifePhase"<< c.InstLifePhase<<"IsTrading"<< c.IsTrading<<"PositionType"<< c.PositionType<<"PositionDateType"<< c.PositionDateType<<"LongMarginRatio"<< c.LongMarginRatio<<"ShortMarginRatio"<< c.ShortMarginRatio<<"MaxMarginSideAlgorithm"<< c.MaxMarginSideAlgorithm<<"reserve4"<< c.reserve4<<"StrikePrice"<< c.StrikePrice<<"OptionsType"<< c.OptionsType<<"UnderlyingMultiple"<< c.UnderlyingMultiple<<"CombinationType"<< c.CombinationType<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"ProductID"<< c.ProductID<<"UnderlyingInstrID"<< c.UnderlyingInstrID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"BrokerAbbr"<< c.BrokerAbbr<<"BrokerName"<< c.BrokerName<<"IsActive"<< c.IsActive;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTraderField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ParticipantID"<< c.ParticipantID<<"Password"<< c.Password<<"InstallCount"<< c.InstallCount<<"BrokerID"<< c.BrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorField& c)
{
return os<<"InvestorID"<< c.InvestorID<<"BrokerID"<< c.BrokerID<<"InvestorGroupID"<< c.InvestorGroupID<<"InvestorName"<< c.InvestorName<<"IdentifiedCardType"<< c.IdentifiedCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"IsActive"<< c.IsActive<<"Telephone"<< c.Telephone<<"Address"<< c.Address<<"OpenDate"<< c.OpenDate<<"Mobile"<< c.Mobile<<"CommModelID"<< c.CommModelID<<"MarginModelID"<< c.MarginModelID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingCodeField& c)
{
return os<<"InvestorID"<< c.InvestorID<<"BrokerID"<< c.BrokerID<<"ExchangeID"<< c.ExchangeID<<"ClientID"<< c.ClientID<<"IsActive"<< c.IsActive<<"ClientIDType"<< c.ClientIDType<<"BranchID"<< c.BranchID<<"BizType"<< c.BizType<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcPartBrokerField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"IsActive"<< c.IsActive;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSuperUserField& c)
{
return os<<"UserID"<< c.UserID<<"UserName"<< c.UserName<<"Password"<< c.Password<<"IsActive"<< c.IsActive;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSuperUserFunctionField& c)
{
return os<<"UserID"<< c.UserID<<"FunctionCode"<< c.FunctionCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorGroupField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorGroupID"<< c.InvestorGroupID<<"InvestorGroupName"<< c.InvestorGroupName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingAccountField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"PreMortgage"<< c.PreMortgage<<"PreCredit"<< c.PreCredit<<"PreDeposit"<< c.PreDeposit<<"PreBalance"<< c.PreBalance<<"PreMargin"<< c.PreMargin<<"InterestBase"<< c.InterestBase<<"Interest"<< c.Interest<<"Deposit"<< c.Deposit<<"Withdraw"<< c.Withdraw<<"FrozenMargin"<< c.FrozenMargin<<"FrozenCash"<< c.FrozenCash<<"FrozenCommission"<< c.FrozenCommission<<"CurrMargin"<< c.CurrMargin<<"CashIn"<< c.CashIn<<"Commission"<< c.Commission<<"CloseProfit"<< c.CloseProfit<<"PositionProfit"<< c.PositionProfit<<"Balance"<< c.Balance<<"Available"<< c.Available<<"WithdrawQuota"<< c.WithdrawQuota<<"Reserve"<< c.Reserve<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"Credit"<< c.Credit<<"Mortgage"<< c.Mortgage<<"ExchangeMargin"<< c.ExchangeMargin<<"DeliveryMargin"<< c.DeliveryMargin<<"ExchangeDeliveryMargin"<< c.ExchangeDeliveryMargin<<"ReserveBalance"<< c.ReserveBalance<<"CurrencyID"<< c.CurrencyID<<"PreFundMortgageIn"<< c.PreFundMortgageIn<<"PreFundMortgageOut"<< c.PreFundMortgageOut<<"FundMortgageIn"<< c.FundMortgageIn<<"FundMortgageOut"<< c.FundMortgageOut<<"FundMortgageAvailable"<< c.FundMortgageAvailable<<"MortgageableFund"<< c.MortgageableFund<<"SpecProductMargin"<< c.SpecProductMargin<<"SpecProductFrozenMargin"<< c.SpecProductFrozenMargin<<"SpecProductCommission"<< c.SpecProductCommission<<"SpecProductFrozenCommission"<< c.SpecProductFrozenCommission<<"SpecProductPositionProfit"<< c.SpecProductPositionProfit<<"SpecProductCloseProfit"<< c.SpecProductCloseProfit<<"SpecProductPositionProfitByAlg"<< c.SpecProductPositionProfitByAlg<<"SpecProductExchangeMargin"<< c.SpecProductExchangeMargin<<"BizType"<< c.BizType<<"FrozenSwap"<< c.FrozenSwap<<"RemainSwap"<< c.RemainSwap;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorPositionField& c)
{
return os<<"reserve1"<< c.reserve1<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"PosiDirection"<< c.PosiDirection<<"HedgeFlag"<< c.HedgeFlag<<"PositionDate"<< c.PositionDate<<"YdPosition"<< c.YdPosition<<"Position"<< c.Position<<"LongFrozen"<< c.LongFrozen<<"ShortFrozen"<< c.ShortFrozen<<"LongFrozenAmount"<< c.LongFrozenAmount<<"ShortFrozenAmount"<< c.ShortFrozenAmount<<"OpenVolume"<< c.OpenVolume<<"CloseVolume"<< c.CloseVolume<<"OpenAmount"<< c.OpenAmount<<"CloseAmount"<< c.CloseAmount<<"PositionCost"<< c.PositionCost<<"PreMargin"<< c.PreMargin<<"UseMargin"<< c.UseMargin<<"FrozenMargin"<< c.FrozenMargin<<"FrozenCash"<< c.FrozenCash<<"FrozenCommission"<< c.FrozenCommission<<"CashIn"<< c.CashIn<<"Commission"<< c.Commission<<"CloseProfit"<< c.CloseProfit<<"PositionProfit"<< c.PositionProfit<<"PreSettlementPrice"<< c.PreSettlementPrice<<"SettlementPrice"<< c.SettlementPrice<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OpenCost"<< c.OpenCost<<"ExchangeMargin"<< c.ExchangeMargin<<"CombPosition"<< c.CombPosition<<"CombLongFrozen"<< c.CombLongFrozen<<"CombShortFrozen"<< c.CombShortFrozen<<"CloseProfitByDate"<< c.CloseProfitByDate<<"CloseProfitByTrade"<< c.CloseProfitByTrade<<"TodayPosition"<< c.TodayPosition<<"MarginRateByMoney"<< c.MarginRateByMoney<<"MarginRateByVolume"<< c.MarginRateByVolume<<"StrikeFrozen"<< c.StrikeFrozen<<"StrikeFrozenAmount"<< c.StrikeFrozenAmount<<"AbandonFrozen"<< c.AbandonFrozen<<"ExchangeID"<< c.ExchangeID<<"YdStrikeFrozen"<< c.YdStrikeFrozen<<"InvestUnitID"<< c.InvestUnitID<<"PositionCostOffset"<< c.PositionCostOffset<<"TasPosition"<< c.TasPosition<<"TasPositionCost"<< c.TasPositionCost<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentMarginRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"IsRelative"<< c.IsRelative<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentCommissionRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OpenRatioByMoney"<< c.OpenRatioByMoney<<"OpenRatioByVolume"<< c.OpenRatioByVolume<<"CloseRatioByMoney"<< c.CloseRatioByMoney<<"CloseRatioByVolume"<< c.CloseRatioByVolume<<"CloseTodayRatioByMoney"<< c.CloseTodayRatioByMoney<<"CloseTodayRatioByVolume"<< c.CloseTodayRatioByVolume<<"ExchangeID"<< c.ExchangeID<<"BizType"<< c.BizType<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcDepthMarketDataField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"reserve2"<< c.reserve2<<"LastPrice"<< c.LastPrice<<"PreSettlementPrice"<< c.PreSettlementPrice<<"PreClosePrice"<< c.PreClosePrice<<"PreOpenInterest"<< c.PreOpenInterest<<"OpenPrice"<< c.OpenPrice<<"HighestPrice"<< c.HighestPrice<<"LowestPrice"<< c.LowestPrice<<"Volume"<< c.Volume<<"Turnover"<< c.Turnover<<"OpenInterest"<< c.OpenInterest<<"ClosePrice"<< c.ClosePrice<<"SettlementPrice"<< c.SettlementPrice<<"UpperLimitPrice"<< c.UpperLimitPrice<<"LowerLimitPrice"<< c.LowerLimitPrice<<"PreDelta"<< c.PreDelta<<"CurrDelta"<< c.CurrDelta<<"UpdateTime"<< c.UpdateTime<<"UpdateMillisec"<< c.UpdateMillisec<<"BidPrice1"<< c.BidPrice1<<"BidVolume1"<< c.BidVolume1<<"AskPrice1"<< c.AskPrice1<<"AskVolume1"<< c.AskVolume1<<"BidPrice2"<< c.BidPrice2<<"BidVolume2"<< c.BidVolume2<<"AskPrice2"<< c.AskPrice2<<"AskVolume2"<< c.AskVolume2<<"BidPrice3"<< c.BidPrice3<<"BidVolume3"<< c.BidVolume3<<"AskPrice3"<< c.AskPrice3<<"AskVolume3"<< c.AskVolume3<<"BidPrice4"<< c.BidPrice4<<"BidVolume4"<< c.BidVolume4<<"AskPrice4"<< c.AskPrice4<<"AskVolume4"<< c.AskVolume4<<"BidPrice5"<< c.BidPrice5<<"BidVolume5"<< c.BidVolume5<<"AskPrice5"<< c.AskPrice5<<"AskVolume5"<< c.AskVolume5<<"AveragePrice"<< c.AveragePrice<<"ActionDay"<< c.ActionDay<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"BandingUpperPrice"<< c.BandingUpperPrice<<"BandingLowerPrice"<< c.BandingLowerPrice;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentTradingRightField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"TradingRight"<< c.TradingRight<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerUserField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"UserName"<< c.UserName<<"UserType"<< c.UserType<<"IsActive"<< c.IsActive<<"IsUsingOTP"<< c.IsUsingOTP<<"IsAuthForce"<< c.IsAuthForce;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerUserPasswordField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"Password"<< c.Password<<"LastUpdateTime"<< c.LastUpdateTime<<"LastLoginTime"<< c.LastLoginTime<<"ExpireDate"<< c.ExpireDate<<"WeakExpireDate"<< c.WeakExpireDate;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerUserFunctionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"BrokerFunctionCode"<< c.BrokerFunctionCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTraderOfferField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ParticipantID"<< c.ParticipantID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"OrderLocalID"<< c.OrderLocalID<<"TraderConnectStatus"<< c.TraderConnectStatus<<"ConnectRequestDate"<< c.ConnectRequestDate<<"ConnectRequestTime"<< c.ConnectRequestTime<<"LastReportDate"<< c.LastReportDate<<"LastReportTime"<< c.LastReportTime<<"ConnectDate"<< c.ConnectDate<<"ConnectTime"<< c.ConnectTime<<"StartDate"<< c.StartDate<<"StartTime"<< c.StartTime<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"MaxTradeID"<< c.MaxTradeID<<"MaxOrderMessageReference"<< c.MaxOrderMessageReference;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSettlementInfoField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"SequenceNo"<< c.SequenceNo<<"Content"<< c.Content<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentMarginRateAdjustField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"IsRelative"<< c.IsRelative<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeMarginRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeMarginRateAdjustField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"ExchLongMarginRatioByMoney"<< c.ExchLongMarginRatioByMoney<<"ExchLongMarginRatioByVolume"<< c.ExchLongMarginRatioByVolume<<"ExchShortMarginRatioByMoney"<< c.ExchShortMarginRatioByMoney<<"ExchShortMarginRatioByVolume"<< c.ExchShortMarginRatioByVolume<<"NoLongMarginRatioByMoney"<< c.NoLongMarginRatioByMoney<<"NoLongMarginRatioByVolume"<< c.NoLongMarginRatioByVolume<<"NoShortMarginRatioByMoney"<< c.NoShortMarginRatioByMoney<<"NoShortMarginRatioByVolume"<< c.NoShortMarginRatioByVolume<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"FromCurrencyID"<< c.FromCurrencyID<<"FromCurrencyUnit"<< c.FromCurrencyUnit<<"ToCurrencyID"<< c.ToCurrencyID<<"ExchangeRate"<< c.ExchangeRate;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSettlementRefField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCurrentTimeField& c)
{
return os<<"CurrDate"<< c.CurrDate<<"CurrTime"<< c.CurrTime<<"CurrMillisec"<< c.CurrMillisec<<"ActionDay"<< c.ActionDay;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCommPhaseField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"CommPhaseNo"<< c.CommPhaseNo<<"SystemID"<< c.SystemID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcLoginInfoField& c)
{
return os<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"LoginDate"<< c.LoginDate<<"LoginTime"<< c.LoginTime<<"reserve1"<< c.reserve1<<"UserProductInfo"<< c.UserProductInfo<<"InterfaceProductInfo"<< c.InterfaceProductInfo<<"ProtocolInfo"<< c.ProtocolInfo<<"SystemName"<< c.SystemName<<"PasswordDeprecated"<< c.PasswordDeprecated<<"MaxOrderRef"<< c.MaxOrderRef<<"SHFETime"<< c.SHFETime<<"DCETime"<< c.DCETime<<"CZCETime"<< c.CZCETime<<"FFEXTime"<< c.FFEXTime<<"MacAddress"<< c.MacAddress<<"OneTimePassword"<< c.OneTimePassword<<"INETime"<< c.INETime<<"IsQryControl"<< c.IsQryControl<<"LoginRemark"<< c.LoginRemark<<"Password"<< c.Password<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcLogoutAllField& c)
{
return os<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"SystemName"<< c.SystemName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcFrontStatusField& c)
{
return os<<"FrontID"<< c.FrontID<<"LastReportDate"<< c.LastReportDate<<"LastReportTime"<< c.LastReportTime<<"IsActive"<< c.IsActive;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcUserPasswordUpdateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"OldPassword"<< c.OldPassword<<"NewPassword"<< c.NewPassword;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OrderRef"<< c.OrderRef<<"UserID"<< c.UserID<<"OrderPriceType"<< c.OrderPriceType<<"Direction"<< c.Direction<<"CombOffsetFlag"<< c.CombOffsetFlag<<"CombHedgeFlag"<< c.CombHedgeFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeTotalOriginal"<< c.VolumeTotalOriginal<<"TimeCondition"<< c.TimeCondition<<"GTDDate"<< c.GTDDate<<"VolumeCondition"<< c.VolumeCondition<<"MinVolume"<< c.MinVolume<<"ContingentCondition"<< c.ContingentCondition<<"StopPrice"<< c.StopPrice<<"ForceCloseReason"<< c.ForceCloseReason<<"IsAutoSuspend"<< c.IsAutoSuspend<<"BusinessUnit"<< c.BusinessUnit<<"RequestID"<< c.RequestID<<"UserForceClose"<< c.UserForceClose<<"IsSwapOrder"<< c.IsSwapOrder<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OrderRef"<< c.OrderRef<<"UserID"<< c.UserID<<"OrderPriceType"<< c.OrderPriceType<<"Direction"<< c.Direction<<"CombOffsetFlag"<< c.CombOffsetFlag<<"CombHedgeFlag"<< c.CombHedgeFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeTotalOriginal"<< c.VolumeTotalOriginal<<"TimeCondition"<< c.TimeCondition<<"GTDDate"<< c.GTDDate<<"VolumeCondition"<< c.VolumeCondition<<"MinVolume"<< c.MinVolume<<"ContingentCondition"<< c.ContingentCondition<<"StopPrice"<< c.StopPrice<<"ForceCloseReason"<< c.ForceCloseReason<<"IsAutoSuspend"<< c.IsAutoSuspend<<"BusinessUnit"<< c.BusinessUnit<<"RequestID"<< c.RequestID<<"OrderLocalID"<< c.OrderLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OrderSysID"<< c.OrderSysID<<"OrderSource"<< c.OrderSource<<"OrderStatus"<< c.OrderStatus<<"OrderType"<< c.OrderType<<"VolumeTraded"<< c.VolumeTraded<<"VolumeTotal"<< c.VolumeTotal<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"ActiveTime"<< c.ActiveTime<<"SuspendTime"<< c.SuspendTime<<"UpdateTime"<< c.UpdateTime<<"CancelTime"<< c.CancelTime<<"ActiveTraderID"<< c.ActiveTraderID<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"UserProductInfo"<< c.UserProductInfo<<"StatusMsg"<< c.StatusMsg<<"UserForceClose"<< c.UserForceClose<<"ActiveUserID"<< c.ActiveUserID<<"BrokerOrderSeq"<< c.BrokerOrderSeq<<"RelativeOrderSysID"<< c.RelativeOrderSysID<<"ZCETotalTradedVolume"<< c.ZCETotalTradedVolume<<"IsSwapOrder"<< c.IsSwapOrder<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"reserve3"<< c.reserve3<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeOrderField& c)
{
return os<<"OrderPriceType"<< c.OrderPriceType<<"Direction"<< c.Direction<<"CombOffsetFlag"<< c.CombOffsetFlag<<"CombHedgeFlag"<< c.CombHedgeFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeTotalOriginal"<< c.VolumeTotalOriginal<<"TimeCondition"<< c.TimeCondition<<"GTDDate"<< c.GTDDate<<"VolumeCondition"<< c.VolumeCondition<<"MinVolume"<< c.MinVolume<<"ContingentCondition"<< c.ContingentCondition<<"StopPrice"<< c.StopPrice<<"ForceCloseReason"<< c.ForceCloseReason<<"IsAutoSuspend"<< c.IsAutoSuspend<<"BusinessUnit"<< c.BusinessUnit<<"RequestID"<< c.RequestID<<"OrderLocalID"<< c.OrderLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OrderSysID"<< c.OrderSysID<<"OrderSource"<< c.OrderSource<<"OrderStatus"<< c.OrderStatus<<"OrderType"<< c.OrderType<<"VolumeTraded"<< c.VolumeTraded<<"VolumeTotal"<< c.VolumeTotal<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"ActiveTime"<< c.ActiveTime<<"SuspendTime"<< c.SuspendTime<<"UpdateTime"<< c.UpdateTime<<"CancelTime"<< c.CancelTime<<"ActiveTraderID"<< c.ActiveTraderID<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"BranchID"<< c.BranchID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeOrderInsertErrorField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderLocalID"<< c.OrderLocalID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OrderActionRef"<< c.OrderActionRef<<"OrderRef"<< c.OrderRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"ActionFlag"<< c.ActionFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeChange"<< c.VolumeChange<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OrderActionRef"<< c.OrderActionRef<<"OrderRef"<< c.OrderRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"ActionFlag"<< c.ActionFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeChange"<< c.VolumeChange<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderLocalID"<< c.OrderLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"StatusMsg"<< c.StatusMsg<<"reserve1"<< c.reserve1<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeOrderActionField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"ActionFlag"<< c.ActionFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeChange"<< c.VolumeChange<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderLocalID"<< c.OrderLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"BranchID"<< c.BranchID<<"reserve1"<< c.reserve1<<"MacAddress"<< c.MacAddress<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeOrderActionErrorField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderLocalID"<< c.OrderLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeTradeField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"TradeID"<< c.TradeID<<"Direction"<< c.Direction<<"OrderSysID"<< c.OrderSysID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"TradingRole"<< c.TradingRole<<"reserve1"<< c.reserve1<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"Price"<< c.Price<<"Volume"<< c.Volume<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"TradeType"<< c.TradeType<<"PriceSource"<< c.PriceSource<<"TraderID"<< c.TraderID<<"OrderLocalID"<< c.OrderLocalID<<"ClearingPartID"<< c.ClearingPartID<<"BusinessUnit"<< c.BusinessUnit<<"SequenceNo"<< c.SequenceNo<<"TradeSource"<< c.TradeSource<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OrderRef"<< c.OrderRef<<"UserID"<< c.UserID<<"ExchangeID"<< c.ExchangeID<<"TradeID"<< c.TradeID<<"Direction"<< c.Direction<<"OrderSysID"<< c.OrderSysID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"TradingRole"<< c.TradingRole<<"reserve2"<< c.reserve2<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"Price"<< c.Price<<"Volume"<< c.Volume<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"TradeType"<< c.TradeType<<"PriceSource"<< c.PriceSource<<"TraderID"<< c.TraderID<<"OrderLocalID"<< c.OrderLocalID<<"ClearingPartID"<< c.ClearingPartID<<"BusinessUnit"<< c.BusinessUnit<<"SequenceNo"<< c.SequenceNo<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"BrokerOrderSeq"<< c.BrokerOrderSeq<<"TradeSource"<< c.TradeSource<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcUserSessionField& c)
{
return os<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"LoginDate"<< c.LoginDate<<"LoginTime"<< c.LoginTime<<"reserve1"<< c.reserve1<<"UserProductInfo"<< c.UserProductInfo<<"InterfaceProductInfo"<< c.InterfaceProductInfo<<"ProtocolInfo"<< c.ProtocolInfo<<"MacAddress"<< c.MacAddress<<"LoginRemark"<< c.LoginRemark<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryMaxOrderVolumeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"Direction"<< c.Direction<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"MaxVolume"<< c.MaxVolume<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSettlementInfoConfirmField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ConfirmDate"<< c.ConfirmDate<<"ConfirmTime"<< c.ConfirmTime<<"SettlementID"<< c.SettlementID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDepositField& c)
{
return os<<"DepositSeqNo"<< c.DepositSeqNo<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"Deposit"<< c.Deposit<<"IsForce"<< c.IsForce<<"CurrencyID"<< c.CurrencyID<<"IsFromSopt"<< c.IsFromSopt<<"TradingPassword"<< c.TradingPassword;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncFundMortgageField& c)
{
return os<<"MortgageSeqNo"<< c.MortgageSeqNo<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"FromCurrencyID"<< c.FromCurrencyID<<"MortgageAmount"<< c.MortgageAmount<<"ToCurrencyID"<< c.ToCurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerSyncField& c)
{
return os<<"BrokerID"<< c.BrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingInvestorField& c)
{
return os<<"InvestorID"<< c.InvestorID<<"BrokerID"<< c.BrokerID<<"InvestorGroupID"<< c.InvestorGroupID<<"InvestorName"<< c.InvestorName<<"IdentifiedCardType"<< c.IdentifiedCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"IsActive"<< c.IsActive<<"Telephone"<< c.Telephone<<"Address"<< c.Address<<"OpenDate"<< c.OpenDate<<"Mobile"<< c.Mobile<<"CommModelID"<< c.CommModelID<<"MarginModelID"<< c.MarginModelID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingTradingCodeField& c)
{
return os<<"InvestorID"<< c.InvestorID<<"BrokerID"<< c.BrokerID<<"ExchangeID"<< c.ExchangeID<<"ClientID"<< c.ClientID<<"IsActive"<< c.IsActive<<"ClientIDType"<< c.ClientIDType;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingInvestorGroupField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorGroupID"<< c.InvestorGroupID<<"InvestorGroupName"<< c.InvestorGroupName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingTradingAccountField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"PreMortgage"<< c.PreMortgage<<"PreCredit"<< c.PreCredit<<"PreDeposit"<< c.PreDeposit<<"PreBalance"<< c.PreBalance<<"PreMargin"<< c.PreMargin<<"InterestBase"<< c.InterestBase<<"Interest"<< c.Interest<<"Deposit"<< c.Deposit<<"Withdraw"<< c.Withdraw<<"FrozenMargin"<< c.FrozenMargin<<"FrozenCash"<< c.FrozenCash<<"FrozenCommission"<< c.FrozenCommission<<"CurrMargin"<< c.CurrMargin<<"CashIn"<< c.CashIn<<"Commission"<< c.Commission<<"CloseProfit"<< c.CloseProfit<<"PositionProfit"<< c.PositionProfit<<"Balance"<< c.Balance<<"Available"<< c.Available<<"WithdrawQuota"<< c.WithdrawQuota<<"Reserve"<< c.Reserve<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"Credit"<< c.Credit<<"Mortgage"<< c.Mortgage<<"ExchangeMargin"<< c.ExchangeMargin<<"DeliveryMargin"<< c.DeliveryMargin<<"ExchangeDeliveryMargin"<< c.ExchangeDeliveryMargin<<"ReserveBalance"<< c.ReserveBalance<<"CurrencyID"<< c.CurrencyID<<"PreFundMortgageIn"<< c.PreFundMortgageIn<<"PreFundMortgageOut"<< c.PreFundMortgageOut<<"FundMortgageIn"<< c.FundMortgageIn<<"FundMortgageOut"<< c.FundMortgageOut<<"FundMortgageAvailable"<< c.FundMortgageAvailable<<"MortgageableFund"<< c.MortgageableFund<<"SpecProductMargin"<< c.SpecProductMargin<<"SpecProductFrozenMargin"<< c.SpecProductFrozenMargin<<"SpecProductCommission"<< c.SpecProductCommission<<"SpecProductFrozenCommission"<< c.SpecProductFrozenCommission<<"SpecProductPositionProfit"<< c.SpecProductPositionProfit<<"SpecProductCloseProfit"<< c.SpecProductCloseProfit<<"SpecProductPositionProfitByAlg"<< c.SpecProductPositionProfitByAlg<<"SpecProductExchangeMargin"<< c.SpecProductExchangeMargin<<"FrozenSwap"<< c.FrozenSwap<<"RemainSwap"<< c.RemainSwap;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingInvestorPositionField& c)
{
return os<<"reserve1"<< c.reserve1<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"PosiDirection"<< c.PosiDirection<<"HedgeFlag"<< c.HedgeFlag<<"PositionDate"<< c.PositionDate<<"YdPosition"<< c.YdPosition<<"Position"<< c.Position<<"LongFrozen"<< c.LongFrozen<<"ShortFrozen"<< c.ShortFrozen<<"LongFrozenAmount"<< c.LongFrozenAmount<<"ShortFrozenAmount"<< c.ShortFrozenAmount<<"OpenVolume"<< c.OpenVolume<<"CloseVolume"<< c.CloseVolume<<"OpenAmount"<< c.OpenAmount<<"CloseAmount"<< c.CloseAmount<<"PositionCost"<< c.PositionCost<<"PreMargin"<< c.PreMargin<<"UseMargin"<< c.UseMargin<<"FrozenMargin"<< c.FrozenMargin<<"FrozenCash"<< c.FrozenCash<<"FrozenCommission"<< c.FrozenCommission<<"CashIn"<< c.CashIn<<"Commission"<< c.Commission<<"CloseProfit"<< c.CloseProfit<<"PositionProfit"<< c.PositionProfit<<"PreSettlementPrice"<< c.PreSettlementPrice<<"SettlementPrice"<< c.SettlementPrice<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OpenCost"<< c.OpenCost<<"ExchangeMargin"<< c.ExchangeMargin<<"CombPosition"<< c.CombPosition<<"CombLongFrozen"<< c.CombLongFrozen<<"CombShortFrozen"<< c.CombShortFrozen<<"CloseProfitByDate"<< c.CloseProfitByDate<<"CloseProfitByTrade"<< c.CloseProfitByTrade<<"TodayPosition"<< c.TodayPosition<<"MarginRateByMoney"<< c.MarginRateByMoney<<"MarginRateByVolume"<< c.MarginRateByVolume<<"StrikeFrozen"<< c.StrikeFrozen<<"StrikeFrozenAmount"<< c.StrikeFrozenAmount<<"AbandonFrozen"<< c.AbandonFrozen<<"ExchangeID"<< c.ExchangeID<<"YdStrikeFrozen"<< c.YdStrikeFrozen<<"InvestUnitID"<< c.InvestUnitID<<"PositionCostOffset"<< c.PositionCostOffset<<"TasPosition"<< c.TasPosition<<"TasPositionCost"<< c.TasPositionCost<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingInstrumentMarginRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"IsRelative"<< c.IsRelative<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingInstrumentCommissionRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OpenRatioByMoney"<< c.OpenRatioByMoney<<"OpenRatioByVolume"<< c.OpenRatioByVolume<<"CloseRatioByMoney"<< c.CloseRatioByMoney<<"CloseRatioByVolume"<< c.CloseRatioByVolume<<"CloseTodayRatioByMoney"<< c.CloseTodayRatioByMoney<<"CloseTodayRatioByVolume"<< c.CloseTodayRatioByVolume<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncingInstrumentTradingRightField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"TradingRight"<< c.TradingRight<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"InsertTimeStart"<< c.InsertTimeStart<<"InsertTimeEnd"<< c.InsertTimeEnd<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTradeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"TradeID"<< c.TradeID<<"TradeTimeStart"<< c.TradeTimeStart<<"TradeTimeEnd"<< c.TradeTimeEnd<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInvestorPositionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTradingAccountField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"CurrencyID"<< c.CurrencyID<<"BizType"<< c.BizType<<"AccountID"<< c.AccountID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInvestorField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTradingCodeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID<<"ClientID"<< c.ClientID<<"ClientIDType"<< c.ClientIDType<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInvestorGroupField& c)
{
return os<<"BrokerID"<< c.BrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInstrumentMarginRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInstrumentCommissionRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInstrumentTradingRightField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBrokerField& c)
{
return os<<"BrokerID"<< c.BrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTraderField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"TraderID"<< c.TraderID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySuperUserFunctionField& c)
{
return os<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryUserSessionField& c)
{
return os<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryPartBrokerField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"BrokerID"<< c.BrokerID<<"ParticipantID"<< c.ParticipantID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryFrontStatusField& c)
{
return os<<"FrontID"<< c.FrontID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeOrderField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeOrderActionField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySuperUserField& c)
{
return os<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeField& c)
{
return os<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryProductField& c)
{
return os<<"reserve1"<< c.reserve1<<"ProductClass"<< c.ProductClass<<"ExchangeID"<< c.ExchangeID<<"ProductID"<< c.ProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInstrumentField& c)
{
return os<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"reserve2"<< c.reserve2<<"reserve3"<< c.reserve3<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"ProductID"<< c.ProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryDepthMarketDataField& c)
{
return os<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBrokerUserField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBrokerUserFunctionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTraderOfferField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"TraderID"<< c.TraderID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySyncDepositField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"DepositSeqNo"<< c.DepositSeqNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySettlementInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"TradingDay"<< c.TradingDay<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeMarginRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeMarginRateAdjustField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"FromCurrencyID"<< c.FromCurrencyID<<"ToCurrencyID"<< c.ToCurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySyncFundMortgageField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"MortgageSeqNo"<< c.MortgageSeqNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryHisOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"InsertTimeStart"<< c.InsertTimeStart<<"InsertTimeEnd"<< c.InsertTimeEnd<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionInstrMiniMarginField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"MinMargin"<< c.MinMargin<<"ValueMethod"<< c.ValueMethod<<"IsRelative"<< c.IsRelative<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionInstrMarginAdjustField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"SShortMarginRatioByMoney"<< c.SShortMarginRatioByMoney<<"SShortMarginRatioByVolume"<< c.SShortMarginRatioByVolume<<"HShortMarginRatioByMoney"<< c.HShortMarginRatioByMoney<<"HShortMarginRatioByVolume"<< c.HShortMarginRatioByVolume<<"AShortMarginRatioByMoney"<< c.AShortMarginRatioByMoney<<"AShortMarginRatioByVolume"<< c.AShortMarginRatioByVolume<<"IsRelative"<< c.IsRelative<<"MShortMarginRatioByMoney"<< c.MShortMarginRatioByMoney<<"MShortMarginRatioByVolume"<< c.MShortMarginRatioByVolume<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionInstrCommRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OpenRatioByMoney"<< c.OpenRatioByMoney<<"OpenRatioByVolume"<< c.OpenRatioByVolume<<"CloseRatioByMoney"<< c.CloseRatioByMoney<<"CloseRatioByVolume"<< c.CloseRatioByVolume<<"CloseTodayRatioByMoney"<< c.CloseTodayRatioByMoney<<"CloseTodayRatioByVolume"<< c.CloseTodayRatioByVolume<<"StrikeRatioByMoney"<< c.StrikeRatioByMoney<<"StrikeRatioByVolume"<< c.StrikeRatioByVolume<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionInstrTradeCostField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"FixedMargin"<< c.FixedMargin<<"MiniMargin"<< c.MiniMargin<<"Royalty"<< c.Royalty<<"ExchFixedMargin"<< c.ExchFixedMargin<<"ExchMiniMargin"<< c.ExchMiniMargin<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryOptionInstrTradeCostField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"InputPrice"<< c.InputPrice<<"UnderlyingPrice"<< c.UnderlyingPrice<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryOptionInstrCommRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcIndexPriceField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"ClosePrice"<< c.ClosePrice<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputExecOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExecOrderRef"<< c.ExecOrderRef<<"UserID"<< c.UserID<<"Volume"<< c.Volume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"ActionType"<< c.ActionType<<"PosiDirection"<< c.PosiDirection<<"ReservePositionFlag"<< c.ReservePositionFlag<<"CloseFlag"<< c.CloseFlag<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputExecOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExecOrderActionRef"<< c.ExecOrderActionRef<<"ExecOrderRef"<< c.ExecOrderRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"ExecOrderSysID"<< c.ExecOrderSysID<<"ActionFlag"<< c.ActionFlag<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExecOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExecOrderRef"<< c.ExecOrderRef<<"UserID"<< c.UserID<<"Volume"<< c.Volume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"ActionType"<< c.ActionType<<"PosiDirection"<< c.PosiDirection<<"ReservePositionFlag"<< c.ReservePositionFlag<<"CloseFlag"<< c.CloseFlag<<"ExecOrderLocalID"<< c.ExecOrderLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"ExecOrderSysID"<< c.ExecOrderSysID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"CancelTime"<< c.CancelTime<<"ExecResult"<< c.ExecResult<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"UserProductInfo"<< c.UserProductInfo<<"StatusMsg"<< c.StatusMsg<<"ActiveUserID"<< c.ActiveUserID<<"BrokerExecOrderSeq"<< c.BrokerExecOrderSeq<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"reserve3"<< c.reserve3<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExecOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExecOrderActionRef"<< c.ExecOrderActionRef<<"ExecOrderRef"<< c.ExecOrderRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"ExecOrderSysID"<< c.ExecOrderSysID<<"ActionFlag"<< c.ActionFlag<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"ExecOrderLocalID"<< c.ExecOrderLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"ActionType"<< c.ActionType<<"StatusMsg"<< c.StatusMsg<<"reserve1"<< c.reserve1<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExecOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"ExecOrderSysID"<< c.ExecOrderSysID<<"InsertTimeStart"<< c.InsertTimeStart<<"InsertTimeEnd"<< c.InsertTimeEnd<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeExecOrderField& c)
{
return os<<"Volume"<< c.Volume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"ActionType"<< c.ActionType<<"PosiDirection"<< c.PosiDirection<<"ReservePositionFlag"<< c.ReservePositionFlag<<"CloseFlag"<< c.CloseFlag<<"ExecOrderLocalID"<< c.ExecOrderLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"ExecOrderSysID"<< c.ExecOrderSysID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"CancelTime"<< c.CancelTime<<"ExecResult"<< c.ExecResult<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"BranchID"<< c.BranchID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeExecOrderField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExecOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeExecOrderActionField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ExecOrderSysID"<< c.ExecOrderSysID<<"ActionFlag"<< c.ActionFlag<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"ExecOrderLocalID"<< c.ExecOrderLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"ActionType"<< c.ActionType<<"BranchID"<< c.BranchID<<"reserve1"<< c.reserve1<<"MacAddress"<< c.MacAddress<<"reserve2"<< c.reserve2<<"Volume"<< c.Volume<<"IPAddress"<< c.IPAddress<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeExecOrderActionField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcErrExecOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExecOrderRef"<< c.ExecOrderRef<<"UserID"<< c.UserID<<"Volume"<< c.Volume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"ActionType"<< c.ActionType<<"PosiDirection"<< c.PosiDirection<<"ReservePositionFlag"<< c.ReservePositionFlag<<"CloseFlag"<< c.CloseFlag<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryErrExecOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcErrExecOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExecOrderActionRef"<< c.ExecOrderActionRef<<"ExecOrderRef"<< c.ExecOrderRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"ExecOrderSysID"<< c.ExecOrderSysID<<"ActionFlag"<< c.ActionFlag<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryErrExecOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionInstrTradingRightField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"Direction"<< c.Direction<<"TradingRight"<< c.TradingRight<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryOptionInstrTradingRightField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"Direction"<< c.Direction<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputForQuoteField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ForQuoteRef"<< c.ForQuoteRef<<"UserID"<< c.UserID<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcForQuoteField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ForQuoteRef"<< c.ForQuoteRef<<"UserID"<< c.UserID<<"ForQuoteLocalID"<< c.ForQuoteLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"ForQuoteStatus"<< c.ForQuoteStatus<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"StatusMsg"<< c.StatusMsg<<"ActiveUserID"<< c.ActiveUserID<<"BrokerForQutoSeq"<< c.BrokerForQutoSeq<<"InvestUnitID"<< c.InvestUnitID<<"reserve3"<< c.reserve3<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryForQuoteField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InsertTimeStart"<< c.InsertTimeStart<<"InsertTimeEnd"<< c.InsertTimeEnd<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeForQuoteField& c)
{
return os<<"ForQuoteLocalID"<< c.ForQuoteLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"ForQuoteStatus"<< c.ForQuoteStatus<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeForQuoteField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputQuoteField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"QuoteRef"<< c.QuoteRef<<"UserID"<< c.UserID<<"AskPrice"<< c.AskPrice<<"BidPrice"<< c.BidPrice<<"AskVolume"<< c.AskVolume<<"BidVolume"<< c.BidVolume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"AskOffsetFlag"<< c.AskOffsetFlag<<"BidOffsetFlag"<< c.BidOffsetFlag<<"AskHedgeFlag"<< c.AskHedgeFlag<<"BidHedgeFlag"<< c.BidHedgeFlag<<"AskOrderRef"<< c.AskOrderRef<<"BidOrderRef"<< c.BidOrderRef<<"ForQuoteSysID"<< c.ForQuoteSysID<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress<<"ReplaceSysID"<< c.ReplaceSysID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputQuoteActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"QuoteActionRef"<< c.QuoteActionRef<<"QuoteRef"<< c.QuoteRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"QuoteSysID"<< c.QuoteSysID<<"ActionFlag"<< c.ActionFlag<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"InvestUnitID"<< c.InvestUnitID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQuoteField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"QuoteRef"<< c.QuoteRef<<"UserID"<< c.UserID<<"AskPrice"<< c.AskPrice<<"BidPrice"<< c.BidPrice<<"AskVolume"<< c.AskVolume<<"BidVolume"<< c.BidVolume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"AskOffsetFlag"<< c.AskOffsetFlag<<"BidOffsetFlag"<< c.BidOffsetFlag<<"AskHedgeFlag"<< c.AskHedgeFlag<<"BidHedgeFlag"<< c.BidHedgeFlag<<"QuoteLocalID"<< c.QuoteLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"NotifySequence"<< c.NotifySequence<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"QuoteSysID"<< c.QuoteSysID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"CancelTime"<< c.CancelTime<<"QuoteStatus"<< c.QuoteStatus<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"AskOrderSysID"<< c.AskOrderSysID<<"BidOrderSysID"<< c.BidOrderSysID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"UserProductInfo"<< c.UserProductInfo<<"StatusMsg"<< c.StatusMsg<<"ActiveUserID"<< c.ActiveUserID<<"BrokerQuoteSeq"<< c.BrokerQuoteSeq<<"AskOrderRef"<< c.AskOrderRef<<"BidOrderRef"<< c.BidOrderRef<<"ForQuoteSysID"<< c.ForQuoteSysID<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"reserve3"<< c.reserve3<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress<<"ReplaceSysID"<< c.ReplaceSysID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQuoteActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"QuoteActionRef"<< c.QuoteActionRef<<"QuoteRef"<< c.QuoteRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"QuoteSysID"<< c.QuoteSysID<<"ActionFlag"<< c.ActionFlag<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"QuoteLocalID"<< c.QuoteLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"StatusMsg"<< c.StatusMsg<<"reserve1"<< c.reserve1<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryQuoteField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"QuoteSysID"<< c.QuoteSysID<<"InsertTimeStart"<< c.InsertTimeStart<<"InsertTimeEnd"<< c.InsertTimeEnd<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeQuoteField& c)
{
return os<<"AskPrice"<< c.AskPrice<<"BidPrice"<< c.BidPrice<<"AskVolume"<< c.AskVolume<<"BidVolume"<< c.BidVolume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"AskOffsetFlag"<< c.AskOffsetFlag<<"BidOffsetFlag"<< c.BidOffsetFlag<<"AskHedgeFlag"<< c.AskHedgeFlag<<"BidHedgeFlag"<< c.BidHedgeFlag<<"QuoteLocalID"<< c.QuoteLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"NotifySequence"<< c.NotifySequence<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"QuoteSysID"<< c.QuoteSysID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"CancelTime"<< c.CancelTime<<"QuoteStatus"<< c.QuoteStatus<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"AskOrderSysID"<< c.AskOrderSysID<<"BidOrderSysID"<< c.BidOrderSysID<<"ForQuoteSysID"<< c.ForQuoteSysID<<"BranchID"<< c.BranchID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeQuoteField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryQuoteActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeQuoteActionField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"QuoteSysID"<< c.QuoteSysID<<"ActionFlag"<< c.ActionFlag<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"QuoteLocalID"<< c.QuoteLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"MacAddress"<< c.MacAddress<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeQuoteActionField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionInstrDeltaField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"Delta"<< c.Delta<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcForQuoteRspField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"reserve1"<< c.reserve1<<"ForQuoteSysID"<< c.ForQuoteSysID<<"ForQuoteTime"<< c.ForQuoteTime<<"ActionDay"<< c.ActionDay<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcStrikeOffsetField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"Offset"<< c.Offset<<"OffsetType"<< c.OffsetType<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryStrikeOffsetField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputBatchOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OrderActionRef"<< c.OrderActionRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"UserID"<< c.UserID<<"InvestUnitID"<< c.InvestUnitID<<"reserve1"<< c.reserve1<<"MacAddress"<< c.MacAddress<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBatchOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OrderActionRef"<< c.OrderActionRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"StatusMsg"<< c.StatusMsg<<"InvestUnitID"<< c.InvestUnitID<<"reserve1"<< c.reserve1<<"MacAddress"<< c.MacAddress<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeBatchOrderActionField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"MacAddress"<< c.MacAddress<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBatchOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCombInstrumentGuardField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"GuarantRatio"<< c.GuarantRatio<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCombInstrumentGuardField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputCombActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"CombActionRef"<< c.CombActionRef<<"UserID"<< c.UserID<<"Direction"<< c.Direction<<"Volume"<< c.Volume<<"CombDirection"<< c.CombDirection<<"HedgeFlag"<< c.HedgeFlag<<"ExchangeID"<< c.ExchangeID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InvestUnitID"<< c.InvestUnitID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCombActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"CombActionRef"<< c.CombActionRef<<"UserID"<< c.UserID<<"Direction"<< c.Direction<<"Volume"<< c.Volume<<"CombDirection"<< c.CombDirection<<"HedgeFlag"<< c.HedgeFlag<<"ActionLocalID"<< c.ActionLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"ActionStatus"<< c.ActionStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"SequenceNo"<< c.SequenceNo<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"UserProductInfo"<< c.UserProductInfo<<"StatusMsg"<< c.StatusMsg<<"reserve3"<< c.reserve3<<"MacAddress"<< c.MacAddress<<"ComTradeID"<< c.ComTradeID<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCombActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeCombActionField& c)
{
return os<<"Direction"<< c.Direction<<"Volume"<< c.Volume<<"CombDirection"<< c.CombDirection<<"HedgeFlag"<< c.HedgeFlag<<"ActionLocalID"<< c.ActionLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"ActionStatus"<< c.ActionStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"SequenceNo"<< c.SequenceNo<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ComTradeID"<< c.ComTradeID<<"BranchID"<< c.BranchID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeCombActionField& c)
{
return os<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcProductExchRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"QuoteCurrencyID"<< c.QuoteCurrencyID<<"ExchangeRate"<< c.ExchangeRate<<"ExchangeID"<< c.ExchangeID<<"ProductID"<< c.ProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryProductExchRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"ProductID"<< c.ProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryForQuoteParamField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcForQuoteParamField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"LastPrice"<< c.LastPrice<<"PriceInterval"<< c.PriceInterval<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMMOptionInstrCommRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OpenRatioByMoney"<< c.OpenRatioByMoney<<"OpenRatioByVolume"<< c.OpenRatioByVolume<<"CloseRatioByMoney"<< c.CloseRatioByMoney<<"CloseRatioByVolume"<< c.CloseRatioByVolume<<"CloseTodayRatioByMoney"<< c.CloseTodayRatioByMoney<<"CloseTodayRatioByVolume"<< c.CloseTodayRatioByVolume<<"StrikeRatioByMoney"<< c.StrikeRatioByMoney<<"StrikeRatioByVolume"<< c.StrikeRatioByVolume<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryMMOptionInstrCommRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMMInstrumentCommissionRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OpenRatioByMoney"<< c.OpenRatioByMoney<<"OpenRatioByVolume"<< c.OpenRatioByVolume<<"CloseRatioByMoney"<< c.CloseRatioByMoney<<"CloseRatioByVolume"<< c.CloseRatioByVolume<<"CloseTodayRatioByMoney"<< c.CloseTodayRatioByMoney<<"CloseTodayRatioByVolume"<< c.CloseTodayRatioByVolume<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryMMInstrumentCommissionRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentOrderCommRateField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"OrderCommByVolume"<< c.OrderCommByVolume<<"OrderActionCommByVolume"<< c.OrderActionCommByVolume<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID<<"OrderCommByTrade"<< c.OrderCommByTrade<<"OrderActionCommByTrade"<< c.OrderActionCommByTrade;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInstrumentOrderCommRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradeParamField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"TradeParamID"<< c.TradeParamID<<"TradeParamValue"<< c.TradeParamValue<<"Memo"<< c.Memo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentMarginRateULField& c)
{
return os<<"reserve1"<< c.reserve1<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcFutureLimitPosiParamField& c)
{
return os<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"SpecOpenVolume"<< c.SpecOpenVolume<<"ArbiOpenVolume"<< c.ArbiOpenVolume<<"OpenVolume"<< c.OpenVolume<<"ProductID"<< c.ProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcLoginForbiddenIPField& c)
{
return os<<"reserve1"<< c.reserve1<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcIPListField& c)
{
return os<<"reserve1"<< c.reserve1<<"IsWhite"<< c.IsWhite<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputOptionSelfCloseField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OptionSelfCloseRef"<< c.OptionSelfCloseRef<<"UserID"<< c.UserID<<"Volume"<< c.Volume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"HedgeFlag"<< c.HedgeFlag<<"OptSelfCloseFlag"<< c.OptSelfCloseFlag<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInputOptionSelfCloseActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OptionSelfCloseActionRef"<< c.OptionSelfCloseActionRef<<"OptionSelfCloseRef"<< c.OptionSelfCloseRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"OptionSelfCloseSysID"<< c.OptionSelfCloseSysID<<"ActionFlag"<< c.ActionFlag<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionSelfCloseField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OptionSelfCloseRef"<< c.OptionSelfCloseRef<<"UserID"<< c.UserID<<"Volume"<< c.Volume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"HedgeFlag"<< c.HedgeFlag<<"OptSelfCloseFlag"<< c.OptSelfCloseFlag<<"OptionSelfCloseLocalID"<< c.OptionSelfCloseLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OptionSelfCloseSysID"<< c.OptionSelfCloseSysID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"CancelTime"<< c.CancelTime<<"ExecResult"<< c.ExecResult<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"UserProductInfo"<< c.UserProductInfo<<"StatusMsg"<< c.StatusMsg<<"ActiveUserID"<< c.ActiveUserID<<"BrokerOptionSelfCloseSeq"<< c.BrokerOptionSelfCloseSeq<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"reserve3"<< c.reserve3<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOptionSelfCloseActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OptionSelfCloseActionRef"<< c.OptionSelfCloseActionRef<<"OptionSelfCloseRef"<< c.OptionSelfCloseRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"OptionSelfCloseSysID"<< c.OptionSelfCloseSysID<<"ActionFlag"<< c.ActionFlag<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OptionSelfCloseLocalID"<< c.OptionSelfCloseLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"StatusMsg"<< c.StatusMsg<<"reserve1"<< c.reserve1<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryOptionSelfCloseField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"OptionSelfCloseSysID"<< c.OptionSelfCloseSysID<<"InsertTimeStart"<< c.InsertTimeStart<<"InsertTimeEnd"<< c.InsertTimeEnd<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeOptionSelfCloseField& c)
{
return os<<"Volume"<< c.Volume<<"RequestID"<< c.RequestID<<"BusinessUnit"<< c.BusinessUnit<<"HedgeFlag"<< c.HedgeFlag<<"OptSelfCloseFlag"<< c.OptSelfCloseFlag<<"OptionSelfCloseLocalID"<< c.OptionSelfCloseLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve1"<< c.reserve1<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OptionSelfCloseSysID"<< c.OptionSelfCloseSysID<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"CancelTime"<< c.CancelTime<<"ExecResult"<< c.ExecResult<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"BranchID"<< c.BranchID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryOptionSelfCloseActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeOptionSelfCloseActionField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"OptionSelfCloseSysID"<< c.OptionSelfCloseSysID<<"ActionFlag"<< c.ActionFlag<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OptionSelfCloseLocalID"<< c.OptionSelfCloseLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"BranchID"<< c.BranchID<<"reserve1"<< c.reserve1<<"MacAddress"<< c.MacAddress<<"reserve2"<< c.reserve2<<"OptSelfCloseFlag"<< c.OptSelfCloseFlag<<"IPAddress"<< c.IPAddress<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDelaySwapField& c)
{
return os<<"DelaySwapSeqNo"<< c.DelaySwapSeqNo<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"FromCurrencyID"<< c.FromCurrencyID<<"FromAmount"<< c.FromAmount<<"FromFrozenSwap"<< c.FromFrozenSwap<<"FromRemainSwap"<< c.FromRemainSwap<<"ToCurrencyID"<< c.ToCurrencyID<<"ToAmount"<< c.ToAmount<<"IsManualSwap"<< c.IsManualSwap<<"IsAllRemainSetZero"<< c.IsAllRemainSetZero;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySyncDelaySwapField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"DelaySwapSeqNo"<< c.DelaySwapSeqNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestUnitField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"InvestUnitID"<< c.InvestUnitID<<"InvestorUnitName"<< c.InvestorUnitName<<"InvestorGroupID"<< c.InvestorGroupID<<"CommModelID"<< c.CommModelID<<"MarginModelID"<< c.MarginModelID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInvestUnitField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSecAgentCheckModeField& c)
{
return os<<"InvestorID"<< c.InvestorID<<"BrokerID"<< c.BrokerID<<"CurrencyID"<< c.CurrencyID<<"BrokerSecAgentID"<< c.BrokerSecAgentID<<"CheckSelfAccount"<< c.CheckSelfAccount;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSecAgentTradeInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"BrokerSecAgentID"<< c.BrokerSecAgentID<<"InvestorID"<< c.InvestorID<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"reserve2"<< c.reserve2<<"LastPrice"<< c.LastPrice<<"PreSettlementPrice"<< c.PreSettlementPrice<<"PreClosePrice"<< c.PreClosePrice<<"PreOpenInterest"<< c.PreOpenInterest<<"OpenPrice"<< c.OpenPrice<<"HighestPrice"<< c.HighestPrice<<"LowestPrice"<< c.LowestPrice<<"Volume"<< c.Volume<<"Turnover"<< c.Turnover<<"OpenInterest"<< c.OpenInterest<<"ClosePrice"<< c.ClosePrice<<"SettlementPrice"<< c.SettlementPrice<<"UpperLimitPrice"<< c.UpperLimitPrice<<"LowerLimitPrice"<< c.LowerLimitPrice<<"PreDelta"<< c.PreDelta<<"CurrDelta"<< c.CurrDelta<<"UpdateTime"<< c.UpdateTime<<"UpdateMillisec"<< c.UpdateMillisec<<"ActionDay"<< c.ActionDay<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataBaseField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"PreSettlementPrice"<< c.PreSettlementPrice<<"PreClosePrice"<< c.PreClosePrice<<"PreOpenInterest"<< c.PreOpenInterest<<"PreDelta"<< c.PreDelta;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataStaticField& c)
{
return os<<"OpenPrice"<< c.OpenPrice<<"HighestPrice"<< c.HighestPrice<<"LowestPrice"<< c.LowestPrice<<"ClosePrice"<< c.ClosePrice<<"UpperLimitPrice"<< c.UpperLimitPrice<<"LowerLimitPrice"<< c.LowerLimitPrice<<"SettlementPrice"<< c.SettlementPrice<<"CurrDelta"<< c.CurrDelta;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataLastMatchField& c)
{
return os<<"LastPrice"<< c.LastPrice<<"Volume"<< c.Volume<<"Turnover"<< c.Turnover<<"OpenInterest"<< c.OpenInterest;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataBestPriceField& c)
{
return os<<"BidPrice1"<< c.BidPrice1<<"BidVolume1"<< c.BidVolume1<<"AskPrice1"<< c.AskPrice1<<"AskVolume1"<< c.AskVolume1;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataBid23Field& c)
{
return os<<"BidPrice2"<< c.BidPrice2<<"BidVolume2"<< c.BidVolume2<<"BidPrice3"<< c.BidPrice3<<"BidVolume3"<< c.BidVolume3;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataAsk23Field& c)
{
return os<<"AskPrice2"<< c.AskPrice2<<"AskVolume2"<< c.AskVolume2<<"AskPrice3"<< c.AskPrice3<<"AskVolume3"<< c.AskVolume3;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataBid45Field& c)
{
return os<<"BidPrice4"<< c.BidPrice4<<"BidVolume4"<< c.BidVolume4<<"BidPrice5"<< c.BidPrice5<<"BidVolume5"<< c.BidVolume5;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataAsk45Field& c)
{
return os<<"AskPrice4"<< c.AskPrice4<<"AskVolume4"<< c.AskVolume4<<"AskPrice5"<< c.AskPrice5<<"AskVolume5"<< c.AskVolume5;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataUpdateTimeField& c)
{
return os<<"reserve1"<< c.reserve1<<"UpdateTime"<< c.UpdateTime<<"UpdateMillisec"<< c.UpdateMillisec<<"ActionDay"<< c.ActionDay<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataBandingPriceField& c)
{
return os<<"BandingUpperPrice"<< c.BandingUpperPrice<<"BandingLowerPrice"<< c.BandingLowerPrice;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataExchangeField& c)
{
return os<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSpecificInstrumentField& c)
{
return os<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInstrumentStatusField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"reserve1"<< c.reserve1<<"SettlementGroupID"<< c.SettlementGroupID<<"reserve2"<< c.reserve2<<"InstrumentStatus"<< c.InstrumentStatus<<"TradingSegmentSN"<< c.TradingSegmentSN<<"EnterTime"<< c.EnterTime<<"EnterReason"<< c.EnterReason<<"ExchangeInstID"<< c.ExchangeInstID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInstrumentStatusField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"reserve1"<< c.reserve1<<"ExchangeInstID"<< c.ExchangeInstID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorAccountField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcPositionProfitAlgorithmField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"Algorithm"<< c.Algorithm<<"Memo"<< c.Memo<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcDiscountField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorRange"<< c.InvestorRange<<"InvestorID"<< c.InvestorID<<"Discount"<< c.Discount;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTransferBankField& c)
{
return os<<"BankID"<< c.BankID<<"BankBrchID"<< c.BankBrchID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferBankField& c)
{
return os<<"BankID"<< c.BankID<<"BankBrchID"<< c.BankBrchID<<"BankName"<< c.BankName<<"IsActive"<< c.IsActive;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInvestorPositionDetailField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorPositionDetailField& c)
{
return os<<"reserve1"<< c.reserve1<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"Direction"<< c.Direction<<"OpenDate"<< c.OpenDate<<"TradeID"<< c.TradeID<<"Volume"<< c.Volume<<"OpenPrice"<< c.OpenPrice<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"TradeType"<< c.TradeType<<"reserve2"<< c.reserve2<<"ExchangeID"<< c.ExchangeID<<"CloseProfitByDate"<< c.CloseProfitByDate<<"CloseProfitByTrade"<< c.CloseProfitByTrade<<"PositionProfitByDate"<< c.PositionProfitByDate<<"PositionProfitByTrade"<< c.PositionProfitByTrade<<"Margin"<< c.Margin<<"ExchMargin"<< c.ExchMargin<<"MarginRateByMoney"<< c.MarginRateByMoney<<"MarginRateByVolume"<< c.MarginRateByVolume<<"LastSettlementPrice"<< c.LastSettlementPrice<<"SettlementPrice"<< c.SettlementPrice<<"CloseVolume"<< c.CloseVolume<<"CloseAmount"<< c.CloseAmount<<"TimeFirstVolume"<< c.TimeFirstVolume<<"InvestUnitID"<< c.InvestUnitID<<"SpecPosiType"<< c.SpecPosiType<<"InstrumentID"<< c.InstrumentID<<"CombInstrumentID"<< c.CombInstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingAccountPasswordField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMDTraderOfferField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"TraderID"<< c.TraderID<<"ParticipantID"<< c.ParticipantID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"OrderLocalID"<< c.OrderLocalID<<"TraderConnectStatus"<< c.TraderConnectStatus<<"ConnectRequestDate"<< c.ConnectRequestDate<<"ConnectRequestTime"<< c.ConnectRequestTime<<"LastReportDate"<< c.LastReportDate<<"LastReportTime"<< c.LastReportTime<<"ConnectDate"<< c.ConnectDate<<"ConnectTime"<< c.ConnectTime<<"StartDate"<< c.StartDate<<"StartTime"<< c.StartTime<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"MaxTradeID"<< c.MaxTradeID<<"MaxOrderMessageReference"<< c.MaxOrderMessageReference;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryMDTraderOfferField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"TraderID"<< c.TraderID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryNoticeField& c)
{
return os<<"BrokerID"<< c.BrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcNoticeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"Content"<< c.Content<<"SequenceLabel"<< c.SequenceLabel;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcUserRightField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"UserRightType"<< c.UserRightType<<"IsForbidden"<< c.IsForbidden;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySettlementInfoConfirmField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcLoadSettlementInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerWithdrawAlgorithmField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"WithdrawAlgorithm"<< c.WithdrawAlgorithm<<"UsingRatio"<< c.UsingRatio<<"IncludeCloseProfit"<< c.IncludeCloseProfit<<"AllWithoutTrade"<< c.AllWithoutTrade<<"AvailIncludeCloseProfit"<< c.AvailIncludeCloseProfit<<"IsBrokerUserEvent"<< c.IsBrokerUserEvent<<"CurrencyID"<< c.CurrencyID<<"FundMortgageRatio"<< c.FundMortgageRatio<<"BalanceAlgorithm"<< c.BalanceAlgorithm;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingAccountPasswordUpdateV1Field& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OldPassword"<< c.OldPassword<<"NewPassword"<< c.NewPassword;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingAccountPasswordUpdateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"OldPassword"<< c.OldPassword<<"NewPassword"<< c.NewPassword<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCombinationLegField& c)
{
return os<<"reserve1"<< c.reserve1<<"LegID"<< c.LegID<<"reserve2"<< c.reserve2<<"CombInstrumentID"<< c.CombInstrumentID<<"LegInstrumentID"<< c.LegInstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySyncStatusField& c)
{
return os<<"TradingDay"<< c.TradingDay;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCombinationLegField& c)
{
return os<<"reserve1"<< c.reserve1<<"LegID"<< c.LegID<<"reserve2"<< c.reserve2<<"Direction"<< c.Direction<<"LegMultiple"<< c.LegMultiple<<"ImplyLevel"<< c.ImplyLevel<<"CombInstrumentID"<< c.CombInstrumentID<<"LegInstrumentID"<< c.LegInstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncStatusField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"DataSyncStatus"<< c.DataSyncStatus;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryLinkManField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcLinkManField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"PersonType"<< c.PersonType<<"IdentifiedCardType"<< c.IdentifiedCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"PersonName"<< c.PersonName<<"Telephone"<< c.Telephone<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Priority"<< c.Priority<<"UOAZipCode"<< c.UOAZipCode<<"PersonFullName"<< c.PersonFullName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBrokerUserEventField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"UserEventType"<< c.UserEventType;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerUserEventField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"UserEventType"<< c.UserEventType<<"EventSequenceNo"<< c.EventSequenceNo<<"EventDate"<< c.EventDate<<"EventTime"<< c.EventTime<<"UserEventInfo"<< c.UserEventInfo<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryContractBankField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"BankID"<< c.BankID<<"BankBrchID"<< c.BankBrchID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcContractBankField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"BankID"<< c.BankID<<"BankBrchID"<< c.BankBrchID<<"BankName"<< c.BankName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorPositionCombineDetailField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"OpenDate"<< c.OpenDate<<"ExchangeID"<< c.ExchangeID<<"SettlementID"<< c.SettlementID<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ComTradeID"<< c.ComTradeID<<"TradeID"<< c.TradeID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"Direction"<< c.Direction<<"TotalAmt"<< c.TotalAmt<<"Margin"<< c.Margin<<"ExchMargin"<< c.ExchMargin<<"MarginRateByMoney"<< c.MarginRateByMoney<<"MarginRateByVolume"<< c.MarginRateByVolume<<"LegID"<< c.LegID<<"LegMultiple"<< c.LegMultiple<<"reserve2"<< c.reserve2<<"TradeGroupID"<< c.TradeGroupID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID<<"CombInstrumentID"<< c.CombInstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcParkedOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OrderRef"<< c.OrderRef<<"UserID"<< c.UserID<<"OrderPriceType"<< c.OrderPriceType<<"Direction"<< c.Direction<<"CombOffsetFlag"<< c.CombOffsetFlag<<"CombHedgeFlag"<< c.CombHedgeFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeTotalOriginal"<< c.VolumeTotalOriginal<<"TimeCondition"<< c.TimeCondition<<"GTDDate"<< c.GTDDate<<"VolumeCondition"<< c.VolumeCondition<<"MinVolume"<< c.MinVolume<<"ContingentCondition"<< c.ContingentCondition<<"StopPrice"<< c.StopPrice<<"ForceCloseReason"<< c.ForceCloseReason<<"IsAutoSuspend"<< c.IsAutoSuspend<<"BusinessUnit"<< c.BusinessUnit<<"RequestID"<< c.RequestID<<"UserForceClose"<< c.UserForceClose<<"ExchangeID"<< c.ExchangeID<<"ParkedOrderID"<< c.ParkedOrderID<<"UserType"<< c.UserType<<"Status"<< c.Status<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"IsSwapOrder"<< c.IsSwapOrder<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"ClientID"<< c.ClientID<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcParkedOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OrderActionRef"<< c.OrderActionRef<<"OrderRef"<< c.OrderRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"ActionFlag"<< c.ActionFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeChange"<< c.VolumeChange<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"ParkedOrderActionID"<< c.ParkedOrderActionID<<"UserType"<< c.UserType<<"Status"<< c.Status<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryParkedOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryParkedOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRemoveParkedOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ParkedOrderID"<< c.ParkedOrderID<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRemoveParkedOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ParkedOrderActionID"<< c.ParkedOrderActionID<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorWithdrawAlgorithmField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorRange"<< c.InvestorRange<<"InvestorID"<< c.InvestorID<<"UsingRatio"<< c.UsingRatio<<"CurrencyID"<< c.CurrencyID<<"FundMortgageRatio"<< c.FundMortgageRatio;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInvestorPositionCombineDetailField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"CombInstrumentID"<< c.CombInstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarketDataAveragePriceField& c)
{
return os<<"AveragePrice"<< c.AveragePrice;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcVerifyInvestorPasswordField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"Password"<< c.Password;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcUserIPField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"IPAddress"<< c.IPAddress<<"IPMask"<< c.IPMask;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingNoticeInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"SendTime"<< c.SendTime<<"FieldContent"<< c.FieldContent<<"SequenceSeries"<< c.SequenceSeries<<"SequenceNo"<< c.SequenceNo<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingNoticeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorRange"<< c.InvestorRange<<"InvestorID"<< c.InvestorID<<"SequenceSeries"<< c.SequenceSeries<<"UserID"<< c.UserID<<"SendTime"<< c.SendTime<<"SequenceNo"<< c.SequenceNo<<"FieldContent"<< c.FieldContent<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTradingNoticeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryErrOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcErrOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OrderRef"<< c.OrderRef<<"UserID"<< c.UserID<<"OrderPriceType"<< c.OrderPriceType<<"Direction"<< c.Direction<<"CombOffsetFlag"<< c.CombOffsetFlag<<"CombHedgeFlag"<< c.CombHedgeFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeTotalOriginal"<< c.VolumeTotalOriginal<<"TimeCondition"<< c.TimeCondition<<"GTDDate"<< c.GTDDate<<"VolumeCondition"<< c.VolumeCondition<<"MinVolume"<< c.MinVolume<<"ContingentCondition"<< c.ContingentCondition<<"StopPrice"<< c.StopPrice<<"ForceCloseReason"<< c.ForceCloseReason<<"IsAutoSuspend"<< c.IsAutoSuspend<<"BusinessUnit"<< c.BusinessUnit<<"RequestID"<< c.RequestID<<"UserForceClose"<< c.UserForceClose<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"IsSwapOrder"<< c.IsSwapOrder<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcErrorConditionalOrderField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"OrderRef"<< c.OrderRef<<"UserID"<< c.UserID<<"OrderPriceType"<< c.OrderPriceType<<"Direction"<< c.Direction<<"CombOffsetFlag"<< c.CombOffsetFlag<<"CombHedgeFlag"<< c.CombHedgeFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeTotalOriginal"<< c.VolumeTotalOriginal<<"TimeCondition"<< c.TimeCondition<<"GTDDate"<< c.GTDDate<<"VolumeCondition"<< c.VolumeCondition<<"MinVolume"<< c.MinVolume<<"ContingentCondition"<< c.ContingentCondition<<"StopPrice"<< c.StopPrice<<"ForceCloseReason"<< c.ForceCloseReason<<"IsAutoSuspend"<< c.IsAutoSuspend<<"BusinessUnit"<< c.BusinessUnit<<"RequestID"<< c.RequestID<<"OrderLocalID"<< c.OrderLocalID<<"ExchangeID"<< c.ExchangeID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"reserve2"<< c.reserve2<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderSubmitStatus"<< c.OrderSubmitStatus<<"NotifySequence"<< c.NotifySequence<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OrderSysID"<< c.OrderSysID<<"OrderSource"<< c.OrderSource<<"OrderStatus"<< c.OrderStatus<<"OrderType"<< c.OrderType<<"VolumeTraded"<< c.VolumeTraded<<"VolumeTotal"<< c.VolumeTotal<<"InsertDate"<< c.InsertDate<<"InsertTime"<< c.InsertTime<<"ActiveTime"<< c.ActiveTime<<"SuspendTime"<< c.SuspendTime<<"UpdateTime"<< c.UpdateTime<<"CancelTime"<< c.CancelTime<<"ActiveTraderID"<< c.ActiveTraderID<<"ClearingPartID"<< c.ClearingPartID<<"SequenceNo"<< c.SequenceNo<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"UserProductInfo"<< c.UserProductInfo<<"StatusMsg"<< c.StatusMsg<<"UserForceClose"<< c.UserForceClose<<"ActiveUserID"<< c.ActiveUserID<<"BrokerOrderSeq"<< c.BrokerOrderSeq<<"RelativeOrderSysID"<< c.RelativeOrderSysID<<"ZCETotalTradedVolume"<< c.ZCETotalTradedVolume<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"IsSwapOrder"<< c.IsSwapOrder<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"reserve3"<< c.reserve3<<"MacAddress"<< c.MacAddress<<"InstrumentID"<< c.InstrumentID<<"ExchangeInstID"<< c.ExchangeInstID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryErrOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcErrOrderActionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OrderActionRef"<< c.OrderActionRef<<"OrderRef"<< c.OrderRef<<"RequestID"<< c.RequestID<<"FrontID"<< c.FrontID<<"SessionID"<< c.SessionID<<"ExchangeID"<< c.ExchangeID<<"OrderSysID"<< c.OrderSysID<<"ActionFlag"<< c.ActionFlag<<"LimitPrice"<< c.LimitPrice<<"VolumeChange"<< c.VolumeChange<<"ActionDate"<< c.ActionDate<<"ActionTime"<< c.ActionTime<<"TraderID"<< c.TraderID<<"InstallID"<< c.InstallID<<"OrderLocalID"<< c.OrderLocalID<<"ActionLocalID"<< c.ActionLocalID<<"ParticipantID"<< c.ParticipantID<<"ClientID"<< c.ClientID<<"BusinessUnit"<< c.BusinessUnit<<"OrderActionStatus"<< c.OrderActionStatus<<"UserID"<< c.UserID<<"StatusMsg"<< c.StatusMsg<<"reserve1"<< c.reserve1<<"BranchID"<< c.BranchID<<"InvestUnitID"<< c.InvestUnitID<<"reserve2"<< c.reserve2<<"MacAddress"<< c.MacAddress<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"InstrumentID"<< c.InstrumentID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryExchangeSequenceField& c)
{
return os<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcExchangeSequenceField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"SequenceNo"<< c.SequenceNo<<"MarketStatus"<< c.MarketStatus;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryMaxOrderVolumeWithPriceField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"Direction"<< c.Direction<<"OffsetFlag"<< c.OffsetFlag<<"HedgeFlag"<< c.HedgeFlag<<"MaxVolume"<< c.MaxVolume<<"Price"<< c.Price<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBrokerTradingParamsField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"CurrencyID"<< c.CurrencyID<<"AccountID"<< c.AccountID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerTradingParamsField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"MarginPriceType"<< c.MarginPriceType<<"Algorithm"<< c.Algorithm<<"AvailIncludeCloseProfit"<< c.AvailIncludeCloseProfit<<"CurrencyID"<< c.CurrencyID<<"OptionRoyaltyPriceType"<< c.OptionRoyaltyPriceType<<"AccountID"<< c.AccountID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBrokerTradingAlgosField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"ExchangeID"<< c.ExchangeID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerTradingAlgosField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"ExchangeID"<< c.ExchangeID<<"reserve1"<< c.reserve1<<"HandlePositionAlgoID"<< c.HandlePositionAlgoID<<"FindMarginRateAlgoID"<< c.FindMarginRateAlgoID<<"HandleTradingAccountAlgoID"<< c.HandleTradingAccountAlgoID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQueryBrokerDepositField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"ExchangeID"<< c.ExchangeID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerDepositField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"ParticipantID"<< c.ParticipantID<<"ExchangeID"<< c.ExchangeID<<"PreBalance"<< c.PreBalance<<"CurrMargin"<< c.CurrMargin<<"CloseProfit"<< c.CloseProfit<<"Balance"<< c.Balance<<"Deposit"<< c.Deposit<<"Withdraw"<< c.Withdraw<<"Available"<< c.Available<<"Reserve"<< c.Reserve<<"FrozenMargin"<< c.FrozenMargin;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCFMMCBrokerKeyField& c)
{
return os<<"BrokerID"<< c.BrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCFMMCBrokerKeyField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"ParticipantID"<< c.ParticipantID<<"CreateDate"<< c.CreateDate<<"CreateTime"<< c.CreateTime<<"KeyID"<< c.KeyID<<"CurrentKey"<< c.CurrentKey<<"KeyKind"<< c.KeyKind;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCFMMCTradingAccountKeyField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"ParticipantID"<< c.ParticipantID<<"AccountID"<< c.AccountID<<"KeyID"<< c.KeyID<<"CurrentKey"<< c.CurrentKey;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCFMMCTradingAccountKeyField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerUserOTPParamField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"OTPVendorsID"<< c.OTPVendorsID<<"SerialNumber"<< c.SerialNumber<<"AuthKey"<< c.AuthKey<<"LastDrift"<< c.LastDrift<<"LastSuccess"<< c.LastSuccess<<"OTPType"<< c.OTPType;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcManualSyncBrokerUserOTPField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"OTPType"<< c.OTPType<<"FirstOTP"<< c.FirstOTP<<"SecondOTP"<< c.SecondOTP;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCommRateModelField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"CommModelID"<< c.CommModelID<<"CommModelName"<< c.CommModelName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCommRateModelField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"CommModelID"<< c.CommModelID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMarginModelField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"MarginModelID"<< c.MarginModelID<<"MarginModelName"<< c.MarginModelName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryMarginModelField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"MarginModelID"<< c.MarginModelID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcEWarrantOffsetField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID<<"reserve1"<< c.reserve1<<"Direction"<< c.Direction<<"HedgeFlag"<< c.HedgeFlag<<"Volume"<< c.Volume<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryEWarrantOffsetField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID<<"reserve1"<< c.reserve1<<"InvestUnitID"<< c.InvestUnitID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryInvestorProductGroupMarginField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"reserve1"<< c.reserve1<<"HedgeFlag"<< c.HedgeFlag<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"ProductGroupID"<< c.ProductGroupID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcInvestorProductGroupMarginField& c)
{
return os<<"reserve1"<< c.reserve1<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"FrozenMargin"<< c.FrozenMargin<<"LongFrozenMargin"<< c.LongFrozenMargin<<"ShortFrozenMargin"<< c.ShortFrozenMargin<<"UseMargin"<< c.UseMargin<<"LongUseMargin"<< c.LongUseMargin<<"ShortUseMargin"<< c.ShortUseMargin<<"ExchMargin"<< c.ExchMargin<<"LongExchMargin"<< c.LongExchMargin<<"ShortExchMargin"<< c.ShortExchMargin<<"CloseProfit"<< c.CloseProfit<<"FrozenCommission"<< c.FrozenCommission<<"Commission"<< c.Commission<<"FrozenCash"<< c.FrozenCash<<"CashIn"<< c.CashIn<<"PositionProfit"<< c.PositionProfit<<"OffsetAmount"<< c.OffsetAmount<<"LongOffsetAmount"<< c.LongOffsetAmount<<"ShortOffsetAmount"<< c.ShortOffsetAmount<<"ExchOffsetAmount"<< c.ExchOffsetAmount<<"LongExchOffsetAmount"<< c.LongExchOffsetAmount<<"ShortExchOffsetAmount"<< c.ShortExchOffsetAmount<<"HedgeFlag"<< c.HedgeFlag<<"ExchangeID"<< c.ExchangeID<<"InvestUnitID"<< c.InvestUnitID<<"ProductGroupID"<< c.ProductGroupID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQueryCFMMCTradingAccountTokenField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"InvestUnitID"<< c.InvestUnitID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCFMMCTradingAccountTokenField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"ParticipantID"<< c.ParticipantID<<"AccountID"<< c.AccountID<<"KeyID"<< c.KeyID<<"Token"<< c.Token;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryProductGroupField& c)
{
return os<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"ProductID"<< c.ProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcProductGroupField& c)
{
return os<<"reserve1"<< c.reserve1<<"ExchangeID"<< c.ExchangeID<<"reserve2"<< c.reserve2<<"ProductID"<< c.ProductID<<"ProductGroupID"<< c.ProductGroupID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBulletinField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"TradingDay"<< c.TradingDay<<"BulletinID"<< c.BulletinID<<"SequenceNo"<< c.SequenceNo<<"NewsType"<< c.NewsType<<"NewsUrgency"<< c.NewsUrgency<<"SendTime"<< c.SendTime<<"Abstract"<< c.Abstract<<"ComeFrom"<< c.ComeFrom<<"Content"<< c.Content<<"URLLink"<< c.URLLink<<"MarketID"<< c.MarketID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryBulletinField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"BulletinID"<< c.BulletinID<<"SequenceNo"<< c.SequenceNo<<"NewsType"<< c.NewsType<<"NewsUrgency"<< c.NewsUrgency;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcMulticastInstrumentField& c)
{
return os<<"TopicID"<< c.TopicID<<"reserve1"<< c.reserve1<<"InstrumentNo"<< c.InstrumentNo<<"CodePrice"<< c.CodePrice<<"VolumeMultiple"<< c.VolumeMultiple<<"PriceTick"<< c.PriceTick<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryMulticastInstrumentField& c)
{
return os<<"TopicID"<< c.TopicID<<"reserve1"<< c.reserve1<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcAppIDAuthAssignField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AppID"<< c.AppID<<"DRIdentityID"<< c.DRIdentityID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqOpenAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"CashExchangeCode"<< c.CashExchangeCode<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"TID"<< c.TID<<"UserID"<< c.UserID<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqCancelAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"CashExchangeCode"<< c.CashExchangeCode<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"TID"<< c.TID<<"UserID"<< c.UserID<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqChangeAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"NewBankAccount"<< c.NewBankAccount<<"NewBankPassWord"<< c.NewBankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"BankAccType"<< c.BankAccType<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"TID"<< c.TID<<"Digest"<< c.Digest<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqTransferField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"FutureSerial"<< c.FutureSerial<<"UserID"<< c.UserID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"TradeAmount"<< c.TradeAmount<<"FutureFetchAmount"<< c.FutureFetchAmount<<"FeePayFlag"<< c.FeePayFlag<<"CustFee"<< c.CustFee<<"BrokerFee"<< c.BrokerFee<<"Message"<< c.Message<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"TransferStatus"<< c.TransferStatus<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspTransferField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"FutureSerial"<< c.FutureSerial<<"UserID"<< c.UserID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"TradeAmount"<< c.TradeAmount<<"FutureFetchAmount"<< c.FutureFetchAmount<<"FeePayFlag"<< c.FeePayFlag<<"CustFee"<< c.CustFee<<"BrokerFee"<< c.BrokerFee<<"Message"<< c.Message<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"TransferStatus"<< c.TransferStatus<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqRepealField& c)
{
return os<<"RepealTimeInterval"<< c.RepealTimeInterval<<"RepealedTimes"<< c.RepealedTimes<<"BankRepealFlag"<< c.BankRepealFlag<<"BrokerRepealFlag"<< c.BrokerRepealFlag<<"PlateRepealSerial"<< c.PlateRepealSerial<<"BankRepealSerial"<< c.BankRepealSerial<<"FutureRepealSerial"<< c.FutureRepealSerial<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"FutureSerial"<< c.FutureSerial<<"UserID"<< c.UserID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"TradeAmount"<< c.TradeAmount<<"FutureFetchAmount"<< c.FutureFetchAmount<<"FeePayFlag"<< c.FeePayFlag<<"CustFee"<< c.CustFee<<"BrokerFee"<< c.BrokerFee<<"Message"<< c.Message<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"TransferStatus"<< c.TransferStatus<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspRepealField& c)
{
return os<<"RepealTimeInterval"<< c.RepealTimeInterval<<"RepealedTimes"<< c.RepealedTimes<<"BankRepealFlag"<< c.BankRepealFlag<<"BrokerRepealFlag"<< c.BrokerRepealFlag<<"PlateRepealSerial"<< c.PlateRepealSerial<<"BankRepealSerial"<< c.BankRepealSerial<<"FutureRepealSerial"<< c.FutureRepealSerial<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"FutureSerial"<< c.FutureSerial<<"UserID"<< c.UserID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"TradeAmount"<< c.TradeAmount<<"FutureFetchAmount"<< c.FutureFetchAmount<<"FeePayFlag"<< c.FeePayFlag<<"CustFee"<< c.CustFee<<"BrokerFee"<< c.BrokerFee<<"Message"<< c.Message<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"TransferStatus"<< c.TransferStatus<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqQueryAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"FutureSerial"<< c.FutureSerial<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspQueryAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"FutureSerial"<< c.FutureSerial<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"BankUseAmount"<< c.BankUseAmount<<"BankFetchAmount"<< c.BankFetchAmount<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcFutureSignIOField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Digest"<< c.Digest<<"CurrencyID"<< c.CurrencyID<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspFutureSignInField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Digest"<< c.Digest<<"CurrencyID"<< c.CurrencyID<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"PinKey"<< c.PinKey<<"MacKey"<< c.MacKey;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqFutureSignOutField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Digest"<< c.Digest<<"CurrencyID"<< c.CurrencyID<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspFutureSignOutField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Digest"<< c.Digest<<"CurrencyID"<< c.CurrencyID<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqQueryTradeResultBySerialField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"Reference"<< c.Reference<<"RefrenceIssureType"<< c.RefrenceIssureType<<"RefrenceIssure"<< c.RefrenceIssure<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"CurrencyID"<< c.CurrencyID<<"TradeAmount"<< c.TradeAmount<<"Digest"<< c.Digest<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspQueryTradeResultBySerialField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"Reference"<< c.Reference<<"RefrenceIssureType"<< c.RefrenceIssureType<<"RefrenceIssure"<< c.RefrenceIssure<<"OriginReturnCode"<< c.OriginReturnCode<<"OriginDescrInfoForReturnCode"<< c.OriginDescrInfoForReturnCode<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"CurrencyID"<< c.CurrencyID<<"TradeAmount"<< c.TradeAmount<<"Digest"<< c.Digest;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqDayEndFileReadyField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"FileBusinessCode"<< c.FileBusinessCode<<"Digest"<< c.Digest;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReturnResultField& c)
{
return os<<"ReturnCode"<< c.ReturnCode<<"DescrInfoForReturnCode"<< c.DescrInfoForReturnCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcVerifyFuturePasswordField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"InstallID"<< c.InstallID<<"TID"<< c.TID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcVerifyCustInfoField& c)
{
return os<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcVerifyFuturePasswordAndCustInfoField& c)
{
return os<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"CurrencyID"<< c.CurrencyID<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcDepositResultInformField& c)
{
return os<<"DepositSeqNo"<< c.DepositSeqNo<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"Deposit"<< c.Deposit<<"RequestID"<< c.RequestID<<"ReturnCode"<< c.ReturnCode<<"DescrInfoForReturnCode"<< c.DescrInfoForReturnCode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqSyncKeyField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Message"<< c.Message<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspSyncKeyField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Message"<< c.Message<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcNotifyQueryAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustType"<< c.CustType<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"FutureSerial"<< c.FutureSerial<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"BankUseAmount"<< c.BankUseAmount<<"BankFetchAmount"<< c.BankFetchAmount<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTransferSerialField& c)
{
return os<<"PlateSerial"<< c.PlateSerial<<"TradeDate"<< c.TradeDate<<"TradingDay"<< c.TradingDay<<"TradeTime"<< c.TradeTime<<"TradeCode"<< c.TradeCode<<"SessionID"<< c.SessionID<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BankAccType"<< c.BankAccType<<"BankAccount"<< c.BankAccount<<"BankSerial"<< c.BankSerial<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"FutureAccType"<< c.FutureAccType<<"AccountID"<< c.AccountID<<"InvestorID"<< c.InvestorID<<"FutureSerial"<< c.FutureSerial<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CurrencyID"<< c.CurrencyID<<"TradeAmount"<< c.TradeAmount<<"CustFee"<< c.CustFee<<"BrokerFee"<< c.BrokerFee<<"AvailabilityFlag"<< c.AvailabilityFlag<<"OperatorCode"<< c.OperatorCode<<"BankNewAccount"<< c.BankNewAccount<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryTransferSerialField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"BankID"<< c.BankID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcNotifyFutureSignInField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Digest"<< c.Digest<<"CurrencyID"<< c.CurrencyID<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"PinKey"<< c.PinKey<<"MacKey"<< c.MacKey;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcNotifyFutureSignOutField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Digest"<< c.Digest<<"CurrencyID"<< c.CurrencyID<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcNotifySyncKeyField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"InstallID"<< c.InstallID<<"UserID"<< c.UserID<<"Message"<< c.Message<<"DeviceID"<< c.DeviceID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"OperNo"<< c.OperNo<<"RequestID"<< c.RequestID<<"TID"<< c.TID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryAccountregisterField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcAccountregisterField& c)
{
return os<<"TradeDay"<< c.TradeDay<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BankAccount"<< c.BankAccount<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"AccountID"<< c.AccountID<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"CustomerName"<< c.CustomerName<<"CurrencyID"<< c.CurrencyID<<"OpenOrDestroy"<< c.OpenOrDestroy<<"RegDate"<< c.RegDate<<"OutDate"<< c.OutDate<<"TID"<< c.TID<<"CustType"<< c.CustType<<"BankAccType"<< c.BankAccType<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcOpenAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"CashExchangeCode"<< c.CashExchangeCode<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"TID"<< c.TID<<"UserID"<< c.UserID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCancelAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"CashExchangeCode"<< c.CashExchangeCode<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"DeviceID"<< c.DeviceID<<"BankSecuAccType"<< c.BankSecuAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankSecuAcc"<< c.BankSecuAcc<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"OperNo"<< c.OperNo<<"TID"<< c.TID<<"UserID"<< c.UserID<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcChangeAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"NewBankAccount"<< c.NewBankAccount<<"NewBankPassWord"<< c.NewBankPassWord<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"BankAccType"<< c.BankAccType<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"BrokerIDByBank"<< c.BrokerIDByBank<<"BankPwdFlag"<< c.BankPwdFlag<<"SecuPwdFlag"<< c.SecuPwdFlag<<"TID"<< c.TID<<"Digest"<< c.Digest<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg<<"LongCustomerName"<< c.LongCustomerName;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSecAgentACIDMapField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID<<"BrokerSecAgentID"<< c.BrokerSecAgentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySecAgentACIDMapField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"AccountID"<< c.AccountID<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcUserRightsAssignField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"DRIdentityID"<< c.DRIdentityID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcBrokerUserRightAssignField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"DRIdentityID"<< c.DRIdentityID<<"Tradeable"<< c.Tradeable;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcDRTransferField& c)
{
return os<<"OrigDRIdentityID"<< c.OrigDRIdentityID<<"DestDRIdentityID"<< c.DestDRIdentityID<<"OrigBrokerID"<< c.OrigBrokerID<<"DestBrokerID"<< c.DestBrokerID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcFensUserInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"LoginMode"<< c.LoginMode;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCurrTransferIdentityField& c)
{
return os<<"IdentityID"<< c.IdentityID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcLoginForbiddenUserField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"reserve1"<< c.reserve1<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryLoginForbiddenUserField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcTradingAccountReserveField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"Reserve"<< c.Reserve<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryLoginForbiddenIPField& c)
{
return os<<"reserve1"<< c.reserve1<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryIPListField& c)
{
return os<<"reserve1"<< c.reserve1<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryUserRightsAssignField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReserveOpenAccountConfirmField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"TID"<< c.TID<<"AccountID"<< c.AccountID<<"Password"<< c.Password<<"BankReserveOpenSeq"<< c.BankReserveOpenSeq<<"BookDate"<< c.BookDate<<"BookPsw"<< c.BookPsw<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReserveOpenAccountField& c)
{
return os<<"TradeCode"<< c.TradeCode<<"BankID"<< c.BankID<<"BankBranchID"<< c.BankBranchID<<"BrokerID"<< c.BrokerID<<"BrokerBranchID"<< c.BrokerBranchID<<"TradeDate"<< c.TradeDate<<"TradeTime"<< c.TradeTime<<"BankSerial"<< c.BankSerial<<"TradingDay"<< c.TradingDay<<"PlateSerial"<< c.PlateSerial<<"LastFragment"<< c.LastFragment<<"SessionID"<< c.SessionID<<"CustomerName"<< c.CustomerName<<"IdCardType"<< c.IdCardType<<"IdentifiedCardNo"<< c.IdentifiedCardNo<<"Gender"<< c.Gender<<"CountryCode"<< c.CountryCode<<"CustType"<< c.CustType<<"Address"<< c.Address<<"ZipCode"<< c.ZipCode<<"Telephone"<< c.Telephone<<"MobilePhone"<< c.MobilePhone<<"Fax"<< c.Fax<<"EMail"<< c.EMail<<"MoneyAccountStatus"<< c.MoneyAccountStatus<<"BankAccount"<< c.BankAccount<<"BankPassWord"<< c.BankPassWord<<"InstallID"<< c.InstallID<<"VerifyCertNoFlag"<< c.VerifyCertNoFlag<<"CurrencyID"<< c.CurrencyID<<"Digest"<< c.Digest<<"BankAccType"<< c.BankAccType<<"BrokerIDByBank"<< c.BrokerIDByBank<<"TID"<< c.TID<<"ReserveOpenAccStas"<< c.ReserveOpenAccStas<<"ErrorID"<< c.ErrorID<<"ErrorMsg"<< c.ErrorMsg;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcAccountPropertyField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"BankID"<< c.BankID<<"BankAccount"<< c.BankAccount<<"OpenName"<< c.OpenName<<"OpenBank"<< c.OpenBank<<"IsActive"<< c.IsActive<<"AccountSourceType"<< c.AccountSourceType<<"OpenDate"<< c.OpenDate<<"CancelDate"<< c.CancelDate<<"OperatorID"<< c.OperatorID<<"OperateDate"<< c.OperateDate<<"OperateTime"<< c.OperateTime<<"CurrencyID"<< c.CurrencyID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCurrDRIdentityField& c)
{
return os<<"DRIdentityID"<< c.DRIdentityID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCurrDRIdentityField& c)
{
return os<<"DRIdentityID"<< c.DRIdentityID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySecAgentCheckModeField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQrySecAgentTradeInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"BrokerSecAgentID"<< c.BrokerSecAgentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqUserAuthMethodField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspUserAuthMethodField& c)
{
return os<<"UsableAuthMethod"<< c.UsableAuthMethod;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqGenUserCaptchaField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspGenUserCaptchaField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"CaptchaInfoLen"<< c.CaptchaInfoLen<<"CaptchaInfo"<< c.CaptchaInfo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqGenUserTextField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspGenUserTextField& c)
{
return os<<"UserTextSeq"<< c.UserTextSeq;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqUserLoginWithCaptchaField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"Password"<< c.Password<<"UserProductInfo"<< c.UserProductInfo<<"InterfaceProductInfo"<< c.InterfaceProductInfo<<"ProtocolInfo"<< c.ProtocolInfo<<"MacAddress"<< c.MacAddress<<"reserve1"<< c.reserve1<<"LoginRemark"<< c.LoginRemark<<"Captcha"<< c.Captcha<<"ClientIPPort"<< c.ClientIPPort<<"ClientIPAddress"<< c.ClientIPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqUserLoginWithTextField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"Password"<< c.Password<<"UserProductInfo"<< c.UserProductInfo<<"InterfaceProductInfo"<< c.InterfaceProductInfo<<"ProtocolInfo"<< c.ProtocolInfo<<"MacAddress"<< c.MacAddress<<"reserve1"<< c.reserve1<<"LoginRemark"<< c.LoginRemark<<"Text"<< c.Text<<"ClientIPPort"<< c.ClientIPPort<<"ClientIPAddress"<< c.ClientIPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqUserLoginWithOTPField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"Password"<< c.Password<<"UserProductInfo"<< c.UserProductInfo<<"InterfaceProductInfo"<< c.InterfaceProductInfo<<"ProtocolInfo"<< c.ProtocolInfo<<"MacAddress"<< c.MacAddress<<"reserve1"<< c.reserve1<<"LoginRemark"<< c.LoginRemark<<"OTPPassword"<< c.OTPPassword<<"ClientIPPort"<< c.ClientIPPort<<"ClientIPAddress"<< c.ClientIPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqApiHandshakeField& c)
{
return os<<"CryptoKeyVersion"<< c.CryptoKeyVersion;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRspApiHandshakeField& c)
{
return os<<"FrontHandshakeDataLen"<< c.FrontHandshakeDataLen<<"FrontHandshakeData"<< c.FrontHandshakeData<<"IsApiAuthEnabled"<< c.IsApiAuthEnabled;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcReqVerifyApiKeyField& c)
{
return os<<"ApiHandshakeDataLen"<< c.ApiHandshakeDataLen<<"ApiHandshakeData"<< c.ApiHandshakeData;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcDepartmentUserField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"InvestorRange"<< c.InvestorRange<<"InvestorID"<< c.InvestorID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQueryFreqField& c)
{
return os<<"QueryFreq"<< c.QueryFreq;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcAuthForbiddenIPField& c)
{
return os<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryAuthForbiddenIPField& c)
{
return os<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDelaySwapFrozenField& c)
{
return os<<"DelaySwapSeqNo"<< c.DelaySwapSeqNo<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"FromCurrencyID"<< c.FromCurrencyID<<"FromRemainSwap"<< c.FromRemainSwap<<"IsManualSwap"<< c.IsManualSwap;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcUserSystemInfoField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"UserID"<< c.UserID<<"ClientSystemInfoLen"<< c.ClientSystemInfoLen<<"ClientSystemInfo"<< c.ClientSystemInfo<<"reserve1"<< c.reserve1<<"ClientIPPort"<< c.ClientIPPort<<"ClientLoginTime"<< c.ClientLoginTime<<"ClientAppID"<< c.ClientAppID<<"ClientPublicIP"<< c.ClientPublicIP<<"ClientLoginRemark"<< c.ClientLoginRemark;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcAuthUserIDField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AppID"<< c.AppID<<"UserID"<< c.UserID<<"AuthType"<< c.AuthType;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcAuthIPField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AppID"<< c.AppID<<"IPAddress"<< c.IPAddress;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryClassifiedInstrumentField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"ExchangeID"<< c.ExchangeID<<"ExchangeInstID"<< c.ExchangeInstID<<"ProductID"<< c.ProductID<<"TradingType"<< c.TradingType<<"ClassType"<< c.ClassType;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryCombPromotionParamField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcCombPromotionParamField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID<<"CombHedgeFlag"<< c.CombHedgeFlag<<"Xparameter"<< c.Xparameter;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryRiskSettleInvstPositionField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"InstrumentID"<< c.InstrumentID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcQryRiskSettleProductStatusField& c)
{
return os<<"ProductID"<< c.ProductID;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRiskSettleInvstPositionField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"PosiDirection"<< c.PosiDirection<<"HedgeFlag"<< c.HedgeFlag<<"PositionDate"<< c.PositionDate<<"YdPosition"<< c.YdPosition<<"Position"<< c.Position<<"LongFrozen"<< c.LongFrozen<<"ShortFrozen"<< c.ShortFrozen<<"LongFrozenAmount"<< c.LongFrozenAmount<<"ShortFrozenAmount"<< c.ShortFrozenAmount<<"OpenVolume"<< c.OpenVolume<<"CloseVolume"<< c.CloseVolume<<"OpenAmount"<< c.OpenAmount<<"CloseAmount"<< c.CloseAmount<<"PositionCost"<< c.PositionCost<<"PreMargin"<< c.PreMargin<<"UseMargin"<< c.UseMargin<<"FrozenMargin"<< c.FrozenMargin<<"FrozenCash"<< c.FrozenCash<<"FrozenCommission"<< c.FrozenCommission<<"CashIn"<< c.CashIn<<"Commission"<< c.Commission<<"CloseProfit"<< c.CloseProfit<<"PositionProfit"<< c.PositionProfit<<"PreSettlementPrice"<< c.PreSettlementPrice<<"SettlementPrice"<< c.SettlementPrice<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"OpenCost"<< c.OpenCost<<"ExchangeMargin"<< c.ExchangeMargin<<"CombPosition"<< c.CombPosition<<"CombLongFrozen"<< c.CombLongFrozen<<"CombShortFrozen"<< c.CombShortFrozen<<"CloseProfitByDate"<< c.CloseProfitByDate<<"CloseProfitByTrade"<< c.CloseProfitByTrade<<"TodayPosition"<< c.TodayPosition<<"MarginRateByMoney"<< c.MarginRateByMoney<<"MarginRateByVolume"<< c.MarginRateByVolume<<"StrikeFrozen"<< c.StrikeFrozen<<"StrikeFrozenAmount"<< c.StrikeFrozenAmount<<"AbandonFrozen"<< c.AbandonFrozen<<"ExchangeID"<< c.ExchangeID<<"YdStrikeFrozen"<< c.YdStrikeFrozen<<"InvestUnitID"<< c.InvestUnitID<<"PositionCostOffset"<< c.PositionCostOffset<<"TasPosition"<< c.TasPosition<<"TasPositionCost"<< c.TasPositionCost;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcRiskSettleProductStatusField& c)
{
return os<<"ExchangeID"<< c.ExchangeID<<"ProductID"<< c.ProductID<<"ProductStatus"<< c.ProductStatus;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaInfoField& c)
{
return os<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo<<"SyncDeltaStatus"<< c.SyncDeltaStatus<<"SyncDescription"<< c.SyncDescription<<"IsOnlyTrdDelta"<< c.IsOnlyTrdDelta;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaProductStatusField& c)
{
return os<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo<<"ExchangeID"<< c.ExchangeID<<"ProductID"<< c.ProductID<<"ProductStatus"<< c.ProductStatus;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaInvstPosDtlField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"Direction"<< c.Direction<<"OpenDate"<< c.OpenDate<<"TradeID"<< c.TradeID<<"Volume"<< c.Volume<<"OpenPrice"<< c.OpenPrice<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"TradeType"<< c.TradeType<<"CombInstrumentID"<< c.CombInstrumentID<<"ExchangeID"<< c.ExchangeID<<"CloseProfitByDate"<< c.CloseProfitByDate<<"CloseProfitByTrade"<< c.CloseProfitByTrade<<"PositionProfitByDate"<< c.PositionProfitByDate<<"PositionProfitByTrade"<< c.PositionProfitByTrade<<"Margin"<< c.Margin<<"ExchMargin"<< c.ExchMargin<<"MarginRateByMoney"<< c.MarginRateByMoney<<"MarginRateByVolume"<< c.MarginRateByVolume<<"LastSettlementPrice"<< c.LastSettlementPrice<<"SettlementPrice"<< c.SettlementPrice<<"CloseVolume"<< c.CloseVolume<<"CloseAmount"<< c.CloseAmount<<"TimeFirstVolume"<< c.TimeFirstVolume<<"SpecPosiType"<< c.SpecPosiType<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaInvstPosCombDtlField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"OpenDate"<< c.OpenDate<<"ExchangeID"<< c.ExchangeID<<"SettlementID"<< c.SettlementID<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ComTradeID"<< c.ComTradeID<<"TradeID"<< c.TradeID<<"InstrumentID"<< c.InstrumentID<<"HedgeFlag"<< c.HedgeFlag<<"Direction"<< c.Direction<<"TotalAmt"<< c.TotalAmt<<"Margin"<< c.Margin<<"ExchMargin"<< c.ExchMargin<<"MarginRateByMoney"<< c.MarginRateByMoney<<"MarginRateByVolume"<< c.MarginRateByVolume<<"LegID"<< c.LegID<<"LegMultiple"<< c.LegMultiple<<"TradeGroupID"<< c.TradeGroupID<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaTradingAccountField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"AccountID"<< c.AccountID<<"PreMortgage"<< c.PreMortgage<<"PreCredit"<< c.PreCredit<<"PreDeposit"<< c.PreDeposit<<"PreBalance"<< c.PreBalance<<"PreMargin"<< c.PreMargin<<"InterestBase"<< c.InterestBase<<"Interest"<< c.Interest<<"Deposit"<< c.Deposit<<"Withdraw"<< c.Withdraw<<"FrozenMargin"<< c.FrozenMargin<<"FrozenCash"<< c.FrozenCash<<"FrozenCommission"<< c.FrozenCommission<<"CurrMargin"<< c.CurrMargin<<"CashIn"<< c.CashIn<<"Commission"<< c.Commission<<"CloseProfit"<< c.CloseProfit<<"PositionProfit"<< c.PositionProfit<<"Balance"<< c.Balance<<"Available"<< c.Available<<"WithdrawQuota"<< c.WithdrawQuota<<"Reserve"<< c.Reserve<<"TradingDay"<< c.TradingDay<<"SettlementID"<< c.SettlementID<<"Credit"<< c.Credit<<"Mortgage"<< c.Mortgage<<"ExchangeMargin"<< c.ExchangeMargin<<"DeliveryMargin"<< c.DeliveryMargin<<"ExchangeDeliveryMargin"<< c.ExchangeDeliveryMargin<<"ReserveBalance"<< c.ReserveBalance<<"CurrencyID"<< c.CurrencyID<<"PreFundMortgageIn"<< c.PreFundMortgageIn<<"PreFundMortgageOut"<< c.PreFundMortgageOut<<"FundMortgageIn"<< c.FundMortgageIn<<"FundMortgageOut"<< c.FundMortgageOut<<"FundMortgageAvailable"<< c.FundMortgageAvailable<<"MortgageableFund"<< c.MortgageableFund<<"SpecProductMargin"<< c.SpecProductMargin<<"SpecProductFrozenMargin"<< c.SpecProductFrozenMargin<<"SpecProductCommission"<< c.SpecProductCommission<<"SpecProductFrozenCommission"<< c.SpecProductFrozenCommission<<"SpecProductPositionProfit"<< c.SpecProductPositionProfit<<"SpecProductCloseProfit"<< c.SpecProductCloseProfit<<"SpecProductPositionProfitByAlg"<< c.SpecProductPositionProfitByAlg<<"SpecProductExchangeMargin"<< c.SpecProductExchangeMargin<<"FrozenSwap"<< c.FrozenSwap<<"RemainSwap"<< c.RemainSwap<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaInitInvstMarginField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"LastRiskTotalInvstMargin"<< c.LastRiskTotalInvstMargin<<"LastRiskTotalExchMargin"<< c.LastRiskTotalExchMargin<<"ThisSyncInvstMargin"<< c.ThisSyncInvstMargin<<"ThisSyncExchMargin"<< c.ThisSyncExchMargin<<"RemainRiskInvstMargin"<< c.RemainRiskInvstMargin<<"RemainRiskExchMargin"<< c.RemainRiskExchMargin<<"LastRiskSpecTotalInvstMargin"<< c.LastRiskSpecTotalInvstMargin<<"LastRiskSpecTotalExchMargin"<< c.LastRiskSpecTotalExchMargin<<"ThisSyncSpecInvstMargin"<< c.ThisSyncSpecInvstMargin<<"ThisSyncSpecExchMargin"<< c.ThisSyncSpecExchMargin<<"RemainRiskSpecInvstMargin"<< c.RemainRiskSpecInvstMargin<<"RemainRiskSpecExchMargin"<< c.RemainRiskSpecExchMargin<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaDceCombInstrumentField& c)
{
return os<<"CombInstrumentID"<< c.CombInstrumentID<<"ExchangeID"<< c.ExchangeID<<"ExchangeInstID"<< c.ExchangeInstID<<"TradeGroupID"<< c.TradeGroupID<<"CombHedgeFlag"<< c.CombHedgeFlag<<"CombinationType"<< c.CombinationType<<"Direction"<< c.Direction<<"ProductID"<< c.ProductID<<"Xparameter"<< c.Xparameter<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaInvstMarginRateField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"IsRelative"<< c.IsRelative<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaExchMarginRateField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InstrumentID"<< c.InstrumentID<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaOptExchMarginField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InstrumentID"<< c.InstrumentID<<"SShortMarginRatioByMoney"<< c.SShortMarginRatioByMoney<<"SShortMarginRatioByVolume"<< c.SShortMarginRatioByVolume<<"HShortMarginRatioByMoney"<< c.HShortMarginRatioByMoney<<"HShortMarginRatioByVolume"<< c.HShortMarginRatioByVolume<<"AShortMarginRatioByMoney"<< c.AShortMarginRatioByMoney<<"AShortMarginRatioByVolume"<< c.AShortMarginRatioByVolume<<"MShortMarginRatioByMoney"<< c.MShortMarginRatioByMoney<<"MShortMarginRatioByVolume"<< c.MShortMarginRatioByVolume<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaOptInvstMarginField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"SShortMarginRatioByMoney"<< c.SShortMarginRatioByMoney<<"SShortMarginRatioByVolume"<< c.SShortMarginRatioByVolume<<"HShortMarginRatioByMoney"<< c.HShortMarginRatioByMoney<<"HShortMarginRatioByVolume"<< c.HShortMarginRatioByVolume<<"AShortMarginRatioByMoney"<< c.AShortMarginRatioByMoney<<"AShortMarginRatioByVolume"<< c.AShortMarginRatioByVolume<<"IsRelative"<< c.IsRelative<<"MShortMarginRatioByMoney"<< c.MShortMarginRatioByMoney<<"MShortMarginRatioByVolume"<< c.MShortMarginRatioByVolume<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaInvstMarginRateULField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"HedgeFlag"<< c.HedgeFlag<<"LongMarginRatioByMoney"<< c.LongMarginRatioByMoney<<"LongMarginRatioByVolume"<< c.LongMarginRatioByVolume<<"ShortMarginRatioByMoney"<< c.ShortMarginRatioByMoney<<"ShortMarginRatioByVolume"<< c.ShortMarginRatioByVolume<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaOptInvstCommRateField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OpenRatioByMoney"<< c.OpenRatioByMoney<<"OpenRatioByVolume"<< c.OpenRatioByVolume<<"CloseRatioByMoney"<< c.CloseRatioByMoney<<"CloseRatioByVolume"<< c.CloseRatioByVolume<<"CloseTodayRatioByMoney"<< c.CloseTodayRatioByMoney<<"CloseTodayRatioByVolume"<< c.CloseTodayRatioByVolume<<"StrikeRatioByMoney"<< c.StrikeRatioByMoney<<"StrikeRatioByVolume"<< c.StrikeRatioByVolume<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaInvstCommRateField& c)
{
return os<<"InstrumentID"<< c.InstrumentID<<"InvestorRange"<< c.InvestorRange<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"OpenRatioByMoney"<< c.OpenRatioByMoney<<"OpenRatioByVolume"<< c.OpenRatioByVolume<<"CloseRatioByMoney"<< c.CloseRatioByMoney<<"CloseRatioByVolume"<< c.CloseRatioByVolume<<"CloseTodayRatioByMoney"<< c.CloseTodayRatioByMoney<<"CloseTodayRatioByVolume"<< c.CloseTodayRatioByVolume<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaProductExchRateField& c)
{
return os<<"ProductID"<< c.ProductID<<"QuoteCurrencyID"<< c.QuoteCurrencyID<<"ExchangeRate"<< c.ExchangeRate<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaDepthMarketDataField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"InstrumentID"<< c.InstrumentID<<"ExchangeID"<< c.ExchangeID<<"ExchangeInstID"<< c.ExchangeInstID<<"LastPrice"<< c.LastPrice<<"PreSettlementPrice"<< c.PreSettlementPrice<<"PreClosePrice"<< c.PreClosePrice<<"PreOpenInterest"<< c.PreOpenInterest<<"OpenPrice"<< c.OpenPrice<<"HighestPrice"<< c.HighestPrice<<"LowestPrice"<< c.LowestPrice<<"Volume"<< c.Volume<<"Turnover"<< c.Turnover<<"OpenInterest"<< c.OpenInterest<<"ClosePrice"<< c.ClosePrice<<"SettlementPrice"<< c.SettlementPrice<<"UpperLimitPrice"<< c.UpperLimitPrice<<"LowerLimitPrice"<< c.LowerLimitPrice<<"PreDelta"<< c.PreDelta<<"CurrDelta"<< c.CurrDelta<<"UpdateTime"<< c.UpdateTime<<"UpdateMillisec"<< c.UpdateMillisec<<"BidPrice1"<< c.BidPrice1<<"BidVolume1"<< c.BidVolume1<<"AskPrice1"<< c.AskPrice1<<"AskVolume1"<< c.AskVolume1<<"BidPrice2"<< c.BidPrice2<<"BidVolume2"<< c.BidVolume2<<"AskPrice2"<< c.AskPrice2<<"AskVolume2"<< c.AskVolume2<<"BidPrice3"<< c.BidPrice3<<"BidVolume3"<< c.BidVolume3<<"AskPrice3"<< c.AskPrice3<<"AskVolume3"<< c.AskVolume3<<"BidPrice4"<< c.BidPrice4<<"BidVolume4"<< c.BidVolume4<<"AskPrice4"<< c.AskPrice4<<"AskVolume4"<< c.AskVolume4<<"BidPrice5"<< c.BidPrice5<<"BidVolume5"<< c.BidVolume5<<"AskPrice5"<< c.AskPrice5<<"AskVolume5"<< c.AskVolume5<<"AveragePrice"<< c.AveragePrice<<"ActionDay"<< c.ActionDay<<"BandingUpperPrice"<< c.BandingUpperPrice<<"BandingLowerPrice"<< c.BandingLowerPrice<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaIndexPriceField& c)
{
return os<<"BrokerID"<< c.BrokerID<<"InstrumentID"<< c.InstrumentID<<"ClosePrice"<< c.ClosePrice<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

std::ostream& operator<<(std::ostream& os, const CThostFtdcSyncDeltaEWarrantOffsetField& c)
{
return os<<"TradingDay"<< c.TradingDay<<"BrokerID"<< c.BrokerID<<"InvestorID"<< c.InvestorID<<"ExchangeID"<< c.ExchangeID<<"InstrumentID"<< c.InstrumentID<<"Direction"<< c.Direction<<"HedgeFlag"<< c.HedgeFlag<<"Volume"<< c.Volume<<"ActionDirection"<< c.ActionDirection<<"SyncDeltaSequenceNo"<< c.SyncDeltaSequenceNo;
};

