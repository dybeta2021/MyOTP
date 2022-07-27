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
        int order_ref_num = -1;//order序号
        int cancel_ref_num = -1;//order序号

    public:
        OrderManager() {
            //vector的resize：既分配了空间，也创建了对象，会调用构造函数
            //vector的reserve：reserve()表示容器预留空间，但不是真正的创建对象，需要通过insert()或push_back()等操作创建对象
            //reserve()只修改capacity大小，不修改size大小，
            //resize()既修改capacity大小，也修改size大小。
            //因此，在只需要足够的空间而不需要生成对象时（通常是为了节约插入元素的时间），应该选择reserve方法。
            order_vec_.reserve(OTS_ORDER_VECTOR_SIZE);
        }
        ~OrderManager() = default;

        int GetOrderRef() { return ++order_ref_num; };
        int GetCancelRef() { return ++cancel_ref_num; };

        void Show() {
            SPDLOG_INFO("order_vector size:{}.", order_vec_.size());
            for (auto iter = order_vec_.begin(); iter != order_vec_.end(); iter++) {
                SPDLOG_INFO("ref:{}, update_time:{}, symbol:{}, direction:{}, offset:{}, volume:{}, traded_volume:{}, left_volume:{}, cancel_volume:{}, price:{}, type:{}, status:{}, msg:{}.",
                            iter->order_ref_num,
                            iter->update_time,
                            iter->symbol,
                            magic_enum::enum_name(iter->direction),
                            magic_enum::enum_name(iter->offset),
                            iter->volume,
                            iter->traded_volume,
                            iter->left_volume,
                            iter->cancel_volume,
                            iter->price,
                            magic_enum::enum_name(iter->type),
                            magic_enum::enum_name(iter->status),
                            iter->status_msg);
            }
        }

        void InsertOrder(const Order &order) {
            order_vec_.insert(order_vec_.begin() + order.order_ref_num, order);
            SPDLOG_INFO(
                    "Insert-order, order_id:{}, account_id:{}, symbol:{}, type:{}, direction:{}, offset:{}, volume:{}, price:{}",
                    order.order_ref_num,
                    order.account_id,
                    order.symbol,
                    magic_enum::enum_name(order.type),
                    magic_enum::enum_name(order.direction),
                    magic_enum::enum_name(order.offset),
                    order.volume,
                    order.price);
        }

        void OnError(Order &order) {
            order_vec_[order.order_ref_num] = order;
        }

        void OnRejected(const OrderRejected &rejected){
            auto order = &order_vec_[rejected.order_ref_num];
            order->update_time = rejected.update_time;
            order->status = rejected.status;
            strcpy(order->status_msg, rejected.status_msg);
        }

        // 订单回报
        void OnEntrust(const OrderEntrust &entrust) {
            auto order = &order_vec_[entrust.order_ref_num];
            order->update_time = entrust.update_time;
            order->status = entrust.status;
            strcpy(order->status_msg, entrust.status_msg);
            order->traded_volume = entrust.traded_volume;
            order->left_volume = entrust.left_volume;
            order->cancel_volume = entrust.cancel_volume;
        }

        // todo:
        // 查询回报
        void OnQuery(const Order &order){

        }
    };

}// namespace ots::broker

#endif//OTS_FT_ORDER_H
