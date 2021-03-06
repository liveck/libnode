libnode
=======

libnode is a native implementation of Node.js.

### Build

    git clone --recursive https://github.com/plenluno/libnode.git
    mkdir libnode/build
    cd libnode/build
    cmake ..
    make

The memory management of libnode is automatic, based on either shared_ptr or bdw-gc.  
libnode uses shared_ptr by default. In order to use bdw-gc,  

    cmake -DLIBNODE_USE_BDWGC=ON ..

If your compiler supports C++11,

    cmake -DLIBNODE_USE_CXX11=ON ..

It allows you to use closures like the example below.

### Example

The following HTTP server responds with "Hello World" for every request.

    http::Server::Ptr srv = http::Server::create(
        JsClosure::create([] (JsArray::Ptr args) -> Value {
            http::ServerResponse::Ptr res =
                args->getPtr<http::ServerResponse>(1);
            res->setHeader(
                http::HEADER_CONTENT_TYPE,
                String::create("text/plain"));
            res->end(String::create("Hello World\n"));
            return Status::OK;
        }));
    srv->listen(1337, String::create("127.0.0.1"));
    node::run();

For more information about the usage, please refer to libnode/gtest.
