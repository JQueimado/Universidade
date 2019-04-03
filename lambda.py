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
    
    lexer = lex.lex()

    test = r"\x.x"

    lexer.input(test)

    while True:
        tok = lexer.token()
        
        if not tok:
            break
        
        print(tok)

    pass