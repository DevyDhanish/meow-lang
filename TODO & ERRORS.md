# TODO
[ ] - Better parsing of if statements and it's conditions
[ DONE ] - Better handling of if else statements
[ DONE ] - Nested if statements

# ERRORS
[ ] - Sometimes it gives a seg fault when interpreting sometimes it does not.
[ FIXIED ] - Single if statement causes
terminate called after throwing an instance of 'std::length_error'
  what():  basic_string::_M_create
Aborted (core dumped)

[ FIXIED ] - If file contains only if and else block it causes
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
Aborted (core dumped)