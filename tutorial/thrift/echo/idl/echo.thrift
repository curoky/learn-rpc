namespace cpp echo
namespace java echo
namespace rs echo
namespace go echo

const string GLOBAL_CONST_VAR_STRING = "123";

struct Req {
  1:string message;
}

struct Rsp {
  1:string message;
}

service Echo {
  Rsp echo(1: Req req)
}
