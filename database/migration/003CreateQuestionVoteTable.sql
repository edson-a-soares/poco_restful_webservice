CREATE TABLE question_vote (
    question_id     VARCHAR(36) NOT NULL,
    option_id       VARCHAR(36) NOT NULL,
    created_at      DATETIME    NOT NULL,

    INDEX(option_id),
    INDEX(question_id),
    FOREIGN KEY(question_id)
        REFERENCES question(question_id)
        ON DELETE CASCADE,
    FOREIGN KEY(option_id)
        REFERENCES question_option(option_id)
        ON DELETE CASCADE
);

--//@UNDO

DROP TABLE question_vote;
