#include <catch2/catch_session.hpp>
#include <folly/init/Init.h>

int main(int argc, char* argv[]) {
  folly::InitOptions opt;
  folly::init(&argc, &argv, opt);

  int result = Catch::Session().run(argc, argv);

  return result;
}
