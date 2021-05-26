#pragma once

#include "../gen-cpp2/HelloSvc.h"

namespace example {
namespace hello {

class HelloHandler : virtual public HelloSvcSvIf {
 public:
  void get_hello(
      std::string& response, std::unique_ptr<std::string> name) override;
};
} // namespace hello
} // namespace example