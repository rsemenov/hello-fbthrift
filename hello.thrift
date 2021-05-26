namespace cpp2 example.hello

struct Message {
  1: string message;
  2: string sender;
  3: i64 timestamp;
}

service HelloSvc {
    string get_hello(1: string name)
}