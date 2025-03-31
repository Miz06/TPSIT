-- Creazione del database DB_GameShop
CREATE DATABASE DB_GameShop;

-- Creazione delle tabelle
CREATE TABLE DB_GameShop.users (
                                   email VARCHAR(30) PRIMARY KEY,
                                   name VARCHAR(30),
                                   password VARCHAR(255)
);

CREATE TABLE DB_GameShop.types(
                                  description VARCHAR(30) PRIMARY KEY
);

CREATE TABLE DB_GameShop.games (
                                   title VARCHAR(30) PRIMARY KEY,
                                   type VARCHAR(30),
                                   text VARCHAR(255),
                                   image VARCHAR(255),
                                   price FLOAT,
                                   edition_year INT,
                                   FOREIGN KEY (type) REFERENCES DB_GameShop.types(description)
);

CREATE TABLE DB_GameShop.editions(
                                     edition_year INT PRIMARY KEY
);

CREATE TABLE DB_GameShop.buy(
                                quantity INT,
                                customer_email VARCHAR(30),
                                date DATE DEFAULT CURRENT_DATE,
                                time TIME DEFAULT CURRENT_TIME,
                                game_title VARCHAR(30),
                                edition_year int,
                                PRIMARY KEY (customer_email, date, time),
                                FOREIGN KEY (customer_email) REFERENCES DB_GameShop.users(email),
                                FOREIGN KEY (game_title) REFERENCES DB_GameShop.games(title),
                                foreign key (edition_year) references db_GameShop.editions(edition_year)
);

CREATE TABLE DB_GameShop.having(
                                   edition_year INT,
                                   title VARCHAR(30),
                                   FOREIGN KEY (edition_year) REFERENCES DB_GameShop.editions(edition_year),
                                   FOREIGN KEY(title) REFERENCES DB_GameShop.games(title),
                                   PRIMARY KEY(edition_year, title)
);

CREATE TABLE DB_GameShop.save(
                                 title VARCHAR(30),
                                 edition_year INT,
                                 email VARCHAR(30),
                                 quantity int,
                                 FOREIGN KEY (title, edition_year) REFERENCES DB_GameShop.having(title, edition_year),
                                 FOREIGN KEY (email) REFERENCES DB_GameShop.users(email),
                                 PRIMARY KEY(title, edition_year, email)
);

-- Inserimento tipi di gioco
INSERT INTO DB_GameShop.types (description) VALUES
                                                ('Sandbox'),
                                                ('Sparatutto'),
                                                ('Avventura'),
                                                ('Battle Royale'),
                                                ('RPG d\'azione'),
('Platform'),
('Open World'),
('Azione/Avventura'),
('Sport');

-- Inserimento giochi
INSERT INTO DB_GameShop.games (title, type, text, image, price) VALUES
('Minecraft', 'Sandbox', 'Minecraft è un gioco sandbox...', '../references/images/minecraft.jpg', 24.99),
('Call of Duty', 'Sparatutto', 'Call of Duty è uno dei più iconici sparatutto...', '../references/images/cod.jpg', 59.99),
('The Legend of Zelda', 'Avventura', 'The Legend of Zelda è una delle saghe più celebri dei videogiochi...', '../references/images/Zelda.jpg', 49.99),
('Fortnite', 'Battle Royale', 'Fortnite è un gioco battle royale molto popolare...', '../references/images/fortnite.jpg', 0.00),
('Elden Ring', 'RPG d\'azione', 'Elden Ring è un RPG d\'azione sviluppato da FromSoftware...', '../references/images/elden_ring.jpg', 69.99),
('Super Mario Bros', 'Platform', 'Super Mario Bros è il classico platform di Nintendo...', '../references/images/super_mario_bros.jpg', 39.99),
('Grand Theft Auto V', 'Open World', 'Grand Theft Auto V è un open world con una storia coinvolgente...', '../references/images/gta_v.jpg', 29.99),
('Red Dead Redemption 2', 'Azione/Avventura', 'Red Dead Redemption 2 è un epico gioco d\'azione ambientato nel Far West...', '../references/images/red_dead_redemption_2.jpg', 49.99),
                                                ('EA Sports FC 24', 'Sport', 'EA Sports FC 24 è il nuovo capitolo della famosa serie di simulazione calcistica...', '../references/images/fc_24.jpg', 69.99);

-- Inserimento edizioni
INSERT INTO DB_GameShop.editions (edition_year) VALUES
                                                    (2011), (2003), (1986), (2017), (2022), (1985), (2013), (2018), (2024), (2015), (2009), (1998), (2020), (2021), (1996), (2010), (2019);

-- Associazione giochi con edizioni
INSERT INTO DB_GameShop.having (edition_year, title) VALUES
                                                         (2011, 'Minecraft'),
                                                         (2003, 'Call of Duty'),
                                                         (1986, 'The Legend of Zelda'),
                                                         (2017, 'Fortnite'),
                                                         (2022, 'Elden Ring'),
                                                         (1985, 'Super Mario Bros'),
                                                         (2013, 'Grand Theft Auto V'),
                                                         (2018, 'Red Dead Redemption 2'),
                                                         (2024, 'EA Sports FC 24'),
                                                         (2015, 'Minecraft'),
                                                         (2009, 'Call of Duty'),
                                                         (1998, 'The Legend of Zelda'),
                                                         (2020, 'Fortnite'),
                                                         (2021, 'Elden Ring'),
                                                         (1996, 'Super Mario Bros'),
                                                         (2010, 'Grand Theft Auto V'),
                                                         (2019, 'Red Dead Redemption 2');
