namespace cpp echo
namespace go echo
namespace java echo

struct Req {
  1:string message;
}

struct Rsp {
  1:string message;
}

service Echo {
  Rsp echo(1: Req req)
}
