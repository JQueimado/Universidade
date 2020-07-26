
--Utilizadores
insert into Utilizador values ('001', 'ToZé','1234','ZéToino@hotmail.com');
insert into Utilizador values ('002', 'Kito','4321','Kitolelo@tudooquepoderes.com');
insert into Utilizador values ('003', 'Manel','1379','l3222@gmail.com');

--Usuario
insert into Usuario values ('001');
insert into Usuario values ('003');

--Administrador
insert into Administrador values ('002');

--Livros
insert into Livros values ('001','J.K. Rowling', 'Harry Potter e a Pedra Filosofal');
insert into Livros values ('002','E.L. James'  , 'Cinquenta Tons de Cinza');
insert into Livros values ('003','J.K. Rowling', 'Harry Potter e os Talismãs da Morte');
insert into Livros values ('004','E.L. James'  , 'Cinquenta Tons Mais Escuros');
insert into Livros values ('005','J.K. Rowling', 'Harry Potter e o Cálice de Fogo');

--Serie
insert into Serie values ('A Saga Do Secador De Cabelo','Kesyn & Skelter');
insert into Serie values ('Initial D','Studio Comet');

--Videos
insert into Videos values ('A Saga Do Secador De Cabelo Ep1',1);
insert into Videos values ('A Saga Do Secador De Cabelo Ep2',2);
insert into Videos values ('A Saga Do Secador De Cabelo Ep3',3);
insert into Videos values ('Initial D First Stage',1);
insert into Videos values ('Initial D Second Stage',2);

--ListaDeLivros
insert into ListaDeLivros values ('001','001');
insert into ListaDeLivros values ('001','003');
insert into ListaDeLivros values ('001','005');

insert into ListaDeLivros values ('002','002');
insert into ListaDeLivros values ('002','004');
insert into ListaDeLivros values ('002','001');

--ListaDeSeries 
insert into ListaDeSeries values ('001','A Saga Do Secador De Cabelo');

insert into ListaDeSeries values ('002','A Saga Do Secador De Cabelo');
insert into ListaDeSeries values ('002','Initial D');

insert into ListaDeSeries values ('003','Initial D');

--Episodios
insert into Episodios values ('A Saga Do Secador De Cabelo Ep1','A Saga Do Secador De Cabelo');
insert into Episodios values ('A Saga Do Secador De Cabelo Ep2','A Saga Do Secador De Cabelo');
insert into Episodios values ('Initial D First Stage','Initial D');
insert into Episodios values ('Initial D Second Stage','Initial D');

--Categorias 
insert into Categorias values ('A Saga Do Secador De Cabelo','Acao');
insert into Categorias values ('A Saga Do Secador De Cabelo','Comedia');
insert into Categorias values ('Initial D','Comedia');
insert into Categorias values ('Initial D','Acao');
insert into Categorias values ('Initial D','Drama');

