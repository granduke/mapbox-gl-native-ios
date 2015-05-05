#pragma once

#include <mbgl/storage/file_source.hpp>

#include <node.h>
#include <nan.h>

#include <map>

namespace node_mbgl {

namespace util { template <typename T> class AsyncQueue; }

class NodeFileSource : public node::ObjectWrap, public mbgl::FileSource {
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Static Node Methods
public:
    static void Init(v8::Handle<v8::Object> target);
    static NAN_METHOD(New);

    static v8::Persistent<v8::FunctionTemplate> constructorTemplate;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Instance
public:
    NodeFileSource();
    ~NodeFileSource();

    mbgl::Request* request(const mbgl::Resource&, uv_loop_t*, Callback);
    void cancel(mbgl::Request*);

    void request(const mbgl::Resource&, Callback);

    // visiblity?
    void notify(mbgl::Request*, const std::shared_ptr<const mbgl::Response>&);

private:
    struct Action;
    using Queue = util::AsyncQueue<Action>;

    void processAdd(mbgl::Request*);
    void processCancel(mbgl::Request*);

private:
    std::map<mbgl::Request*, v8::Persistent<v8::Object>> pending;
    Queue *queue = nullptr;
};

}
