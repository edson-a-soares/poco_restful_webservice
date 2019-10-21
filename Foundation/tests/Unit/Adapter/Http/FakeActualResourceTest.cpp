#include <string>
#include <gtest/gtest.h>

#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Environment.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Adapter/Http/Context/FakeRouter.h"
#include "Adapter/Http/Context/FakeErrorJsonAPIParser.h"


class FakeActualResourceTest : public ::testing::Test
{
protected:
    const std::string TEST_ADDRESS     = "127.0.0.1";
    const std::string TEST_ENDPOINT    = "/testing_endpoint";
    const std::string CONTENT_TYPE     = "application/vnd.api+json";

};


TEST_F(FakeActualResourceTest, AllowedHttpMediaHeader) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PATCH, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());

}

TEST_F(FakeActualResourceTest, DisallowedHttpMediaType) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType("application/json");
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_UNSUPPORTED_MEDIA_TYPE, response.getStatus());

}

TEST_F(FakeActualResourceTest, DisallowedMethod) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_TRACE, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED, response.getStatus());

}

TEST_F(FakeActualResourceTest, HttpErrorParser) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/not_existing_endpoint");

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    std::string jsonResponse;
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response) >> jsonResponse;

    Poco::URI uri = Poco::URI(request.getURI());
    UnitTests::Http::Context::FakeErrorJSONParser errorParser;

    std::string jsonHandlerReturn = errorParser.toJson(
        request.getHost(),
        std::to_string(Poco::Net::HTTPResponse::HTTP_NOT_FOUND),
        uri.getPath(),
        Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND,
        " This endpoint does not exist."
    );

    ASSERT_EQ(jsonHandlerReturn, jsonResponse);
    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(jsonHandlerReturn.length(), response.getContentLength());
    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, response.getStatus());

}
