// Copyright (c) 2012 Plenluno All rights reserved.

#include <libnode/process.h>
#include <libnode/timer.h>

#include <libj/status.h>
#include <libj/typed_linked_list.h>

namespace libj {
namespace node {
namespace process {

class NextTick : LIBJ_JS_FUNCTION(NextTick)
 public:
    typedef TypedLinkedList<JsFunction::Ptr> CallbackQueue;

    NextTick() : queue_(CallbackQueue::create()) {}

    Value operator()(JsArray::Ptr args) {
        Size len = queue_->length();
        for (Size i = 0; i < len; i++) {
            JsFunction::Ptr cb = queue_->shiftTyped();
            (*cb)();
        }
        return Status::OK;
    }

    void push(JsFunction::Ptr cb) {
        queue_->pushTyped(cb);
    }

 private:
    CallbackQueue::Ptr queue_;
};

void nextTick(JsFunction::Ptr callback) {
    // TODO(plenluno): implement without setTimeout
    static NextTick::Ptr nt(new NextTick());
    if (callback) nt->push(callback);
    setTimeout(nt, 0);
}

}  // namespace process
}  // namespace node
}  // namespace libj
