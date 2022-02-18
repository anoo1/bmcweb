#include "http_request.hpp"
#include "include/async_resp.hpp"
#include "nlohmann/json.hpp"
#include "redfish-core/lib/service_root.hpp"

#include <memory>
#include <string>

#include "gmock/gmock.h"

void assertServiceRootGet(crow::Response& res)
{
    nlohmann::json& json = res.jsonValue;
    EXPECT_EQ(json["@odata.id"], "/redfish/v1");
    EXPECT_EQ(json["@odata.type"], "#ServiceRoot.v1_11_0.ServiceRoot");

    EXPECT_EQ(json["AccountService"]["@odata.id"],
              "/redfish/v1/AccountService");
    EXPECT_EQ(json["AccountService"].size(), 1);

    EXPECT_EQ(json["CertificateService"]["@odata.id"],
              "/redfish/v1/CertificateService");
    EXPECT_EQ(json["CertificateService"].size(), 1);

    EXPECT_EQ(json["Chassis"]["@odata.id"], "/redfish/v1/Chassis");
    EXPECT_EQ(json["Chassis"].size(), 1);

    EXPECT_EQ(json["EventService"]["@odata.id"], "/redfish/v1/EventService");
    EXPECT_EQ(json["EventService"].size(), 1);

    EXPECT_EQ(json["Id"], "RootService");
    EXPECT_EQ(json["Links"]["Sessions"]["@odata.id"],
              "/redfish/v1/SessionService/Sessions");
    EXPECT_EQ(json["Links"].size(), 1);
    EXPECT_EQ(json["Links"]["Sessions"].size(), 1);

    EXPECT_EQ(json["Managers"]["@odata.id"], "/redfish/v1/Managers");
    EXPECT_EQ(json["Managers"].size(), 1);

    EXPECT_EQ(json["Name"], "Root Service");
    EXPECT_EQ(json["RedfishVersion"], "1.9.0");

    EXPECT_EQ(json["Registries"]["@odata.id"], "/redfish/v1/Registries");
    EXPECT_EQ(json["Registries"].size(), 1);

    EXPECT_EQ(json["SessionService"]["@odata.id"],
              "/redfish/v1/SessionService");
    EXPECT_EQ(json["SessionService"].size(), 1);

    EXPECT_EQ(json["Systems"]["@odata.id"], "/redfish/v1/Systems");
    EXPECT_EQ(json["Systems"].size(), 1);

    EXPECT_EQ(json["Tasks"]["@odata.id"], "/redfish/v1/TaskService");
    EXPECT_EQ(json["Tasks"].size(), 1);

    EXPECT_EQ(json["TelemetryService"]["@odata.id"],
              "/redfish/v1/TelemetryService");
    EXPECT_EQ(json["TelemetryService"].size(), 1);

    EXPECT_THAT(
        json["UUID"],
        testing::MatchesRegex("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-"
                              "9a-fA-F]{4}-[0-9a-fA-F]{12}"));

    EXPECT_EQ(json["UpdateService"]["@odata.id"], "/redfish/v1/UpdateService");
    EXPECT_EQ(20, json.size());
}

TEST(ServiceRootTest, ServiceRootConstructor)
{
    std::error_code ec;
    crow::Request req({}, ec);
    auto shareAsyncResp = std::make_shared<bmcweb::AsyncResp>();

    shareAsyncResp->res.setCompleteRequestHandler(assertServiceRootGet);

    redfish::handleServiceRootGet(req, shareAsyncResp);
}