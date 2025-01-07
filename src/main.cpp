#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <cstdlib>
#include <memory>
#include <string>

boost::asio::awaitable<void> tcp_client(boost::asio::io_context& ioc, const std::string& host, const std::string& port) {
    try {
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address(host), std::atoi(port.c_str()));

        std::string request;
        char response[1024] = {0};

        boost::asio::ip::tcp::socket sock(ioc);
        co_await sock.async_connect(ep, boost::asio::use_awaitable);
/*
    OPTIONS rtsp://192.168.1.106:554/live/test RTSP/1.0
    CSeq: 1
    User-Agent: Lavf61.9.101
*/
        request = "OPTIONS rtsp://192.168.1.106:554/live/test RTSP/1.0\r\nCSeq: 1\r\nUser-Agent: Lavf61.9.101\r\n\r\n";
        co_await sock.async_write_some(boost::asio::buffer(request), boost::asio::use_awaitable);
        request.clear();

/*
    RTSP/1.0 200 OK
    CSeq: 1
    Date: Tue, Jan 07 2025 02:01:00 GMT
    Public: OPTIONS, DESCRIBE, SETUP, TEARDOWN, PLAY, PAUSE, ANNOUNCE, RECORD, SET_PARAMETER, GET_PARAMETER
    Server: ZLMediaKit(git hash:a226794,branch:master,build time:Sep 22 2022 01:57:44)
*/
        int length = co_await sock.async_read_some(boost::asio::buffer(response), boost::asio::use_awaitable);
        std::cout << "Received response: " << std::string(response, length) << std::endl;

/*
    DESCRIBE rtsp://192.168.1.106:554 RTSP/1.0
    Accept: application/sdp
    CSeq: 2
    User-Agent: Lavf61.9.101
*/
        request = "DESCRIBE rtsp://192.168.1.106:554/live/test RTSP/1.0\r\nAccept: application/sdp\r\nCSeq: 2\r\nUser-Agent: Lavf61.9.101\r\n\r\n";
        co_await sock.async_write_some(boost::asio::buffer(request), boost::asio::use_awaitable);
        request.clear();

/*
    RTSP/1.0 200 OK
    Content-Base: rtsp://192.168.1.106:554/live/test/
    Content-Length: 570
    Content-Type: application/sdp
    CSeq: 2
    Date: Tue, Jan 07 2025 02:01:00 GMT
    Server: ZLMediaKit(git hash:a226794,branch:master,build time:Sep 22 2022 01:57:44)
    Session: DgApOqc9QRrM
    x-Accept-Dynamic-Rate: 1
    x-Accept-Retransmit: our-retransmit

    v=0
    o=- 0 0 IN IP4 0.0.0.0
    s=Streamed by ZLMediaKit(git hash:a226794,branch:master,build time:Sep 22 2022 01:57:44)
    c=IN IP4 0.0.0.0
    t=0 0
    a=range:npt=now-
    a=control:*
    m=video 0 RTP/AVP 96
    b=AS:2099
    a=fmtp:96 packetization-mode=1; profile-level-id=640028; sprop-parameter-sets=Z2QAKKyyAPAET8sIAAADAAgAAAMBkHjBkkA=,aOvMsiw=
    a=rtpmap:96 H264/90000
    a=control:trackID=0
    m=audio 0 RTP/AVP 98
    a=fmtp:98 streamtype=5;profile-level-id=1;mode=AAC-hbr;sizelength=13;indexlength=3;indexdeltalength=3;config=1588
    a=rtpmap:98 mpeg4-generic/8000/1
    a=control:trackID=1
*/
        length = co_await sock.async_read_some(boost::asio::buffer(response), boost::asio::use_awaitable);
        std::cout << "Received response: " << std::string(response, length) << std::endl;



        sock.close();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context ioc;

        boost::asio::co_spawn(ioc, tcp_client(ioc, "192.168.1.106", "554"), boost::asio::detached);

        ioc.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}