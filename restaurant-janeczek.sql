-- Autor: CJ
-- Datum: 2014/26/09
-- Zweck: Musterloesung fuer "Stored Routines"

\c template1
DROP DATABASE restaurant;
CREATE DATABASE restaurant;
\c restaurant

-- DROP TABLE IF EXISTS kellner CASCADE;
CREATE TABLE kellner (
             knr         INTEGER,
             name        VARCHAR(255),
             PRIMARY KEY (knr)
             );

INSERT INTO kellner VALUES (1, 'Kellner1');
INSERT INTO kellner VALUES (2, 'Kellner2');
INSERT INTO kellner VALUES (3, 'Kellner3');

-- DROP TABLE IF EXISTS speise CASCADE;
CREATE TABLE speise (
             snr         INTEGER,
             bezeichnung VARCHAR(255),
             preis       DECIMAL(6,2),
             PRIMARY KEY (snr)
             );

INSERT INTO speise VALUES (1, 'Heisse Liebe',         3);
INSERT INTO speise VALUES (2, 'Schoko Palatschinken', 4);
INSERT INTO speise VALUES (3, 'Pute gebacken',        7);
INSERT INTO speise VALUES (4, 'Pute natur',           8);
INSERT INTO speise VALUES (5, 'Puten-Cordon',         9);
INSERT INTO speise VALUES (6, 'Menue fuer 2',        15);
INSERT INTO speise VALUES (7, 'Menue fuer 3',        19);
INSERT INTO speise VALUES (8, 'Menue fuer 4',        22);

-- DROP TABLE IF EXISTS rechnung CASCADE;
CREATE TABLE rechnung (
             rnr         INTEGER,
             datum       DATE,
             tisch       SMALLINT,
             status      CHAR(8),
             knr         INTEGER,
             PRIMARY KEY (rnr),
             FOREIGN KEY (knr) REFERENCES kellner (knr)
                               ON UPDATE CASCADE ON DELETE CASCADE
             );

INSERT INTO rechnung VALUES (1, '2013-03-07', 1, 'bezahlt', 1);
INSERT INTO rechnung VALUES (2, '2013-03-07', 2, 'offen', 2);
INSERT INTO rechnung VALUES (3, '2013-03-07', 1, 'gedruckt', 3);
INSERT INTO rechnung VALUES (4, '2013-03-07', 1, 'gedruckt', 1);
INSERT INTO rechnung VALUES (5, '2013-03-07', 1, 'bezahlt', 1);
INSERT INTO rechnung VALUES (6, '2013-03-07', 2, 'offen', 2);

-- DROP TABLE IF EXISTS bestellung CASCADE;
CREATE TABLE bestellung (
             anzahl      SMALLINT,
             rnr         INTEGER,
             snr         INTEGER,
             PRIMARY KEY (rnr, snr),
             FOREIGN KEY (rnr) REFERENCES rechnung (rnr)
                               ON UPDATE CASCADE ON DELETE CASCADE,
             FOREIGN KEY (snr) REFERENCES speise (snr)
                               ON UPDATE CASCADE ON DELETE CASCADE
             );

INSERT INTO bestellung VALUES (9, 1, 1);
INSERT INTO bestellung VALUES (1, 1, 4);
INSERT INTO bestellung VALUES (1, 1, 5);
INSERT INTO bestellung VALUES (1, 2, 7);
INSERT INTO bestellung VALUES (1, 3, 8);
INSERT INTO bestellung VALUES (9, 4, 1);
INSERT INTO bestellung VALUES (9, 5, 1);
INSERT INTO bestellung VALUES (9, 6, 2);

-- ABGABE ÜBUNG 1 DDL ERGÄNZUNG

-- SELECT * FROM speise;

-- -- PREIS RUNDEN, SODASS .99er PREISE

-- CREATE FUNCTION preis99() RETURNS VOID AS '
-- 	UPDATE speise SET preis = trunc(preis)+0.99;' LANGUAGE SQL;
-- SELECT preis99();
-- SELECT * FROM speise;

-- -- RECHNUNGEN, WELCHE NICHT BESTELLT WURDEN, SOLLEN GELOESCHT WERDEN
-- -- DELETE FROM rechnung r INNER JOIN bestellung b ON r.rnr=b.rnr WHERE r.rnr IS NULL; does not work? martinides fragen!
-- CREATE FUNCTION loescheRechnung() RETURNS VOID AS '
-- 	DELETE FROM rechnung WHERE rnr NOT IN(SELECT rnr FROM bestellung);' LANGUAGE SQL;

-- INSERT INTO rechnung VALUES(7,'2014-12-05',2,'offen',3);
-- SELECT * FROM rechnung;
-- SELECT loescheRechnung();
-- SELECT * FROM rechnung;

-- CREATE FUNCTION preiserhoehung(INTEGER) RETURNS VOID AS 'UPDATE speise SET preis = preis * (100 + $1) / 100;' LANGUAGE SQL;
-- SELECT * FROM speise;
-- SELECT preiserhoehung(10);
-- SELECT * FROM speise;

CREATE FUNCTION preiserhoehung(INTEGER, INTEGER, NUMERIC) RETURNS VOID AS 'UPDATE speise SET preis = preis * (100 + $2)/100 WHERE preis >= $3; 
                                                                  UPDATE speise SET preis = preis + $1 WHERE preis <= $3;' LANGUAGE SQL;

SELECT * FROM speise;
SELECT preiserhoehung(1,5,(SELECT AVG(preis) FROM speise));
SELECT * FROM speise;