#include "HelloService.h"

namespace example {
namespace hello {

void HelloHandler::get_hello(
    std::string& response, std::unique_ptr<std::string> name) {
  response = *name;
}
} // namespace hello
} // namespace example