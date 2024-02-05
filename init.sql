-- database: /root/Studia/C++/Bazadanych/przychodnia/przychodnia.db

-- Use the ▷ button in the top right corner to run the entire file.

create table Lekarz (
	PESEL int not null primary key,
	Imie nchar(20) not null,
	Nazwisko nchar(20) not null,
	NrTelefonu nchar(20) not null
);

insert into Lekarz(PESEL, Imie, Nazwisko, NrTelefonu) values
(11111,	'Jan',      'Nowak',     	66665157),
(12342,	'Tomasz',   'Karwowski', 	77881935),
(22223,	'Piotr',    'Śpiewak',   	123456789),
(33334,	'Jacek',    'Bąk',       	12186611),
(56565,	'Anna',		'Stępniak',		5462331),
(44886,	'Wanda',	'Stępniak',		44889944),
(33117,	'Tadeusz',	'Kapel',		84556465),
(99878,	'Jan',		'Prus',			12154887),
(65479,	'Piotr',	'Markiewicz',	989544656);

create table Specjalizacja (
	SpecjalizacjaID int not null primary key,
	Nazwa nchar(20) not null
);

insert into Specjalizacja(SpecjalizacjaID, Nazwa) values
(1,	'Ortopeda'),
(2,	'Neurolog'),
(3,	'Gastrolog'),
(4,	'Kardiolog'),
(5,	'Dermatolog'),
(6, 'Podolog'),
(7, 'Psycholog'),
(8, 'Internista');

create table LekarzSpecjalizacja (
	LekarzPESEL int not null,
	SpecjalizacjaID int not null,
	constraint FK_LekarzSpecjalizacja_Lekarz foreign key (LekarzPESEL)
    references Lekarz(PESEL),
	constraint FK_LekarzSpecjalizacja_Specjalizacja foreign key (SpecjalizacjaID)
    references Specjalizacja(SpecjalizacjaID)
);

insert into LekarzSpecjalizacja(LekarzPESEL, SpecjalizacjaID) values
(11111,	2),
(12342,	1),
(22223,	4),
(22223,	3),
(33334, 5),
(56565, 8),
(56565, 1),
(44886, 7),
(33117, 6),
(99878, 1),
(65479, 8),
(65479, 7);

create table Leki (
	LekID int not null primary key,
	Nazwa nchar(20) not null,
	Typ nchar(20) not null,
	Przeznaczenie nchar(20) not null
);

insert into Leki(LekID,	Nazwa, Typ,	Przeznaczenie) values
(1,	'Acai',      	'Tabletki',  	'Witaminy'),  
(2,	'Daktarin',  	'Krem',      	'Grzybica'),  
(3,	'Galvenox',  	'Żel',       	'Żylaki'),    
(4,	'Gelacet',   	'Kapsułki',  	'Kolagen'),   
(5,	'Kalivit',   	'Tabletki',  	'Potas'),
(6, 'Zypadhera',	'Fiolka',		'Przeciwpsychotyczne'),
(7, 'Rybelsus',		'Tabletki',		'Cukrzyca'),
(8, 'Cartexan',		'Kapsułki',		'Stawy');

create table Pacjent (
	PESEL int not null primary key,
	Imie nchar(20) not null,
	Nazwisko nchar(20) not null,
	Miejscowosc nchar(20) not null,
	KodPocztowy nchar(20)  not null,
	UlicaNumer nchar(20)  not null,
	NrTelefonu nchar(20)  not null,
	Email nchar(20)
);

insert into Pacjent(PESEL, Imie, Nazwisko, Miejscowosc, KodPocztowy, UlicaNumer, NrTelefonu, Email) values
(14444, 'Tomek',     	'Nowak',     	'Wrocław',        	'22-333',    	'Prosta 5',         121212131, 'tomek@gmail.com'),
(25555,	'Anna',      	'Kowalska',  	'Legnica',        	'44-556',    	'Wrocławska 10/4',  458123654, NULL),
(36666,	'Barbara',   	'Stec',      	'Poznań',         	'77-111',    	'Kręta 10/6',       451478963, NULL),
(47777,	'Aleksandra',	'Wesoła',    	'Koluszki',       	'23-567',    	'Sucha 16',         489123745, 'aleksandra@o2.pl'),
(45668, 'Wacław',		'Jasionek',		'Warszawa',			'00-220',		'Poznańska 2',	454643215, 'waclaw@gmail.com'),
(59631, 'Maria',		'Kulik',		'Żórawina',			'50-220',		'Tyrmanda 5',		645686686, NULL),
(74513, 'Iga',			'Gałat',		'Wałbrzych',		'10-220',		'Trawowa 5/2',		996554788, 'iga@o2.pl'),
(96410, 'Natalia',		'Bednarek',		'Wrocław',			'51-220',		'Mińska 7',		787897898, 'natalia@edukacja.wroc.pl'),
(98874, 'Mirek',		'Jasionek',		'Wrocław',			'55-220',		'Bukowa 10B',		123454877, 'mirek@mirek.pl');

create table Poradnia (
	PoradniaID int not null primary key,
	NazwaPoradni nchar(20) not null,
	SpecjalizacjaID int not null,
	NrPokoju nchar(20) not null,
	constraint FK_Poradnia_Specjalizacja foreign key (SpecjalizacjaID)
    references Specjalizacja(SpecjalizacjaID)
);

insert into Poradnia(PoradniaID, NazwaPoradni, SpecjalizacjaID, NrPokoju) values
(1,	'Ortopedyczna',        	1,	115),
(2,	'Neurologiczna',       	2,	2),
(3,	'Gastrologiczna',      	3,	15),
(4,	'Kardiologiczna',      	4,	101),
(5,	'Dermatologiczna',     	5,	6),
(6,	'Podologiczna',     	6,	16),
(7,	'Psychologiczna',     	7,	20),
(8,	'Internistyczna',     	8,	1);

create table Wizyta (
	WizytaID int not null primary key,
	LekarzPESEL int not null,
	PoradniaID int not null,
	DataWizyty date not null,
	PacjentPESEL int  not null,
	Status nchar(15) not null,
	constraint FK_Wizyta_Lekarz foreign key (LekarzPESEL)
    references Lekarz(PESEL),
	constraint FK_Wizyta_Pacjent foreign key (PacjentPESEL)
    references Pacjent(PESEL)
);

insert into Wizyta(WizytaID, LekarzPESEL, PoradniaID, DataWizyty, PacjentPESEL, Status) values
(1,	 11111,	2,	'2023-02-02',	14444,	'Zaliczona'),    
(2,	 12342,	1,	'2023-12-12',	25555,	'Zaliczona'), 
(3,	 22223,	3,	'2023-12-10',	36666,	'Zaliczona'),  
(4,	 22223,	4,	'2023-12-12',	25555,	'Zaliczona'),
(5,	 33334,	5,	'2023-01-11',	74513,	'Zaliczona'), 
(6,	 33117,	6,	'2023-06-12',	36666,	'Zaliczona'), 
(7,	 44886,	7,	'2022-09-02',	96410,	'Zaliczona'),
(8,	 56565,	8,	'2020-02-02',	47777,	'Odwołana'), 
(9,	 12342,	1,	'2022-03-02',	47777,	'Odwołana'), 
(10, 12342,	1,	'2026-04-02',	96410,	'Zaplanowana'), 
(11, 11111,	2,	'2019-09-01',	59631,	'Zaliczona'), 
(12, 33334,	5,	'2021-01-12',	98874,	'Odwołana'),
(13, 22223,	3,	'2023-01-02',	74513,	'Zaplanowana'),
(14, 22223,	4,	'2021-01-22',	98874,	'Odwołana'),
(15, 33117,	6,	'2022-08-12',	36666,	'Zaplanowana'),
(16, 65479,	7,	'2023-11-02',	14444,	'Zaliczona');

create table Recepta (
	ReceptaID int not null primary key,
	WizytaID int not null,
	constraint FK_Recepta_Wizyta foreign key (WizytaID)
    references Wizyta(WizytaID)
);

insert into Recepta(ReceptaID, WizytaID) values
(1,	2),
(2,	1),
(3,	3),
(4,	4),
(5, 16),
(6, 11),
(7, 6),
(8, 7),
(9, 5);

create table ReceptaLek (
	ReceptaID int not null,
	LekID int not null,
	constraint FK_ReceptaLek_Recepta foreign key (ReceptaID)
    references Recepta(ReceptaID),
	constraint FK_ReceptaLek_Leki foreign key (LekID)
    references Leki(LekID)

);

insert into ReceptaLek(ReceptaID, LekID) values
(1, 1),
(1,	2),
(2,	1),
(3,	4),
(3,	1),
(4, 8),
(5, 1),
(6, 1),
(6, 2),
(7, 3),
(8, 3),
(9, 1);