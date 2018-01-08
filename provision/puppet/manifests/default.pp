
    include environment
    include environment::configure

    include mysql
    include mysql::server

    include gcc
    include gcc::install

    include poco
    include poco::install

    include cmake
    include cmake::install

    mysql::create_user { "create-mysql-user":
      username => $environment::configure::mysql_username,
      password => $environment::configure::mysql_password
    } ->

    Class[ "environment::configure" ]   ->
    Class[ "gcc::install" ]             ->
    Class[ "poco::install" ]            ->
    Class[ "cmake::install" ]
