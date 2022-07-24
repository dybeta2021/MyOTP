//
// Created by 稻草人 on 2022/7/11.
//

#ifndef OTS_FT_ORDER_H
#define OTS_FT_ORDER_H
#include "magic_enum.hpp"
#include "ots/data.h"
#include "ots/define.h"
#include "spdlog/spdlog.h"
#include <vector>

namespace ots::broker {
    using namespace ots::data;
    class OrderManager {
    private:
        std::vector<Order> order_vec_;
        size_t order_ref_num = 0;//order序号

    public:
        OrderManager() {
            order_vec_.reserve(OTS_ORDER_VECTOR_SIZE);
        }
        ~OrderManager() = default;

        size_t GetOrderRef() { return order_ref_num++; };

        void InsertOrder(const Order &order) {
            order_vec_[order.order_ref_num] = order;
            SPDLOG_DEBUG(
                    "Insert-order, order_id:{}, account_id:{}, symbol:{}, direction:{}, offset:{}, volume:{}, price:{}",
                    order.order_ref_num,
                    order.account_id,
                    order.symbol,
                    magic_enum::enum_name(order.direction),
                    magic_enum::enum_name(order.offset),
                    order.volume,
                    order.price);
        }

        void OnError(Order &order){
            order_vec_[order.order_ref_num] = order;
        }

        void OnOrder(Order &order_) {
        }

        void OnTrade() {}
    };

}// namespace ots::broker

#endif//OTS_FT_ORDER_H
