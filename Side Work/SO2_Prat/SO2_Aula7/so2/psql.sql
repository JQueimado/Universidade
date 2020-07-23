

create table aluno ( 
    n int primary key,
    nome text, 
    bi int, 
    telefone int );

create table disciplina ( 
    codigo int primary key,
    nome text, 
    descricao text );

create table inscricao (
    n int references aluno(n),
    codigo int references disciplina(codigo)
);