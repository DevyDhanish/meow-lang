program ::= import stmts | simple stmts | compound stmts

import stmts ::= "import" module-name

simple stmts ::= assignment | expression

assignment ::= identifier "=" expression | identifier

compound stmts ::= if stmts
                |  elif stmts
                |  else stmts
                |  function def
                |  class def
                |  function calls

if stmts ::= "if" expression | function call "{ ... }"<br>
else stmts ::= "elif" experession | function call "{ ... }"<br>
else ::= "else"