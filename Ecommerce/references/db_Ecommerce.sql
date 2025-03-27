create database db_Ecommerce;

create table db_Ecommerce.users (
                                    email varchar(30) primary key,
                                    name varchar(30),
                                    password varchar(255)
);

create table db_Ecommerce.types(
                                   description varchar(30) primary key
);

create table db_Ecommerce.games (
                                    title varchar(30) primary key,
                                    type varchar(30),
                                    text varchar(30),
                                    image varchar(30),
                                    price float,
                                    foreign key (type) references db_Ecommerce.types(description)
);

create table db_Ecommerce.buy(
                                 quantity int,
                                 customer_email varchar(30),
                                 date date DEFAULT CURRENT_DATE,
                                 time time DEFAULT CURRENT_TIME,
                                 game_title varchar(30),
                                 primary key (customer_email, date, time),
                                 foreign key (customer_email) references db_Ecommerce.users(email),
                                 foreign key (game_title) references db_Ecommerce.games(title)
);

create table db_Ecommerce.editions(
                                      year int primary key
);

create table db_Ecommerce.having(
                                    year int,
                                    title varchar(30),
                                    foreign key (year) references db_Ecommerce.editions(year),
                                    foreign key(title) references db_Ecommerce.games(title),
                                    primary key(YEAR, title)
);