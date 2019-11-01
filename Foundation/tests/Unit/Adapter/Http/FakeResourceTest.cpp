#include <string>
#include <gtest/gtest.h>

#include "Poco/URI.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Adapter/Http/Context/FakeRouter.h"
#include "Adapter/Http/Context/FakeErrorJsonAPIParser.h"


class FakeResourceTest : public ::testing::Test
{
protected:
    const std::string TEST_ADDRESS     = "127.0.0.1";
    const std::string TEST_ENDPOINT    = "/testing_endpoint";
    const std::string CONTENT_TYPE     = "application/vnd.api+json";

};


TEST_F(FakeResourceTest, AllowedHttpMediaHeader) {

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

TEST_F(FakeResourceTest, DisallowedHttpMediaType) {

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

TEST_F(FakeResourceTest, DisallowedMethod) {

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

TEST_F(FakeResourceTest, MethodNotImplemented) {

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

    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED, response.getStatus());

}

TEST_F(FakeResourceTest, ExceptionThrownWithinHttpMethod) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    std::string responseContent;
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response) >> responseContent;


    Poco::URI uri = Poco::URI(request.getURI());
    UnitTests::Http::Context::FakeErrorJSONParser errorParser;

    std::string jsonHandlerReturn = errorParser.toJson(
        request.getHost(),
        std::to_string(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST),
        uri.getPath(),
        Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
        " You sent a request that this server could not understand."
    );

    ASSERT_EQ(jsonHandlerReturn, responseContent);
    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(jsonHandlerReturn.length(), response.getContentLength());
    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST, response.getStatus());

}

TEST_F(FakeResourceTest, HttpGETResponse) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    std::string responseContent;
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response) >> responseContent;

    ASSERT_EQ("{}", responseContent);
    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_OK, response.getStatus());

}

TEST_F(FakeResourceTest, HttpPOSTResponse) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_CREATED, response.getStatus());
    ASSERT_EQ("http://localhost?key=value", response.get("Content-Location"));

}

TEST_F(FakeResourceTest, HttpOPTIONSResponse) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_OPTIONS, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_OK, response.getStatus());
    ASSERT_EQ("GET, POST, PUT, OPTIONS, PATCH", response.get("Allow"));

}

TEST_F(FakeResourceTest, HttpCORSHeaders) {

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new UnitTests::Http::Context::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ("github.com, localhost:8080, 127.0.0.1:9000", response.get("Access-Control-Allow-Origin"));
    ASSERT_EQ("GET, PUT, PATH, POST, DELETE, OPTIONS",      response.get("Access-Control-Request-Method"));
    ASSERT_EQ("Accept, Content-Type, Accept-Language",      response.get("Access-Control-Request-Headers"));
    ASSERT_EQ("true",                                       response.get("Access-Control-Allow-Credentials"));

}

TEST_F(FakeResourceTest, HttpErrorParser) {

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
