CREATE TABLE changelog (
  change_number INT(11)       NOT NULL,
  complete_dt   TIMESTAMP     NOT NULL,
  applied_by    VARCHAR(100)  NOT NULL,
  description   VARCHAR(500)  NOT NULL
);

ALTER TABLE changelog ADD CONSTRAINT pk_changelog
PRIMARY KEY (change_number);