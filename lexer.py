import ply.lex as lexer

'''  
TOKENS:

   VARIAVEL-> a-z
   LAMBDA  -> \
   DOT     -> .
   SPACE   -> " "
   LP      -> (
   RP      -> )
'''

# Tokens 
tokens = (
    'VARIABLE',
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
    t.type = 'VARIABLE'
    return t

precedence = (
    ()
)

# error handeling
def t_error( t ):
    print("Invalid Sintax!")
    t.lexer.skip(1)


# test #
'''
if __name__ == "__main__":
    
    lexer = lex.lex()

    try:
        while True:
            test = input()

            print("-> %s" % test)

            lexer.input(test)

            while True:
                tok = lexer.token()
                
                if not tok:
                    break
                
                print(tok)
            
            print("------------------")

    except EOFError as e:
        pass
'''