CREATE TABLE question(
    question_id             VARCHAR(36)  NOT NULL,
    question_label          VARCHAR(50)  NULL,
    question_text           VARCHAR(200) NOT NULL,
    created_at              DATETIME     NOT NULL,
    last_updated_at         DATETIME     NOT NULL,
    starts_at               DATETIME     NOT NULL,
    ends_at                 DATETIME     NOT NULL,
    details                 VARCHAR(400) NULL,

    PRIMARY KEY (question_id)
);

--//@UNDO

DROP TABLE question;
