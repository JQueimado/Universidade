import ply.yacc as yacc

import lexer

'''
Gramatica

    <termo> ::= VARIAVEL
            | LP LAMBDA <listav> DOT <termo> RP
            | LP <termo> SPACE <termo> RP

    <listav> ::= VARIAVEL
            | VARIAVEL <listav>
'''

def p_term_var(p):
    'termo : VARIABLE'
    pass

def p_term_lamb(p):
    'termo : LP LAMBDA listav DOT termo RP'
    pass

def p_term_apl(p):
    'termo : LP termo SPACE termo RP'
    pass

def p_list_var(p):
    'listav : VARIABLE'
    pass

def p_list_cont(p):
    'listav : VARIABLE listav'
    pass

if __name__ == "__main__":

    parser = yacc.yacc()

    while True:
        try:
            s = raw_input('calc > ')
        except EOFError:
            break
        if not s: 
            continue
        result = parser.parse(s)
        print(result)

    pass
