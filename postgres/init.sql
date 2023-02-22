--CREATE database measurements;
\c measurements;

CREATE TABLE IF NOT EXISTS dht22 (
id SERIAL PRIMARY KEY,
timestamp TIMESTAMP NOT NULL,
payload TEXT NOT NULL
);

GRANT SELECT ON dht22 TO postgres;
