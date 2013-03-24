#ifndef USBMUX_PROXY2__PROTOCOL__
#define USBMUX_PROXY2__PROTOCOL__

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
class BinaryProtocol
{
public:
//  enum { VERSION = 0, RESULT  = 1, CONNECT = 2, LISTEN  = 3, DEVICE_ADD = 4, 
//         DEVICE_REMOVE = 5 };

public:
    BinaryProtocol(tcp::socket& sock); // 미룬다.

protected:
    tcp::socket& m_socket;
    
private:
    bool connected;
};

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
class PlistProtocol: public BinaryProtocol
{
public:
//  enum { VERSION = 1, RESULT  = 1, CONNECT = 2, LISTEN  = 3, DEVICE_ADD = 4, 
//         DEVICE_REMOVE = 5 };

public:
    PlistProtocol(tcp::socket& sock); // 미룬다.
};

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
class MuxConnection
{
public:
    MuxConnection();
};

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
class USBMux
{
public:
    USBMux();

    void start();
};

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////

#endif