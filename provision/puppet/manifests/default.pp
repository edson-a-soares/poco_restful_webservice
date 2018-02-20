
    include environment
    include environment::configure

    include gcc
    include gcc::install

    include poco
    include poco::install

    include cmake
    include cmake::install

    include gtest
    include gtest::install

    include mysql
    include mysql::server

    mysql::create_user { "create-mysql-user":
        username => $environment::configure::mysql_username,
        password => $environment::configure::mysql_password
    }
