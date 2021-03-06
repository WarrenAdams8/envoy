#include "test/mocks/config/mocks.h"

#include "envoy/config/core/v3/config_source.pb.h"

#include "test/test_common/utility.h"

namespace Envoy {
namespace Config {

MockSubscriptionFactory::MockSubscriptionFactory() {
  ON_CALL(*this, subscriptionFromConfigSource(_, _, _, _, _))
      .WillByDefault(testing::Invoke(
          [this](const envoy::config::core::v3::ConfigSource&, absl::string_view, Stats::Scope&,
                 SubscriptionCallbacks& callbacks, OpaqueResourceDecoder&) -> SubscriptionPtr {
            auto ret = std::make_unique<testing::NiceMock<MockSubscription>>();
            subscription_ = ret.get();
            callbacks_ = &callbacks;
            return ret;
          }));
  ON_CALL(*this, messageValidationVisitor())
      .WillByDefault(testing::ReturnRef(ProtobufMessage::getStrictValidationVisitor()));
}

MockSubscriptionFactory::~MockSubscriptionFactory() = default;

MockGrpcMuxWatch::MockGrpcMuxWatch() = default;
MockGrpcMuxWatch::~MockGrpcMuxWatch() { cancel(); }

MockGrpcMux::MockGrpcMux() = default;
MockGrpcMux::~MockGrpcMux() = default;

MockGrpcStreamCallbacks::MockGrpcStreamCallbacks() = default;
MockGrpcStreamCallbacks::~MockGrpcStreamCallbacks() = default;

MockSubscriptionCallbacks::MockSubscriptionCallbacks() = default;
MockSubscriptionCallbacks::~MockSubscriptionCallbacks() = default;

MockOpaqueResourceDecoder::MockOpaqueResourceDecoder() = default;
MockOpaqueResourceDecoder::~MockOpaqueResourceDecoder() = default;

MockUntypedConfigUpdateCallbacks::MockUntypedConfigUpdateCallbacks() = default;
MockUntypedConfigUpdateCallbacks::~MockUntypedConfigUpdateCallbacks() = default;

MockTypedFactory::~MockTypedFactory() = default;
} // namespace Config
} // namespace Envoy
