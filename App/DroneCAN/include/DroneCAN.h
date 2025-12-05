/*
 
*/

#pragma once

// system includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>

// include the canard C++ APIs
#include "stm32f7xx_hal.h"

#include <canard/publisher.h>
#include <canard/subscriber.h>
#include <canard/service_client.h>
#include <canard/service_server.h>
#include <canard/handler_list.h>
#include <canard/transfer_object.h>

// include the base canard API
#include <canard.h>
// #include <canard_stm32.h>
#include "canard_stm32.h"

// include the headers for the generated DroneCAN messages
#include <dronecan_msgs.h>

#define MY_NODE_ID 0
#define PREFERRED_NODE_ID 73


/*
  create a DroneCANInterface class for interfacing with the hardware
 */
class DroneCANInterface : public Canard::Interface {
    friend class DroneCANNode;

    DroneCANInterface(uint8_t iface_index) :
        Interface(iface_index) {}
    
public:
    void init(const char *interface_name);

    // implement required interface functions
    bool broadcast(const Canard::Transfer &bcast_transfer) override;
    bool request(uint8_t destination_node_id, const Canard::Transfer &req_transfer) override;
    bool respond(uint8_t destination_node_id, const Canard::Transfer &res_transfer) override;

    void process(uint32_t duration_ms);

    static void onTransferReceived(CanardInstance* ins, CanardRxTransfer* transfer);
    static bool shouldAcceptTransfer(const CanardInstance* ins,
                                     uint64_t* out_data_type_signature,
                                     uint16_t data_type_id,
                                     CanardTransferType transfer_type,
                                     uint8_t source_node_id);

    uint8_t get_node_id() const override { return canard.node_id; }
    void set_node_id(uint8_t node_id) {
        canardSetLocalNodeID(&canard, node_id);
    }

private:
    uint8_t memory_pool[2048];
    CanardInstance canard;
    CanardTxTransfer tx_transfer;

    CanardSTM32CANTimings timings;
};


class DroneCANNode {
public:
    void start_node(const char *interface_name);

private:
    DroneCANInterface canard_iface{0};

    // declare publishers for outgoing messages
    Canard::Publisher<uavcan_protocol_NodeStatus> node_status{canard_iface};

    // Node Info Server
    void handle_GetNodeInfo(const CanardRxTransfer& transfer, const uavcan_protocol_GetNodeInfoRequest& req);
    Canard::ObjCallback<DroneCANNode, uavcan_protocol_GetNodeInfoRequest> node_info_req_cb{this, &DroneCANNode::handle_GetNodeInfo};
    Canard::Server<uavcan_protocol_GetNodeInfoRequest> node_info_server{canard_iface, node_info_req_cb};

    // handlers for dynamic node allocation (DNA)
    Canard::Publisher<uavcan_protocol_dynamic_node_id_Allocation> allocation_pub{canard_iface};
    void handle_DNA_Allocation(const CanardRxTransfer& transfer, const uavcan_protocol_dynamic_node_id_Allocation& msg);
    Canard::ObjCallback<DroneCANNode, uavcan_protocol_dynamic_node_id_Allocation> allocation_cb{this, &DroneCANNode::handle_DNA_Allocation};
    Canard::Subscriber<uavcan_protocol_dynamic_node_id_Allocation> allocation_listener{allocation_cb, 0};

    // DNA request call
    void request_DNA();

    void send_NodeStatus(void);
    void process1HzTasks(uint64_t timestamp_usec);

    // keep node_status around for updating status
    uavcan_protocol_NodeStatus node_status_msg;

    /*
      data for dynamic node allocation process
    */
    struct {
        uint32_t send_next_node_id_allocation_request_at_ms;
        uint32_t node_id_allocation_unique_id_offset;
    } DNA;

};