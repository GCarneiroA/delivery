

CREATE TABLE IF NOT EXISTS user(  
    id int NOT NULL primary key AUTO_INCREMENT comment 'primary key',
    created_time DATETIME COMMENT 'created time',
    updated_time DATETIME COMMENT 'updated time',
    username varchar(20) comment 'user name',
    password varchar(45) comment 'user password',
    email varchar(50) comment 'user email'
) default charset utf8 comment '';

