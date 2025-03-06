create database db_Ecommerce;
use db_Ecommerce;

create table db_Ecommerce.user (
	user_email varchar(30) primary key,
	username varchar(30),
	name varchar(30),
	surname varchar(30)
);

create table db_Ecommerce.type(
	description varchar(30) primary key
);

create table db_Ecommerce.game (
	game_title varchar(30) primary key,
	game_type varchar(30),
	text varchar(30),
	image varchar(30),
	price float,
	foreign key (game_type) references db_Ecommerce.type(description)
);

create table db_Ecommerce.buy(
	quantity int,
	email varchar(30),
	title varchar(30),
	primary key (email, title),
	foreign key (email) references db_Ecommerce.user(user_email),
	foreign key (title) references db_Ecommerce.game(game_title)
);
