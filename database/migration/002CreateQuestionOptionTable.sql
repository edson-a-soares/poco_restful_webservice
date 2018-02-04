CREATE TABLE question_option (
    option_id       VARCHAR(36)  NOT NULL,
    question_id     VARCHAR(36)  NOT NULL,
    option_text     VARCHAR(120) NOT NULL,
    created_at      DATETIME     NOT NULL,
    last_updated_at DATETIME     NOT NULL,
    position_number INT,

    PRIMARY KEY (option_id),
    FOREIGN KEY (question_id)
        REFERENCES question(question_id)
        ON DELETE CASCADE
);

--//@UNDO

DROP TABLE question_option;
