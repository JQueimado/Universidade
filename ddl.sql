
drop table if exists Utilizador cascade;

create table Utilizador ( 
    ID char(3) primary key, 
    NomeU varchar(64), 
    pass varchar(4),
    Mail varchar(64)
);

drop table if exists Usuario cascade;

create table Usuario ( 
    ID char(3) primary key
);

drop table if exists Administrador cascade;

create table Administrador ( 
    ID char(3) primary key
);

drop table if exists Livros cascade;

create table Livros ( 
    IDLivro char(3) primary key,
    Autor varchar(64),
    TituloLivro varchar(64)
);

drop table if exists ListaDeLivros cascade;

create table ListaDeLivros ( 
    IDLivro char(3),
    ID char(3)
);

drop table if exists Serie cascade;

create table Serie ( 
    NomeSerie varchar(64) primary key,
    Estudio varchar(64) 
);

drop table if exists Videos cascade;

create table Videos ( 
    TituloVideo varchar(64) primary key,
    Ep int, 
    Duracao_horas int,
    Duracao_minutos int,
    Duracao_segundos int
);

drop table if exists Episodios cascade;

create table Episodios ( 
    TituloVideo varchar(64) primary key,
    NomeSerie varchar(64)
);

drop table if exists ListaDeSeries cascade;

create table ListaDeSeries ( 
    ID char(3),
    NomeSerie varchar(64)
);

drop table if exists Categorias cascade;

create table Categorias ( 
    IDLivro char(3),
    Categoria varchar(64)
);

drop table if exists Generos cascade;

create table Generos ( 
    NomeSerie varchar(64),
    Genero varchar(64)
);






