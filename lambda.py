import ply.lex as lex

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
    t.type = 'VARIAVEL'
    return t

# error handeling
def t_error( t ):
    print("Invalid Sintaxe")
    t.lexer.skip(1)

if __name__ == "__main__":
    
    lexer = lex.lex()

    test ='''\x.x y'''

    lexer.input(test)

    while True:
        tok = lexer.token()
        
        if not tok:
            break
        
        print(tok)

    pass
