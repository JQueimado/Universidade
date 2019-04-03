from Resources import lex
from Resources import yacc

# Gramatica em BNF
# 
#   <termo> ::= <variavel>
#               | (\<termo>.<listav>)
#               | (<termo> <termo>)
#
#   <listav> ::= <variavel>
#               | (<variavel><listav>)
#
#   <variavel> ::= a|b|c|d|...|z
#

# Tokens 
tokens = (
    'VARIAVEL',
    'LAMBDA',
    'DOT',
    'SPACE',
    'LP',
    'RP'
)

t_LAMBDA = r'\\'
t_DOT = r'\.'
t_SPACE = r'\ '
t_LP = r'\('
t_RP = r'\)'

def t_VARIAVEL ( t ):
    r'[a-z]'
    t.value = t
    return t

# lines
def t_newline( t ):
    r'\n+'
    t.lexer.lineno += len(t.value)

# error handeling
def t_error( t ):
    print("Invalid Sintaxe at char nº: %s" % t.value[0])
    t.lexer.skip(1)

if __name__ == "__main__":
<<<<<<< HEAD
    
    lexer = lex.lex()

    test = r"\x.x"

    lexer.input(test)

    while True:
        tok = lexer.token()
        
        if not tok:
            break
        
        print(tok)

    pass
=======
    pass
>>>>>>> 1e9f3495b88f9248eabf3d1e114b063f49e9cadc
>>>>>>> 0b6f0d3e36ff02cb628ac524e11c33da2589753c
