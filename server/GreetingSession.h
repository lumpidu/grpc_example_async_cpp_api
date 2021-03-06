#ifndef GRPC_EXAMPLE_TIME_SERVER_SESSION_H
#define GRPC_EXAMPLE_TIME_SERVER_SESSION_H

#include <greeting.grpc.pb.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/server_context.h>

#include <cstdint>
#include <deque>
#include <mutex>
#include <string>

#include "GrpcType.h"
#include "Performance.h"

class GreetingSession {
  public:
    GreetingSession(uint64_t sessionId) : session_id_(sessionId){};

    bool init();

    void process(GrpcEvent event);

    void reply();

    void finish();

  public:
    const uint64_t session_id_{0};
    std::mutex mutex_{};
    GrpcSessionStatus status_{GrpcSessionStatus::WAIT_CONNECT};

    ::grpc::ServerContext server_context_{};
    ::grpc::ServerAsyncReaderWriter<::grpc::example::ReplyGreeting, ::grpc::example::RequestSubscribe>
        subscribe_stream{&server_context_};
    ::grpc::example::RequestSubscribe request_{};

    std::string name_{};
    std::deque<std::shared_ptr<::grpc::example::ReplyGreeting>> message_queue_{};
    Performance performance_{};
    uint64_t reply_times_{0};
};

#endif  // GRPC_EXAMPLE_TIME_SERVER_SESSION_H
